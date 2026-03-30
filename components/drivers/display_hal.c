#include "am_display_hal.h"

#include "sdkconfig.h"

#include "esp_log.h"

#include "am_board.h"

static const char *TAG = "am_display_hal";
static bool s_display_configured;

esp_err_t am_display_hal_init(void)
{
#if CONFIG_AURAMATE_FEATURE_DISPLAY
    if (!am_board_lcd_is_configured()) {
        s_display_configured = false;
        ESP_LOGW(TAG, "显示功能已启用，但 LCD 引脚未确认");
        return ESP_OK;
    }

    s_display_configured = true;
    ESP_LOGI(TAG, "LCD 链路已占位，后续在此接入屏驱与 UI 渲染");
#else
    s_display_configured = false;
    ESP_LOGI(TAG, "显示功能已关闭");
#endif

    return ESP_OK;
}

bool am_display_hal_is_configured(void)
{
    return s_display_configured;
}

esp_err_t am_display_hal_show_boot_status(const char *phase, int progress_pct)
{
    if (phase == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (progress_pct < 0) {
        progress_pct = 0;
    } else if (progress_pct > 100) {
        progress_pct = 100;
    }

    if (!s_display_configured) {
        ESP_LOGI(TAG, "LCD 未配置，改为串口显示启动状态: [%d%%] %s",
                 progress_pct, phase);
        return ESP_OK;
    }

    ESP_LOGI(TAG, "LCD 启动页更新: [%d%%] %s", progress_pct, phase);
    return ESP_OK;
}
