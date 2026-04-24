#include "cub3d.h"
#include "utility.h"

void	my_mlx_pixel_put(t_game *g, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= (int)g->win_w || y < 0 || y >= (int)g->win_h)
		return ;
	dst = g->img.addr + (y * g->img.line_len + x * (g->img.bpp / 8));
	*(unsigned int *)dst = color;
}

t_texture	load_texture(t_game *g, void *mlx, char *path)
{
	t_texture	text;

	text.imge = mlx_xpm_file_to_image(mlx, path, &text.width, &text.height);
	if (!text.imge)
	{
		perror("Loading Texture Error");
		mlx_destroy_window(g->mlx, g->win);
		free_struct(g->txt, g);
		exit(0);
	}
	text.addr = mlx_get_data_addr(text.imge, &text.bpp,
			&text.line_len, &text.endian);
	return (text);
}

void	find_id_texture(t_game *g, int side, double raydir_x, double raydir_y)
{
	if (side == 0 && raydir_x > 0)
		g->current_text_id = 3;
	else if (side == 0 && raydir_x < 0)
		g->current_text_id = 2;
	else if (side == 1 && raydir_y > 0)
		g->current_text_id = 1;
	else if (side == 1 && raydir_y < 0)
		g->current_text_id = 0;
}

void	find_floor_position_on_wallbase(t_ray *r)
{
	if (r->side == 0 && r->raydir_x > 0)
	{
		r->floor_wall_x = r->map_x;
		r->floor_wall_y = r->map_y + r->wall_x;
	}
	else if (r->side == 0 && r->raydir_x < 0)
	{
		r->floor_wall_x = r->map_x + 1.0;
		r->floor_wall_y = r->map_y + r->wall_x;
	}
	else if (r->side == 1 && r->raydir_y > 0)
	{
		r->floor_wall_x = r->map_x + r->wall_x;
		r->floor_wall_y = r->map_y;
	}
	else if (r->side == 1 && r->raydir_y < 0)
	{
		r->floor_wall_x = r->map_x + r->wall_x;
		r->floor_wall_y = r->map_y + 1.0;
	}
}
