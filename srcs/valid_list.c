#include "../includes/ft_ls.h"

void		print_links(int nbr, int *maxs)
{
	ft_putchar(' ');
	if (maxs != NULL)
		ft_putnbrright(nbr, maxs[0]);
	else
		ft_putnbr(nbr);
	ft_putchar(' ');
}

void		print_device(int device, int *maxs)
{
	if (maxs != NULL)
		ft_putnbrright(major(device), maxs[3] - 2 - maxs[4]);
	else
		ft_putnbr(major(device));
	ft_putstr(" ");
	ft_putnbrright(minor(device), (maxs) ? maxs[4] : 0);
}

int			do_sort(char **tab, int size, int (*f)(const char*, const char*))
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	while (j < size)
	{
		i = j - 1;
		tmp = tab[j];
		while (i >= 0 && f(tab[i], tmp) > 0)
		{
			tab[i + 1] = tab[i];
			i--;
		}
		tab[i + 1] = tmp;
		j++;
	}
	return (1);
}

t_elem		*valid_file(char **names_list, int ac, int first)
{
	t_elem	*begin;
	int		i;

	begin = NULL;
	(!ac) ? get_info("", ".", &begin) : do_sort(names_list, ac, &ft_strcmp);
	i = -1;
	while (++i < ac)
		if (get_info("", names_list[i], &begin) == -1 && first)
			print_error(names_list[i], ERRNO);
	return (begin);
}

int			block_size(t_elem *list, int *total)
{
	int size;

	size = 0;
	while (list)
	{
		size = POS(ft_nbrlen(list->st_blocks), size);
		*total += list->st_blocks;
		list = list->next;
	}
	return (size);
}