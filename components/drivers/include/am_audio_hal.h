#ifndef AM_AUDIO_HAL_H
#define AM_AUDIO_HAL_H

#include <stdbool.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化音频 HAL 占位层。 */
esp_err_t am_audio_hal_init(void);

/* 判断音频接口是否已经具备最小配置条件。 */
bool am_audio_hal_is_configured(void);

/* 预留语音播报接口，当前阶段仅做日志占位。 */
esp_err_t am_audio_hal_play_prompt(const char *prompt_key);

#ifdef __cplusplus
}
#endif

#endif /* AM_AUDIO_HAL_H */
