/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:22:15 by caymard           #+#    #+#             */
/*   Updated: 2024/07/05 14:37:08 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	check_move_hitbox(t_data *data, int new_x, int new_y)
{
	if (is_node_free((new_x - PLAYER_SIZE) / HITBOX, (new_y - PLAYER_SIZE) / HITBOX, data) == 1
		&& is_node_free((new_x + PLAYER_SIZE) / HITBOX, (new_y) / HITBOX, data) == 1
		&& is_node_free((new_x + PLAYER_SIZE) / HITBOX, (new_y + PLAYER_SIZE) / HITBOX, data) == 1
		&& is_node_free((new_x) / HITBOX, (new_y + PLAYER_SIZE) / HITBOX, data) == 1)
		return 1;
	return 0;
}

void	move_player(t_data *data)
{	
	data->player.oldyaw = data->player.yaw;
	data->player.oldpitch = data->player.pitch;
	// GESTION SOURIS, SI ON BOUGE LE YAW VIA LES KEYs CELA OVERRIDE LA SOURIS
	if (data->player.righting_yaw_key != 0 || data->player.lefting_yaw_key != 0)
	{
		if (data->player.righting_yaw_key != 0)
			data->player.yaw += data->player.righting_yaw_key;
		if (data->player.lefting_yaw_key != 0)
			data->player.yaw -= data->player.lefting_yaw_key;
	}
	else if (data->player.righting_yaw != 0)
		data->player.yaw += data->player.righting_yaw;
	else if (data->player.lefting_yaw != 0)
		data->player.yaw -= data->player.lefting_yaw;

	if (data->player.upping_pitch_key != 0 || data->player.downing_pitch_key != 0)
	{
		if (data->player.downing_pitch_key != 0)
			data->player.pitch += data->player.downing_pitch_key;
		if (data->player.upping_pitch_key != 0)
			data->player.pitch -= data->player.upping_pitch_key;
	}
	else if (data->player.upping_pitch != 0)
		data->player.pitch += data->player.upping_pitch;
	else if (data->player.downing_pitch != 0)
		data->player.pitch -= data->player.downing_pitch;
	if (data->player.pitch < -HEIGHT)
		data->player.pitch = -HEIGHT;
	else if (data->player.pitch > HEIGHT)
		data->player.pitch = HEIGHT;
	// CALCULS COORDONNEES DEPLACEMENTS
	double yaw_radians = (data->player.yaw) * (M_PI / 180.0);
	double oldx = data->player.newx;
	double oldy = data->player.newy;
	if (data->player.forwarding != 0)
	{
		data->player.newx += data->player.forwarding * cos(yaw_radians);
		data->player.newy += data->player.forwarding * sin(yaw_radians);
	}
	else if (data->player.backwarding != 0)
	{
		data->player.newx -= (data->player.backwarding * cos(yaw_radians));
		data->player.newy -= (data->player.backwarding * sin(yaw_radians));
	}
	if (data->player.lefting != 0)
	{
		data->player.newx += data->player.lefting * cos(yaw_radians - M_PI / 2);
		data->player.newy += data->player.lefting * sin(yaw_radians - M_PI / 2);
	}
	if (data->player.righting != 0)
	{
		data->player.newx += data->player.righting * cos(yaw_radians + M_PI / 2);
		data->player.newy += data->player.righting * sin(yaw_radians + M_PI / 2);
	}

	double distance = sqrt(((data->player.newx - data->player.x) * (data->player.newx - data->player.x)) + ((data->player.newy - data->player.y) * (data->player.newy - data->player.y)));
	if (distance >= data->player.speed + 0.01)
	{
		double echelle = data->player.speed / distance;
		data->player.newx += ((data->player.newx - data->player.x) * echelle) - (data->player.newx - data->player.x);
		data->player.newy += ((data->player.newy - data->player.y) * echelle) - (data->player.newy - data->player.y);
	}

	data->player.oldx = data->player.x;
	data->player.oldy = data->player.y;
	if(check_move_hitbox(data, data->player.newx, data->player.newy))
	{
		data->player.x = data->player.newx;
		data->player.y = data->player.newy;
		check_to_door(data, data->player.newx, data->player.newy);
	}
	else
	{
		data->player.newx = oldx;
		data->player.newy = oldy;
	}
	return ;
}
