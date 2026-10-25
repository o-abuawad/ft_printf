# ft_printf

<p align="center">
  <img src="https://img.shields.io/badge/Score-100%2F100-success?style=for-the-badge&logo=42" alt="Score 100/100" />
  <img src="https://img.shields.io/badge/Campus-42%20Amman-000000?style=for-the-badge&logo=42" alt="42 Amman" />
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c" alt="Language C" />
  <img src="https://img.shields.io/badge/Norminette-v4%20OK-brightgreen?style=for-the-badge" alt="Norminette OK" />
</p>

*This project was created as part of the 42 Network Core Curriculum by [oabu-awa](https://github.com/o-abuawad).*

---

## 📌 Overview

`ft_printf` is a custom implementation of standard libc `printf`. The goal of this project is to explore and master **variadic functions** in C using `<stdarg.h>`, string parsing, base conversion, recursive number formatting, and careful output counting without relying on dynamic heap allocation or buffer management.

---

## 🚀 Supported Conversions

`ft_printf` handles all required mandatory conversions conforming to the behavior of standard `printf`:

| Specifier | Description | Example / Output |
| :---: | :--- | :--- |
| `%c` | Prints a single character | `'A'` |
| `%s` | Prints a string | `"Hello, 42!"` *(outputs `(null)` if pointer is `NULL`)* |
| `%p` | Prints a pointer address in lowercase hex | `0x7ffeefbff568` *(outputs `(nil)` if pointer is `NULL`)* |
| `%d` | Prints a signed decimal integer | `-42`, `1337` |
| `%i` | Prints a signed base-10 integer | `-42`, `1337` |
| `%u` | Prints an unsigned decimal integer | `4294967295` |
| `%x` | Prints a number in lowercase hexadecimal | `2a`, `deadbeef` |
| `%X` | Prints a number in uppercase hexadecimal | `2A`, `DEADBEEF` |
| `%%` | Prints a literal percent character | `%` |

---

## 🧠 Design and Implementation

### 1. Format String Parsing
The format string is traversed character by character. Plain characters are output directly using `write(1, &c, 1)`. When a `%` token is encountered:
- The next character is read and evaluated by `check_val()`.
- If an unknown specifier or trailing `%` is provided, it safely returns `-1`.
- Total characters printed are accumulated and returned upon completion.

### 2. Variadic Arguments
Argument retrieval is managed using the `<stdarg.h>` macros:
- `va_start(arg, format)` initializes the variadic list.
- `va_arg(arg, type)` fetches the next argument cast to its designated type (`int`, `char *`, `unsigned int`, `void *`).
- `va_end(arg)` cleanly tears down the argument list.

### 3. Recursive Number Output (Zero Dynamic Memory Leaks)
Rather than allocating memory on the heap with `malloc()` or utilizing static buffers:
- Decimal integers (`%d`, `%i`, `%u`) and hexadecimal values (`%x`, `%X`, `%p`) are printed **recursively**.
- By dividing by the base (10 or 16) until reaching the base case, digits are written in correct forward order during call stack unwinding.
- Signed integers are cast to `long` before negation, completely avoiding two's complement integer overflow on `INT_MIN` (`-2147483648`).
- Since heap allocation is never used, memory leaks are fundamentally impossible.

---

## 🛠️ Instructions

### Compilation

Compile the static library from the project directory:

```bash
make
```

This compiles all source files with `-Wall -Wextra -Werror` and archives them into:
```
libftprintf.a
```

### Makefile Rules

| Rule | Description |
| :--- | :--- |
| `make` / `make all` | Compiles the source files and creates `libftprintf.a` |
| `make clean` | Removes compiled `.o` object files |
| `make fclean` | Removes `.o` object files and `libftprintf.a` |
| `make re` | Recompiles the library from scratch |

---

## 💻 Usage Example

Include the header in your C code:

```c
#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("Hello %s! Number: %d, Hex: %x, Ptr: %p\n", "42", 42, 255, main);
    ft_printf("Printed %d characters\n", count);
    return (0);
}
```

Compile and link against `libftprintf.a`:

```bash
cc main.c -L. -lftprintf -o program
./program
```

---

## 📖 Resources

- `man 3 printf`
- `man 3 stdarg`
- The Linux Programmer's Manual
- [42 Norminette Standard](https://github.com/42School/norminette)
