#pragma once
#ifdef __ZEPHYR__

#include <zephyr/devicetree.h>
#include <zephyr/storage/flash_map.h>

// Pull slot addresses from devicetree instead of board_config.h
#define SLOTA_START_ADDRESS FIXED_PARTITION_OFFSET(stmboot_slot0_partition)
#define SLOTB_START_ADDRESS FIXED_PARTITION_OFFSET(stmboot_slot1_partition)
#define METADATA_ADDRESS_SLOT1         FIXED_PARTITION_OFFSET(metadata_slot0_partition)
#define METADATA_ADDRESS_SLOT2        FIXED_PARTITION_OFFSET(metadata_slot1_partition)
#define SLOT_NUM_PAGES       (CONFIG_STMBOOT_SLOT_SIZE_KB * 1024 / FLASH_PAGE_SIZE_BL)
#define FLASH_PAGE_SIZE_BL   1024U

#endif