// ui_commands.h

#ifndef UI_COMMANDS_H
#define UI_COMMANDS_H

#include <sts_main.h>

typedef struct {
    const char *name;
    void (*function)();
} Command;

void register_ui_commands();


void simple_command();
void help_command();

void execute_command(char *command_name);


extern Command command_list[];
extern const int COMMAND_COUNT;


#endif // UI_COMMANDS_H
