#ifndef TEXTURE_PATH_H
# define TEXTURE_PATH_H
# include "libft.h"
# include "utility.h"
# include "cub3d.h"

char	**textures_path(int fd);
void	missing_path_print(size_t errNo, char **textures);
int		check_color_gradient(char *texture);

#endif