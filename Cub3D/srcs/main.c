/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/14 15:23:04 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	close_window(t_data *data)
{
	clear(data, NULL, NULL);
	system("leaks cub3d");
	exit(0);
	return (1);
}

void	init_list(char **argv, char *reader, int fileChars, t_data *data)
{
	data->nodes = malloc((count_map(get_fd(argv[1], NULL, (void *)reader), fileChars, reader) + 1) * sizeof(t_node));
	if (!data->nodes)
	{
		free(reader);
		exit_error("Failed malloc allocation", data, NULL, NULL);
	}
	data->nodes = read_map(get_fd(argv[1], (void *)data->nodes, (void *)reader), fileChars, reader, data);
}

t_prog	get_prog()
{
	t_prog	prog;

	prog.mlx = mlx_init();
	if (prog.mlx == NULL)
		exit_error("Failed malloc allocation", NULL, NULL, NULL);
	prog.win = mlx_new_window(prog.mlx, 10 * SIZE,
			10 * SIZE, "Cub3D by Syden_");
	if (prog.win == NULL)
		exit_error("Failed malloc allocation", NULL, prog.mlx, NULL);
	return (prog);
}

int	check_move_hitbox(t_data *data, int new_x, int new_y)
{
	// printf("Node checked %d %d\n", (new_x - PLAYER_SIZE) / HITBOX, (new_y) / HITBOX);
	// printf("Node checked right %d %d\n", (new_x + PLAYER_SIZE) / HITBOX, (new_y) / HITBOX);
	// printf("Node checked down %d %d\n", (new_x) / HITBOX, (new_y + PLAYER_SIZE) / HITBOX);
	// printf("Node checked right down %d %d\n", (new_x + PLAYER_SIZE) / HITBOX, (new_y + PLAYER_SIZE) / HITBOX);
	if (is_node_free((new_x - PLAYER_SIZE) / HITBOX, (new_y - PLAYER_SIZE) / HITBOX, data) == 1
		&& is_node_free((new_x + PLAYER_SIZE) / HITBOX, (new_y) / HITBOX, data) == 1
		&& is_node_free((new_x + PLAYER_SIZE) / HITBOX, (new_y + PLAYER_SIZE) / HITBOX, data) == 1
		&& is_node_free((new_x) / HITBOX, (new_y + PLAYER_SIZE) / HITBOX, data) == 1)
		return 1;
	return 0;
}

void	key_pressed(int key, t_data *data)
{
	if (key == KEY_W)
	{
		data->playerxw = data->playerspeed;
	}
	else if (key == KEY_S)
	{
		data->playerxs = data->playerspeed;
	}
	else if (key == KEY_A)
	{
		data->playerxa = data->playerspeed;
	}
	else if (key == KEY_D)
	{
		data->playerxd = data->playerspeed;
	}
	else if (key == KEY_RIGHT)
		data->playeryawr = data->playersensivity;
	else if (key == KEY_LEFT)
		data->playeryawl = data->playersensivity;
}

int	key_released(int key, t_data *data)
{
	if (key == KEY_W)
	{
		data->playerxw = 0;
	}
	else if (key == KEY_S)
	{
		data->playerxs = 0;
	}
	else if (key == KEY_A)
	{
		data->playerxa = 0;
	}
	else if (key == KEY_D)
	{
		data->playerxd = 0;
	}
	else if (key == KEY_RIGHT)
		data->playeryawr = 0;
	else if (key == KEY_LEFT)
		data->playeryawl = 0;
	return 0;
}

