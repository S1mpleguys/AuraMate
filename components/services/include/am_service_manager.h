#ifndef AM_SERVICE_MANAGER_H
#define AM_SERVICE_MANAGER_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AM_SERVICE_STATE_BOOT = 0,
    AM_SERVICE_STATE_PRECHECK,
    AM_SERVICE_STATE_IDLE,
    AM_SERVICE_STATE_TRAINING,
    AM_SERVICE_STATE_CLOUD_SYNC,
    AM_SERVICE_STATE_FAULT,
} am_service_state_t;

/* 按既定顺序初始化所有业务服务。 */
esp_err_t am_service_manager_init(void);

/* 启动所有业务服务。 */
esp_err_t am_service_manager_start(void);

/* 查询当前系统状态。 */
am_service_state_t am_service_manager_get_state(void);

/* 把状态枚举转换为日志可读字符串。 */
const char *am_service_manager_state_to_string(am_service_state_t state);

#ifdef __cplusplus
}
#endif

#endif /* AM_SERVICE_MANAGER_H */
