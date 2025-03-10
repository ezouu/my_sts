#ifndef STS_LIB_H
#define STS_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

// LED Control Functions
int led_red_on(void);
int led_red_off(void);
int led_green_on(void);
int led_green_off(void);

// I2C Functions
int write_i2c(int expander, unsigned char addr, unsigned char value);
int read_i2c(int expander, unsigned char addr);

// Joystick Functions
int init_joystick(void);
int read_joystick(void);

// SysTick Functions
int init_systick(void);
unsigned long get_systick_count(void);

// Memory Operations
int display_memory(unsigned long addr);
int edit_memory(unsigned long addr, unsigned long value);

#ifdef __cplusplus
}
#endif

#endif // STS_LIB_H 