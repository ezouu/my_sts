#!/usr/bin/env python3
import os
import sys
import time
import serial.tools.list_ports

# Add the current directory to the Python path
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from stm32_utils import STM32Utils

def test_led_commands():
    # Use the direct USB serial port
    port = '/dev/cu.usbserial-FTDO6V6D'
    print(f"Attempting to connect to {port}")
    
    # Initialize with the USB serial port
    stm32 = STM32Utils(port=port)
    
    print("\nAttempting to connect to STM32 board...")
    if stm32.connect():
        print("\nConnection successful! Testing LED commands...")
        
        # Test LED commands
        commands = [
            "ledr 1",  # Turn on red LED
            "ledr 0",  # Turn off red LED
            "ledg 1",  # Turn on green LED
            "ledg 0"   # Turn off green LED
        ]
        
        for cmd in commands:
            print(f"\nSending command: {cmd}")
            response = stm32.send_command(cmd)
            print(f"Response: {response}")
            time.sleep(1)  # Wait a second between commands to see the LED changes
        
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
    test_led_commands() 