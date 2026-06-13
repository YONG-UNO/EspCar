/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

#include "gray_sensor.h"
#include "motor_l298p.h"
#include "track_fsm.h"
#include "hc_sr04.h"
#include "ws2812b.h"

void app_main(void)
{
    printf("五路灰度循迹传感器测试\n");

    gray_sensor_init();
    motor_l298p_init();
    hc_sr04_init(21, 3);
    ws2812b_init();

    track_state_t cur_state;

    for(;;)
    {
        // ws2812b_set_color(0, 0, 0);
        // ws2812b_refresh();

        cur_state = track_fsm_get_state();  // 获取当前循迹状态
        track_fsm_run(cur_state);           // 执行对应电机动作

        vTaskDelay(20 / portTICK_PERIOD_MS); // 控制循环帧率，可微调
    }
}
