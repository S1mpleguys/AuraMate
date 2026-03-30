# AuraMate

基于 `ESP32-C5 + ESP-IDF v5.4.1` 的乐鑫比赛项目，目标是实现《方案一》中的“AI 气韵小师”居家国术康养伴侣。当前仓库已经完成第一阶段的工程化收口：目录分层、板级配置入口、驱动占位层、服务编排层、协作文档和构建入口都已固定，后续可以直接并行推进硬件 bring-up、动作算法、语音链路和云端接口。

## 项目定位

- 比赛方向：智能康养 / 多模态交互 / 传统功法训练辅助
- 设备形态：佩戴式主机，联动传感器、音频、屏幕、RGB 灯效
- 主控平台：`ESP32-C5`
- 当前阶段：`P0 - 工程骨架稳定，可开始真实驱动接入`

## 当前约束与假设

- 构建环境固定为 `ESP-IDF v5.4.1`
- Flash 容量按 `2MB` 规划
- 已知资源包含 Bosch 传感器子板、I2S 麦克风/扬声器、LCD、RGB、Wi-Fi/BLE
- 具体引脚、LCD 控制器、音频 codec、传感器地址和 BLE 扩展节点协议仍待确认

## 仓库入口

- 文档总入口：`docs/README.md`
- 运行时入口：`main/app_entry.c`
- 板级配置入口：`components/board/`
- 外设封装入口：`components/drivers/`
- 业务服务入口：`components/services/`

## 目录总览

```text
AuraMate/
├── CMakeLists.txt
├── sdkconfig.defaults
├── partitions.csv
├── main/                  # 启动入口与状态切换
├── components/
│   ├── board/             # 板级资源与 menuconfig
│   ├── drivers/           # 传感器/音频/显示/RGB 占位驱动
│   └── services/          # 环境/动作/语音/云端/UI 服务编排
├── docs/                  # 架构、bring-up、任务、演示与待确认项
└── tools/                 # 数据采集、模板处理、发布脚本预留
```

## 快速开始

1. 配置 ESP-IDF 环境。
2. 首次拉取后执行：

```bash
idf.py set-target esp32c5
idf.py build
```

3. 需要修改板级引脚或功能开关时执行：

```bash
idf.py menuconfig
```

当前工程已经预留以下菜单：

- `AuraMate Board Config`
- `AuraMate Feature Flags`

如果当前目录来自旧的最小工程，且本地还保留旧 `sdkconfig`，建议先删除本地 `sdkconfig` 后重新执行 `idf.py build`，这样 `sdkconfig.defaults` 和 `partitions.csv` 才会完整接管配置。

## 当前已经完成

- 标准 ESP-IDF 比赛项目目录分层
- `main -> board -> drivers -> services` 调用链打通
- 板级资源、外设占位、服务占位、状态机骨架
- `sdkconfig.defaults` 与分区表
- 架构文档、bring-up 清单、任务拆分、演示脚本和协作规范

## 当前还没做的部分

- 真实 I2C / I2S / LCD / RGB 外设驱动接入
- 传感器周期采样与动作特征提取任务
- 云端 HTTP/MQTT 鉴权、上报和流式回包
- 唤醒词、ASR、LLM、TTS 闭环
- 比赛演示数据和训练报告输出

## 推荐开发顺序

1. 确认硬件引脚和实际芯片型号
2. 接通 `sensor_hub`
3. 接通 `display_hal` 与 `light_hal`
4. 接通 `audio_hal`
5. 落地 `motion_service` 与 `env_service`
6. 最后再打通云端与语音链路

## 协作约定

- `main` 分支始终保持可编译
- 硬件假设先写进 `docs/hardware-open-items.md`
- 接近硬件的代码优先放在 `components/board` 或 `components/drivers`
- 业务编排和模式切换只放在 `components/services`
- 提交前至少执行一次本地 `idf.py build`

## 文档导航

- `docs/README.md`
- `docs/architecture.md`
- `docs/project-layout.md`
- `docs/bringup-checklist.md`
- `docs/task-breakdown.md`
- `docs/hardware-open-items.md`
- `docs/demo-script.md`
- `CONTRIBUTING.md`
- `CHANGELOG.md`
