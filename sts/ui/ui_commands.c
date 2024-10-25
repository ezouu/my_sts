
#include <ui_commands.h>
#include <gpio.h>
#include<stdint.h>
/*
void simple_command();
void help_command();
void register_ui_commands();
void LED_Init();
*/
#define NULL ((void*)0)
#define BUFFER_SIZE 100


#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
#define GPIOC_BASE 0x48000800

static int ui_CM(int argc, char *argv[]);

void simple_command(int argc, char *argv[]);
void help_command(int argc, char *argv[]);
void led_command(int argc, char *argv[]);
void ui_cmd_display(int argc, char *argv[]);
void ui_cmd_edit(int argc, char *argv[]);
void LEDR_Init(int argc, char *argv[]);
void ui_cmd_I2C(int argc, char *argv[]);
static int ui_cmd_joystick(int argc, char *argv[]);
static int uart_handler(int argc, char *argv[]);
static int ui_cmd_write_I2C(int argc, char *argv[]);
static int ui_clock_measure(int argc, char *argv[]);
static int ui_cmd_LEDG(int argc, char *argv[]);
static int SysTick_Init(int argc, char *argv[]);


#define MAX_COMMANDS 50
CommandWithArgs command_list[MAX_COMMANDS];
int command_count = 0;

int add_cmd(const char *name, void (*function)(int argc, char *argv[]), const char *description) {
    command_list[command_count].name = name;
    command_list[command_count].function = function;
    command_list[command_count].description = description;
    command_count++;

    return 0;
}

void register_ui_commands() {
    add_cmd("simple", simple_command, "Executes a simple command.");
    add_cmd("help", help_command, "Displays help information.");
    add_cmd("display", ui_cmd_display, "Displays memory contents.");
    add_cmd("edit", ui_cmd_edit, "Edits a memory location.");
    add_cmd("ledr", LEDR_Init, "Red LED.");
    add_cmd("i2c", ui_cmd_I2C, "Executes an I2C command.");
    add_cmd("joystick", ui_cmd_joystick, "Handles joystick input.");
    add_cmd("uart", uart_handler, "Handles UART communication.");
    add_cmd("i2cwrite", ui_cmd_write_I2C, "Writes to I2C.");
    add_cmd("measureclock", ui_clock_measure, "measure clock" );
    add_cmd("ledg", ui_cmd_LEDG, "Green LED" );
    add_cmd("cm", ui_CM, "measure clock" );
    add_cmd("systick", SysTick_Init, "systick init" );
}



#define COMMAND_COUNT (sizeof(command_list) / sizeof(CommandWithArgs))


char* split_string(char* str, char delimiter, int* current_position) {
    if (str[*current_position] == '\0') {
        return NULL;
    }

    char* token = &str[*current_position];
    while (str[*current_position] != '\0') {
        if (str[*current_position] == delimiter) {
            str[*current_position] = '\0';
            (*current_position)++;
            return token;
        }
        (*current_position)++;
    }

    return token;
}


void execute_command(char *input_buffer) {
    char *argv[BUFFER_SIZE];
    int argc = 0;
    int current_position = 0;

    char *token = split_string(input_buffer, ' ', &current_position);
    while (token != NULL && argc < BUFFER_SIZE) {
        argv[argc++] = token;
        token = split_string(input_buffer, ' ', &current_position);
    }

    for (int i = 0; i < COMMAND_COUNT; i++) {
        if (strcmp(argv[0], command_list[i].name) == 0) {
            command_list[i].function(argc, argv);
            return;
        }
    }
    printf("Unknown command: %s\n", argv[0]);
}


void simple_command(int argc, char *argv[]) {
    printf("Executing simple command.\n");
    if (argc > 1) {
        printf("Argument: %s\n", argv[1]);
        printf("Argument: %s\n", argv[2]);

    }
}

void help_command(int argc, char *argv[]) {
    printf("Available commands:\n");
    for (int i = 0; i < command_count; i++) {
        printf("- %s: %s\n", command_list[i].name, command_list[i].description);
    }
}

