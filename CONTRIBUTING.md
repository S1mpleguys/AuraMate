# 协作说明

## 结论

这个仓库当前处于比赛研发早期，最重要的是保证目录边界稳定、假设统一、分支清晰。不要在一个提交里同时改板级、驱动、服务和文档。

## 分支建议

- `main`
  始终保持可编译、可同步

- `feature/<module>`
  例如 `feature/sensor-hub`、`feature/audio-hal`、`feature/cloud-link`

- `docs/<topic>`
  用于纯文档修改

## 提交前检查

1. 相关硬件假设是否已经写入 `docs/hardware-open-items.md`
2. 是否只在对应层目录修改代码
3. 是否执行过 `idf.py build`
4. 是否补充了必要注释和错误处理

## 目录修改约束

- 改 GPIO/I2C/I2S/LCD/RGB 配置：优先改 `components/board/`
- 改具体设备读写：优先改 `components/drivers/`
- 改业务流程和状态机：优先改 `components/services/`
- 除非必须，不要把业务逻辑放进 `main/`

## 当前阶段特别注意

- 现在很多驱动还是占位层，不要误以为已经完成真实外设接入
- 任何“硬编码引脚”在提交前都要确认是否已经写入 `menuconfig`
- 涉及外设型号、时序和协议时，如果资料还不完整，先在文档里写“假设条件”
