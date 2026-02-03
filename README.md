# STM32 Modern C++ Base Project

This repository demonstrates a **Modern C++ (C++17)** approach to embedded development on the **STM32F4 Discovery** board.

Instead of the traditional C-style HAL usage, this project utilizes **RAII (Resource Acquisition Is Initialization)** and **Object-Oriented Programming** principles to create safer and cleaner hardware abstractions.

## 🚀 Key Features

* **Modern C++17:** Uses `std::unique_ptr`, `std::vector`, and `auto` for memory safety and readability.
* **RAII Wrapper:** GPIO pins are initialized within the constructor and cleaned up (if necessary) in the destructor.
* **Polymorphism:** An abstract `ILed` interface allows for hardware-agnostic application logic.
* **Build System:** Fully configured **CMake** setup, replacing proprietary IDE project files.
* **Toolchain:** Designed for **VS Code** with Cortex-Debug and CMake Tools extensions.

## 🛠️ Tech Stack

* **Hardware:** STM32F407VG (Discovery Board)
* **Language:** C++17 / C11
* **Drivers:** STM32 HAL (Hardware Abstraction Layer)
* **Build:** CMake & Ninja/Make
* **Debugger:** OpenOCD / ST-Link

## 📂 Project Structure

* `Core/Inc/ILed.hpp`: Abstract interface for LED control.
* `Core/Inc/Stm32Led.hpp`: Concrete implementation using HAL and RAII.
* `Core/Src/app_main.cpp`: Main C++ application entry point using smart pointers.
* `CMakeLists.txt`: Build configuration integrating CubeMX generation with custom C++ logic.

## 📦 How to Build

1.  Open the project folder in **VS Code**.
2.  Ensure **ARM GNU Toolchain** and **CMake** are installed.
3.  Press `Ctrl+Shift+P` and select `CMake: Configure`.
4.  Press `F7` (or Build button) to compile.
5.  Press `F5` to flash and debug on the target.

---
*Developed to explore the intersection of high-level software patterns and low-level hardware control.*
