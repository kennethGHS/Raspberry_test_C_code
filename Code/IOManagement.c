//
// Created by kenneth on 16/3/21.
//

#include "IOManagement.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <pthread.h>

void *analise_Gpio(void *gpioValue) {
    int gpio = *(int *) gpioValue;
    gpioSetMode(gpio, PI_INPUT);
    int previous_state = gpioRead(gpio);
    while (active) {
        int actual_state = gpioRead(gpio);
        if (previous_state != actual_state) {
            if (actual_state == PI_HIGH) {
                printf("Change to value %d in pin %d",1,gpio);
                execute_change(1);
            } else if (actual_state == PI_LOW) {
                printf("Change to value %d in pin %d",0,gpio);
                execute_change(0);
            }
            previous_state = actual_state;
        }
    }
}

/**
 * This function is what happens when we detect a high or a low
 */
void execute_change(short mode) {
    if (mode) {
        printf("Changes to another one 1");
    } else {
        printf("Changed again top 0");
        //Execute something
    }

}

void set_gpio_list_predefined(int *list) {
    gpio_list = list;
}

void set_gpio_list(int *list, int size) {
    gpio_list = malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i) {
        gpio_list[i] = list[i];
    }
}

void clear_list() {
    if (gpio_list) {
        free(gpio_list);
    } else {
        perror("No list to free");
    }
}

void execute_monitoring() {
    pthread_t id[20];
    gpioInitialise(); // this has to be executed
    for (int i = 0; i < 20; ++i) {
        pthread_create(&(id[i]), NULL, analise_Gpio, (void *) &(gpio_list[i]));
    }
}