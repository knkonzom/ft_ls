#include "libft.h"

void	ft_putstrleft(const char *s, size_t min_len)
{
	size_t		len;

	len = ft_strlen(s);
	ft_putstr(s);
	if (len < min_len)
		ft_putspace(min_len - len);
}
