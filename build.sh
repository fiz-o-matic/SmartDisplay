#!/bin/bash

pio_ini="platformio.ini"



strings=(
    FW_BETA
    FW_GAMMA
    DEBUG
    FW_ALPHA_OLED
    FW_ALPHA_LCD
)

for env in "${strings[@]}"; do
    echo "$env"
    rm build/$env.hex
    pio run -e $env -t clean
    pio run -e $env -t build
    cp build/$env/firmware.hex build/$env.hex
done


