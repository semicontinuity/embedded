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


def main():
        max_length = 0
        while True:
            line = sys.stdin.readline()
            if not line:
                stdout_print(' '*max_length, end='\r')
                break

            l = ''.join('%-8s' % item for item in line.strip().split('\t'))
            if len(l) > max_length:
                max_length = len(l)
            stdout_print(l + ' '*(max_length - len(l)) , end='\r')

if __name__ == "__main__":
    main()
