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

#include <string.h>
#include "freertos/message_buffer.h"

MessageBufferHandle_t MessageBufferHandle = NULL;

void Task1(void *pvParam)
{
   int i = 0;
   int str_length = 0;
   int send_bytes = 0;
   char tx_buf[50]; //发送的数据

   for (int i = 0; i < 3; i++)
   {
      str_length = sprintf(tx_buf, "hello I am zgf number %d", i);
      send_bytes = xMessageBufferSend(MessageBufferHandle,
                                      (void *)tx_buf,
                                      str_length,
                                      portMAX_DELAY);

      printf("Send : i = %d,send_bytes = %d!\n", i, send_bytes);

      /* code */
   }

   vTaskDelete(NULL);

   /* code */
}

void Task2(void *pvParam)
{
   char rx_buf[200]; //
   int rec_bytes = 0;

   vTaskDelay(pdMS_TO_TICKS(3000));
   while (1)
   {
      memset(rx_buf, 0, sizeof(rx_buf));
      rec_bytes = xMessageBufferReceive(MessageBufferHandle,
                                       (void *)rx_buf,
                                       sizeof(rx_buf),
                                       portMAX_DELAY);

      printf("Receive : rec_bytes = %d,data = %s!\n", rec_bytes, rx_buf);
      vTaskDelay(pdMS_TO_TICKS(1000));
   }
}
void app_main(void)
{

   MessageBufferHandle = xMessageBufferCreate(1000);

   if (MessageBufferHandle == NULL)
   {
      printf("MessageBufferHandle creation failed\n");
   }
   else
   {

      vTaskSuspendAll();
      xTaskCreate(Task1, "Task1", 1024 * 5, NULL, 1, NULL);
      xTaskCreate(Task2, "Task2", 1024 * 5, NULL, 1, NULL);
      xTaskResumeAll();
   }
}
