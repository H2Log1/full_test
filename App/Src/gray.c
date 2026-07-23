#include "gray.h"
#include "gpio.h"

float error=0;
void get_error(float *p)
{
  int a=1-(int)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3);
  int b=1-(int)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4);
  int c=1-(int)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5);
  int d=1-(int)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);
  int e=1-(int)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9);
  int f=1-(int)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10);
  int g=1-(int)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
  int h=1-(int)HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14);
  if ((a+b+c+d+e+f+g+h)==0){
    error =0;
  }
  else{
  *p= - (float)(((float)(4*a+3*b+2*c+1*d+
        (-1)*e+(-2)*f+(-3)*g+(-4)*h)) / (a+b+c+d+e+f+g+h));
  }    
}