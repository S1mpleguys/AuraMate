# 项目结构规划

## 目录树

```text
AuraMate/
├── CMakeLists.txt
├── sdkconfig.defaults
├── partitions.csv
├── main/
│   ├── CMakeLists.txt
│   ├── main.c
│   ├── app_entry.c
│   └── app_entry.h
├── components/
│   ├── board/
│   │   ├── CMakeLists.txt
│   │   ├── Kconfig
│   │   ├── board.c
│   │   └── include/am_board.h
│   ├── drivers/
│   │   ├── CMakeLists.txt
│   │   ├── sensor_hub.c
│   │   ├── audio_hal.c
│   │   ├── display_hal.c
│   │   ├── light_hal.c
│   │   ├── device_registry.c
│   │   └── include/
│   └── services/
│       ├── CMakeLists.txt
│       ├── Kconfig
│       ├── env_service.c
│       ├── motion_service.c
│       ├── voice_service.c
│       ├── cloud_service.c
│       ├── ui_service.c
│       ├── service_manager.c
│       └── include/
├── docs/
└── tools/
```

## 模块职责

- `main/`
  只负责启动流程与异常出口，不直接写外设读写逻辑。

- `components/board/`
  保存所有板级资源参数，任何 GPIO/I2C/I2S/LCD 变更都从这里走。

- `components/drivers/`
  面向“设备”封装，不掺业务判断。驱动层要能在无云端、无 UI 时独立调通。

- `components/services/`
  面向“场景”封装，把多个驱动组织成环境感知、动作评分、语音交互等能力。

- `docs/`
  保存系统架构、bring-up 步骤、任务拆分和待确认硬件项，保证多人协作时信息不丢。

- `tools/`
  后续放 IMU 数据采集、DTW 模板整理、RAG 资源处理和测试脚本。

## 放代码时的约束

- 新增外设驱动，优先落在 `components/drivers/`。
- 新增板级 pin 定义或时序参数，只改 `components/board/`。
- 新增业务流程、训练逻辑或云端接口，只改 `components/services/`。
- 除非必须，否则不要在 `main/` 增加新逻辑。

## 推荐分支策略

- `main`：始终保持可编译。
- `feature/board-bringup`
- `feature/sensor-hub`
- `feature/audio-pipeline`
- `feature/ui-display`
- `feature/cloud-link`
- `feature/motion-score`
- `docs/*`

## 推荐提交流程

1. 先在 `docs/hardware-open-items.md` 补充假设。
2. 再在对应功能分支实现。
3. 本地 `idf.py build` 通过后再合入 `main`。
