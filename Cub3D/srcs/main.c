/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/13 16:58:44 by jtollena         ###   ########.fr       */
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

void	move_player(int key, t_data *data)
{
	int speed = 5;

	mlx_pixel_put(data->prog->mlx, data->prog->win, 150, 150, 0x000000);
	printf("  %f\n", (data->playerx + speed) / HITBOX);
	printf("- %f\n", (data->playerx + speed) / HITBOX + HITBOX - 1);
	
	if ((key == KEY_W || key == KEY_UP) && is_node_free((data->playerx) / HITBOX, (data->playery - speed) / HITBOX, data) == 1
			&& is_node_free((data->playerx + PLAYER_SIZE) / HITBOX, (data->playery - speed) / HITBOX, data) == 1
			&& is_node_free((data->playerx) / HITBOX, (data->playery + PLAYER_SIZE - speed) / HITBOX, data) == 1
			&& is_node_free((data->playerx + PLAYER_SIZE) / HITBOX, (data->playery + PLAYER_SIZE - speed) / HITBOX, data) == 1)
		data->playery -= speed;
	else if ((key == KEY_S || key == KEY_DOWN) && is_node_free((data->playerx) / HITBOX, (data->playery + speed) / HITBOX, data) == 1
			&& is_node_free((data->playerx + PLAYER_SIZE) / HITBOX, (data->playery + speed) / HITBOX, data) == 1
			&& is_node_free((data->playerx) / HITBOX, (data->playery + PLAYER_SIZE + speed) / HITBOX, data) == 1
			&& is_node_free((data->playerx + PLAYER_SIZE) / HITBOX, (data->playery + PLAYER_SIZE + speed) / HITBOX, data) == 1)
		data->playery += speed;
	else if ((key == KEY_A || key == KEY_LEFT) && is_node_free((data->playerx - speed) / HITBOX, (data->playery) / HITBOX, data) == 1
			&& is_node_free((data->playerx + PLAYER_SIZE - speed) / HITBOX, (data->playery) / HITBOX, data) == 1
			&& is_node_free((data->playerx - speed) / HITBOX, (data->playery + PLAYER_SIZE) / HITBOX, data) == 1
			&& is_node_free((data->playerx + PLAYER_SIZE - speed) / HITBOX, (data->playery + PLAYER_SIZE) / HITBOX, data) == 1)
		data->playerx -= speed;
	else if ((key == KEY_D || key == KEY_RIGHT) && is_node_free((data->playerx + speed) / HITBOX, (data->playery) / HITBOX, data) == 1
			&& is_node_free((data->playerx + PLAYER_SIZE + speed) / HITBOX, (data->playery) / HITBOX, data) == 1
			&& is_node_free((data->playerx + speed) / HITBOX, (data->playery + PLAYER_SIZE) / HITBOX, data) == 1
			&& is_node_free((data->playerx + PLAYER_SIZE + speed) / HITBOX, (data->playery + PLAYER_SIZE) / HITBOX, data) == 1)
		data->playerx += speed;
	map_init(data);
}

int	event_key_pressed(int keycode, t_data *datav)
{
	if (keycode == KEY_W || keycode == KEY_A 
		|| keycode == KEY_D || keycode == KEY_S
		|| keycode == KEY_UP || keycode == KEY_RIGHT 
		|| keycode == KEY_LEFT || keycode == KEY_DOWN)
		move_player(keycode, datav);
	else if (keycode == KEY_ESCAPE)
		close_window(datav);
	return (1);
}

void	init_hooks(t_data *data)
{
	mlx_hook((*data).prog->win, 2, 0, &event_key_pressed, (data));
	mlx_hook((*data).prog->win, 17, 0, &close_window, (data));
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
	data.playery = 16;
	data.playerx = 16;
	prog = get_prog();
	data.prog = &prog;
	init_list(argv, reader, filechars, &data);
	init_hooks(&data);
	init_images(&data);
	system("leaks cub3d");
	return (argc);
}
