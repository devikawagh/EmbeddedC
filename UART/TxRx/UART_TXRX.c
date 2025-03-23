#include "ti_msp_dl_config.h"
#include "stdio.h"

#define UART_BUFFER_SIZE (4)
#define RXTX_BUFFER_SIZE (264)
#define TRUE (1)
#define FALSE (0)

uint8_t TXBuffer[RXTX_BUFFER_SIZE];
uint8_t TXIndex = 0;
uint16_t bytesRemaining = 0;
uint8_t RXBuffer[RXTX_BUFFER_SIZE];
uint16_t RXIndex = 0;
uint8_t recievedData = 0;
volatile uint16_t flag = FALSE;


void addData(uint8_t* data, uint16_t dataSize) {
    for(uint8_t i =0; i<dataSize; i++) {
        TXBuffer[i] = data[i];
    }
    bytesRemaining = dataSize;
}

void transmitData() {
    while(bytesRemaining>0) {
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

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(GPIO_GRP_0_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    uint8_t TXmsg[] = "I am Devika Wagh";
    while (1) {
        if(FALSE == flag) {
            __WFI();
        }
        addData(TXmsg, sizeof(TXmsg)-1);
        if(bytesRemaining>0) {
            transmitData();
        }
        flag = FALSE;

        for(int i =0; i<20; i++) {
            printf("%c ", RXBuffer[i]);
        }
        printf("\n");
    }
}
void GROUP1_IRQHandler(void){
    switch(DL_GPIO_getPendingInterrupt(GPIOA)) {
    case DL_GPIO_IIDX_DIO18:
        flag = TRUE;
        break;
    default:
        break;
    }
}
void UART_0_INST_IRQHandler() {
    switch(DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
    case DL_UART_MAIN_IIDX_RX:
        while(!DL_UART_isRXFIFOEmpty(UART_0_INST)){
            uint8_t recieveOneByte = DL_UART_Main_receiveData(UART_0_INST);
            if(RXIndex < RXTX_BUFFER_SIZE){
                RXBuffer[RXIndex] = recieveOneByte;
                (RXIndex)++;
            }
        }
        break;
    case DL_UART_MAIN_IIDX_OVERRUN_ERROR:
        break;
    case DL_UART_MAIN_IIDX_FRAMING_ERROR:
        break;
    case DL_UART_MAIN_IIDX_PARITY_ERROR:
        break;
    case DL_UART_MAIN_IIDX_BREAK_ERROR:
        break;
    default:
        break;
    }
}
//#include "ti_msp_dl_config.h"
//#include "stdio.h"
//
//#define UART_BUFFER_SIZE (4)
//#define RXTX_BUFFER_SIZE (264)
//#define TRUE (1)
//#define FALSE (0)
//
//uint8_t TXBuffer[RXTX_BUFFER_SIZE];
//uint8_t TXIndex = 0;
//uint16_t bytesRemaining = 0;
//
//volatile uint8_t switch1Pressed = FALSE;
//volatile uint8_t switch2Pressed = FALSE;
//volatile uint16_t flag = FALSE;
//
//void addData(uint8_t* data, uint16_t dataSize) {
//    for(uint8_t i = 0; i < dataSize; i++) {
//        TXBuffer[i] = data[i];
//    }
//    bytesRemaining = dataSize;
//}
//
//void transmitData() {
//    while(bytesRemaining > 0) {
//        uint8_t bytesToSend = (bytesRemaining > UART_BUFFER_SIZE) ? UART_BUFFER_SIZE : bytesRemaining;
//        DL_GPIO_setPins(GPIO_UART_0_TX_PORT, GPIO_UART_0_TX_PIN);
//        DL_UART_Main_fillTXFIFO(UART_0_INST, &TXBuffer[TXIndex], bytesToSend);
//        while(DL_UART_Main_isBusy(UART_0_INST));
//        DL_GPIO_clearPins(GPIO_UART_0_TX_PORT, GPIO_UART_0_TX_PIN);
//        TXIndex += bytesToSend;
//        bytesRemaining -= bytesToSend;
//    }
//    TXIndex = 0;
//}
//
//int main(void) {
//    SYSCFG_DL_init();
//    NVIC_EnableIRQ(GPIO_GRP_0_GPIOA_INT_IRQN);
//    NVIC_EnableIRQ(GPIO_GRP_0_GPIOB_INT_IRQN);
//
//    while (1) {
//        if(FALSE == flag) {
//            __WFI();
//        }
//
//        if(switch1Pressed && switch2Pressed) {
//            uint8_t TXmsg[] = "Mood Lighting Mode";
//            addData(TXmsg, sizeof(TXmsg) - 1);
//            DL_GPIO_setPins(GPIO_GRP_0_LED_PB22_PORT, GPIO_GRP_0_LED_PB22_PIN);
//            DL_GPIO_setPins(GPIO_GRP_0_LED_PB26_PORT, GPIO_GRP_0_LED_PB26_PIN);
//            if(bytesRemaining > 0) {
//                transmitData();
//            }
//        } else if (switch1Pressed) {
//            uint8_t TXmsg[] = "Ambient Lighting Mode";
//            addData(TXmsg, sizeof(TXmsg) - 1);
//            DL_GPIO_setPins(GPIO_GRP_0_LED_PB22_PORT, GPIO_GRP_0_LED_PB22_PIN);
//            DL_GPIO_clearPins(GPIO_GRP_0_LED_PB26_PORT, GPIO_GRP_0_LED_PB26_PIN);
//            if (bytesRemaining > 0) {
//                transmitData();
//            }
//        } else if (switch2Pressed) {
//            uint8_t TXmsg[] = "Reading Lighting Mode";
//            addData(TXmsg, sizeof(TXmsg) - 1);
//            DL_GPIO_clearPins(GPIO_GRP_0_LED_PB22_PORT, GPIO_GRP_0_LED_PB22_PIN);
//            DL_GPIO_setPins(GPIO_GRP_0_LED_PB26_PORT, GPIO_GRP_0_LED_PB26_PIN);
//            if(bytesRemaining > 0) {
//                transmitData();
//            }
//        } else {
//            DL_GPIO_clearPins(GPIO_GRP_0_LED_PB22_PORT, GPIO_GRP_0_LED_PB22_PIN);
//            DL_GPIO_clearPins(GPIO_GRP_0_LED_PB26_PORT, GPIO_GRP_0_LED_PB26_PIN);
//        }
//
//        flag = FALSE;
//    }
//}
//
//void GROUP1_IRQHandler(void) {
//    switch (DL_GPIO_getPendingInterrupt(GPIOA)) {
//        case DL_GPIO_IIDX_DIO18: // Assuming Switch 1 is connected to DIO18
//            switch1Pressed = !switch1Pressed;
//            flag = TRUE;
//            break;
//        default:
//            break;
//    }
//    switch (DL_GPIO_getPendingInterrupt(GPIOB)) {
//        case DL_GPIO_IIDX_DIO21: // Assuming Switch 2 is connected to DIO21
//            switch2Pressed = !switch2Pressed;
//            flag = TRUE;
//            break;
//        default:
//            break;
//    }
//}
//
//void UART_0_INST_IRQHandler() {
//    // UART receive handling, if needed for future expansion
//}
//
//
