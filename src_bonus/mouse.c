#include "cub3d.h"

static int	mouse_rotation(int x, int y, t_game *g)
{
	int		delta_x;
	double	angle;
	double	oldplane_x;
	double	olddir_x;

	(void)y;
	delta_x = x - g->win_w / 2;
	if (delta_x != 0)
	{
		angle = delta_x * MOUSE_SENSITIVITY;
		olddir_x = g->dir_x;
		g->dir_x = g->dir_x * cos(angle) - g->dir_y * sin(angle);
		g->dir_y = olddir_x * sin(angle) + g->dir_y * cos(angle);
		oldplane_x = g->plane_x;
		g->plane_x = g->plane_x * cos(angle) - g->plane_y * sin(angle);
		g->plane_y = oldplane_x * sin(angle) + g->plane_y * cos(angle);
		mlx_mouse_move(g->mlx, g->win, g->win_w / 2, g->win_h / 2);
	}
	return (0);
}

void	mouse_controls(t_game *g)
{
	mlx_mouse_hide(g->mlx, g->win);
	mlx_mouse_move(g->mlx, g->win, g->win_w / 2, g->win_h / 2);
	mlx_hook(g->win, 6, 1L << 6, mouse_rotation, g);
}
