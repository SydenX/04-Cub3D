/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:48:38 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/11 12:18:53 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	do_map_checks(int fd, char *reader)
{
	close(fd);
	linesize_checks(reader);
	surr_checks(reader);
	return (0);
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
	fc = do_map_checks(fd, reader);
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
	while (cpy->type != NULLT)
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
