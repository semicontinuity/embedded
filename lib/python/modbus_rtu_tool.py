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
# ./modbus_rtu_tool read coils <ADDRESS> <COUNT>
# ./modbus_rtu_tool read inputs <ADDRESS> <COUNT>
# ./modbus_rtu_tool read holding-registers <ADDRESS> <COUNT>
# ./modbus_rtu_tool read input-registers <ADDRESS> <COUNT>
# ./modbus_rtu_tool write coil <ADDRESS> <VALUE>
# ./modbus_rtu_tool write register <ADDRESS> <VALUE>
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
#   OF:             output format (yaml or json)
#
# Watching device:
# watch -d -n 0.2 -t --color 'OF=json PROXY_PORT=8000 DEVICE_ADDRESS=2 python3 -m modbus_rtu_tool read all modbus-device-spec.yaml | python3 -m datatools.json.json2ansi'
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
EXIT_CODE_INVALID_ADDRESS = 41
EXIT_CODE_INVALID_COUNT = 42
EXIT_CODE_INVALID_COIL_VALUE = 43
EXIT_CODE_INVALID_REGISTER_VALUE = 44

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


def get_uint16(s, error_message, exit_code, max_value=65535) -> int:
    try:
        value = int(s)
        if value >= 0 and value < max_value:
            return value
        else:
            raise ValueError()
    except:
        print(f"{error_message}: {value}", file=sys.stderr)
        sys.exit(exit_code)


def get_coil_address(s) -> int:
    return get_uint16(s, f"Coil address is invalid", EXIT_CODE_INVALID_ADDRESS)


def get_coil_count(s) -> int:
    return get_uint16(s, f"Coil count is invalid", EXIT_CODE_INVALID_COUNT)


def get_discrete_input_address(s) -> int:
    return get_uint16(s, f"Discrete input address is invalid", EXIT_CODE_INVALID_ADDRESS)


def get_discrete_input_count(s) -> int:
    return get_uint16(s, f"Discrete input count is invalid", EXIT_CODE_INVALID_COUNT)


def get_holding_register_address(s) -> int:
    return get_uint16(s, f"Holding register address is invalid", EXIT_CODE_INVALID_ADDRESS)


def get_holding_register_count(s) -> int:
    return get_uint16(s, f"Holding register count is invalid", EXIT_CODE_INVALID_COUNT, 128)


def get_input_register_address(s) -> int:
    return get_uint16(s, f"Input register address is invalid", EXIT_CODE_INVALID_ADDRESS)


def get_input_register_count(s) -> int:
    return get_uint16(s, f"Input register count is invalid", EXIT_CODE_INVALID_COUNT, 128)


def get_coil_value(s) -> int:
    if s == '1':
        return 1
    elif s == '0':
        return 0
    else:
        print(f"Coil value is invalid: {s}", file=sys.stderr)
        sys.exit(EXIT_CODE_INVALID_COIL_VALUE)


def get_register_value(s) -> int:
    return get_uint16(s, f"Register value is invalid", EXIT_CODE_INVALID_REGISTER_VALUE)


def get_spec(spec_file_name: str):
    with open(spec_file_name, "r") as stream:
        try:
            return yaml.safe_load(stream)
        except yaml.YAMLError as exc:
            exit(EXIT_CODE_INVALID_SPEC)


def usage():
    print("Usage:", file=sys.stderr)
    print("modbus_rtu_tool <read|write> <input|inputs|coil|coils|holding-registers>", file=sys.stderr)
    sys.exit(EXIT_CODE_SYNTAX_ERROR)

# ==============================================================================

MF_READ_COILS = 1
MF_READ_DISCRETE_INPUTS = 2
MF_READ_HOLDING_REGISTERS = 3
MF_READ_INPUT_REGISTERS = 4
MF_WRITE_SINGLE_COIL = 5
MF_WRITE_SINGLE_REGISTER = 6
MF_WRITE_MULTIPLE_COILS = 15
MF_WRITE_MULTIPLE_REGISTERS = 16
MF_READ_FILE_RECORD = 20
MF_WRITE_FILE_RECORD = 21
MF_READ_FIFO_QUEUE = 24


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

