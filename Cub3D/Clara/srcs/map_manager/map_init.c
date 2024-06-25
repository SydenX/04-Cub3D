/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:48:38 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/24 18:41:19 by caymard          ###   ########.fr       */
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

int	get_tex_buffer_img(t_data *data, t_img *img, t_type type) //clara
{
	int	*pixels;
	int	i;
	int	j;

	pixels = malloc(sizeof(int) *((img->width * img->height) + 1));
	if (!pixels)
		return (1);
	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			pixels[i * img->width + j] = img->addr[i * img->width + j];
			j++;
		}
		i++;
	}
	data->buffer[type] = pixels;
	return (0);
}

int	get_img(t_data *data, char *path, int type)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(data->mlx, path, &img.width, &img.height);
	if (!img.img)
		return (1);
	img.addr = mlx_get_data_addr(img.img,
			&img.bits_pixel, &img.length, &img.endian);
	if (!img.addr)
		return (mlx_destroy_image(data->mlx, img.img));
	if (get_tex_buffer_img(data, &img, type))
		return (mlx_destroy_image(data->mlx, img.img));
	mlx_destroy_image(data->mlx, img.img);
	return (0);
}

int	check_texture_file(char *path, char *reader, t_data *data, int type)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		if (errno == 2)
			error_filedonotexist(path, (void *)reader, data);
		else
			error_fileerror(path, (void *)reader, data);
		return (1);
	}
	close(fd);
	get_img(data, path, type);
	return (0);
}

int read_texture(char *reader, t_node *list, t_data *data, int i)
{
	int		j;
	char	*path;
	int		type;

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
		if (check_texture_file(path, reader, data, type)) //c
			return (0);
		free(path);
	}
	return (1);
}

int read_rgb(char *reader, t_node *list, t_data *data, int i)
{
	int	digit;
	int	isf;
	int	count;

	count = 0;
	if (reader[i++] == 'F')
		isf = 1;
	else
		isf = 0;
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
					data->f_rgb.r = digit;
				else if (count == 1)
					data->f_rgb.g = digit;
				else if (count == 2)
					data->f_rgb.b = digit;
			}
			else
			{
				if (count == 0)
					data->c_rgb.r = digit;
				else if (count == 1)
					data->c_rgb.g = digit;
				else if (count == 2)
					data->c_rgb.b = digit;
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
	int	numberoftextures;
	int	fc;

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
		{
			if (reader[i++] == 0)
				exit_error(ERROR_NOTFORMATTED, data, (void *)list, (void *)reader);
		}
		if (numberoftextures == 4 && fc == 2)
			break ;
	}
	// printf("%d %d %d\n", data->f_rgb.r, data->f_rgb.g, data->f_rgb.b);
	// printf("%d %d %d\n", data->c_rgb.r, data->c_rgb.g, data->c_rgb.b);
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
	// close(fd); //deja close dans file_chars
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
