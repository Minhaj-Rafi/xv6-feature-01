#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
  int inuse[NPROC];         // 1 for process table slot is in use, 0 if not
  int pid[NPROC];           // Process ID
  int creation_time[NPROC]; // Custom FCFS Ticket Number!
  int state[NPROC];         // Process State (RUNNING, SLEEPING, etc.)
  char name[NPROC][16];     // process name
};

#endif // _PSTAT_H_
