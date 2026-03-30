#include "am_ui_service.h"

#include "sdkconfig.h"

#include "esp_log.h"

#include "am_display_hal.h"
#include "am_light_hal.h"

static const char *TAG = "am_ui_srv";

esp_err_t am_ui_service_init(void)
{
#if CONFIG_AURAMATE_FEATURE_DISPLAY
    if (!am_display_hal_is_configured()) {
        ESP_LOGW(TAG, "UI 服务已启用，但 LCD 尚未完整配置");
    }

    if (!am_light_hal_is_configured()) {
        ESP_LOGW(TAG, "UI 服务已启用，但 RGB 灯尚未完整配置");
    }

    ESP_LOGI(TAG, "UI 服务已初始化，预留状态页、分数页和呼吸灯逻辑");
#else
    ESP_LOGI(TAG, "UI 服务已关闭");
#endif

    return ESP_OK;
}

esp_err_t am_ui_service_start(void)
{
#if CONFIG_AURAMATE_FEATURE_DISPLAY
    esp_err_t ret = am_display_hal_show_boot_status("系统待机", 100);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "更新启动页失败: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = am_light_hal_set_mode(AM_LIGHT_MODE_BREATHING);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "设置呼吸灯失败: %s", esp_err_to_name(ret));
        return ret;
    }

    ESP_LOGI(TAG, "UI 服务启动完成");
#else
    ESP_LOGI(TAG, "UI 服务未启用，跳过启动");
#endif

    return ESP_OK;
}
