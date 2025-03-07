#!/usr/bin/env python3
import os
import sys
import time
import serial.tools.list_ports

# Add the current directory to the Python path
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from stm32_utils import STM32Utils

def test_i2c_operations():
    """Test I2C read and write operations"""
    print("\nTesting I2C Operations...")
    
    # Test writei2c command
    print("\nTesting writei2c command...")
    response = stm32.send_command("writei2c 1 0x20 0x00")  # Example: Write to IOexpander 1
    print(f"Response: {response}")
    
    # Test displayi2c command
    print("\nTesting displayi2c command...")
    response = stm32.send_command("displayi2c 1 0x20")  # Example: Read from IOexpander 1
    print(f"Response: {response}")
    
    # Test writei2cio2 command
    print("\nTesting writei2cio2 command...")
    response = stm32.send_command("writei2cio2 1 0x20 0x00")  # Example: Write and display from IOexpander 1
    print(f"Response: {response}")

def test_joystick():
    """Test joystick functionality"""
    print("\nTesting Joystick...")
    
    # Initialize joystick
    print("Initializing joystick...")
    response = stm32.send_command("joystick")
    print(f"Response: {response}")
    
    # Monitor joystick input for 5 seconds
    print("\nMonitoring joystick input for 5 seconds...")
    print("Move the joystick in different directions")
    start_time = time.time()
    while time.time() - start_time < 5:
        response = stm32.send_command("joystick")
        if response and "STS>" not in response:
            print(f"Joystick position: {response}")
        time.sleep(0.1)

def test_systick():
    """Test systick timer functionality"""
    print("\nTesting Systick Timer...")
    
    # Initialize and start systick
    print("Initializing systick...")
    response = stm32.send_command("systick")
    print(f"Response: {response}")
    
    # Monitor systick countdown for 5 seconds
    print("\nMonitoring systick countdown for 5 seconds...")
    start_time = time.time()
    while time.time() - start_time < 5:
        response = stm32.send_command("systick")
        if response and "STS>" not in response:
            print(f"Systick value: {response}")
        time.sleep(0.1)

def test_memory_operations():
    """Test memory display and edit operations"""
    print("\nTesting Memory Operations...")
    
    # Test display command
    print("\nTesting display command...")
    response = stm32.send_command("display 0x20000000")  # Example: Display memory at address 0x20000000
    print(f"Response: {response}")
    
    # Test edit command
    print("\nTesting edit command...")
    response = stm32.send_command("edit 0x20000000 0x12345678")  # Example: Edit memory at address 0x20000000
    print(f"Response: {response}")

def main():
    # Use the direct USB serial port
    port = '/dev/cu.usbserial-FTDO6V6D'
    print(f"Attempting to connect to {port}")
    
    # Initialize with the USB serial port
    stm32 = STM32Utils(port=port)
    
    print("\nAttempting to connect to STM32 board...")
    if stm32.connect():
        print("\nConnection successful! Starting advanced tests...")
        
        try:
            # Run all tests
            test_i2c_operations()
            time.sleep(1)  # Wait between tests
            
            test_joystick()
            time.sleep(1)
            
            test_systick()
            time.sleep(1)
            
            test_memory_operations()
            
        except KeyboardInterrupt:
            print("\nTests interrupted by user")
        finally:
            # Clean up
            stm32.disconnect()
    else:
        print("\nFailed to connect to the board. Please check:")
        print("1. Is the USB serial device properly connected?")
        print("2. Is the STM32 board connected to the USB serial device?")
        print("3. Are the TX/RX connections correct?")
        print("4. Do you have permission to access the port?")
        print("\nYou can check the connection using:")
        print("ls -l /dev/cu.*")

if __name__ == "__main__":
    # Change to the script's directory
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    main() 