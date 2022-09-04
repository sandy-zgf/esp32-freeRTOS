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

#include "freertos/semphr.h" //add by zgf

SemaphoreHandle_t mutexHandle;

void Task1(void *pvParam)
{
    while (1)
    {
        printf("----------------------------------------------------------------\n");
        printf("task1 begin\n");
        xSemaphoreTakeRecursive(mutexHandle, portMAX_DELAY);

        printf("Task1 take A!\n");
        for (int i = 0; i < 10; i++)
        {
            printf("task1 i = %d for A\n", i);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        xSemaphoreTakeRecursive(mutexHandle, portMAX_DELAY);

        printf("Task1 take B!\n");
        for (int i = 0; i < 10; i++)
        {
            printf("task1 i = %d for B\n", i);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }


        printf("Task1 give B!\n");
        xSemaphoreGiveRecursive(mutexHandle);

        vTaskDelay(pdMS_TO_TICKS(3000));

        printf("Task1 give A!\n");
        xSemaphoreGiveRecursive(mutexHandle);

        vTaskDelay(pdMS_TO_TICKS(3000));

        /* code */
    }
}

void Task2(void *pvParam)
{
    vTaskDelay(pdMS_TO_TICKS(1000));

    while (1)
    {
        printf("----------------------------------------------------------------\n");
        printf("task2 begin\n");
        xSemaphoreTakeRecursive(mutexHandle, portMAX_DELAY);

        printf("Task2 take !\n");
        for (int i = 0; i < 10; i++)
        {
            printf("task2 i = %d\n", i);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        printf("Task2 give !\n");
        xSemaphoreGiveRecursive(mutexHandle);

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void app_main(void)
{
    mutexHandle = xSemaphoreCreateRecursiveMutex();
    // mutexHandle = xSemaphoreCreateBinary();
    vTaskSuspendAll();
    xTaskCreate(Task1, "Task1", 1024 * 5, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", 1024 * 5, NULL, 1, NULL);
    // xTaskCreate(Task3, "Task3", 1024 * 5, NULL, 3, NULL);

    xTaskResumeAll();
}
