/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:48:38 by jtollena          #+#    #+#             */
/*   Updated: 2024/07/05 11:22:21 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	is_in_minimap(int x, int y, t_data *data)
{
	if ((x >= data->minimap_x && x <= data->minimap_endx) && (y >= data->minimap_y && y <= data->minimap_endy))
		return (1);
	return (0);
}

void	write_cubes_map(int color, int startX, int startY, t_data *data, int tailleX, int tailleY)
{
	int x = 0;
	int y = 0;
	while (x < tailleX){
		y = 0;
		while (y < tailleY){
			my_mlx_pixel_put(&data->img, x + startX, y + startY, color);
			y++;
		}
		x++;
	}
}

void draw_line_map(t_data *data, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (1) {
		my_mlx_pixel_put(&data->img, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void draw_oriented_player_map(int color, double startX, double startY, t_data *data, int taille, double yaw_degrees) {
    double yaw_radians = (yaw_degrees - 125) * M_PI / 180.0;

    double x0 = startX;
    double y0 = startY;

    double x1 = x0 + (double)(taille * cos(yaw_radians));
    double y1 = y0 + (double)(taille * sin(yaw_radians));

    double x2 = x0 + (double)(taille * cos(yaw_radians + 2.0 * M_PI / 3.0));
    double y2 = y0 + (double)(taille * sin(yaw_radians + 2.0 * M_PI / 3.0));

    double x3 = x0 + (double)(taille * cos(yaw_radians - 2.0 * M_PI / 3.0));
    double y3 = y0 + (double)(taille * sin(yaw_radians - 2.0 * M_PI / 3.0));

    draw_line_map(data, x0, y0, x1, y1, color);
    draw_line_map(data, x1, y1, x2, y2, color);
    draw_line_map(data, x2, y2, x3, y3, color);
    draw_line_map(data, x3, y3, x0, y0, color);
}

void	check_nodes_arround_map(t_node node, t_data *data, int is_player)
{
	t_node *node1 = get_node_at(data->nodes, node.x, node.y + 1);
	t_node *node2 = get_node_at(data->nodes, node.x, node.y - 1);
	t_node *node3 = get_node_at(data->nodes, node.x - 1, node.y);
	t_node *node4 = get_node_at(data->nodes, node.x + 1, node.y);

	if (node1 != NULL && node1->type == WALL)
		write_cubes_map(0xFF0000, (data->minimap_x + MINIMAP_HITBOX / 2) + node1->x * MINIMAP_HITBOX, (data->minimap_y + MINIMAP_HITBOX / 2) + node1->y * MINIMAP_HITBOX, data, MINIMAP_HITBOX, MINIMAP_HITBOX);
	if (node2 != NULL && node2->type == WALL)
		write_cubes_map(0xFF0000, (data->minimap_x + MINIMAP_HITBOX / 2) + node2->x * MINIMAP_HITBOX, (data->minimap_y + MINIMAP_HITBOX / 2) + node2->y * MINIMAP_HITBOX, data, MINIMAP_HITBOX, MINIMAP_HITBOX);
	if (node3 != NULL && node3->type == WALL)
		write_cubes_map(0xFF0000, (data->minimap_x + MINIMAP_HITBOX / 2) + node3->x * MINIMAP_HITBOX, (data->minimap_y + MINIMAP_HITBOX / 2) + node3->y * MINIMAP_HITBOX, data, MINIMAP_HITBOX, MINIMAP_HITBOX);
	if (node4 != NULL && node4->type == WALL)
		write_cubes_map(0xFF0000, (data->minimap_x + MINIMAP_HITBOX / 2) + node4->x * MINIMAP_HITBOX, (data->minimap_y + MINIMAP_HITBOX / 2) + node4->y * MINIMAP_HITBOX, data, MINIMAP_HITBOX, MINIMAP_HITBOX);

	if (is_player)
	{
		node1 = get_node_at(data->nodes, node.x + 1, node.y + 1);
		node2 = get_node_at(data->nodes, node.x + 1, node.y - 1);
		node3 = get_node_at(data->nodes, node.x - 1, node.y + 1);
		node4 = get_node_at(data->nodes, node.x - 1, node.y - 1);

		if (node1 != NULL && node1->type == WALL)
			write_cubes_map(0xFF0000, (data->minimap_x + MINIMAP_HITBOX / 2) + node1->x * MINIMAP_HITBOX, (data->minimap_y + MINIMAP_HITBOX / 2) + node1->y * MINIMAP_HITBOX, data, MINIMAP_HITBOX, MINIMAP_HITBOX);
		if (node2 != NULL && node2->type == WALL)
			write_cubes_map(0xFF0000, (data->minimap_x + MINIMAP_HITBOX / 2) + node2->x * MINIMAP_HITBOX, (data->minimap_y + MINIMAP_HITBOX / 2) + node2->y * MINIMAP_HITBOX, data, MINIMAP_HITBOX, MINIMAP_HITBOX);
		if (node3 != NULL && node3->type == WALL)
			write_cubes_map(0xFF0000, (data->minimap_x + MINIMAP_HITBOX / 2) + node3->x * MINIMAP_HITBOX, (data->minimap_y + MINIMAP_HITBOX / 2) + node3->y * MINIMAP_HITBOX, data, MINIMAP_HITBOX, MINIMAP_HITBOX);
		if (node4 != NULL && node4->type == WALL)
			write_cubes_map(0xFF0000, (data->minimap_x + MINIMAP_HITBOX / 2) + node4->x * MINIMAP_HITBOX, (data->minimap_y + MINIMAP_HITBOX / 2) + node4->y * MINIMAP_HITBOX, data, MINIMAP_HITBOX, MINIMAP_HITBOX);
	}
}

int	draw_minimap(t_data *data)
{
	int i = 0;
	if (!data->in_menu)
	{
		write_cubes_map(0x33CCFF, (MINIMAP_HITBOX / 2), (MINIMAP_HITBOX / 2), data, MINIMAP_HITBOX * (get_map_width(data) + 1), MINIMAP_HITBOX * (get_map_height(data) + 1));
		data->minimap_x = (MINIMAP_HITBOX / 2);
		data->minimap_y = (MINIMAP_HITBOX / 2);
		data->minimap_endx = data->minimap_x + MINIMAP_HITBOX * (get_map_width(data) + 1);
		data->minimap_endy = data->minimap_y + MINIMAP_HITBOX * (get_map_height(data) + 1);

		t_node *list = (data->nodes);
		while (list[i].type != ENDL)
		{
			if (list[i].type == WALL)
				write_cubes_map(0xFF0000, ((list[i].x + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2), ((list[i].y + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2), data, MINIMAP_HITBOX, MINIMAP_HITBOX);
			if (list[i].type == DOOR)
			{
				if (list[i].direction == LAT)
					write_cubes_map(0x0FFF00, (((list[i].x + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2)) + list[i].door_loc, ((list[i].y + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2), data, MINIMAP_HITBOX, MINIMAP_HITBOX);
				else
					write_cubes_map(0x0FFF00, (((list[i].x + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2)), (((list[i].y + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2)) + list[i].door_loc, data, MINIMAP_HITBOX, MINIMAP_HITBOX);
			}
			i++;
		}
		draw_oriented_player_map(0xFFFFFF, (data->minimap_x + MINIMAP_HITBOX / 2) + (int)(data->player.x * ((float)MINIMAP_HITBOX / HITBOX)), (data->minimap_y + MINIMAP_HITBOX / 2) + (int)(data->player.y * ((float)MINIMAP_HITBOX / HITBOX)), data, PLAYER_SIZE, data->player.yaw);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
