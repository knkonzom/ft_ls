#include "../includes/ft_ls.h"

static char		get_file_type(int mode)
{
	mode = (mode & S_IFMT);
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

static char		ft_get_file_acl(char path[PATH_MAX])
{
	int		xattrs;
	acl_t	acl;

	xattrs = (int)listxattr(path, NULL, 1, XATTR_NOFOLLOW);
	if (xattrs > 0)
		return ('@');
	else
	{
		acl = acl_get_file(path, ACL_TYPE_EXTENDED);
		if (acl != NULL)
			return ('+');
		else
			return (' ');
	}
}

char			*get_mode(char chmod[12], int mode, char path[PATH_MAX])
{
	chmod[0] = get_file_type(mode);
	chmod[1] = (mode & S_IRUSR) ? 'r' : '-';
	chmod[2] = (mode & S_IWUSR) ? 'w' : '-';
	chmod[3] = (mode & S_IXUSR) ? 'x' : '-';
	chmod[4] = (mode & S_IRGRP) ? 'r' : '-';
	chmod[5] = (mode & S_IWGRP) ? 'w' : '-';
	chmod[6] = (mode & S_IXGRP) ? 'x' : '-';
	chmod[7] = (mode & S_IROTH) ? 'r' : '-';
	chmod[8] = (mode & S_IWOTH) ? 'w' : '-';
	chmod[9] = (mode & S_IXOTH) ? 'x' : '-';
	chmod[10] = ft_get_file_acl(path);
	chmod[11] = '\0';
	if (S_ISUID & mode)
		chmod[3] = chmod[3] == '-' ? 'S' : 's';
	if (S_ISGID & mode)
		chmod[6] = chmod[6] == '-' ? 'S' : 's';
	if (S_ISVTX & mode)
		chmod[9] = chmod[9] == '-' ? 'T' : 't';
	ft_putstr(chmod);
	return (chmod);
}

static void		get_time(t_elem *file)
{
	time_t	today;
	char	*s;

	time(&today);
	s = ctime(&(file->time)) + 4;
	ft_putnstr(s, 12);
	ft_putchar(' ');
}

int				get_permissions(t_elem *file, int size[7], int flags)
{
	char	str[12];
	char	buf[NAME_MAX];

	(flags & FLAG_S) ? print_links(file->st_blocks, size) : 0;
	get_mode(str, file->st_mode, file->full_path);
	print_links(file->st_nlink, &size[1]);
	print_groups(file, size);
	if (str[0] != 'c' && str[0] != 'b')
	{
		print_size(file->size, size);
		ft_putstr(" ");
	}
	else
		print_device(file->st_rdev, size);
	get_time(file);
	if (str[0] != 'l')
		ft_putstr(file->name);
	else
		ft_readlink(file);
	return (1);
}