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
int  variable =1;
void * execute_analysis(){
    pinMode(23,1);
    pinMode(24,1);
    int result =digitalRead(23);
    int result2 = digitalRead(24);
    int prev_result2= result2;
    int prev_result = result;
    while (variable){
        result = digitalRead(23);
        result2 = digitalRead(24);
        if (result!= prev_result) {
            printf("changed to value %d in pin %d", result,23);
            prev_result = result;
            sleep(1);
        }
        if (result2!= prev_result2) {
            printf("changed to value %d in pin %d", result,24);
            prev_result2 = result2;
            sleep(1);
        }
    }
    gpio_unexport(23);
    gpio_unexport(24);
}
int main()
{
    pthread_t id[1];
    pthread_create(&(id[0]), NULL, execute_analysis,NULL);
    char a_word[50];
    printf ("Press any to finish ");
    scanf ("%s", a_word);
    variable = 0;
//    printf("test");
//    int array[] = {23,24,35};
//    set_gpio_list(array,3);
//    execute_monitoring();
//    char array[20];
//    int prueba = 1000;
//    snprintf(array,10,"%d",prueba);
//    printf("test es %s",array);
//    printf("El largo fue %d",strlen(array));


    return 0;
}
