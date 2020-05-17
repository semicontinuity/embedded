## Register allocations

|    |                                                                 |
|----|-----------------------------------------------------------------|
|  0 | compiler temp                                                   |
|  1 | compiler zero                                                   |
|  2 | allocated by compiler                                           |
|  3 | allocated by compiler                                           |
|  4 | allocated by compiler                                           |
|  5 | allocated by compiler                                           |
|  6 | allocated by compiler                                           |
|  7 | COMM_LEDS__HEADER__REG                                          |
|  8 | allocated by compiler                                           |
|  9 | allocated by compiler                                           |
| 10 | allocated by compiler                                           |
| 11 | KEYBOARD__PORT_B__PREVIOUS_STATE__REG                           |
| 12 | KEYBOARD__PORT_C__PREVIOUS_STATE__REG                           |
| 13 | KEYBOARD__PORT_D__PREVIOUS_STATE__REG                           |
| 14 | allocated by compiler                                           |
| 15 | allocated by compiler                                           |
| 16 | KEYBOARD__PORT_B__MASK__REG                                     |
| 17 | KEYBOARD__PORT_C__MASK__REG                                     |
| 18 | KEYBOARD__PORT_D__MASK__REG                                     |
| 19 | COMM_KEYBOARD__EVENT__REG                                       |
| 20 | COMM_LEDS__DATA__INDEX__REG                                     |
| 21 | allocated by compiler                                           |
| 22 | allocated by compiler                                           |
| 23 | allocated by compiler                                           |
| 24 | allocated by compiler                                           |
| 25 | allocated by compiler                                           |
| 26 | COMM_LEDS__PALETTE__PTR__REG (L)                                |
| 27 | COMM_LEDS__PALETTE__PTR__REG (H)                                |
| 28 | COMM_LEDS__SELECTORS__PTR__REG (L)                              |
| 29 | COMM_LEDS__SELECTORS__PTR__REG (L)                              |
| 30 | COMM_LEDS__MEMORY__PTR__REG (L)                                 |
| 31 | COMM_LEDS__MEMORY__PTR__REG (H)                                 |


## Flag allocations

|        |   |                                                         |
|--------|---|---------------------------------------------------------|
| GPIOR0 | 0 | COMM_LEDS__HEADER_RECEIVED                              |
| GPIOR0 | 1 | COMM_LEDS__HEADER_PARSED                                |
| GPIOR0 | 2 | LEDS__REFRESH                                           |


## Notes

The WS2812 pin is kept low between transmissions, so LEDs are kept in reset.
Data transmission to LEDs can commence right away, without issuing reset pulse.
As a consequence, the interval between LED updates must be at least 50uS.

## Test 128-color palette (Atari 2600 NTSC)

RGB Values:

000000
404000
702800
841800
880000
78005c
480078
140084
000088
00187c
002c5c
003c2c
003c00
143800
2c3000
442800

404040
646410
844414
983418
9c2020
8c2074
602090
302098
1c209c
1c3890
1c4c78
1c5c48
205c20
345c1c
4c501c
644818

6c6c6c
848424
985c28
ac5030
b03c3c
a03c88
783ca4
4c3cac
3840b0
3854a8
386890
387c64
407c40
507c38
687034
846830

909090
a0a034
ac783c
c06848
c05858
b0589c
8c58b8
6858c0
505cc0
5070bc
5084ac
509c80
5c9c5c
6c9850
848c4c
a08444

b0b0b0
b8b840
bc8c4c
d0805c
d07070
c070b0
a070cc
7c70d0
6874d0
6888cc
689cc0
68b494
74b474
84b468
9ca864
b89c58

c8c8c8
d0d050
cca05c
e09470
e08888
d084c0
b484dc
9488e0
7c8ce0
7c9cdc
7cb4d4
7cd0ac
8cd08c
9ccc7c
b4c078
d0b46c

dcdcdc
e8e85c
dcb468
eca880
eca0a0
dc9cd0
c49cec
a8a0ec
90a4ec
90b4ec
90cce8
90e4c0
a4e4a4
b4e490
ccd488
e8cc7c

ececec
fcfc68
ecc878
fcbc94
fcb4b4
ecb0e0
d4b0fc
bcb4fc
a4b8fc
a4c8fc
a4e0fc
a4fcd4
b8fcb8
c8fca4
e0ec9c
fce08c

## Test: WRITE_PALETTE commands (GRB format):

60=8000000040400028700018840000880000785C00487800148400008818007C2C005C3C002C3C0000381400302C00284400
60=90404040646410448414349818209C20208C74206090203098201C9C381C904C1C785C1C485C20205C341C504C1C486418
60=A06C6C6C8484245C982850AC303CB03C3CA0883C78A43C4CAC4038B05438A86838907C38647C40407C5038706834688430
60=B0909090A0A03478AC3C68C04858C05858B09C588CB85868C05C50C07050BC8450AC9C50809C5C5C986C508C844C84A044
60=C0B0B0B0B8B8408CBC4C80D05C70D07070C0B070A0CC707CD07468D08868CC9C68C0B46894B47474B48468A89C649CB858
60=D0C8C8C8D0D050A0CC5C94E07088E08884D0C084B4DC8894E08C7CE09C7CDCB47CD4D07CACD08C8CCC9C7CC0B478B4D06C
60=E0DCDCDCE8E85CB4DC68A8EC80A0ECA09CDCD09CC4ECA0A8ECA490ECB490ECCC90E8E490C0E4A4A4E4B490D4CC88CCE87C
60=F0ECECECFCFC68C8EC78BCFC94B4FCB4B0ECE0B0D4FCB4BCFCB8A4FCC8A4FCE0A4FCFCA4D4FCB8B8FCC8A4ECE09CE0FC8C

## Test: Paint colors blocks of 16 consecutive colors from 128-color palette, with refresh

60=50000102030405060708090A0B0C0D0E0F
60=50101112131415161718191A1B1C1D1E1F
60=50202122232425262728292A2B2C2D2E2F
60=50303132333435363738393A3B3C3D3E3F
60=50404142434445464748494A4B4C4D4E4F
60=50505152535455565758595A5B5C5D5E5F
60=50606162636465666768696A6B6C6D6E6F
60=50707172737475767778797A7B7C7D7E7F

# Test: horizontal lines with UNPACK4 commands

Horizontal, Channel 0
60=0F 60=00
60=2F 60=20
60=4F 60=40
60=6F 60=60

Horizontal, Channel 1
60=8F 60=80
60=AF 60=A0
60=CF 60=C0
60=EF 60=E0

Vertical, Channel 0
60=1F
60=3F
60=5F
60=7F

Vertical, Channel 1
60=9F
60=BF
60=DF
60=FF

# Test: paint GBR colors, with refresh

60=10000088
60=1018007C

# Test palette: 4 gray + 4 green + 4 red + 4 blue

60=800000000404040808080C0C0C0400000800000C0000100000000400000800000C0000100000000400000800000C000010

# Test indexed colors: color 0 + color 1 + color 2 + color 3

60=5000010203 # color 0 + color 1 + color 2 + color 3
60=5004050607 # color 4 + color 5 + color 6 + color 7

# Test indexed colors: color 0 + color 4 + color 8 + color 12

60=500004080C
