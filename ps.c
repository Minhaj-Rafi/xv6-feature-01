#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"
#include "pstat.h"

int main(void) {
  struct pstat ps;

  if(getprocs(&ps) < 0){
    printf(2, "ps: error getting process info\n");
    exit();
  }

  printf(1, "PID\tSTATE\t\tTICKET\tNAME\n");

  for(int i = 0; i < NPROC; i++){
    if(ps.inuse[i]){
      char *state_str;
      switch(ps.state[i]){
        case 0: state_str = "UNUSED  "; break;
        case 1: state_str = "EMBRYO  "; break;
        case 2: state_str = "SLEEPING"; break;
        case 3: state_str = "RUNNABLE"; break;
        case 4: state_str = "RUNNING "; break;
        case 5: state_str = "ZOMBIE  "; break;
        default: state_str = "UNKNOWN "; break;
      }
      printf(1, "%d\t%s\t%d\t%s\n", ps.pid[i], state_str, ps.creation_time[i], ps.name[i]);
    }
  }
  exit();
}
