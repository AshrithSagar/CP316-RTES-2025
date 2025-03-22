#include "os.h"

void task1(void) {
  while (1) {
    task_yield();
  }
}

void task2(void) {
  while (1) {
    task_yield();
  }
}

void task3(void) {
  while (1) {
    task_yield();
  }
}

int main(void) {
  task_create(task1);
  task_create(task2);
  task_create(task3);

  while (1) {
    task_yield();
  }
}
