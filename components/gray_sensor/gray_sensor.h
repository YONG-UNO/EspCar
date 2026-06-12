//
// Created by DingYong on 2026/6/11.
//
#ifndef GRAY_SENSOR_H
#define GRAY_SENSOR_H

#include <stdint.h>

#define GRAY_PIN_1    GPIO_NUM_35
#define GRAY_PIN_2    GPIO_NUM_36
#define GRAY_PIN_3    GPIO_NUM_37
#define GRAY_PIN_4    GPIO_NUM_38
#define GRAY_PIN_5    GPIO_NUM_39

#define GRAY_PIN_COUNT  5

void gray_sensor_init(void);
int gray_sensor_read(uint8_t ch);

#endif //GRAY_SENSOR_H