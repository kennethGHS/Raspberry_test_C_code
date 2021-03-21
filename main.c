#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "Code/IOManagement.h"
#include "Code/ManualGPIO.h"

int main()
{
 pinMode(23,1);
 int result =digitalRead(23);
 int prev_result = result;
 while (1){
     result = digitalRead(23);
     if (result!= prev_result) {
         printf("changed to value %d", result);
         prev_result = result;
         sleep(0.1);
     }
    }
//    printf("test");
    int array[] = {23,24,35};
    set_gpio_list(array,3);
    execute_monitoring();
//    char array[20];
//    int prueba = 1000;
//    snprintf(array,10,"%d",prueba);
//    printf("test es %s",array);
//    printf("El largo fue %d",strlen(array));


    return 0;
}