def read_entities(proxy_port: int, device_address: int, address: int, count: int, func: int):
    data = bytearray(8)
    data[0] = device_address
    data[1] = func
    data[2] = address >> 8
    data[3] = address & 0xFF
    data[4] = count >> 8
    data[5] = count & 0xFF

    crc = crc16(0xFFFF, data, 6)

    data[6] = crc & 0xFF
    data[7] = crc >> 8

    return exchange(data)


def read_bit_data(proxy_port: int, device_address: int, address: int, count: int, func: int, ans: List[int]):
    data = bytearray(8)
    data[0] = device_address
    data[1] = func
    data[2] = address >> 8
    data[3] = address & 0xFF
    data[4] = count >> 8
    data[5] = count & 0xFF

    crc = crc16(0xFFFF, data, 6)

    data[6] = crc & 0xFF
    data[7] = crc >> 8

    result = exchange(data)
    payload_size = ((count + 7) // 8)
    expected_response_length = 5 + payload_size
    # print(f"Response payload size: {result[2]} bytes", file=sys.stderr)
    # sys.stderr.write(repr(result))
    print(file=sys.stderr)

    if len(result) != expected_response_length:
        print(f"Unexpected length of response: for {count} bits, expected response size is {expected_response_length}", file=sys.stderr)
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE
    if result[0] != data[0]:
        print("Answer from another device", file=sys.stderr)
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE
    if result[1] == 0x80 | data[1]:
        exception_code = result[2]
        if exception_code == 1:
            print('MODBUS_EXCEPTION__ILLEGAL_FUNCTION', file=sys.stderr)
        elif exception_code == 2:
            print('MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS', file=sys.stderr)
        elif exception_code == 3:
            print('MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE', file=sys.stderr)
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE
    if result[1] != data[1]:
        print("Unexpected value in 'function' field", file=sys.stderr)
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE

    # Check CRC

    bits = result[3:-2]
    for i in range(count):
        b = bits[i >> 3]
        ans.append((b >> (i % 8)) & 1)
    return EXIT_CODE_OK



def decode_register_data(response, device_address, func, count, ans: List[int]):
    if len(response) < 2:
        print(f"Response is too short", file=sys.stderr)
        sys.stderr.write(repr(response))
        return EXIT_CODE_FAILURE
    if response[0] != device_address:
        print("Answer from another device", file=sys.stderr)
        sys.stderr.write(repr(response))
        return EXIT_CODE_FAILURE
    if response[1] == 0x80 | func:
        exception_code = response[2]
        if exception_code == 1:
            print('MODBUS_EXCEPTION__ILLEGAL_FUNCTION', file=sys.stderr)
        elif exception_code == 2:
            print('MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS', file=sys.stderr)
        elif exception_code == 3:
            print('MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE', file=sys.stderr)
        sys.stderr.write(repr(response))
        return EXIT_CODE_FAILURE
    if response[1] != func:
        print("Unexpected value in 'function' field", file=sys.stderr)
        sys.stderr.write(repr(response))
        return EXIT_CODE_FAILURE

    payload_size = count*2
    expected_response_length = 5 + payload_size
    if len(response) != expected_response_length:
        print(f"Unexpected length of response: for {count} registers, expected response size is {expected_response_length}", file=sys.stderr)
        sys.stderr.write(repr(response))
        return EXIT_CODE_FAILURE

    # Check CRC

    if os.environ.get('BYTES') == '1':
        for i in range(count):
            hi = response[3 + 2 * i]
            ans.append(hi)
            lo = response[4 + 2 * i]
            ans.append(lo)
    else:
        for i in range(count):
            hi = response[3 + 2 * i]
            lo = response[4 + 2 * i]
            ans.append((hi << 8) | lo)

    # for i in range(count):
    #     hi = response[3 + 2 * i]
    #     lo = response[4 + 2 * i]
    #     ans.append((hi << 8) | lo)

    return EXIT_CODE_OK


def read_coils(proxy_port: int, device_address: int, address: int, count: int, ans: List[int]):
    """
    address: coil address (0-based)
    returns process exit code
    """
    # data, result = read_entities(proxy_port, device_address, address, count, MF_READ_COIL)
    return read_bit_data(proxy_port, device_address, address, count, MF_READ_COILS, ans)


def read_discrete_inputs(proxy_port: int, device_address: int, address: int, count: int, ans: List[int]):
    """
    address: discrete input address (0-based)
    returns process exit code
    """
    return read_bit_data(proxy_port, device_address, address, count, MF_READ_DISCRETE_INPUTS, ans)


def read_holding_registers(proxy_port: int, device_address: int, address: int, count: int, ans: List[int]):
    """
    address: holding register address (0-based)
    returns process exit code
    """
    response = read_entities(proxy_port, device_address, address, count, MF_READ_HOLDING_REGISTERS)
    return decode_register_data(response, device_address, MF_READ_HOLDING_REGISTERS, count, ans)


def read_input_registers(proxy_port: int, device_address: int, address: int, count: int, ans: List[int]):
    """
    address: holding register address (0-based)
    returns process exit code
    """
    response = read_entities(proxy_port, device_address, address, count, MF_READ_INPUT_REGISTERS)
    return decode_register_data(response, device_address, MF_READ_INPUT_REGISTERS, count, ans)


def write_entity(proxy_port: int, device_address: int, address: int, vh: int, vl: int, function: int):
    """
    address: coil address (0-based)
    returns process exit code
    """
    data = bytearray(8)
    data[0] = device_address
    data[1] = function
    data[2] = address >> 8
    data[3] = address & 0xFF
    data[4] = vh
    data[5] = vl

    crc = crc16(0xFFFF, data, 6)

    data[6] = crc & 0xFF
    data[7] = crc >> 8

    # sys.stderr.write(repr(data))
    result = exchange(data)

    if result[0] != data[0]:
        print("Answer from another device", file=sys.stderr)
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE
    if result[1] == 0x80 | data[1]:
        exception_code = result[2]
        if exception_code == 1:
            print('MODBUS_EXCEPTION__ILLEGAL_FUNCTION', file=sys.stderr)
        elif exception_code == 2:
            print('MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS', file=sys.stderr)
        elif exception_code == 3:
            print('MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE', file=sys.stderr)
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE
    if result != data:
        sys.stderr.write(repr(result))
        return EXIT_CODE_FAILURE
    return EXIT_CODE_OK


def write_coil(proxy_port: int, device_address: int, address: int, value: int):
    """
    address: coil address (0-based)
    returns process exit code
    """
    return write_entity(proxy_port, device_address, address, 0x00 if value == 0 else 0xFF, 0x00, MF_WRITE_SINGLE_COIL)


def write_register(proxy_port: int, device_address: int, address: int, value: int):
    """
    address: register address (0-based)
    returns process exit code
    """
    return write_entity(proxy_port, device_address, address, value >> 8, value & 0xFF, MF_WRITE_SINGLE_REGISTER)

# ==============================================================================

read_f = {
    'coils': read_coils,
    'discrete_inputs': read_discrete_inputs,
    'holding_registers': read_holding_registers,
    'input_registers': read_input_registers,
}

def read_blocks(proxy_port: int, device_address: int, all_specs, what, read_f):
    blocks = all_specs.get(what)
    if blocks:
        for block in blocks:
            contents = block['contents']
            values = []
            code = read_f(proxy_port, device_address, block['address'], len(contents), values)
            if code != EXIT_CODE_OK: return code
            for i, spec in enumerate(contents):
                spec['value'] = values[i]

def read_all(proxy_port: int, device_address: int, all_specs, what: List[str]):
    for w in what:
        read_blocks(proxy_port, device_address, all_specs, w, read_f[w])
    for w in list(read_f):
        if w not in what and w in all_specs:
            del all_specs[w]
    return EXIT_CODE_OK

# ==============================================================================


def main():
    proxy_port = get_proxy_port()
    device_address = get_device_address()

    if len(sys.argv) < 3 or not (sys.argv[1] == 'read' or sys.argv[1] == 'write'):
        usage()
    elif sys.argv[1] == 'read' and sys.argv[2] == 'coils' and len(sys.argv) == 5:
        if len(sys.argv) != 5:
            print("Usage:", file=sys.stderr)
            print("modbus_rtu_tool read coils <address> <count>", file=sys.stderr)
            sys.exit(EXIT_CODE_SYNTAX_ERROR)
        ans = []
        result = read_coils(
            proxy_port=proxy_port,
            device_address=device_address,
            address=get_coil_address(sys.argv[3]),
            count=get_coil_count(sys.argv[4]),
            ans=ans
        )
        if result == EXIT_CODE_OK:
            print(ans)
        else:
            exit(result)
    elif sys.argv[1] == 'read' and sys.argv[2] == 'inputs' and len(sys.argv) == 5:
        if len(sys.argv) != 5:
            print("Usage:", file=sys.stderr)
            print("modbus_rtu_tool read inputs <address> <count>", file=sys.stderr)
            sys.exit(EXIT_CODE_SYNTAX_ERROR)
        ans = []
        result = read_discrete_inputs(
            proxy_port=proxy_port,
            device_address=device_address,
            address=get_discrete_input_address(sys.argv[3]),
            count=get_discrete_input_count(sys.argv[4]),
            ans=ans
        )
        if result == EXIT_CODE_OK:
            print(ans)
        else:
            exit(result)
    elif sys.argv[1] == 'read' and sys.argv[2] == 'holding-registers' and len(sys.argv) == 5:
        if len(sys.argv) != 5:
            print("Usage:", file=sys.stderr)
            print("modbus_rtu_tool read holding-registers <address> <count>", file=sys.stderr)
            sys.exit(EXIT_CODE_SYNTAX_ERROR)
        ans = []
        result = read_holding_registers(
            proxy_port=proxy_port,
            device_address=device_address,
            address=get_holding_register_address(sys.argv[3]),
            count=get_holding_register_count(sys.argv[4]),
            ans=ans
        )
        if result == EXIT_CODE_OK:
            print(ans)
        else:
            exit(result)
    elif sys.argv[1] == 'read' and sys.argv[2] == 'input-registers' and len(sys.argv) == 5:
        if len(sys.argv) != 5:
            print("Usage:", file=sys.stderr)
            print("modbus_rtu_tool read input-registers <address> <count>", file=sys.stderr)
            sys.exit(EXIT_CODE_SYNTAX_ERROR)
        ans = []
        result = read_input_registers(
            proxy_port=proxy_port,
            device_address=device_address,
            address=get_input_register_address(sys.argv[3]),
            count=get_input_register_count(sys.argv[4]),
            ans=ans
        )
        if result == EXIT_CODE_OK:
            print(ans)
        else:
            exit(result)
    elif sys.argv[1] == 'read':
        if len(sys.argv) != 4:
            print("Usage:", file=sys.stderr)
            print("modbus_rtu_tool read [all|category,category..] <SPEC.yaml>", file=sys.stderr)
            sys.exit(EXIT_CODE_SYNTAX_ERROR)
        all_specs = get_spec(sys.argv[3])
        what = list(read_f) if sys.argv[2] == 'all' else sys.argv[2].split(',')
        result = read_all(
            proxy_port=proxy_port,
            device_address=device_address,
            all_specs=all_specs,
            what=what
        )
        if result == EXIT_CODE_OK:
            print(serialize(all_specs))
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
            address=get_coil_address(sys.argv[3]),
            value=get_coil_value(sys.argv[4])
        )
        exit(EXIT_CODE_OK if result else EXIT_CODE_FAILURE)
    elif sys.argv[1] == 'write' and sys.argv[2] == 'register':
        if len(sys.argv) != 5:
            print("Usage:", file=sys.stderr)
            print("modbus_rtu_tool write register <address> <value>", file=sys.stderr)
            sys.exit(EXIT_CODE_SYNTAX_ERROR)
        result = write_register(
            proxy_port=proxy_port,
            device_address=device_address,
            address=get_coil_address(sys.argv[3]),
            value=get_register_value(sys.argv[4])
        )
        exit(EXIT_CODE_OK if result else EXIT_CODE_FAILURE)
    else:
        usage()


if __name__ == '__main__':
    main()
