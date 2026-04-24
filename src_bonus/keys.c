#include "cub3d.h"
#include "utility.h"

int	key_press(int key, t_game *g)
{
	if (key == KEY_ESC)
		close_window(g);
	else if (key == KEY_LEFT)
		g->keys.left = 1;
	else if (key == KEY_RIGHT)
		g->keys.right = 1;
	else if (key == KEY_W)
		g->keys.w = 1;
	else if (key == KEY_S)
		g->keys.s = 1;
	else if (key == KEY_A)
		g->keys.a = 1;
	else if (key == KEY_D)
		g->keys.d = 1;
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key == KEY_LEFT)
		g->keys.left = 0;
	else if (key == KEY_RIGHT)
		g->keys.right = 0;
	else if (key == KEY_W)
		g->keys.w = 0;
	else if (key == KEY_S)
		g->keys.s = 0;
	else if (key == KEY_A)
		g->keys.a = 0;
	else if (key == KEY_D)
		g->keys.d = 0;
	return (0);
}

int	close_window(t_game *g)
{
	mlx_destroy_image(g->mlx, g->img.img);
	mlx_destroy_window(g->mlx, g->win);
	free_struct(g->txt, g);
	exit(0);
}
