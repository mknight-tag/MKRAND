/*                                 
 * Machine Logic
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

 /* Random means YOU do the choosing.
 *  -- Ross Ashby
 *
 *
 *                                        
 *                               Cellular Automata Rule 30              Universal Constant
 *                                    Field of Action                          R30
 *  Gen                                                                  (Center Column)
 * [001]   00000000000000000000000000000000001000000000000000000000000000000000 1
 * [002]   00000000000000000000000000000000011100000000000000000000000000000000 1
 * [003]   00000000000000000000000000000000110010000000000000000000000000000000 0
 * [004]   00000000000000000000000000000001101111000000000000000000000000000000 1
 * [005]   00000000000000000000000000000011001000100000000000000000000000000000 1
 * [006]   00000000000000000000000000000110111101110000000000000000000000000000 1
 * [007]   00000000000000000000000000001100100001001000000000000000000000000000 0
 * [008]   00000000000000000000000000011011110011111100000000000000000000000000 0
 * [009]   00000000000000000000000000110010001110000010000000000000000000000000 1
 * [010]   00000000000000000000000001101111011001000111000000000000000000000000 1
 * [011]   00000000000000000000000011001000010111101100100000000000000000000000 0
 * [012]   00000000000000000000000110111100110100001011110000000000000000000000 0
 * [013]   00000000000000000000001100100011100110011010001000000000000000000000 0
 * [014]   00000000000000000000011011110110011101110011011100000000000000000000 1
 * [015]   00000000000000000000110010000101110001001110010010000000000000000000 0
 * [016]   00000000000000000001101111001101001011111001111111000000000000000000 1
 * [017]   00000000000000000011001000111001111010000111000000100000000000000000 1
 * [018]   00000000000000000110111101100111000011001100100001110000000000000000 0
 * [019]   00000000000000001100100001011100100110111011110011001000000000000000 0
 * [020]   00000000000000011011110011010011111100100010001110111100000000000000 1
 * 
 *                                       Randomness
 *                                          /|\
 *                                         / | \
 *                                        /  |  \ 
 *                                       /___|___\
 *                                   Order       Chaos                              
 *           
 *                      
 * Randomness is naturally the conjunction of Order and Chaos in Rule 30         
 *
 *
 * Syntropy - a Holistic Function for Universal Processing  
                             




                              Pattern
                               SYNC
                         +/- Biopsychic (Mind)
            Individual{Gravitational, Electromagnetic, Biopsychic}                            
                            Conjunctive                  
                                /\
                               /  \           
                              /    \     
                             /______\
                       Absolute     Relative
{Order, Chaos, Random}Rule 30           Machine{Logic, Memory, Time} 
                +/- R30                      +/- Time 
              CELEST                           PSI
            Image                                Imitation




 
 * A technik for generating Knightian randomness, in three parts:
 *
 * The cycle of creation moves in this order : PSI -> CELEST -> SYNC
 *    
 *    
 * Deterministic Randomess is chosen without conscious decision. R30 is deterministically random.
 * Syntropic Randomness is a co-creative act between Man, Machine, and Universe.
 * 
 * To request a co-deterministic value is to initiate Information Creation.
 *
 *  This process takes an image of the relative (PSI), then an image of the absolute (CELEST (PSI)),
 *   and finally fuses the two (SYNC) to produce the created information.
 *
 *   PSI is the time-dependent, weakly deterministic environmental state. In von Neumann architectures 
 *   an initial 64-bit PSI Seed is created by fusing external, passing time 
 *   with internal, cyclic time (Time Seed).
 *   
 *   This seed is then projected and magnified into a cryptographically unique image with SHA30, becoming PSI.
 *   This PSI value is structurally compatible with the upcoming CELEST which is simply SHA30 of PSI.
 *   
 *   Finally to create the new, co-deterministic value we fuse the two together with XOR
 *   in the SYNCHRONIC phase.
 *   
 *   In cybernetic notation, the complete transform is
 *
 *   PSI -> PSI XOR CELEST(PSI)
 *
 *   TERMS
 *
 *   Time Quantum - Smallest (atomic) time interval for the purposes of higher-level computations. 
 *                  It is the time required to load, evaluate, and store a 128x128 CA frame, which 
 *                  at the hardware level is approximately 130 clock cycles. During this time, the instructions
 *                  mi1_R30, mi1_PSI begin their incrementation process on shadow registers, and their results 
 *                  will be copied to R30 and PSI at the beginning of the following cycle.
 *                  mi0_incSDTIME is executed at the beginning of the cycle
 *
 *   Compute Cycle - The closed cycle of cybernetic transformation that includes load, evaluate, 3-step process, 
 *                   and store. It takes 3 Time Quanta end-to-end, however, parts of the computation may
 *                   be scheduled ahead of time and interleaved with other independent computations. And of course 
 *                   compute cycles can be chained for a single thread of computation.
 *                   The beginning of each compute cycle includes an incSDTIME as well as the results of 
 *                    incR30 and incPSI calculated during the previous cycle. Therefore all computational processes 
 *                    in the same quantum have access to the latest deterministic randomness through R30 and the latest
 *                    PSI fingerprint. These registers are synchronized for all cells (processes) in the same row (time quantum).
 *
 *   Machine instructions are named in the format miN_name where N is the number of time quanta they require
 *   with 0 meaning it is a digital operation that can be accomplished in between Compute Cycles (< 10 clock cycles)
 *   On its own hardware, a Compute Cycle is < 200 clock cycles. On von Neumann architectures it is at least millions.
 *
 *   As a concurrent process expressed on a serial architecture, this program is approximately 0% efficient. 
 *   Code optimizations at the expense of clarity will not be productive.
 */


