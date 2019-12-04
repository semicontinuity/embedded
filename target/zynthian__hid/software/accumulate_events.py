#!/usr/bin/env python3
"""
Accepts stream of tab-separated recods with format
<source> <diff>
where source can be 0, 1, ...
<diff> will be summed for each source,
and the summary line with format
<sum0> <sum1> ... <sumN> 
will be printed
"""

import sys
import time
from threading import Thread, Event

def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)

def stdout_flush():
    sys.stdout.flush()

def stderr_print(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def main(columns):
        accumulated = {}
        while True:
            line = sys.stdin.readline()
            if not line: break

            l = line.strip()
            fields = l.split('\t')
            source = int(fields[0])
            diff = int(fields[1])
            if source in accumulated:
                accumulated[source] += diff
            else:
                accumulated[source] = diff

            result = []
            for c in range(columns):
                result.append(0 if c not in accumulated else accumulated[c])

            stdout_print(*tuple(result), sep='\t')
            stdout_flush()

if __name__ == "__main__":
    main(int(sys.argv[1]))
