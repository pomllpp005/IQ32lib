-- # IQ32

**STM32F466RET** is part of the STM32F4 series, featuring:

- **Core:** ARM Cortex-M4 32-bit, up to 180 MHz
- **Flash Memory:** 512 KB
- **SRAM:** 128 KB
- **GPIO:** Up to 82 general-purpose I/Os
- **Timers:** Multiple 16-bit and 32-bit timers for PWM, input capture, etc.
- **ADC:** 12-bit, up to 24 channels
- **Communication:** UART, SPI, I2C, CAN, USB
- **PWM Support:** Up to 168 MHz timer clocks for high-frequency PWM
- **Voltage Range:** 1.8V to 3.6V

**Key features in this project:**

- Read multiple analog sensors via ADC and 16-channel MUX  
- Display numerical data (float and integer) and strings on SSD1306 OLED  
- Generate PWM signals for motor control, configurable frequency  
- Supports both I2C and SPI for OLED communication  

---

## ⚙️ Setup & Usage

### 1. Hardware Connection

- **ADC Sensors:** Connect sensor outputs to **MUX** channels (PA3 for analog input)  
- **MUX Control Pins:**  
  - S0 → PC7  
  - S1 → PC6  
  - S2 → PB10  
  - S3 → PB2  
- **OLED Display:** Connect via **I2C** (default) or **SPI**  
- **PWM Motor Output:** Connect to the corresponding timer output pin (e.g., TIM2_CH1)

### 2. Software Setup

1. https://github.com/stm32duino/Arduino_Core_STM32
2. https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json


IQ32_Init();           // Board and peripheral initialization
Battery_Init();        // ADC and battery measurement
MUX_Init();            // Multiplexer initialization
ssd1306_Init();        // OLED initialization

3. Reading ADC Values
Single channel:


Copy code
uint16_t rawValue = MUX_Read();
float voltage = Battery_GetVoltage();
Average over samples:


Copy code
float avgVoltage = Battery_GetVoltage_Avg();
4. Displaying Data on OLED
Integer:


Copy code
OLED_ShowInt(123, x_column, y_line);
Float:


Copy code
OLED_ShowFloat(7.61, 2, x_column, y_line); // 2 decimal places
String + Integer in one function:


Copy code
OLED_ShowStringInt("Sensor:", 3, 15); // Example: "Sensor: 123"
5. Generating PWM
Configure TIM2 for motor PWM:


Copy code
htim2.Instance = TIM2;
htim2.Init.Prescaler = 84 - 1;    // Timer tick 1 MHz
htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
htim2.Init.Period = 200 - 1;      // 5 kHz PWM
HAL_TIM_PWM_Init(&htim2);
Adjust Period for different PWM frequencies:

PWM Frequency	Prescaler	Period
1 kHz	84-1	999
5 kHz	84-1	199
10 kHz	84-1	99

6. Switch Input
Read a switch (SW1/SW2) for triggering display or action:


Copy code
if(Read_SW2() == 1) {
    // Do something, e.g., display sensor values
} -->