//
// Created by DingYong on 2026/6/11.
//
#include "ws2812b.h"

#include <esp_rom_sys.h>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"

// WS2812B 官方时序 + ESP32-S3@240MHz 精准NOP数量
#define NOP_T0H     60    // 250ns
#define NOP_T0L     240   // 1000ns
#define NOP_T1H     240   // 1000ns
#define NOP_T1L     60    // 250ns
#define RST_US      60    // 复位 60us (>50us 标准)

static uint8_t led_r = 0;
static uint8_t led_g = 0;
static uint8_t led_b = 0;

// 纯NOP延时，无函数开销
static inline void delay_nop(uint32_t cnt)
{
    for (uint32_t i = 0; i < cnt; i--)
    {
        __asm__ __volatile__("nop");
    }
}

// 发送单个Bit
static void ws2812_send_bit(uint8_t bit)
{
    if (bit)
    {
        // 1码: T1H=1000ns , T1L=250ns
        gpio_set_level(WS2812_PIN, 1);
        delay_nop(NOP_T1H);
        gpio_set_level(WS2812_PIN, 0);
        delay_nop(NOP_T1L);
    }
    else
    {
        // 0码: T0H=250ns , T0L=1000ns
        gpio_set_level(WS2812_PIN, 1);
        delay_nop(NOP_T0H);
        gpio_set_level(WS2812_PIN, 0);
        delay_nop(NOP_T0L);
    }
}

// 发送1字节，高位优先
static void ws2812_send_byte(uint8_t dat)
{
    for (int i = 7; i >= 0; i--)
    {
        ws2812_send_bit((dat >> i) & 0x01);
    }
}

// 复位信号
static void ws2812_send_reset(void)
{
    gpio_set_level(WS2812_PIN, 0);
    for (uint32_t i = 0; i < RST_US; i++)
    {
        esp_rom_delay_us(1);
    }
}

void ws2812b_init(void)
{
    gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << WS2812_PIN,
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE
    };
    gpio_config(&cfg);
    gpio_set_level(WS2812_PIN, 0);
}

void ws2812b_set_color(uint8_t r, uint8_t g, uint8_t b)
{
    led_r = r;
    led_g = g;
    led_b = b;
}

// GRB 顺序，高位先发（符合WS2812B手册）
void ws2812b_refresh(void)
{
    ws2812_send_byte(led_g);
    ws2812_send_byte(led_r);
    ws2812_send_byte(led_b);
    ws2812_send_reset();
}