#include <stdint.h>
void ui_cmd_display(int argc, char *argv[]) {

    printf("Printing out Memory Contents:\n");

    char *addr_str = argv[1];
    uint32_t address = (uint32_t)strtoul(addr_str, NULL, 0);

    volatile uint32_t *ptr;
    uint32_t value;

    volatile uint32_t *ADDRESS_END = (uint32_t *)(address + 0x32);

    for (; address <= (uint32_t)ADDRESS_END; address += 0x4) {
        ptr = (volatile uint32_t *)address;
        value = *ptr;

        printf("0x%08X: 0x%08X\n", address, value);
    }
}


void ui_cmd_edit(int argc, char *argv[])
{

	volatile uint32_t *ptr;
	uint32_t value;

	char *addr_str = argv[1];
    uint32_t address = (uint32_t)strtoul(addr_str, NULL, 0);

    ptr = (volatile uint32_t *)address;
    value = *ptr;

    printf("original value 0x%08X: 0x%08X\n", address, value);


	char *value_str = argv[2];
	uint32_t value2 = (uint32_t)strtoul(value_str, NULL, 0);




    ptr = (volatile uint32_t *)address;
    *ptr = value;

    printf("new value 0x%08X: 0x%08X\n", address, value2);

}

#define GPIOC_BASE 0x48000800

void LEDR_Init(int argc, char *argv[])

{

	*(volatile uint32_t *)(0x40007004) |= 0x200;



    //RCC->AHB2ENR |= (1 << 2);
    RCC->AHB2ENR |= 0xF;
    RCC->APB1ENR1 |= (1 << 28);
    //RCC->APB2ENR |= (1 << 28);
    *(volatile uint32_t *)(GPIOC_BASE) = 0x4;
    *(volatile uint32_t *)(GPIOC_BASE + 0x14) = 0x0; // turn off

    //GPIOC->GPIOx_MODER &= ~(0x3 << (1 * 2));
    //GPIOC->GPIOx_MODER |= (0x1 << (1 * 2));

    int state = atoi(argv[1]);
    volatile uint32_t *GPIOC_ODR = (uint32_t *)(GPIOC_BASE + 0x14);
    if (state == 1) {
        GPIOC->GPIOx_ODR &= ~(1 << 1);
        printf("LED is ON\n");
    } else if (state == 0) {
        GPIOC->GPIOx_ODR |= (1 << 1);
        printf("LED is OFF\n");
    } else {
        printf("Invalid state. Use 0 for OFF and 1 for ON.\n");
    }
}

void LEDG_Init(void) {

    *(volatile uint32_t *)(0x40007004) = 0x200;

    volatile uint32_t *RCC_AHB2ENR = (uint32_t *)(0x40021000 + 0x4C);
    *RCC_AHB2ENR = 0xf;

    volatile uint32_t *RCC_APB1ENR1 = (uint32_t *)(0x40021000 + 0x58);
    *RCC_APB1ENR1 |= (1 << 28);


    *(volatile uint32_t *)(GPIOB_BASE + 0)  |= 0x10; //

    *(volatile uint32_t *)(GPIOB_BASE + 0x14) = 0x0;
}


static int ui_cmd_LEDG(int argc, char *argv[]) {

    int state = atoi(argv[1]);


    LEDG_Init();
    volatile uint32_t *GPIOB_ODR = (uint32_t *)(GPIOB_BASE + 0x14);

    if (state == 0) {
    	*GPIOB_ODR |= (1 << 2);
        printf("LED1 is OFF\n");
    } else if (state == 1) {
        *GPIOB_ODR &= ~(1 << 2);
        printf("LED1 is ON\n");

    } else{
    	printf("Invalid state. Use 0 for OFF and 1 for ON.\n");


    }

    return 0;
}



void I2C_Init(void) {



    // Transmit
    I2C->I2C_CR1 = 0; // I2C_CR1, clear
    I2C->I2C_TIMINGR = 0x20303e5d; // I2C timing configuration
    I2C->I2C_OAR1 = 0; // I2C OAR1 configuration
    I2C->I2C_OAR1 = 0x8000; // Ack own address1 mode
    I2C->I2C_CR2 = 0; // I2C CR2 configuration
    USART -> USART_CR2 = 0x2008000; // Auto end, bit 15, NACK
    I2C->I2C_OAR2 = 0; // I2C OAR2 configuration
    I2C->I2C_CR1 = 1; // Enable the selected I2C peripheral
/*
    *(volatile uint32_t *)(0x40005400) = 0; // I2C_CR1, clear
    *(volatile uint32_t *)(0x40005410) = 0x20303e5d; // I2C timing configuration
    *(volatile uint32_t *)(0x40005408) = 0; // I2C OAR1 configuration
    *(volatile uint32_t *)(0x40005408) = 0x8000; // Ack own address1 mode
    *(volatile uint32_t *)(0x40005404) = 0; // I2C CR2 configuration
    *(volatile uint32_t *)(0x40004404) = 0x2008000; // Auto end, bit 15, NACK
    *(volatile uint32_t *)(0x4000540C) = 0; // I2C OAR2 configuration

    *(volatile uint32_t *)(0x40005400) = 1; // Enable the selected I2C peripheral
*/
}


