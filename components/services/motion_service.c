#include "am_motion_service.h"

#include "sdkconfig.h"

#include "esp_log.h"

#include "am_sensor_hub.h"

static const char *TAG = "am_motion_srv";

esp_err_t am_motion_service_init(void)
{
#if CONFIG_AURAMATE_FEATURE_MOTION
    if (!am_sensor_hub_is_configured()) {
        ESP_LOGW(TAG, "动作服务已启用，但传感器 Hub 尚未完整配置");
        return ESP_OK;
    }

    ESP_LOGI(TAG, "动作服务已初始化，预留姿态解算与 DTW 特征提取");
#else
    ESP_LOGI(TAG, "动作服务已关闭");
#endif

    return ESP_OK;
}

esp_err_t am_motion_service_start(void)
{
#if CONFIG_AURAMATE_FEATURE_MOTION
    if (!am_sensor_hub_is_configured()) {
        ESP_LOGW(TAG, "动作服务跳过启动，等待 IMU/地磁链路确认");
        return ESP_OK;
    }

    ESP_LOGI(TAG, "动作服务启动，占位等待采样任务与动作评分任务接入");
#if CONFIG_AURAMATE_FEATURE_BLE_EXT_NODES
    ESP_LOGI(TAG, "BLE 扩展动作节点功能已预留");
#endif
#else
    ESP_LOGI(TAG, "动作服务未启用，跳过启动");
#endif

    return ESP_OK;
}
