
/*                                 
 * Command-line processing.
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
#include <math.h>
#include <errno.h>
#include "command.h"
#include "machine_logic.h"
#include "fmt_vec.h"
#include "fmt_cp.h"

typedef struct usage_t {
  char* name;
  char* format;
  char* description;
} usage_t;

typedef struct fib_t {
  size_t n1;
  size_t n2;
} fib_t;

typedef struct profile_t {
  size_t rbps;            // Randomness in bps
  float entropy;          // H
} profile_t;



/* Flag set by ‘--verbose’. */
int verbose_flag = 0;

int profile_flag = 0;

unsigned int uint_limit( unsigned int lower, unsigned int upper, unsigned int val){
    return ((val < lower) ? lower : (val > upper ? upper : val));
}

fib_t* new_fib() {
  fib_t* t = malloc(sizeof(fib_t));
  t->n1 = 1;
  t->n2 = 2;
  return (t);
}

size_t fib (fib_t* f) {
  size_t r = f->n1 + f->n2;
  f->n1 = f->n2;
  f->n2 = r;
  return (r);
}


void to_stream(FILE* stream, size_t num_blocks, int output_format, vec128bec_t* v){
size_t i;
char* out_str;
uint8_t* bytes;
  
  if ((output_format == FMT_VEC_BINARY) && (stream != stdout)) {    /* Binary File */
        bytes = malloc(16 * num_blocks);
        if (bytes == NULL) { halt  ("to_stream : Out of Memory"); }
        
        for (i=0; i<num_blocks; i++) {
           vecbe_pack(&bytes[i*16],&v[i]);
        }     
        fwrite(bytes, 16, num_blocks, stream);
        free(bytes);
  } else {                                                          /* Text File */
      for (i=0; i<num_blocks; i++) {
        out_str = fmt_vecbe(&v[i], output_format);
        fprintf(stream,"%s\n",out_str);
        free(out_str);
        } 
  }
}



/* Profile
 * Run escalating loads until desired number of seconds have elapsed.
 * Calculates bps produced
 */
profile_t profile(cell_proc_t* cp, unsigned int profile_seconds){
  profile_t r;
  size_t i,j;
  size_t load = 0;
  size_t cumulative_load = 0;

  fib_t* f = new_fib();
  unsigned int start_time = (unsigned int) time (NULL);
  unsigned int current_time;
  unsigned int cumulative_seconds = 0;
  float bps = 0;
  char speed_factor = ' '; // k M 
  
  /* Profile rand */
  for (i=0; i<100; i++) {
     load = fib(f);
     cumulative_load += load;  // Number of vectors produced
     for (j=0; j<load; j++){
       mi5_time_quantum(cp);   
     }
     current_time = (unsigned int) time (NULL);
     cumulative_seconds += current_time - start_time;

     if (cumulative_seconds >= profile_seconds) {
        bps =  ((cumulative_load * 128) / cumulative_seconds);
        r.rbps = bps;

        if (bps > 1000000) {
          speed_factor = 'M';
          bps = bps / 1000000;
        } else if (bps > 1000) {
              speed_factor = 'k';
              bps = bps / 1000;
        }  

        break;
     }
  }

  /* Entropy measurement 
     Generate 12,800 bits
     Calculate H per Shannon's Mathematical Theory of Communication
   */
  uint32_t weight = 0;
  double_t p_0 = 0;
  double_t p_1 = 0;

  for (i=0; i<100; i++) {
     mi5_time_quantum(cp);
     weight += vecbe_hamming_weight(cp->R);
  }

  p_1 = ((double_t) weight) / 12800;     // Probability of Bit = 1
  p_0 = 1.0 - p_1;                       // Probability of Bit = 0
  
  r.entropy =  0.0 - ((p_1 * (log2f(p_1))) + (p_0 * (log2f(p_0))));

  printf("%0.2f %cbps  Entropy (H): %0.5f\n", bps,  speed_factor, r.entropy);
  return (r);
}



