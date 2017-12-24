CC = gcc

ifeq ($(DEBUG),yes)
    CFLAGS = -Wall -Wextra -O0 -g -fsanitize=address
else
    CFLAGS = -Wall -Wextra -Ofast -fomit-frame-pointer
endif

NAME = lem-in

SRC_HASHMAP = hashmap_init_crc_0.c hashmap_init_crc_1.c hashmap_init_crc_2.c \
		hashmap_init.c hashmap_crc32.c hashmap.c hashmap_op.c
SRC_UTIL = ft.c slist.c get_next_common.c get_next_line.c write_next.c $(SRC_HASHMAP)
SRC = $(SRC_UTIL) room_list.c debug.c build_map.c parse_line.c parse_input.c solver.c move_ants.c lem_in.c
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJDIR = obj

VPATH = util util/hashmap src
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
