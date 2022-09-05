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

EventGroupHandle_t xCreatedEventGroup;

#define BIT_0 (1 << 0)
#define BIT_4 (1 << 4)

void Task1(void *pvParam)
{
   while (1)
   {
      printf("----------------------------------------------------------------\n");
      printf("task1 begin to wait \n");

      xEventGroupWaitBits(
          xCreatedEventGroup,
          BIT_0 | BIT_4,
          pdTRUE,
          pdTRUE,
          portMAX_DELAY);

      printf("----------------------\n");
      printf("In task1, bit0 or bit4 is set!");

      vTaskDelay(pdMS_TO_TICKS(3000));
   }

   /* code */
}

void Task2(void *pvParam)
{
   vTaskDelay(pdMS_TO_TICKS(1000));

   while (1)
   {
      printf("----------------------!\n");
      printf("task2 begin to set bit 0!\n");

      xEventGroupSetBits(xCreatedEventGroup,BIT_0);

      vTaskDelay(pdMS_TO_TICKS(5000));
   
      printf("task2 begin to set bit 4!\n");
      xEventGroupSetBits(xCreatedEventGroup,BIT_4);

      vTaskDelay(pdMS_TO_TICKS(5000));



   }
}

void app_main(void)
{
   xCreatedEventGroup = xEventGroupCreate();

   if (xCreatedEventGroup == NULL)
   {
      printf("Error: Failed to create event_groups\n");
   }
   else
   {
      vTaskSuspendAll();
      xTaskCreate(Task1,"Task1",1024*5,NULL,1,NULL);
      xTaskCreate(Task2,"Task2",1024*5,NULL,1,NULL);
      xTaskResumeAll();
   }
}
