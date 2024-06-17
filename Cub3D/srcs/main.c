/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/17 15:32:52 by jtollena         ###   ########.fr       */
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
	prog.win = mlx_new_window(prog.mlx, 10 * SIZE, 10 * SIZE, "Cub3D by Syden_");
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
		data->player.forwarding = data->player.speed;
	}
	else if (key == KEY_S)
	{
		data->player.backwarding = data->player.speed;
	}
	else if (key == KEY_A)
	{
		data->player.lefting = data->player.speed;
	}
	else if (key == KEY_D)
	{
		data->player.righting = data->player.speed;
	}
	else if (key == KEY_RIGHT)
		data->player.righting_yaw_key = data->player.sensivity;
	else if (key == KEY_LEFT)
		data->player.lefting_yaw_key = data->player.sensivity;
}

int	key_released(int key, t_data *data)
{
	if (key == KEY_W)
	{
		data->player.forwarding = 0;
	}
	else if (key == KEY_S)
	{
		data->player.backwarding = 0;
	}
	else if (key == KEY_A)
	{
		data->player.lefting = 0;
	}
	else if (key == KEY_D)
	{
		data->player.righting = 0;
	}
	else if (key == KEY_RIGHT)
		data->player.righting_yaw_key = 0;
	else if (key == KEY_LEFT)
		data->player.lefting_yaw_key = 0;
	return 0;
}

void	move_player(t_data *data)
{
	mlx_pixel_put(data->prog->mlx, data->prog->win, 150, 150, 0x000000);
	
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
	
	// CALCULS COORDONNEES DEPLACEMENTS
	float yaw_radians = (data->player.yaw) * (M_PI / 180.0);
	int oldx = data->player.newx;
	int oldy = data->player.newy;
	if (data->player.forwarding != 0)
	{
		data->player.newx += data->player.forwarding * cos(yaw_radians);
		data->player.newy += data->player.forwarding * sin(yaw_radians);
	}
	if (data->player.backwarding != 0)
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
int mouse_hook(int x,int y,t_data *data)
{
	// printf("%d %d\n", x, y);
	return 0;
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
	mlx_mouse_hide();
	mlx_do_key_autorepeaton((*data).prog->mlx);
	mlx_mouse_move(data->prog->win, (SIZE * 10 / 2), (SIZE * 10 / 2));
	mlx_hook((*data).prog->win, 2, 0, &event_key_pressed, (data));
	mlx_hook((*data).prog->win, 3, 0, &key_released, (data));
	mlx_hook((*data).prog->win, 17, 0, &close_window, (data));
	mlx_hook((*data).prog->win, 6, 0, &mouse_hook, (data));
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

t_player	init_player(t_node spawn)
{
	t_player	player;

	player.speed = 10;
	player.sensivity = 11;
	player.forwarding = 0;
	player.lefting = 0;
	player.backwarding = 0;
	player.righting = 0;
	player.righting_yaw = 0;
	player.lefting_yaw = 0;
	player.righting_yaw_key = 0;
	player.lefting_yaw_key = 0;
	player.righting_pitch = 0;
	player.lefting_pitch = 0;
	player.x = spawn.x * HITBOX + (HITBOX / 2);
	player.y = spawn.y * HITBOX + (HITBOX / 2);
	player.newx = player.x;
	player.newy = player.y;
	if (spawn.direction == NORTH)
		player.yaw = 270;
	else if (spawn.direction == EAST)
		player.yaw = 0;
	else if (spawn.direction == SOUTH)
		player.yaw = 90;
	else if (spawn.direction == WEST)
		player.yaw = 180;
	return (player.pitch = 0, player);
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
	data.mousex = NULL;
	data.mousey = NULL;
	prog = get_prog();
	data.prog = &prog;
	init_list(argv, reader, filechars, &data);
	t_node spawn = find_spawn_point(data.nodes);
	data.player = init_player(spawn);
	data.mousex = malloc(sizeof(int));
	data.mousey = malloc(sizeof(int));
	init_hooks(&data);
	init_images(&data);
	system("leaks cub3d");
	return (argc);
}
