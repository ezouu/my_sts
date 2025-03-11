#!/usr/bin/env python3
import time
import random
from typing import List, Tuple
from sts_wrapper.sts import (
    led_red_on, led_red_off,
    led_green_on, led_green_off,
    write_i2c, read_i2c,
    init_joystick, read_joystick,
    init_systick, get_systick_count,
    display_memory, edit_memory
)

class TestResult:
    def __init__(self, name: str, passed: bool, message: str = ""):
        self.name = name
        self.passed = passed
        self.message = message

def run_test(name: str, test_func) -> TestResult:
    """Run a test function and return the result"""
    print(f"\nRunning test: {name}")
    try:
        test_func()
        return TestResult(name, True)
    except Exception as e:
        return TestResult(name, False, str(e))

def test_led_pattern(pattern: List[Tuple[str, float]]) -> None:
    """Test LED patterns with specified timings"""
    for action, duration in pattern:
        if action == "red_on":
            led_red_on()
        elif action == "red_off":
            led_red_off()
        elif action == "green_on":
            led_green_on()
        elif action == "green_off":
            led_green_off()
        time.sleep(duration)

def test_led_sequences():
    """Test various LED sequences and patterns"""
    print("\nTesting LED Sequences...")
    
    # Test alternating pattern
    pattern = [
        ("red_on", 0.2),
        ("green_on", 0.2),
        ("red_off", 0.2),
        ("green_off", 0.2)
    ] * 3
    print("Testing alternating pattern...")
    test_led_pattern(pattern)
    
    # Test morse code SOS pattern
    sos_pattern = [
        # S (... short)
        ("red_on", 0.2), ("red_off", 0.2),
        ("red_on", 0.2), ("red_off", 0.2),
        ("red_on", 0.2), ("red_off", 0.4),
        # O (--- long)
        ("red_on", 0.6), ("red_off", 0.2),
        ("red_on", 0.6), ("red_off", 0.2),
        ("red_on", 0.6), ("red_off", 0.4),
        # S (... short)
        ("red_on", 0.2), ("red_off", 0.2),
        ("red_on", 0.2), ("red_off", 0.2),
        ("red_on", 0.2), ("red_off", 0.2)
    ]
    print("Testing SOS pattern...")
    test_led_pattern(sos_pattern)

def test_i2c_stress():
    """Stress test I2C operations"""
    print("\nStress Testing I2C...")
    
    # Test multiple writes and reads
    expander = 1
    addr = 0x20
    num_tests = 10
    
    for i in range(num_tests):
        value = random.randint(0, 255)
        print(f"Test {i+1}/{num_tests}: Writing {hex(value)}...")
        write_i2c(expander, addr, value)
        read_value = read_i2c(expander, addr)
        assert read_value == value, f"Read value {hex(read_value)} doesn't match written value {hex(value)}"
        time.sleep(0.1)
    
    # Test boundary values
    boundary_values = [0x00, 0xFF, 0x55, 0xAA]
    for value in boundary_values:
        print(f"Testing boundary value {hex(value)}...")
        write_i2c(expander, addr, value)
        read_value = read_i2c(expander, addr)
        assert read_value == value, f"Boundary test failed for value {hex(value)}"

def test_joystick_advanced():
    """Advanced joystick testing"""
    print("\nAdvanced Joystick Testing...")
    
    print("Initializing joystick...")
    init_joystick()
    
    # Test rapid reads
    print("Testing rapid joystick reads...")
    readings = []
    for _ in range(50):  # 50 rapid reads
        readings.append(read_joystick())
        time.sleep(0.01)
    
    # Analyze readings
    unique_positions = len(set(readings))
    print(f"Detected {unique_positions} unique positions")
    
    # Test for stuck positions
    print("Testing for stuck positions...")
    prev_reading = None
    stuck_count = 0
    for reading in readings:
        if reading == prev_reading:
            stuck_count += 1
        prev_reading = reading
    print(f"Stuck position count: {stuck_count}")

def test_systick_precision():
    """Test SysTick timer precision"""
    print("\nTesting SysTick Precision...")
    
    print("Initializing SysTick...")
    init_systick()
    
    # Measure tick intervals
    intervals = []
    prev_count = get_systick_count()
    
    print("Measuring tick intervals...")
    for _ in range(20):
        time.sleep(0.1)  # Should be approximately 100ms
        current_count = get_systick_count()
        interval = current_count - prev_count
        intervals.append(interval)
        prev_count = current_count
    
    # Analyze intervals
    avg_interval = sum(intervals) / len(intervals)
    max_deviation = max(abs(i - avg_interval) for i in intervals)
    print(f"Average interval: {avg_interval}")
    print(f"Maximum deviation: {max_deviation}")

def test_memory_patterns():
    """Test memory operations with various patterns"""
    print("\nTesting Memory Patterns...")
    
    # Test patterns
    patterns = [
        (0x20000000, 0x00000000),  # All zeros
        (0x20000004, 0xFFFFFFFF),  # All ones
        (0x20000008, 0x55555555),  # Alternating 0101
        (0x2000000C, 0xAAAAAAAA),  # Alternating 1010
        (0x20000010, 0x12345678),  # Ascending pattern
        (0x20000014, 0x87654321)   # Descending pattern
    ]
    
    for addr, value in patterns:
        print(f"\nTesting pattern {hex(value)} at address {hex(addr)}...")
        print("Writing value...")
        edit_memory(addr, value)
        
        print("Reading back value...")
        display_memory(addr)
        
        # Add small delay between operations
        time.sleep(0.1)

def main():
    print("Starting advanced native function tests...")
    
    tests = [
        ("LED Sequences", test_led_sequences),
        ("I2C Stress Test", test_i2c_stress),
        ("Advanced Joystick", test_joystick_advanced),
        ("SysTick Precision", test_systick_precision),
        ("Memory Patterns", test_memory_patterns)
    ]
    
    results = []
    try:
        for name, test_func in tests:
            result = run_test(name, test_func)
            results.append(result)
            
    except KeyboardInterrupt:
        print("\nTests interrupted by user")
    except Exception as e:
        print(f"\nUnexpected error during tests: {e}")
    finally:
        # Print test summary
        print("\nTest Summary:")
        print("-" * 40)
        passed = sum(1 for r in results if r.passed)
        total = len(results)
        print(f"Passed: {passed}/{total} tests")
        
        if passed < total:
            print("\nFailed Tests:")
            for result in results:
                if not result.passed:
                    print(f"- {result.name}: {result.message}")

if __name__ == "__main__":
    main() 