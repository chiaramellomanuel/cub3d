#include "check_map_validity.h"
#include "cub3d.h"

void	print_map_error(char **map, char *str, size_t errRow, size_t errCol)
{
	size_t	row;
	size_t	col;

	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (row == errRow && col == errCol)
			{
				ft_putstr_fd("\033[41m", 2);
				ft_putchar_fd(map[row][col], 2);
				ft_putstr_fd("\033[0m", 2);
			}
			else
				ft_putchar_fd(map[row][col], 2);
			col++;
		}
		ft_putchar_fd('\n', 2);
		row++;
	}
}

static int	check_for_duplicate_player(char **map)
{
	size_t	col;
	size_t	row;
	int		found;

	found = 0;
	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (ft_strchr("NESW", map[row][col]))
			{
				if (found > 0)
				{
					ft_putstr_fd("Error\nToo many players\n", 2);
					return (-1);
				}
				found++;
			}
			col++;
		}
		row++;
	}
	return (found);
}

static int	check_for_invalid_char(char **map)
{
	size_t	col;
	size_t	row;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (!ft_strchr(" 01NESW", map[row][col]))
			{
				ft_putstr_fd("Error\n\"", 2);
				ft_putchar_fd(map[row][col], 2);
				ft_putstr_fd("\": Not a valid map char\n", 2);
				return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}

int	map_validity(char **map)
{
	int	p_found;
	if (!check_for_invalid_char(map)
		|| !check_enclosed_map(map))
		return (0);
	p_found = check_for_duplicate_player(map);
	if (!p_found)
	{
		ft_putendl_fd("Error\nPlayer not found", 2);
		return (0);
	}
	else if (p_found == -1)
		return (0);
	return (1);
}
