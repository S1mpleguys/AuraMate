#include "am_env_service.h"

#include "sdkconfig.h"

#include "esp_log.h"

#include "am_sensor_hub.h"

static const char *TAG = "am_env_srv";

esp_err_t am_env_service_init(void)
{
#if CONFIG_AURAMATE_FEATURE_ENV
    if (!am_sensor_hub_is_configured()) {
        ESP_LOGW(TAG, "环境服务已启用，但传感器 Hub 尚未完整配置");
        return ESP_OK;
    }

    ESP_LOGI(TAG, "环境服务已初始化，预留 VOC/温湿压采样与阈值告警");
#else
    ESP_LOGI(TAG, "环境服务已关闭");
#endif

    return ESP_OK;
}

esp_err_t am_env_service_start(void)
{
#if CONFIG_AURAMATE_FEATURE_ENV
    if (!am_sensor_hub_is_configured()) {
        ESP_LOGW(TAG, "环境服务跳过启动，等待 I2C 与 BME690 参数确认");
        return ESP_OK;
    }

    ESP_LOGI(TAG, "环境服务启动，占位等待周期采样任务接入");
#else
    ESP_LOGI(TAG, "环境服务未启用，跳过启动");
#endif

    return ESP_OK;
}
