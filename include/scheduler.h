#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>
#include <stddef.h>

typedef void (*task_func_pointer)(void);

typedef struct{
    const char *name;
    task_func_pointer func;
    uint32_t periodMS; //how often to run the task in ms
    uint32_t next_runMS; //next time this task is scheduled to run
    uint32_t run_count; 
    uint32_t deadline_miss; //#time it run late
}task_t; //this is the record for one task

void scheduler_intial(uint32_t startMS); //set start time
int scheduler_task_add(task_t *task_list, size_t maxN_task, task_t task);
/*
task_list - array of task_t, where tasks stores
maxN_task - the maximum capacity of the array task_list
task - the specific task to insert
*/

//tick hook
void scheduler_tick(uint32_t nowMS);
//run due tasks
void run_due_tasks(task_t *task_list, size_t num_tasks, uint32_t nowMS);

#endif
