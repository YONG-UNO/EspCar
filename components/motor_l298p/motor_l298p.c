//
// Created by DingYong on 2026/6/11.
//
#include "motor_l298p.h"
#include <driver/ledc.h>
static void motor_gpio_init(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << MOTOR_A_IN1) |
                        (1ULL << MOTOR_A_IN2) |
                        (1ULL << MOTOR_B_IN1) |
                        (1ULL << MOTOR_B_IN2) |
                        (1ULL << L298P_ENABLE_A) |
                        (1ULL << L298P_ENABLE_B),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    // 初始状态：全部拉低，电机停止
    gpio_set_level(MOTOR_A_IN1, 0);
    gpio_set_level(MOTOR_A_IN2, 0);
    gpio_set_level(MOTOR_B_IN1, 0);
    gpio_set_level(MOTOR_B_IN2, 0);

    gpio_set_level(L298P_ENABLE_A, 1);
    gpio_set_level(L298P_ENABLE_B, 1);
}

void motor_l298p_init(void)
{
    motor_gpio_init();
}

void motor_right_control(motor_dir_t dir)
{
    switch (dir) {
        case MOTOR_FORWARD:
            gpio_set_level(MOTOR_A_IN1, 0);
            gpio_set_level(MOTOR_A_IN2, 1);
            break;
        case MOTOR_BACKWARD:
            gpio_set_level(MOTOR_A_IN1, 1);
            gpio_set_level(MOTOR_A_IN2, 0);
            break;
        case MOTOR_STOP:
        default:
            gpio_set_level(MOTOR_A_IN1, 0);
            gpio_set_level(MOTOR_A_IN2, 0);
            break;
    }
}

void motor_left_control(motor_dir_t dir)
{
    switch (dir) {
        case MOTOR_FORWARD:
            gpio_set_level(MOTOR_B_IN1, 0);
            gpio_set_level(MOTOR_B_IN2, 1);
            break;
        case MOTOR_BACKWARD:
            gpio_set_level(MOTOR_B_IN1, 1);
            gpio_set_level(MOTOR_B_IN2, 0);
            break;
        case MOTOR_STOP:
        default:
            gpio_set_level(MOTOR_B_IN1, 0);
            gpio_set_level(MOTOR_B_IN2, 0);
            break;
    }
}