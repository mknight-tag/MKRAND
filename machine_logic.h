#ifndef ML_H
#define ML_H

#include <stdlib.h>
#include <time.h>
#include "cell_logic.h"

typedef struct machine_instruction_t {
    size_t   clock_cycles;
    uint64_t instruction;
} machine_instruction_t;

typedef struct program_t {
  machine_instruction_t* instructions;
  size_t CP;
} program_t;

typedef enum {CP_NIL, CP_NULL, CP_IDLE, CP_RUN, CP_HALT} cp_state_t;

typedef struct cell_proc_t {
  frame_t* Stack;
  cp_state_t s;       // private state - make 64
  size_t  index;      // cell row index
  vec128bec_t* A;      // GP Input 1
  vec128bec_t* B;      // GP Input 2
  vec128bec_t* C;      // GP Buffer - will automatically be updated with D in next cycle
  vec128bec_t* D;      // GP Output (Next State)
  vec128bec_t* X;      // GP Transfer
  vec128bec_t* PSI;    // Timestamp                                     Synchronized with other cells on row
  vec128bec_t* R30;    // Deterministic randomness                      Synchronized with other cells on row
  vec128bec_t* SDR30;  // Seed for R30INC
  vec128bec_t* SDTIME; // Time Seed
  vec128bec_t* R;      // Free variable (non-deterministic randomness)  Synchronized with other cells on row ?
  vec128bec_t* NR;     // Next Row pointer
  vec128bec_t* CR;     // Current Row pointer
  program_t program;
} cell_proc_t;

typedef struct machine_t {
    cell_proc_t cells[128];
} machine_t;

typedef cell (*rulefunc)(cell, cell, cell);
cell rule (cell left, cell middle, cell right);

/* 96-bit entropy seed containing RTC seconds, microseconds, and an internal cycle count  */
typedef struct TimeSeed {
  uint32_t   long_count;
  uint32_t   short_count;
  uint32_t   cyclic;
} TimeSeed;

TimeSeed time_seed();
char* timeseed_tostr(TimeSeed* ts);
int check_clocks();

uint16_t cp_init(struct cell_proc_t* cp);
void cp_reset(struct cell_proc_t* cp);
void cp_halt(struct cell_proc_t* cp, char* msg);
void cp_free(struct cell_proc_t* cp);
void cp_setstate(struct cell_proc_t * cp, cp_state_t st);
cp_state_t cp_getstate(struct cell_proc_t* cp);
void show_cp(cell_proc_t* cp);

void mi0_xor  (cell_proc_t* cp);
void mi0_incSDTIME (cell_proc_t*  cp);
void mi1_incR30 (cell_proc_t*  cp);
void mi2_sha30 (cell_proc_t*  cp);
void mi2_genR (cell_proc_t*  cp);
void mi2_incPSI (cell_proc_t*  cp);

void pushSD(cell_proc_t* cp);
void popSD(cell_proc_t* cp);
void pushGP(cell_proc_t* cp);
void popGP(cell_proc_t* cp);

/* During Time Quantum :
   I/O input transfers occur (A,B loaded), get_neighbor calls resolved 
   PSI is atomically updated
   R30 is atomically advanced by 128 bits
   R is atomically updated based on PSI
   1 Process Cycle occurs
   I/O output transfers occur
 */
void mi5_time_quantum(cell_proc_t* cp);

#endif
