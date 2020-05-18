#include "../includes/ft_ls.h"

int		main(int ac, char **av)
{
	int			i;
	int			flags;
	t_elem		*list;
	int			num;

	if ((i = display_options(ac, av, &flags)) == -1)
		return (1);
	av += i;
	ac -= i;
	list = valid_file(av, ac, 1);
	num = (!list ? 1 : 0);
	display_all_content(list, flags, (!num ? 1 : 2), ac);
	free_folder(&list);
	return (0);
}
