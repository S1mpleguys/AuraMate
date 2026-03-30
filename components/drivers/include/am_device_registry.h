#ifndef AM_DEVICE_REGISTRY_H
#define AM_DEVICE_REGISTRY_H

#include <stdbool.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 汇总所有外设骨架的配置完成度。 */
typedef struct {
    bool sensor_hub_configured;
    bool audio_configured;
    bool display_configured;
    bool light_configured;
} am_device_registry_t;

/* 初始化所有外设骨架并记录可用性。 */
esp_err_t am_device_registry_init(void);

/* 获取外设骨架可用性快照。 */
const am_device_registry_t *am_device_registry_get(void);

#ifdef __cplusplus
}
#endif

#endif /* AM_DEVICE_REGISTRY_H */
