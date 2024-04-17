/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:43:28 by jetol             #+#    #+#             */
/*   Updated: 2023/12/12 13:49:20 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	pathf_setup_h(t_node *list)
{
	t_node	exit;
	t_node	*cpy;
	int		xdiff;
	int		ydiff;

	exit = find_exit_point(list);
	cpy = list;
	while (cpy->type != NULLT)
	{
		xdiff = absolute(cpy->x - exit.x);
		ydiff = absolute(cpy->y - exit.y);
		cpy->h = xdiff + ydiff;
		cpy++;
	}
}

void	reset_node(t_node *list)
{
	t_node	*cpy;

	cpy = list;
	while (cpy->type != NULLT)
	{
		cpy->g = 0;
		cpy->f = 0;
		cpy++;
	}
}

void	pathf_run(t_node *list)
{
	t_node	*cpy;
	int		lstsize;
	int		checked;

	cpy = list;
	lstsize = get_list_size(list);
	while (cpy->type != NULLT)
	{
		if (cpy->type == COLLECTIBLE || cpy->type == SPAWN)
		{
			checked = check_arround(*cpy, list);
			if (checked == 0)
				error_nopathfound(list, NULL);
			if (cpy->type == COLLECTIBLE)
			{
				reset_node(list);
				checked = check_arround_tospawn(*cpy, list);
				if (checked == 0)
					error_nopathfound(list, NULL);
			}
			reset_node(list);
		}
		cpy++;
	}
}
