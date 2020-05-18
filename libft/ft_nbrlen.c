#include "libft.h"

size_t		ft_nbrlen(int nbr)
{
	size_t		len;

	len = 1;
	while (nbr > 9)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}
