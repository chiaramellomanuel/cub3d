#include "texture_path.h"

static void	print_error(char *texture, int errNo)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(texture, 2);
	if (errNo == 0)
		ft_putendl_fd(": no such file or directory", 2);
	else if (errNo == 1)
		ft_putendl_fd(": not a valid gradient [0,255]", 2);
	else if (errNo == 2)
		ft_putendl_fd(": not a valid gradient format (0,0,0)", 2);
}

static int	check_path(int i, char *texture)
{
	int	fd;

	if (i == 1)
	{
		fd = open(texture, O_RDONLY);
		if (fd == -1)
		{
			print_error(texture, 0);
			return (0);
		}
		return (1);
	}
	else if (i != 3)
	{
		print_error(texture, 2);
		return (0);
	}
	return (1);
}

static int	check_values(char **colorValues, char *texture)
{
	int	i;
	int	j;

	i = 0;
	while (colorValues[i])
		i++;
	if (!check_path(i, texture))
		return (0);
	else if (i == 3)
	{
		i = -1;
		while (colorValues[++i])
		{
			j = -1;
			while (colorValues[i][++j])
			{
				if (!isdigit(colorValues[i][j]))
				{
					print_error(texture, 1);
					return (0);
				}
			}
		}
	}
	return (1);
}

int	check_color_gradient(char *texture)
{
	char	**color_values;
	int		i;

	color_values = ft_split(texture, ',');
	if (!check_values(color_values, texture))
	{
		free_mat(color_values);
		return (0);
	}
	if (color_values[1] && color_values[2])
	{
		i = -1;
		while (color_values[++i])
		{
			if (ft_atoi(color_values[i]) < 0 || ft_atoi(color_values[i]) > 255)
			{
				print_error(texture, 1);
				free_mat(color_values);
				return (0);
			}
		}
	}
	free_mat(color_values);
	return (1);
}

void	missing_path_print(size_t errNo, char **textures)
{
	if (errNo == 1)
		ft_putendl_fd("Error\nNorth wall texture's path missing", 2);
	else if (errNo == 2)
		ft_putendl_fd("Error\nSouth wall texture's path missing", 2);
	else if (errNo == 3)
		ft_putendl_fd("Error\nWest wall texture's path missing", 2);
	else if (errNo == 4)
		ft_putendl_fd("Error\nEast wall texture's path missing", 2);
	else if (errNo == 5)
		ft_putendl_fd("Error\nFloor texture's path missing", 2);
	else if (errNo == 6)
		ft_putendl_fd("Error\nCeiling texture's path missing", 2);
	else if (errNo >= 7)
	{
		if (errNo <= 10)
		{
			ft_putendl_fd("Error", 2);
			ft_putstr_fd(textures[errNo - 7], 2);
			ft_putendl_fd(": no such file or directory", 2);
		}
		else
			check_color_gradient(textures[errNo - 7]);
	}
}
