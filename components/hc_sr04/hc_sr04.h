//
// Created by DingYong on 2026/6/13.
//
#ifndef HC_SR04_H
#define HC_SR04_H

#include <esp_err.h>
#include <driver/gpio.h>

/**
 * @brief HC-SR04 GPIO模式初始化
 * @param trig_io 触发引脚
 * @param echo_io 回声引脚
 * @return ESP_OK 成功
 */
esp_err_t hc_sr04_init(gpio_num_t trig_io, gpio_num_t echo_io);

/**
 * @brief 单次读取距离
 * @return 距离(单位 cm)，异常/超出量程返回 0
 * @note 两次读取间隔 ≥ 200ms
 */
uint16_t hc_sr04_get_dist(void);

/**
 * @brief 多次采样滤波读取距离
 * @param cnt 采样次数
 * @return 滤波后距离(单位 cm)
 */
uint16_t hc_sr04_get_dist_filter(uint8_t cnt);

#endif //HC_SR04_H