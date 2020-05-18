#include "../includes/ft_ls.h"

t_elem	*swap_list(t_elem *list)
{
	t_elem *x;
	t_elem *y;
	t_elem *z;

	x = NULL;
	y = list;
	z = (list)->next;
	while (y)
	{
		z = y->next;
		y->next = x;
		x = y;
		y = z;
	}
	return (x);
}

int		print_error(char *s, int err)
{
	if (err == USAGE)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(*s, 2);
		ft_putchar_fd('\n', 2);
		ft_putendl_fd("usage: ft_ls [-alRrtdG1Ss] [file ...]", 2);
	}
	else if (err == ERRNO || err == MALL_ERR)
		ft_putstr_fd("ft_ls: ", 2);
	if (err == ERRNO)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else if (err == ERRNO)
		ft_putendl_fd(strerror(errno), 2);
	if (err == USAGE || err == MALL_ERR)
		exit(EXIT_FAILURE);
	return (0);
}

int		free_folder(t_elem **list)
{
	while (*list)
	{
		free((*list)->name);
		free(*list);
		*list = (*list)->next;
	}
	return (1);
}