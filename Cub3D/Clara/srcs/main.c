/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/24 18:14:51 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	check_move_hitbox(t_data *data, int new_x, int new_y)
{
	if (is_node_free((new_x - PLAYER_SIZE) / HITBOX, (new_y - PLAYER_SIZE) / HITBOX, data) == 1
		&& is_node_free((new_x + PLAYER_SIZE) / HITBOX, (new_y) / HITBOX, data) == 1
		&& is_node_free((new_x + PLAYER_SIZE) / HITBOX, (new_y + PLAYER_SIZE) / HITBOX, data) == 1
		&& is_node_free((new_x) / HITBOX, (new_y + PLAYER_SIZE) / HITBOX, data) == 1)
		return (1);
	return (0);
}

void	move_player(t_data *data)
{
	// mlx_pixel_put(data->mlx, data->win, 150, 150, 0x000000);

	data->player.oldyaw = data->player.yaw;
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
	if (check_move_hitbox(data, data->player.newx, data->player.newy))
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

void	draw_menu(t_data *data)
{
	int	x;
	int	y;

	for (x = 0; x < WIDTH; x++)
		for (y = 0; y < HEIGHT; y++)
			my_mlx_pixel_put(&data->img, x, y, 0x000000);
	for (x = 100; x < 180; x++)
		for (y = 100; y < 150; y++)
			my_mlx_pixel_put(&data->img, x, y, 0x00FF00);
	for (x = 200; x < 280; x++)
		for (y = 100; y < 150; y++)
			my_mlx_pixel_put(&data->img, x, y, 0xAFC2D2);
	for (x = 300; x < 380; x++)
		for (y = 100; y < 150; y++)
			my_mlx_pixel_put(&data->img, x, y, 0xFF0000);
}

int	open_menu(t_data *data)
{
	if (!data->in_menu)
	{
		data->in_menu = 1;
		mlx_mouse_show();
		draw_menu(data);
		return (0);
	}
	mlx_clear_window(data->mlx, data->win);
	mlx_mouse_hide();
	mlx_mouse_move(data->win, (WIDTH / 2), (HEIGHT / 2));
	data->in_menu = 0;
	return (1);
}

int	visual(t_data *data)
{
	// char	*moves;

	move_player(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	update_img(data);
	// moves = get_moves(ft_itoa(data->moves++));
	// mlx_string_put(data->mlx, data->win, 15, 15, 0xFFFFFF, moves);
    // mlx_pixel_put(data->mlx, data->win, data->playerx, data->playery, 0xFFFFFF);
	// free(moves);
	return 0;
}

void	mlx_events(t_data *data)
{
	// mlx_mouse_hide(); //pb linux
	mlx_do_key_autorepeaton(data->mlx);
	// mlx_mouse_move(data->win, (WIDTH / 2), (HEIGHT / 2)); //pb linux
	mlx_hook(data->win, 2, 0, &event_key_pressed, (data));
	mlx_hook(data->win, 3, 0, &key_released, (data));
	mlx_mouse_hook(data->win, &mouse_hook, (data));
	mlx_hook(data->win, 17, 0, &close_window, (data));
	mlx_loop_hook(data->mlx, visual, data);
	mlx_loop(data->mlx);
}

int	rgb_to_int_to_char(t_data *data)
{
	data->f = (data->f_rgb.r << 16) + (data->f_rgb.g << 8) + data->f_rgb.b;
	data->c = (data->c_rgb.r << 16) + (data->c_rgb.g << 8) + data->c_rgb.b;
	return (0);
}

void	init_list(char **argv, char *reader, int fileChars, t_data *data)
{
	int		cm;
	int		fd;
	t_node	spawn;

	cm = count_map(get_fd(argv[1], NULL, (void *)reader), fileChars, reader);
	data->nodes = malloc((cm + 1) * sizeof(t_node));
	if (!data->nodes)
	{
		free(reader);
		exit_error(ERROR_ALLOCATION, data, NULL, NULL);
	}
	fd = get_fd(argv[1], (void *)data->nodes, (void *)reader);
	data->nodes = read_map(fd, fileChars, reader, data);
	spawn = find_spawn_point(data->nodes);
	data->player = init_player(spawn);
}

int	data_init(t_data *data)
{
	data->mousex = NULL;
	data->mousey = NULL;
	data->in_menu = 0;
	data->mousex = malloc(sizeof(int));
	data->mousey = malloc(sizeof(int));
	data->rc = malloc(sizeof(t_rays));
	if (!data->rc)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		filechars;
	char	*reader;

	if (ac != 2)
	{
		write(2, "You must put a map file path (.cub) as argument.\n", 49);
		return (1);
	}
	filechars = file_chars(av[1]);
	reader = malloc((filechars + 1) * sizeof(char));
	if (!reader)
		exit_error(ERROR_ALLOCATION, NULL, NULL, NULL);
	reader[filechars] = 0;
	if (data_init(&data))
		return (1); //free precedent
	preparing_window(&data, 0);
	init_list(av, reader, filechars, &data);
	if (rgb_to_int_to_char(&data))
		return (1);
	mlx_events(&data);
	system("leaks cub3d");
	return (0);
}
