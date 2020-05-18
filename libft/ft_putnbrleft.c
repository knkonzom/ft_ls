#include "libft.h"

void		ft_putnbrleft(int nbr, size_t min_len)
{
	size_t		len;

	len = ft_nbrlen(nbr);
	ft_putnbr(nbr);
	if (len < min_len)
		ft_putspace(min_len - len);
}
