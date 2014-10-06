/*                                 
 * Cell Logic
 * Three state logic functions and vector operations
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

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "cell_logic.h"

void halt(char* msg)
{
  printf("HALT: %s\n",msg);
  exit(EXIT_FAILURE); 
}

/* Allocate vector memory slot */
vec128bec_t* vec_alloc() { 
  vec128bec_t* r = malloc(sizeof(vec128bec_t));
  if (r) {
    vset(r, CELL_NULL);
  }

  return (r);
}

/* Allocate frame pointer and vector memory slots */
frame_t* frame_alloc() {
  int i;
  frame_t* f = malloc(sizeof(frame_t));

  if (f) {
    for (i=1; i<= 128; i++){
      (f->rows[i-1]) = vec_alloc();
    }
   f->count = 0;
  }
  
  return (f);
}

/* Deallocate vector memory slots and frame pointer */
void frame_free(frame_t* f) {
  size_t i;

  for (i=1; i <= 128; i++){
    free(f->rows[i-1]);
  }

  free(f);
}

/* Nullify vector memory slots
   C - Does not deallocate memory
 */
void frame_clear(frame_t* f){
  size_t i;

  for (i=1; i <= 128; i++){
    vsetN(f->rows[i-1]);
  }

  f->count = 0;
}

/* Copy vector from given frame slot
 * C - no memory operations
 */
void frame_get_row(frame_t* f, uint8_t row, vec128bec_t* v){
  if ((row < 1) || (row > 128)) { halt ("frame_get_row: bad index"); }
  
  vcopy (f->rows[row-1], v);
}

/* Copy vector into frame slot at given index 
   C - no memory operations
 */
void frame_put_row(frame_t* f, uint8_t row, vec128bec_t* v){
  if ((row < 1) || (row > 128)) { halt ("frame_put_row: bad index"); }

  vcopy(v, f->rows[row-1]);
} 

/* Pop vector from stack and place in v  */
void frame_pop (frame_t* f, vec128bec_t* v){
  if (f->count == 0) { return; }
  vmov (f->rows[(f->count)-1], v);
  f->count -= 1;
}

/* Copies vector into topmost frame memory slot, nullifying source 
   C - no memory operations
 */
size_t frame_push(vec128bec_t* v, frame_t* f){
  f->count += 1;
  vmov(v, f->rows[(f->count)-1]);
  return (f->count);
}


/* GetCell - Vectors are Big-Endian and 1-based. C Index 0 is reserved and not exposed. */
cell get_cell(vec128bec_t* v, uint8_t index){
  if ((index < 1) || (index > 128)) { halt ("get_cell : Bad Index"); }

  /* Index Mapping
     Cell Vector : [RES] [128] [127] .. [1] 
     C Array     : [0]   [1]   [2]   .. [128]
   */

  return (v->c[129-index]); 
}

uint8_t set_cell(vec128bec_t* v, uint8_t index, cell c){
  if ((index < 1) || (index > 128)) { halt ("set_cell : Bad Index"); } 

  v->c[129-index] = c;

  return(0);
}

/* VSET - Set vector to given value */
void vset (vec128bec_t* v, cell c){
  size_t i;

  for (i=1; i<=128; i++){
     set_cell(v,i,c);
  }
}

/* Copy vector, leaving source intact */
void vcopy (vec128bec_t* from, vec128bec_t* to) {
  size_t i;

  for (i=1; i<=128; i++){
     set_cell(to,i,get_cell(from, i));
  }
}

/* Move vector, nullifying source 
 * C - no memory operations */
void vmov (vec128bec_t* from, vec128bec_t* to) {
  vcopy(from, to);
  vsetN(from);
}

/* Move vector, freeing source memory (von Neumann) */
void vxfer (vec128bec_t* from, vec128bec_t* to) {
  vcopy(from, to);
  free(from);
}

/* Set vector to 00.. */
void vsetZ(vec128bec_t* v) {
  vset(v, CELL_FALSE);
}

/* Set register to NULL
 * C - no memory operations
 * Synchronization/wavefront actions hooked here
 */
void vsetN(vec128bec_t* v){
  vset(v, CELL_NULL);
}


/* Extract Byte from Vec. Byte index 1..16 */
uint8_t vecbe_get_byte(uint8_t byte_num, vec128bec_t* v){
  uint8_t i;
  uint8_t r = 0;
  uint8_t b = 0;
  uint8_t offset = ((byte_num-1) * 8) +1;

  if ((byte_num < 1) || (byte_num > 16)) { halt("get_byte: invalid index"); }

  for (i = offset; i<= (offset + 7); i++){
    b = (get_cell(v,i) == CELL_TRUE) ? 1 : 0;
    r = r | (b << (i-offset));  
  }
  return(r);
}

uint8_t vecbe_pack(uint8_t* bytes, vec128bec_t* v)
{
  for (int i = 0; i<16; i++) {
    bytes[i] = vecbe_get_byte(i+1, v);
  }
  return(16);
}

uint32_t vecbe_hamming_weight (vec128bec_t* v) {
  int i = 0;
  uint32_t w = 0;
  for (i=1; i<=128; i++){
    if (get_cell(v, i) == CELL_TRUE) {
      w += 1;
    }
  }
  return(w);  
}


/* AND */
cell cand (cell left, cell right) 
{
   if ((left == CELL_NULL) || (right == CELL_NULL)) {
      return (CELL_NULL);
   } else {
      if ((left == CELL_TRUE) && (right == CELL_TRUE)) {
         return (CELL_TRUE);
      } else {
         return (CELL_FALSE);
      }
   }
}

/* OR */
cell cor (cell left, cell right)
{
   if ((left == CELL_NULL) || (right == CELL_NULL)) {
      return (CELL_NULL);
   } else {
      if ((left == CELL_TRUE) || (right == CELL_TRUE)) {
         return (CELL_TRUE);
      } else {
         return (CELL_FALSE);
      }
   }
}


/* XOR */
cell cxor (cell left, cell right)
{
   if ((left == CELL_NULL) || (right == CELL_NULL)) {
      return (CELL_NULL);
   } else {
      if (((left == CELL_TRUE)  && (right == CELL_FALSE)) ||
          ((left == CELL_FALSE) && (right == CELL_TRUE))) {
         return (CELL_TRUE);
      } else {
         return (CELL_FALSE);
      }
   }
}


char cell_to_binary (cell c) {
    char r = 0;

    switch (c)
      {
         case CELL_FALSE : r = 0;
                  break;

         case CELL_TRUE  : r = 1;
                  break;

         case CELL_NULL  : halt("cell_to_binary - NULL cell");
                  break;

         default : halt("cell_to_binary - invalid cell value");

      }

      return(r);
}

cell binary_to_cell (char c) {
    char r = CELL_FALSE;

    switch (c)
      {
         case 0  : r = CELL_FALSE;
                  break;

         case 1  : r = CELL_TRUE;
                  break;

         default : halt("binary_to_cell - invalid binary value");

      }

      return(r);
}

