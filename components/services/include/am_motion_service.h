#ifndef AM_MOTION_SERVICE_H
#define AM_MOTION_SERVICE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化动作服务。 */
esp_err_t am_motion_service_init(void);

/* 启动动作服务。 */
esp_err_t am_motion_service_start(void);

#ifdef __cplusplus
}
#endif

#endif /* AM_MOTION_SERVICE_H */
