/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/25 08:55:38 by jtollena         ###   ########.fr       */
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
		exit_error(ERROR_ALLOCATION, data, NULL, NULL);
	}
	data->nodes = read_map(get_fd(argv[1], (void *)data->nodes, (void *)reader), fileChars, reader, data);
}

t_prog	get_prog()
{
	t_prog	prog;

	prog.mlx = mlx_init();
	if (prog.mlx == NULL)
		exit_error(ERROR_ALLOCATION, NULL, NULL, NULL);
	prog.win = mlx_new_window(prog.mlx, WIDTH, HEIGHT, "Cub3D by Syden_");
	if (prog.win == NULL)
		exit_error(ERROR_ALLOCATION, NULL, prog.mlx, NULL);
	return (prog);
}

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

void draw_menu(t_data *data)
{
    int	x;
	int	y;

    for (x = 0; x < WIDTH; x++)
        for (y = 0; y < HEIGHT; y++)
            mlx_pixel_put(data->prog->mlx, data->prog->win, x, y, 0x000000);
    for (x = 100; x < 180; x++)
        for (y = 100; y < 150; y++)
            mlx_pixel_put(data->prog->mlx, data->prog->win, x, y, 0x00FF00);
    for (x = 200; x < 280; x++)
        for (y = 100; y < 150; y++)
            mlx_pixel_put(data->prog->mlx, data->prog->win, x, y, 0xAFC2D2);
	for (x = 300; x < 380; x++)
        for (y = 100; y < 150; y++)
            mlx_pixel_put(data->prog->mlx, data->prog->win, x, y, 0xFF0000);
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
	mlx_clear_window(data->prog->mlx, data->prog->win);
	mlx_mouse_hide();
	mlx_mouse_move(data->prog->win, (WIDTH / 2), (HEIGHT / 2));
	data->in_menu = 0;
	map_init(data);
	return (1);
}

void init_images(t_data *data)
{
}

int	main(int argc, char **argv)
{
	int		filechars;
	char	*reader;
	t_prog	prog;
	t_data	data;

	if (argc != 2)
		exit_error("You must put a map file path (.cub) as argument.", NULL, NULL, NULL);
	filechars = file_chars(argv[1]);
	reader = malloc((filechars + 1) * sizeof(char));
	if (!reader)
		exit_error(ERROR_ALLOCATION, NULL, NULL, NULL);
	reader[filechars] = 0;
	data.prog = NULL;
	data.mousex = NULL;
	data.mousey = NULL;
	data.in_menu = 0;
	prog = get_prog();
	data.prog = &prog;
	init_list(argv, reader, filechars, &data);
	t_node spawn = find_spawn_point(data.nodes);
	data.player = init_player(spawn);
	data.mousex = malloc(sizeof(int));
	data.mousey = malloc(sizeof(int));

	debugfps(&data);

	init_hooks(&data);
	init_images(&data);
	system("leaks cub3d");
	return (argc);
}
