/*                                 
 * Vector Formatting.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, TAG Universal Machine.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>
#include "cell_logic.h"
#include "fmt_vec.h"

const char b64[64] = {'A','B','C','D','E','F','G','H',
                     'I','J','K','L','M','N','O','P',
                     'Q','R','S','T','U','V','W','X',
                     'Y','Z','a','b','c','d','e','f',
                     'g','h','i','j','k','l','m','n',
                     'o','p','q','r','s','t','u','v',
                     'w','x','y','z','0','1','2','3',
                     '4','5','6','7','8','9','-','_'    // URL-friendly mod
                     };

const char bc[58] = {'A','B','C','D','E','F','G','H',
                     'J','K','L','M','N','P',
                     'Q','R','S','T','U','V','W','X',
                     'Y','Z','a','b','c','d','e','f',
                     'g','h','j','k','l','m','n',
                     'p','q','r','s','t','u','v',
                     'w','x','y','z','1','2','3',
                     '4','5','6','7','8','9'
                     };

const int b64_padding = 0;

char* b64triplet = NULL;

/* Convert 3 bytes into 4 base64 characters */
char* encode_b64_triplet(uint8_t b1, uint8_t b2, uint8_t b3){
  char* r = malloc(5);
  memset(r, '\0', 5);
  uint8_t idx1, idx2, idx3, idx4;
  
  idx1  = ((b1 & 0xFC) >> 2);                       // First 6 Bits of b1
  idx2  = ((b1 & 0x03) << 4) | ((b2 & 0xF0) >> 2);  // Last 2 bits of b1 and first 4 of b2
  idx3  = ((b2 & 0x0F) << 2) | ((b3 & 0xC0) >> 4);  // Second nibble of b2, first 2 bits of b3
  idx4  =  (b3 & 0x3F);                             // Last 6 bits of b3

  r[0] = b64[idx1];
  r[1] = b64[idx2];
  r[2] = b64[idx3];
  r[3] = b64[idx4];
  r[4] = '\0';
  return(r);
}

char cell_to_char(cell c) 
{
   char r;
   switch (c)
        {
            case CELL_FALSE : r = '0';
                     break;

            case CELL_TRUE  : r = '1';
                     break;

            case CELL_NULL  : r = 'N';
                     break;

            default : r = '?';
        }

  return (r);
}

/* Format Vector 
   Caller frees returned string
 */
