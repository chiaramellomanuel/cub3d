#include "cub3d.h"

static void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	find_color(const char	*input)
{
	int		r;
	int		g;
	int		b;
	int		color;
	char	**rgb;

	rgb = ft_split(input, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	color = (r << 16) | (g << 8) | b;
	free_split(rgb);
	return (color);
}

void	init_texture(t_game *g, t_texture *txt)
{
	size_t	i;

	i = 0;
	while (txt->texturepath[i])
	{
		if (ft_strncmp(txt->texturepath[i], "./", 2) == 0)
			g->texture[i] = load_texture(g, g->mlx, txt->texturepath[i]);
		else if (i == 4)
		{
			g->use_floor_text = FALSE;
			g->floor_color = find_color(txt->texturepath[i]);
		}
		else if (i == 5)
		{
			g->use_ceil_text = FALSE;
			g->ceil_color = find_color(txt->texturepath[i]);
		}
		i++;
	}
}
