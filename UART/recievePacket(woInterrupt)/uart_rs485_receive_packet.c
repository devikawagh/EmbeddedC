#include "ti_msp_dl_config.h"

/*
 * Configure the internal loopback mode.
 * Note that data received on the UART RXD IO pin will be ignored when
 * loopback is enabled.
 */
#define ENABLE_LOOPBACK_MODE true

/*
 * Number of bytes for UART packet size
 * The packet will be transmitted by the UART.
 * This example uses FIFOs with polling, and the maximum FIFO size is 4.
 * Refer to interrupt examples to handle larger packets.
 */
#define UART_PACKET_SIZE (6)

/* Data received from UART */
uint8_t rxPacket[UART_PACKET_SIZE];

int main(void)
{
    SYSCFG_DL_init();

    while (1) {
        for (uint8_t i = 0; i < UART_PACKET_SIZE; i++) {
            rxPacket[i] = DL_UART_receiveDataBlocking(UART_0_INST);
        }
        for (uint8_t i = 0; i < UART_PACKET_SIZE; i++) {
            printf("%c ", rxPacket[i]);
    //        rxPacket[i] = DL_UART_receiveDataBlocking(UART_0_INST);
        }
        printf("\n");
    }
}
