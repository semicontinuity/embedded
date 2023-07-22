#!/usr/bin/python3
# ==============================================================================
# MODBUS RTU tool
#
# Works in pair with 'tcp_serial_redirect',
# that wraps serial port in a TCP socket.
# This might be necessary, when interfacing Arduino-type board
# via USB-to-serial converter.
# Opening USB serial port toggles DTR uncontrollably, which resets the board.
# So, before using this program, launch tcp_serial_redirect, e.g.:
#
# python3 -m tcp_serial_redirect -P 8000 /dev/ttyUSB0 4800
#
# Usage of modbus_rtu_tool:
#
# ./modbus_rtu_tool read coils <COIL> <COUNT>
# ./modbus_rtu_tool write coil <COIL> <VALUE>
#
# ./modbus_rtu_tool read all <SPEC FILE>
# Spec file is a YAML file with the folowing structure:
# ==============================================================================
# discrete_inputs:
#   -
#     address: 0
#     contents:
#       - { alias: DI_ALIAS_0 }
#       - { alias: DI_ALIAS_1 }
#       ...
#   -
#     address: 256
#     contents:
#       - { alias: DI_ALIAS_256 }
#       - { alias: DI_ALIAS_257 }
#       ...
# coils:
#   -
#     address: 0
#     contents:
#       - { alias: CO_ALIAS_0 }
#       ...
# input_registers:
# ...
# holding_registers:
# ...
# ==============================================================================
# After reading the data, the same YAML is returned,
# but with "value" field next to each "alias".
# ==============================================================================
#
# Environment variables:
#   PROXY_PORT:     port, on which tcp_serial_redirect is running on localhost
#   DEVICE_ADDRESS: address of MODBUS device to communicate with

# ==============================================================================
# Exit codes:
# ==============================================================================
EXIT_CODE_OK = 0
EXIT_CODE_FAILURE = 9

EXIT_CODE_UNSET_PROXY_PORT = 10
EXIT_CODE_INVALID_PROXY_PORT = 11
EXIT_CODE_UNSET_DEVICE_ADDRESS = 12
EXIT_CODE_INVALID_DEVICE_ADDRESS = 13
EXIT_CODE_INVALID_SPEC = 19

EXIT_CODE_SYNTAX_ERROR = 40
EXIT_CODE_INVALID_COIL_ADDRESS = 41
EXIT_CODE_INVALID_COIL_COUNT = 42
EXIT_CODE_INVALID_COIL_VALUE = 43
# ==============================================================================

import os
import sys
import yaml
import json

from crc16 import crc16
from typing import List

# ==============================================================================

def get_output_format():
    return os.environ.get('OF', 'yaml')


def serialize(o):
    if get_output_format() == 'yaml':
        return yaml.safe_dump(o)
    else:
        return json.dumps(o)


def get_proxy_port():
    proxy_port = os.environ.get('PROXY_PORT')
    if proxy_port == None:
        print("Proxy port is not set", file=sys.stderr)
        sys.exit(EXIT_CODE_UNSET_PROXY_PORT)

    try:
        proxy_port = int(proxy_port)
        if proxy_port < 1 or proxy_port > 65535:
            raise ValueError()
        return proxy_port
    except:
        print(f"Proxy port is invalid: {proxy_port}", file=sys.stderr)
        sys.exit(EXIT_CODE_INVALID_PROXY_PORT)


def get_device_address():
    device_address = os.environ.get('DEVICE_ADDRESS')
    if device_address == None:
        print("Device address is not set", file=sys.stderr)
        sys.exit(EXIT_CODE_UNSET_DEVICE_ADDRESS)

    try:
        device_address = int(device_address)
        if device_address < 1 or device_address > 247:
            raise ValueError()
        return device_address
    except:
        print(f"Device address is invalid: {device_address}", file=sys.stderr)
        sys.exit(EXIT_CODE_INVALID_DEVICE_ADDRESS)


def get_uint16(s, error_message, exit_code) -> int:
    try:
        value = int(s)
        if value >= 0 and value < 65536:
            return value
        else:
            raise ValueError()
    except:
        print(f"{error_message}: {value}", file=sys.stderr)
        sys.exit(exit_code)


def get_coil_address(s) -> int:
    return get_uint16(s, f"Coil address is invalid", EXIT_CODE_INVALID_COIL_ADDRESS)


def get_coil_count(s) -> int:
    return get_uint16(s, f"Coil count is invalid", EXIT_CODE_INVALID_COIL_COUNT)


def get_coil_value(s) -> int:
    if s == '1':
        return 1
    elif s == '0':
        return 0
    else:
        print(f"Coil value is invalid: {s}", file=sys.stderr)
        sys.exit(EXIT_CODE_INVALID_COIL_VALUE)


def get_spec(spec_file_name: str):
    with open(spec_file_name, "r") as stream:
        try:
            return yaml.safe_load(stream)
        except yaml.YAMLError as exc:
            exit(EXIT_CODE_INVALID_SPEC)


