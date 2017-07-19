#include "lem_in.h"

int main(void)
{
	t_lem_in	lem_in;

	init(&lem_in);
	parse_input(&lem_in);
	print_room_stack(&(lem_in.rooms));
	printf("Start: ");
	print_room(lem_in.start);
	printf("End: ");
	print_room(lem_in.start);
}
