#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <grp.h>
# include <pwd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>
# include <uuid/uuid.h>
# include <limits.h>
# include <errno.h>

enum	{ERRNO, USAGE, MALL_ERR};
typedef struct stat		t_stat;

# define FLAG_A 1
# define FLAG_L 2
# define FLAG_BR 4
# define FLAG_R 8
# define FLAG_T 16
# define FLAG_D 32
# define FLAG_1 128
# define FLAG_BS 256
# define FLAG_S 512
# define POS(x, y) (((x) > (y)) ? (x) : (y))

typedef	struct		s_elem
{
	time_t			time;
	long			ntime;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			size;
	blkcnt_t		st_blocks;
	dev_t			st_rdev;
	struct s_elem	*next;
	char			*name;
	char			full_path[PATH_MAX];
}					t_elem;

static t_elem	    *read_folder(char path[PATH_MAX], char *name, int options);
t_elem				*list_swap(t_elem *a, t_elem *b);
t_elem				*swap_list(t_elem *list);
t_elem				*valid_file(char **names_list, int ac, int first);

char				*get_mode(char chmod[12], int mode, char path[PATH_MAX]);

int					print_error(char *s, int error);
int					free_folder(t_elem **list);
int					display_all_content(t_elem *begin, int flags, int first, int n);
int					get_sort(t_elem **begin, short flags);
int					get_info(char path[PATH_MAX], char *name, t_elem **list);
int					display_list(t_elem **list, int flags);
int					display_long_list(t_elem *list, int flags);
int					get_permissions(t_elem *file, int size[7], int flags);
int					display_options(int ac, char **av, int *flags);
int					make_list(t_elem *list, int flags);
int					block_size(t_elem *list, int *total);

void				print_links(int nbr, int *maxs);
void				print_device(int device, int *maxs);
void				print_groups(t_elem *file, int	*maxs);
void				print_size(int size, int *maxs);
void				display_basic_list(t_elem *list, int flags);
void				ft_readlink(t_elem *file);

#endif