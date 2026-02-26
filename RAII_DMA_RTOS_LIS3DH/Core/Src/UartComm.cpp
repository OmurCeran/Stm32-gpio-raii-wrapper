#include "UartComm.hpp"

/*Static array of UartCommunication instances*/
UartCommunication* UartCommunication::instance[MAX_UART_INSTANCES] = {nullptr};

UartCommunication::UartCommunication(UART_HandleTypeDef* huart) : huart(huart) , rx_read_index(0), rx_write_index(0) {
    /*Assign the instance to the static array based on the UART instance number*/
    if(huart->Instance == USART1) instance[0] = this;
    else if(huart->Instance == USART2) instance[1] = this;
    else if(huart->Instance == USART3) instance[2] = this;
    else if(huart->Instance == UART4) instance[3] = this;
    else if(huart->Instance == UART5) instance[4] = this;
    else if(huart->Instance == USART6) instance[5] = this;
}
/*Destructor for UartCommunication class*/
UartCommunication::~UartCommunication() {
    /*Remove the instance from the static array*/
    for(int i = 0; i < MAX_UART_INSTANCES; i++) {
        if(instance[i] == this) {
            instance[i] = nullptr;
            break;
        }
    }
}
/*Listen IDLE function*/
void UartCommunication::startIdleListening() {
    /*Circular buffer for DMA, continuosly write for buffer , if line is idle , inform*/
    HAL_UARTEx_ReceiveToIdle_DMA(huart, rx_buffer, RX_BUFFER_SIZE);

    /*Half-transfer callback IRQ is disabled*/
    __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
}
/*Transmit function for UART*/
bool UartCommunication::transmit(const uint8_t* data, uint16_t size) {
    /*Start UART transmission using HAL library*/
    if(HAL_UART_Transmit_DMA(huart, const_cast<uint8_t*>(data), size) == HAL_OK) {
        /*Wait for the DMA transfer to complete, sleep RTOS , this will be woken up by the ISR*/
        return (xSemaphoreTake(tx_sem, portMAX_DELAY) == pdTRUE);
    }
    return false;
}
/*Receive function for UART*/
uint16_t UartCommunication::receive(uint8_t* buffer, uint16_t size) {
    /*Sleep until new value comes in*/
    /*After ISR , we will wake up the task*/
    if(xSemaphoreTake(rx_sem, pdMS_TO_TICKS(5000)) == pdTRUE) {
        uint16_t bytes_copy = 0;
        /*Copy data from the ring buffer to the provided buffer*/
        uint16_t current_write_index = rx_write_index; // Capture the current write index
        while(rx_read_index != current_write_index && bytes_copy < size) {
            buffer[bytes_copy++] = rx_buffer[rx_read_index]; // Copy byte and increment read index
            rx_read_index = (rx_read_index + 1) % RX_BUFFER_SIZE; // Wrap around the buffer
        }
        return bytes_copy;/*Return the number of bytes copied*/
    }
    return 0; /*Timeout occurred*/
}
/*The Bridge for Tx_ISR*/
void UartCommunication::Tx_ISR_Bridge(UART_HandleTypeDef* huart) {
    /*Find the corresponding instance based on the UART instance number*/
    for(int i = 0; i < MAX_UART_INSTANCES; i++) {
        if(instance[i] != nullptr && instance[i]->huart->Instance == huart->Instance) {
            /*Give the semaphore to wake up the waiting task*/
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            instance[i]->giveTxSemaphoreFromISR(&xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            break;
        }
    }
}
/*The Bridge for Rx_ISR*/
void UartCommunication::Rx_ISR_Bridge(UART_HandleTypeDef* huart, uint16_t position) {
    /*Find the corresponding instance based on the UART instance number*/
    for(int i = 0; i < MAX_UART_INSTANCES; i++) {
        if(instance[i] != nullptr && instance[i]->huart->Instance == huart->Instance) {
            /*Update the write index based on the DMA position*/
            instance[i]->rx_write_index = position;
            /*Give the semaphore to wake up the waiting task*/
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            instance[i]->giveRxSemaphoreFromISR(&xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            break;
        }
    }
}