#!/usr/bin/env python3
import time
from sts_wrapper.sts import (
    led_red_on, led_red_off,
    led_green_on, led_green_off,
    write_i2c, read_i2c,
    init_joystick, read_joystick,
    init_systick, get_systick_count,
    display_memory, edit_memory
)

def test_led_functions():
    """Test direct LED control through C functions"""
    print("\nTesting LED Functions...")
    
    # Test red LED
    print("Testing Red LED...")
    led_red_on()
    time.sleep(1)
    led_red_off()
    time.sleep(1)
    
    # Test green LED
    print("Testing Green LED...")
    led_green_on()
    time.sleep(1)
    led_green_off()
    time.sleep(1)

def test_i2c_functions():
    """Test I2C operations through C functions"""
    print("\nTesting I2C Functions...")
    
    # Test I2C write/read
    expander = 1
    addr = 0x20
    value = 0x55
    
    print(f"Writing {hex(value)} to expander {expander} at address {hex(addr)}...")
    write_i2c(expander, addr, value)
    
    print("Reading back value...")
    read_value = read_i2c(expander, addr)
    print(f"Read value: {hex(read_value)}")

def test_joystick():
    """Test joystick functionality through C functions"""
    print("\nTesting Joystick...")
    
    print("Initializing joystick...")
    init_joystick()
    
    print("Reading joystick for 5 seconds...")
    start_time = time.time()
    while time.time() - start_time < 5:
        position = read_joystick()
        print(f"Joystick position: {position}")
        time.sleep(0.1)

def test_systick():
    """Test systick functionality through C functions"""
    print("\nTesting SysTick...")
    
    print("Initializing SysTick...")
    init_systick()
    
    print("Reading SysTick count for 5 seconds...")
    start_time = time.time()
    while time.time() - start_time < 5:
        count = get_systick_count()
        print(f"SysTick count: {count}")
        time.sleep(0.1)

def test_memory_operations():
    """Test memory operations through C functions"""
    print("\nTesting Memory Operations...")
    
    # Test address
    addr = 0x20000000
    value = 0x12345678
    
    print(f"Displaying memory at {hex(addr)}...")
    display_memory(addr)
    
    print(f"Writing {hex(value)} to address {hex(addr)}...")
    edit_memory(addr, value)
    
    print("Reading back memory...")
    display_memory(addr)

def main():
    print("Starting native function tests...")
    
    try:
        # Run all tests
        test_led_functions()
        test_i2c_functions()
        test_joystick()
        test_systick()
        test_memory_operations()
        
    except KeyboardInterrupt:
        print("\nTests interrupted by user")
    except Exception as e:
        print(f"\nError during tests: {e}")

if __name__ == "__main__":
    main() 