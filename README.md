# AuraMate

基于 `ESP32-C5 + ESP-IDF v5.4.1` 的乐鑫比赛项目骨架，面向《方案一》中的“AI 气韵小师”居家国术康养伴侣。当前阶段重点是把目录分层、模块边界、构建入口和协作文档一次搭好，方便团队并行推进传感器、音频、显示、算法和云端联调。

## 当前假设

- 主控芯片：`ESP32-C5`
- 构建环境：`ESP-IDF v5.4.1`
- Flash 容量：`2MB`
- 已知外设：Bosch 传感器子板、I2S 麦克风/扬声器、LCD、RGB、Wi-Fi/BLE
- 未确认项：具体引脚、LCD 控制器、音频 codec、传感器地址与扩展 BLE 节点协议

## 目录总览

```text
AuraMate/
├── CMakeLists.txt
├── sdkconfig.defaults
├── partitions.csv
├── main/                  # 入口编排层，只处理启动顺序和状态切换
├── components/
│   ├── board/             # 板级资源、Kconfig、总线占位
│   ├── drivers/           # 传感器/音频/显示/RGB 外设封装
│   └── services/          # 环境、动作、语音、云端、UI 服务
├── docs/                  # 架构、任务拆分、bring-up 清单、待确认硬件项
└── tools/                 # 采样、模型、数据转换等脚本预留目录
```

详细规划见：

- `docs/architecture.md`
- `docs/project-layout.md`
- `docs/bringup-checklist.md`
- `docs/task-breakdown.md`
- `docs/hardware-open-items.md`

## 构建方法

1. 配置 ESP-IDF 环境。
2. 首次拉取后执行：

```bash
idf.py set-target esp32c5
idf.py build
```

3. 如需修改板级引脚或功能开关，执行：

```bash
idf.py menuconfig
```

当前骨架已经预留以下菜单：

- `AuraMate Board Config`
- `AuraMate Feature Flags`

如果当前目录来自旧的最小工程，且已经存在历史 `sdkconfig`，建议先删除本地 `sdkconfig` 后再重新 `idf.py build`，这样 `sdkconfig.defaults` 和 `partitions.csv` 才会完整生效。

## 协作约定

- `main` 分支保持可编译。
- 功能开发分支建议使用 `feature/<module>` 命名，例如 `feature/sensor-hub`。
- 文档分支建议使用 `docs/<topic>` 命名。
- 所有板级硬件假设先写入 `docs/hardware-open-items.md`，确认后再落驱动细节。
- 任何接近硬件的改动优先放入 `components/board` 和 `components/drivers`，避免业务代码直接操作寄存器或总线。

## 当前已完成

- 标准 ESP-IDF 比赛项目目录分层
- 启动入口、板级骨架、外设骨架、服务骨架
- `sdkconfig.defaults` 与自定义分区表
- 团队协作文档与 bring-up 清单

## 下一步建议

- 补齐实际板卡引脚定义与 LCD/音频芯片型号
- 在 `components/drivers` 中接入 BMI270/BMM350/BME690、LCD、I2S 真实驱动
- 在 `components/services` 中落地采样任务、音频流缓存、HTTP/MQTT 云端链路
- 在 `tools/` 中补 IMU 数据采集、DTW 模板生成与提示词资源脚本
