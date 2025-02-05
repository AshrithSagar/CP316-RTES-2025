typedef void (*taskfn_t)(void);
void task_create(taskfn_t entry);
void task_yield(void);
