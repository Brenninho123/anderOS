# anderOS 🚀

**A custom 32-bit protected mode operating system built from scratch**, created by Brenninho123 as a learning and experimental project.  
This project explores the fundamentals of operating system development using **Assembly** and **C**, gradually building a minimal but expandable kernel.

---

## 🧠 About

anderOS is a **real bootable OS** starting from a simple BIOS bootloader, evolving into a **modular 32-bit kernel** capable of:  

- Displaying text on the screen  
- Handling keyboard input  
- Running a custom terminal with commands (`help`, `clear`, `version`, `reboot`, `info`)  
- Preparing the system for future features like memory management, drivers, and graphical interface  

This project is intended as a **hands-on OS development learning platform (osdev)** for hobbyists and students.

---

## ✨ Features

- 🌟 **Assembly bootloader** with Protected Mode initialization  
- 🚀 **32-bit protected mode kernel** with modular architecture  
- 🖥️ **Custom terminal** supporting multiple commands  
- 🔧 **Modular source layout** in `source/` and `source/os/` for scalability  
- 🧩 Basic **memory and I/O utilities** for system programming  
- 🛠️ Fully compatible with **QEMU** for safe testing  

---

## 🗂️ Project Structure

```
anderOS/
├── boot.asm           # Bootloader (Protected Mode ready)
├── linker.ld          # Linker script
├── build.bat          # Build script for Windows
├── anderOS.bin        # Final OS image
└── source/
    ├── kernel.c       # Kernel main loop & terminal integration
    ├── terminal.c     # Terminal commands
    ├── logo.c         # ASCII logo
    ├── keyboard.c     # Keyboard input
    ├── utils.c        # Print, scroll, string functions
    └── os/           # Core OS utilities
        ├── system.c   # OS commands: reboot, info, delay
        ├── memory.c   # Basic memory functions: memset, memcpy
        └── io.c       # Port I/O abstraction
```

---

## 🛠️ Technologies & Tools

- 🧠 **Assembly (NASM)** — bootloader and low-level system initialization  
- 💻 **C** — kernel and OS logic development  
- 🧰 **QEMU** — virtual machine for testing OS safely  
- 🛠️ **GCC & LD** — compiling and linking 32-bit kernel modules  
- 💡 Modular project structure to enable **future expansion** (drivers, GUI, filesystem)

---

## 💡 Build & Run

### 🔧 Requirements

Make sure you have installed:

- `nasm`  
- `gcc` (with `-m32` support)  
- `ld` (linker)  
- `qemu-system-x86_64`  

On **Linux / WSL**:

```sh
sudo apt install nasm gcc build-essential qemu
```

On **Windows**, make sure your PATH includes NASM, GCC (32-bit), LD, and QEMU executables.

---

### ⚡ Build

```bat
build.bat
```

This will:

1. Compile all `source/` modules as 32-bit object files  
2. Link kernel with `linker.ld`  
3. Assemble the bootloader (`boot.asm`)  
4. Combine bootloader + kernel into `anderOS.bin`  
5. Launch the OS in QEMU for testing  

---

### 🖥️ Terminal Commands

- `help` — Show all available commands  
- `clear` — Clear the screen  
- `version` — Show current OS version  
- `reboot` — Restart the OS  
- `info` — Display OS info (author, status, terminal features)  

---

## 💡 Future Plans

- Implement **basic memory management** (heap, stack, paging)  
- Add **drivers** (keyboard, timer, display, storage)  
- Build a **graphical interface** and window system  
- Create a **simple filesystem**  
- Expand **terminal commands** and modular OS features  

---

## 📖 Learning Resources

- [OSDev Wiki](https://wiki.osdev.org) — Core OS development guide  
- [JamesM’s kernel development tutorial](http://www.jamesmolloy.co.uk/tutorial_html/)  
- [Low-level C and Assembly programming](https://wiki.osdev.org)