# ft_printf

A custom implementation of standard libc `printf` written for the 42 Network core curriculum.

The project focuses on variadic arguments in C (`<stdarg.h>`), format string parsing, and handling numeric conversions recursively without heap allocations or static buffers.

## Supported Conversions

The implementation handles the mandatory conversions required by the 42 subject:

| Specifier | Description | Behavior |
|:---|:---|:---|
| `%c` | Character | Writes a single unsigned char |
| `%s` | String | Writes a null-terminated string; outputs `(null)` if pointer is NULL |
| `%p` | Pointer | Writes memory address in lowercase hex with `0x` prefix; outputs `(nil)` if NULL |
| `%d` / `%i` | Signed integer | Base-10 signed integer; handles `INT_MIN` cleanly via 64-bit promotion |
| `%u` | Unsigned integer | Base-10 unsigned decimal |
| `%x` | Hexadecimal (lower) | Base-16 lowercase (`0123456789abcdef`) |
| `%X` | Hexadecimal (upper) | Base-16 uppercase (`0123456789ABCDEF`) |
| `%%` | Percent literal | Writes a single `%` character |

## Architecture Notes

- **Parsing loop:** The format string is read sequentially. Regular characters are written directly to stdout via `write`. When a `%` is encountered, the specifier is evaluated and dispatched to the corresponding helper.
- **Variadic arguments:** Uses `va_start`, `va_arg`, and `va_end` to step through the argument list based on the format tokens.
- **Recursive output:** Numbers (`%d`, `%i`, `%u`, `%x`, `%X`) are converted recursively to write digits in natural order during stack unwinding. No dynamic memory is allocated, eliminating memory leak paths entirely.
- **Return value:** Returns the total count of characters written to stdout, or `-1` on format error.

## Compilation

The project builds as a static library `libftprintf.a`.

```bash
make
```

Additional rules:
- `make clean`: Removes intermediate object files (`.o`)
- `make fclean`: Removes object files and `libftprintf.a`
- `make re`: Performs a clean rebuild

## Usage

Include `ft_printf.h` and link the compiled library:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hex: %x, Pointer: %p\n", 255, main);
    return (0);
}
```

```bash
cc main.c -L. -lftprintf -o test
./test
```

## Norminette

All source files adhere to 42's Norminette (v4) requirements.
