#include "app_entry.h"
#include "esp_err.h"
#include "esp_log.h"

static const char *TAG = "main";

void app_main(void)
{
    esp_err_t ret = aura_app_start();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "系统启动失败: %s", esp_err_to_name(ret));
    }
}
