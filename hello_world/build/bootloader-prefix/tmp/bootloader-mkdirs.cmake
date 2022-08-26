# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/esp/esp-idf/components/bootloader/subproject"
  "D:/file_zgf/vscode/esp32/esp32-freeRTOS/esp32-freeRTOS/hello_world/build/bootloader"
  "D:/file_zgf/vscode/esp32/esp32-freeRTOS/esp32-freeRTOS/hello_world/build/bootloader-prefix"
  "D:/file_zgf/vscode/esp32/esp32-freeRTOS/esp32-freeRTOS/hello_world/build/bootloader-prefix/tmp"
  "D:/file_zgf/vscode/esp32/esp32-freeRTOS/esp32-freeRTOS/hello_world/build/bootloader-prefix/src/bootloader-stamp"
  "D:/file_zgf/vscode/esp32/esp32-freeRTOS/esp32-freeRTOS/hello_world/build/bootloader-prefix/src"
  "D:/file_zgf/vscode/esp32/esp32-freeRTOS/esp32-freeRTOS/hello_world/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/file_zgf/vscode/esp32/esp32-freeRTOS/esp32-freeRTOS/hello_world/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