void	move_player(t_data *data)
{
	mlx_pixel_put(data->prog->mlx, data->prog->win, 150, 150, 0x000000);

	if (data->playeryawr != 0)
		data->playeryaw += data->playeryawr;
	if (data->playeryawl != 0)
		data->playeryaw -= data->playeryawl;
	float yaw_radians = data->playeryaw * M_PI / 180.0;
	// printf("%d\n", data->playerxw);
	int oldx = data->newplayerx;
	int oldy = data->newplayery;
	// if (data->playerxw != 0 || data->playerxs != 0 || data->playerxa != 0 || data->playerxd != 0)
	// {
	// 	float move_length = sqrt(data->playerxw * data->playerxw + data->playerxs * data->playerxs +
	// 							data->playerxa * data->playerxa + data->playerxd * data->playerxd);
	// 	printf("%f\n", move_length);
	// 	float move_factor = 0.0;
	// 	if (move_length != 0.0)
	// 	{
	// 		move_factor = 1.0 / move_length;
	// 	}
	// 	float move_direction = yaw_radians;

	// 	if (data->playerxs != 0)
	// 	{
	// 		data->newplayerx -= data->playerxs * move_factor * cos(move_direction);
	// 		data->newplayery -= data->playerxs * move_factor * sin(move_direction);
	// 	}

	// 	if (data->playerxw != 0)
	// 	{
	// 		data->newplayerx += data->playerxw * move_factor * cos(move_direction);
	// 		data->newplayery += data->playerxw * move_factor * sin(move_direction);
	// 	}

	// 	if (data->playerxd != 0)
	// 	{
	// 		data->newplayerx += data->playerxd * move_factor * cos(move_direction + M_PI / 2);
	// 		data->newplayery += data->playerxd * move_factor * sin(move_direction + M_PI / 2);
	// 	}

	// 	if (data->playerxa != 0)
	// 	{
	// 		data->newplayerx += data->playerxa * move_factor * cos(move_direction - M_PI / 2);
	// 		data->newplayery += data->playerxa * move_factor * sin(move_direction - M_PI / 2);
	// 	}
	// }
	if (data->playerxw != 0)
	{
		data->newplayerx += data->playerxw * cos(yaw_radians);
		data->newplayery += data->playerxw * sin(yaw_radians);
	}
	if (data->playerxs != 0)
	{
		data->newplayerx -= data->playerxs * cos(yaw_radians);
		data->newplayery -= data->playerxs * sin(yaw_radians);
	}
	if (data->playerxa != 0)
	{
		data->newplayerx += data->playerxa * cos(yaw_radians - M_PI / 2);
		data->newplayery += data->playerxa * sin(yaw_radians - M_PI / 2);
	}
	if (data->playerxd != 0)
	{
		data->newplayerx += data->playerxd * cos(yaw_radians + M_PI / 2);
		data->newplayery += data->playerxd * sin(yaw_radians + M_PI / 2);
	}
	if(check_move_hitbox(data, data->newplayerx, data->newplayery))
	{
		data->playerx = data->newplayerx;
		data->playery = data->newplayery;
		check_to_door(data, data->newplayerx, data->newplayery);
	}
	else
	{
		data->newplayerx = oldx;
		data->newplayery = oldy;
	}
	return ;
}

int	event_key_pressed(int keycode, t_data *datav)
{
	if (keycode == KEY_W || keycode == KEY_A 
		|| keycode == KEY_D || keycode == KEY_S
		|| keycode == KEY_UP || keycode == KEY_RIGHT 
		|| keycode == KEY_LEFT || keycode == KEY_DOWN)
		key_pressed(keycode, datav);
	else if (keycode == KEY_ESCAPE)
		close_window(datav);
	return (1);
}

void	init_hooks(t_data *data)
{
	mlx_hook((*data).prog->win, 2, 0, &event_key_pressed, (data));
	mlx_hook((*data).prog->win, 3, 0, &key_released, (data));
	mlx_hook((*data).prog->win, 17, 0, &close_window, (data));
	mlx_loop_hook(data->prog->mlx, map_init, data);
	mlx_loop((*data).prog->mlx);
}

void init_images(t_data *data)
{
	// int	i = 0;
	// while(data->nodes[i].type != NULLT)
	// {
	// 	if (data->nodes[i].type == FLOOR);
	// 		data->nodes[i].img_top
	// }
}

int	main(int argc, char **argv)
{
	int		filechars;
	char	*reader;
	t_prog	prog;
	t_data	data;

	if (argc != 2)
		exit_error("You must put a map path as argument.", NULL, NULL, NULL);
	filechars = file_chars(argv[1]);
	reader = malloc((filechars + 1) * sizeof(char));
	if (!reader)
		exit_error("Failed malloc allocation", NULL, NULL, NULL);
	reader[filechars] = 0;
	data.prog = NULL;
	data.playery = 25;
	data.playerx = 25;
	data.playerspeed = 2;
	data.playersensivity = 4;
	data.playerxa = 0;
	data.playerxs = 0;
	data.playerxw = 0;
	data.playerxd = 0;
	data.playeryawl = 0;
	data.playeryawr = 0;
	data.newplayery = data.playery;
	data.newplayerx = data.playerx;
	prog = get_prog();
	data.prog = &prog;
	init_list(argv, reader, filechars, &data);
	init_hooks(&data);
	init_images(&data);
	system("leaks cub3d");
	return (argc);
}
