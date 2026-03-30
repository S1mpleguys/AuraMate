#ifndef AM_CLOUD_SERVICE_H
#define AM_CLOUD_SERVICE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化云端链路服务。 */
esp_err_t am_cloud_service_init(void);

/* 启动云端链路服务。 */
esp_err_t am_cloud_service_start(void);

#ifdef __cplusplus
}
#endif

#endif /* AM_CLOUD_SERVICE_H */
