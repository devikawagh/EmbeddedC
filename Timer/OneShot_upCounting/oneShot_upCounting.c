#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerA_startCounter(TIMER_0_INST);

//    while (1) {
//        //__WFI();
//    }
}

void TIMER_0_INST_IRQHandler(void){
    DL_GPIO_togglePins(GPIO_GRP_0_PORT,GPIO_GRP_0_led_PIN);
    DL_TimerA_stopCounter(TIMER_0_INST);

    //TIMER_0_INST->COUNTERREGS.CTR = TIMER_0_INST_LOAD_VALUE;
    DL_TimerA_startCounter(TIMER_0_INST);

}
