#include "idt.h"
#include "../io.h"

#define IDT_ENTRIES 256

struct IDTEntry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));

struct IDTPtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern void isr0();
extern void irq1();
extern void irq0();

static struct IDTEntry idt[IDT_ENTRIES];
static struct IDTPtr idt_ptr;

static void idt_set_gate(int n, uint32_t handler) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].zero = 0;
    idt[n].type_attr = 0x8E;
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_init() {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    for (int i = 0; i < IDT_ENTRIES; i++)
        idt_set_gate(i, (uint32_t)isr0);

    idt_set_gate(32, (uint32_t)irq0); // timer
    idt_set_gate(33, (uint32_t)irq1); // keyboard

    __asm__ volatile("lidt %0" : : "m"(idt_ptr));
    __asm__ volatile("sti");
}