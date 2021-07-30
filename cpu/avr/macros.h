#ifndef __MACROS_H
#define __MACROS_H

#ifndef QUOTE
#define QUOTE__(x)                   #x
#define QUOTE_(x)                    QUOTE__(x)
#define QUOTE(x)                     QUOTE_(x)
#endif

#ifndef CONCAT
#define CONCAT2(s1, s2)              s1##s2
#define CONCAT(s1, s2)               CONCAT2(s1, s2)
#endif

#define SINGLEQUOTED_A 'A'
#define SINGLEQUOTED_B 'B'
#define SINGLEQUOTED_C 'C'
#define SINGLEQUOTED_D 'D'
#define SINGLEQUOTED_E 'E'
#define SINGLEQUOTED_F 'F'
#define SINGLEQUOTED_G 'G'
#define SINGLEQUOTED_H 'H'
#define SINGLEQUOTED_I 'I'
#define SINGLEQUOTED_J 'J'
#define SINGLEQUOTED_K 'K'
#define SINGLEQUOTED_L 'L'
#define SINGLEQUOTED_M 'M'
#define SINGLEQUOTED_N 'N'
#define SINGLEQUOTED_O 'O'
#define SINGLEQUOTED_P 'P'
#define SINGLEQUOTED_Q 'Q'
#define SINGLEQUOTED_R 'R'
#define SINGLEQUOTED_S 'S'
#define SINGLEQUOTED_T 'T'
#define SINGLEQUOTED_U 'U'
#define SINGLEQUOTED_V 'V'
#define SINGLEQUOTED_W 'W'
#define SINGLEQUOTED_X 'X'
#define SINGLEQUOTED_Y 'Y'
#define SINGLEQUOTED_Z 'Z'

#define SINGLEQUOTED__(x) SINGLEQUOTED_##x
#define SINGLEQUOTED_(x) SINGLEQUOTED__(x)
#define SINGLEQUOTED(x) SINGLEQUOTED_(x)

#endif