#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  printf(1, "User space calling...\n");
  hello();
  printf(1, "Success!\n");
  exit();
}
