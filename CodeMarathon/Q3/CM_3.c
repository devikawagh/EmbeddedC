#include "ti_msp_dl_config.h"
#include "stdio.h"

#define UART_BUFFER_SIZE (4)
#define RXTX_BUFFER_SIZE (264)
#define TRUE (1)
#define FALSE (0)

uint8_t TXBuffer[RXTX_BUFFER_SIZE];
uint8_t TXIndex = 0;
uint16_t bytesRemaining = 0;

volatile uint16_t flag = FALSE;
volatile char receivedChar = '\0';

void addData(uint8_t* data, uint16_t dataSize) {
    for(uint8_t i = 0; i < dataSize; i++) {
        TXBuffer[i] = data[i];
    }
    bytesRemaining = dataSize;
}

void transmitData() {
    while(bytesRemaining > 0) {
        uint8_t bytesToSend = (bytesRemaining > UART_BUFFER_SIZE) ? UART_BUFFER_SIZE : bytesRemaining;
        DL_GPIO_setPins(GPIO_UART_0_TX_PORT, GPIO_UART_0_TX_PIN);
        DL_UART_Main_fillTXFIFO(UART_0_INST, &TXBuffer[TXIndex], bytesToSend);
        while(DL_UART_Main_isBusy(UART_0_INST));
        DL_GPIO_clearPins(GPIO_UART_0_TX_PORT, GPIO_UART_0_TX_PIN);
        TXIndex += bytesToSend;
        bytesRemaining -= bytesToSend;
    }
    TXIndex = 0;
}

int main(void) {
    SYSCFG_DL_init();
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    while (1) {
        if(FALSE == flag) {
            __WFI();
        }

        if(receivedChar == 'L') {
            uint8_t TXmsg[] = "Windshield wiper speed is low";
            addData(TXmsg, sizeof(TXmsg) - 1);
            if(bytesRemaining > 0) {
                transmitData();
            }
        } else if (receivedChar == 'M') {
            uint8_t TXmsg[] = "Windshield wiper speed is medium";
            addData(TXmsg, sizeof(TXmsg) - 1);
            if (bytesRemaining > 0) {
                transmitData();
            }
        } else if (receivedChar == 'H') {
            uint8_t TXmsg[] = "Windshield wiper speed is high";
            addData(TXmsg, sizeof(TXmsg) - 1);
            if(bytesRemaining > 0) {
                transmitData();
            }
        }

        receivedChar = '\0';
        flag = FALSE;
    }
}

void UART_0_INST_IRQHandler() {
    switch(DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_MAIN_IIDX_RX:
            while(!DL_UART_isRXFIFOEmpty(UART_0_INST)) {
                receivedChar = DL_UART_Main_receiveData(UART_0_INST);
                flag = TRUE;
            }
            break;
        default:
            break;
    }
}


