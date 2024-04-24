/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodestype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:12:42 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/24 11:58:43 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_node	*check_nodes_type(t_node *nodes, int size)
{
	t_node	cpy;
	int		spawn;
	int		exit;
	int		collectible;
	int		i;

	i = 0;
	spawn = 0;
	exit = 0;
	collectible = 0;
	cpy = nodes[i++];
	while (i < size)
	{
		if (cpy.type == SPAWN)
			spawn++;
		cpy = nodes[i++];
	}
	if (spawn != 1)
		error_notcorrectinterest((void *)nodes, NULL, NULL);
	return (nodes);
}
