#ifndef AM_BOARD_H
#define AM_BOARD_H

#include <stdbool.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 板级固定资源配置，由 menuconfig 统一生成。 */
typedef struct {
    int i2c_port;
    int i2c_sda_gpio;
    int i2c_scl_gpio;
    int i2c_freq_hz;
    int i2s_port;
    int i2s_mclk_gpio;
    int i2s_bclk_gpio;
    int i2s_ws_gpio;
    int i2s_dout_gpio;
    int i2s_din_gpio;
    int lcd_host_id;
    int lcd_sclk_gpio;
    int lcd_mosi_gpio;
    int lcd_cs_gpio;
    int lcd_dc_gpio;
    int lcd_rst_gpio;
    int lcd_bl_gpio;
    int rgb_gpio;
} am_board_config_t;

/* 初始化板级资源描述，不直接做具体驱动绑定。 */
esp_err_t am_board_init(void);

/* 获取当前板级配置快照。 */
const am_board_config_t *am_board_get_config(void);

/* 判断 I2C 总线占位是否已完整配置。 */
bool am_board_i2c_is_configured(void);

/* 判断 I2S 音频接口是否已完整配置。 */
bool am_board_i2s_is_configured(void);

/* 判断 LCD 所需 SPI/控制脚是否已完整配置。 */
bool am_board_lcd_is_configured(void);

/* 判断 RGB 灯是否已配置。 */
bool am_board_rgb_is_configured(void);

#ifdef __cplusplus
}
#endif

#endif /* AM_BOARD_H */
