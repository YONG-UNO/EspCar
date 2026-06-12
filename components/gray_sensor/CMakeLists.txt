idf_component_register(
        SRCS "gray_sensor.c"
        INCLUDE_DIRS "."
        PRIV_REQUIRES esp_driver_gpio
)