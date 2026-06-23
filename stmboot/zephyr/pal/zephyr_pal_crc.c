#ifdef __ZEPHYR__

#include "pal_crc.h"

/* WARNING: this must match the polynomial/config used by the bare-metal
 * STM32 hardware CRC peripheral in platform/stm32/f1/pal/pal_crc.c exactly.
 * STM32's CRC peripheral default is poly 0x04C11DB7, init 0xFFFFFFFF,
 * input NOT reflected, output NOT reflected, no final XOR.
 * CONFIRM against the real pal_crc.c before trusting this.
 */

static uint32_t crc_state;

void PAL_CRC_Reset(void) {
    crc_state = 0xFFFFFFFFU;
}

uint32_t PAL_CRC_Accumulate(uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        crc_state ^= ((uint32_t)data[i]) << 24;
        for (int b = 0; b < 8; b++) {
            crc_state = (crc_state & 0x80000000U)
                      ? (crc_state << 1) ^ 0x04C11DB7U
                      : (crc_state << 1);
        }
    }
    return crc_state;
}

uint32_t PAL_CRC_GetResult(void) {
    return crc_state;
}

#endif