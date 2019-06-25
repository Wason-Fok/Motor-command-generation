# 星火 STD2611M 控制器命令生成工具

![Build-passing](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Qt](https://img.shields.io/badge/Qt-5.12.0-orange.svg)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-2015-blueviolet.svg)
![License](https://img.shields.io/badge/license-Apache%20License%202.0-blue.svg)
[![Follow](https://img.shields.io/github/followers/Wason-Fok.svg?label=%E5%85%B3%E6%B3%A8%E6%88%91&style=social)](https://github.com/Wason-Fok)

![PNG](IMAGE/application.PNG)

## 2019/06/25 更新记录
- 初始版本

### 支持功能
- 选择机器码、对应控制命令以及数据值，程序通过 CRC16/MODBUS 验证算法自动计算出对应的调试控制命令以及 Modulo 服务器所需的控制命令数据格式。
- 添加常用命令汇总窗口
- 添加关于窗口

#### 依赖
- Qt 5.12.0
- Visual Studio 2015