#include "../includes/ft_ls.h"

int		get_position_size(t_elem *file, int size[7], int *blocks)
{
	int	len;

	size[5] = 3;
	size[6] = 3;
	while (file)
	{
		size[0] = POS(ft_nbrlen(file->st_blocks), size[0]);
		size[1] = POS(ft_nbrlen(file->st_nlink), size[1]);
		size[2] = POS(ft_strlen(getpwuid(file->st_uid)->pw_name), size[2]);
		size[3] = POS(ft_strlen(getgrgid(file->st_gid)->gr_name), size[3]);
		if (!S_ISCHR(file->st_mode))
			len = ft_nbrlen(file->size);
		else
		{
			size[5] = POS(ft_nbrlen(major(file->st_rdev)), size[5]);
			size[6] = POS(ft_nbrlen(minor(file->st_rdev)), size[6]);
			len = size[5] + size[6] + 2;
		}
		size[4] = POS(len, size[4]);
		*blocks += file->st_blocks;
		file = file->next;
	}
	size[5] = POS(size[4] - size[6] - 1, size[5]);
	return (1);
}

int		make_list(t_elem *list, int flags)
{
	char	buff[5];
	int		size[7];
	int		blocks;
	int		first;

	ft_bzero(size, sizeof(size));
	blocks = 0;
	first = 1;
	get_position_size(list, size, &blocks);
	while (list)
	{
		get_permissions(list, size, flags);
		ft_putchar('\n');
		list = list->next;
	}
	return (1);
}

int		display_long_list(t_elem *list, int flags)
{
	char	buff[5];
	int		size[7];
	int		blocks;
	int		first;

	ft_bzero(size, sizeof(size));
	blocks = 0;
	first = 1;
	get_position_size(list, size, &blocks);
	while (list)
	{
		if (first == 1 && !(flags & FLAG_D))
		{
			ft_putstr("total ");
			ft_putnbr(blocks);
			ft_putchar('\n');
			first = 0;
		}
		get_permissions(list, size, flags);
		ft_putchar('\n');
		list = list->next;
	}
	return (1);
}

int		display_list(t_elem **list, int flags)
{
	get_sort(list, flags);
	if (!(flags & FLAG_L))
		display_basic_list(*list, flags);
	else
		display_long_list(*list, flags);
	return (1);
}

void	display_basic_list(t_elem *list, int flags)
{
	int total;
	int first;

	total = 0;
	first = 1;
	block_size(list, &total);
	while (list)
	{
		if (first == 1 && flags & FLAG_S)
		{
			ft_putstr("total ");
			ft_putnbr(total);
			ft_putchar('\n');
			first = 0;
		}
		if (flags & FLAG_S && !(flags & FLAG_L))
		{
			ft_putnbr(list->st_blocks);
			ft_putstr(" ");
		}
		ft_putstr(list->name);
		ft_putchar('\n');
		list = list->next;
	}
}