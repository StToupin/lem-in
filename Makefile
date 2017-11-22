CC = gcc

ifeq ($(DEBUG),yes)
    CFLAGS = -Wall -Wextra -O0 -g -fsanitize=address
else
    CFLAGS = -Wall -Wextra -O2
endif

NAME = lem-in

SRC_UTIL = ft.c slist.c get_next_common.c get_next_line.c write_next.c
SRC = $(SRC_UTIL) room_list.c debug.c build_map.c parse_input.c solver.c move_ants.c lem_in.c
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
