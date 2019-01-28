#ifndef __OUTPUT_H
#define __OUTPUT_H

inline void output__init(void)       { USE_AS_OUTPUT(OUTPUT); }
inline void output__on(void)         { OUT_1(OUTPUT); }
inline void output__off(void)        { OUT_0(OUTPUT); }

#endif