void I2C_Init_INIT(void) {
    // Initialization and clock configuration
    RCC->APB2ENR = 0x4001; // __HAL_RCC_SYSCFG_CLK_ENABLE();
    RCC->APB1ENR1 = 0x10000000; // __HAL_RCC_PWR_CLK_ENABLE();
    // RCC->CCIPR = 0; // RCC I2C clock selection (commented out as it was in the original code)
    PWR->PWR_CR2 = 0x200; // PWR_CR2 enable
    RCC->AHB2ENR = 0x20ff; // GPIOG_CLK_ENABLE
    RCC->APB1ENR1 = 0x32200000;

    // GPIO configuration
    GPIOG->GPIOx_OSPEEDR = 0xc3c0fff; // GPIOx_OSPEEDR
    GPIOG->GPIOx_OTYPER = 0x2000; // GPIO port output type register (GPIOx_OTYPER)
    GPIOG->GPIOx_PUPDR = 0x4000000; // GPIOG_PUPDR
    GPIOG->GPIOx_AFRL = 0x400cc0; // Configure Alternate function mapped with the current IO
    GPIOG->GPIOx_MODER = 0x3bebcaaa; // Configure IO Direction mode (Input, Output, Alternate or Analog)
    GPIOG->GPIOx_OSPEEDR = 0x3c3c0fff; // Configure the IO Speed
    GPIOG->GPIOx_OTYPER = 0x6000; // GPIO_OTYPER
    GPIOA->GPIOx_PUPDR = 0x4000000; // Activate pull up or pull down GPIO_PUPDR
    GPIOG->GPIOx_AFRL = 0x4400cc0; // Configure Alternate function mapped with the current IO
    GPIOG->GPIOx_MODER = 0x2bebcaaa; // Configure IO Direction mode (Input, Output, Alternate or Analog)
    GPIOG->GPIOx_OSPEEDR = 0x3c3c0fff; // Configure the IO Speed
    GPIOG->GPIOx_OTYPER = 0x6000; // GPIO_OTYPER
    GPIOA->GPIOx_PUPDR = 0x0; // Activate pull up or pull down GPIO_PUPDR
    //*(volatile uint8_t *)(0x48001841) = 0x24; // hi2c->State = HAL_I2C_STATE_BUSY (specific address not covered by provided structures)

    I2C->I2C_CR1 = 0; // Disable the selected I2C peripheral
    I2C->I2C_TIMINGR = 0x20303E5D; // Configure I2Cx: Frequency range
    I2C->I2C_OAR1 = 0; // I2Cx OAR1 Configuration
    I2C->I2C_OAR1 = 0x8000; // Ack own address1 mode
    I2C->I2C_CR2 = 0; // Clear the I2C ADD10 bit
    I2C->I2C_OAR2 = 0; // I2Cx OAR2 Configuration
    I2C->I2C_CR1 = 0; // Configure I2Cx: Generalcall and NoStretch mode
    I2C->I2C_CR1 = 1; // Enable the selected I2C peripheral
}

