#include <stdio.h>
#include <string.h>
#include "fmt_vec.h"
#include "machine_logic.h"

/* CProcToStr */
char* cproc_to_str(cell_proc_t *restrict cp) {
  char* r = malloc(10000);
  memset(r, '\0', 10000);

  char* t = malloc(1000);
  memset(t, '\0',1000);
  
  sprintf(t,"CELLPROC STATE: %0X\n", cp_getstate(cp));
  strcat(r, t);

  t = fmt_vecbe(cp->A, 2);
  strcat(r, "      A : ");
  strcat(r,t);
  strcat(r,"\n");

  t = fmt_vecbe(cp->B, 2);
  strcat(r, "      B : ");
  strcat(r,t);
  strcat(r,"\n");

  t = fmt_vecbe(cp->C, 2);
  strcat(r, "      C : ");
  strcat(r,t);
  strcat(r,"\n");

  t = fmt_vecbe(cp->D, 2);
  strcat(r, "      D : ");
  strcat(r,t);
  strcat(r,"\n");

  t = fmt_vecbe(cp->X, 2);
  strcat(r, "      X : ");
  strcat(r,t);
  strcat(r,"\n");

  t = fmt_vecbe(cp->PSI, 2);
  strcat(r, "    PSI : ");
  strcat(r,t);
  strcat(r,"\n");

  t = fmt_vecbe(cp->R30, 2);
  strcat(r, "    R30 : ");
  strcat(r,t);
  strcat(r,"\n");

  t = fmt_vecbe(cp->SDR30, 2);
  strcat(r, "  SDR30 : ");
  strcat(r,t);
  strcat(r,"\n");

  t = fmt_vecbe(cp->SDTIME, 2);
  strcat(r, " SDTIME : ");
  strcat(r,t);
  strcat(r,"\n");
  
  t = fmt_vecbe(cp->R, 2);
  strcat(r, "      R : ");
  strcat(r,t);
  strcat(r,"\n");

  char* str_stack = frame_to_str(cp->Stack, 0);

  strcat(r,str_stack);
  strcat(r,"\n");

  free(str_stack);

  free(t);

  return(r);
}


void show_cp(cell_proc_t* cp) {
  char* str = cproc_to_str(cp);
  printf("%s\n",str);
  free(str);
}

