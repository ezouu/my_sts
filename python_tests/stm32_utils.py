#!/usr/bin/env python3
import serial
import time
import os
import subprocess
from typing import Optional, List, Dict
import json
import serial.tools.list_ports

class STM32Utils:
    def __init__(self, port: str = None, baudrate: int = 115200):
        """Initialize STM32 utilities with serial port configuration."""
        self.port = port
        self.baudrate = baudrate
        self.serial = None
        self.connected = False

    def connect(self) -> bool:
        """Connect to the STM32 board via serial."""
        if not self.port:
            print("Error: No port specified")
            return False

        try:
            # Print available ports for debugging
            print("\nAvailable ports:")
            for port in serial.tools.list_ports.comports():
                print(f"  {port.device} - {port.description}")

            print(f"\nAttempting to connect to {self.port}")
            
            # Check if port exists
            if not os.path.exists(self.port):
                print(f"Error: Port {self.port} does not exist")
                return False
                
            # Check port permissions
            try:
                with open(self.port, 'rb') as f:
                    pass
            except PermissionError:
                print(f"Error: Permission denied accessing {self.port}")
                print("Try running with sudo or check port permissions")
                return False

            self.serial = serial.Serial(
                port=self.port,
                baudrate=self.baudrate,
                timeout=1,
                bytesize=serial.EIGHTBITS,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                xonxoff=False,  # Disable software flow control
                rtscts=False,   # Disable hardware flow control
                dsrdtr=False    # Disable hardware flow control
            )
            
            # Flush any existing data
            self.serial.flushInput()
            self.serial.flushOutput()
            
            # Set DTR and RTS lines
            self.serial.setDTR(True)
            self.serial.setRTS(True)
            
            self.connected = True
            print(f"Connected to {self.port}")
            return True
        except serial.SerialException as e:
            print(f"Failed to connect: {e}")
            print("\nTroubleshooting tips:")
            print("1. Check if the port exists: ls -l /dev/cu.*")
            print("2. Check port permissions: ls -l /dev/cu.*")
            print("3. Try running with sudo if permission denied")
            print("4. Check if another program is using the port")
            print("5. Try unplugging and replugging the USB device")
            return False

    def disconnect(self):
        """Disconnect from the STM32 board."""
        if self.serial and self.serial.is_open:
            # Set DTR and RTS lines low before closing
            self.serial.setDTR(False)
            self.serial.setRTS(False)
            self.serial.close()
            self.connected = False
            print("Disconnected from board")

    def send_command(self, command: str, wait_time: float = 0.1) -> str:
        """Send a command to the STM32 board and wait for response."""
        if not self.connected:
            print("Not connected to board")
            return ""

        try:
            # Add carriage return and line feed
            command = f"{command}\r\n"
            print(f"Sending command: {command.strip()}")
            
            # Clear any existing data
            self.serial.flushInput()
            
            # Send the command
            self.serial.write(command.encode())
            self.serial.flush()
            
            # Wait for response
            time.sleep(wait_time)
            
            if self.serial.in_waiting:
                response = self.serial.read(self.serial.in_waiting).decode()
                return response.strip()
            return ""
        except Exception as e:
            print(f"Error sending command: {e}")
            return ""

    def flash_binary(self, binary_path: str) -> bool:
        """Flash a binary file to the STM32 board using STM32CubeProgrammer."""
        try:
            cmd = [
                "STM32_Programmer_CLI",
                "-c", "port=SWD",
                "-w", binary_path,
                "-v"
            ]
            result = subprocess.run(cmd, capture_output=True, text=True)
            return result.returncode == 0
        except Exception as e:
            print(f"Error flashing binary: {e}")
            return False

    def build_project(self, project_path: str) -> bool:
        """Build the STM32 project using STM32CubeIDE."""
        try:
            cmd = [
                "STM32CubeIDE",
                "-nosplash",
                "-application", "org.eclipse.cdt.managedbuilder.core.headlessbuild",
                "-data", project_path,
                "-import", project_path,
                "-build", "test_cfe"
            ]
            result = subprocess.run(cmd, capture_output=True, text=True)
            return result.returncode == 0
        except Exception as e:
            print(f"Error building project: {e}")
            return False

    def get_debug_info(self) -> Dict:
        """Get debug information from the STM32 board."""
        if not self.connected:
            return {}

        info = {}
        # Send various debug commands and collect information
        info['version'] = self.send_command("version")
        info['status'] = self.send_command("status")
        return info

    def monitor_serial(self, duration: float = 60.0):
        """Monitor serial output for a specified duration."""
        if not self.connected:
            print("Not connected to board")
            return

        start_time = time.time()
        try:
            while time.time() - start_time < duration:
                if self.serial.in_waiting:
                    data = self.serial.read(self.serial.in_waiting)
                    print(data.decode(), end='')
                time.sleep(0.1)
        except KeyboardInterrupt:
            print("\nMonitoring stopped by user")

def main():
    """Example usage of STM32Utils."""
    stm32 = STM32Utils()
    
    # Example workflow
    if stm32.connect():
        # Send a test command
        response = stm32.send_command("help")
        print(f"Response: {response}")
        
        # Monitor serial output for 10 seconds
        stm32.monitor_serial(duration=10)
        
        # Get debug info
        debug_info = stm32.get_debug_info()
        print("Debug Info:", json.dumps(debug_info, indent=2))
        
        stm32.disconnect()

if __name__ == "__main__":
    main() 