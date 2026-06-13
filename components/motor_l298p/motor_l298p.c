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

    // gpio_set_level(L298P_ENABLE_A, 1);
    // gpio_set_level(L298P_ENABLE_B, 1);
}

// PWM(LEDC) 初始化
static void motor_pwm_init(void)
{
    // 1. 配置LEDC定时器
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQ_HZ,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // 2. 配置右电机 PWM 通道
    ledc_channel_config_t ledc_ch_a = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_A,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = L298P_ENABLE_A,
        .duty           = 0,  // 初始 0 占空比 → 电机停
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_ch_a);

    // 3. 配置左电机 PWM 通道
    ledc_channel_config_t ledc_ch_b = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL_B,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = L298P_ENABLE_B,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_ch_b);
}

void motor_l298p_init(void)
{
    motor_gpio_init();
    motor_pwm_init();
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


// 左电机 PWM 调速 0~1023
void motor_left_set_speed(uint16_t duty)
{
    if(duty > 1023) duty = 1023;
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_B, duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_B);
}

// 右电机 PWM 调速 0~1023
void motor_right_set_speed(uint16_t duty)
{
    if(duty > 1023) duty = 1023;
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_A, duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_A);
}

// 左右电机同速
void motor_set_all_speed(uint16_t duty)
{
    motor_right_set_speed(duty);
    motor_left_set_speed(duty);
}