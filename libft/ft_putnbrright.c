#include "libft.h"

void		ft_putnbrright(int nbr, size_t min_len)
{
	size_t		len;

	len = ft_nbrlen(nbr);
	if (len < min_len)
		ft_putspace(min_len - len);
	ft_putnbr(nbr);
}
