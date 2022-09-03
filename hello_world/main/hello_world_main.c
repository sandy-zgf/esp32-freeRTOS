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

SemaphoreHandle_t semphrHandle;

int iCount = 0; //

void myTask1(void *pvParam)
{
    while (1)
    {
        xSemaphoreTake(semphrHandle, portMAX_DELAY);
        for (int i = 0; i < 10; i++)
        {
            iCount++; // count
            printf("myTask1 iCount = %d\n", iCount);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        xSemaphoreGive(semphrHandle);
        vTaskDelay(pdMS_TO_TICKS(1000));

        /* code */
    }
}

void myTask2(void *pvParam)
{
    while (1)
    {
        xSemaphoreTake(semphrHandle, portMAX_DELAY);
        for (int i = 0; i < 10; i++)
        {
            iCount++; // count
            printf("myTask2 iCount = %d\n", iCount);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        xSemaphoreGive(semphrHandle);
        vTaskDelay(pdMS_TO_TICKS(1000));

        /* code */
    }
}

int testNum = 99;
int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void app_main(void)
{
    semphrHandle = xSemaphoreCreateBinary();
    xSemaphoreGive(semphrHandle);
    
    xTaskCreate(myTask1,"myTask1",1024*5,NULL,1,NULL);
    xTaskCreate(myTask2,"myTask2",1024*5,NULL,1,NULL);
}
