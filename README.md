# STM32F103ZET6 电赛驱动库

专为全国大学生电子设计竞赛(电赛)设计的STM32F103ZET6完整底层驱动库。拿来即用，适配历届电赛题目。

## 📋 项目概述

本项目提供了STM32F103ZET6微控制器的完整底层驱动代码，包括：

- ✅ **系统初始化** - 时钟配置、GPIO初始化
- ✅ **8个定时器驱动** - TIM1/TIM3/TIM4/TIM5/TIM8 PWM输出
- ✅ **5路UART通信** - UART1/UART2/UART3/UART4/UART5
- ✅ **OLED屏幕驱动** - SPI接口OLED显示
- ✅ **按键扫描** - 8个按键及拨码开关处理
- ✅ **ADC驱动** - 灰度传感器采集
- ✅ **I2C驱动** - 传感器通信
- ✅ **SPI驱动** - 高速通信
- ✅ **步进电机驱动** - 两路步进电机控制
- ✅ **MOS电机驱动** - 直流电机PWM控制
- ✅ **蜂鸣器驱动** - 报警和提示音
- ✅ **中断管理** - 完整的中断处理机制

## 🔧 硬件配置

### 核心处理器
- **MCU**: STM32F103ZET6 (144引脚, 512KB Flash, 64KB SRAM)
- **主频**: 72MHz
- **工作电压**: 3.3V/5V

### 外设接口

| 功能 | 接口 | 数量 | 引脚 |
|------|------|------|------|
| LCD屏幕 | SPI | 1 | SCREEN_CLK/MOSI/CS/DC/RES |
| 按键 | GPIO | 8 | KEY1-KEY5, SW1-SW5 |
| 定时器PWM | TIM1/3/4/5/8 | 8路 | CH1/CH2各通道 |
| UART | UART1/2/3/4/5 | 5路 | TX/RX |
| 灰度传感器 | ADC | 1 | H9 |
| 步进电机 | GPIO+PWM | 2 | U1/U2 |
| 直流电机 | MOS驱动 | 2 | MOS1/MOS2 |
| 蜂鸣器 | GPIO | 1 | BUZZER |
| LED指示灯 | GPIO | 2 | LED1/LED2 |

## 📁 项目结构

```
STM32F103-Driver/
├── Inc/                          # 头文件目录
│   ├── stm32f10x_conf.h         # 标准库配置
│   ├── stm32f10x_it.h           # 中断处理头文件
│   ├── sys.h                    # 系统初始化
│   ├── gpio.h                   # GPIO驱动
│   ├── uart.h                   # UART通信 (5路)
│   ├── timer.h                  # 定时器驱动
│   ├── spi.h                    # SPI驱动
│   ├── i2c.h                    # I2C驱动
│   ├── oled.h                   # OLED屏幕驱动
│   ├── adc.h                    # ADC驱动
│   ├── motor.h                  # 步进电机驱动
│   ├── servo.h                  # PWM舵机驱动
│   ├── buzzer.h                 # 蜂鸣器驱动
│   └── key.h                    # 按键扫描驱动
├── Src/                          # 源文件目录
│   ├── main.c                   # 主程序 (示例)
│   ├── stm32f10x_it.c          # 中断处理
│   ├── sys.c                    # 系统初始化实现
│   ├── gpio.c
│   ├── uart.c
│   ├── timer.c
│   ├── spi.c
│   ├── i2c.c
│   ├── oled.c
│   ├── adc.c
│   ├── motor.c
│   ├── servo.c
│   ├── buzzer.c
│   └── key.c
├── Startup/                      # 启动文件
│   └── startup_stm32f10x_hd.s   # STM32F10x高密度启动文件
├── Doc/                          # 文档
│   ├── 引脚配置表.md
│   ├── 电赛题目适配指南.md
│   └── 调试技巧.md
├── project.uvprojx               # Keil MDK项目文件
└── README.md
```

## 🚀 快速开始

### 1. 下载项目
```bash
git clone https://github.com/Zhao-Luu/STM32F103-Driver.git
cd STM32F103-Driver
```

### 2. 在Keil中打开项目
- 打开 Keil MDK-ARM
- File → Open Project
- 选择 `project.uvprojx`

### 3. 配置编译器
- 选择编译器版本 (推荐 ARM Compiler v5.x)
- 配置Flash编程器 (ST-Link v2)

