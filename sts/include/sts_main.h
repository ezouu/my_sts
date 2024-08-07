// cfe_main.h

#ifndef CFE_MAIN_H
#define CFE_MAIN_H



void putc(char c);
int printf(const char *templat, ...);
char getc();


#include "ui_commands.h"

void poll_for_input(char *buffer, int size);
void cfe_main(int a, int b);

#endif // CFE_MAIN_H
