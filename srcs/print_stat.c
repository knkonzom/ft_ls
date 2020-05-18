#include "../includes/ft_ls.h"

static int		get_path(char path[PATH_MAX], char *name, char full_path[PATH_MAX])
{
	int x;

	x = -1;
	while (path[++x])
		full_path[x] = path[x];
	if (x && x < PATH_MAX)
		if (!(path[0] == '/' && path[1] == '\0'))
			full_path[x++] = '/';
	while (*name && x < PATH_MAX)
		full_path[x++] = *name++;
	if (x < PATH_MAX)
		full_path[x] = '\0';
	else
		errno = ENAMETOOLONG;
	return ((x < PATH_MAX) ? 1 : 0);
}

static t_elem	*file_info(char path[PATH_MAX], char *name, t_stat *st)
{
	t_elem *info;

	if (!(info = (t_elem *)ft_memalloc(sizeof(t_elem))) || (!(info->name = ft_strdup(name))))
	{
		print_error(NULL, 2);
	}
	info->st_mode = st->st_mode;
	info->st_nlink = st->st_nlink;
	info->st_uid = st->st_uid;
	info->st_gid = st->st_gid;
	info->size = st->st_size;
	info->st_rdev = st->st_rdev;
	info->time = st->st_mtimespec.tv_sec;
	info->ntime = st->st_mtimespec.tv_nsec;
	info->st_blocks = st->st_blocks;
	get_path(path, name, info->full_path);
	info->next = NULL;
	return (info);
}

int				get_info(char path[PATH_MAX], char *name, t_elem **list)
{
	char	full_path[PATH_MAX];
	t_stat	st;

	if (!(get_path(path, name, full_path)))
	{
		print_error(name, 1);
		return (-1);
	}
	if (lstat(full_path, &st) == -1)
		return (-1);
	if (!*list)
		*list = file_info(path, name, &st);
	else
	{
		while ((*list)->next)
			list = &((*list)->next);
		(*list)->next = file_info(path, name, &st);
	}
	return (1);
}

void			print_size(int size, int *maxs)
{
	if (maxs != NULL)
		ft_putnbrright(size, maxs[4]);
	else
		ft_putnbr(size);
}

void			print_groups(t_elem *file, int *maxs)
{
	struct passwd	*usr;
	struct group	*grp;

	usr = getpwuid(file->st_uid);
	if (usr != NULL)
		ft_putstrleft(usr->pw_name, (maxs) ? maxs[1] : 0);
	else
		ft_putnbrleft(file->st_uid, (maxs) ? maxs[1] : 0);
	ft_putspace(2);
	grp = getgrgid(file->st_gid);
	if (grp != NULL)
		ft_putstrleft(grp->gr_name, (maxs) ? maxs[2] : 0);
	ft_putspace(1);
}