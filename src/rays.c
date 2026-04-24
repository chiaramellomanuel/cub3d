#include "cub3d.h"

static void	dda_algoritm(t_game *g, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->sidedist_x < r->sidedist_y)
		{
			r->sidedist_x += r->deltadist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->sidedist_y += r->deltadist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_x >= (int)g->map_w
			|| r->map_y < 0 || r->map_y >= (int)g->map_h)
		{
			ft_printf("Error\n");
			break ;
		}
		if (g->map[r->map_y][r->map_x] == 1)
			r->hit = 1;
	}
}

static void	calculate_init_step_sidedist(t_game *g, t_ray *r)
{
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->sidedist_x = (g->pos_x - r->map_x) * r->deltadist_x;
	}
	else
	{
		r->step_x = 1;
		r->sidedist_x = (r->map_x + 1.0 - g->pos_x) * r->deltadist_x;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->sidedist_y = (g->pos_y - r->map_y) * r->deltadist_y;
	}
	else
	{
		r->step_y = 1;
		r->sidedist_y = (r->map_y + 1.0 - g->pos_y) * r->deltadist_y;
	}
}

static void	init_ray(t_game *g, t_ray *r, int x)
{
	r->camera_x = 2 * x / (double)g->win_w -1;
	r->raydir_x = g->dir_x + g->plane_x * r->camera_x;
	if (r->raydir_x == 0)
		r->deltadist_x = __DBL_MAX__;
	else
		r->deltadist_x = fabs(1 / r->raydir_x);
	r->raydir_y = g->dir_y + g->plane_y * r->camera_x;
	if (r->raydir_y == 0)
		r->deltadist_y = __DBL_MAX__;
	else
		r->deltadist_y = fabs(1 / r->raydir_y);
	r->map_x = (int)g->pos_x;
	r->map_y = (int)g->pos_y;
	calculate_init_step_sidedist(g, r);
}

static void	find_wall_parameters(t_game *g, t_ray *r)
{
	if (r->side == 0)
		r->walldist = r->sidedist_x - r->deltadist_x;
	else
		r->walldist = r->sidedist_y - r->deltadist_y;
	if (r->walldist <= 0 || isnan(r->walldist))
		r->walldist = 0.0001;
	if (r->side == 0)
		r->wall_x = g->pos_y + r->walldist * r->raydir_y;
	else
		r->wall_x = g->pos_x + r->walldist * r->raydir_x;
	r->wall_x -= floor(r->wall_x);
	r->text_x = 0;
	r->height = (int)(g->win_h / r->walldist);
	r->draw_start = -r->height / 2 + g->win_h / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->height / 2 + g->win_h / 2;
	if (r->draw_end >= g->win_h)
		r->draw_end = g->win_h - 1;
	r->text_x = (int)(r->wall_x * (double)g->texture[g->current_text_id].width);
	if ((r->side == 0 && r->raydir_x > 0) || (r->side == 1 && r->raydir_y < 0))
		r->text_x = g->texture[g->current_text_id].width - r->text_x - 1;
}

void	cast_ray(t_game *g, int x)
{
	t_ray	r;

	init_struct_ray(&r);
	init_ray(g, &r, x);
	dda_algoritm(g, &r);
	find_id_texture(g, r.side, r.raydir_x, r.raydir_y);
	find_wall_parameters(g, &r);
	draw_map(g, &r, x);
}

/* cast_ray is called inside a while loop (from x = 0 to WIN_W):
for each column of the screen, a ray is initialized.
For each ray, we apply the DDA algorithm to find the wall it hits,
so we can calculate its height relative to the player's position for perspective.
Finally, we draw the vertical column at x based on the acquired data. */
