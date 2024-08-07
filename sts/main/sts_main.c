//#ifndef CFG_STACK_SIZE
#define STACK_SIZE	8192

#define CFG_BOARDNAME "STM32L476G-Board"
#define CFG_HEAP_SIZE 64

const char *cfe_boardname = CFG_BOARDNAME;

void cfe_main(int,int);
extern void cfe_device_poll(void *x);

extern unsigned int CPUCFG_CPUSPEED(void);

extern int ui_init_envcmds(void);
extern int ui_init_devcmds(void);
extern int ui_init_netcmds(void);
extern int ui_init_memcmds(void);
extern int ui_init_loadcmds(void);
extern int ui_init_pcicmds(void);
extern int ui_init_examcmds(void);
extern int ui_init_flashcmds(void);
extern int ui_init_misccmds(void);
#if CFG_VAPI
extern int ui_init_vapicmds(void);
#endif

#if CFG_VENDOR_EXTENSIONS
extern int ui_init_vendorcmds(void);
#endif

//void cfe_command_restart(uint64_t status);

//extern segtable_t *_getsegtbl(void);

extern const char *builddate;
extern const char *builduser;

#if CFG_MULTI_CPUS
extern int altcpu_cmd_start(uint64_t,uint64_t *);
extern int altcpu_cmd_stop(uint64_t);
#endif


extern void puts(char);

#include <stdint.h>

// Function prototypes from lib_printf.c
void putc(char c);
int printf(const char *templat, ...);
char getc(); // Function to get a character from USART

#define BUFFER_SIZE 100


void poll_for_input(char *buffer, int size) {
    int index = 0;
    char ch;

    printf("STS>");

    while (1) {
        ch = getc();
        if (ch == '\r' || ch == '\n') {

			if (index == 0) {
				printf("\n");
				printf("STS> ");
				continue;
			}
            buffer[index] = '\0';
            printf("\nCaptured command: '%s'\n", buffer);
            break;
        } else if (ch == '\b' && index > 0) {
            index--;
            printf("\b \b");
        } else if (index < size - 1) {
            buffer[index++] = ch;
            putc(ch);
        }
    }
}

void sts_main(int a, int b) {
    char input_buffer[BUFFER_SIZE];

	while(1){

		poll_for_input(input_buffer, BUFFER_SIZE);


		//printf("\nYou entered: %s\n", input_buffer);

		execute_command(input_buffer);

		printf("\n");

	}

}


char getc() {
    volatile uint32_t *usart_isr = (volatile uint32_t *)(0x40013800 + 0x1C);
    volatile uint32_t *usart_rdr = (volatile uint32_t *)(0x40013800 + 0x24);


    while ((*usart_isr & (1 << 5)) == 0);

    return (char)(*usart_rdr & 0xFF);
}



