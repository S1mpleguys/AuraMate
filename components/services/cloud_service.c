#include "am_cloud_service.h"

#include "sdkconfig.h"

#include "esp_log.h"

static const char *TAG = "am_cloud_srv";

esp_err_t am_cloud_service_init(void)
{
#if CONFIG_AURAMATE_FEATURE_CLOUD
    ESP_LOGI(TAG, "云端服务已初始化，预留 HTTP/MQTT 与模型接口");
#else
    ESP_LOGI(TAG, "云端服务已关闭");
#endif

    return ESP_OK;
}

esp_err_t am_cloud_service_start(void)
{
#if CONFIG_AURAMATE_FEATURE_CLOUD
    ESP_LOGI(TAG, "云端服务启动，占位等待接入鉴权、上报与流式返回");
#else
    ESP_LOGI(TAG, "云端服务未启用，跳过启动");
#endif

    return ESP_OK;
}
