#ifndef CHECK_MAP_VALIDITY_H
# define CHECK_MAP_VALIDITY_H
# include "libft.h"
# include "check_enclosed_map.h"
# include "cub3d.h"

int		map_validity(char **map);
void	print_map_error(char **map, char *str, size_t errRow, size_t errCol);

#endif