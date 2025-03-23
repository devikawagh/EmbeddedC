
#include "ti_msp_dl_config.h"
#include "stdio.h"

#define UART_BUFFER_SIZE (4)
#define RXTX_BUFFER_SIZE (264)
#define TRUE (1)
#define FALSE (0)

uint8_t TXBuffer[RXTX_BUFFER_SIZE];
uint8_t TXIndex = 0;
uint16_t bytesRemaining = 0;

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

void delay_ms(uint32_t ms) {
    // Implementing a basic software delay
    for (volatile uint32_t i = 0; i < ms * 1000; i++);
}

int main(void) {
    SYSCFG_DL_init();
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    while (1) {
        // Turn on LED1 and send message
        uint8_t TXmsg1[] = "Ambient Lighting Mode";
        addData(TXmsg1, sizeof(TXmsg1) - 1);
        DL_GPIO_setPins(GPIO_GRP_0_LED_PB22_PORT, GPIO_GRP_0_LED_PB22_PIN);
        if (bytesRemaining > 0) {
            transmitData();
        }
        delay_ms(5000); // 5 second delay

        // Turn off LED1
        DL_GPIO_clearPins(GPIO_GRP_0_LED_PB22_PORT, GPIO_GRP_0_LED_PB22_PIN);

        // Turn on LED2 and send message
        uint8_t TXmsg2[] = "Reading Lighting Mode";
        addData(TXmsg2, sizeof(TXmsg2) - 1);
        DL_GPIO_setPins(GPIO_GRP_0_LED_PB26_PORT, GPIO_GRP_0_LED_PB26_PIN);
        if (bytesRemaining > 0) {
            transmitData();
        }
        delay_ms(5000); // 5 second delay

        // Turn off LED2
        DL_GPIO_clearPins(GPIO_GRP_0_LED_PB26_PORT, GPIO_GRP_0_LED_PB26_PIN);

        // Turn on both LEDs and send message
        uint8_t TXmsg3[] = "Mood Lighting Mode";
        addData(TXmsg3, sizeof(TXmsg3) - 1);
        DL_GPIO_setPins(GPIO_GRP_0_LED_PB22_PORT, GPIO_GRP_0_LED_PB22_PIN);
        DL_GPIO_setPins(GPIO_GRP_0_LED_PB26_PORT, GPIO_GRP_0_LED_PB26_PIN);
        if (bytesRemaining > 0) {
            transmitData();
        }
        delay_ms(5000); // 5 second delay

        // Turn off both LEDs
        DL_GPIO_clearPins(GPIO_GRP_0_LED_PB22_PORT, GPIO_GRP_0_LED_PB22_PIN);
        DL_GPIO_clearPins(GPIO_GRP_0_LED_PB26_PORT, GPIO_GRP_0_LED_PB26_PIN);
    }
}


