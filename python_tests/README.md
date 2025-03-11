# STM32 Python Testing Tools

This directory contains Python scripts for testing and controlling the STM32 board through serial communication.

## Files

- `stm32_utils.py`: Core utility class for STM32 board communication
- `test_communication.py`: Test script for verifying board communication
- `test_leds.py`: Script for testing LED functionality
- `test_advanced.py`: Script for testing advanced board features
- `test_native.py`: Basic native function testing through C interface
- `test_native_advanced.py`: Advanced native function testing with comprehensive test cases
- `requirements.txt`: Python package dependencies

## Setup

1. Create and activate a virtual environment (recommended):
   ```bash
   python3 -m venv venv
   source venv/bin/activate  # On macOS/Linux
   ```

2. Install required packages:
   ```bash
   pip install -r requirements.txt
   ```

## Usage

### Testing Communication
```bash
python3 test_communication.py
```
This script verifies basic communication with the STM32 board.

### Testing LED Control
```bash
python3 test_leds.py
```
This script tests LED control functionality using commands like:
- `ledr 1`: Turn on red LED
- `ledr 0`: Turn off red LED
- `ledg 1`: Turn on green LED
- `ledg 0`: Turn off green LED

### Testing Advanced Features
```bash
python3 test_advanced.py
```
This script tests various advanced board features:
- I2C Operations:
  - `writei2c`: Write to I2C devices
  - `displayi2c`: Read from I2C devices
  - `writei2cio2`: Write and display I2C values
- Joystick:
  - `joystick`: Initialize and read joystick input
- Systick Timer:
  - `systick`: Initialize and monitor system tick timer
- Memory Operations:
  - `display`: View memory contents
  - `edit`: Modify memory values

### Native Function Testing
```bash
python3 test_native.py
```
This script provides basic testing of native C functions through the Python interface:
- LED control functions
- Basic I2C operations
- Simple joystick reading
- Basic SysTick timer operations
- Memory read/write operations

### Advanced Native Function Testing
```bash
python3 test_native_advanced.py
```
This script provides comprehensive testing with advanced test cases:

1. **LED Pattern Testing**
   - Alternating LED patterns
   - Morse code SOS pattern
   - Custom pattern support with timing control

2. **I2C Stress Testing**
   - Random value write/read verification
   - Boundary value testing (0x00, 0xFF, 0x55, 0xAA)
   - Multiple consecutive operations

3. **Advanced Joystick Testing**
   - Rapid read testing (50 reads with 10ms intervals)
   - Unique position detection
   - Stuck position analysis

4. **SysTick Precision Testing**
   - Interval measurement and analysis
   - Average interval calculation
   - Maximum deviation tracking

5. **Memory Pattern Testing**
   - Various bit patterns (zeros, ones, alternating)
   - Ascending/descending patterns
   - Sequential address testing

The advanced test suite includes:
- Automated test execution
- Test result tracking
- Detailed failure reporting
- Test summary generation

## Port Configuration

The scripts are configured to use the USB-to-Serial converter at `/dev/cu.usbserial-FTDO6V6D`. If your port is different, modify the port in the test scripts.

## Troubleshooting

1. If you get a "Resource busy" error:
   - Check if another program is using the serial port
   - Try unplugging and replugging the USB device
   - Use `lsof | grep usbserial` to check port usage

2. If you get a "Permission denied" error:
   - Check port permissions: `ls -l /dev/cu.*`
   - Try running with sudo if needed

3. If no response from the board:
   - Verify TX/RX connections
   - Check if the board is powered on
   - Verify the correct baudrate is set (default: 115200) 