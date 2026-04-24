#include "utility.h"

static void	free_struct_game(t_game *g)
{
	size_t	i;

	i = 0;
	if (g->map)
	{
		i = 0;
		while (g->map[i])
			free (g->map[i++]);
		free (g->map);
	}
	i = 0;
	while (i < 6)
	{
		if (g->texture[i].imge)
			mlx_destroy_image(g->mlx, g->texture[i].imge);
		i++;
	}
	if (g)
		free (g);
}

void	free_struct(t_texture *txt, t_game *g)
{
	size_t	i;

	i = 0;
	if (txt->texturepath)
	{
		while (txt->texturepath[i])
			free(txt->texturepath[i++]);
		free (txt->texturepath);
	}
	if (txt->direction)
		free (txt->direction);
	if (txt)
		free (txt);
	free_struct_game(g);
}

char	**free_mat(char **mat)
{
	size_t	i;

	i = 0;
	while (mat[i])
		free (mat[i++]);
	free (mat);
	mat = NULL;
	return (mat);
}
