0x08000000  Bootloader   24 KB → 0x08006000
0x08006000  Slot A       48 KB → 0x08012000
0x08012000  Slot B       48 KB → 0x0801E000
0x0801E000  Metadata      8 KB → 0x08020000

debug build takes up 18.5KB:
[build] Memory region         Used Size  Region Size  %age Used
[build]              RAM:        3296 B        20 KB     16.09%
[build]            FLASH:       18488 B        24 KB     75.23%

Packet structure from python to mcu in little endian:
0xAA | 0xBB | SIZE (4 bytes LE) | DATA (N bytes) | Hardware CRC32 (4 bytes LE) |
