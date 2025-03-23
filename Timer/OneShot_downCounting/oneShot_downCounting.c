

#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(TIMER_INST_INT_IRQN);
    DL_TimerA_startCounter(TIMER_INST);
    while (1) {
        __WFI();
    }

}

void TIMER_INST_IRQHandler(void) {
    DL_GPIO_togglePins(GPIO_GRP_0_PORT, GPIO_GRP_0_LED_PB27_PIN);
    DL_TimerA_stopCounter(TIMER_INST);
    DL_TimerA_startCounter(TIMER_INST);
}
