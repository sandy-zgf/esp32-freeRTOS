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

typedef struct A_STRUCT
{
    int id;
    char data;
} aStruct;

char *pcText = "Hello World zgf";

aStruct aStructTest = {6, 9};

void sendTask(void *pvParam)
{

    QueueHandle_t QHandle;

    QHandle = (QueueHandle_t)pvParam;

    BaseType_t xStatus;

    char *pStrToSend;

    int i = 0;

    while (1)
    {

        pStrToSend = (char *)malloc(50);

        snprintf(pStrToSend, 50, "strInglessthan50 %d", i);
        i++;

        xStatus = xQueueSend(QHandle,&pStrToSend, 0);

        if (xStatus == pdPASS)
            printf("send successfully\n");
        else
            printf("send failed\n");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void recTask(void *pvParam)
{

    QueueHandle_t QHandle;

    QHandle = (QueueHandle_t)pvParam;

    char *pStrToReceive;

    BaseType_t xStatus;


    while (1)
    {

        if (uxQueueMessagesWaiting(QHandle) != 0)
        {
            xStatus = xQueueReceive(QHandle,&pStrToReceive, 0);

            if (xStatus == pdPASS)
                printf("receive successfully \n%s\n",pStrToReceive);
            else
                printf("receive failed\n");
            free(pStrToReceive);
        }
        else
        {
            printf("no data received !\n");
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

int testNum = 99;
int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void app_main(void)
{
    QueueHandle_t QHandle;

    QHandle = xQueueCreate(5, sizeof(char *));

    if (QHandle != NULL)
    {
        printf(" create queue handle successfully\n");

        // TaskHandle_t pxTask = NULL;
        xTaskCreate(sendTask, "sendTask", 1024 * 5, (void *)QHandle, 1, NULL);
        xTaskCreate(recTask, "rectask", 1024 * 5, (void *)QHandle, 1, NULL);
    }
    else
    {
        printf(" error!!!\n");
    }

    // UBaseType_t iStack;

    // while (1)
    // {
    //     iStack = uxTaskGetStackHighWaterMark(myHandle); //获取当前堆栈的值
    //     printf("the number of istask is %d\n",iStack);
    //     vTaskDelay(1000 / portTICK_PERIOD_MS); //delay

    // }

    // vTaskSuspend(myHandle);

    // vTaskDelay(5000 / portTICK_PERIOD_MS);
    // vTaskResume(myHandle); //恢复当前的任务；

    // vTaskDelay(3000/ portTICK_PERIOD_MS);
    // vTaskSuspend(myHandle);

    // vTaskPrioritySet(myHandle,3);

    // iPriority = uxTaskPriorityGet(myHandle);

    // printf("iPriority: %d\n", iPriority);
}
