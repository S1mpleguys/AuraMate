#include "am_light_hal.h"

#include "sdkconfig.h"

#include "esp_log.h"

#include "am_board.h"

static const char *TAG = "am_light_hal";
static bool s_light_configured;

static const char *am_light_mode_to_string(am_light_mode_t mode)
{
    switch (mode) {
    case AM_LIGHT_MODE_OFF:
        return "关闭";
    case AM_LIGHT_MODE_SOLID:
        return "常亮";
    case AM_LIGHT_MODE_BREATHING:
        return "呼吸";
    default:
        return "未知";
    }
}

esp_err_t am_light_hal_init(void)
{
#if CONFIG_AURAMATE_FEATURE_DISPLAY
    if (!am_board_rgb_is_configured()) {
        s_light_configured = false;
        ESP_LOGW(TAG, "RGB 灯功能已启用，但数据脚未确认");
        return ESP_OK;
    }

    s_light_configured = true;
    ESP_LOGI(TAG, "RGB 灯链路已占位，后续在此接入呼吸灯/PWM 实现");
#else
    s_light_configured = false;
    ESP_LOGI(TAG, "灯效功能随显示功能一起关闭");
#endif

    return ESP_OK;
}

bool am_light_hal_is_configured(void)
{
    return s_light_configured;
}

esp_err_t am_light_hal_set_mode(am_light_mode_t mode)
{
    if (!s_light_configured) {
        ESP_LOGI(TAG, "RGB 未配置，改为串口提示灯效模式: %s",
                 am_light_mode_to_string(mode));
        return ESP_OK;
    }

    ESP_LOGI(TAG, "设置灯效模式: %s", am_light_mode_to_string(mode));
    return ESP_OK;
}
