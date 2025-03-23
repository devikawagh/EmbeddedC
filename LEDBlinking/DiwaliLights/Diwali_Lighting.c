//#include "ti_msp_dl_config.h"
//
//volatile uint32_t timerCounter = 0;
//#define LED1_ON (50)
//#define LED2_ON (50)
//#define LED3_ON (50)
//
//int main(void)
//{
//    SYSCFG_DL_init();
//    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
//    DL_TimerA_startCounter(TIMER_0_INST);
//
//    while (1) {
//        if(timerCounter % (LED1_ON + LED2_ON + LED3_ON) < (LED1_ON)) {
//            DL_GPIO_setPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB22_PIN);
//            DL_GPIO_clearPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
//            DL_GPIO_clearPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB27_PIN);
//        }
//        else if (timerCounter % (LED1_ON + LED2_ON + LED3_ON) < (LED1_ON + LED2_ON))
//        {
//            DL_GPIO_clearPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB22_PIN);
//            DL_GPIO_setPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
//            DL_GPIO_clearPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB27_PIN);
//        }
//        else {
//            DL_GPIO_clearPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB22_PIN);
//            DL_GPIO_clearPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
//            DL_GPIO_setPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB27_PIN);
//        }
//
//    }
//}
//void TIMER_0_INST_IRQHandler(void) {
//    timerCounter++;
//}

#include "ti_msp_dl_config.h"
#include "stdio.h"

#define TRUE (1)
#define FALSE (0)

volatile uint32_t timerCounter = 0;
volatile uint8_t distanceArray[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
volatile uint8_t distanceIndex = 0;
volatile uint16_t flag = FALSE;

void addData(uint8_t* data, uint16_t dataSize) {
    DL_UART_Main_fillTXFIFO(UART_0_INST, data, dataSize);
    while(DL_UART_Main_isBusy(UART_0_INST));
}

void TIMER_0_INST_IRQHandler(void) {
    timerCounter++;
    flag = TRUE;
}

void configureTimer() {
    // Configure the hardware timer to generate interrupts every 10ms
    DL_TIMER_configure(TIMER_0_INST, 10); // 10ms intervals
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
}

int main(void) {
    SYSCFG_DL_init();
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    configureTimer();

    uint32_t nextToggleTime = 0;

    while (1) {
        if(FALSE == flag) {
            __WFI();
        }

        uint8_t currentDistance = distanceArray[distanceIndex];

        if (currentDistance < 2) {
            if (timerCounter >= nextToggleTime) {
                DL_GPIO_togglePins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
                uint8_t TXmsg[] = "Danger: distance less than 2 meters";
                addData(TXmsg, sizeof(TXmsg) - 1);
                nextToggleTime = timerCounter + 50; // 0.5 second delay (50 * 10ms)
            }
        } else if(currentDistance < 5) {
            if (timerCounter >= nextToggleTime) {
                DL_GPIO_togglePins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
                uint8_t TXmsg[] = "Caution: distance less than 5 meters";
                addData(TXmsg, sizeof(TXmsg) - 1);
                nextToggleTime = timerCounter + 100; // 1 second delay (100 * 10ms)
            }
        } else if (currentDistance < 10) {
            if (timerCounter >= nextToggleTime) {
                DL_GPIO_togglePins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
                uint8_t TXmsg[] = "Caution: distance less than 10 meters";
                addData(TXmsg, sizeof(TXmsg) - 1);
                nextToggleTime = timerCounter + 200; // 2 seconds delay (200 * 10ms)
            }
        }

        distanceIndex = (distanceIndex + 1) % 10; // Cycle through distanceArray
        flag = FALSE;
    }
}

