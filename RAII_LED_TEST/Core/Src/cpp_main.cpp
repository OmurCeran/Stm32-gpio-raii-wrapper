#include "app_main.h"
#include "stm32Led.hpp"
#include <vector> /*Dynamic arrays*/
#include <memory> /*Smart pointers*/

void cpp_main(){

    std::vector<std::unique_ptr<ILED>> leds;

    leds.push_back(std::make_unique<stm32Led>(GPIOD, GPIO_PIN_12));
    leds.push_back(std::make_unique<stm32Led>(GPIOD, GPIO_PIN_13));
    leds.push_back(std::make_unique<stm32Led>(GPIOD, GPIO_PIN_14));
    leds.push_back(std::make_unique<stm32Led>(GPIOD, GPIO_PIN_15));

    while (1) {
        for (auto& led : leds) {
            led->Toggle();
            HAL_Delay(500);
        }
    }

}