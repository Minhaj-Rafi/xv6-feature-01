#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int main(void) {
  printf(1, "=== FEATURE 01 TEST CASE ===\n");
  printf(1, "Spawning 3 background tasks to test FCFS tickets...\n\n");

  // Fork 3 child processes
  for(int i = 0; i < 3; i++) {
    if(fork() == 0) {
      // Children sleep for 200 ticks so they stay in the process table
      sleep(200);
      exit();
    }
  }

  // Parent sleeps for just 10 ticks to let the children initialize
  sleep(10);

  // --- AUTOMATIC PS TABLE ---
  struct pstat ps;
  if(getprocs(&ps) < 0) {
    printf(2, "Error getting process info\n");
    exit();
  }

  printf(1, "--- Live Process Table ---\n");
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
  printf(1, "--------------------------\n\n");

  // Parent waits for the children to wake up and finish
  printf(1, "Waiting for tasks to finish...\n");
  for(int i = 0; i < 3; i++) {
    wait();
  }

  printf(1, "Feature 01 Test Case Complete. Success!\n");
  exit();
}
