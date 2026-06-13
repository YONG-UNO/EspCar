//
// Created by DingYong on 2026/6/12.
//
#ifndef TRACK_FSM_H
#define TRACK_FSM_H

// 循迹状态枚举
typedef enum
{
    TRACK_STOP,        // 离线停止
    TRACK_GO_STRAIGHT,// 直行
    TRACK_LEFT_SMALL,  // 小幅左偏 → 右修正
    TRACK_RIGHT_SMALL,// 小幅右偏 → 左修正
    TRACK_LEFT_BIG,    // 大幅左偏 → 急左转
    TRACK_RIGHT_BIG,    // 大幅右偏 → 急右转
    TRACK_LEFT_CORNER,   // 左直角转弯
    TRACK_RIGHT_CORNER   // 右直角转弯
} track_state_t;

/**
 * @brief  获取当前循迹状态（读取五路灰度 + 逻辑判断）
 * @return 当前状态机状态
 */
track_state_t track_fsm_get_state(void);

/**
 * @brief  根据状态执行电机动作
 * @param state 状态机状态
 */
void track_fsm_run(track_state_t state);

#endif //TRACK_FSM_H