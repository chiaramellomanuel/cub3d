#include "libft.h"

char	*ft_charcpy(char **dst, char c)
{
	if (!*dst)
		*dst = ft_calloc(2, sizeof(char));
	*dst[0] = c;
	return (*dst);
}
