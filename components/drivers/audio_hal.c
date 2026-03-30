#include "am_audio_hal.h"

#include "sdkconfig.h"

#include "esp_log.h"

#include "am_board.h"

static const char *TAG = "am_audio_hal";
static bool s_audio_configured;

esp_err_t am_audio_hal_init(void)
{
#if CONFIG_AURAMATE_FEATURE_AUDIO
    if (!am_board_i2s_is_configured()) {
        s_audio_configured = false;
        ESP_LOGW(TAG, "音频功能已启用，但 I2S 引脚未确认");
        return ESP_OK;
    }

    s_audio_configured = true;
    ESP_LOGI(TAG, "I2S 音频链路已占位，后续在此接入麦克风与扬声器驱动");
#else
    s_audio_configured = false;
    ESP_LOGI(TAG, "音频功能已关闭");
#endif

    return ESP_OK;
}

bool am_audio_hal_is_configured(void)
{
    return s_audio_configured;
}

esp_err_t am_audio_hal_play_prompt(const char *prompt_key)
{
    if (prompt_key == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!s_audio_configured) {
        ESP_LOGW(TAG, "音频未配置，跳过提示音键值: %s", prompt_key);
        return ESP_OK;
    }

    ESP_LOGI(TAG, "音频播放占位: %s", prompt_key);
    return ESP_OK;
}
