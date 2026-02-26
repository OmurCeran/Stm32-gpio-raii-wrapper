#pragma once
#include <cstdint> // C++ standard library for fixed-width integer types

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "semphr.h"
#ifdef __cplusplus
}
#endif

class ICommmunication
{
protected:
    SemaphoreHandle_t tx_sem;
    SemaphoreHandle_t rx_sem;
public:
    /*Constructor for DMA Synch Semaphore*/
    ICommmunication() : tx_sem(xSemaphoreCreateBinary()), rx_sem(xSemaphoreCreateBinary()) {}
    /*Destructor for DMA Synch Semaphore*/
    virtual ~ICommmunication() { 
        if(tx_sem != nullptr) vSemaphoreDelete(tx_sem);
        if(rx_sem != nullptr) vSemaphoreDelete(rx_sem);
     }
     /*Pure virtual functions for transmit and receive operations*/
    virtual bool transmit(const uint8_t* data, uint16_t size) = 0;
    virtual uint16_t receive(uint8_t* buffer, uint16_t size) = 0;

    virtual void startIdleListening() = 0; /*For UART, start listening for IDLE line detection*/

    /*Interrupt wake-up function*/
    void giveTxSemaphoreFromISR(BaseType_t *xHigherPriorityTaskWoken) {
        xSemaphoreGiveFromISR(tx_sem, xHigherPriorityTaskWoken);
    }
    void giveRxSemaphoreFromISR(BaseType_t *xHigherPriorityTaskWoken) {
        xSemaphoreGiveFromISR(rx_sem, xHigherPriorityTaskWoken);
    }
};