#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "command.h"
#include "fmt_vec.h"
#include "cell_logic.h"
#include "machine_logic.h"

/* Time Seed
 * A catalyst. 96 bits of environmental entropy in the form of
 * internal (Relative, Cyclic) and external (Absolute, Passing) time. 
 * Entropy is amplified to 128 bits to create the PSI fingerprint.
 * ts_cycle is the internal cycle counter to guarantee differentiation from call to call,
 * even if RTC clock does not increment.
 */

static uint32_t ts_cycle = 0;

TimeSeed time_seed()
{
  struct timeval tv; 
  ts_cycle += 1;
  if (gettimeofday(&tv, NULL) != 0) { halt("TimeSeed: gettimeofday failed");}               

  TimeSeed r = {.long_count = tv.tv_sec,    // RTC seconds
                .short_count = tv.tv_usec,  // RTC microseconds
                .cyclic = ts_cycle};        // Internal cyclic state

  return (r);
}

char* timeseed_tostr(TimeSeed* ts) {
   size_t  strsize = 100;
   char* r = malloc(strsize);
   memset(r, '\0', strsize);
   sprintf(r,"LC:%08X SC:%08X CY:%08X",ts->long_count, ts->short_count, ts->cyclic);
   return (r);
}

/* Compare TimeSeeds, return CELL_TRUE if equal, CELL_FALSE otherwise */
int ts_cmpE(TimeSeed* s0,  TimeSeed* s1){
  return ((s0->long_count  == s1->long_count)  &&
          (s0->short_count == s1->short_count) &&
          (s0->cyclic      == s1->cyclic)) ? CELL_TRUE : CELL_FALSE; 
}

void cp_setstate(struct cell_proc_t *restrict cp, cp_state_t st){
  cp->s = st;
}

cp_state_t cp_getstate(struct cell_proc_t *restrict cp) {
  return (cp->s);
}

void cp_halt(struct cell_proc_t *restrict cp, char* msg){
  cp_setstate(cp, CP_HALT);
  printf("Program Halt - %s.\n", msg);
  exit(EXIT_FAILURE);
}

/* Nullify memory slots and reset state
   C - does not deallocate any memory
 */
void cp_reset(struct cell_proc_t *restrict cp){
  cp->index = 0;
  cp->NR = cp->B;
  cp->CR = cp->A;

  cp_setstate(cp, CP_IDLE);
  frame_clear(cp->Stack);
  vsetN(cp->A);
  vsetN(cp->B);
  vsetN(cp->C);
  vsetN(cp->D);
  vsetN(cp->X);
  vsetN(cp->PSI);
  vsetN(cp->R30);
  vsetN(cp->R);
  vsetZ(cp->SDR30);
  vsetN(cp->SDTIME);
}

