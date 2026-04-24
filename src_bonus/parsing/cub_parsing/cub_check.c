#include "cub_check.h"

static int	get_file_fd(char *fileName)
{
	int		fd;
	char	*file_path;

	file_path = NULL;
	if (ft_strncmp(fileName, "./", 2))
	{
		file_path = ft_strcat(&file_path, "./maps/");
		file_path = ft_freejoin(file_path, fileName);
		fd = open(file_path, O_RDONLY);
	}
	else
		fd = open(fileName, O_RDONLY);
	if (fd == -1)
		perror("Error\n");
	if (file_path)
		free (file_path);
	return (fd);
}

static int	check_file_name(char *fileName)
{
	if (!ft_strncmp(fileName, "./", 2))
		fileName++;
	while (*fileName)
	{
		if (*fileName == '.')
		{
			if (ft_strcmp(fileName, ".cub") != 0)
				break ;
			else
				return (1);
		}
		fileName++;
	}
	ft_putendl_fd("Error\nNot a valid .cub file", 2);
	return (0);
}

int	check_input_file(int argc, char *fileName)
{
	int	fd;

	if (argc == 1)
	{
		ft_putendl_fd("Error\nSpecify .cub file as argument", 2);
		return (0);
	}
	else if (argc != 2)
	{
		ft_putendl_fd("Error\nToo many arguments", 2);
		return (0);
	}
	if (!check_file_name(fileName))
		return (0);
	fd = get_file_fd(fileName);
	return (fd);
}

/*
*	Checks that the number of parameters is exactly 2, this includes
*	program file name and .cub file name.
*	Checks if the .cub format is correct and tries to open the file descriptor
*
*	RETURN VALUE
*	opened fd number
*/