/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdlib.h"
// app
#include "init.h"
#include "key.h"

// bsp
#include "motor.h"
#include "multi_button.h"
#include "Emm_V5.h"
#include "pid.h"
#include "hwt.h"
#include "lcd_fonts.h"
#include "lcd_spi_200.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

  uint8_t RxData;/*用于开启hwt中断回调*/
  float PID_K[3]={1.0,1.0,1.0};/*pid数组初始定义*/

  /*串口发送函数*/
  int _write(int file, char *ptr, int len)
  {
      HAL_UART_Transmit(&huart3, (uint8_t*)ptr, len, HAL_MAX_DELAY);
      return len;
  }

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  HAL_Delay(1000);

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM9_Init();
  MX_USART3_UART_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART6_UART_Init();
  MX_SPI1_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  
  Tim_Init();/*开启pwm，encoder，定时器*/
  Motor_Init();/*4500占空比，双极性，使能*/
  SPI_LCD_Init();/*lcd屏幕启动*/
  /*开启第一个motor的pid环*/
  PidInit(&motor_pid[1], POSITION_PID, 4500, 3000, 2.0f, PID_K[0],PID_K[1],PID_K[2]);
  PidInit(&motor_pid[2], POSITION_PID, 4500, 3000, 2.0f, PID_K[0],PID_K[1],PID_K[2]);


  /*按键*/
  key();


  /*进入hwt串口中断回调*/
  HAL_UART_Receive_IT(&huart3,&RxData,1);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/*usart中断回调，3->vofa，1-> hwt  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if (huart == &huart3)
    {
        static uint8_t RxIndex;
        static uint8_t RxPacket[128];
        static enum{
          Wait_Head, //等待包头
		      Wait_Flag, //等待接收标识
		      Wait_Data  //等待接收数据
	      }RxState=Wait_Head;//初始状�?�为等待�????
            
        static enum{
            CMD_NONE,  //空状�????
            CMD_Kp,    //Kp
            CMD_Ki,    //Ki
            CMD_Kd     //Kd
        }CurrentCmd=CMD_NONE; //初始为空状�??
            
        switch(RxState)
        {
            case Wait_Head:
                if(RxData=='K')
                {
                    RxState=Wait_Flag;
                }
                break;
            case Wait_Flag:
                if(RxData=='P')
                {
                    CurrentCmd=CMD_Kp;
                    RxState=Wait_Data;
                    RxIndex=0;
                }
                else if(RxData=='I')
                {
                    CurrentCmd=CMD_Ki;
                    RxState=Wait_Data;
                    RxIndex=0;
                }
                else if(RxData=='D')
                {
                    CurrentCmd=CMD_Kd;
                    RxState=Wait_Data;
                    RxIndex=0;
                }
                else
                    RxState=Wait_Head;
                break;

            case Wait_Data:
                if(RxData=='M')
                {
                    RxPacket[RxIndex]='\0';
                    uint8_t *endptr;
                    float NewValue = strtof((char*)RxPacket, (char**)&endptr);  // 双重转换
                    if(endptr!=RxPacket && *endptr == '\0') 
                    {
                        switch(CurrentCmd)
                        {
                            case CMD_Kp:
                                PID_K[0]=NewValue;
                                // printf("Kp updated:%.2f\n",PID_K[0]);
                                break;
                            case CMD_Ki:
                                PID_K[1]=NewValue;
                                // printf("Ki updated:%.2f\n",PID_K[1]);
                                break;
                            case CMD_Kd:
                                PID_K[2]=NewValue;
                                // printf("Kd updated:%.2f\n",PID_K[2]);
                                break;
                            case CMD_NONE:
                                break;
                        }
                    }
                    else
                        // printf("Error:%s\n",RxPacket);
                    RxState=Wait_Head;
                    CurrentCmd=CMD_NONE;
                }
                else
                {
                    if(RxIndex<sizeof(RxPacket)-1)
                    {
                        RxPacket[RxIndex++]=RxData;
                    }
                    else
                    {
                        RxState=Wait_Head;
                    }
                }
                break;
            default:
                RxState = Wait_Head;
                break;
        }
        HAL_UART_Receive_IT(&huart3,&RxData,1);
    }


  if (huart->Instance == USART1)
  {    

    static uint8_t buf[FRAME_SIZE];
    static uint8_t idx = 0;
    static uint8_t step = 0;

    switch (step)
    {
      case 0:
          if (rx_byte == 0x55)
          {
              buf[0] = 0x55;
              step = 1;
          }
          break;

      case 1:
          if (rx_byte == 0x53)
          {
              buf[1] = 0x53;
              idx = 2;
              step = 2;
          }
          else if (rx_byte == 0x55)
          {
              buf[0] = 0x55;
          }
          else
          {
              step = 0;
          }
          break;

      default:
          buf[idx++] = rx_byte;
          if (idx >= FRAME_SIZE) 
          {
              ParseYaw(buf, &yaw);
              step = 0;
          }
          break;
    }
  
  LCD_DisplayDecimals(10,10,yaw,6,2);
  HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
  }

}


/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  // static uint32_t tick_count = 0;

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  else if (htim->Instance == TIM6) // 5ms
  {
    // tick_count++;
    // if (tick_count % 5 == 0) // 5ms
    // {
    //   tick_count = 0;
    //   button_ticks();
    // }
    button_ticks();
  }
  else if (htim->Instance == TIM9) // 10ms   编码器计算并vofa
  {
    Get_Motor_Speed(&motor_speed[0].now_vel, &htim2);
    Get_Motor_Speed(&motor_speed[1].now_vel, &htim3);
    printf("Speed_1:%.2f\n", motor_speed[0].now_vel);
    printf("Speed_2:%.2f\n", motor_speed[1].now_vel);
  }

  else if (htim->Instance == TIM5) // 10ms  改变pid数值并进行pid环计算输出值 
  {
    motor_pid[0].p=PID_K[0];
    motor_pid[0].i=PID_K[1];
    motor_pid[0].d=PID_K[2];
    motor_pid[1].p=PID_K[0];
    motor_pid[1].i=PID_K[1];
    motor_pid[1].d=PID_K[2];
    float pid_output_1 = PidCalc(&motor_pid[0], motor_speed[0].now_vel, motor_speed[0].target_vel);
    float pid_output_2 = PidCalc(&motor_pid[1], motor_speed[1].now_vel, motor_speed[1].target_vel);
    Motor_Set_Vel_1((int16_t)pid_output_1);
    Motor_Set_Vel_2((int16_t)pid_output_2);
  }

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
