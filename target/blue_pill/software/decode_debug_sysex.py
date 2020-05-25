#!/usr/bin/env python3
import sys
import json

def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)

def stdout_flush():
    sys.stdout.flush()

def stderr_print(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def stderr_flush():
    sys.stderr.flush()


def run(mapping):
    while True:
        line = sys.stdin.readline()
        if not line: break

        event = line.strip()
        stdout_print(event, end='')

        hex_numbers = event.split(" ")
        if len(hex_numbers) > 2 and hex_numbers[0] == "F0" and hex_numbers[-1] == "F7":
            param = mapping.get(hex_numbers[1])

            if param is not None:
                hex_digits = [int(i, 16) for i in hex_numbers[2:-1]]
                v = 0
                for d in hex_digits:
                    v = (v << 4) + d
                if len(hex_digits) == 0:
                    stdout_print('\t' + '\u001b[33;1m' + param + '\u001b[0m')
                else:
                    stdout_print('\t' + '\u001b[33m' + param + '\u001b[37m' + '=' + '\u001b[36m' + ("%0" + str(len(hex_digits)) + "X") % v + '\u001b[0m')
                stdout_flush()
                continue

        stdout_print()
        stdout_flush()


def main():
    if len(sys.argv) < 2:
        sys.exit("Argument: 'json-with-mapping'")

    mapping = {k:v for k, v in json.loads(sys.argv[1]).items()}
    run(mapping)


if __name__ == "__main__":
    main()
