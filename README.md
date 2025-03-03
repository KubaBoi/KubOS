# KubOS

Program for LilyGo TWatch 2020 v3. System can manage multiple applications as c++ classes. 

Via managers can applications operate IO of watch.

## Description

- config
  - headers for configuration
- core
  - main parts of system
- managers
  - managers of IO
- apps
  - applications

## Setup

https://wellys.com/posts/esp32_cli/

```
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

arduino-cli core update-index --additional-urls https://dl.espressif.com/dl/package_esp32_index.json

arduino-cli config init
```

config file: `~/.arduino15/arduino-cli.yaml`

```
board_manager:
  additional_urls:
    - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

```
arduino-cli core install esp32:esp32

arduino-cli board list

arduino-cli compile --fqbn esp32:esp32:nodemcu-32s KubOS.ino

arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:nodemcu-32s KubOS.ino
```
