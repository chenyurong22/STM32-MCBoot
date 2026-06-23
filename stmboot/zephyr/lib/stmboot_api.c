#include <stmboot.h>
#include "metadata.h"

int stmboot_confirm_image(void) {
    Metadata m;
    Metadata_Load(&m);
    if (m.image_state != IMG_STATE_TRIAL) return -1;
    m.image_state = IMG_STATE_HEALTHY;
    m.bootcount   = 0;
    Metadata_Save(&m);
    return 0;
}

int stmboot_request_upgrade(void) {
    Metadata m;
    Metadata_Load(&m);
    m.fwu_state = FWU_STATE_START;
    Metadata_Save(&m);
    return 0;
}

int stmboot_get_active_slot(void) {
    Metadata m;
    Metadata_Load(&m);
    return m.SLOTA_LATEST ? 0 : 1;
}

void stmboot_get_image_version(uint8_t *major, uint8_t *minor) {
    Metadata m;
    Metadata_Load(&m);
    *major = m.FW_VER_MAJOR;
    *minor = m.FW_VER_MINOR;
}

uint32_t stmboot_get_boot_count(void) {
    Metadata m;
    Metadata_Load(&m);
    return m.bootcount;
}

uint32_t stmboot_get_image_state(void) {
    Metadata m;
    Metadata_Load(&m);
    return m.image_state;
}