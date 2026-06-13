/**
 * @file todos.h
 * @brief file to search for todos in issues, features and YTI (ideas yet to implement)
 * @date 2026-06-05
 */

/* Features */
/** @todo Make modules removable/configurable: CRC32, AES128 Encryption, SHA256 Hashing, EDCSA, and EDCSA Curve Selection */
/** @todo implement PAL functions needed before jumping to app */
/** @todo TEST IWDG AND COMMIT then test rollback*/
/** @todo INCLUDES.H ADDITION */

/* Learning */
/** @todo CALCULATE ACCUMULATE ALGO */

/* YTI */
/** @todo Shell */
/** @todo Settings KV store and Logging framework */
/** @todo Diagnostics */
/** @todo Zephyr Integration for Bootloader + App */
/** @todo Github Actions: Tests in gtest, static unit cppcheck clang-tidy */
/** @todo ESP32 OTA updates */

// other: 
// Power loss during CRC/ECDSA verification
// Metadata - crc tampering?
// Flash wear resistance (Wear levelling)
// Security:
// 	◦	Implement AES, SHA256 and ECC by self
// 	◦	Cryptographic ownership transfer by rotating root keys
// Immutable Trust Chain
// 	◦	Two-stage boot (OEMiRoT + uRoT equivalent) - before this I need implement a tiny(er) SHA256 and EDCSA verification
// 	◦	Bootloader self-update (wolfBoot equivalent)
// 	◦	Memory Protection Unit (MPU) integration
// Rollback: Delta History
// Self-Documenting Hardware
// 	◦	@ boot, the device exposes itself as a USB drive containing schematics, datasheets, API docs, service manuals