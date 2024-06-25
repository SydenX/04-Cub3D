/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_api.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:40:01 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/24 13:23:40 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

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

int	is_node_free(float x, float y, t_data *data)
{
	t_node	*node;

	node = get_node_at(data->nodes, x, y);
	return (node->is_free);
}
