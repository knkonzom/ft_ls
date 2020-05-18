#include "libft.h"

void		ft_putspace(size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		ft_putchar(' ');
		i++;
	}
}
