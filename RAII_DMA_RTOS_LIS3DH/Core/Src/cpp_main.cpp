#include "main.h"
#include "cmsis_os.h"
#include "CommFactory.hpp"
#include "main_cpp.h"
#include "UartComm.hpp"
#include <cstdio> // For printf function
/*Cubemx global variable*/
extern UART_HandleTypeDef huart2;

/*Smart pointer for UART communication*/
std::unique_ptr<ICommmunication> uartComm;

/*Bridge function between C and C++*/
extern "C" {
    void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
        /*Call the ISR bridge to handle the completion of UART transmission*/
        UartCommunication::Tx_ISR_Bridge(huart);
    }
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
        /*Call the ISR bridge to handle the reception event, providing the current DMA position*/
        UartCommunication::Rx_ISR_Bridge(huart, Size);
    }
}

void UART_ThreadTx(void *argument) {
    /*Example data to transmit*/
    uint8_t data[] = "Hello, UART with DMA and RTOS!\n\r";
//    uint8_t buffer[sizeof(data)] = {0};  // Initialize buffer with zeros
    while (1) {
        /*Transmit data using the UART communication interface*/
        uartComm->transmit(data, sizeof(data) - 1);  // -1 to exclude null terminator
//        vTaskDelay(500);  // Delay for 1 second before next transmission
    }
}
void UART_ThreadRx(void *argument) {
    uint8_t buffer[RX_BUFFER_SIZE] = {0};  // Buffer to store received data
    while (1) {
        /*Receive data using the UART communication interface*/
        uint16_t bytes_received = uartComm->receive(buffer, sizeof(buffer) - 1);  // -1 to exclude null terminator
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';  // Null-terminate the received data
            /*Process the received data as needed, e.g., print it or handle commands*/
            //printf("Received: %s\n", (char*)buffer);
            uartComm->transmit(buffer, bytes_received); // Echo back the received data
        }
    }
}
int main_cpp(void)
{
    /* Create UART communication instance using the factory */
    uartComm = CommunicationFactory::createUartCommunication(&huart2);

    if(uartComm != nullptr) {
            /*Start listening for IDLE line detection to handle incoming data*/
            uartComm->startIdleListening();
    }

    /* Create a thread for UART communication */
//    xTaskCreate(UART_ThreadTx, "UARTThreadTx", 512, NULL, osPriorityNormal, NULL);

    xTaskCreate(UART_ThreadRx, "UARTThreadRx", 512, NULL, osPriorityNormal, NULL);
    /* We should never get here as control is now taken by the scheduler */
    /*while (1) {
        // Optional: Add error handling or idle tasks here
    }*/
   return 0;
}