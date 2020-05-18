#include "../includes/ft_ls.h"

static t_elem	*read_folder(char path[PATH_MAX], char *name, int options)
{
	t_elem			*begin;
	DIR				*folder;
	struct dirent	*entry;

	begin = NULL;
	if (!(folder = opendir(path)))
		print_error(name, 0);
	else if (!(options & FLAG_D))
	{
		while ((entry = readdir(folder)))
			if (entry->d_name[0] != '.' || (options & FLAG_A))
				get_info(path, entry->d_name, &begin);
	}
	else
		get_info(path, ".", &begin);
	if (folder)
		closedir(folder);
	return (begin);
}

static void		get_full_path(char *full_path, int num, int *first)
{
	if (num != 0 && num != 1)
	{
		if (*first == 2)
		{
			*first = 1;
			ft_putstr(full_path);
			ft_putstr(":\n");
		}
		else
		{
			ft_putstr("\n");
			ft_putstr(full_path);
			ft_putstr(":\n");
		}
	}
}

void			list_arg(t_elem *list, int flags, int first)
{
	if (first && !(flags & FLAG_R))
	{
		if (flags & FLAG_L)
			make_list(list, flags);
		else if (flags & FLAG_S)
		{
			while (list)
			{
				ft_putnbr(list->st_blocks);
				ft_putstr(" ");
				ft_putstr(list->name);
				ft_putstr("\n");
				list = list->next;
			}
		}
		else
			display_list(&list, flags);
	}
}

int				display_all_content(t_elem *begin, int flags, int first, int n)
{
	t_elem			*file;

	file = begin;
	if (!(flags & FLAG_BR) && !first)
		return (-1);
	while (file)
	{
		if (S_ISDIR(file->st_mode) && (first || (ft_strcmp(file->name, ".")
			&& ft_strcmp(file->name, ".."))))
		{
			get_full_path(file->full_path, n, &first);
			begin = read_folder(file->full_path, file->name, flags);
			if (begin)
			{
				display_list(&begin, flags);
				display_all_content(begin, flags, 0, -1);
				free_folder(&begin);
			}
		}
		file = file->next;
	}
	list_arg(begin, flags, first);
	return (1);
}