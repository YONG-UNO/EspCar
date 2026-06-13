idf_component_register(
        SRCS "hc_sr04.c"
        INCLUDE_DIRS "."
        # 私有依赖:仅对.c文件内部使用
        PRIV_REQUIRES esp_driver_gpio esp_driver_ledc esp_timer
)