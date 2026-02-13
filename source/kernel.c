#include "utils.h"
#include "logo.h"
#include "terminal.h"

#include "os/system.h"
#include "os/memory.h"
#include "os/io.h"
#include "os/interrupts/idt.h"

#define KERNEL_COLOR 0x0F

/* =====================================
   Estado global do kernel
===================================== */

static int kernel_running = 1;
static unsigned long uptime_ticks = 0;

/* =====================================
   Hooks chamados pelas IRQs
===================================== */

// Chamado pelo timer (IRQ0)
void kernel_timer_tick() {
    uptime_ticks++;
}

// Futuro: scheduler vai rodar aqui
void kernel_scheduler() {
    // reservado para multitarefa futura
}

/* =====================================
   Inicialização de subsistemas
===================================== */

static void kernel_boot_banner() {
    clear_screen();

    print_color("Booting anderOS 32-bit kernel...\n", KERNEL_COLOR);
    os_delay(50);

    show_logo();
    print("\n", KERNEL_COLOR);

    os_print_info();
    print("\n", KERNEL_COLOR);
}

static void kernel_init_interrupts() {
    print_color("Initializing IDT and IRQs...\n", KERNEL_COLOR);
    idt_init();
    print_color("Interrupt system online.\n\n", KERNEL_COLOR);
}

static void kernel_init_terminal() {
    print_color("Starting terminal subsystem...\n", KERNEL_COLOR);
    terminal_init();
    print_color("Terminal ready.\n\n", KERNEL_COLOR);
}

static void kernel_show_prompt() {
    print("> ", KERNEL_COLOR);
}

/* =====================================
   Loop principal do kernel
===================================== */

static void kernel_idle() {
    // instrução HLT reduz uso de CPU até próxima interrupção
    __asm__ volatile("hlt");
}

void kernel_main() {
    /* --- Fase de boot --- */
    kernel_boot_banner();

    /* --- Inicializações críticas --- */
    kernel_init_interrupts();
    kernel_init_terminal();

    print_color("System initialized successfully.\n", KERNEL_COLOR);
    print_color("Type 'help' to list commands.\n\n", KERNEL_COLOR);

    kernel_show_prompt();

    /* --- Loop principal --- */
    while (kernel_running) {

        // executa tarefas de baixo nível
        kernel_scheduler();

        // entra em modo idle até próxima IRQ
        kernel_idle();
    }

    /* Nunca deveria chegar aqui */
    print_color("\nKernel halted.", KERNEL_COLOR);
    while (1) {
        __asm__ volatile("hlt");
    }
}