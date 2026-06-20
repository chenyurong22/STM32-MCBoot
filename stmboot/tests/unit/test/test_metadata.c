#include "unity.h"
#include "metadata.h"
#include "mock_pal_crc.h"
#include "mock_pal_flash.h"   // auto-generated from platform/pal/pal_flash.h

void setUp(void) {}
void tearDown(void) {}

// helper: simulate flash containing valid metadata with given magic/crc
static Metadata fake_flash_metadata;
int Rollback_Check(Metadata *m) {
  if (m->bootcount <= BOOT_COUNT_MAX || (m->runtime_fault_count <= RUNTIME_BOOT_COUNT_MAX)) return 0;
  m->SLOTA_LATEST = !m->SLOTA_LATEST; // flip to previous slot 
  m->bootcount = 0;
  m->image_state = IMG_STATE_REVERTED;
  Metadata_Save(m); 
  return 1;
}

void test_Metadata_test(void) {
    Metadata m;
    // placeholder test
}