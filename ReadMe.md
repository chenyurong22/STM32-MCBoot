## Flash Memory Layout
Bootloader   0x08000000  24 KB  → 0x08006000  
Slot A       0x08006000  48 KB  → 0x08012000  
Slot B       0x08012000  48 KB  → 0x0801E000  
Metadata     0x0801E000   8 KB  → 0x08020000  

---

## Debug Build Memory Usage

[build] Memory region         Used Size  Region Size  %age Used  
[build]              RAM:        3296 B        20 KB     16.09%  
[build]            FLASH:       18488 B        24 KB     75.23%  

---

## UART Packet structure from python to mcu in little endian:

0xAA | 0xBB | SIZE (4 bytes LE) | DATA (N bytes) | CRC32 (4 bytes LE)
