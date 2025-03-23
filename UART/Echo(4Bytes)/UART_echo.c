//echo
#include "ti_msp_dl_config.h"
#include "stdio.h"


volatile uint8_t result = 0;

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    while (1) {
        __WFI();
    }
}

void UART_0_INST_IRQHandler(void) {
    switch(DL_UART_getPendingInterrupt(UART_0_INST)) {
    case DL_UART_IIDX_RX:
        result = DL_UART_receiveData(UART_0_INST);
        DL_UART_transmitData(UART_0_INST, result);

        break;
    default:
        break;
    }
}
