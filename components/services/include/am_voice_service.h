#ifndef AM_VOICE_SERVICE_H
#define AM_VOICE_SERVICE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化语音服务。 */
esp_err_t am_voice_service_init(void);

/* 启动语音服务。 */
esp_err_t am_voice_service_start(void);

#ifdef __cplusplus
}
#endif

#endif /* AM_VOICE_SERVICE_H */
