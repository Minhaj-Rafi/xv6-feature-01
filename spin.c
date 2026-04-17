#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  printf(1, "Spinning forever! If preemption is off, the OS will freeze now.\n");
  while(1) { } // The infinite loop
  exit();
}
