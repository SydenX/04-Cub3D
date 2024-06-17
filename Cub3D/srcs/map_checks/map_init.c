/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:48:38 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/17 15:32:39 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_node	*get_node(int x, int y, t_node *list)
{
	int	i = 0;
	while(list[i].type != ENDL)
	{
		if (list[i].x == x && list[i].y == y)
		{
			if (list[i].type == NULLT || list[i].type == ENDL)
				return NULL;
			return &list[i];
		}
		i++;
	}
	return NULL;
}

int	check_surrounded_points(t_node *list)
{
	int	i = 0;
	while(list[i].type != ENDL)
	{
		if ((list[i].type != WALL) && list[i].type != NULLT)
		{
			if (get_node(list[i].x - 1, list[i].y, list) == NULL)
				return 0;
			if (get_node(list[i].x + 1, list[i].y, list) == NULL)
				return 0;
			if (get_node(list[i].x, list[i].y - 1, list) == NULL)
				return 0;
			if (get_node(list[i].x, list[i].y + 1, list) == NULL)
				return 0;
		}
		i++;
	}
	return 1;
}

int	check_surrounded_doors(t_node *list)
{
	int	i = 0;
	int x = 0;
	int y = 0;
	while(list[i].type != ENDL)
	{
		x = 0;
		y = 0;
		if (list[i].type == DOOR)
		{
			if (get_node(list[i].x - 1, list[i].y, list) != NULL)
				if(get_node(list[i].x - 1, list[i].y, list)->type == WALL)
					x++;
			if (get_node(list[i].x + 1, list[i].y, list) != NULL)
				if(get_node(list[i].x + 1, list[i].y, list)->type == WALL)
					x++;
			if (get_node(list[i].x, list[i].y + 1, list) != NULL)
				if(get_node(list[i].x, list[i].y + 1, list)->type == WALL)
					y++;
			if (get_node(list[i].x, list[i].y - 1, list) != NULL)
				if(get_node(list[i].x, list[i].y - 1, list)->type == WALL)
					y++;
			if (x == 2)
				list[i].direction = LAT;
			if (y == 2)
				list[i].direction = LONG;
			if (!(x == 2 && y == 0) && !(x == 0 && y == 2))
				return 0;
		}
		i++;
	}
	return 1;
}

void check_texture_file(char *path, char *reader, t_data *data, int type)
{
	int 	fd;
	int		img_width;
	int		img_height;
	void	*img;

	fd = open(path, O_RDONLY);
    if (fd != -1) {
		img = mlx_xpm_file_to_image(data->prog->mlx, path, &img_width, &img_height);
		if (img == NULL)
		{
			close(fd);
			return (error_texturefileincorect(path, (void *)reader, data));
		}
		if (type == 0)
			data->txt_path_west = img;
		if (type == 1)
			data->txt_path_north = img;
		if (type == 2)
			data->txt_path_east = img;
		if (type == 3)
			data->txt_path_south = img;
        close(fd);
		return ;
    }
	if (errno == 2)
		error_filedonotexist(path, (void *)reader, data);
	else
		error_fileerror(path, (void *)reader, data);
}

int read_texture(char *reader, t_node *list, t_data *data, int i)
{
	int		j;
	char	*path;
	int 	type;

	while (reader[i] != 0 && reader[i] != '\n')
	{
		while (reader[i] == ' ' || (reader[i] >= 9 && reader[i] < 13))
			i++;
		if ((reader[i] == 'W' && reader[i + 1] == 'E'))
			type = 0;
		else if ((reader[i] == 'N' && reader[i + 1] == 'O'))
			type = 1;
		else if ((reader[i] == 'E' && reader[i + 1] == 'A'))
			type = 2;
		else if ((reader[i] == 'S' && reader[i + 1] == 'O'))
			type = 3;
		else
			error_notformatted((void *)list, (void *)reader, data);
		i += 2;
		while ((reader[i] == ' ' || (reader[i] >= 9 && reader[i] < 13)) && reader[i] != '\n')
			i++;
		j = i;
		while (reader[i] != '\n' && reader[i] != 0)
			i++;
		if (reader[i] == 0)
			error_notformatted((void *)list, (void *)reader, data);
		path = ft_substr(reader, j, i - j);
		if (!path)
			error_allocation((void *)list, (void *)reader, data);
		if (ft_strlen(path) == 0)
			error_notformatted(path, (void *)reader, data);
		check_texture_file(path, reader, data, type);
		free(path);
	}
	return (1);
}

