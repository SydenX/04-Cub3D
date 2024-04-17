/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:13:16 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/17 17:52:59 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	get_list_size(t_node *list)
{
	t_node	*cpy;
	int		i;

	i = 0;
	cpy = list;
	while (cpy->type != NULLT)
	{
		i++;
		cpy++;
	}
	return (i);
}

int	get_list_xlen(t_node *list)
{
	t_node	*cpy;
	int		lastx;

	lastx = 0;
	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->x > lastx)
			lastx = cpy->x;
		cpy++;
	}
	return (lastx + 1);
}

int	get_list_ylen(t_node *list)
{
	t_node	*cpy;
	int		lasty;

	lasty = 0;
	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->y > lasty)
			lasty = cpy->y;
		cpy++;
	}
	return (lasty + 1);
}

