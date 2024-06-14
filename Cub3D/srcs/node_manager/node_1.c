/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:56:14 by jetol             #+#    #+#             */
/*   Updated: 2024/06/14 14:32:57 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	toggle_door(t_node *cpy, t_data *data)
{
	if (cpy->door_state == OPENNING)
	{
		if (cpy->door_loc == HITBOX - 1)
		{
			cpy->door_state = OPEN;
			cpy->is_free = 1;
		}
		cpy->door_loc+=1;
	}
	if (cpy->door_state == CLOSING)
	{
		if (cpy->door_loc == 1)
		{
			cpy->door_state = CLOSE;
			cpy->is_free = 0;
		}
		cpy->door_loc--;
	}
	return 0;
}

void	check_to_door(t_data *data, int x, int y)
{
	t_node	*cpy;
	int		i;

	i = 0;
	cpy = data->nodes;
	while (cpy->type != ENDL)
	{
		if (cpy->type == DOOR)
		{
			int dx = x - ((cpy->x * HITBOX) + (HITBOX / 2));
			int dy = y - ((cpy->y * HITBOX) + (HITBOX / 2));
			double distance = sqrt(dx * dx + dy * dy);
			if (distance <= HITBOX * (sqrt(HITBOX) / 4) && cpy->door_state != OPENNING && cpy->door_state != OPEN)
				cpy->door_state = OPENNING;
			else if (distance > HITBOX * (sqrt(HITBOX) / 4) && cpy->door_state != CLOSING && cpy->door_state != CLOSE)
				cpy->door_state = CLOSING;
		}
		i++;
		cpy++;
	}
}

int	is_node_free(float x, float y, t_data *data)
{
	t_node	*node;
	
	node = get_node_at(data->nodes, x, y);
	return (node->is_free);
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
	else if (name == 'N' || name == 'S' || name == 'W' || name == 'E')
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
	if (new.type == WALL || new.type == DOOR || new.type == NULLT || new.type == ENDL)
		new.is_free = 0;
	else
		new.is_free = 1;
	return (new);
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
