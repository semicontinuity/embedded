#include "alarm__auth.h"

EEMEM struct alarm__auth__password ee__alarm__auth__password = {
    .length = ALARM__AUTH__PASSWORD__LENGTH,
    .data   = {ALARM__AUTH__PASSWORD__DATA}
};

struct alarm__auth__password alarm__auth__password;
