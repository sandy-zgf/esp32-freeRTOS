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

void carInTask(void *pvParam)
{
    int emptySpace = 0;

    BaseType_t iResult;
    while (1)
    {
        emptySpace = uxSemaphoreGetCount(semphrHandle);
        printf("emptySpace = %d\n", emptySpace);

        iResult = xSemaphoreTake(semphrHandle, 0);

        if (iResult == pdPASS)
        {
            printf("one car in!\n");
        }
        else
        {
            printf("no car in!");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));

        /* code */
    }
}

void carOutTask(void *pvParam)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(6000));
        xSemaphoreGive(semphrHandle);

        printf("one car out!\n");

        /* code */
    }
}

int testNum = 99;
int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void app_main(void)
{
    semphrHandle = xSemaphoreCreateCounting(5, 5);
    xSemaphoreGive(semphrHandle);

    xTaskCreate(carInTask, "carInTask", 1024 * 5, NULL, 1, NULL);
    xTaskCreate(carOutTask, "carOutTask", 1024 * 5, NULL, 1, NULL);
}
