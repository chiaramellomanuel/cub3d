#include "libft.h"
#include "check_enclosed_map.h"

void	print_error(int foundP)
{
	if (!foundP)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Player not found", 2);
	}
}
