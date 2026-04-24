#include "cub3d.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	t_game		*g;
	t_texture	*txt;

	g = malloc(1 * sizeof(t_game));
	g->map = NULL;
	txt = NULL;
	txt = init_struct(txt, g);
	if (!parsing_start(argc, argv, txt, g))
	{
		free_struct(txt, g);
		return (1);
	}
	init_struct_game(g, txt);
	mlx_loop_hook(g->mlx, render, g);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, 17, 0, close_window, g);
	mlx_loop(g->mlx);
	free_struct(txt, g);
	return (0);
}
