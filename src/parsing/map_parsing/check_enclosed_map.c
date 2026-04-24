#include "check_enclosed_map.h"

static int	find_wall_east(char **map, int row, size_t col)
{
	while (map[row][col])
	{
		if (map[row][col] == '1')
			return (1);
		if (map[row][++col])
		{
			if (!map[row][col])
				break ;
			else if (map[row][col] == ' ')
			{
				if (map[row][col + 1] && ft_strchr("01", map[row][col + 1]))
				{
					print_map_error(map, "invalid space inside map walls", \
						row, col);
					col++;
					return (0);
				}
				else
					break ;
			}
		}
	}
	print_map_error(map, "map not enclosed by walls\n", row, (col - 1));
	return (0);
}

static int	find_wall_west(char **map, size_t row, int col)
{
	while (col > 0)
	{
		if (map[row][col] == '1')
			return (1);
		col--;
		if (col > 0)
		{
			if (map[row][col] == ' ')
			{
				if (!map[row][col - 1] || map[row][col - 1] == ' ')
					break ;
				else if (ft_strchr("01", map[row][col - 1]))
				{
					print_map_error(map, "invalid space inside map walls", \
						row, col);
					col++;
					return (0);
				}
			}
		}
	}
	print_map_error(map, "map not enclosed by walls\n", row, (col + 1));
	return (0);
}

static int	find_wall_south(char **map, int row, size_t col)
{
	while (map[row])
	{
		if (map[row][col] == '1')
			return (1);
		if (map[++row])
		{
			if (!map[row][1] || !map[row][col])
				break ;
			else if (map[row][col] == ' ')
			{
				if (map[row + 1] && ft_strchr("01", map[row + 1][col]))
				{
					print_map_error(map, "invalid space inside map walls", \
						row, col);
					return (0);
				}
				else
					break ;
			}
		}
	}
	print_map_error(map, "map not enclosed by walls\n", (row - 1), col);
	return (0);
}

static int	find_wall_north(char **map, int row, size_t col)
{
	while (row >= 0)
	{
		if (map[row][col] == '1')
			return (1);
		row--;
		if (row > 0)
		{
			if (!map[row][1] || !map[row][col])
				break ;
			else if (map[row][col] == ' ')
			{
				if (map[row - 1] && ft_strchr("01", map[row - 1][col]))
				{
					print_map_error(map, "invalid space inside map walls", \
						row, col);
					return (0);
				}
				else
					break ;
			}
		}
	}
	print_map_error(map, "map not enclosed by walls\n", (row + 1), col);
	return (0);
}

int	check_enclosed_map(char **map)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (ft_strchr("NESW0", map[row][col]))
			{
				if (!find_wall_north(map, row, col)
					|| !find_wall_south(map, row, col)
					|| !find_wall_west(map, row, col)
					|| !find_wall_east(map, row, col))
					return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}
