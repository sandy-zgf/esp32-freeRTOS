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
   uint32_t ulNotifiedValue;
   while (1)
   {
      printf("----------------------------------\n");
      printf("task1 begin\n");

      xTaskNotifyWait(0x00,
                      ULONG_MAX,
                      &ulNotifiedValue,
                      portMAX_DELAY); //
      if ((ulNotifiedValue & 0x01) != 0)
      {
         printf("task1 process bit0 event!\n");
      }
      if ((ulNotifiedValue & 0x02) != 0)
      {
         printf("task1 process bit1 event!\n");
      }
      if ((ulNotifiedValue & 0x04) != 0)
      {
         printf("task1 process bit2 event!\n");
      }

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

      xTaskNotify(xTask1,0x01,eSetValueWithOverwrite);
      vTaskDelay(pdMS_TO_TICKS(4000));

      xTaskNotify(xTask1,0x02,eSetValueWithOverwrite);
      vTaskDelay(pdMS_TO_TICKS(4000));

      xTaskNotify(xTask1,0x04,eSetValueWithOverwrite);
      vTaskDelay(pdMS_TO_TICKS(4000));
   }
}

void app_main(void)
{

   vTaskSuspendAll();
   xTaskCreate(Task1, "Task1", 1024 * 5, NULL, 1, &xTask1);
   xTaskCreate(Task2, "Task2", 1024 * 5, NULL, 1, NULL);
   xTaskResumeAll();
}
