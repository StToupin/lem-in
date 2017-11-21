#include "lem_in.h"

int	main(void)
{
	int			err;
	t_lem_in	lem_in;

	init(&lem_in);
	err = parse_input(&lem_in);
	if (err == 1)
	{
		ft_putstr("Error\n");
		clean(&lem_in);
	}
	else
	{
		solve_BFS(&lem_in);
		print_room_list(&(lem_in.rooms));
		ft_putstr("Start: ");
		print_room(lem_in.start);
		ft_putstr("End: ");
		print_room(lem_in.end);
	}
}
