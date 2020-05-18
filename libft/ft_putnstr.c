#include "libft.h"

void	ft_putnstr(const char *s, size_t n)
{
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != '\0' && i < n)
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}