def usage():
    print("Usage:", file=sys.stderr)
    print("modbus_rtu_tool <read|write> <input|inputs|coil|coils|reg|regs>", file=sys.stderr)
    sys.exit(EXIT_CODE_SYNTAX_ERROR)

# ==============================================================================

MF_READ_COILS = 1
MF_WRITE_SINGLE_COIL = 5


def exchange(data):
    import os
    import socket
    import select
    port = os.environ.get('TCP_PORT', 8000)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("localhost", port))
    s.setblocking(0)

    s.sendall(data)

    result = bytearray()
    while True:
        inputready, outputready, exceptready = select.select([s], [], [], 0.1)
        if len(inputready) > 0:
            chunk = s.recv(4096)
            if len(chunk) == 0:
                break
            result += chunk
        else:
            break

    s.close()
    return result

# ==============================================================================

def read_coils(proxy_port: int, device_address: int, coil_address: int, coil_count: int, ans: List[int]):
    """
    coil_address: coil address (0-based)
    returns process exit code
    """
    data = bytearray(8)
    data[0] = device_address
    data[1] = MF_READ_COILS
    data[2] = coil_address >> 8
    data[3] = coil_address & 0xFF
    data[4] = coil_count >> 8
    data[5] = coil_count & 0xFF

    crc = crc16(0xFFFF, data, 6)

    data[6] = crc & 0xFF
    data[7] = crc >> 8

    result = exchange(data)

    if len(result) != 5 + ((coil_count + 7) // 8):
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE
    if result[0] != data[0]:
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE
    if result[1] != data[1]:
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE
    # Check CRC

    bits = result[3:-2]
    for i in range(coil_count):
        b = bits[i >> 3]
        ans.append((b >> (i % 8)) & 1)
    return EXIT_CODE_OK


def write_coil(proxy_port: int, device_address: int, coil_address: int, value: int):
    """
    coil_address: coil address (0-based)
    returns process exit code
    """
    data = bytearray(8)
    data[0] = device_address
    data[1] = MF_WRITE_SINGLE_COIL
    data[2] = coil_address >> 8
    data[3] = coil_address & 0xFF
    data[4] = 0x00 if value == 0 else 0xFF
    data[5] = 0x00

    crc = crc16(0xFFFF, data, 6)

    data[6] = crc & 0xFF
    data[7] = crc >> 8

    # sys.stderr.write(repr(data))
    result = exchange(data)
    if result != data:
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE
    return EXIT_CODE_OK

# ==============================================================================

def read_all(proxy_port: int, device_address: int, spec):
    coil_blocks = spec.get('coils')
    if coil_blocks:
        for block in coil_blocks:
            coil_specs = block['contents']
            coil_values = []
            code = read_coils(proxy_port, device_address, block['address'], len(coil_specs), coil_values)
            if code != EXIT_CODE_OK: return code
            for i, coil_spec in enumerate(coil_specs):
                coil_spec['value'] = coil_values[i]

    return EXIT_CODE_OK

# ==============================================================================


def main():
    proxy_port = get_proxy_port()
    device_address = get_device_address()

    if len(sys.argv) < 3 or not (sys.argv[1] == 'read' or sys.argv[1] == 'write'):
        usage()
    elif sys.argv[1] == 'read' and sys.argv[2] == 'all':
        if len(sys.argv) != 4:
            print("Usage:", file=sys.stderr)
            print("modbus_rtu_tool read all <SPEC.yaml>", file=sys.stderr)
            sys.exit(EXIT_CODE_SYNTAX_ERROR)
        spec = get_spec(sys.argv[3])
        result = read_all(
            proxy_port=proxy_port,
            device_address=device_address,
            spec=spec
        )
        if result == EXIT_CODE_OK:
            print(serialize(spec))
        else:
            exit(result)
    elif sys.argv[1] == 'read' and sys.argv[2] == 'coils':
        if len(sys.argv) != 5:
            print("Usage:", file=sys.stderr)
            print("modbus_rtu_tool read coils <address> <count>", file=sys.stderr)
            sys.exit(EXIT_CODE_SYNTAX_ERROR)
        ans = []
        result = read_coils(
            proxy_port=proxy_port,
            device_address=device_address,
            coil_address=get_coil_address(sys.argv[3]),
            coil_count=get_coil_count(sys.argv[4]),
            ans=ans
        )
        if result == EXIT_CODE_OK:
            print(ans)
        else:
            exit(result)
    elif sys.argv[1] == 'write' and sys.argv[2] == 'coil':
        if len(sys.argv) != 5:
            print("Usage:", file=sys.stderr)
            print("modbus_rtu_tool write coil <address> <value=0|1>", file=sys.stderr)
            sys.exit(EXIT_CODE_SYNTAX_ERROR)
        result = write_coil(
            proxy_port=proxy_port,
            device_address=device_address,
            coil_address=get_coil_address(sys.argv[3]),
            value=get_coil_value(sys.argv[4])
        )
        exit(EXIT_CODE_OK if result else EXIT_CODE_FAILURE)
    else:
        usage()


if __name__ == '__main__':
    main()
