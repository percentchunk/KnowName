import serial
import time

# Configure the serial port
# Replace 'COM3' with your actual port (e.g., '/dev/ttyUSB0' on Linux/Mac)
SERIAL_PORT = 'COM3' 
BAUD_RATE = 115200

try:
    # Open the serial port with a 1-second timeout
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to ESP32 on {SERIAL_PORT}")
    
    # Brief pause to allow the connection to settle
    time.sleep(2) 

    while True:
        if ser.in_waiting > 0:
            # Read a line of raw bytes from the ESP32
            raw_data = ser.readline()
            
            # Decode bytes to a string and strip whitespace/newlines
            decoded_data = raw_data.decode('utf-8').rstrip()
            
            print(f"Received: {decoded_data}")
            
except serial.SerialException as e:
    print(f"Error connecting to serial port: {e}")
except KeyboardInterrupt:
    print("\nDisconnecting...")
finally:
    # Always close the port when finishing
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Serial port closed.")