/* Allocate memory slots for registers and stack */
uint16_t cp_init(struct cell_proc_t *restrict cp){
  cp->A      = vec_alloc();
  cp->B      = vec_alloc();
  cp->C      = vec_alloc();
  cp->D      = vec_alloc();
  cp->X      = vec_alloc();
  cp->PSI    = vec_alloc();
  cp->R30    = vec_alloc();
  cp->SDR30  = vec_alloc();
  cp->SDTIME = vec_alloc();
  cp->R      = vec_alloc();
  cp->Stack  = frame_alloc();
  cp_setstate(cp, CP_NULL);

  if (!((cp->A) && (cp->B) && (cp->C) && (cp->D) && (cp->X) && (cp->PSI) && (cp->R30) && (cp->R))) {
     cp_halt(cp, "cp_init: Out of Memory");
  }

  cp_reset(cp);

  return(0);
}


/* Deallocate memory slots */
void cp_free(struct cell_proc_t *restrict cp){
  free(cp->A);
  free(cp->B);  
  free(cp->C);   
  free(cp->D);  
  free(cp->X);
  free(cp->PSI); 
  free(cp->R30); 
  free(cp->SDR30); 
  free(cp->SDTIME); 
  free(cp->R);   
  frame_free(cp->Stack);
}

/* Machine Instructions */

/* CMPZ - Return CELL_TRUE if all cells are False, CELL_FALSE otherwise */
cell_state_t mi0_cmpZ (vec128bec_t* v) {
  uint8_t i;
  cell c;
  cell_state_t r = CELL_NULL;

  for(i = 1; i <= 128; i++) {
     c = get_cell(v, i);
     if ((c == CELL_TRUE) || (c == CELL_NULL)) {
        return (CELL_FALSE);
     }
  }

  r = CELL_TRUE;

  return r;
}

/* CMPN - Return CELL_TRUE if ANY cell is NULL, CELL_FALSE otherwise */
cell_state_t mi0_cmpN (vec128bec_t* v) {
  uint8_t i;

  for(i = 1; i <= 128; i++) {
     if (get_cell(v, i) == CELL_NULL) {
        return (CELL_TRUE);
     }
  }

  return (CELL_FALSE);
}


/* XOR A and B, place result in D     */
void mi0_xor  (cell_proc_t * restrict cp) {
  int i;

  if (verbose_flag) { printf("mi0_xor\n"); }

  if ((mi0_cmpN(cp->A) == CELL_TRUE) || (mi0_cmpN(cp->B) == CELL_TRUE)) { cp_halt(cp, "MI_XOR: NULL Argument(s)");}
  vsetN(cp->D);

  for (i = 1; i <= 128; i++) {
    set_cell(cp->D, i, cxor(get_cell(cp->A, i), get_cell(cp->B,i)));
  } 
}


/* LDA - Load vector into register A */
void mi_LDA (cell_proc_t *restrict cp, vec128bec_t* input) {
  vcopy(input, cp->A);
}

/* LDB - Load vector into register B */
void mi_LDB (cell_proc_t *restrict cp, vec128bec_t* input) {
  vcopy(input, cp->B);
}

/* LDC - Load vector into register C */
void mi_LDC (cell_proc_t *restrict cp, vec128bec_t* input) {
  vcopy(input, cp->C);
}

/* LDD - Load vector into register D */
void mi_LDD (cell_proc_t *restrict cp, vec128bec_t* input) {
  vcopy(input, cp->D);
}

/* Rule 30 : x(n+1,i) = x(n,i-1) xor [x(n,i) or x(n,i+1)] */
cell rule_30(cell left, cell middle, cell right){
  return (cxor (left, cor (middle, right)));
}

rulefunc ruleFactory(rule_t r) {
    rulefunc functionPtr;
    if (r==30) {
      functionPtr = &rule_30;
    } else {
      functionPtr = NULL;
    }
    return functionPtr;
}

/* Evaluate source vector with elemental rule, placing result in dest  */
void eval_rule(rule_t r, vec128bec_t* source, vec128bec_t* dest){
  uint8_t col;
  cell left_cell, right_cell, middle_cell;

  for (col = 1; col <= 128; col++){
     left_cell   = (col == 128) ? get_cell(source, 1)    : get_cell(source, col+1);
     right_cell  = (col == 1)   ? get_cell(source, 128)  : get_cell(source, col-1); 
     middle_cell = get_cell(source, col);
            
     set_cell(dest, col, (*ruleFactory(r))(left_cell, middle_cell, right_cell) );   
  }  
}

