#include "main.h"
#include "key.h"
#include "multi_button.h"
#include "motor.h"

uint8_t read_button_gpio(uint8_t button_id)
{
    switch (button_id)
    {
    case 1:
        return HAL_GPIO_ReadPin(BUTTON123_GPIO_Port, BUTTON1_Pin);
    case 2:
        return HAL_GPIO_ReadPin(BUTTON123_GPIO_Port, BUTTON2_Pin);
    case 3:
        return HAL_GPIO_ReadPin(BUTTON123_GPIO_Port, BUTTON3_Pin);
    case 4:
        return HAL_GPIO_ReadPin(BUTTON4_GPIO_Port, BUTTON4_Pin);
    default:
        return 0;
    }
}

void btn1_single_click_handler(Button *btn, void *user_data)
{
    motor_speed[0].target_vel = 0.0;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_2);
}

void btn2_single_click_handler(Button *btn, void *user_data)
{
    motor_speed[0].target_vel = 50.0;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);
}

void btn3_single_click_handler(Button *btn, void *user_data)
{
    motor_speed[0].target_vel = 100.0;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_4);
}

void btn4_single_click_handler(Button *btn, void *user_data)
{
    motor_speed[0].target_vel = 300.0;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_5);
}

void key(void)
{
    static Button key[4];
    for (int i = 0; i < 4; i++)
    {
        button_init(&key[i], read_button_gpio, 0, i + 1);
    }

    button_attach(&key[0], BTN_SINGLE_CLICK, btn1_single_click_handler, NULL);
    button_attach(&key[1], BTN_SINGLE_CLICK, btn2_single_click_handler, NULL);
    button_attach(&key[2], BTN_SINGLE_CLICK, btn3_single_click_handler, NULL);
    button_attach(&key[3], BTN_SINGLE_CLICK, btn4_single_click_handler, NULL);

    for (int j = 0; j < 4; j++)
    {
        button_start(&key[j]);
    }
}