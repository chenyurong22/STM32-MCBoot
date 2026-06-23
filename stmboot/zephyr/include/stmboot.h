#pragma once
#include <stdint.h>

int stmboot_confirm_image(void);
int stmboot_request_upgrade(void);
int stmboot_get_active_slot(void);
void stmboot_get_image_version(uint8_t *major, uint8_t *minor);
uint32_t stmboot_get_boot_count(void);
uint32_t stmboot_get_image_state(void);