#include <stdio.h>
#include <stdint.h>
#include "scheduler.h"

static uint32_t current_sysT_ms = 0; //set the current system time in ms

static void task_uartRX(void){
    static uint32_t counter = 0;
    counter++;
    if((counter % 20) == 0){
        printf("UART_RX: t = %u\n", current_sysT_ms);
    }
}
static void task_command_parse(void){
    static uint32_t counter = 0;
    counter++;
    if((counter % 5) == 0){
        printf("Command parse: t = %u\n", current_sysT_ms);
    }
}

static void task_fsm(void){
    static uint32_t counter = 0;
    counter++;
    if((counter % 2) == 0){
        printf("Finit State Machine: t = %u\n", current_sysT_ms);
    }
}

static void task_dialog(void){
    printf("Dialog: t = %u\n", current_sysT_ms);
}

int main(void){
    task_t tasks[4];
    size_t num_tasks = 4;

    scheduler_initial(0);
    (void)scheduler_task_add(tasks, 4, (task_t){ "uart_rx",   task_uartRX,   1,   0, 0, 0 });
    (void)scheduler_task_add(tasks, 4, (task_t){ "cmd_parse", task_command_parse, 5,   0, 0, 0 });
    (void)scheduler_task_add(tasks, 4, (task_t){ "fsm",       task_fsm,       10,  0, 0, 0 });
    (void)scheduler_task_add(tasks, 4, (task_t){ "diag",      task_dialog,      100, 0, 0, 0 });

    const uint32_t tick_ms = 1;

    for(uint32_t now_ms = 0; now_ms <= 200; now_ms += tick_ms){
        current_sysT_ms = now_ms;
        scheduler_tick(now_ms);
        run_due_tasks(tasks, num_tasks, now_ms);
    }

    printf("Simulation Complete.\n");
    return 0;
}
