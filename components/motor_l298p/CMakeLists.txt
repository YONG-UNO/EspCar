idf_component_register(
        SRCS "motor_l298p.c"
        INCLUDE_DIRS "."
        PRIV_REQUIRES esp_driver_gpio esp_driver_ledc
)