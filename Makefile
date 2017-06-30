CC = gcc

ifeq ($(DEBUG),yes)
    CFLAGS = -Wall -Wextra -O0 -g -fsanitize=address
else
    CFLAGS = -Wall -Wextra -O2
endif

NAME = lem-in

SRC_UTIL = ft.c get_next_byte.c slist.c get_next_line.c
SRC = $(SRC_UTIL) room_stack.c parse_input.c test.c
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJDIR = obj

VPATH = util src
IFLAGS = -Iutil -Isrc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o: %.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $^ -o $@ $(IFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
