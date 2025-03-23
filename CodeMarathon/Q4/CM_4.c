#include "ti_msp_dl_config.h"
#include "stdio.h"

#define UART_BUFFER_SIZE (4)
#define RXTX_BUFFER_SIZE (264)
#define TRUE (1)
#define FALSE (0)

uint8_t TXBuffer[RXTX_BUFFER_SIZE];
uint8_t TXIndex = 0;
uint16_t bytesRemaining = 0;
volatile uint32_t timerCounter = 0;
volatile uint8_t distanceArray[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
volatile uint8_t distanceIndex = 0;
volatile uint16_t flag = FALSE;


void addData(uint8_t* data, uint16_t dataSize) {
    for (uint8_t i = 0; i < dataSize; i++) {
        TXBuffer[i] = data[i];
    }
    bytesRemaining = dataSize;
}

void transmitData() {
    while (bytesRemaining > 0) {
        uint8_t bytesToSend = (bytesRemaining > UART_BUFFER_SIZE) ? UART_BUFFER_SIZE : bytesRemaining;
        DL_GPIO_setPins(GPIO_UART_0_TX_PORT, GPIO_UART_0_TX_PIN);
        DL_UART_Main_fillTXFIFO(UART_0_INST, &TXBuffer[TXIndex], bytesToSend);
        while (DL_UART_Main_isBusy(UART_0_INST));
        DL_GPIO_clearPins(GPIO_UART_0_TX_PORT, GPIO_UART_0_TX_PIN);
        TXIndex += bytesToSend;
        bytesRemaining -= bytesToSend;
    }
    TXIndex = 0;
}

void delay_ms(uint32_t milliseconds) {
    uint32_t start = timerCounter;
    while ((timerCounter - start) < milliseconds);
}

int main(void) {
    SYSCFG_DL_init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerA_startCounter(TIMER_0_INST);
    uint32_t nextToggleTime = 0;

    while (1) {
        if (FALSE == flag) {
            __WFI();
        }
        uint8_t currentDistance = distanceArray[distanceIndex];
        flag = FALSE;

        // Print current distance to console
        printf("Current distance: %d\n", currentDistance);

        // Check and act based on the current distance
        if (currentDistance < 2) {
            if (timerCounter >= nextToggleTime) {
                DL_GPIO_togglePins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
                uint8_t TXmsg[] = "Danger: distance less than 2 meters";
                addData(TXmsg, sizeof(TXmsg) - 1);
                if (bytesRemaining > 0) {
                    transmitData();
                }
                nextToggleTime = timerCounter + 50; // 0.5 second delay (50 * 10ms)
            }
        } else if (currentDistance < 5) {
            if (timerCounter >= nextToggleTime) {
                DL_GPIO_togglePins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
                uint8_t TXmsg[] = "Warning: distance less than 5 meters";
                addData(TXmsg, sizeof(TXmsg) - 1);
                if (bytesRemaining > 0) {
                    transmitData();
                }
                nextToggleTime = timerCounter + 100; // 1 second delay (100 * 10ms)
            }
        } else if (currentDistance < 10) {
            if (timerCounter >= nextToggleTime) {
                DL_GPIO_togglePins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
                uint8_t TXmsg[] = "Caution: distance less than 10 meters";
                addData(TXmsg, sizeof(TXmsg) - 1);
                if (bytesRemaining > 0) {
                    transmitData();
                }
                nextToggleTime = timerCounter + 200; // 2 seconds delay (200 * 10ms)
            }
        }

        distanceIndex = (distanceIndex + 1) % 10; // Cycle through distanceArray
        delay_ms(500); // Add delay of 500ms between each iteration
    }
}

void TIMER_0_INST_IRQHandler(void) {
    timerCounter++;
    flag = TRUE;
}
