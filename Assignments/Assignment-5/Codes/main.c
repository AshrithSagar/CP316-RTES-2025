#include "os.h"

void task1(void) {
  while (1) {
    task_yield();
  }
}

int main(void) {
  task_create(task1);

  while (1) {
    task_yield();
  }
}
