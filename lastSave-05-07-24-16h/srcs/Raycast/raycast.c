/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:42:59 by caymard           #+#    #+#             */
/*   Updated: 2024/07/05 16:16:50 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

//------------------------------------------PLAYER_MINIMAP------------------------------------------

void	player_cursor_minimap(t_data *data)
{
	if (data->player.oldx != data->player.x
		|| data->player.oldy != data->player.y
		|| data->player.oldyaw != data->player.yaw)
	{
		check_nodes_arround_map(*get_node_at(data->nodes, data->player.x / HITBOX, data->player.y / HITBOX), data, 1);
		draw_oriented_player_map(0x33CCFF, (data->minimap_x + MINIMAP_HITBOX / 2) + (int)(data->player.oldx * ((float)MINIMAP_HITBOX / HITBOX)), (data->minimap_y + MINIMAP_HITBOX / 2) + (int)(data->player.oldy * ((float)MINIMAP_HITBOX / HITBOX)), data, PLAYER_SIZE, data->player.oldyaw);
		draw_oriented_player_map(0xFFFFFF, (data->minimap_x + MINIMAP_HITBOX / 2) + (int)(data->player.x * ((float)MINIMAP_HITBOX / HITBOX)), (data->minimap_y + MINIMAP_HITBOX / 2) + (int)(data->player.y * ((float)MINIMAP_HITBOX / HITBOX)), data, PLAYER_SIZE, data->player.yaw);
	}
}

//------------------------------------------CHECK_DOOR------------------------------------------

void	check_door(t_data *data)
{
	int		i;
	t_node	*list;

	i = 0;
	list = (data->nodes);
	while (list[i].type != ENDL)
	{
		if (list[i].type == DOOR)
		{
			if (list[i].direction == LAT)
				write_cubes_map(0x33CCFF, (data->minimap_x + MINIMAP_HITBOX / 2) + (list[i].x * MINIMAP_HITBOX) + list[i].door_loc, (data->minimap_y + MINIMAP_HITBOX / 2) + list[i].y * MINIMAP_HITBOX, data, MINIMAP_HITBOX - list[i].door_loc, MINIMAP_HITBOX);
			else
				write_cubes_map(0x33CCFF, (data->minimap_x + MINIMAP_HITBOX / 2) + (list[i].x * MINIMAP_HITBOX), (data->minimap_y + MINIMAP_HITBOX / 2) + (list[i].y * MINIMAP_HITBOX) + list[i].door_loc, data, MINIMAP_HITBOX, MINIMAP_HITBOX - list[i].door_loc);
			if (!list[i].running_door)
				toggle_door(&list[i], data);
			if (list[i].direction == LAT)
				write_cubes_map(0x0FFF00, (data->minimap_x + MINIMAP_HITBOX / 2) + (list[i].x * MINIMAP_HITBOX) + list[i].door_loc, (data->minimap_y + MINIMAP_HITBOX / 2) + list[i].y * MINIMAP_HITBOX, data, MINIMAP_HITBOX - list[i].door_loc, MINIMAP_HITBOX);
			else
				write_cubes_map(0x0FFF00, (data->minimap_x + MINIMAP_HITBOX / 2) + (list[i].x * MINIMAP_HITBOX), (data->minimap_y + MINIMAP_HITBOX / 2) + (list[i].y * MINIMAP_HITBOX) + list[i].door_loc, data, MINIMAP_HITBOX, MINIMAP_HITBOX - list[i].door_loc);
		}
		i++;
	}
}

void	get_colomn(t_data *data)
{
	int	mpx = data->minimap_x;
	int	mpy = data->minimap_y;
	int	mpex = data->minimap_endx;
	int	mpey = data->minimap_endy;
	int	y;
	int	x = -1;
	while (++x < WIDTH)
	{
		float distanceToPoint = (data->distance[x].d);

		int colour = 0xFFFFFF;
		if (data->distance[x].ttype == 0) // EAST
			colour = 0x0000FF;
		else if (data->distance[x].ttype == 1) // NORTH
			colour = 0x00FF00;
		else if (data->distance[x].ttype == 2) // WEST
			colour = 0xFF0000;
		else if (data->distance[x].ttype == 3) // SOUTH
			colour = 0x000000;

		y = -1;
		float wall_height = (HITBOX * HEIGHT) / (distanceToPoint);
		int begin = (HEIGHT / 2) - (wall_height / 2) + data->player.pitch;
		int end = (HEIGHT / 2) + (wall_height / 2) + data->player.pitch;

	// while (++y < HEIGHT)
	// {
	// 	tex_y = (int)pos_ver & (data->texture[dir].height - 1);
	// 	pos_ver += step;
	// 	if (y < begin)
	// 		data->img.addr[y * data->img.length / 4 + x] = data->c;
	// 	else if (y <= end && y < HEIGHT && x < WIDTH)
	// 		data->img.addr[y * data->img.length / 4 + x] = data->texture[dir].addr[tex_y * data->texture[dir].length / 4 + tex_x];
	// 	else
	// 		data->img.addr[y * data->img.length / 4 + x] = data->f;
	// }
	// int tex_x = (int)(data->rc->wall_x * data->texture[dir].width);
	// if ((!data->rc->side && data->rc->ray_dir_x > 0)
	// 	|| (data->rc->side == 1 && data->rc->ray_dir_y < 0))
	// 	tex_x = data->texture[dir].width - tex_x - 1;
	// double step = data->texture[0].height / wall_height;
	// double pos_ver = (begin - HEIGHT / 2 + end / 2) * step;
	// while (++y < HEIGHT)
	// {
	// 	tex_y = (int)pos_ver & (data->texture[data->distance[x].ttype].height - 1);
	// 	pos_ver += step;
	// 	if (y < begin)
	// 		data->img.addr[y * data->img.length / 4 + x] = data->c;
	// 	else if (y <= end && y < HEIGHT && x < WIDTH)
	// 		data->img.addr[y * data->img.length / 4 + x] = data->texture[data->distance[x].ttype].addr[tex_y * data->texture[data->distance[x].ttype].length / 4 + tex_x];
	// 	else
	// 		data->img.addr[y * data->img.length / 4 + x] = data->f;
	// }

		while(++y < begin)
			if (x < WIDTH && y < HEIGHT)
				if (!((x > mpx && x < mpex) && (y > mpy && y < mpey)))
					my_mlx_pixel_put(&data->img, x, y, data->c);
		y = begin - 1;
		while (++y < end)
			if (x < WIDTH - 1 && y < HEIGHT - 1 && x > 0 && y > 0)
				if (!((x > mpx && x < mpex) && (y > mpy && y < mpey)))
					my_mlx_pixel_put(&data->img, x, y, colour);
		y--;
		while (++y < HEIGHT)
			if (x < WIDTH && y < HEIGHT )
				if (!((x > mpx && x < mpex) && (y > mpy && y < mpey)))
					my_mlx_pixel_put(&data->img, x, y, data->f);
	}
}

//---------------------LOOP---------------------//
int	map_loop(t_data *data)
{
	mlx_clear_window (data->mlx, data->win);
	int x = -1;
	float degree = ((float)data->player.yaw + 90) - FOV / 2;
	float degree_offset = (FOV / 2);
	
	x = -1;
	// my_mlx_pixel_put(&data->img, data->player.x, data->player.y, 0x0000FF); //ligne bleue trace joueur
	while (++x < WIDTH)
	{
		data->distance[x].h = -1;
		data->distance[x].v = -1;

		data->rc->angle = degree - 90;
		while (data->rc->angle < 0)
			data->rc->angle += 360;
		while (data->rc->angle > 360)
			data->rc->angle -= 360;

		double px = data->player.x;
		while (px >= HITBOX)
			px -= HITBOX;
		double py = data->player.y;
		while (py >= HITBOX)
			py -= HITBOX;

		init_vertical_dist(data, px, x);
		init_horizontal_dist(data, py, x);
		data->distance[x].angle = degree_offset;
		degree += (FOV / WIDTH);
		degree_offset -= ((FOV / WIDTH));
	}
// void get_direction(double angle, t_direction *dir)
// {
// 	if (angle >= 0 && angle < 90)
// 		*dir = EAST;
// 	else if (angle >= 90 && angle < 180)
// 		*dir = SOUTH;
// 	else if (angle >= 180 && angle < 270)
// 		*dir = WEST;
// 	else
// 		*dir = NORTH;
// }
	x = -1;
	while (++x < WIDTH) //data->distance[x].ttype sert a dire si N/S ou E/W
	{
		data->distance[x].d = 10;
		if (data->distance[x].h != -1 && data->distance[x].v != -1)
		{
			if (data->distance[x].v < data->distance[x].h)
			{
				data->distance[x].d = fabs(data->distance[x].v);
				if (data->rc->angle > 90 && data->rc->angle < 270) //mauvaise condition
					data->distance[x].ttype = 2; //WEST
				else
					data->distance[x].ttype = 0; //EAST
			}
			else
			{
				data->distance[x].d = fabs(data->distance[x].h);
				if (data->rc->angle >= 0 && data->rc->angle < 180) //mauvaise condition
					data->distance[x].ttype = 3; //SOUTH
				else
					data->distance[x].ttype = 1; // NORTH
			}
		}
		// if (data->distance[x].ttype == data->distance[x].direction)
		// data->distance[x].d *= cosf(data->distance[x].angle);
			data->distance[x].d *= (cosf((data->distance[x].angle * M_PI / 180)));
	}
	printf("%f\n", cosf((data->distance[0].angle * M_PI / 180)));
	data->distance[WIDTH].type = NULLT;
	get_colomn(data);
	if (!data->in_menu)
	{
		get_mouse_move(data);
		move_player(data);
		check_door(data);
		player_cursor_minimap(data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	debug_affichage_frames(data);
	return (0);
}

