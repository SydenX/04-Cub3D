/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/25 14:17:19 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	close_window(t_data *data)
{
	mlx_clear_window(data->prog->mlx, data->prog->win);
	mlx_destroy_window(data->prog->mlx, data->prog->win);
	free(data->nodes);
	free(data->prog->mlx);
	exit(0);
	return (1);
}

void	init_list(char **argv, char *reader, int fileChars, t_data *data)
{
	t_node	*list;

	list = malloc((count_map(get_fd(argv[1], NULL, (void *)reader), fileChars, reader) + 1) * sizeof(t_node));
	if (!list)
	{
		free(reader);
		exit_error("Failed malloc allocation", data, NULL, NULL);
	}
	data->nodes = &list;
	list = read_map(get_fd(argv[1], (void *)list, (void *)reader),
			fileChars, reader, data);
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
	mlx_pixel_put(data->prog->mlx, data->prog->win, 150, 150, 0x000000);
	if ((key == KEY_W || key == KEY_UP))
		data->playery -= 1;
	else if ((key == KEY_S || key == KEY_DOWN))
		data->playery += 1;
	else if ((key == KEY_A || key == KEY_LEFT))
		data->playerx -= 1;
	else if ((key == KEY_D || key == KEY_RIGHT))
		data->playerx += 1;
	map_init(data);
}

int	event_key_pressed(int keycode, void *datav)
{
	int i = 0;
	t_data *data = (t_data *)datav;
	t_node *list = *(data->nodes);
	while (list[i].type != ENDL) {
		printf("%d, %d - %d\n", list[i].type, list[i].x, list[i].y);
		i++;
	}
	return 1;
	// if (keycode == KEY_W || keycode == KEY_A 
	// 	|| keycode == KEY_D || keycode == KEY_S
	// 	|| keycode == KEY_UP || keycode == KEY_RIGHT 
	// 	|| keycode == KEY_LEFT || keycode == KEY_DOWN)
	// 	move_player(keycode, data);
	// else if (keycode == KEY_ESCAPE)
	// 	close_window(data);
	return (1);
}

void	s(t_data *data)
{
	mlx_hook(data->prog->win, 2, 0, &event_key_pressed, data);
	mlx_hook(data->prog->win, 17, 0, &close_window, data);
	mlx_loop(data->prog->mlx);
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
	data.playery = 0;
	data.playerx = 0;
	prog = get_prog();
	data.prog = &prog;
	data.nodes = malloc(sizeof(t_node *));
	init_list(argv, reader, filechars, &data);
	s(&data);
	// data.imgs = get_img(argv, *data.nodes, data.prog);
	// free(*(data.nodes));
	// system("leaks cub3d");
	return (argc);
}
