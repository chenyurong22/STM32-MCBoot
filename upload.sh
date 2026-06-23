#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd "$SCRIPT_DIR/scripts"

python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt

python3 send_test_ab.py \
    --port /dev/tty.usbmodem103 \
    --baudrate 115200
