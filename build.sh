python build.py
echo "Compilation..."
if arduino-cli compile --fqbn esp32:esp32:nodemcu-32s KubOS.ino
then
    echo "Uploading..."
    arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:nodemcu-32s KubOS.ino;
else
    echo "Compilation error"
fi
python clear.py