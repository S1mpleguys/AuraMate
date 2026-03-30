#include "am_sensor_hub.h"

#include <string.h>

#include "sdkconfig.h"

#include "esp_log.h"

#include "am_board.h"

static const char *TAG = "am_sensor_hub";
static bool s_sensor_hub_configured;

esp_err_t am_sensor_hub_init(void)
{
#if CONFIG_AURAMATE_FEATURE_ENV || CONFIG_AURAMATE_FEATURE_MOTION
    if (!am_board_i2c_is_configured()) {
        s_sensor_hub_configured = false;
        ESP_LOGW(TAG, "传感器功能已启用，但 I2C 引脚未确认");
        return ESP_OK;
    }

    s_sensor_hub_configured = true;
    ESP_LOGI(TAG,
             "传感器 Hub 已占位，后续在此接入 BMI270/BMM350/BME690 驱动");
#else
    s_sensor_hub_configured = false;
    ESP_LOGI(TAG, "环境与动作传感功能均已关闭");
#endif

    return ESP_OK;
}

bool am_sensor_hub_is_configured(void)
{
    return s_sensor_hub_configured;
}

esp_err_t am_sensor_hub_read_env(am_env_sample_t *sample)
{
    if (sample == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!s_sensor_hub_configured) {
        return ESP_ERR_INVALID_STATE;
    }

    memset(sample, 0, sizeof(*sample));
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t am_sensor_hub_read_motion(am_motion_sample_t *sample)
{
    if (sample == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!s_sensor_hub_configured) {
        return ESP_ERR_INVALID_STATE;
    }

    memset(sample, 0, sizeof(*sample));
    return ESP_ERR_NOT_SUPPORTED;
}
