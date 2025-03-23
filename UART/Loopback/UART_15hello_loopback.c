#include "ti_msp_dl_config.h"

#define UART_BUFFER_SIZE (100)
uint8_t txBuffer[UART_BUFFER_SIZE];
uint8_t rxBuffer[UART_BUFFER_SIZE];
uint8_t bufferIndex = 0;
uint8_t dataLength = 0;

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    while (1) {
        if(bufferIndex >= rxBuffer[1] + 1){
            printf("Transmitting %d \n: ", dataLength);
            for(int i =2; i<bufferIndex; i++) {
                DL_UART_transmitData(UART_0_INST, rxBuffer[i]);
                while(DL_UART_isBusy(UART_0_INST)); //checks if it is done transmitting the previous byte before proceeding to the next
                printf("%c", rxBuffer[i]);
            }
            printf("\n");
            bufferIndex = 0;
            dataLength = 0;
        }
        __NOP();

    }
}

void UART_0_INST_IRQHandler(void) {
    switch(DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
    case DL_UART_MAIN_IIDX_RX:
        while(!DL_UART_isRXFIFOEmpty(UART_0_INST)) { //until buffer is not empty
            uint8_t oneByte = DL_UART_Main_receiveData(UART_0_INST);
            if(bufferIndex < UART_BUFFER_SIZE)
            {
                if(bufferIndex == 1)
                {
                    dataLength = oneByte;
                }
                rxBuffer[bufferIndex] = oneByte;
                bufferIndex++;
            }
        }
        break;
    default:
        break;
    }
}
