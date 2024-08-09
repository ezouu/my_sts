
#include <ui_commands.h>
/*
void simple_command();
void help_command();
void register_ui_commands();
void LED_Init();
*/
#define NULL ((void*)0)
#define BUFFER_SIZE 100
void register_ui_commands() {

    simple_command();
}


void simple_command(int argc, char *argv[]);
void help_command(int argc, char *argv[]);
void led_command(int argc, char *argv[]);
void ui_cmd_display(int argc, char *argv[]);
void ui_cmd_edit(int argc, char *argv[]);
void LED_Init(void);

CommandWithArgs command_list[] = {
    {"simple", simple_command},
    {"help", help_command},
	{"display", ui_cmd_display},
	{"edit", ui_cmd_edit},
	{"LED", LED_Init},
};



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
    for (int i = 0; i < COMMAND_COUNT; i++) {
        printf("- %s\n", command_list[i].name);
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

#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
#define GPIOC_BASE 0x48000800


void LED_Init(void) {

    *(volatile uint32_t *)(0x40007004) = 0x200;

    volatile uint32_t *RCC_AHB2ENR = (uint32_t *)(0x40021000 + 0x4C);
    *RCC_AHB2ENR = 0xf;


    volatile uint32_t *RCC_APB1ENR1 = (uint32_t *)(0x40021000 + 0x58);
    *RCC_APB1ENR1 |= (1 << 28);


    *(volatile uint32_t *)(GPIOC_BASE) = 0x4; // turn on


    *(volatile uint32_t *)(GPIOC_BASE + 0x14) = 0x0; // turn off
}

