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

void sendTask1(void *pvParam)
{

    QueueHandle_t QHandle;

    QHandle = (QueueHandle_t)pvParam;

    BaseType_t xStatus;


    int i = 111;

    while (1)
    {

        xStatus = xQueueSend(QHandle,&i, 0);

        if (xStatus == pdPASS)
            printf("send successfully\n");
        else
            printf("send failed\n");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void sendTask2(void *pvParam)
{

    QueueHandle_t QHandle;

    QHandle = (QueueHandle_t)pvParam;

    BaseType_t xStatus;

    int i = 222;

    while (1)
    {

        xStatus = xQueueSend(QHandle,&i, 0);

        if (xStatus == pdPASS)
            printf("send successfully\n");
        else
            printf("send failed\n");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void recTask(void *pvParam)
{

    QueueHandle_t QueueSet;

    QueueSet = (QueueHandle_t)pvParam;

    QueueSetMemberHandle_t QueueData;



    BaseType_t xStatus;

    int i = 0;


    while (1)
    {

        QueueData = xQueueSelectFromSet(QueueSet,portMAX_DELAY);
        xStatus = xQueueReceive(QueueData,&i, portMAX_DELAY);

        if (xStatus == pdPASS)
            printf("receive successfully \n%d\n",i);
        else
            printf("receive failed\n");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

int testNum = 99;
int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void app_main(void)
{
    //发送线程1
    QueueHandle_t QHandle1;
    QHandle1 = xQueueCreate(5, sizeof(int));

    //发送线程2
    QueueHandle_t QHandle2;
    QHandle2 = xQueueCreate(5, sizeof(int));

    QueueSetHandle_t QueueSet;

    QueueSet = xQueueCreateSet(10);

    xQueueAddToSet(QHandle1, QueueSet);
    xQueueAddToSet(QHandle2, QueueSet);


    if ((QHandle1 != NULL) && (QHandle2 != NULL) && (QueueSet!= NULL))
    {
        printf(" create queue handle successfully\n");

        // TaskHandle_t pxTask = NULL;
        xTaskCreate(sendTask1, "sendTask1", 1024 * 5, (void *)QHandle1, 1, NULL);
        xTaskCreate(sendTask2, "sendTask2", 1024 * 5, (void *)QHandle2, 1, NULL);
        xTaskCreate(recTask, "rectask", 1024 * 5, (void *)QueueSet, 1, NULL);
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
