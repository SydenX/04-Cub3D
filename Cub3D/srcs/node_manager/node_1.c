/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:56:14 by jetol             #+#    #+#             */
/*   Updated: 2024/04/19 09:38:02 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_node	create_node(char name, int x, int y)
{
	t_node	new;

	new.x = x;
	new.y = y;
	new.f = 0;
	new.g = 0;
	if (name == '1')
		new.type = WALL;
	else if (name == '0')
		new.type = FLOOR;
	else if (name == 'N' || name == 'S' || name == 'W' || name == 'E')
	{
		new.f = 10000;
		new.type = SPAWN;
		if (name == 'N')
			new.direction = NORTH;
		if (name == 'E')
			new.direction = EAST;
		if (name == 'S')
			new.direction = SOUTH;
		if (name == 'W')
			new.direction = WEST;
	}
	else if (name == 1)
		new.type = ENDL;
	else
		new.type = NULLT;
	return (new);
}

t_node	find_exit_point(t_node *list)
{
	t_node	*cpy;

	cpy = list;
	while (cpy->type != ENDL)
	{
		if (cpy->type == EXIT)
			return (*cpy);
		cpy++;
	}
	return (*cpy);
}

t_node	find_spawn_point(t_node *list)
{
	t_node	*cpy;

	cpy = list;
	while (cpy->type != ENDL)
	{
		if (cpy->type == SPAWN)
			return (*cpy);
		cpy++;
	}
	return (*cpy);
}

t_node	*get_node_at(t_node *list, int x, int y)
{
	t_node	*cpy;
	int		i;

	i = 0;
	cpy = list;
	while (cpy->type != ENDL)
	{
		if (cpy->x == x && cpy->y == y)
			return (&list[i]);
		i++;
		cpy++;
	}
	return (list);
}

int	update_node(t_node node, t_node *list)
{
	t_node	*cpy;

	cpy = list;
	while (cpy->type != ENDL)
	{
		if (cpy->x == node.x && cpy->y == node.y)
		{
			*cpy = node;
			return (1);
		}
		cpy++;
	}
	return (0);
}
