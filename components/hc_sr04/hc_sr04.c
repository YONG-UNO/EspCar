//
// Created by DingYong on 2026/6/13.
//
#include "hc_sr04.h"
#include "stdint.h"
#include <esp_log.h>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "HC_SR04";
static gpio_num_t trig_io = GPIO_NUM_NC;
static gpio_num_t echo_io = GPIO_NUM_NC;

// 声速换算：20℃ 往返 0.017131 cm/us
#define SOUND_FACTOR    0.017131f
#define DIST_BLIND      2U     // 最小盲区 cm
#define DIST_MAX        450U   // 最大测距 cm
#define MEAS_INTERVAL   200U   // 两次测量最小间隔 ms

esp_err_t hc_sr04_init(gpio_num_t trig_pin, gpio_num_t echo_pin)
{
    if (trig_pin == GPIO_NUM_NC || echo_pin == GPIO_NUM_NC)
    {
        ESP_LOGE(TAG, "GPIO invalid");
        return ESP_ERR_INVALID_ARG;
    }

    trig_io = trig_pin;
    echo_io = echo_pin;

    // Trig 配置为输出
    gpio_config_t trig_cfg = {
        .pin_bit_mask = 1ULL << trig_io,
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE
    };
    gpio_config(&trig_cfg);
    gpio_set_level(trig_io, 0);

    // Echo 配置为输入
    gpio_config_t echo_cfg = {
        .pin_bit_mask = 1ULL << echo_io,
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE
    };
    gpio_config(&echo_cfg);

    ESP_LOGI(TAG, "HC-SR04 init ok");
    return ESP_OK;
}

uint16_t hc_sr04_read_dist(void)
{
    if (trig_io == GPIO_NUM_NC || echo_io == GPIO_NUM_NC)
    {
        return 0;
    }

    // 发送 10us 触发高电平
    gpio_set_level(trig_io, 1);
    esp_rom_delay_us(10);
    gpio_set_level(trig_io, 0);

    // 等待 Echo 拉高
    int64_t t_start = esp_timer_get_time();
    while (gpio_get_level(echo_io) == 0)
    {
        if (esp_timer_get_time() - t_start > 50000)
        {
            return 0;
        }
    }

    // 等待 Echo 拉低，计算脉宽
    int64_t pulse_start = esp_timer_get_time();
    while (gpio_get_level(echo_io) == 1)
    {
        if (esp_timer_get_time() - pulse_start > 50000)
        {
            return DIST_MAX;
        }
    }
    int64_t pulse_us = esp_timer_get_time() - pulse_start;

    // 计算距离
    float dist = (float)pulse_us * SOUND_FACTOR;
    uint16_t res = (uint16_t)dist;

    // 范围过滤
    if (res < DIST_BLIND || res > DIST_MAX)
    {
        return 0;
    }
    return res;
}

uint16_t hc_sr04_read_dist_filter(uint8_t sample_cnt)
{
    if (sample_cnt == 0)
    {
        return 0;
    }

    uint32_t sum = 0;
    for (uint8_t i = 0; i < sample_cnt; i++)
    {
        uint16_t d = hc_sr04_read_dist();
        if (d != 0)
        {
            sum += d;
        }
        vTaskDelay(pdMS_TO_TICKS(MEAS_INTERVAL));
    }
    return (uint16_t)(sum / sample_cnt);
}