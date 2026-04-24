#include "cub3d.h"

static void	draw_floor(t_game *g, t_ray *r, int x, int y)
{
	int		color;
	double	weight;
	double	floor_x;
	double	floor_y;
	double	camera_dist;

	camera_dist = g->win_h / (2.0 * y - g->win_h);
	find_floor_position_on_wallbase(r);
	weight = camera_dist / r->walldist;
	floor_x = weight * r->floor_wall_x + (1.0 - weight) * g->pos_x;
	floor_y = weight * r->floor_wall_y + (1.0 - weight) * g->pos_y;
	r->floor_tex_x = (int)(floor_x * g->texture[FLOOR_ID].width)
		% g->texture[FLOOR_ID].width;
	if (r->floor_tex_x < 0)
		r->floor_tex_x += g->texture[FLOOR_ID].width;
	r->floor_tex_y = (int)(floor_y * g->texture[FLOOR_ID].height)
		% g->texture[FLOOR_ID].height;
	if (r->floor_tex_y < 0)
		r->floor_tex_y += g->texture[FLOOR_ID].height;
	color = *(int *)(g->texture[FLOOR_ID].addr
			+ (r->floor_tex_y * g->texture[FLOOR_ID].line_len
				+ r->floor_tex_x * (g->texture[FLOOR_ID].bpp / 8)));
	my_mlx_pixel_put(g, x, y, color);
}

static void	draw_ceil(t_game *g, t_ray *r, int x, int y)
{
	int		color;
	double	floor_x;
	double	floor_y;
	double	weight;
	double	camera_dist;

	camera_dist = g->win_h / (g->win_h - 2.0 * y);
	find_floor_position_on_wallbase(r);
	weight = camera_dist / r->walldist;
	floor_x = weight * r->floor_wall_x + (1.0 - weight) * g->pos_x;
	floor_y = weight * r->floor_wall_y + (1.0 - weight) * g->pos_y;
	r->ceil_tex_x = (int)(floor_x * g->texture[CEIL_ID].width)
		% g->texture[CEIL_ID].width;
	if (r->ceil_tex_x < 0)
		r->ceil_tex_x += g->texture[CEIL_ID].width;
	r->ceil_tex_y = (int)(floor_y * g->texture[CEIL_ID].height)
		% g->texture[CEIL_ID].height;
	if (r->ceil_tex_y < 0)
		r->ceil_tex_y += g->texture[CEIL_ID].height;
	color = *(int *)(g->texture[CEIL_ID].addr
			+ (r->ceil_tex_y * g->texture[CEIL_ID].line_len
				+ r->ceil_tex_x * (g->texture[CEIL_ID].bpp / 8)));
	my_mlx_pixel_put(g, x, y, color);
}

static int	draw_wall(t_game *g, t_ray *r, int x, int y)
{
	int		color;
	int		text_y;
	double	step;
	double	text_pos;

	step = 1.0 * g->texture[g->current_text_id].height / r->height;
	text_pos = (r->draw_start - g->win_h / 2 + r->height / 2) * step;
	while (y <= r->draw_end)
	{
		text_y = (int)text_pos;
		if (text_y < 0)
			text_y = 0;
		if (text_y >= g->texture[g->current_text_id].height)
			text_y = g->texture[g->current_text_id].height - 1;
		color = *(int *)(g->texture[g->current_text_id].addr
				+ (text_y * g->texture[g->current_text_id].line_len
					+ r->text_x * (g->texture[g->current_text_id].bpp / 8)));
		my_mlx_pixel_put(g, x, y++, color);
		text_pos += step;
	}
	return (y);
}

void	draw_map(t_game *g, t_ray *r, int x)
{
	int		y;

	y = 0;
	while (y < r->draw_start)
	{
		if (!g->use_ceil_text)
			my_mlx_pixel_put(g, x, y++, g->ceil_color);
		else
			draw_ceil(g, r, x, y++);
	}
	y = draw_wall(g, r, x, y);
	while (y < g->win_h)
	{
		if (!g->use_floor_text)
			my_mlx_pixel_put(g, x, y++, g->floor_color);
		else
			draw_floor(g, r, x, y++);
	}
}
