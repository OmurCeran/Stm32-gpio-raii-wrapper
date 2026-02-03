#ifndef STM32LED_HPP
#define STM32LED_HPP
#include "stm32ILed.hpp"
#include "stm32f4xx_hal.h"
/*Derived class definition for STM32 LED control class*/
class stm32Led : public ILED
{
private:
GPIO_TypeDef *Port_selection;
uint16_t pin_selection;
bool led_status;
public:
/*Constructor to initialize the GPIO pin for LED control*/
/*RAII constructor LED, it is called when obj is created.*/
    stm32Led(GPIO_TypeDef *port, uint16_t pin) : Port_selection(port), pin_selection(pin), led_status(false) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = pin_selection;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(Port_selection, &GPIO_InitStruct);

        Off();
    };
    ~stm32Led() override{
        Off(); /*Turn off LED in destructor*/
    };
/*Override virtual functions from ILED interface*/
    void On() override{
        HAL_GPIO_WritePin(Port_selection, pin_selection, GPIO_PIN_SET);
        led_status = true;
    };
    void Off() override{
        HAL_GPIO_WritePin(Port_selection, pin_selection, GPIO_PIN_RESET);
        led_status = false;
    };
    void Toggle() override{
        led_status = !led_status;
        HAL_GPIO_WritePin(Port_selection, pin_selection, led_status ? GPIO_PIN_SET : GPIO_PIN_RESET);
    };
    bool IsOn() const override{
        return led_status;
    };
};


#endif