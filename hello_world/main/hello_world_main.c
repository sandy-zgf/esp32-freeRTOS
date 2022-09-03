/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "freertos/timers.h" //add by zgf

void TimerCallback(TimerHandle_t xTimer)
{
    const char * name;

    name = pcTimerGetName(xTimer);

    printf("one shot!!! %s\n",name);
}

typedef struct A_STRUCT
{
    int id;
    char data;
} aStruct;

char *pcText = "Hello World zgf";

aStruct aStructTest = {6, 9};

int testNum = 99;
int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void app_main(void)
{

    TimerHandle_t xTimer1;
    TimerHandle_t xTimer2;

    xTimer1 = xTimerCreate("Timer1", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, TimerCallback); // run once per second
    xTimer2 = xTimerCreate("Timer2", pdMS_TO_TICKS(2000), pdTRUE, (void *)0, TimerCallback); // run once per second

    xTimerStart(xTimer1, 0);
    xTimerStart(xTimer2, 0);

    vTaskDelay(pdMS_TO_TICKS(6000));
    xTimerChangePeriod(xTimer1,pdMS_TO_TICKS(6000), 0); //

    // while (1)
    // {
    //     vTaskDelay(pdMS_TO_TICKS(1000));
    //     xTimerReset(xTimer2, 0);
    // }
    

    // vTaskDelay(pdMS_TO_TICKS(6000));


    // xTimerStop(xTimer1,0);
}