char* fmt_vecbe(vec128bec_t* v, int fmt_type){
  int i;
  uint32_t int32;
  int offset;

  if (v == NULL) { return "[NULL]"; }

  char* r = malloc(128*10);
  memset(r, '\0', 128*10);

  char* t = malloc(10);
  memset(t, '\0', 10);
  
  switch (fmt_type) {
      /* BINARY */
      case FMT_VEC_BINARY :  
                 for (i = 1; i <= 16; i++){ 
                   sprintf(t,"%02X",vecbe_get_byte(i, v));
                   strcat(r,t);
                 }
                 break;

      /* SHA1 - Form only, not SHA1 function */
      case FMT_VEC_SHA1 : 
               offset = 0;
               for (i=0; i<16; i++) {

                 if ((i==4) || (i==10)) {
                    sprintf(&r[(i*2)+offset],"-%02x",vecbe_get_byte(i+1, v));
                    offset++;
                    continue;
                 }

                 if (i==6) {
                    sprintf(&r[(i*2)+offset],"-%02x",(vecbe_get_byte(i+1, v) & 0x0F) | (0x03 << 4)); // Left nibble to 0x3
                    offset++;
                    continue;
                 }

                if (i==8) {
                    sprintf(&r[(i*2)+offset],"-%02x",(vecbe_get_byte(i+1, v) & 0x0F) | (0x0A << 4)); // Left nibble to 0xA
                    offset++;
                    continue;
                 }

                 sprintf(&r[(i*2)+offset],"%02x",vecbe_get_byte(i+1, v));
               }
               break;

      /* Text BINARY */
      case FMT_VEC_BINARY_TEXT :   
                  for (i = 1; i <= 128; i++){   
                    sprintf(t,"%c", cell_to_char(get_cell(v, (129-i))));
                    strcat(r,t);
                  }

              break;

      case 3:   sprintf(r," ");
                    break;

      /* IPV4 */
      case FMT_VEC_IPV4:   
                 sprintf(r,"%d.%d.%d.%d",(vecbe_get_byte(4,v)),(vecbe_get_byte(3,v)),(vecbe_get_byte(2,v)),(vecbe_get_byte(1,v)));
                 break;


      /* GUID 
         One to three of the most significant bits of the first byte in Data 4 define the type variant of the GUID
         Set to 100 or 0x04
       */
      case FMT_VEC_GUID: 
               offset = 1;
               for (i=0; i<16; i++) {

                 if ((i==4) || (i==10)) {
                    sprintf(&r[(i*2)+offset],"-%02X",vecbe_get_byte(i+1, v));
                    offset++;
                    continue;
                  }

                if (i==8) {
                    sprintf(&r[(i*2)+offset],"-%02X",(vecbe_get_byte(i+1, v) & 0x0F) | (0x0A << 4)); // Left nibble to 0x4
                    offset++;
                    continue;
                 }

                 sprintf(&r[(i*2)+offset],"%02X",vecbe_get_byte(i+1, v));
               }
               
               r[0] = '{';  strcat(r,"}");
               break;

      /* IPV6 */
      case FMT_VEC_IPV6: 
              offset = 0;
              for (i=0; i<16; i++) {
                  if ((i % 2 == 0) && (i > 0)) {
                    sprintf(&r[(i*2)+offset],":%02x",vecbe_get_byte(i+1, v));
                    offset++;
                  } else {
                    sprintf(&r[(i*2)+offset],"%02x",vecbe_get_byte(i+1, v));
                  }
              }
              break;

      case 7:   sprintf(r," ");
                    break;

      /* PSI Fingerprint 
         Technically this is a complete NDRAND, not just a fingerprint, but for 
         code simplicity and because there is no functional difference in the von Neumann 
         architecture, it is generated the same way as the others.
      */
      case FMT_VEC_PSI :  
                 strcat(r,"[<:");
                 for (i=0; i<16; i++) {
                   sprintf(&r[(i*2)+3],"%02X",(vecbe_get_byte(i+1,v)));
                  }
                 strcat(r,":>]");
                 break;

      case 9:   sprintf(r," ");
                    break;

      /* Unsigned 32-bit */           
      case FMT_VEC_INT32 :  
                 int32 = ((vecbe_get_byte(4,v)) << 24) | ((vecbe_get_byte(3,v)) << 16) | ((vecbe_get_byte(2,v)) << 8) | ((vecbe_get_byte(1,v)));
                 sprintf(r,"%u", int32);
                 break;

             /* UUID V4 */
      case FMT_VEC_UUID : 
               offset = 0;
               for (i=0; i<16; i++) {

                 if ((i==4) || (i==10)) {
                    sprintf(&r[(i*2)+offset],"-%02x",vecbe_get_byte(i+1, v));
                    offset++;
                    continue;
                  }
                 
                 if (i==6) {
                    sprintf(&r[(i*2)+offset],"-%02x",(vecbe_get_byte(i+1, v) & 0x0F) | (0x04 << 4)); // Left nibble to 0x4
                    offset++;
                    continue;
                 }

                if (i==8) {
                    sprintf(&r[(i*2)+offset],"-%02x",(vecbe_get_byte(i+1, v) & 0x0F) | (0x0A << 4)); // Left nibble to 0xA
                    offset++;
                    continue;
                 }

                 sprintf(&r[(i*2)+offset],"%02x",vecbe_get_byte(i+1, v));
               }
               break;


      /* Base 64 - Produces 22 characters */
      case FMT_VEC_BASE64:   // Encode first 15 bytes in 5 pairs of 3
                 // 1,2,3  4,5,6  7,8,9  10,11,12  13,14,15
                 for(i=1; i<=5; i++){
                   offset = ((i-1) * 3) + 1;
                   b64triplet = encode_b64_triplet(vecbe_get_byte(offset, v),
                                                   vecbe_get_byte(offset+1, v),
                                                   vecbe_get_byte(offset+2, v));
                   sprintf(t, "%s", b64triplet);                                                                                                          
                   strcat(r,t);

                   free(b64triplet);
                 }
                 // Remaining byte 16
                 b64triplet = encode_b64_triplet(vecbe_get_byte(16, v), 0,0);
                 sprintf(t, "%s", b64triplet);
                 // Keep first two hex64 digits and the rest is padding (==) if desired.
                 if (b64_padding) {
                   t[2] = '=';
                   t[3] = '=';
                   t[4] = '\0';
                 } else {
                   t[2] = '\0';
                 }
                 strcat(r,t);
                 free(b64triplet);
                 break;

       case 13:   sprintf(r," ");
                       break;

       default:  sprintf(r,"INVALID FORMAT\n");       
      
  }

  free(t);
  return(r);
}


char* frame_to_str(frame_t* f, int fmt_type) {
  int i;
  vec128bec_t* v = vec_alloc();

  char* r = malloc(2000);
  memset(r, '\0',2000);

  char* s = malloc(500);
  memset(s, '\0',500);

  if (f->count == 0) {
    sprintf(r,"[STACK EMPTY]\n");
  }

  for (i=f->count; i >= 1; i--){
    frame_get_row(f, i, v);
    sprintf(s, "[%03d]     %s\n",i,fmt_vecbe(v, fmt_type));
    strcat (r,s);
    memset(s, '\0',500);
  }

  free(s);
  free(v);

  return(r);
}
