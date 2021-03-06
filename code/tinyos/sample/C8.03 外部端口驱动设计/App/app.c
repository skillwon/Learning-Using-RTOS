/**
 * @brief tOS应用示例
 * @details
 * @author 01课堂 李述铜 http://01ketang.cc
 * @date 2017-06-01
 * @version 1.0
 * @copyright 版权所有，禁止用于商业用途
 */
#include "tinyOS.h"
#include "app.h"
#include "hal.h"

#include "button.h"
#include "uart.h"
#include "extio.h"

static tTaskStack task1Env[TASK1_ENV_SIZE];     // 任务1的堆栈空间
static tTask task1;

void task1Entry (void * param) {

    for (;;) {
        ExtIOSetDir(ExtIOPin0, 0);
        ExtIOSetState(ExtIOPin0, ExtIOHigh);
        tTaskDelay(1);

        ExtIOSetDir(ExtIOPin1, 1);
        ExtIOSetDir(ExtIOPin2, 0);
        ExtIOSetState(ExtIOPin2, ExtIOGetState(ExtIOPin1));
        tTaskDelay(1);
    }
}

/**
 * App的初始化
 */
void tInitApp (void) {
    halInit();

    ButtonInit();
    UartInit();
    ExtIOInit();

    tTaskInit(&task1, task1Entry, (void *) 0x0, TASK1_PRIO, task1Env, sizeof(task1Env));
}

