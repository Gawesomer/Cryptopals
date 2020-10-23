#ifndef _BASE64_H_
#define _BASE64_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "div.h"
#include "hex.h"

char *hextobase64(const char *hexstr);

#endif
