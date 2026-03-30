#include "am_device_registry.h"

#include "esp_log.h"

#include "am_audio_hal.h"
#include "am_display_hal.h"
#include "am_light_hal.h"
#include "am_sensor_hub.h"

static const char *TAG = "am_dev_reg";
static am_device_registry_t s_registry;

static esp_err_t am_device_registry_call(const char *name, esp_err_t ret)
{
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "%s 初始化失败: %s", name, esp_err_to_name(ret));
        return ret;
    }

    return ESP_OK;
}

esp_err_t am_device_registry_init(void)
{
    esp_err_t ret;

    ret = am_audio_hal_init();
    if (am_device_registry_call("音频 HAL", ret) != ESP_OK) {
        return ret;
    }

    ret = am_display_hal_init();
    if (am_device_registry_call("显示 HAL", ret) != ESP_OK) {
        return ret;
    }

    ret = am_light_hal_init();
    if (am_device_registry_call("灯效 HAL", ret) != ESP_OK) {
        return ret;
    }

    ret = am_sensor_hub_init();
    if (am_device_registry_call("传感器 Hub", ret) != ESP_OK) {
        return ret;
    }

    s_registry.audio_configured = am_audio_hal_is_configured();
    s_registry.display_configured = am_display_hal_is_configured();
    s_registry.light_configured = am_light_hal_is_configured();
    s_registry.sensor_hub_configured = am_sensor_hub_is_configured();

    ESP_LOGI(TAG,
             "外设骨架就绪情况: sensor=%s audio=%s display=%s light=%s",
             s_registry.sensor_hub_configured ? "是" : "否",
             s_registry.audio_configured ? "是" : "否",
             s_registry.display_configured ? "是" : "否",
             s_registry.light_configured ? "是" : "否");

    return ESP_OK;
}

const am_device_registry_t *am_device_registry_get(void)
{
    return &s_registry;
}
