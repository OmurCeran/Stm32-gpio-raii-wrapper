#pragma once
#include "IComm.hpp"
#include "stm32f4xx_hal.h"
/*Max UART instances*/
#define MAX_UART_INSTANCES 6
/*Receiver buffer size*/
#define RX_BUFFER_SIZE 256

class UartCommunication : public ICommmunication
{
private:
        UART_HandleTypeDef* huart;
        /*Uart instances for whole UART adress*/
        /*The Bridge for C*/
        static UartCommunication* instance[MAX_UART_INSTANCES];

        /*Ring buffer for received data*/
        uint8_t rx_buffer[RX_BUFFER_SIZE];//DMA circular buffer
        volatile uint16_t rx_read_index; // Index for reading from the buffer
        volatile uint16_t rx_write_index; // Index for writing to the buffer (updated in ISR)

public:
        /*Constructor for UartCommunication class*/
        UartCommunication(UART_HandleTypeDef* huart);
        /*Destructor for UartCommunication class*/
        ~UartCommunication() override;
        /*First starting function for system*/
        void startIdleListening() override;

        bool transmit(const uint8_t* data, uint16_t size) override;
        uint16_t receive(uint8_t* buffer, uint16_t size) override;

        static void Tx_ISR_Bridge(UART_HandleTypeDef* huart);
        /*IDLE event bridge for rx, DMA position*/
        static void Rx_ISR_Bridge(UART_HandleTypeDef* huart, uint16_t position);
};