/* Update Time Seed with current time   
   96 bits of clock information are loaded such that long count is in MSB, 
      short count on LSB with and cyclic in center:
   Short Count (32) -> Random(16) -> Cyclic (32) <- Random(16) <- Long Count (32)
   The rest of the bits are seeded with randomness from previous cycle, or 0 on init
 */ 
void mi0_incSDTIME (cell_proc_t *restrict cp){
  int i;
  TimeSeed seed = time_seed();
  
  if (verbose_flag) {  
    printf("MI2_INCSDTIME: %s\n",timeseed_tostr(&seed));
  }   

  if (mi0_cmpN(cp->R) == CELL_TRUE) {
    vsetZ(cp->SDTIME);         // On init, pre-Seed with 0
  } else {
    vcopy(cp->R, cp->SDTIME);  // pre-Seed with previous output for cycle mode
  }                            
  
  /* MSB 1-32 */
  for (i = 1; i <= 32; i++){
    set_cell(cp->SDTIME, i, binary_to_cell ((seed.long_count  >> (i-1)) & 0x01));  
  }

  /* Center 48-80 */
  for (i=1; i<=32; i++){
     set_cell(cp->SDTIME, (48+i), binary_to_cell ((seed.cyclic >> (i-1)) & 0x01));  
  }

  /* LSB 96-128 */
  for (i = 1; i <= 32; i++){
    set_cell(cp->SDTIME, (96+i), binary_to_cell ((seed.short_count >> (i-1)) & 0x01));  

  }  

  if (verbose_flag) {  
    printf("SDTIME: %s\n",fmt_vecbe(cp->SDTIME, FMT_VEC_BINARY));
  }  

}

/* INCPSI - SHA30 of SDTIME, place result in PSI */
void mi2_incPSI (cell_proc_t *restrict cp){

  if (verbose_flag) {  
    printf("MI2_INCPSI\n");
  }   

  vsetN(cp->PSI);
  vcopy(cp->SDTIME, cp->A);
  mi2_sha30(cp);
  vmov(cp->D, cp->PSI);
}

/* SHA30 - Use REGA as seed for R30, generate 2 blocks, move second block to REGD
 */
void mi2_sha30 (cell_proc_t *restrict cp){

  if (verbose_flag) {  
    printf("MI2_SHA30\n");
  }   
  pushSD(cp);
  vsetN(cp->D);
  vmov(cp->A, cp->SDR30);
  mi1_incR30(cp);
  mi1_incR30(cp);
  vmov(cp->SDR30, cp->D);
  popSD(cp);  // Restore Seeds
}

/* Generate non-deterministic rand, PSI must already exist 
   Take SHA30 of PSI, then XOR that to PSI. Move result to R
 */

void mi2_genR (cell_proc_t *restrict cp) {
  if (verbose_flag) {  
    printf("MI2_GENR\n");
  }   
  vsetN (cp->R);
  vcopy(cp->PSI, cp->A);    // PSI -> A
  mi2_sha30(cp);            // CELEST(PSI) -> D
  vcopy(cp->PSI, cp->A);    // PSI -> A
  vcopy(cp->D, cp->B);      // A:PSI B: CELEST(PSI)
  mi0_xor(cp);              // D: RAND
  vmov(cp->D, cp->R);       // R: PSI XOR CELEST(PSI)
}


/* Machine instruction R30
   Runs R30 for 128 clock cycles to fill R30 with next segment
   RegA : Seed, copied from SDR30, will set center column to 1 if R30 is zero
   RegB : Buffer
   RegD : Output 
   Copies last state to SDR30
 */
