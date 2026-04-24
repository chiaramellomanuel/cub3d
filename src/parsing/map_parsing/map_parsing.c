#include "map_parsing.h"
#include "check_map_validity.h"

static char	**fill_map(char **map, t_game *g)
{
	size_t	row;

	row = 0;
	while (row < g->map_h)
	{
		while (ft_strlen(map[row]) < g->map_w)
			map[row] = ft_freejoin(map[row], " ");
		row++;
	}
	return (map);
}

static char	**copy_map(int fd, char *line, t_game *g)
{
	char	*full_map;
	char	**map;

	full_map = NULL;
	while (line)
	{
		full_map = ft_freejoin(full_map, " ");
		full_map = ft_freejoin(full_map, line);
		g->map_h++;
		if (ft_strlen(line) > g->map_w)
			g->map_w = ft_strlen(line);
		free (line);
		line = get_next_line(fd);
	}
	map = ft_split(full_map, '\n');
	free (full_map);
	map = fill_map(map, g);
	return (map);
}

static int	find_map_start(char *line)
{
	char	*trim_line;

	trim_line = ft_strtrim(line, " \t\n");
	if (*trim_line == '1')
	{
		free (trim_line);
		return (1);
	}
	free (trim_line);
	return (0);
}

char	**get_map(int fd, t_game *g)
{
	char	*line;
	char	**map;

	map = NULL;
	line = get_next_line(fd);
	while (line && !find_map_start(line))
	{
		free (line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		ft_putstr_fd("Error\nMap not found\n", 2);
		return (NULL);
	}
	map = copy_map(fd, line, g);
	if (!map_validity(map))
	{
		map = free_mat(map);
		close(fd);
		return (map);
	}
	return (map);
}
