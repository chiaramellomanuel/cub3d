#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "cub_check.h"
# include "texture_path.h"
# include "map_parsing.h"
# include "cub3d.h"

t_texture	*init_struct(t_texture *txt, t_game *g);
int			parsing_start(int argc, char **argv, t_texture *txt, t_game *g);

#endif