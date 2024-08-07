/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:48:38 by jtollena          #+#    #+#             */
/*   Updated: 2024/07/05 10:59:52 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


void my_pixel_put(int x, int y, t_data *data, int color)
{
	int offset;

	offset = (y * data->img.size_line) + ((data->img.bpp / 8) * x);
	*(unsigned int *)(data->img.img_pixels + offset) = color;
}

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
			exit_error(ERROR_NOTFORMATTED, data, (void *)list, (void *)reader);
		i += 2;
		while ((reader[i] == ' ' || (reader[i] >= 9 && reader[i] < 13)) && reader[i] != '\n')
			i++;
		j = i;
		while (reader[i] != '\n' && reader[i] != 0)
			i++;
		if (reader[i] == 0)
			exit_error(ERROR_NOTFORMATTED, data, (void *)list, (void *)reader);
		path = ft_substr(reader, j, i - j);
		if (!path)
			exit_error(ERROR_ALLOCATION, data, (void *)list, (void *)reader);
		if (ft_strlen(path) == 0)
			exit_error(ERROR_NOTFORMATTED, data, path, (void *)reader);
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
			exit_error(ERROR_NOTFORMATTED, data, (void *)list, (void *)reader);
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
			exit_error(ERROR_NOTFORMATTED, data, (void *)list, (void *)reader);
		while (reader[i] != '\n')
			if (reader[i++] == 0)
				exit_error(ERROR_NOTFORMATTED, data, (void *)list, (void *)reader);
		if (numberoftextures == 4 && fc == 2)
			break ;
	}
	printf("%d %d %d\n", data->f.r, data->f.g, data->f.b);
	printf("%d %d %d\n", data->c.r, data->c.g, data->c.b);
	while (reader[i++] == '\n')
	{
	}
	if (reader[i] == 0)
		exit_error(ERROR_NOTFORMATTED, data, (void *)list, (void *)reader);
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
		exit_error(ERROR_INPUTFILE, data, (void *)reader, (void *)list);
	close(fd);
	i = check_infos(reader, i, list, data);
	x = 0;
	while (reader[++i])
	{
		if (reader[i] == 9)
			exit_error(ERROR_NOTFORMATTED, data, (void *)list, (void *)reader);
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
		exit_error(ERROR_NOTSURROUNDED, data, (void *)(list), (void *)reader);
	if (check_surrounded_doors(list) == 0)
		exit_error(ERROR_DOORNOTPARSED, data, (void *)(list), (void *)reader);
	return (free(reader), check_nodes_type(list, j));
	return NULL;
}

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
			my_pixel_put(x + startX, y + startY, data, color);
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
		my_pixel_put(x0, y0, data, color);
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

float nor_angle(float angle) // normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

double xt = 0;
double yt = 0;
void	vertical_dist(t_data *data, float normdegree, double normpx, int x)
{
	double offsetx = 0;
	double offsety = 0;
	double newx = 0;
	double newy = 0;
	int c = 0;
	if ((normdegree >= 0 && normdegree < 90) || (normdegree > 270 && normdegree < 360)){ //EAST
		offsetx = HITBOX - normpx;
		offsety = (offsetx) * (tanf((normdegree) * M_PI / 180));
		newx = data->player.x + offsetx;
		newy = data->player.y + offsety;
		t_node *node = get_node_at(data->nodes, (newx / HITBOX), (newy / HITBOX));
		if (node != NULL)
			if (node->type == WALL)
				c = data->xlen;
	} else if ((normdegree > 90 && normdegree < 270)){ //WEST
		offsetx = normpx;
		offsety = (offsetx) * (tanf((normdegree) * M_PI / 180));
		newx = data->player.x - offsetx;
		newy = data->player.y - offsety;
		t_node *node = get_node_at(data->nodes, (newx / HITBOX) - 1, (newy / HITBOX));
		if (node != NULL)
			if (node->type == WALL)
				c = data->xlen;
	}

	double nnewx = newx;
	double nnewy = newy;
	while(c++ < data->xlen){
		if ((normdegree > 90 && normdegree < 270)){ //WEST
			double noffsety = (HITBOX) * (tanf((normdegree) * M_PI / 180));
			nnewx -= HITBOX;
			nnewy -= noffsety;
			t_node *node = get_node_at(data->nodes, (nnewx / HITBOX) - 1, (nnewy / HITBOX));
			if (node != NULL)
				if (node->type == WALL)
					c = data->xlen;
		} else if ((normdegree >= 0 && normdegree < 90) || (normdegree > 270 && normdegree < 360)){ //EAST
			double noffsety = (HITBOX) * (tanf((normdegree) * M_PI / 180));
			nnewx += HITBOX;
			nnewy += noffsety;
			t_node *node = get_node_at(data->nodes, (nnewx / HITBOX), (nnewy / HITBOX));
			if (node != NULL)
				if (node->type == WALL)
					c = data->xlen;
		}
	}
	// if (nnewx < WIDTH && nnewy < HEIGHT && nnewx > 0 && nnewy > 0)
	// 	my_pixel_put(nnewx, nnewy, data, 0x00FF00);
	data->distance[x].v = sqrt(fabs((data->player.x - nnewx) * (data->player.x - nnewx)) + fabs((data->player.y - nnewy) * (data->player.y - nnewy)));
	data->distance[x].vx = nnewx;
	data->distance[x].vy = nnewy;
}

void	horizontal_dist(t_data *data, float normdegree, double normpy, int x)
{
	double offsetx = 0;
	double offsety = 0;
	double newx = 0;
	double newy = 0;
	int c = 0;
	if ((normdegree >= 0 && normdegree < 180)){ //SOUTH
		offsety = HITBOX - normpy;
		offsetx = (offsety) * (tanf((90 - normdegree) * M_PI / 180));
		newx = data->player.x + offsetx;
		newy = data->player.y + offsety;
		t_node *node = get_node_at(data->nodes, (newx / HITBOX), (newy / HITBOX));
		if (node != NULL)
			if (node->type == WALL)
				c = data->ylen;
	} else if((normdegree >= 180 && normdegree < 360)){ //NORD
		offsety = normpy;
		offsetx = (offsety) * (tanf((90 - normdegree) * M_PI / 180));
		newx = data->player.x - offsetx;
		newy = data->player.y - offsety;
		t_node *node = get_node_at(data->nodes, (newx / HITBOX), (newy / HITBOX)-1);
		if (node != NULL)
			if (node->type == WALL)
				c = data->ylen;
	}

	double nnewx = newx;
	double nnewy = newy;
	while(c++ < data->ylen){
		if ((normdegree >= 0 && normdegree < 180)){ //SOUTH
			double noffsetx = (HITBOX) * (tanf((90 - normdegree) * M_PI / 180));
			nnewy += HITBOX;
			nnewx += noffsetx;
			t_node *node = get_node_at(data->nodes, (nnewx / HITBOX), (nnewy / HITBOX));
			if (node != NULL)
				if (node->type == WALL)
					c = data->ylen;
		} else if (normdegree >= 180 && normdegree < 360){ //NORTH
			double noffsetx = (HITBOX) * (tanf((90 - normdegree) * M_PI / 180));
			nnewy -= HITBOX;
			nnewx -= noffsetx;
			t_node *node = get_node_at(data->nodes, (nnewx / HITBOX), (nnewy / HITBOX)-1);
			if (node != NULL)
				if (node->type == WALL)
					c = data->ylen;
		}
	}
	// if (nnewx < WIDTH && nnewy < HEIGHT && nnewx > 0 && nnewy > 0)
	// 	my_pixel_put(nnewx, nnewy, data, 0x00FF00);
	data->distance[x].h = sqrt(fabs((data->player.x - nnewx) * (data->player.x - nnewx)) + fabs((data->player.y - nnewy) * (data->player.y - nnewy)));
	data->distance[x].hx = nnewx;
	data->distance[x].hy = nnewy;
}

int	map_loop(t_data *data)
{
	// mlx_clear_window (data->prog->mlx, data->prog->win);
	int x = -1;
	int i1 = 0;
	float yaw = data->player.yaw;
	float yawrad = yaw * M_PI / 180;
	float degree = (yaw + 90) - FOV / 2;
	float playerx = data->player.x;
	float playery = data->player.y;

	// int y2 = 0;
	// while (++x < WIDTH)
	// {
	// 	if (x % HITBOX == 0){
	// 		y2 = -1;
	// 		while (++y2 < HEIGHT){
	// 			if (y2 % HITBOX == 0)
	// 				if (x < HEIGHT)
	// 					draw_line(data, x, y2, WIDTH, y2, 0xFF0000);
	// 			if (y2 % HITBOX == 0)
	// 				if (y2 < HEIGHT)
	// 					draw_line(data, x, y2, x, HEIGHT-1, 0xFF0000);
	// 		}
	// 	}
	// }
	data->distance[WIDTH].type = NULLT;
	int c = rgb_to_hex(data->c);
	int f = rgb_to_hex(data->f);
	int mpx = data->minimap_x;
	int mpy = data->minimap_y;
	int mpex = data->minimap_endx;
	int mpey = data->minimap_endy;
	// my_pixel_put(playerx, playery, data, 0x0000FF);
		
	double normpx = data->player.x;
	while (normpx >= HITBOX)
		normpx-=HITBOX;
	double normpy = data->player.y;
	while (normpy >= HITBOX)
		normpy-=HITBOX;

	while (x++ < WIDTH)
	{
		data->distance[x].h = -1;
		data->distance[x].v = -1;
		data->distance[x].type = ENDL;
		float normdegree = degree - 90;
		while (normdegree < 0)
			normdegree+=360;
		while (normdegree > 360)
			normdegree-=360;

		vertical_dist(data,normdegree,normpx,x);
		horizontal_dist(data,normdegree,normpy,x);

		degree+=(FOV / WIDTH);

		data->distance[x].d = 10;
		if (data->distance[x].h != -1 && data->distance[x].v != -1)
		{
			if (data->distance[x].v < data->distance[x].h){
					data->distance[x].d = fabs(data->distance[x].v);
			} else {
				// if (data->distance[x].hx < data->xlen * HITBOX && data->distance[x].hy < data->ylen * HITBOX && data->distance[x].hx > 0 && data->distance[x].hy > 0){
					data->distance[x].d = fabs(data->distance[x].h);
					data->distance[x].ttype = 1;
					// my_pixel_put(data->distance[x].hx, data->distance[x].hy, data, 0x00FF00);
				// }
			}
		}
		float distanceToPoint = (data->distance[x].d);

		int color = 0xFFFFFF;
		if (data->distance[x].ttype == 0)
			color = 0x0000FF;

		int y = -1;
		float wall_height = (HITBOX * HEIGHT) / (distanceToPoint);
		int begin = (HEIGHT / 2) - (wall_height / 2);
		int end = (HEIGHT / 2) + (wall_height / 2);
		while(++y < begin)
			if (x < WIDTH && y < HEIGHT)
				if (!((x > mpx && x < mpex) && (y > mpy && y < mpey)))
					my_pixel_put(x, y, data, c);
		y = begin - 1;
		while (++y < end)
			if (x < WIDTH - 1 && y < HEIGHT - 1 && x > 0 && y > 0)
				if (!((x > mpx && x < mpex) && (y > mpy && y < mpey)))
					my_pixel_put(x, y, data, color);
		y--;
		while(++y < HEIGHT)
			if (x < WIDTH && y < HEIGHT )
				if (!((x > mpx && x < mpex) && (y > mpy && y < mpey)))
					my_pixel_put(x, y, data, f);
	}
	int i = 0;
	if (!data->in_menu)
	{
		get_mouse_move(data);
		move_player(data);
		t_node *list = (data->nodes);
		while (list[i].type != ENDL) {
			if (list[i].type == DOOR){
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

		if (data->player.oldx != data->player.x || data->player.oldy != data->player.y || data->player.oldyaw != data->player.yaw)
		{
			t_node *node = get_node_at(data->nodes, data->player.x / HITBOX, data->player.y / HITBOX);
			if (node != NULL)
				check_nodes_arround_map(*node, data, 1);
			draw_oriented_player_map(0x33CCFF, (data->minimap_x + MINIMAP_HITBOX / 2) + (int)(data->player.oldx * ((float)MINIMAP_HITBOX / HITBOX)), (data->minimap_y + MINIMAP_HITBOX / 2) + (int)(data->player.oldy * ((float)MINIMAP_HITBOX / HITBOX)), data, PLAYER_SIZE, data->player.oldyaw);
			draw_oriented_player_map(0xFFFFFF, (data->minimap_x + MINIMAP_HITBOX / 2) + (int)(data->player.x * ((float)MINIMAP_HITBOX / HITBOX)), (data->minimap_y + MINIMAP_HITBOX / 2) + (int)(data->player.y * ((float)MINIMAP_HITBOX / HITBOX)), data, PLAYER_SIZE, data->player.yaw);
		}
	}
	mlx_put_image_to_window(data->prog->mlx, data->prog->win, data->img.img_ptr, 0, 0);
	debug_affichage_frames(data);
	return 0;
}

int	map_init(t_data *data)
{
	data->img.img_ptr = mlx_new_image(data->prog->mlx, WIDTH, HEIGHT);
 	data->img.img_pixels = mlx_get_data_addr(data->img.img_ptr,
                                    &data->img.bpp,
                                    &data->img.size_line,
                                    &data->img.endian);
	char	*moves;
	int i = 0;
	if (!data->in_menu)
	{
		write_cubes_map(0x33CCFF, (MINIMAP_HITBOX / 2), (MINIMAP_HITBOX / 2), data, MINIMAP_HITBOX * (get_map_width(data) + 1), MINIMAP_HITBOX * (get_map_height(data) + 1));
		data->minimap_x = (MINIMAP_HITBOX / 2);
		data->minimap_y = (MINIMAP_HITBOX / 2);
		data->minimap_endx = data->minimap_x + MINIMAP_HITBOX * (get_map_width(data) + 1);
		data->minimap_endy = data->minimap_y + MINIMAP_HITBOX * (get_map_height(data) + 1);

		t_node *list = (data->nodes);
		while (list[i].type != ENDL) {
			if (list[i].type == WALL)
				write_cubes_map(0xFF0000, ((list[i].x + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2), ((list[i].y + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2), data, MINIMAP_HITBOX, MINIMAP_HITBOX);
			if (list[i].type == DOOR){
				if (list[i].direction == LAT)
					write_cubes_map(0x0FFF00, (((list[i].x + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2)) + list[i].door_loc, ((list[i].y + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2), data, MINIMAP_HITBOX, MINIMAP_HITBOX);
				else
					write_cubes_map(0x0FFF00, (((list[i].x + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2)), (((list[i].y + 0.5) * MINIMAP_HITBOX) + (MINIMAP_HITBOX / 2)) + list[i].door_loc, data, MINIMAP_HITBOX, MINIMAP_HITBOX);
			}
			i++;
		}
		draw_oriented_player_map(0xFFFFFF, (data->minimap_x + MINIMAP_HITBOX / 2) + (int)(data->player.x * ((float)MINIMAP_HITBOX / HITBOX)), (data->minimap_y + MINIMAP_HITBOX / 2) + (int)(data->player.y * ((float)MINIMAP_HITBOX / HITBOX)), data, PLAYER_SIZE, data->player.yaw);
	}
	mlx_put_image_to_window(data->prog->mlx, data->prog->win, data->img.img_ptr, 0, 0);
	return 0;
}
