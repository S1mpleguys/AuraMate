#ifndef AM_SENSOR_HUB_H
#define AM_SENSOR_HUB_H

#include <stdbool.h>
#include <stdint.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 环境传感器样本，当前阶段用于定义接口边界。 */
typedef struct {
    float temperature_c;
    float humidity_percent;
    float pressure_hpa;
    uint32_t gas_resistance_ohm;
} am_env_sample_t;

/* 姿态/动作样本，后续可扩展为四元数或特征向量。 */
typedef struct {
    float accel_mps2[3];
    float gyro_dps[3];
    float mag_ut[3];
} am_motion_sample_t;

/* 初始化传感器 Hub 占位层。 */
esp_err_t am_sensor_hub_init(void);

/* 判断 I2C 传感器链路是否已经具备最小配置条件。 */
bool am_sensor_hub_is_configured(void);

/* 读取环境样本，当前阶段返回未实现。 */
esp_err_t am_sensor_hub_read_env(am_env_sample_t *sample);

/* 读取动作样本，当前阶段返回未实现。 */
esp_err_t am_sensor_hub_read_motion(am_motion_sample_t *sample);

#ifdef __cplusplus
}
#endif

#endif /* AM_SENSOR_HUB_H */
