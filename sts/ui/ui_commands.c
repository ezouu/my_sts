
#include <ui_commands.h>


void simple_command();
void help_command();
void register_ui_commands();

#define BUFFER_SIZE 100
void register_ui_commands() {

    simple_command();
}


Command command_list[] = {
    {"simple", simple_command},
    {"help", help_command},
};


#define COMMAND_COUNT (sizeof(command_list) / sizeof(Command))


void execute_command(char *input_buffer) {
    int num_commands = sizeof(command_list) / sizeof(Command);
    for (int i = 0; i < num_commands; ++i) {
        printf("Command name: %s\n", command_list[i].name);
    }
	/*
    for (int i = 0; i < COMMAND_COUNT; i++) {
    	printf("Command name: %s\n", command_list[i].name);
        if (strcmp(input_buffer, command_list[i].name) == 0) {
            command_list[i].function();
            return;
        }
    }
    printf("Unknown command: %s\n", input_buffer);
	*/
}


void simple_command() {
    printf("Executing simple command.\n");
}

void help_command() {
    printf("Available commands:\n");
    for (int i = 0; i < COMMAND_COUNT; i++) {
        printf("- %s\n", command_list[i].name);
    }
}
