/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:57:24 by jtollena          #+#    #+#             */
/*   Updated: 2024/07/05 11:42:24 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_player	init_direction(t_node spawn, t_player player)
{
	if (spawn.direction == NORTH)
		player.yaw = 270;
	else if (spawn.direction == EAST)
		player.yaw = 0;
	else if (spawn.direction == SOUTH)
		player.yaw = 90;
	else if (spawn.direction == WEST)
		player.yaw = 180;
	return (player);
}

t_player	init_player(t_node spawn)
{
	t_player	player;

	player.speed = 0.04 * HITBOX;
	player.sensivity = 18;
	player.forwarding = 0;
	player.lefting = 0;
	player.backwarding = 0;
	player.righting = 0;
	player.righting_yaw = 0;
	player.lefting_yaw = 0;
	player.righting_yaw_key = 0;
	player.lefting_yaw_key = 0;
	player.upping_pitch = 0;
	player.downing_pitch = 0;
	player.upping_pitch_key = 0;
	player.downing_pitch_key = 0;
	player.pitch = 0;
	player.x = spawn.x * HITBOX + (HITBOX / 2);
	player.y = spawn.y * HITBOX + (HITBOX / 2);
	player.newx = player.x;
	player.newy = player.y;
	player = init_direction(spawn, player);
	return (player);
}
