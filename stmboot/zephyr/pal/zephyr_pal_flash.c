#ifdef __ZEPHYR__

#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include "pal_flash.h"

#define FLASH_PAGE_SIZE_BL 1024U

static const struct device *flash_dev =
    DEVICE_DT_GET(DT_CHOSEN(zephyr_flash_controller));

PAL_Flash_StatusTypeDef PAL_Flash_ErasePage(uint32_t page_address) {
    int rc = flash_erase(flash_dev, page_address, FLASH_PAGE_SIZE_BL);
    return (rc == 0) ? FLASH_OK : FLASH_ERR_ERASE;
}

PAL_Flash_StatusTypeDef PAL_Flash_EraseSlot(uint32_t slot_start, uint32_t num_pages) {
    for (uint32_t i = 0; i < num_pages; i++) {
        PAL_Flash_StatusTypeDef rc =
            PAL_Flash_ErasePage(slot_start + (i * FLASH_PAGE_SIZE_BL));
        if (rc != FLASH_OK) return rc;
    }
    return FLASH_OK;
}

PAL_Flash_StatusTypeDef PAL_Flash_Write(uint32_t dest, const uint8_t *src, size_t len) {
    int rc = flash_write(flash_dev, dest, src, len);
    return (rc == 0) ? FLASH_OK : FLASH_ERR_WRITE;
}

#endif