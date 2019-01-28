import sys

while 1:
    c = sys.stdin.read(1)
    if len(c) == 0:
        break

    event = ord(c)
    print "%s%s" % (chr(0x50 | (event >> 4)), chr(0x50 | (event & 0x0F)))
