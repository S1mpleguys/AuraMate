#include "am_board.h"

#include "sdkconfig.h"

#include "esp_log.h"

static const char *TAG = "am_board";

static am_board_config_t s_board_cfg = {
    .i2c_port = CONFIG_AURAMATE_I2C_PORT,
    .i2c_sda_gpio = CONFIG_AURAMATE_I2C_SDA_GPIO,
    .i2c_scl_gpio = CONFIG_AURAMATE_I2C_SCL_GPIO,
    .i2c_freq_hz = CONFIG_AURAMATE_I2C_FREQ_HZ,
    .i2s_port = CONFIG_AURAMATE_I2S_PORT,
    .i2s_mclk_gpio = CONFIG_AURAMATE_I2S_MCLK_GPIO,
    .i2s_bclk_gpio = CONFIG_AURAMATE_I2S_BCLK_GPIO,
    .i2s_ws_gpio = CONFIG_AURAMATE_I2S_WS_GPIO,
    .i2s_dout_gpio = CONFIG_AURAMATE_I2S_DOUT_GPIO,
    .i2s_din_gpio = CONFIG_AURAMATE_I2S_DIN_GPIO,
    .lcd_host_id = CONFIG_AURAMATE_LCD_HOST_ID,
    .lcd_sclk_gpio = CONFIG_AURAMATE_LCD_SCLK_GPIO,
    .lcd_mosi_gpio = CONFIG_AURAMATE_LCD_MOSI_GPIO,
    .lcd_cs_gpio = CONFIG_AURAMATE_LCD_CS_GPIO,
    .lcd_dc_gpio = CONFIG_AURAMATE_LCD_DC_GPIO,
    .lcd_rst_gpio = CONFIG_AURAMATE_LCD_RST_GPIO,
    .lcd_bl_gpio = CONFIG_AURAMATE_LCD_BL_GPIO,
    .rgb_gpio = CONFIG_AURAMATE_RGB_GPIO,
};

static bool am_gpio_is_valid(int gpio_num)
{
    return gpio_num >= 0;
}

bool am_board_i2c_is_configured(void)
{
    return am_gpio_is_valid(s_board_cfg.i2c_sda_gpio) &&
           am_gpio_is_valid(s_board_cfg.i2c_scl_gpio);
}

bool am_board_i2s_is_configured(void)
{
    return am_gpio_is_valid(s_board_cfg.i2s_bclk_gpio) &&
           am_gpio_is_valid(s_board_cfg.i2s_ws_gpio) &&
           am_gpio_is_valid(s_board_cfg.i2s_dout_gpio) &&
           am_gpio_is_valid(s_board_cfg.i2s_din_gpio);
}

bool am_board_lcd_is_configured(void)
{
    return am_gpio_is_valid(s_board_cfg.lcd_sclk_gpio) &&
           am_gpio_is_valid(s_board_cfg.lcd_mosi_gpio) &&
           am_gpio_is_valid(s_board_cfg.lcd_cs_gpio) &&
           am_gpio_is_valid(s_board_cfg.lcd_dc_gpio) &&
           am_gpio_is_valid(s_board_cfg.lcd_rst_gpio) &&
           am_gpio_is_valid(s_board_cfg.lcd_bl_gpio);
}

bool am_board_rgb_is_configured(void)
{
    return am_gpio_is_valid(s_board_cfg.rgb_gpio);
}

const am_board_config_t *am_board_get_config(void)
{
    return &s_board_cfg;
}

esp_err_t am_board_init(void)
{
    ESP_LOGI(TAG,
             "板级配置载入: I2C[%d] SDA=%d SCL=%d FREQ=%d, "
             "I2S[%d] MCLK=%d BCLK=%d WS=%d DOUT=%d DIN=%d",
             s_board_cfg.i2c_port, s_board_cfg.i2c_sda_gpio,
             s_board_cfg.i2c_scl_gpio, s_board_cfg.i2c_freq_hz,
             s_board_cfg.i2s_port, s_board_cfg.i2s_mclk_gpio,
             s_board_cfg.i2s_bclk_gpio, s_board_cfg.i2s_ws_gpio,
             s_board_cfg.i2s_dout_gpio, s_board_cfg.i2s_din_gpio);

    ESP_LOGI(TAG,
             "显示配置: SPI_HOST=%d SCLK=%d MOSI=%d CS=%d DC=%d RST=%d BL=%d, RGB=%d",
             s_board_cfg.lcd_host_id, s_board_cfg.lcd_sclk_gpio,
             s_board_cfg.lcd_mosi_gpio, s_board_cfg.lcd_cs_gpio,
             s_board_cfg.lcd_dc_gpio, s_board_cfg.lcd_rst_gpio,
             s_board_cfg.lcd_bl_gpio, s_board_cfg.rgb_gpio);

    if (!am_board_i2c_is_configured()) {
        ESP_LOGW(TAG, "I2C 引脚尚未确认，Bosch 传感器驱动先保持占位");
    }

    if (!am_board_i2s_is_configured()) {
        ESP_LOGW(TAG, "I2S 引脚尚未确认，音频链路先保持占位");
    }

    if (!am_board_lcd_is_configured()) {
        ESP_LOGW(TAG, "LCD 引脚尚未确认，显示驱动先保持占位");
    }

    if (!am_board_rgb_is_configured()) {
        ESP_LOGW(TAG, "RGB 数据脚尚未确认，呼吸灯逻辑先保持占位");
    }

    return ESP_OK;
}
