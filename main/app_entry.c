#include "app_entry.h"

#include "esp_idf_version.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "am_board.h"
#include "am_device_registry.h"
#include "am_service_manager.h"

static const char *TAG = "app_entry";

static esp_err_t aura_init_nvs(void)
{
    esp_err_t ret = nvs_flash_init();
    if ((ret == ESP_ERR_NVS_NO_FREE_PAGES) ||
        (ret == ESP_ERR_NVS_NEW_VERSION_FOUND)) {
        ESP_LOGW(TAG, "NVS 分区需要擦除后重新初始化");
        ret = nvs_flash_erase();
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "擦除 NVS 失败: %s", esp_err_to_name(ret));
            return ret;
        }

        ret = nvs_flash_init();
    }

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "初始化 NVS 失败: %s", esp_err_to_name(ret));
        return ret;
    }

    return ESP_OK;
}

esp_err_t aura_app_start(void)
{
    esp_err_t ret;

    ESP_LOGI(TAG, "AuraMate 启动，IDF 版本: %s，目标芯片: %s",
             esp_get_idf_version(), CONFIG_IDF_TARGET);

    ret = aura_init_nvs();
    if (ret != ESP_OK) {
        return ret;
    }

    ret = am_board_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "板级初始化失败: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = am_device_registry_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "外设骨架初始化失败: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = am_service_manager_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "服务初始化失败: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = am_service_manager_start();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "服务启动失败: %s", esp_err_to_name(ret));
        return ret;
    }

    ESP_LOGI(TAG, "系统进入 %s 状态，等待后续接入业务逻辑",
             am_service_manager_state_to_string(am_service_manager_get_state()));

    return ESP_OK;
}
