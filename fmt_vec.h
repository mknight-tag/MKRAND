
#ifndef FV_H
#define FV_H

#include  "cell_logic.h"

#define FMT_VEC_BINARY        0
#define FMT_VEC_SHA1          1
#define FMT_VEC_BINARY_TEXT   2
#define FMT_VEC_IPV4          4
#define FMT_VEC_GUID          5
#define FMT_VEC_IPV6          6
#define FMT_VEC_PSI           8
#define FMT_VEC_INT32         10
#define FMT_VEC_UUID          11
#define FMT_VEC_BASE64        12

char* fmt_vecbe(vec128bec_t* v, int fmt_type);
char cell_to_char(cell c);
char* frame_to_str(frame_t* f, int fmt_type);

#endif
