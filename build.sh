INO_NAME="KubOS.ino"
PORT="/dev/ttyACM0"

python build.py
echo "Compilation..."
if arduino-cli compile --fqbn esp32:esp32:nodemcu-32s $INO_NAME
then
    echo "Uploading..."
    arduino-cli upload -p $PORT --fqbn esp32:esp32:nodemcu-32s $INO_NAME
else
    echo "Compilation error"
fi
python clear.py
#arduino-cli monitor -p $PORT -c baudrate=115200