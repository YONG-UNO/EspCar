idf_component_register(
        SRCS "track_fsm.c"
        INCLUDE_DIRS "."
        REQUIRES gray_sensor motor_l298p
        PRIV_REQUIRES esp_driver_gpio esp_driver_ledc
)