void I2C_Init_INIT2(void) {
    // Initialization and clock configuration



    *(volatile uint32_t *)(0x40021060) = 0x4001; // __HAL_RCC_SYSCFG_CLK_ENABLE();



    *(volatile uint32_t *)(0x40021058) = 0x10000000; // __HAL_RCC_PWR_CLK_ENABLE();

  //  *(volatile uint32_t *)(0x40021088) = 0; // RCC I2C clock selection

    *(volatile uint32_t *)(0x40007004) = 0x200; // PWR_CR2 enable


    *(volatile uint32_t *)(0x4002104C) = 0x20ff; // GPIOG_CLK_ENABLE


    *(volatile uint32_t *)(0x40021058) = 0x32200000;


    // GPIO configuration
    *(volatile uint32_t *)(0x48001808) = 0xc3c0fff; // GPIOx_OSPEEDR
    *(volatile uint32_t *)(0x48001804) = 0x2000; // GPIO port output type register (GPIOx_OTYPER)
    *(volatile uint32_t *)(0x4800180C) = 0x4000000; // GPIOG_PUPDR
    *(volatile uint32_t *)(0x48001824) = 0x400cc0; // Configure Alternate function mapped with the current IO
    *(volatile uint32_t *)(0x48001800) = 0x3bebcaaa; // Configure IO Direction mode (Input, Output, Alternate or Analog)
    *(volatile uint32_t *)(0x48001808) = 0x3c3c0fff; // Configure the IO Speed
    *(volatile uint32_t *)(0x48001804) = 0x6000; // GPIO_OTYPER
    *(volatile uint32_t *)(0x4800082C) = 0x4000000; // Activate pull up or pull down GPIO_PUPDR
    *(volatile uint32_t *)(0x48001824) = 0x4400cc0; // Configure Alternate function mapped with the current IO
    *(volatile uint32_t *)(0x48001800) = 0x2bebcaaa; // Configure IO Direction mode (Input, Output, Alternate or Analog)
    *(volatile uint32_t *)(0x48001808) = 0x3c3c0fff; // Configure the IO Speed
    *(volatile uint32_t *)(0x48001804) = 0x6000; // GPIO_OTYPER
    *(volatile uint32_t *)(0x4800082C) = 0x0; // Activate pull up or pull down GPIO_PUPDR
    *(volatile uint8_t *)(0x48001841) = 0x24; // hi2c->State = HAL_I2C_STATE_BUSY


    *(volatile uint32_t *)(0x40005400) = 0; // Disable the selected I2C peripheral
    *(volatile uint32_t *)(0x40005410) = 0x20303E5D; // Configure I2Cx: Frequency range
    *(volatile uint32_t *)(0x40005408) = 0; // I2Cx OAR1 Configuration
    *(volatile uint32_t *)(0x40005408) = 0x8000; // Ack own address1 mode
    *(volatile uint32_t *)(0x40005404) = 0; // Clear the I2C ADD10 bit
    *(volatile uint32_t *)(0x4000540C) = 0; // I2Cx OAR2 Configuration
    *(volatile uint32_t *)(0x40005400) = 0; // Configure I2Cx: Generalcall and NoStretch mode
    *(volatile uint32_t *)(0x40005400) = 1; // Enable the selected I2C peripheral

}


