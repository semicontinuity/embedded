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

#endif