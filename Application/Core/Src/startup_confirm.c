#include "startup_confirm.h"
#include "metadata.h"
#include "stm32f1xx_hal.h"

void StartupConfirm(uint8_t APP_VERSION_MAJOR, uint8_t APP_VERSION_MINOR) {
    // signal to bootloader that this boot was successful
    // write 0 to boot_count in metadata
    // HAL_IWDG_Refresh(&hiwdg);
    Metadata meta;
    Metadata_Load(&meta);
    if (meta.image_state == IMG_STATE_TRIAL) {
        meta.image_state = IMG_STATE_HEALTHY;
        meta.bootcount = 0;
        meta.FW_VER_MAJOR = APP_VERSION_MAJOR; // todo important don't know if I need it
        meta.FW_VER_MINOR = APP_VERSION_MINOR; 
        Metadata_Save(&meta);
    }
}
