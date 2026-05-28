#include "metadata.h"

PAL_Flash_StatusTypeDef Metadata_Load(Metadata *m) {
    Metadata *stored = (Metadata *)METADATA_ADDRESS; // casting to Treat the bytes at memory address METADATA_ADDRESS as if they were a Metadata struct
    if (stored->magic == METADATA_MAGIC) {
        *m = *stored; // valid metadata found
        return FLASH_OK;
    } else { // first boot ever, set defaults
        m->magic = METADATA_MAGIC;
        m->SLOTA_LATEST = true;
        m->bootcount = 0;
        m->runtime_fault_count = 0;
        m->FW_VER_MAJOR = 0x0;
        m->FW_VER_MINOR = 0x0;
        m->image_state = IMG_STATE_NONE;
        return Metadata_Save(m);
    }
}

PAL_Flash_StatusTypeDef Metadata_Save(Metadata *m) {
    if(PAL_Flash_ErasePage(METADATA_ADDRESS) != FLASH_OK) {
        return FLASH_ERR_ERASE;
    }
    if(PAL_Flash_Write(METADATA_ADDRESS, (const uint8_t *)m, sizeof(Metadata)) != FLASH_OK) {
        return FLASH_ERR_WRITE;
    }
}

PAL_Flash_StatusTypeDef Metadata_IncrementBootCount(Metadata *m) {
    m->bootcount++;
    return Metadata_Save(m);
}

PAL_Flash_StatusTypeDef Metadata_UpdateAfterRecieve(Metadata *m, bool SLOTA_LATEST) {
    m->SLOTA_LATEST = SLOTA_LATEST ? 0 : 1; 
    m->bootcount = 0;
    m->image_state = IMG_STATE_PENDING; // not confirmed, will be confirmed by app
    return Metadata_Save(m);
}