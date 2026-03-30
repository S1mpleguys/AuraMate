#include "am_voice_service.h"

#include "sdkconfig.h"

#include "esp_log.h"

#include "am_audio_hal.h"

static const char *TAG = "am_voice_srv";

esp_err_t am_voice_service_init(void)
{
#if CONFIG_AURAMATE_FEATURE_AUDIO
    if (!am_audio_hal_is_configured()) {
        ESP_LOGW(TAG, "语音服务已启用，但音频链路尚未完整配置");
        return ESP_OK;
    }

    ESP_LOGI(TAG, "语音服务已初始化，预留唤醒词、录音缓存与播报接口");
#else
    ESP_LOGI(TAG, "语音服务已关闭");
#endif

    return ESP_OK;
}

esp_err_t am_voice_service_start(void)
{
#if CONFIG_AURAMATE_FEATURE_AUDIO
    if (!am_audio_hal_is_configured()) {
        ESP_LOGW(TAG, "语音服务跳过启动，等待 I2S 与 codec 参数确认");
        return ESP_OK;
    }

    ESP_LOGI(TAG, "语音服务启动，占位等待流式 ASR/LLM/TTS 接入");
    return am_audio_hal_play_prompt("boot_ready");
#else
    ESP_LOGI(TAG, "语音服务未启用，跳过启动");
    return ESP_OK;
#endif
}
