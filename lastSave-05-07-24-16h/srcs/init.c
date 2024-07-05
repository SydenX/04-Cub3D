/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:57:03 by caymard           #+#    #+#             */
/*   Updated: 2024/07/05 11:10:30 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	init_list(char **argv, char *reader, int filechars, t_data *data)
{
	int		cm;
	int		fd;
	t_node	spawn;

	cm = count_map(get_fd(argv[1], NULL, (void *)reader), filechars, reader);
	data->nodes = malloc((cm + 1) * sizeof(t_node));
	if (!data->nodes)
	{
		free(reader);
		exit_error(ERROR_ALLOCATION, data, NULL, NULL); //return (0);
	}
	fd = get_fd(argv[1], (void *)data->nodes, (void *)reader);
	data->nodes = read_map(fd, filechars, reader, data);
	spawn = find_spawn_point(data->nodes);
	data->player = init_player(spawn);
	return (1);
}


// void	get_ray(t_data *data)
// {
// 	// if (data->rc->dir == NORTH)
// 	// {
// 	// 	data->rc->ray_dir_x = -1;
// 	// 	data->rc->ray_plan_y = 0.66;
// 	// }
// 	// else if (data->rc->dir == SOUTH)
// 	// {
// 	// 	data->rc->ray_dir_x = 1;
// 	// 	data->rc->ray_plan_y = -0.66;
// 	// }
// 	// else if (data->rc->dir == EAST)
// 	// {
// 	// 	data->rc->ray_dir_y = 1;
// 	// 	data->rc->ray_plan_x = 0.66;
// 	// }
// 	// else if (data->rc->dir == WEST)
// 	// {
// 	// 	data->rc->ray_dir_y = -1;
// 	// 	data->rc->ray_plan_x = -0.66;
// 	// }
// 	if (data->rc->dir == EAST)
// 		data->rc->angle = 0; // 0 degrees, east
// 	else if (data->rc->dir == SOUTH)
// 		data->rc->angle = M_PI / 2; // 90 degrees, south
// 	else if (data->rc->dir == WEST)
// 		data->rc->angle = M_PI; // 180 degrees, west
// 	else if (data->rc->dir == NORTH)
// 		data->rc->angle = 3 * M_PI / 2; // 270 degrees, north

// 	// Convert angle to direction vector
// 	data->rc->ray_dir_x = cos(data->rc->angle);
// 	data->rc->ray_dir_y = sin(data->rc->angle);

// 	// Assuming the plane is perpendicular to the direction vector
// 	// For simplicity, using a fixed plane distance of 0.66 from the player viewpoint
// 	data->rc->ray_plan_x = data->rc->ray_dir_y * 0.66; // Perpendicular to direction x
// 	data->rc->ray_plan_y = -data->rc->ray_dir_x * 0.66; // Perpendicular to direction y

// 	data->rc->map_x = data->player.x / HITBOX;
// 	data->rc->map_y = data->player.y / HITBOX;
// 	data->rc->pos_x = data->rc->map_x + 0.5;
// 	data->rc->pos_y = data->rc->map_y + 0.5;
// }

// void	init_dir(t_data *data)
// {
// 	// fprintf(stderr, "data->player.yaw: %f\n", data->player.yaw);
// 	if (data->player.yaw == 270)
// 		data->rc->dir = NORTH;
// 	else if (data->player.yaw == 0)
// 		data->rc->dir = EAST;
// 	else if (data->player.yaw == 90)
// 		data->rc->dir = SOUTH;
// 	else if (data->player.yaw == 180)
// 		data->rc->dir = WEST;
// }

int	data_init(t_data *data, char **av)
{
	int		filechars;
	char	*reader;

	filechars = file_chars(av[1]);
	reader = malloc((filechars + 1) * sizeof(char));
	if (!reader)
		exit_error(ERROR_ALLOCATION, NULL, NULL, NULL);
	reader[filechars] = 0;

	data->in_menu = 0;
	data->mousex = NULL;
	data->mousey = NULL;
	data->in_menu = 0;
	data->distance = malloc((WIDTH + 1) * sizeof(t_distance));
	data->mousex = malloc(sizeof(int));
	data->mousey = malloc(sizeof(int));
	if (!data->mousex || !data->mousey)
		return (1);
	data->rc = malloc(sizeof(t_rays));
	if (!data->rc)
		return (1); //free precedent
	// data->rc->ray_dir_x = 0;
	// data->rc->ray_dir_y = 0;
	// data->rc->ray_plan_x = 0;
	// data->rc->ray_plan_y = 0;
	preparing_window(data);
	if (!init_list(av, reader, filechars, data))
		return (1); //free precedent
	rgb_to_int(data);
	data->xlen = get_list_xlen(data->nodes);
	data->ylen = get_list_ylen(data->nodes);
	// get_ray(data);
	// init_dir(data);
	return (0);
}
