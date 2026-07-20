#ifndef __KEY_H
#define __KEY_H

#include "main.h"
#include "multi_button.h"

#define BUTTON123_GPIO_Port GPIOB
#define BUTTON4_GPIO_Port GPIOC
#define BUTTON1_Pin GPIO_PIN_13
#define BUTTON2_Pin GPIO_PIN_14
#define BUTTON3_Pin GPIO_PIN_15
#define BUTTON4_Pin GPIO_PIN_1

uint8_t read_button_gpio(uint8_t button_id);
void btn_single_click_handler(Button *btn, void *user_data);
void key(void);

#endif // __KEY_H