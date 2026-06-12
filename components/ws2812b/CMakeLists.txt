idf_component_register(
        SRCS "ws2812b.c"
        INCLUDE_DIRS "."
        PRIV_REQUIRES esp_driver_gpio esp_driver_ledc
)