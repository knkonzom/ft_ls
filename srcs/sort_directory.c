#include "../includes/ft_ls.h"

t_elem				*list_swap(t_elem *p1, t_elem *p2)
{
	p1->next = p2->next;
	p2->next = p1;
	return (p2);
}

static t_elem		*quick_sort(t_elem *list)
{
	if (!list)
		return (NULL);
	if (list->next && ft_strcmp(list->name, list->next->name) > 0)
		list = list_swap(list, list->next);
	list->next = quick_sort(list->next);
	if (list->next && ft_strcmp(list->name, list->next->name) > 0)
	{
		list = list_swap(list, list->next);
		list->next = quick_sort(list->next);
	}
	return (list);
}

static t_elem		*sort_time(t_elem *list)
{
	if (!list)
		return (NULL);
	if (list->next && (list->time < list->next->time))
		list = list_swap(list, list->next);
	else if (list->next && list->time == list->next->time)
			list = list_swap(list, list->next);
	list->next = sort_time(list->next);
	if (list->next && (list->ntime < list->next->ntime))
	{
		list = list_swap(list, list->next);
		list->next = sort_time(list->next);
	}
	return (list);
}

static t_elem		*sort_size(t_elem *list)
{
	if (!list)
		return (NULL);
	if (list->next && (list->size < list->next->size))
		list = list_swap(list, list->next);
	list->next = sort_size(list->next);
	if (list->next && (list->size < list->next->size))
	{
		list = list_swap(list, list->next);
		list->next = sort_size(list->next);
	}
	return (list);
}

int					get_sort(t_elem **begin, short flags)
{
	*begin = quick_sort(*begin);
	if (flags & FLAG_T)
		*begin = sort_time(*begin);
	if (flags & FLAG_BS)
		*begin = sort_size(*begin);
	if (flags & FLAG_R)
		*begin = swap_list(*begin);
	return (1);
}