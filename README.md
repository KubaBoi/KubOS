# KubOS

Program for LilyGo TWatch 2020 v3. System can manage multiple applications as c++ classes. 

Via managers can applications operate IO of watch.

## Setup

https://wellys.com/posts/esp32_cli/

`arduino-cli core update-index https://dl.espressif.com/dl/package_esp32_index.json`

`arduino-cli config init`

```
board_manager:
  additional_urls:
    - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

`arduino-cli core install esp32:esp32`

`arduino-cli board list`

```
arduino-cli compile --fqbn esp32:esp32:nodemcu-32s KubOS.ino

arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:nodemcu-32s KubOS.ino
```
