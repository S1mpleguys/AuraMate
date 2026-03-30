#ifndef APP_ENTRY_H
#define APP_ENTRY_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 启动 AuraMate 应用编排层。 */
esp_err_t aura_app_start(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_ENTRY_H */
