NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

REM = rm -f
AR = ar rcs

SRCS = ft_putchar.c \
	   ft_putstr.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(REM) $(OBJS)

fclean: clean
	$(REM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
