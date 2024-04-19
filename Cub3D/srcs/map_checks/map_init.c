/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:48:38 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/19 08:31:26 by jtollena         ###   ########.fr       */
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
			if (list[i].type == NULLT)
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

t_node	*read_map(int fd, int fc, char *reader, t_node *list)
{
	int		readable;
	int		i;
	int		j;
	int		y;

	readable = 1;
	i = -1;
	j = 0;
	y = 0;
	readable = read(fd, reader, fc);
	if (readable == -1)
		error_inputfile((void *)reader, (void *)list);
	fc = close(fd);
	while (reader[++i])
	{
		if (reader[i] != '\n')
			list[j++] = create_node(reader[i], fc++, y);
		else
		{
			y++;
			fc = 0;
		}
	}
	list[j] = create_node(1, 0, 0);
	if (check_surrounded_points(list) == 0)
		exit_error("SURROUNDED", NULL, list, NULL);
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
