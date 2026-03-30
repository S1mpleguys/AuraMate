#ifndef AM_UI_SERVICE_H
#define AM_UI_SERVICE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化 UI 服务。 */
esp_err_t am_ui_service_init(void);

/* 启动 UI 服务。 */
esp_err_t am_ui_service_start(void);

#ifdef __cplusplus
}
#endif

#endif /* AM_UI_SERVICE_H */
