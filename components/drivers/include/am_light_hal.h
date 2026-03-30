#ifndef AM_LIGHT_HAL_H
#define AM_LIGHT_HAL_H

#include <stdbool.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AM_LIGHT_MODE_OFF = 0,
    AM_LIGHT_MODE_SOLID,
    AM_LIGHT_MODE_BREATHING,
} am_light_mode_t;

/* 初始化灯效 HAL 占位层。 */
esp_err_t am_light_hal_init(void);

/* 判断灯效输出是否已经具备最小配置条件。 */
bool am_light_hal_is_configured(void);

/* 设置当前灯效模式。 */
esp_err_t am_light_hal_set_mode(am_light_mode_t mode);

#ifdef __cplusplus
}
#endif

#endif /* AM_LIGHT_HAL_H */
