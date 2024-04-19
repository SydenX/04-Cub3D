/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:48:38 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/19 11:03:57 by jtollena         ###   ########.fr       */
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
		if (list[i].type != WALL && list[i].type != NULLT)
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
			error_notformatted((void *)list, (void *)reader);
		i += 2;
		while ((reader[i] == ' ' || (reader[i] >= 9 && reader[i] < 13)) && reader[i] != '\n')
			i++;
		j = i;
		while (reader[i] != '\n' && reader[i] != 0)
			i++;
		if (reader[i] == 0)
			error_notformatted((void *)list, (void *)reader);
		path = ft_substr(reader, j, i - j);
		if (!path)
			error_allocation((void *)list, (void *)reader);
		if (ft_strlen(path) == 0)
			error_notformatted((void *)list, (void *)reader);
		printf("%s-\n", path);
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
			error_notformatted((void *)list, (void *)reader);
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
			exit_error("0", NULL, (void *)list, (void *)reader);
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
			error_notformatted((void *)list, (void *)reader);
		while (reader[i] != '\n')
			if (reader[i++] == 0)
				error_notformatted((void *)list, (void *)reader);
		if (numberoftextures == 4 && fc == 2)
			break ;
	}
	printf("%d %d %d\n", data->f.r, data->f.g, data->f.b);
	printf("%d %d %d\n", data->c.r, data->c.g, data->c.b);
	while (reader[i++] == '\n')
	{
	}
	if (reader[i] == 0)
		error_notformatted((void *)list, (void *)reader);
	return (i - 1);
}

t_node	*read_map(int fd, int x, char *reader, t_data *data)
{
	int		readable;
	int		i;
	int		j;
	int		y;
	t_node	*list;

	list = *data->nodes;
	readable = 1;
	i = -1;
	j = 0;
	y = 0;
	readable = read(fd, reader, x);
	if (readable == -1)
		error_inputfile((void *)reader, (void *)list);
	close(fd);
	i = check_infos(reader, i, list, data);
	x = 0;
	while (reader[++i])
	{
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
		error_notsurrounded((void *)(list), (void *)reader);
	return (free(reader), check_nodes_type(list, j));
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

void	map_init(t_data *data)
{
	t_img	*cpy;
	t_img	*loadafter;
	char	*moves;

	cpy = data->imgs;
	mlx_clear_window(data->prog->mlx, data->prog->win);
	while (cpy->type != ENDL)
	{
		if (cpy->type == SPAWN)
			loadafter = cpy;
		else
			mlx_put_image_to_window(data->prog->mlx, data->prog->win,
				cpy->img, cpy->x * SIZE, cpy->y * SIZE);
		cpy++;
	}
	moves = get_moves(ft_itoa(data->moves));
	if (!moves)
		exit_error("Failed malloc allocation", data->prog, data, NULL);
	mlx_put_image_to_window(data->prog->mlx, data->prog->win,
		loadafter->img, loadafter->x * SIZE, loadafter->y * SIZE);
	mlx_string_put(data->prog->mlx, data->prog->win, 15, 15, 0xFFFFFF, moves);
	free(moves);
}