int read_rgb(char *reader, t_node *list, t_data *data, int i)
{
	int	isok;
	int	digit;
	int	isf;
	int	count;

	count = 0;
	if (reader[i++] == 'F')
		isf = 1;
	else
		isf = 0;
	isok = 0;
	digit = -1;
	while (reader[i] != 0 && reader[i] != '\n')
	{
		while ((reader[i] == ' ' || (reader[i] >= 9 && reader[i] < 13)) && reader[i] != '\n')
			i++;
		while (ft_isdigit(reader[i])){
			if (digit == -1)
				digit++;
			digit = (reader[i] - '0') + 10 * digit;
			i++;
		}
		if (((reader[i] == ',' && count < 2) || (reader[i] == '\n')) && digit >= 0 && digit <= 255)
		{
			if (isf)
			{
				if (count == 0)
					data->f.r = digit;
				else if (count == 1)
					data->f.g = digit;
				else if (count == 2)
					data->f.b = digit;
			}
			else
			{
				if (count == 0)
					data->c.r = digit;
				else if (count == 1)
					data->c.g = digit;
				else if (count == 2)
					data->c.b = digit;
			}
			digit = -1;
			count++;
			i++;
		}
		else
			error_notformatted((void *)list, (void *)reader, data);
	}
	return (1);
}

int	check_infos(char *reader, int i, t_node *list, t_data *data)
{
	int numberoftextures;
	int fc;

	numberoftextures = 0;
	fc = 0;
	while (reader[++i])
	{
		while (reader[i] == '\n' || reader[i] == ' '
			|| (reader[i] >= 9 && reader[i] < 13))
			i++;
		if (!reader[i])
			exit_error("0", data, (void *)list, (void *)reader);
		if ((reader[i] == 'N' && reader[i + 1] == 'O')
			|| (reader[i] == 'E' && reader[i + 1] == 'A')
			|| (reader[i] == 'S' && reader[i + 1] == 'O')
			|| (reader[i] == 'W' && reader[i + 1] == 'E')
			|| (reader[i] == 'F') || (reader[i] == 'C'))
		{
			if ((reader[i] == 'F') || (reader[i] == 'C'))
				fc += read_rgb(reader, list, data, i);
			else
				numberoftextures += read_texture(reader, list, data, i);
		}
		else
			error_notformatted((void *)list, (void *)reader, data);
		while (reader[i] != '\n')
			if (reader[i++] == 0)
				error_notformatted((void *)list, (void *)reader, data);
		if (numberoftextures == 4 && fc == 2)
			break ;
	}
	printf("%d %d %d\n", data->f.r, data->f.g, data->f.b);
	printf("%d %d %d\n", data->c.r, data->c.g, data->c.b);
	while (reader[i++] == '\n')
	{
	}
	if (reader[i] == 0)
		error_notformatted((void *)list, (void *)reader, data);
	return (i - 1);
}

t_node	*read_map(int fd, int x, char *reader, t_data *data)
{
	int		readable;
	int		i;
	int		j;
	int		y;
	t_node	*list;

	list = data->nodes;
	readable = 1;
	i = -1;
	j = 0;
	y = 0;
	readable = read(fd, reader, x);
	if (readable == -1)
		error_inputfile((void *)reader, (void *)list, data);
	close(fd);
	i = check_infos(reader, i, list, data);
	x = 0;
	while (reader[++i])
	{
		if (reader[i] == 9)
			error_notformatted((void *)list, (void *)reader, data);
		if (reader[i] != '\n')
			list[j++] = create_node(reader[i], x++, y);
		else
		{
			y++;
			x = 0;
		}
	}
	list[j] = create_node(1, 0, 0);
	if (check_surrounded_points(list) == 0)
		error_notsurrounded((void *)(list), (void *)reader, data);
	if (check_surrounded_doors(list) == 0)
		error_doornotparsedcorrectly((void *)(list), (void *)reader, data);
	return (free(reader), check_nodes_type(list, j));
	return NULL;
}

char	*get_moves(char *moves)
{
	char	*msg;

	if (!moves)
		return (NULL);
	msg = ft_strjoin("Total moves: ", moves);
	free(moves);
	return (msg);
}

void	write_cubes(int color, int startX, int startY, t_data *data, int taille)
{
	int x = 0;
	int y = 0;
	while (x < taille){
		y = 0;
		while (y < taille){
			mlx_pixel_put(data->prog->mlx, data->prog->win, x + startX, y + startY, color);
			y++;
		}
		x++;
	}
}

