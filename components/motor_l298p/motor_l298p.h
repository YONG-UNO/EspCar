//
// Created by DingYong on 2026/6/11.
//
#ifndef MOTOR_L298P_H
#define MOTOR_L298P_H

#define MOTOR_A_IN1  GPIO_NUM_4
#define MOTOR_A_IN2  GPIO_NUM_5
#define MOTOR_B_IN1  GPIO_NUM_6
#define MOTOR_B_IN2  GPIO_NUM_7
#define L298P_ENABLE_A  GPIO_NUM_16
#define L298P_ENABLE_B  GPIO_NUM_17

// PWM 配置
#define LEDC_TIMER       LEDC_TIMER_0
#define LEDC_MODE        LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL_A   LEDC_CHANNEL_0
#define LEDC_CHANNEL_B   LEDC_CHANNEL_1
#define LEDC_DUTY_RES    LEDC_TIMER_10_BIT  // 0-1023 占空比
#define LEDC_FREQ_HZ     1000               // 1kHz PWM

// 电机方向定义
typedef enum {
    MOTOR_STOP = 0,
    MOTOR_FORWARD,
    MOTOR_BACKWARD
} motor_dir_t;


// 初始化L298P驱动
void motor_l298p_init(void);

// 控制电机A（方向控制，无PWM）
void motor_right_control(motor_dir_t dir);

// 控制电机B（方向控制，无PWM）
void motor_left_control(motor_dir_t dir);

#endif //MOTOR_L298P_H