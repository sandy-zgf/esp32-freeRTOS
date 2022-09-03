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

void writeTask(void *pvParam)
{

    QueueHandle_t Mailbox;

    Mailbox = (QueueHandle_t)pvParam;

    BaseType_t xStatus;


    int i = 111;

    while (1)
    {

        xStatus = xQueueOverwrite(Mailbox,&i);

        if (xStatus == pdPASS)
            printf("send successfully\n");
        else
            printf("send failed\n");

        i++; //自加

        vTaskDelay(6000 / portTICK_PERIOD_MS);
    }
}

void readTask1(void *pvParam)
{

    QueueHandle_t Mailbox;

    Mailbox = (QueueHandle_t)pvParam;

    BaseType_t xStatus;

    int i = 0;


    while (1)
    {

        xStatus = xQueuePeek(Mailbox,&i, 0);

        if (xStatus == pdPASS)
            printf("receive successfully \n%d\n",i);
        else
            printf("receive failed\n");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void readTask2(void *pvParam)
{

    QueueHandle_t Mailbox;

    Mailbox = (QueueHandle_t)pvParam;

    BaseType_t xStatus;

    int i = 0;


    while (1)
    {

        xStatus = xQueuePeek(Mailbox,&i, 0);

        if (xStatus == pdPASS)
            printf("receive successfully \n%d\n",i);
        else
            printf("receive failed\n");

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void readTask3(void *pvParam)
{

    QueueHandle_t Mailbox;

    Mailbox = (QueueHandle_t)pvParam;

    BaseType_t xStatus;

    int i = 0;


    while (1)
    {

        xStatus = xQueuePeek(Mailbox,&i, 0);

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
    QueueHandle_t Mailbox;
    Mailbox = xQueueCreate(1, sizeof(int));



    if (Mailbox != NULL)
    {
        printf(" create queue handle successfully\n");

        // TaskHandle_t pxTask = NULL;
        xTaskCreate(writetask, "writetask", 1024 * 5, (void *)Mailbox, 1, NULL);
        xTaskCreate(readtask1, "readtask1", 1024 * 5, (void *)Mailbox, 2, NULL);
        xTaskCreate(readtask2, "readtask2", 1024 * 5, (void *)Mailbox, 2, NULL);
        xTaskCreate(readtask3, "readtask3", 1024 * 5, (void *)Mailbox, 2, NULL);
    }
    else
    {
        printf(" error!!!\n");
    }


}