void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (1) {
        mlx_pixel_put(mlx, win, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void draw_oriented_player(int color, int startX, int startY, t_data *data, int taille, double yaw_degrees) {
    double yaw_radians = (yaw_degrees - 125) * M_PI / 180.0;

    int x0 = startX;
    int y0 = startY;

    int x1 = x0 + (int)(taille * cos(yaw_radians));
    int y1 = y0 + (int)(taille * sin(yaw_radians));

    int x2 = x0 + (int)(taille * cos(yaw_radians + 2.0 * M_PI / 3.0));
    int y2 = y0 + (int)(taille * sin(yaw_radians + 2.0 * M_PI / 3.0));

    int x3 = x0 + (int)(taille * cos(yaw_radians - 2.0 * M_PI / 3.0));
    int y3 = y0 + (int)(taille * sin(yaw_radians - 2.0 * M_PI / 3.0));

    draw_line(data->prog->mlx, data->prog->win, x0, y0, x1, y1, color);
    draw_line(data->prog->mlx, data->prog->win, x1, y1, x2, y2, color);
    draw_line(data->prog->mlx, data->prog->win, x2, y2, x3, y3, color);
    draw_line(data->prog->mlx, data->prog->win, x3, y3, x0, y0, color);
}

void	get_mouse_move(t_data *data)
{
	int	deadangle = 15;

	mlx_mouse_get_pos(data->prog->win, (data->mousex), (data->mousey));
	if ((*data->mousex) > (SIZE * 10 / 2) + deadangle)
	{
		data->player.righting_yaw = (limitor(*data->mousex, SIZE * 10) - (SIZE * 10 / 2)) / data->player.sensivity;
		data->player.lefting_yaw = 0;
	}
	else if ((*data->mousex) < (SIZE * 10 / 2) - deadangle)
	{
		data->player.lefting_yaw = ((-1 * (limitor(*data->mousex, - (SIZE * 10)) - (SIZE * 10 / 2)))) / data->player.sensivity;
		data->player.righting_yaw = 0;
	}
	else if ((*data->mousex) >= (SIZE * 10 / 2) - deadangle && (*data->mousex) <= (SIZE * 10 / 2) + deadangle)
	{
		data->player.righting_yaw = 0;
		data->player.lefting_yaw = 0;
	}
	mlx_mouse_move(data->prog->win, (SIZE * 10 / 2), (SIZE * 10 / 2));
}

int	map_init(t_data *data)
{
	char	*moves;
	int i = 0;
	get_mouse_move(data);
	move_player(data);
	t_node *list = (data->nodes);
	while (list[i].type != ENDL) {
		if (list[i].type == WALL)
			write_cubes(0xFF0000, list[i].x * HITBOX, list[i].y * HITBOX, data, HITBOX);
		if (list[i].type == DOOR){
			if (list[i].direction == LAT)
				write_cubes(0x000000, (list[i].x * HITBOX) + list[i].door_loc, list[i].y * HITBOX, data, HITBOX);
			else
				write_cubes(0x000000, (list[i].x * HITBOX), (list[i].y * HITBOX) + list[i].door_loc, data, HITBOX);
			if (!list[i].running_door){
				toggle_door(&list[i], data);
			}
			if (list[i].direction == LAT)
				write_cubes(0x0FFF00, (list[i].x * HITBOX) + list[i].door_loc, list[i].y * HITBOX, data, HITBOX);
			else
				write_cubes(0x0FFF00, (list[i].x * HITBOX), (list[i].y * HITBOX) + list[i].door_loc, data, HITBOX);
		}
		i++;
	}
	moves = get_moves(ft_itoa(data->moves++));
	// mlx_string_put(data->prog->mlx, data->prog->win, 15, 15, 0xFFFFFF, moves);
	draw_oriented_player(0x000000, data->player.oldx, data->player.oldy, data, PLAYER_SIZE, data->player.oldyaw);
	draw_oriented_player(0xFFFFFF, data->player.x, data->player.y, data, PLAYER_SIZE, data->player.yaw);
	// dessiner_des_carres_pour_tester(0xFFFFFF, data->playerx, data->playery, data, PLAYER_SIZE);
    // mlx_pixel_put(data->prog->mlx, data->prog->win, data->playerx, data->playery, 0xFFFFFF);
	free(moves);
	return 0;
}
