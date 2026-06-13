idf_component_register(SRCS "main.c"
                       PRIV_REQUIRES spi_flash esp_driver_gpio gray_sensor motor_l298p ws2812b track_fsm hc_sr04
                       INCLUDE_DIRS "")
