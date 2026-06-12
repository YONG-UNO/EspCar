//
// Created by DingYong on 2026/6/11.
//
#include "gray_sensor.h"
#include <driver/gpio.h>
#include <soc/gpio_num.h>

static const gpio_num_t gray_pins[] = {
    GRAY_PIN_1,
    GRAY_PIN_2,
    GRAY_PIN_3,
    GRAY_PIN_4,
    GRAY_PIN_5
};

void gray_sensor_init(void)
{
    gpio_config_t io_conf = {0};
    uint64_t pin_mask = 0;

    for(uint8_t i = 0; i < GRAY_PIN_COUNT; i++)
    {
        pin_mask |= 1ULL << gray_pins[i];
    }

    io_conf.pin_bit_mask   = pin_mask;
    io_conf.mode          = GPIO_MODE_INPUT;
    io_conf.pull_up_en    = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en  = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type     = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);
}

int gray_sensor_read(uint8_t ch)
{
    if(ch >= GRAY_PIN_COUNT)
    {
        return 1;
    }
    return gpio_get_level(gray_pins[ch]);
}