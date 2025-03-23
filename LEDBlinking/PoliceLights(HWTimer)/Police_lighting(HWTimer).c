include "ti_msp_dl_config.h"

volatile uint32_t timerCounter = 0;

#define LED1_ON (50)
#define LED2_ON (50)

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerA_startCounter(TIMER_0_INST);

    while (1) {
        if(timerCounter % (LED1_ON + LED2_ON) < LED1_ON) {
            DL_GPIO_setPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB22_PIN);
            DL_GPIO_clearPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
        }
        else
        {
            DL_GPIO_clearPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB22_PIN);
            DL_GPIO_setPins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB26_PIN);
        }
    }
}

void TIMER_0_INST_IRQHandler(void) {
    timerCounter++;
}