void ui_cmd_I2C(int argc, char *argv[])
{
    RCC->APB2ENR = 0x4001;
    // *(volatile uint32_t *)(0x40021060) = 0x4001; // __HAL_RCC_SYSCFG_CLK_ENABLE();

    RCC->APB1ENR1 = 0x10000000;
    //*(volatile uint32_t *)(0x40021058) = 0x10000000; // __HAL_RCC_PWR_CLK_ENABLE();

    RCC->CCIPR = 0;
    //*(volatile uint32_t *)(0x40021088) = 0; // RCC i2c clock selection

    PWR->PWR_CR2 = 0x200;
    //*(volatile uint32_t *)(0x40007004) = 0x200; // PWR_CR2 enable

    RCC->AHB2ENR = 0x20ff;
    //*(volatile uint32_t *)(0x4002104C) = 0x20ff; // GPIOG_CLK_ENABLE

    RCC->APB1ENR1 = 0x32200000;
    //*(volatile uint32_t *)(0x40021058) = 0x32200000;

    GPIOG->GPIOx_OSPEEDR = 0xc3c0fff;
    //*(volatile uint32_t *)(0x48001808) = 0xc3c0fff; // GPIOx_OSPEEDR

    GPIOG->GPIOx_OTYPER = 0x2000;
    //*(volatile uint32_t *)(0x48001804) = 0x2000; // GPIO port output type register (GPIOx_OTYPER)

    GPIOG->GPIOx_PUPDR = 0x4000000;
    //*(volatile uint32_t *)(0x4800180C) = 0x4000000; // GPIOG_PUPDR

    GPIOG->GPIOx_AFRL = 0x400cc0;
    //*(volatile uint32_t *)(0x48001824) = 0x400cc0; // Configure Alternate function mapped with the current IO

    GPIOG->GPIOx_MODER = 0x3bebcaaa;
    //*(volatile uint32_t *)(0x48001800) = 0x3bebcaaa; // Configure IO Direction mode (Input, Output, Alternate or Analog)

    GPIOG->GPIOx_OSPEEDR = 0x3c3c0fff;
    //*(volatile uint32_t *)(0x48001808) = 0x3c3c0fff; // Configure the IO Speed

    GPIOG->GPIOx_OTYPER = 0x6000;
    //*(volatile uint32_t *)(0x48001804) = 0x6000; // GPIO_OTYPER

    GPIOA->GPIOx_PUPDR = 0x4000000;
    //*(volatile uint32_t *)(0x4800082C) = 0x4000000; // Activate pull up or pull down GPIO_PUPDR

    // GPIOG->GPIOx_AFRL = 0x4400cc0;
    *(volatile uint32_t *)(0x48001824) = 0x4400cc0; // Configure Alternate function mapped with the current IO

    // GPIOG->GPIOx_MODER = 0x2bebcaaa;
    *(volatile uint32_t *)(0x48001800) = 0x2bebcaaa; // Configure IO Direction mode (Input, Output, Alternate or Analog)

    // GPIOG->GPIOx_OSPEEDR = 0x3c3c0fff;
    *(volatile uint32_t *)(0x48001808) = 0x3c3c0fff; // Configure the IO Speed

    // GPIOG->GPIOx_OTYPER = 0x6000;
    *(volatile uint32_t *)(0x48001804) = 0x6000; // GPIO_OTYPER

    // GPIOA->GPIOx_PUPDR = 0x0;
    *(volatile uint32_t *)(0x4800082C) = 0x0; // Activate pull up or pull down GPIO_PUPDR

    // *(volatile uint8_t *)(0x48001841) = 0x24; (specific address not covered by provided structures)
    *(volatile uint8_t *)(0x48001841) = 0x24; // hi2c->State = HAL_I2C_STATE_BUSY;

    // I2C->I2C_CR1 = 0;
    *(volatile uint32_t *)(0x40005400) = 0; // Disable the selected I2C peripheral

    // I2C->I2C_TIMINGR = 0x20303E5D;
    *(volatile uint32_t *)(0x40005410) = 0x20303E5D; // Configure I2Cx: Frequency range

    // I2C->I2C_OAR1 = 0;
    *(volatile uint32_t *)(0x40005408) = 0; // I2Cx OAR1 Configuration

    // I2C->I2C_OAR1 = 0x8000;
    *(volatile uint32_t *)(0x40005408) = 0x8000; // Ack own address1 mode

    // I2C->I2C_CR2 = 0;
    *(volatile uint32_t *)(0x40005404) = 0; // Clear the I2C ADD10 bit

    // I2C->I2C_OAR2 = 0;
    *(volatile uint32_t *)(0x4000540C) = 0; // I2Cx OAR2 Configuration

    // I2C->I2C_CR1 = 0;
    *(volatile uint32_t *)(0x40005400) = 0; // Configure I2Cx: Generalcall and NoStretch mode

    // I2C->I2C_CR1 = 1;
    *(volatile uint32_t *)(0x40005400) = 1; // Enable the selected I2C peripheral

    // Transmit
    // I2C->I2C_CR1 = 0;
    *(volatile uint32_t *)(0x40005400) = 0; // I2C_CR1, clear

    // I2C->I2C_TIMINGR = 0x20303e5d;
    *(volatile uint32_t *)(0x40005410) = 0x20303e5d; // 595, timing

    // I2C->I2C_OAR1 = 0;
    *(volatile uint32_t *)(0x40005408) = 0; // 595, OAR1

    // I2C->I2C_OAR1 = 0x8000;
    *(volatile uint32_t *)(0x40005408) = 0x8000;

    // I2C->I2C_CR2 = 0;
    *(volatile uint32_t *)(0x40005404) = 0; // 616, CR2

    // USART->USART_CR2 = 0x2008000;
    *(volatile uint32_t *)(0x40004404) = 0x2008000; // 618, auto end, bit 15, NACK

    // I2C->I2C_OAR2 = 0;
    *(volatile uint32_t *)(0x4000540C) = 0; // 623, OAR2

    // I2C->I2C_CR1 = 1;
    *(volatile uint32_t *)(0x40005400) = 1; // 634, peripheral enable bit 0

    // I2C->I2C_TXDR = 0x0;
    *(volatile uint32_t *)(0x40005428) = 0x0; // 1162, TX reg

    // I2C->I2C_CR2 = 0x2012082;
    *(volatile uint32_t *)(0x40005404) = 0x2012082; // 7217, 82 device address

    // Receive
    uint32_t temp = 0; // I2C_ISR STOPF: STOP detection flag
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}

    // I2C->I2C_CR2 = 0x2012482;
    *(volatile uint32_t *)(0x40005404) = 0x2012482; // 7217 update CR2 register

    uint32_t busy = 0; // I2C_ISR BUSY: BUSY detection flag
    while (((busy = *(volatile uint32_t *)(0x40005400)) & 0x8000) == 1) {}

    uint32_t RXNE_BUSY = 0; // RXNE: Receive data register
    while (((RXNE_BUSY = *(volatile uint32_t *)(0x40005418)) & 0x4) == 0) {}

    // Corrections for printing function
    // RCC->CCIPR = 0x2;
    *(volatile uint32_t *)(0x40021088) = 0x2;

    uint32_t received_data = *(volatile uint32_t *)(0x40005424);
    printf("data");
    printf("Received data: 0x%08X\n", received_data);
}

