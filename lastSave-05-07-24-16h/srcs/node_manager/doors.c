/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:44:39 by jtollena          #+#    #+#             */
/*   Updated: 2024/07/04 17:42:27 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	toggle_door(t_node *cpy, t_data *data)
{
	(void)data;
	if (cpy->door_state == OPENNING)
	{
		if (cpy->door_loc == HITBOX - 1)
		{
			cpy->door_state = OPEN;
			cpy->is_free = 1;
		}
		cpy->door_loc += 1;
	}
	if (cpy->door_state == CLOSING)
	{
		cpy->is_free = 0;
		if (cpy->door_loc == 1)
			cpy->door_state = CLOSE;
		cpy->door_loc--;
	}
	return (0);
}

void	check_to_door(t_data *data, int x, int y)
{
	t_node	*cpy;
	int		i;
	int		dx;
	int		dy;
	float	distance;

	i = 0;
	cpy = data->nodes;
	while (cpy->type != ENDL)
	{
		if (cpy->type == DOOR)
		{
			dx = x - ((cpy->x * HITBOX) + (HITBOX / 2));
			dy = y - ((cpy->y * HITBOX) + (HITBOX / 2));
			distance = sqrt(dx * dx + dy * dy);
			if (distance <= HITBOX + (HITBOX * 0.05)
				&& cpy->door_state != OPENNING && cpy->door_state != OPEN)
				cpy->door_state = OPENNING;
			else if (distance > HITBOX + (HITBOX * 0.05)
				&& cpy->door_state != CLOSING && cpy->door_state != CLOSE)
				cpy->door_state = CLOSING;
		}
		i++;
		cpy++;
	}
}
