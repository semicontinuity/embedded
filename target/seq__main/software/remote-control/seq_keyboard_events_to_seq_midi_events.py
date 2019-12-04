#!/usr/bin/env python3
import sys
import json

def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)

def stdout_flush():
    sys.stdout.flush()

def stderr_print(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def with_tabs(s):
    return '\t'.join(s.split())


def run(mapping):
    while True:
        line = sys.stdin.readline()
        if not line: break

        event = line.strip()
        action = mapping.get(event)

        if action is None:
            continue

        stdout_print(action)
        stdout_flush()


def main():
    if len(sys.argv) < 2:
        sys.exit("Argument: 'json-with-mapping'")

    mapping = {with_tabs(k): with_tabs(v) for k, v in json.loads(sys.argv[1]).items()}
    run(mapping)


if __name__ == "__main__":
    main()
