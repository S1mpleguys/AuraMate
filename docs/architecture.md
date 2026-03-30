# 软件架构说明

## 结论

当前工程采用适合比赛早期推进的四层结构：

1. `main/` 只负责启动顺序和系统状态切换。
2. `components/board/` 统一承接板级资源、引脚和总线配置。
3. `components/drivers/` 负责传感器、音频、显示、RGB 等外设封装。
4. `components/services/` 负责环境、动作、语音、云端和 UI 业务服务。

这样做的原因是先把“接口边界”和“协作边界”固定，后面无论换屏驱、换音频链路、换云端协议，都不需要把业务代码和板级代码搅在一起。

## 分层职责

### 1. 入口层 `main/`

- `main.c`：保留 `app_main()` 最小入口。
- `app_entry.c`：统一处理 NVS、板级初始化、外设骨架初始化、服务初始化和服务启动。

### 2. 板级层 `components/board/`

- 维护 `menuconfig` 可配置项。
- 管理 I2C、I2S、LCD、RGB 的板级引脚和总线参数。
- 只做“资源描述”和“初始化顺序控制”，不直接承载具体设备协议。

### 3. 驱动层 `components/drivers/`

- `sensor_hub.c`：承接 BMI270/BMM350/BME690。
- `audio_hal.c`：承接 I2S 麦克风与扬声器。
- `display_hal.c`：承接 LCD 屏和启动页渲染。
- `light_hal.c`：承接 RGB 呼吸灯。
- `device_registry.c`：汇总外设是否具备最小配置条件。

### 4. 服务层 `components/services/`

- `env_service.c`：环境感知、VOC 预警、温湿压解释。
- `motion_service.c`：姿态采样、动作分段、DTW/评分入口。
- `voice_service.c`：唤醒词、录音、播报链路。
- `cloud_service.c`：HTTP/MQTT、鉴权、数据上报、云端推理结果回收。
- `ui_service.c`：LCD 页面和灯效协调。
- `service_manager.c`：统一维护系统状态机。

## 当前状态机

当前实现先保留轻量状态机，避免在硬件参数未确认前过早拆成多个常驻任务：

```text
BOOT -> PRECHECK -> IDLE
                 \-> FAULT
```

后续建议扩展为：

```text
BOOT -> PRECHECK -> IDLE -> TRAINING -> CLOUD_SYNC -> IDLE
                 \-------------------------------> FAULT
```

## 推荐的后续任务拆分

当板级资源确认后，再把服务层逐步拆成以下 FreeRTOS 任务：

- `sensor_task`：固定周期读取 IMU / BME690，并做一阶滤波。
- `audio_task`：I2S 录音、播放、环形缓冲管理。
- `cloud_task`：Wi-Fi 保活、HTTP/MQTT 收发、重试与超时控制。
- `ui_task`：屏幕刷新、状态页切换、灯效同步。
- `app_task`：模式切换、训练流程编排、异常恢复。

## 设计取舍

- 先不引入复杂事件总线和大中间层，原因是当前 Flash 仅 `2MB`。
- 先不把所有服务拆成独立任务，原因是硬件时序、栈深和优先级尚未实测。
- 先使用占位驱动接口，原因是比赛初期最重要的是确定目录边界和集成节奏，而不是过早把硬件细节写死。
