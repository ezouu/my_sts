import serial
import time
import sys

def send_command(ser, command):
    """Send a command to the STM32 board and wait for response"""
    print(f"Sending command: {command}")
    
    # Clear any existing data
    ser.reset_input_buffer()
    ser.reset_output_buffer()
    
    # Send command with newline
    ser.write(f"{command}\r\n".encode())
    print("Command sent, waiting for response...")
    
    # Read response until we get a prompt or timeout
    response = ""
    start_time = time.time()
    timeout = 5  # 5 second timeout
    
    while time.time() - start_time < timeout:
        if ser.in_waiting:
            char = ser.read(1).decode()
            response += char
            print(f"Received: {char}", end='', flush=True)
            # Look for the complete response pattern
            if "Captured command:" in response and "STS>" in response:
                break
        time.sleep(0.1)
    
    if time.time() - start_time >= timeout:
        print("\nTimeout waiting for response!")
        return "TIMEOUT"
        
    return response.strip()

def test_red_led(ser):
    """Test the red LED functionality"""
    print("\nTesting Red LED...")
    
    # Turn LED ON
    print("Turning Red LED ON...")
    response = send_command(ser, "ledr 1")
    print(f"Response: {response}")
    time.sleep(1)
    
    # Turn LED OFF
    print("Turning Red LED OFF...")
    response = send_command(ser, "ledr 0")
    print(f"Response: {response}")
    time.sleep(1)

def test_green_led(ser):
    """Test the green LED functionality"""
    print("\nTesting Green LED...")
    
    # Turn LED ON
    print("Turning Green LED ON...")
    response = send_command(ser, "ledg 1")
    print(f"Response: {response}")
    time.sleep(1)
    
    # Turn LED OFF
    print("Turning Green LED OFF...")
    response = send_command(ser, "ledg 0")
    print(f"Response: {response}")
    time.sleep(1)

def main():
    # Configure serial connection
    try:
        print("Opening serial port...")
        ser = serial.Serial(
            port='/dev/cu.usbserial-FTDO6V6D',  # Using FTDI serial port
            baudrate=115200,
            timeout=1,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE
        )
        print("Serial port opened successfully")
        
        # Set DTR and RTS lines
        ser.setDTR(True)
        ser.setRTS(True)
        
    except serial.SerialException as e:
        print(f"Error: Could not open serial port: {e}")
        sys.exit(1)

    try:
        print("Starting LED test sequence...")
        
        # Wait for initial prompt
        print("Waiting for board to initialize...")
        time.sleep(2)  # Give the board more time to initialize
        
        # Clear any initial data
        while ser.in_waiting:
            data = ser.read(ser.in_waiting)
            print(f"Cleared initial data: {data}")
        
        # Test red LED
        test_red_led(ser)
        
        # Test green LED
        test_green_led(ser)
        
        print("\nLED test sequence completed!")
        
    except KeyboardInterrupt:
        print("\nTest interrupted by user")
    except Exception as e:
        print(f"\nError during test: {e}")
    finally:
        print("Closing serial port...")
        ser.close()
        print("Serial port closed")

if __name__ == "__main__":
    main() 