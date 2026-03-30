#ifndef AM_DISPLAY_HAL_H
#define AM_DISPLAY_HAL_H

#include <stdbool.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化显示 HAL 占位层。 */
esp_err_t am_display_hal_init(void);

/* 判断显示接口是否已经具备最小配置条件。 */
bool am_display_hal_is_configured(void);

/* 统一展示系统启动阶段，后续可替换为真实 LCD 绘制逻辑。 */
esp_err_t am_display_hal_show_boot_status(const char *phase, int progress_pct);

#ifdef __cplusplus
}
#endif

#endif /* AM_DISPLAY_HAL_H */
