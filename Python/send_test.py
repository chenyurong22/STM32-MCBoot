import serial
import struct
import sys

PORT     = "/dev/tty.usbmodem103"
BAUDRATE = 115200
CHUNK_SIZE = 1024

def compute_crc32_stm32(data: bytes) -> int:
    crc = 0xFFFFFFFF
    remainder = len(data) % 4
    if remainder:
        data = data + b'\xFF' * (4 - remainder)
    for i in range(0, len(data), 4):
        word = struct.unpack(">I", data[i:i+4])[0]
        crc ^= word
        for _ in range(32):
            if crc & 0x80000000:
                crc = ((crc << 1) ^ 0x04C11DB7) & 0xFFFFFFFF
            else:
                crc = (crc << 1) & 0xFFFFFFFF
    return crc

def wait_response(ser) -> str:
    line = ser.readline().decode(errors="replace").strip()
    print(f"  MCU: {line}")
    return line

def expect_ack(ser, context: str):
    response = wait_response(ser)
    if response != "ACK":
        print(f"NACK or unexpected response at: {context}")
        sys.exit(1)

def send_firmware(port: str, data: bytes):
    crc = compute_crc32_stm32(data)

    print(f"Firmware : {len(data)} bytes")
    print(f"CRC32    : 0x{crc:08X}")

    with serial.Serial(port, BAUDRATE, timeout=10000) as ser:

        # wait for READY — ignore debug lines
        print("\nWaiting for READY...")
        while True:
            line = ser.readline().decode(errors="replace").strip()
            print(f"  MCU: {line}")
            if line == "READY":
                break

        # # START_0
        # print("Sending START_0 (0xAA)...")
        # ser.write(bytes([0xAA]))
        # expect_ack(ser, "START_0")

        # # START_1
        # print("Sending START_1 (0xBB)...")
        # ser.write(bytes([0xBB]))
        # expect_ack(ser, "START_1")

        # # SIZE
        # print(f"Sending SIZE ({len(data)} bytes)...")
        # ser.write(struct.pack("<I", len(data)))
        # ser.flush()
        # expect_ack(ser, "SIZE")

        print(f"Sending header...")
        header = b'\xAA\xBB' + struct.pack("<I", len(data))
        ser.write(header)
        expect_ack(ser, "HEADER")

        # DATA — one chunk at a time, wait for ACK after each
        print("Sending DATA...")
        ser.write(data)
        expect_ack(ser, "DATA")
        total = len(data)
        offset = 0
        chunk_num = 0
        while offset < total:
            chunk = data[offset:offset + CHUNK_SIZE]
            ser.write(chunk)
            expect_ack(ser, f"chunk {chunk_num}")
            offset += len(chunk)
            chunk_num += 1
            print(f"  Progress: {offset}/{total} bytes", end="\r")
        print()

        # CRC
        print(f"Sending CRC (0x{crc:08X})...")
        ser.write(struct.pack("<I", crc))
        expect_ack(ser, "CRC")

        # final result from main.c (OK or FAIL)
        print("Waiting for final result...")
        result = wait_response(ser)
        if result == "OK":
            print("\nSuccess — firmware written to flash")
        else:
            print(f"\nFailed — MCU replied: {result}")
            sys.exit(1)

if __name__ == "__main__":
    # swap for: data = open("application.bin", "rb").read()
    data = bytes([0xAA, 0xBB, 0xCC, 0xDD] * 256)  # 1KB test pattern
    send_firmware(PORT, data)