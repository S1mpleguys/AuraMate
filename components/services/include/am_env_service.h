#ifndef AM_ENV_SERVICE_H
#define AM_ENV_SERVICE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化环境服务。 */
esp_err_t am_env_service_init(void);

/* 启动环境服务。 */
esp_err_t am_env_service_start(void);

#ifdef __cplusplus
}
#endif

#endif /* AM_ENV_SERVICE_H */