void usage(cell_proc_t* cp){
  
  static usage_t u[14];
  int i;

  vec128bec_t* v = vec_alloc();

  for (i=0; i<NUM_FORMATS; i++){
    mi5_time_quantum(cp);
    vmov(cp->R,v);

    switch (i) {
      case FMT_VEC_BINARY: 
              u[i].name = "Pure";
              u[i].description = "128-bit Binary";
              u[i].format = fmt_vecbe(v, i);
              break;

      case FMT_VEC_SHA1: 
              u[i].name = "SHA1";
              u[i].description = "SHA1 Format";
              u[i].format = fmt_vecbe(v, i);
              break;

      case FMT_VEC_BINARY_TEXT: 
              u[i].name = "BINARY";
              u[i].description = "Text Mode Binary";
              u[i].format = malloc(128+1);
              memset(u[i].format, '\0', 128+1);
              strcat(u[i].format,"...");
              strncpy(u[i].format+3,fmt_vecbe(v, i),30);
              u[i].format[32] = '\0';        
              break;

      case 3: u[i].name = "RESERVED";
              u[i].description = "";
              u[i].format = fmt_vecbe(v, i); 
              break;

      case FMT_VEC_IPV4: 
               u[i].name = "IPV4";
               u[i].description = "IPV4 Address";
               u[i].format = fmt_vecbe(v, i);
               break;

      case FMT_VEC_GUID: 
              u[i].name = "GUID";
              u[i].description = "Globally Unique ID";
              u[i].format = fmt_vecbe(v, i); 
              break;

      case FMT_VEC_IPV6: 
              u[i].name = "IPV6";
              u[i].description = "IPV6 Address";
              u[i].format = fmt_vecbe(v,i);
              break;

      case 7: u[i].name = "RESERVED";
              u[i].description = "";
              u[i].format = fmt_vecbe(v, i); 
              break;

      case FMT_VEC_PSI: 
              u[i].name = "PSI";
              u[i].description = "Time Fingerprint";
              u[i].format = fmt_vecbe(v,i);
              break;

      case 9: u[i].name = "RESERVED";
              u[i].description = "";
              u[i].format = fmt_vecbe(v, i); 
              break;

      case FMT_VEC_INT32: 
               u[i].name = "INT";
               u[i].description = "32-bit Unsigned Integer";
               u[i].format = fmt_vecbe(v,i);
               break;

      case FMT_VEC_UUID: 
              u[i].name = "UUID V4";
              u[i].description = "Universally Unique ID";
              u[i].format = fmt_vecbe(v, i); 
              break;

      case FMT_VEC_BASE64: 
              u[i].name = "BASE64";
              u[i].description = "Text Encoding";
              u[i].format = fmt_vecbe(v, i); 
              break;

      case 13: u[i].name = "RESERVED";
              u[i].description = "";
              u[i].format = fmt_vecbe(v, i); 
              break;

      default : u[i].name = "UNDEFINED";
                u[i].description = "UNDEFINED";
                u[i].format = "UNDEFINED";

    } 
  }   

  char* msg = malloc(10000);
  if (msg == NULL) { halt("Out of Memory");}
  memset(msg, '\0', 10000);
  
  strcat(msg, "MKRAND - A Randomness Well  [von Neumann] (Test Article 1)\n");
  strcat(msg, "Copyright (c) 2013 TAG Universal Machine.\n\n");
  strcat(msg, "USAGE: mkrand [-f format] [-n blocks] [-o filename] [--profile] [--verbose]\n");
  strcat(msg, "Formats:\n");

  printf("%s",msg);

  for (i=0; i<NUM_FORMATS; i++){
       printf("%2d  - %10s      %40s     %30s\n",i,u[i].name, u[i].format, u[i].description);
       free(u[i].format);
     }  
  free(msg);
}


int main(int argc, char *argv[]) 
{
   int c;
   size_t i;
   FILE* out_stream;

   int output_format = FMT_VEC_BINARY;
   int show_usage = 0;

   char* out_file_name = NULL;

   cell_proc_t cpa;
   cell_proc_t* cp = &cpa;

   vec128bec_t* out_vecs;

   /* Set limits for number of blocks */
   size_t num_blocks = 1;
   const size_t MIN_BLOCKS = 0;
   const size_t MAX_BLOCKS = UINT_MAX;
   
   verbose_flag = 0;
   opterr = 0;
     
   while (1)
     {
       static struct option long_options[] =
         {
           /* These options set a flag. */
           {"verbose", no_argument,       &verbose_flag, 1},
           {"profile", no_argument,       &profile_flag, 1},
           /* These options don't set a flag.
              We distinguish them by their indices. */
           {"blocks",  required_argument,       0, 'n'},  // Chain the production of n blocks
           {"output",  required_argument,       0, 'o'},  // Write to file         
           {"format",  required_argument,       0, 'f'},
           {"help",    no_argument,             0, 'h'},  // Usage
           {0, 0, 0, 0}
         };
       /* getopt_long stores the option index here. */
       int option_index = 0;
 
       c = getopt_long (argc, argv, "n:o:f:h?",
                        long_options, &option_index);
 
       /* Detect the end of the options. */
       if (c == -1)
         break;
 
       switch (c)
         {
         case 0:
           /* If this option set a flag, do nothing else now. */
           if (long_options[option_index].flag != 0)
             break;
           printf ("option %s", long_options[option_index].name);
           if (optarg)
             printf (" with arg %s", optarg);
           printf ("\n");
           break;
 

        case 'f':
           output_format = uint_limit(0, NUM_FORMATS-1, strtol(optarg, NULL, 10));
           break;
 
         case 'n':
           num_blocks = uint_limit(MIN_BLOCKS, MAX_BLOCKS, (size_t) strtol(optarg, NULL, 10));
           break;

         case 'o':
           out_file_name = optarg;
           break;

         case '?':
           /* getopt_long already printed an error message. */
           show_usage = 1;
           break;

        case 'h':
           show_usage = 1;
           break;
 
         default:
           show_usage = 1;
         }
     }

     check_clocks();

     cp_init(cp);

     if (show_usage) {
       usage(cp);
       exit(EXIT_SUCCESS);
    }

    if (profile_flag) {
      profile(cp, 60);  // ~1 Minute profile
      exit(EXIT_SUCCESS);
    }

    if (out_file_name) {
      out_stream = fopen(out_file_name, "w");
      if (out_stream == NULL) { halt ("Error opening output file."); }
    } else {
      out_stream = stdout;
    }

    if (num_blocks == 0) {
      out_vecs = malloc(sizeof(vec128bec_t));              /* Streaming, one vector at a time */
      memset(out_vecs, '\0', (sizeof(vec128bec_t)));
      while (1) {
        mi5_time_quantum(cp);
        vcopy(cp->R, &out_vecs[0]);
        to_stream(out_stream, 1, output_format, out_vecs);
      }
    } else {
      out_vecs = malloc(sizeof(vec128bec_t) * num_blocks); /* Block Mode */
      memset(out_vecs, '\0', (sizeof(vec128bec_t) * num_blocks));
    }

    if (out_vecs == NULL) { halt ("Command - Out of Memory"); }

    for (i = 0; i < num_blocks; i++) {
       mi5_time_quantum(cp);
       vcopy(cp->R, &out_vecs[i]);
    }

    to_stream(out_stream, num_blocks, output_format, out_vecs);

    fclose(out_stream);

    cp_free(cp);

    return (EXIT_SUCCESS);
}


