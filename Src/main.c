/**
  ******************************************************************************
  * @file    main.c
  * @author   Zhao-Luu
  * @version  V1.0.0
  * @date     June 9, 2026
  * @brief    Main program body
  ******************************************************************************
  */

#include "sys.h"
#include "gpio.h"
#include "uart.h"
#include "timer.h"
#include "key.h"
#include "oled.h"
#include "adc.h"
#include "motor.h"
#include "servo.h"
#include "buzzer.h"
#include "i2c.h"
#include "spi.h"

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* System initialization */
    SystemInit();           /* Clock configuration */
    SysTick_Init();        /* SysTick timer for Delay_ms/Delay_us */
    
    /* Peripheral initialization */
    GPIO_Init();            /* GPIO initialization */
    UART1_Init(115200);    /* UART1: 115200 baud rate */
    KEY_Init();            /* Key scan initialization */
    BUZZER_Init();         /* Buzzer initialization */
    
    /* Display initialization */
    OLED_Init();           /* OLED SPI display */
    OLED_Clear();
    OLED_ShowString(0, 0, "STM32F103ZET6");
    OLED_ShowString(0, 2, "Electronic Design");
    OLED_ShowString(0, 4, "Competition Kit");
    OLED_Refresh();
    
    /* Motor/Servo initialization */
    TIM1_PWM_Init(1000, 72);   /* TIM1: 72MHz/(1000*72) = 1kHz */
    TIM3_PWM_Init(1000, 72);   /* TIM3: 1kHz */
    TIM4_PWM_Init(1000, 72);   /* TIM4: 1kHz */
    StepMotor_Init();
    DCMotor_Init();
    Servo_Init();
    
    /* Sensor initialization */
    ADC_Init();            /* ADC for grayscale sensor */
    I2C1_Init();           /* I2C1 for sensors */
    SPI1_Init();           /* SPI1 for communication */
    
    /* Initial beep to indicate successful startup */
    BUZZER_Beep(100);
    Delay_ms(100);
    BUZZER_Beep(100);
    
    UART1_SendString("=== STM32F103ZET6 Electronic Design Kit ===\r\n");
    UART1_SendString("System initialized successfully!\r\n");
    
    /* Main loop */
    while(1)
    {
        /* Key scan */
        u8 key = KEY_Scan();
        
        if(key != KEY_NONE)
        {
            OLED_Clear();
            OLED_ShowString(0, 0, "Key Pressed: ");
            OLED_ShowNum(96, 0, key, 2);
            OLED_Refresh();
            
            /* Example: Control different devices by key */
            switch(key)
            {
                case KEY1_PRESS:
                    UART1_SendString("KEY1 pressed\r\n");
                    LED1_TOGGLE();
                    break;
                    
                case KEY2_PRESS:
                    UART1_SendString("KEY2 pressed\r\n");
                    LED2_TOGGLE();
                    BUZZER_Beep(50);
                    break;
                    
                case KEY3_PRESS:
                    UART1_SendString("KEY3 pressed\r\n");
                    /* Start motor or other action */
                    DCMotor1_SetSpeed(500);
                    break;
                    
                case KEY4_PRESS:
                    UART1_SendString("KEY4 pressed\r\n");
                    /* Stop motor */
                    DCMotor1_Stop();
                    break;
                    
                case KEY5_PRESS:
                    UART1_SendString("KEY5 pressed\r\n");
                    /* Servo control example */
                    Servo1_SetAngle(90);
                    break;
                    
                default:
                    break;
            }
            
            Delay_ms(20);  /* Debounce */
        }
        
        /* ADC sampling - grayscale sensor */
        u16 gray_value = ADC_GetGrayValue_Avg(10);
        
        /* Display on OLED */
        OLED_Clear();
        OLED_ShowString(0, 0, "Gray Sensor:");
        OLED_ShowNum(0, 2, gray_value, 4);
        
        /* Display system status */
        OLED_ShowString(0, 4, "Motors/Servos OK");
        OLED_ShowString(0, 6, "Ready for Contest");
        OLED_Refresh();
        
        Delay_ms(50);
    }
}

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    
    UART1_SendString("Assert failed at ");
    UART1_SendString((u8*)file);
    UART1_SendString(" line ");
    UART1_SendNum(line, 10);
    UART1_SendString("\r\n");
    
    while(1);
}
#endif

/************************ (C) COPYRIGHT Zhao-Luu *****************************/
