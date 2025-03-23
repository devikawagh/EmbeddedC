#include "ti_msp_dl_config.h"
#include "stdio.h"

int main(void) {
    SYSCFG_DL_init();

    while (1) {
        //Cheching if S1 is pressed
        if(DL_GPIO_readPins(GPIO_GRP_0_SWITCH_PA18_PORT, GPIO_GRP_0_SWITCH_PA18_PIN)) {
            DL_GPIO_setPins(GPIO_GRP_0_LED_PB27_PORT, GPIO_GRP_0_LED_PB27_PIN);  // LED1 ON when S1 pressed
        } else {
            DL_GPIO_clearPins(GPIO_GRP_0_LED_PB27_PORT, GPIO_GRP_0_LED_PB27_PIN); // LED1 OFF when S1 released
        }

        //Checking if S2 is pressed
        if(DL_GPIO_readPins(GPIO_GRP_0_SWITCH_PB21_PORT,  GPIO_GRP_0_SWITCH_PB21_PIN)) {
            DL_GPIO_setPins(GPIO_GRP_0_LED_PB26_PORT, GPIO_GRP_0_LED_PB26_PIN);  // LED2 ON when S2 pressed
        } else {
            DL_GPIO_clearPins(GPIO_GRP_0_LED_PB26_PORT, GPIO_GRP_0_LED_PB26_PIN); // LED2 OFF when S2 released
        }
    }
}
