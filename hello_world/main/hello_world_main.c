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

EventGroupHandle_t xEventBits;

#define TASK_0_BIT (1 << 0)
#define TASK_1_BIT (1 << 1)
#define TASK_2_BIT (1 << 2)

#define All_SYNC_BITS (TASK_0_BIT | TASK_1_BIT | TASK_2_BIT)

void Task0(void *pvParam)
{
   while (1)
   {
      printf("----------------------------------\n");
      printf("task0 begin\n");

      vTaskDelay(pdMS_TO_TICKS(1000));

      printf("----------------------------------\n");
      printf("task0 set bit 0\n");

      xEventGroupSync(
          xEventBits,
          TASK_0_BIT,
          All_SYNC_BITS,
          portMAX_DELAY);

      printf("task0 sync !!!\n");
      vTaskDelay(pdMS_TO_TICKS(8000));
      /* code */
   }
}

void Task1(void *pvParam)
{
   while (1)
   {
      printf("----------------------------------\n");
      printf("task1 begin\n");

      vTaskDelay(pdMS_TO_TICKS(3000));

      printf("----------------------------------\n");
      printf("task1 set bit 1\n");

      xEventGroupSync(
          xEventBits,
          TASK_1_BIT,
          All_SYNC_BITS,
          portMAX_DELAY);

      printf("task1 sync !!!\n");
      vTaskDelay(pdMS_TO_TICKS(8000));
      /* code */
   }

   /* code */
}

void Task2(void *pvParam)
{
   while (1)
   {
      printf("----------------------------------\n");
      printf("task2 begin\n");

      vTaskDelay(pdMS_TO_TICKS(5000));

      printf("----------------------------------\n");
      printf("task2 set bit 2\n");

      xEventGroupSync(
          xEventBits,
          TASK_2_BIT,
          All_SYNC_BITS,
          portMAX_DELAY);

      printf("task2 sync !!!\n");
      vTaskDelay(pdMS_TO_TICKS(8000));
      /* code */
   }
}

void app_main(void)
{
   xEventBits = xEventGroupCreate();

   if (xEventBits == NULL)
   {
      printf("Error: Failed to create event_groups\n");
   }
   else
   {
      vTaskSuspendAll();
      xTaskCreate(Task0, "Task0", 1024 * 5, NULL, 1, NULL);
      xTaskCreate(Task1, "Task1", 1024 * 5, NULL, 1, NULL);
      xTaskCreate(Task2, "Task2", 1024 * 5, NULL, 1, NULL);
      xTaskResumeAll();
   }
}
