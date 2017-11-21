#include "lem_in.h"

int	main(void)
{
	int			err;
	t_lem_in	lem_in;
	int			len;

	init(&lem_in);
	lem_in.verbose = 1;
	err = parse_input(&lem_in);
	if (err == 1)
	{
		ft_putstr("Error\n");
		clean(&lem_in);
	}
	else
	{
		solve_bfs(&lem_in);
		print_room_list(&(lem_in.rooms));
		ft_putstr("Start: ");
		print_room(lem_in.start);
		ft_putstr("End: ");
		print_room(lem_in.end);
		ft_putstr("\n");
		ft_putstr("Shortest path:\n");
		len = print_path_from_end(lem_in.end);
		ft_putstr("Path length: ");
		ft_putnbr(len);
		ft_putstr("\n");
		clean(&lem_in);
	}		
}