static int READ_I2C_IO2(int reg_address)
{
    I2C_Init();
    uint32_t temp = 0;

    *(volatile uint32_t *)(0x40005428) = reg_address;
    //I2C->I2C_TXDR = reg_address; // Register address
    // I2C->I2C_TXDR = value_to_send; // Data to send

    //I2C->I2C_CR2 = 0x2012084; // 7217, 82 device address
    *(volatile uint32_t *)(0x40005404) = 0x2012084;

    //while (((temp = I2C->I2C_ISR) & 0x1) == 0) {}

    // Wait for STOPF
    temp = 0;
    //while (((temp = I2C->I2C_ISR) & 0x20) == 0) {}
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}

    I2C->I2C_CR2 = 0x2012484; // 7217 update CR2 register

    // Wait for RXNE
    uint32_t RXNE_BUSY = 0;
    while (((RXNE_BUSY = I2C->I2C_ISR) & 0x4) == 0) {}

    uint32_t received_data = I2C->I2C_RXDR;

    // Corrections for printing function
    // RCC->CCIPR = 0x2;
    // printf("Received data: 0x%08X\n", received_data);

    return received_data;
}
static int ui_cmd_write_I2C(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: write_I2C <reg_address> <value_to_send>\n");
        return -1;
    }

    char *reg_input = argv[1];
    char *val_input = argv[2];

    int reg_address = atoi(reg_input);
    int value_to_send = atoi(val_input);

    // Initialization and clock configuration
    I2C_Init_INIT();
    I2C_Init();

    // Write to I2C
    uint32_t temp = 0;

    while (((temp = I2C->I2C_ISR) & 0x1) == 0) {}

    I2C->I2C_TXDR = reg_address; // Register address
    I2C->I2C_CR2 = 0x2022082; // I2C device address

    while (((temp = I2C->I2C_ISR) & 0x1) == 0) {}

    I2C->I2C_TXDR = value_to_send;

    // Wait for STOPF
    temp = 0;
    while (((temp = I2C->I2C_ISR) & 0x20) == 0) {}

    // Read back the written value to verify
    while (((temp = I2C->I2C_ISR) & 0x1) == 0) {}

    I2C->I2C_TXDR = reg_address; // Register address
    I2C->I2C_CR2 = 0x2012082; // I2C device address

    while (((temp = I2C->I2C_ISR) & 0x1) == 0) {}

    // Wait for STOPF
    temp = 0;
    while (((temp = I2C->I2C_ISR) & 0x20) == 0) {}

    I2C->I2C_CR2 = 0x2012482; // Update CR2 register

    // Wait for RXNE
    uint32_t RXNE_BUSY = 0;
    while (((RXNE_BUSY = I2C->I2C_ISR) & 0x4) == 0) {}

    uint32_t received_data = I2C->I2C_RXDR;

    // Print results
    printf("Writing 0x%02X to register 0x%02X\n", value_to_send, reg_address);
    printf("Received data: 0x%08X\n", received_data);

    return 0;
}


