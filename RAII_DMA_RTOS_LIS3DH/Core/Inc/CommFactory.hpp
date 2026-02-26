#pragma once
#include <memory>
#include "UartComm.hpp"

class CommunicationFactory {
public:
/*ICommunication pointer return , because user will not know what comm is*/
    static std::unique_ptr<ICommmunication> createUartCommunication(UART_HandleTypeDef* huart) {
        return std::make_unique<UartCommunication>(huart);
    }
};