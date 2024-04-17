/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder_arround.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:48:48 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/12 13:49:19 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	check_arround(t_node node, t_node *list)
{
	if (check_precisely(node, list, node.x, node.y + 1) == 0
		&& check_precisely(node, list, node.x, node.y - 1) == 0
		&& check_precisely(node, list, node.x + 1, node.y) == 0
		&& check_precisely(node, list, node.x - 1, node.y) == 0)
		return (0);
	return (1);
}

int	check_precisely_tospawn(t_node current, t_node *list, int x, int y)
{
	t_node	newnode;

	newnode = *get_node_at(list, x, y);
	if (newnode.x == 0 || newnode.y == 0)
		return (0);
	if (newnode.type == SPAWN)
		return (1);
	if (newnode.f > 0)
		return (0);
	newnode.g = current.g + 1;
	newnode.f = newnode.h + newnode.g;
	update_node(newnode, list);
	if (newnode.type == FLOOR || newnode.type == COLLECTIBLE)
		return (check_arround_tospawn(newnode, list));
	return (0);
}

int	check_arround_tospawn(t_node node, t_node *list)
{
	if (check_precisely_tospawn(node, list, node.x, node.y + 1) == 0
		&& check_precisely_tospawn(node, list, node.x, node.y - 1) == 0
		&& check_precisely_tospawn(node, list, node.x + 1, node.y) == 0
		&& check_precisely_tospawn(node, list, node.x - 1, node.y) == 0)
		return (0);
	return (1);
}

int	check_precisely(t_node current, t_node *list, int x, int y)
{
	t_node	newnode;

	newnode = *get_node_at(list, x, y);
	if (newnode.x == 0 || newnode.y == 0)
		return (0);
	if (newnode.type == EXIT)
		return (1);
	if (newnode.f > 0)
		return (0);
	newnode.g = current.g + 1;
	newnode.f = newnode.h + newnode.g;
	update_node(newnode, list);
	if (newnode.type == FLOOR || newnode.type == COLLECTIBLE)
		return (check_arround(newnode, list));
	return (0);
}
