NAME    = libasm.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
NASM    = nasm
NASMFLAGS= -Wall -Werror
NASM_FORMAT = elf64

SRCS_S  = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJS    = $(SRCS_S:.s=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.s
	$(NASM) -f $(NASM_FORMAT) $(NASMFLAGS) $< -o $@

test: $(NAME) main.o
	$(CC) $(CFLAGS) main.o -L. -lasm -o test

main.o: main.c libasm.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f $(OBJS) main.o

fclean: clean
	rm -f $(NAME) test

re: fclean all

.PHONY: all clean fclean re test
