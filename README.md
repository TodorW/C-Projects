
---

# ZephyrOS

![ZephyrOS Logo](ZephyrOS.png)

**ZephyrOS** is a lightweight, modular operating system designed and implemented in C. Its focus is on simplicity, efficiency, and scalability. ZephyrOS is built from the ground up, aiming to provide a minimal but flexible foundation for operating system design, kernel development, and system-level programming. It supports basic multitasking, memory management, process scheduling, and file system operations, all of which are essential for modern operating systems.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Technical Details](#technical-details)
- [Development Tools](#development-tools)
- [How to Contribute](#how-to-contribute)
- [License](#license)

---

## Project Overview

ZephyrOS is intended for developers interested in learning or contributing to low-level system software. It is currently a work in progress, with core components like the kernel and shell being developed alongside memory management, process handling, and interrupt systems.

The aim of ZephyrOS is to serve as both an educational project and a foundation for future expansion. It offers a platform where developers can experiment with various kernel features, file systems, and even drivers, while keeping the system modular and lightweight.

### Why "Zephyr"?
The name **Zephyr** reflects the project's philosophy: **lightweight, fast, and efficient**, akin to a gentle breeze. This OS is designed to be minimal yet powerful, much like the wind that’s swift but subtle.

---

## Features

### Core Components
- **Monolithic Kernel**: ZephyrOS uses a monolithic kernel, where core services such as memory management, process scheduling, and hardware I/O are handled in a unified space.
- **Basic Shell**: A command-line interface shell for user interaction, supporting essential commands (`ls`, `cd`, `pwd`, etc.).
- **Memory Management**: Virtual memory management with support for paging and dynamic memory allocation.
- **Process Management**: Basic process scheduling, multitasking, and context switching.
- **File System**: Integration with a minimal file system for data storage and retrieval.
- **Interrupt Handling**: Support for hardware and software interrupts via an Interrupt Descriptor Table (IDT).
- **System Calls**: Provides an API for user-space programs to interact with kernel functions.

### Planned Features
- **Advanced File System Support**: Extensions to support popular file systems like FAT or ext2/3.
- **Networking**: Initial support for networking protocols, including a basic TCP/IP stack.
- **Graphical User Interface (GUI)**: A simple windowing system for a more user-friendly interface (future goal).

---

## Project Structure

The source code for ZephyrOS is organized as follows:

```
/ZephyrOS
│
├── /bootloader        # Bootloader code (e.g., GRUB config, or custom bootloader)
├── /kernel            # Core kernel code (scheduler, memory, system calls, etc.)
├── /drivers           # Device drivers for keyboard, disk, etc.
├── /shell             # Shell and user interaction layer
├── /fs                # File system implementations
├── /lib               # Basic libraries (e.g., libc implementation)
├── /include           # Header files and system-wide definitions
├── /userland          # User-space applications and programs
└── /docs              # Documentation for the OS, API, and internal structures
```

---

## Getting Started

### Prerequisites
To compile and run ZephyrOS, you will need the following tools:
- **Cross Compiler**: GCC or Clang for cross-compiling to your target architecture (e.g., x86).
- **QEMU**: An emulator for running and testing the OS.
- **GRUB**: (Optional) A bootloader for loading your kernel.

### Building ZephyrOS

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/ZephyrOS.git
   cd ZephyrOS
   ```

2. **Configure the cross-compiler** (if not already set up):
   ```bash
   export PREFIX="/usr/local/i386elfgcc"
   export TARGET=i386-elf
   export PATH="$PREFIX/bin:$PATH"
   ```

3. **Build the kernel**:
   ```bash
   make
   ```

4. **Run ZephyrOS on QEMU**:
   ```bash
   qemu-system-i386 -kernel path/to/zephyros-kernel
   ```

### Running ZephyrOS
Once the system boots up, you can interact with the **Zephyr Shell**. Enter basic commands like `ls`, `cd`, and `pwd` to explore the system's directory structure, manage files, or start processes.

---

## Technical Details

### Memory Management
- **Paging**: ZephyrOS implements basic virtual memory management using paging.
- **Dynamic Memory Allocation**: Memory is allocated dynamically through a `malloc()`-like interface in kernel-space.

### Process Management
- **Multitasking**: The kernel supports cooperative multitasking with basic process switching.
- **Scheduler**: A round-robin scheduler is implemented for simplicity, with plans to improve the algorithm.

### Interrupt Handling
- **Interrupt Descriptor Table (IDT)**: The kernel configures the IDT for handling hardware interrupts (e.g., keyboard input, timer).
- **Exception Handling**: Basic exception handling for CPU-generated errors like page faults or division by zero.

### File System
- **Basic File System**: ZephyrOS comes with a minimal file system implementation that supports reading and writing files, with plans to add support for more advanced file systems like FAT and ext2.

---

## Development Tools

To aid development, ZephyrOS leverages the following tools:
- **QEMU**: For system emulation and testing without requiring real hardware.
- **GDB**: For debugging kernel-level code using QEMU’s debugging integration.
- **Make/CMake**: For automating the build process and compiling the kernel, shell, and userland programs.

---

## How to Contribute

Contributions to ZephyrOS are welcome! Whether you want to add new features, fix bugs, or improve documentation, your input will help this project grow.

To contribute:
1. Fork the repository.
2. Create a new branch for your feature/bugfix.
3. Submit a pull request with a detailed description of your changes.

Please make sure to follow the project's coding style and submit tests where applicable.

---

## License

ZephyrOS is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

Thank you for your interest in ZephyrOS! Feel free to open issues or discussions for any questions or suggestions.
