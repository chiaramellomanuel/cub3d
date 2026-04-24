#include "cub3d.h"

static void	init_double_struct_ray(t_ray *r)
{
	r->wall_x = 0.0;
	r->floor_wall_x = 0.0;
	r->floor_wall_y = 0.0;
	r->camera_x = 0.0;
	r->raydir_x = 0.0;
	r->raydir_y = 0.0;
	r->sidedist_x = 0.0;
	r->sidedist_y = 0.0;
	r->deltadist_x = 0.0;
	r->deltadist_y = 0.0;
	r->walldist = 0.0;
}

void	init_struct_ray(t_ray *r)
{
	r->text_x = 0;
	r->text_y = 0;
	r->hit = 0;
	r->side = 0;
	r->map_x = 0;
	r->map_y = 0;
	r->step_x = 0;
	r->step_y = 0;
	r->height = 0;
	r->draw_start = 0;
	r->draw_end = 0;
	r->floor_tex_x = 0;
	r->floor_tex_y = 0;
	r->ceil_tex_x = 0;
	r->ceil_tex_y = 0;
	init_double_struct_ray(r);
}

void	init_struct_keys(t_game *g)
{
	t_keys	key;

	key.a = 0;
	key.d = 0;
	key.left = 0;
	key.right = 0;
	key.s = 0;
	key.w = 0;
	g->keys = key;
}

static void	init_game_direction(t_game *g, t_texture *txt)
{
	g->dir_x = 0;
	g->dir_y = 0;
	g->plane_x = 0;
	g->plane_y = 0;
	if (!ft_strcmp(txt->direction, "N"))
	{
		g->dir_y = -1;
		g->plane_x = 0.66;
	}
	else if (!ft_strcmp(txt->direction, "S"))
	{
		g->dir_y = 1;
		g->plane_x = -0.66;
	}
	else if (!ft_strcmp(txt->direction, "W"))
	{
		g->dir_x = -1;
		g->plane_y = -0.66;
	}
	else if (!ft_strcmp(txt->direction, "E"))
	{
		g->dir_x = 1;
		g->plane_y = 0.66;
	}
}

void	init_struct_game(t_game *g, t_texture *txt)
{
	if (WIN_W > 1920)
		g->win_w = 1920;
	else
		g->win_w = WIN_W;
	if (WIN_H > 1080)
		g->win_h = 1080;
	else
		g->win_h = WIN_H;
	g->pos_x = txt->pos_x;
	g->pos_y = txt->pos_y;
	init_game_direction(g, txt);
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, g->win_w,
			g->win_h, "cub3d - base raycasting");
	g->img.img = mlx_new_image(g->mlx,
			g->win_w, g->win_h);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	init_struct_keys(g);
	g->use_ceil_text = TRUE;
	g->use_floor_text = TRUE;
	init_texture(g, txt);
	g->current_text_id = 0;
	g->txt = txt;
}
