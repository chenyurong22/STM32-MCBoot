#ifndef METADATA_H
#define METADATA_H

#include <stdint.h>
#include <stdbool.h>
#include "Middleware/flash.h"

#define METADATA_ADDRESS 0x0801E000
#define METADATA_MAGIC 0xDEADBEEFU // start of metadata
#define BOOT_COUNT_MAX 3U // rollback feature
#define RUNTIME_BOOT_COUNT_MAX 10U

typedef enum { // has vals alr def
    IMG_STATE_NONE = 0x0, // no fw erased flash
    IMG_STATE_PENDING = 0x1, // fw recieved, not booted
    IMG_STATE_TRIAL = 0x2, // booted not confirmed
    IMG_STATE_HEALTHY = 0x3, 
    IMG_STATE_REVERTED = 0x4, // BOOT_COUNT_MAX exceeded, rolled back
} ImageState;

typedef struct __attribute__((packed)) {
    uint32_t magic;
    uint32_t SLOTA_LATEST;
    uint32_t bootcount; // increment every boot, clear by successful firmware
    uint8_t  FW_VER_MAJOR;
    uint8_t  FW_VER_MINOR;
    uint16_t _pad;
    uint32_t image_state;
    uint32_t runtime_fault_count;
} Metadata;
// _Static_assert(sizeof(Metadata) == 16, "Metadata struct size not 16b"); // todo is failing

Flash_Status Metadata_Load(Metadata *m); // reads from flash, writes defaults
Flash_Status Metadata_Save(Metadata *m); // erases metadata page & writes new
Flash_Status Metadata_IncrementBootCount(Metadata *m);
Flash_Status Metadata_UpdateAfterRecieve(Metadata *m, bool SLOTA_LATEST);

#endif