#include "cub3d.h"

static int	draw_walls(t_game *g)
{
	int	x;

	x = 0;
	while (x < g->win_w)
	{
		cast_ray(g, x);
		x++;
	}
	return (0);
}

static void	rotation(t_game *g)
{
	double	angle;
	double	oldplane_x;
	double	olddir_x;

	if (g->keys.left || g->keys.right)
	{
		olddir_x = g->dir_x;
		angle = (g->keys.right - g->keys.left) * ROT_SPEED;
		g->dir_x = g->dir_x * cos(angle) - g->dir_y * sin(angle);
		g->dir_y = olddir_x * sin(angle) + g->dir_y * cos(angle);
		oldplane_x = g->plane_x;
		g->plane_x = g->plane_x * cos(angle) - g->plane_y * sin(angle);
		g->plane_y = oldplane_x * sin(angle) + g->plane_y * cos(angle);
	}
	else
		return ;
}

static void	move_forward_backward(t_game *g)
{
	if (g->keys.w)
	{
		if (g->map[(int)(g->pos_y)][(int)(g->pos_x + g->dir_x
			* (MOVE_SPEED + WALL_MARGIN))] == 0)
			g->pos_x += g->dir_x * MOVE_SPEED;
		if (g->map[(int)(g->pos_y + g->dir_y
				* (MOVE_SPEED + WALL_MARGIN))][(int)(g->pos_x)] == 0)
			g->pos_y += g->dir_y * MOVE_SPEED;
	}
	else if (g->keys.s)
	{
		if (g->map[(int)(g->pos_y)][(int)(g->pos_x - g->dir_x
			* (MOVE_SPEED + WALL_MARGIN))] == 0)
			g->pos_x -= g->dir_x * MOVE_SPEED;
		if (g->map[(int)(g->pos_y - g->dir_y
				* (MOVE_SPEED + WALL_MARGIN))][(int)(g->pos_x)] == 0)
			g->pos_y -= g->dir_y * MOVE_SPEED;
	}
	else
		return ;
}

static void	movements(t_game *g)
{
	move_forward_backward(g);
	if (g->keys.a)
	{
		if (g->map[(int)(g->pos_y)][(int)(g->pos_x - g->plane_x
			* (MOVE_SPEED + WALL_MARGIN))] == 0)
			g->pos_x -= g->plane_x * MOVE_SPEED;
		if (g->map[(int)(g->pos_y - g->plane_y
				* (MOVE_SPEED + WALL_MARGIN))][(int)(g->pos_x)] == 0)
			g->pos_y -= g->plane_y * MOVE_SPEED;
	}
	else if (g->keys.d)
	{
		if (g->map[(int)(g->pos_y)][(int)(g->pos_x + g->plane_x
			* (MOVE_SPEED + WALL_MARGIN))] == 0)
			g->pos_x += g->plane_x * MOVE_SPEED;
		if (g->map[(int)(g->pos_y + g->plane_y
				* (MOVE_SPEED + WALL_MARGIN))][(int)(g->pos_x)] == 0)
			g->pos_y += g->plane_y * MOVE_SPEED;
	}
	else
		return ;
}

int	render(t_game *g)
{
	movements(g);
	rotation(g);
	mlx_destroy_image(g->mlx, g->img.img);
	g->img.img = mlx_new_image(g->mlx, g->win_w, g->win_h);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	draw_walls(g);
	if (g->img.img && g->win)
		mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (0);
}

/* These functions handle the commands for player movement and view direction.
Depending on the command, they update the position and field of view variables
contained in the t_game structure. */
