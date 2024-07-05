/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:56:14 by jetol             #+#    #+#             */
/*   Updated: 2024/06/18 13:55:29 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_node	spawn_setup(char name, t_node new)
{
	if (name == 'N' || name == 'S' || name == 'W' || name == 'E')
	{
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

t_node	create_node(char name, int x, int y)
{
	t_node	new;

	new.x = x;
	new.y = y;
	if (name == '1')
		new.type = WALL;
	else if (name == '0')
		new.type = FLOOR;
	else if (name == 'D')
	{
		new.type = DOOR;
		new.door_state = CLOSE;
		new.running_door = 0;
		new.door_loc = 0;
	}
	else
		new = spawn_setup(name, new);
	if (new.type == WALL || new.type == DOOR
		|| new.type == NULLT || new.type == ENDL)
		new.is_free = 0;
	else
		new.is_free = 1;
	return (new);
}
