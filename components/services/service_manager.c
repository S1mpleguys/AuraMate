#include "am_service_manager.h"

#include "esp_log.h"

#include "am_cloud_service.h"
#include "am_env_service.h"
#include "am_motion_service.h"
#include "am_ui_service.h"
#include "am_voice_service.h"

static const char *TAG = "am_srv_mgr";
static am_service_state_t s_state = AM_SERVICE_STATE_BOOT;

static void am_service_manager_set_state(am_service_state_t state)
{
    s_state = state;
    ESP_LOGI(TAG, "系统状态切换为: %s",
             am_service_manager_state_to_string(state));
}

const char *am_service_manager_state_to_string(am_service_state_t state)
{
    switch (state) {
    case AM_SERVICE_STATE_BOOT:
        return "启动中";
    case AM_SERVICE_STATE_PRECHECK:
        return "自检中";
    case AM_SERVICE_STATE_IDLE:
        return "待机";
    case AM_SERVICE_STATE_TRAINING:
        return "训练中";
    case AM_SERVICE_STATE_CLOUD_SYNC:
        return "云端同步";
    case AM_SERVICE_STATE_FAULT:
        return "故障";
    default:
        return "未知";
    }
}

am_service_state_t am_service_manager_get_state(void)
{
    return s_state;
}

static esp_err_t am_service_manager_step(const char *name, esp_err_t ret)
{
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "%s 执行失败: %s", name, esp_err_to_name(ret));
        am_service_manager_set_state(AM_SERVICE_STATE_FAULT);
        return ret;
    }

    return ESP_OK;
}

esp_err_t am_service_manager_init(void)
{
    esp_err_t ret;

    am_service_manager_set_state(AM_SERVICE_STATE_BOOT);

    ret = am_ui_service_init();
    if (am_service_manager_step("UI 服务初始化", ret) != ESP_OK) {
        return ret;
    }

    ret = am_env_service_init();
    if (am_service_manager_step("环境服务初始化", ret) != ESP_OK) {
        return ret;
    }

    ret = am_motion_service_init();
    if (am_service_manager_step("动作服务初始化", ret) != ESP_OK) {
        return ret;
    }

    ret = am_voice_service_init();
    if (am_service_manager_step("语音服务初始化", ret) != ESP_OK) {
        return ret;
    }

    ret = am_cloud_service_init();
    if (am_service_manager_step("云端服务初始化", ret) != ESP_OK) {
        return ret;
    }

    return ESP_OK;
}

esp_err_t am_service_manager_start(void)
{
    esp_err_t ret;

    am_service_manager_set_state(AM_SERVICE_STATE_PRECHECK);

    ret = am_ui_service_start();
    if (am_service_manager_step("UI 服务启动", ret) != ESP_OK) {
        return ret;
    }

    ret = am_cloud_service_start();
    if (am_service_manager_step("云端服务启动", ret) != ESP_OK) {
        return ret;
    }

    ret = am_env_service_start();
    if (am_service_manager_step("环境服务启动", ret) != ESP_OK) {
        return ret;
    }

    ret = am_motion_service_start();
    if (am_service_manager_step("动作服务启动", ret) != ESP_OK) {
        return ret;
    }

    ret = am_voice_service_start();
    if (am_service_manager_step("语音服务启动", ret) != ESP_OK) {
        return ret;
    }

    am_service_manager_set_state(AM_SERVICE_STATE_IDLE);
    return ESP_OK;
}
