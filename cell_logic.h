#ifndef CL_H
#define CL_H

#include <inttypes.h>
#include <stdlib.h>


typedef uint8_t cell;
/* Bit 0: S0   
 * Bit 1: S1                 
 * Bit 2..7: reserved                
 *      
 */

typedef uint8_t rule_t;

/* 128-bit vector */
typedef struct vec128b_t { 
  uint8_t b [16]; 
} vec128b_t;

/* 128-cell vector */
typedef struct vec128c_t {
  cell c [16 * 8]; 
} vec128c_t;

/* 128 + 1 -cell vector */   // big-endian, index 0 is reserved, 1-based indexing 
                             // acccess with get_cell set_cell
typedef struct vec128bec_t {
  cell c [(16 * 8) + 1]; 
} vec128bec_t;

vec128bec_t* vec_alloc();

/* Little-endian version for display */
typedef struct vec128lec_t {
  cell c [(16 * 8) + 1]; 
} vec128lec_t;

typedef struct frame_t {
    size_t count;
    vec128bec_t* rows[128];
} frame_t;

frame_t* frame_alloc();
void frame_free(frame_t* f);
void frame_clear(frame_t* f);


void frame_pop (frame_t* f, vec128bec_t* v);
size_t frame_push(vec128bec_t* v, frame_t* f);

void frame_get_row(frame_t* f, uint8_t row, vec128bec_t* v);
void frame_put_row(frame_t* f, uint8_t row, vec128bec_t* v);

typedef enum {CELL_NIL, CELL_TRUE, CELL_FALSE, CELL_NULL} cell_state_t;

uint8_t vecbe_get_byte(uint8_t byte_num, vec128bec_t* v);
uint32_t vecbe_hamming_weight (vec128bec_t* vec);
cell get_cell(vec128bec_t* v, uint8_t index);
uint8_t set_cell(vec128bec_t* v, uint8_t index, cell c);

void vcopy (vec128bec_t* from, vec128bec_t* to);
void vmov (vec128bec_t* from, vec128bec_t* to);
void vxfer (vec128bec_t* from, vec128bec_t* to);
void vset (vec128bec_t* v, cell c);
void vsetN(vec128bec_t* v);
void vsetZ(vec128bec_t* v);

cell cxor (cell left, cell right);
cell cor (cell left, cell right);
cell cand (cell left, cell right);

cell binary_to_cell (char c);
char cell_to_binary (cell c);

void halt(char* msg);

#endif
