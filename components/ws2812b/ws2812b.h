//
// Created by DingYong on 2026/6/11.
//
#ifndef WS2812B_H
#define WS2812B_H

#include <stdint.h>

#define WS2812_PIN      GPIO_NUM_48
// 单颗灯珠
#define LED_NUM         1

// 初始化WS2812 GPIO
void ws2812b_init(void);

// 设置颜色 (r,g,b)
void ws2812b_set_color(uint8_t r, uint8_t g, uint8_t b);

// 刷新点亮灯珠
void ws2812b_refresh(void);

#endif //WS2812B_H