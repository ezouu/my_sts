import os
import ctypes
from ctypes import c_int, c_ulong, c_ubyte

# Load the shared library
_lib_path = os.path.join(os.path.dirname(__file__), 'libsts.so')
_sts = ctypes.CDLL(_lib_path)

# LED Control Functions
def led_red_on():
    return _sts.led_red_on()

def led_red_off():
    return _sts.led_red_off()

def led_green_on():
    return _sts.led_green_on()

def led_green_off():
    return _sts.led_green_off()

# I2C Functions
def write_i2c(expander: int, addr: int, value: int) -> int:
    _sts.write_i2c.argtypes = [c_int, c_ubyte, c_ubyte]
    _sts.write_i2c.restype = c_int
    return _sts.write_i2c(expander, addr, value)

def read_i2c(expander: int, addr: int) -> int:
    _sts.read_i2c.argtypes = [c_int, c_ubyte]
    _sts.read_i2c.restype = c_int
    return _sts.read_i2c(expander, addr)

# Joystick Functions
def init_joystick() -> int:
    _sts.init_joystick.restype = c_int
    return _sts.init_joystick()

def read_joystick() -> int:
    _sts.read_joystick.restype = c_int
    return _sts.read_joystick()

# SysTick Functions
def init_systick() -> int:
    _sts.init_systick.restype = c_int
    return _sts.init_systick()

def get_systick_count() -> int:
    _sts.get_systick_count.restype = c_ulong
    return _sts.get_systick_count()

# Memory Operations
def display_memory(addr: int) -> int:
    _sts.display_memory.argtypes = [c_ulong]
    _sts.display_memory.restype = c_int
    return _sts.display_memory(addr)

def edit_memory(addr: int, value: int) -> int:
    _sts.edit_memory.argtypes = [c_ulong, c_ulong]
    _sts.edit_memory.restype = c_int
    return _sts.edit_memory(addr, value) 