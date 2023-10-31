# OS Memory Management Project

## Overview
This project is a memory management application developed for the Operating Systems course at Universidade do Vale do Itajaí (UNIVALI), created by [Alexandre Debortoli de Souza](https://github.com/alexandredebortoli) and [Bernar Duarte Freitas](https://github.com/bernarDuarte). The course was instructed by Professor Felipe Viel.

## Description
This application is designed to convert virtual addresses to page numbers and offsets, allowing you to read data from memory files based on these addresses. It is written in C++ and supports both normal and two-level pagination for 32-bit virtual addresses.

## Features
- Converts virtual addresses to page numbers and offsets.
- Supports both normal and two-level pagination for 32-bit virtual addresses.
- Reads data from memory files using the converted addresses.

## Usage
1. Clone the repository.
    ``` bash
    git clone https://github.com/alexandredebortoli/os-memory-management-project.git
    ```

2. Compile the C++ code using your preferred C++ compiler (e.g., `g++`).
    ``` bash
    g++ -std=c++11 main.cpp -o main.exe
    ```
  
3. Run the compiled executable.
    - Run the following to run and use the virtual addresses passed through the arguments.
      ``` bash
      ./main.exe 19986
      ```
      > You may pass as many arguments as you want.
  
    - Run the following to run and use the virtual addresses specified in the `addresses.txt` file.
      ``` bash
      ./main.exe
      ```

## Contributors
- [Alexandre Debortoli de Souza](https://github.com/alexandredebortoli)
  - Major: Computer Engineering
- [Bernar Duarte Freitas](https://github.com/bernarDuarte)
  - Major: Computer Science

## Instructor
- Professor Felipe Viel

## License
This code is not open to the public and is intended for private or authorized use only. Unauthorized use, distribution, or modification is strictly prohibited.