### 4. 编译并下载
```
Build (F7) → Download (F8)
```

## 📝 使用示例

### 初始化系统
```c
#include "sys.h"

int main(void)
{
    SystemInit();           // 系统初始化
    SysTick_Init();        // 滴答定时器
    GPIO_Init();           // GPIO初始化
    UART1_Init(115200);    // UART1初始化
    
    while(1)
    {
        // 你的应用代码
    }
}
```

### OLED屏幕显示
```c
#include "oled.h"

OLED_Init();                              // 初始化OLED
OLED_ShowString(0, 0, "Hello STM32!");   // 显示字符串
OLED_Refresh();                           // 刷新屏幕
```

### UART通信
```c
#include "uart.h"

// 发送数据
UART1_SendByte(0x55);
UART1_SendString("Hello\r\n");

// 接收数据 (中断方式)
// 在中断处理函数中自动接收
```

### PWM输出 (电机/舵机)
```c
#include "timer.h"

// TIM1 CH1通道输出50% PWM
TIM1_SetPWM(TIM_CHANNEL_1, 500);  // 0-1000映射为0-100%

// TIM3 CH2通道
TIM3_SetPWM(TIM_CHANNEL_2, 800);
```

### 按键扫描
```c
#include "key.h"

uint8_t key_val = KEY_Scan();  // 扫描按键
if(key_val == KEY1_PRESS)      // 检测KEY1按下
{
    // 处理按键事件
}
```

### ADC采集 (灰度传感器)
```c
#include "adc.h"

uint16_t adc_value = ADC_GetValue(ADC_CH9);  // 读取灰度值
```

## 🔌 引脚分配表

| 功能 | GPIO | 说明 |
|------|------|------|
| UART1_TX | PA9 | 通信1发送 |
| UART1_RX | PA10 | 通信1接收 |
| UART2_TX | PA2 | 通信2发送 |
| UART2_RX | PA3 | 通信2接收 |
| OLED_CLK | PB13 | OLED时钟 |
| OLED_MOSI | PB15 | OLED数据 |
| OLED_CS | PB12 | OLED片选 |
| OLED_DC | PB14 | OLED数据/命令 |
| OLED_RES | PB11 | OLED复位 |
| KEY1 | PE5 | 按键1 |
| KEY2 | PE6 | 按键2 |
| LED1 | PB5 | 指示灯1 |
| LED2 | PE5 | 指示灯2 |
| BUZZER | PB8 | 蜂鸣器 |
| TIM1_CH1 | PA8 | 定时器1通道1 |
| TIM3_CH1 | PA6 | 定时器3通道1 |
| ... | ... | ... |

## 💡 电赛常见题目应用

### 循迹小车
- 使用灰度传感器采集地面信息 (ADC)
- PWM控制直流电机转速 (TIM3/TIM4)
- OLED显示实时信息
- 按键切换工作模式

### 智能车
- 步进电机控制转向 (U1/U2)
- 直流电机控制速度 (MOS驱动)
- 多传感器融合 (I2C/SPI)
- UART与上位机通信

### 机器人控制
- 多路PWM控制关节 (TIM1/3/4/5/8)
- 舵机精确控制 (PWM调制)
- 实时显示机器人状态 (OLED)
- 蜂鸣器提示和报警

## 🛠️ 编译环境

- **IDE**: Keil MDK-ARM v5.x
- **编译器**: ARM Compiler v5.x 或 v6.x
- **库**: STM32F10x 标准库 v3.5.0
- **OS**: Windows / Linux / macOS

## 📚 文档

详细文档请参考 `Doc/` 文件夹：
- `引脚配置表.md` - 完整的引脚映射表
- `电赛题目适配指南.md` - 历届题目的应用方案
- `调试技巧.md` - 常见问题和解决方案

## ⚠️ 注意事项

1. **电源电压**: 确保电压稳定在3.3V或5V
2. **晶振频率**: 使用8MHz外部晶振
3. **SWD下载**: 使用ST-Link v2进行代码下载
4. **中断优先级**: 不要修改中断优先级配置，除非你完全理解后果

## 📞 反馈与支持

如有问题或建议，请提交Issue或Pull Request。

## 📄 许可证

MIT License - 自由使用和修改

---

**最后更新**: 2026年6月9日  
**维护者**: Zhao-Luu  
**版本**: v1.0.0

**祝你电赛取得好成绩！** 🎉
