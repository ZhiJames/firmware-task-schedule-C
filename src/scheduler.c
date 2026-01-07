#include "scheduler.h"
#include <stdio.h>
#include <stdint.h>

static size_t num_tasks_tracker; //I need this to let scheduler_task_add to now where to insert task

void scheduler_initial(uint32_t startMS){
    (void)startMS;
    num_tasks_tracker = 0;
}

int scheduler_task_add(task_t *task_list, size_t maxN_task, task_t task){
    //saftey and overflow check
    if(task_list == NULL){
        return 0;
    }
    if(num_tasks_tracker >= maxN_task){
        return 0;
    }

    task_list[num_tasks_tracker] = task; //store the task to task list
    num_tasks_tracker++;
    return 1;
}

/*I can centralize timing related bookkeeping later
  Left empty intentionally */
void scheduler_tick(uint32_t nowMS){
    (void)nowMS;
}

void run_due_tasks(task_t *task_list, size_t num_tasks, uint32_t nowMS){
    for(size_t i = 0; i < num_tasks; i++){
        task_t *t = &task_list[i];

        if(t->func == NULL){
            continue;
        }
        if(t->periodMS == 0){
            continue;
        }
        if(nowMS >= t->next_runMS){
            if(nowMS > t->next_runMS){
                t->deadline_miss++;
            }

            t->func();
            t-> run_count++;
            t->next_runMS += t->periodMS;
        }
    }
}
