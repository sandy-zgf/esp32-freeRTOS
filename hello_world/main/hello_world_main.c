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

#include "freertos/queue.h" //add by zgf
#include "freertos/event_groups.h"

static TaskHandle_t xTask1 = NULL;

void Task1(void *pvParam)
{
   while (1)
   {
      printf("----------------------------------\n");
      printf("task1 begin\n");

      ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

      printf("----------------------------------\n");
      printf("task1 got notification !!!\n");
      vTaskDelay(pdMS_TO_TICKS(3000));
      /* code */
   }

   /* code */
}

void Task2(void *pvParam)
{
   while (1)
   {
      vTaskDelay(pdMS_TO_TICKS(4000));
      printf("----------------------------------\n");
      printf("task2 begin notify 1\n");

      xTaskNotifyGive(xTask1);
   }
}

void app_main(void)
{

   vTaskSuspendAll();
   xTaskCreate(Task1, "Task1", 1024 * 5, NULL, 1, &xTask1);
   xTaskCreate(Task2, "Task2", 1024 * 5, NULL, 1, NULL);
   xTaskResumeAll();
}
