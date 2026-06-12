//
// Created by DingYong on 2026/6/12.
//
#include "track_fsm.h"
#include "gray_sensor.h"
#include "motor_l298p.h"
#include <stdio.h>

track_state_t track_fsm_get_state(void)
{
    int s1 = gray_sensor_read(0);
    int s2 = gray_sensor_read(1);
    int s3 = gray_sensor_read(2);
    int s4 = gray_sensor_read(3);
    int s5 = gray_sensor_read(4);

    printf("S1:%d S2:%d S3:%d S4:%d S5:%d | ", s1, s2, s3, s4, s5);

    // 规则：黑线=1，白纸=0
    if (s3 == 1)
    {
        return TRACK_GO_STRAIGHT;
    }
    else if (s2 == 1 && s1 == 0)
    {
        return TRACK_LEFT_SMALL;
    }
    else if (s4 == 1 && s5 == 0)
    {
        return TRACK_RIGHT_SMALL;
    }
    else if (s1 == 1)
    {
        return TRACK_LEFT_BIG;
    }
    else if (s5 == 1)
    {
        return TRACK_RIGHT_BIG;
    }
    else
    {
        return TRACK_STOP;
    }
}

void track_fsm_run(track_state_t state)
{
    switch (state)
    {
        case TRACK_GO_STRAIGHT:
            printf("直行\n");
            motor_left_control(MOTOR_FORWARD);
            motor_right_control(MOTOR_FORWARD);
            break;

        case TRACK_LEFT_SMALL:
            printf("右修正\n");
            motor_left_control(MOTOR_FORWARD);
            motor_right_control(MOTOR_STOP);
            break;

        case TRACK_RIGHT_SMALL:
            printf("左修正\n");
            motor_left_control(MOTOR_STOP);
            motor_right_control(MOTOR_FORWARD);
            break;

        case TRACK_LEFT_BIG:
            printf("急左转\n");
            motor_left_control(MOTOR_BACKWARD);
            motor_right_control(MOTOR_FORWARD);
            break;

        case TRACK_RIGHT_BIG:
            printf("急右转\n");
            motor_left_control(MOTOR_FORWARD);
            motor_right_control(MOTOR_BACKWARD);
            break;

        case TRACK_STOP:
        default:
            printf("停止\n");
            motor_left_control(MOTOR_STOP);
            motor_right_control(MOTOR_STOP);
            break;
    }
}
