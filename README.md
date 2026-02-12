# anderOS 🚀

**A custom operating system built from scratch**, created by Brenninho123 for fun and learning purposes.  
This project explores the fundamentals of operating system development using Assembly and C.

---

## 🧠 About

anderOS is a **real bootable OS** that starts from a simple BIOS bootloader and evolves into a minimal kernel capable of displaying text on the screen and preparing the environment for future features like a terminal and graphical interface.

This repository is intended as a practical learning example for anyone interested in **OS development (osdev)**.

---

## ✨ Current Features

- 🌟 Assembly bootloader that displays a startup message  
- 🚀 Minimal kernel structure prepared for future expansion  
- 🧩 Project layout designed for continuous evolution  

---

## 🛠️ Technologies

The project uses traditional OS development tools:

- 🧠 **Assembly (NASM)** — bootloader  
- 💻 **C** — kernel development  
- 🧰 **QEMU** — virtual machine testing  
- 🛠️ **GCC & LD** — compilation and linking  

---

## 💡 Build & Run

### 🔧 Requirements

Make sure you have installed:

- `nasm`
- `gcc`
- `ld`
- `qemu`

On Linux / WSL:

```sh
sudo apt install nasm gcc build-essential qemu