#ifndef _SINGLE_XOR_H_
#define _SINGLE_XOR_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <float.h>

#include "hex.h"
#include "freq.h"

char *decrypt_singlebytexor_on_hex(const char *hex, const float lang_freq[26]);

#endif
