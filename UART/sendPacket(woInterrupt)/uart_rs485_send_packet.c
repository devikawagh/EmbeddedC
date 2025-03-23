#include "ti_msp_dl_config.h"

/* Number of bytes for UART packet size, the maximum FIFO size is 4 */
#define UART_PACKET_SIZE (4)

/* Delay for 5ms to ensure UART TX is idle before starting transmission */
#define UART_TX_DELAY (160000)

/* Data for UART to transmit */
uint8_t gTxPacket[UART_PACKET_SIZE] = {'M', 'S', 'P', '!'};

int main(void){
    SYSCFG_DL_init();

    /* Transmit data, set DE high before */
    DL_GPIO_setPins(GPIO_DE_TX_PORT, GPIO_DE_TX_TRANSMITTER_PIN);
    DL_UART_Main_fillTXFIFO(UART_0_INST, &gTxPacket[0], UART_PACKET_SIZE);

    /*
     * Wait until all bytes have been transmitted and the TX FIFO
     * is empty
     */
    while (DL_UART_isBusy(UART_0_INST))
        ;

    /* Set DE low after transmission */
    DL_GPIO_clearPins(GPIO_DE_TX_PORT, GPIO_DE_TX_TRANSMITTER_PIN);

    /* If write successful, toggle LED */
    while (1) {
        DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);
        delay_cycles(5000000);
    }
}