static int ui_cmd_joystick(int argc, char *argv[])
{
/*
    char *state_str;
    int state;

    state_str = cmd_getarg(cmd, 0);
    state = atoi(state_str);

*/
    // *(volatile uint32_t *)(0x40005404) = 0x12084;
	I2C_Init_INIT2();
	//*(volatile uint32_t *)(0x40021088) = 0x2;


    while(1){

    	if((READ_I2C_IO2(0x10) & 1) == 0){
    		printf("SEL\r");
    		break;
    	}
    	if((READ_I2C_IO2(0x10) & 2) == 0){
    		printf("DOWN   \r");
    	}
    	if((READ_I2C_IO2(0x10) & 4) == 0){
    		printf("LEFT \r");
    	}
    	if((READ_I2C_IO2(0x10) & 8) == 0){
    		printf("RIGHT \r");
    	}
    	if((READ_I2C_IO2(0x10) & 16) == 0){
    		printf("UP      \r");
    	}

    }
    printf("joystick end");

    return 0;
}


static int uart_handler(int argc, char *argv[]){

	*(volatile uint32_t *)0xE000ED08 = 0x20000000;

	*(volatile uint32_t *)0xE000E104 = 0x20;
//	(*(volatile uint32_t *)0x40021058)|= (1 << 17); //RCC->APB1ENR1

	//(*(volatile uint32_t *)0x4000440C) = 0xD0;
	(*(volatile uint32_t *)0x40013800) |= 0x2D; //10 1101

	//(*(volatile uint32_t *)0x40013800) |= 0x2000;

	//(*(volatile uint32_t *)(0x40013800 + 0x0C)) |= 0x20;

//	(*(volatile uint32_t *)0x40004400) |= 0x2D;


	//(*(volatile uint32_t *)0xE000E104) = 0x7;
	while(1){
		printf("hello\n");
	}


	return 0;

}

void mytest_1(){
	printf("hello");

    // Clear the USART interrupt flag
    //volatile uint32_t *USART1_ICR = (volatile uint32_t *)(0x40013800 + 0x1C);

    // Clear the RXNE interrupt flag
    //volatile uint32_t *USART1_ISR = (volatile uint32_t *)(0x40013800 + 0x1C); // USART_ISR register
    volatile uint32_t USART1_ICR = *(volatile uint32_t *)(0x40013800 + 0x24); // USART_ICR register

    //printf("%c", USART1_ISR );
    printf("%c", USART1_ICR );

    while(1){

    }


    //*(volatile uint32_t *)0x40013824 = 0xFFFFFFFF;
    //*USART1_ICR = 0xFFFFFFFF;
    //printf("%c", USART1_ICR);

    /*
	volatile uint32_t *LPUART_ISR = (uint32_t *)(0x40013800 + 0x1C);
	printf("%c", LPUART_ISR);
	*LPUART_ISR = 0xFFFFFFFF;
yeah
	*/
}


static int ui_clock_measure(int argc, char *argv[]){

	*(volatile uint32_t *)(0x40007000) = 0x200;

    RCC->AHB2ENR |= 0xf;

    RCC->APB1ENR1 |= (1 << 28);



	volatile uint32_t val;

	val = *(volatile uint32_t *)(0x48000000);
	val &= 0xFFFCFFFF;
	val |= 0x10000;
	*(volatile uint32_t *)(0x48000000) = val;
	//convert to function
	val = *(volatile uint32_t *)(0x4800000C);
	val &= 0xFFFCFFFF;

	*(volatile uint32_t *)(0x4800000C) = val;

	val = *(volatile uint32_t *)(0x48000014);
	val &= 0xFFFCFFFF;
	val |= 0x100;
	*(volatile uint32_t *)(0x48000014) = val;




    int state = atoi(argv[1]);

    val = *(volatile uint32_t *)(0x48000014);

    if (state == 1) {

    	val |= 0x100;
    	*(volatile uint32_t *)(0x48000014) = val;
    	printf("0x%08X\n", val);
    } else if (state == 0) {
    	val &= ~0x100;
    	*(volatile uint32_t *)(0x48000014) = val;
    	printf("0x%08X\n", val);

    } else{
    	printf("Invalid state");

    }

    return 0;
}


