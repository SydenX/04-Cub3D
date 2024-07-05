/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:12:42 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/18 14:47:44 by jtollena         ###   ########.fr       */
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
		exit_error(ERROR_NOTINTERESTS, NULL, (void *)nodes, NULL);
	return (nodes);
}
