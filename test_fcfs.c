#include "types.h"
#include "stat.h"
#include "user.h"

// A massive mathematical loop to keep the CPU busy for a few seconds
void do_work() {
  int i;
  volatile int sum = 0; // volatile prevents the compiler from skipping the loop
  for(i = 0; i < 300000000; i++){
    sum = sum + i;
  }
}

int main(void) {
  int i;
  int pid;

  printf(1, "Starting FCFS Test. Watch the order of completion!\n");

  // Create 3 child processes
  for(i = 1; i <= 3; i++) {
    pid = fork();
    if(pid == 0) { // If this is the child process
      printf(1, "Process %d started\n", i);
      do_work();   // Hog the CPU for a while
      printf(1, "Process %d finished\n", i);
      exit();      // Child is done
    }
  }

  // The parent process waits for all 3 children to finish
  for(i = 0; i < 3; i++) {
    wait();
  }

  printf(1, "Test Complete!\n");
  exit();
}