static int ui_CM(int argc, char *argv[]){




	*(volatile uint32_t *)(0x40007000) = 0x200;

    RCC->AHB2ENR |= 0xf;

    RCC->APB1ENR1 |= (1 << 28);



	volatile uint32_t val;

	val = *(volatile uint32_t *)(0x48000000);
	val &= 0xFFFCFFFF;
	val |= 0x20000;
	*(volatile uint32_t *)(0x48000000) = val;

	//convert to function

	val = *(volatile uint32_t *)(0x4800000C);
	val &= 0xFFFCFFFF;
	*(volatile uint32_t *)(0x4800000C) = val;


	val = *(volatile uint32_t *)(0x48000024);
	val &= 0xFFFFFFF0;
	*(volatile uint32_t *)(0x48000024) = val;

	RCC ->CFGR |= (2<< 24);
	RCC ->CFGR |= (4<< 28);





    return 0;
}


static int SysTick_Init(int argc, char *argv[]){

	 *(volatile uint32_t *)0xE000ED08 = 0x20000000; // vtor

    *(volatile uint32_t *)0xE000E010 = 0x7; // 00000111

    *(volatile uint32_t *)0xE000E014 = 1000000;

    *(volatile uint32_t *)0xE000E018 = 0;

    *(volatile uint32_t *)0xE000ED20 = 0;

    volatile uint32_t *ptr;
    uint32_t value;




    uint32_t address = 0xE000E018;


	while (1) {
	    ptr = (volatile uint32_t *)address;
	    value = *ptr;
		printf("0x%08X\n", value);
	    }


    return 0;
}


#if 0

#define RCC_BASE_ADDR              0x40021000UL
#define PWR_BASE_ADDR              0x40007000UL

#define RCC_CFGR_REG_OFFSET        0x08UL

#define RCC_CFGR_REG_ADDR          (RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET )

#define GPIOA_BASE_ADDR            0x48000000UL

static int ui_CM(int argc, char *argv[])
{
	uint32_t *pRccCfgrReg =  (uint32_t*) RCC_CFGR_REG_ADDR;


	// 1. Configure the RCC_CFGR MCOSEL bit fields to select LSE as clock source: 0111: LSE clock selected
	*pRccCfgrReg &=~(0U << 27);
	*pRccCfgrReg |= (1U << 26);
	*pRccCfgrReg |= (1U << 25);
	*pRccCfgrReg |= (1U << 24);

	// 2. Configure PA8 to AF0 mode to behave as MCO signal
	// 2.1 Enable the peripheral clock for GPIOA peripheral - RCC_AHB2ENR
	uint32_t *pRCCAhb2Enr = (uint32_t*)(RCC_BASE_ADDR + 0x4C);
	*pRCCAhb2Enr |= (1U << 0); //Enable GPIOA peripheral clock

	// 2.2 Configure the mode of GPIOA pin 8 as alternate function mode - GPIOx_MODER
	uint32_t *pGPIOAModeReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x00UL);
	*pGPIOAModeReg &=~(1U << 16); 	// clear bit 16
	*pGPIOAModeReg |= (1U << 17);   // set bit 17

	// 2.3 Configure the alternation function register to set the mode 0 for PA8 - GPIOx_AFRH
	uint32_t *pGPIOAAltFunHighReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x24);
	*pGPIOAAltFunHighReg &=~(1U << 0); // clear bit 0
	*pGPIOAAltFunHighReg &=~(1U << 1); // clear bit 1
	*pGPIOAAltFunHighReg &=~(1U << 2); // clear bit 2
	*pGPIOAAltFunHighReg &=~(1U << 3); // clear bit 3

	// 3. Turn on PWR peripheral clock
	uint32_t *pRCC_APB1ENR1 = (uint32_t*)(RCC_BASE_ADDR + 0x58);
	*pRCC_APB1ENR1 |= (1U << 28);

	// 4. Disable backup domain write protection
	uint32_t *pPWR_CR1 = (uint32_t*)(PWR_BASE_ADDR + 0x00);
	*pPWR_CR1 |= (1U << 8);

	// 5. Turn on LSE clock (LSEON)
	uint32_t *pRCC_BDCR = (uint32_t*)(RCC_BASE_ADDR + 0x90);
	*pRCC_BDCR |= (1U << 0);
	for (;;);
}

#endif

