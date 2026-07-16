import serial
import time
import svgwrite as draw
from difflib import SequenceMatcher
import cv2

def display_imgs(svg1_path, svg2_path, percent):
        # Load the background and foreground images
    bg = cv2.imread(svg2_path)
    fg = cv2.imread(svg1_path)

    # Both images must have identical dimensions; resize fg to match bg if needed
    fg_resized = cv2.resize(fg, (bg.shape[1], bg.shape[0]))

    # Blend the images: final = (bg * 0.7) + (fg * 0.3) + 0
    # Adjust the weights (0.7 and 0.3) to change individual opacity
    blended_img = cv2.addWeighted(bg, 0.7, fg_resized, 0.3, 0)

    text = percent
    coordinates = (50, 100)  # (X, Y) position of the bottom-left corner of the text
    font = cv2.FONT_HERSHEY_SIMPLEX  # Font type
    font_scale = 1.0  # Font size multiplier
    color = (0, 255, 0)  # Text color in BGR format (Green)
    thickness = 2  # Thickness of the stroke in pixels

    # 3. Add text to the image
    cv2.putText(
        blended_img, text, coordinates, font, font_scale, color, thickness, cv2.LINE_AA
    )

    # Display the combined result in a single window
    cv2.imshow('Overlaid Images', blended_img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def update_svg(data): 
    # Example: Draw a simple line based on the received data
    # Assuming data is a string of coordinates like "x1,y1,x2,y2
    coords = list(map(int, data.split(',')))
    if len(coords) == 4:
        dwg.add(dwg.line(start=(coords[0], coords[1]), end=(coords[2], coords[3]), stroke=draw.rgb(10, 10, 16, '%')))
    # Save the SVG file
    dwg.save()

    percent = compare_svgs('output/output.svg', 'reference/reference.svg')  # Compare with a reference SVG
    display_imgs('output/output.svg', 'reference/reference.svg', percent)  # Display the image after updating the SVG

def compare_svgs(svg1_path, svg2_path):
    with open(svg1_path, 'r') as file1, open(svg2_path, 'r') as file2:
        svg1_content = file1.read()
        svg2_content = file2.read()
        
        # Use SequenceMatcher to compare the two SVG contents
        similarity_ratio = SequenceMatcher(None, svg1_content, svg2_content).ratio()
        
        print(f"Similarity ratio between {svg1_path} and {svg2_path}: {similarity_ratio:.2f}")
        return f"{similarity_ratio:.2f}"


# Configure the serial port
# Replace 'COM3' with your actual port (e.g., '/dev/ttyUSB0' on Linux/Mac)
SERIAL_PORT = 'COM3' 
BAUD_RATE = 115200

try:
    # Open the serial port with a 1-second timeout
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to ESP32 on {SERIAL_PORT}")
    
    data = []  # List to store received data
    dwg = draw.Drawing('output/output.svg', profile='tiny') # create .svg file

    # Brief pause to allow the connection to settle
    time.sleep(2) 

    while True:
        if ser.in_waiting > 0:
            # Read a line of raw bytes from the ESP32
            raw_data = ser.readline()
            
            # Decode bytes to a string and strip whitespace/newlines
            decoded_data = raw_data.decode('utf-8').rstrip()
            
            print(f"Received: {decoded_data}")

            data.append(decoded_data)  # Store the received data for later use
            
except serial.SerialException as e:
    print(f"Error connecting to serial port: {e}")
except KeyboardInterrupt:
    print("\nDisconnecting...")
finally:
    # Always close the port when finishing
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Serial port closed.")

    update_svg(decoded_data)  # Update the SVG with the latest data
    display_imgs('output/output.svg', 'reference/reference.svg', "0.00")  # Initial display with 0% similarity