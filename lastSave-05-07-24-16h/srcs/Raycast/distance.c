/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:31:22 by caymard           #+#    #+#             */
/*   Updated: 2024/07/05 14:18:14 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	get_vertical_dist(t_data *data, int x, int c, double newx, double newy)
{
	double	noffset_y;
	t_node	*node;

	node = NULL;
	while (c++ < data->xlen)
	{
		noffset_y = (HITBOX) * (tanf((data->rc->angle) * M_PI / 180));
		if (data->rc->angle > 90 && data->rc->angle < 270) //WEST
		{
			newx -= HITBOX;
			newy -= noffset_y;
			node = get_node_at(data->nodes, (newx / HITBOX)
					- 1, (newy / HITBOX));
		}
		else if ((data->rc->angle >= 0 && data->rc->angle < 90)
			|| (data->rc->angle > 270 && data->rc->angle < 360)) //EAST
		{
			newx += HITBOX;
			newy += noffset_y;
			node = get_node_at(data->nodes, (newx / HITBOX)
					, (newy / HITBOX));
		}
		if (node != NULL && node->type == WALL)
			break ;
	}
	data->distance[x].v = sqrt(fabs((data->player.x - newx)
				* (data->player.x - newx))
			+ fabs((data->player.y - newy)
				* (data->player.y - newy)));
}

void	init_vertical_dist(t_data *data, double px, int x)
{
	double	newx;
	double	newy;
	int		c;
	t_node	*node;

	newx = 0;
	newy = 0;
	c = 0;
	data->rc->offset_x = 0;
	data->rc->offset_y = 0;
	node = NULL;
	if ((data->rc->angle >= 0 && data->rc->angle < 90)
		|| (data->rc->angle > 270 && data->rc->angle < 360)) //EAST
	{
		data->rc->offset_x = HITBOX - px;
		data->rc->offset_y = (data->rc->offset_x) * (tanf((data->rc->angle) * M_PI / 180));
		newx = data->player.x + data->rc->offset_x;
		newy = data->player.y + data->rc->offset_y;
		node = get_node_at(data->nodes, (newx / HITBOX), (newy / HITBOX));
	}
	else if ((data->rc->angle > 90 && data->rc->angle < 270)) //WEST
	{
		data->rc->offset_x = px;
		data->rc->offset_y = (data->rc->offset_x) * (tanf((data->rc->angle) * M_PI / 180));
		newx = data->player.x - data->rc->offset_x;
		newy = data->player.y - data->rc->offset_y;
		node = get_node_at(data->nodes, (newx / HITBOX) - 1, (newy / HITBOX));
	}
	if (node != NULL && node->type == WALL)
		c = data->xlen;
	get_vertical_dist(data, x, c, newx, newy);
}

void	get_horizontal_dist(t_data *data, int x, int c, double newx, double newy)
{
	t_node	*node;
	double	noffset_x;

	noffset_x = 0;
	while (c++ < data->ylen)
	{
		if (data->rc->angle >= 0 && data->rc->angle < 180) //SOUTH
		{
			noffset_x = (HITBOX) * (tanf((90 - data->rc->angle) * M_PI / 180));
			newy += HITBOX;
			newx += noffset_x;
			node = get_node_at(data->nodes, (newx / HITBOX), (newy / HITBOX));
			if (node != NULL)
				if (node->type == WALL)
					break ;
		}
		else if (data->rc->angle >= 180 && data->rc->angle < 360) //NORTH
		{
			noffset_x = (HITBOX) * (tanf((90 - data->rc->angle) * M_PI / 180));
			newy -= HITBOX;
			newx -= noffset_x;
			node = get_node_at(data->nodes, (newx / HITBOX), (newy / HITBOX) - 1);
			if (node != NULL)
				if (node->type == WALL)
					break ;
		}
	}
	data->distance[x].h = sqrt(fabs((data->player.x - newx)
				* (data->player.x - newx))
			+ fabs((data->player.y - newy)
				* (data->player.y - newy)));
}

void	init_horizontal_dist(t_data *data, double py, int x)
{
	double	newx;
	double	newy;
	int		c;
	t_node	*node;

	newx = 0;
	newy = 0;
	c = 0;
	data->rc->offset_x = 0;
	data->rc->offset_y = 0;
	node = NULL;
	if (data->rc->angle >= 0 && data->rc->angle < 180) //SOUTH ---- lignes bleues/blanches quand long distance
	{
		data->rc->offset_y = HITBOX - py;
		data->rc->offset_x = (data->rc->offset_y) * (tanf((90 - data->rc->angle) * M_PI / 180));
		newx = data->player.x + data->rc->offset_x;
		newy = data->player.y + data->rc->offset_y;
		node = get_node_at(data->nodes, (newx / HITBOX), (newy / HITBOX));
	}
	else if (data->rc->angle >= 180 && data->rc->angle < 360) //NORTH
	{
		data->rc->offset_y = py;
		data->rc->offset_x = (data->rc->offset_y) * (tanf((90 - data->rc->angle) * M_PI / 180));
		newx = data->player.x - data->rc->offset_x;
		newy = data->player.y - data->rc->offset_y;
		node = get_node_at(data->nodes, (newx / HITBOX), (newy / HITBOX) - 1);
	}
	if (node != NULL && node->type == WALL)
		c = data->ylen;
	get_horizontal_dist(data, x, c, newx, newy);
}