void mi1_incR30 (cell_proc_t *restrict cp){
  uint32_t gen;
  uint32_t center_col = 0;
  char* out_str = NULL;// malloc(300);

  if (verbose_flag) {  
    printf("MI1_INCR30\n");
  }   

  if (cp_getstate(cp) != CP_IDLE)       { cp_halt (cp, "INCR30: Celproc not idle");  }

  if (mi0_cmpN(cp->SDR30) == CELL_TRUE) { cp_halt (cp, "INCR30: Null Input on SDR30"); }

  vmov(cp->SDR30, cp->A);    // Copy R30 Seed to input 

  vsetN(cp->B);              // Clear Buffer

  cp->NR = cp->A;            // Set row pointers
  cp->CR = cp->B;

  cp_setstate(cp, CP_RUN);

  center_col = (128 / 2);

  if (mi0_cmpZ(cp->A) == CELL_TRUE) {
    set_cell(cp->A, center_col, CELL_TRUE);
  }

  for (gen = 1; gen <= 128; gen++) {
    if (gen & 0x01) {    // Toggle Row pointers every other gen
      cp->NR = cp->B;
      cp->CR = cp->A;
    } else {
      cp->NR = cp->A;
      cp->CR = cp->B;
    }

    if (verbose_flag) {
      out_str = fmt_vecbe(cp->CR, FMT_VEC_BINARY_TEXT);
      printf("[%03d]     %s %c\n", gen, out_str, cell_to_char(get_cell(cp->CR, center_col)));
      free(out_str);
    }
    
    eval_rule(30, cp->CR, cp->NR);
    
    set_cell(cp->D, gen, get_cell(cp->NR, center_col)); //  Copy center cell to D[gen]
  } 

  vmov(cp->CR, cp->SDR30);    /* Update Seed        */
  vmov(cp->D,  cp->R30);      /* Move result to R30 */

  cp_setstate(cp, CP_IDLE);  
}

/* During Time Quantum :
   I/O input transfers occur (A,B loaded), get_neighbor calls resolved 
   TimeSeed (SDTIME) is updated
   R30 is atomically advanced by 128 bits
   PSI is atomically updated
   R is atomically updated based on PSI
   1 Process Cycle occurs
   I/O output transfers occur (D loaded)
   Can be reduced by 1 quantum when incR30 is moved to previous cycle
 */
void mi5_time_quantum(cell_proc_t* restrict cp){
  if (verbose_flag) { printf ("Time Quantum\n");}

  if (!(cp_getstate(cp) == CP_IDLE)) { cp_halt(cp, "time_quantum : CellProc not Idle"); }

  mi0_incSDTIME(cp);
  mi1_incR30(cp);
  mi2_incPSI(cp);
  mi2_genR(cp);
}

/* Push Seed Registers onto stack */
void pushSD(cell_proc_t* restrict cp) {
  frame_push(cp->SDTIME, cp->Stack);
  frame_push(cp->SDR30,  cp->Stack);
  if (verbose_flag) { 
     printf("\nPUSHSD\n%s\n", frame_to_str(cp->Stack, FMT_VEC_BINARY_TEXT)); 
  }  
}

/* Pop Seed Registers from stack */
void popSD(cell_proc_t* restrict cp){
  if (verbose_flag) { 
     printf("\nPOPSD\n%s\n", frame_to_str(cp->Stack, FMT_VEC_BINARY_TEXT)); 
  }   
  frame_pop(cp->Stack, cp->SDR30);
  frame_pop(cp->Stack, cp->SDTIME);  
}

/* Push General Purpose Registers onto stack */
void pushGP(cell_proc_t* restrict cp) {
  frame_push(cp->A, cp->Stack);
  frame_push(cp->B, cp->Stack);
  frame_push(cp->C, cp->Stack);
  frame_push(cp->D, cp->Stack);

  if (verbose_flag) { 
     printf("PUSHGP\n%s\n", frame_to_str(cp->Stack, FMT_VEC_BINARY_TEXT)); 
  }  
}

/* Pop General Purpose Registers from stack */
void popGP(cell_proc_t* restrict cp) {
  frame_pop(cp->Stack, cp->D);
  frame_pop(cp->Stack, cp->C);
  frame_pop(cp->Stack, cp->B);
  frame_pop(cp->Stack, cp->A);

  if (verbose_flag) { 
     printf("POPGP\n%s\n", frame_to_str(cp->Stack, FMT_VEC_BINARY_TEXT)); 
  }  
}

/* Check clocks
 * Return 0 if OK, print error and halts otherwise
 */
int check_clocks()
{  
  int r = 0;

  if (verbose_flag) { printf("Clock Check\n"); }
   
  /* Test Clock */

  TimeSeed s0 = time_seed();
  TimeSeed s1 = time_seed();

  if (verbose_flag) {
    printf("s0: %s\n",timeseed_tostr(&s0));
    printf("s1: %s\n",timeseed_tostr(&s1));
  }

  /* Error if TimeSeeds did not change */
  if (ts_cmpE(&s0, &s1) == CELL_TRUE) {  
     halt("Clock failed\n");
  }

  return (r);
}




