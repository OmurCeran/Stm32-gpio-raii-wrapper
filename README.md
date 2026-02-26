Harika bir özet oldu. İki farklı projenin (Temel C++ ve Gelişmiş RTOS/DMA) ortak yönlerini birleştiren, teknik derinliği yüksek ve profesyonel bir **README.md** hazırladım. Bu yapıyı doğrudan GitHub depona kopyalayıp yapıştırabilirsin.

---

# STM32 Modern C++ & RTOS Architecture Suite

This repository demonstrates a **Modern C++ (C++17)** and **Real-Time OS** approach to embedded development on the **STM32F4 Discovery** board. It bridges the gap between high-level software patterns and low-level hardware control, moving away from traditional procedural C-style development.

## 🚀 Key Features

* **Modern C++17:** Leverages `std::unique_ptr`, `std::vector`, and `auto` to ensure memory safety and zero-cost abstractions.
* **RAII Hardware Wrappers:** Resource management is handled via **RAII (Resource Acquisition Is Initialization)**; peripherals like GPIO and UART are initialized in constructors and safely managed throughout their lifecycle.
* **Asynchronous DMA Architecture:** High-performance communication using **Circular DMA** and **UART Idle Line Detection** for non-blocking, variable-length data transfers.
* **RTOS Integration:** Fully synchronized with **FreeRTOS**, using binary semaphores to eliminate CPU-heavy polling and transition tasks into power-efficient blocked states during hardware I/O.
* **Hardware Agnostic Logic:** Abstract interfaces (`ILed`, `IComm`) allow application logic to remain decoupled from the specific STM32 HAL implementation.

## 🛠️ Tech Stack

* **Hardware:** STM32F407VG (Discovery Board)
* **Language:** C++17 / C11
* **Operating System:** FreeRTOS
* **Drivers:** STM32 HAL (Hardware Abstraction Layer)
* **Build System:** CMake & Ninja/Make
* **Debugger:** OpenOCD / ST-Link / Cortex-Debug

## 📂 Project Structure

### 1. Modern C++ Base Module

* `Core/Inc/ILed.hpp`: Abstract interface for hardware-independent LED control.
* `Core/Inc/Stm32Led.hpp`: Concrete implementation using **RAII** to wrap GPIO operations.
* `Core/Src/app_main.cpp`: Entry point demonstrating **Smart Pointer** usage for peripheral management.

### 2. Advanced RTOS & DMA Module

* `Core/Inc/IComm.hpp`: Interface for asynchronous communication protocols.
* `Core/Src/UartCommunication.cpp`: Advanced UART driver featuring **Ring Buffer** and **DMA Event Callbacks**.
* `Core/Src/main_cpp.cpp`: Bridging C and C++ worlds, managing RTOS task creation.

## 📦 How to Build

1. Open the project folder in **VS Code**.
2. Ensure **ARM GNU Toolchain**, **CMake**, and **Ninja** are installed.
3. Press `Ctrl+Shift+P` and select `CMake: Configure` (Select your ARM GCC toolchain).
4. Press `F7` (or use the Build button) to compile the project.
5. Press `F5` to flash the firmware and start a live debugging session.

---

*Developed by Ömür Ceran to explore the intersection of modern software engineering and high-performance embedded systems.*

---
