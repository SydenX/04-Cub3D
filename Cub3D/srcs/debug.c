/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:53:03 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/26 10:43:05 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	*fps_debug(void *arg)
{
	t_data *data;
	data = (t_data *)arg;
	while (1)
	{
		int oldframe = data->frame;
		usleep(1000000);
		int newframe = data->frame;
		data->fps = (newframe - oldframe);
	}
	return NULL;
}

void	debugfps(t_data *data)
{
	pthread_t	thread;
	pthread_create(&thread, NULL, &fps_debug, data);
}

char	*get_frames(char *moves)
{
	char	*msg;

	if (!moves)
		return (NULL);
	msg = ft_strjoin("Frame: ", moves);
	free(moves);
	return (msg);
}
char	*get_fps(char *moves)
{
	char	*msg;

	if (!moves)
		return (NULL);
	msg = ft_strjoin("FPS: ", moves);
	free(moves);
	return (msg);
}

void	debug_affichage_frames(t_data *data)
{
	char	*moves;
	moves = get_frames(ft_itoa(data->frame));
	mlx_string_put(data->prog->mlx, data->prog->win, 15, 15, 0x000000, moves);
	free(moves);
	data->frame++;
	moves = get_frames(ft_itoa(data->frame));
	mlx_string_put(data->prog->mlx, data->prog->win, 15, 15, 0xFFFFFF, moves);
	free(moves);

	moves = get_fps(ft_itoa(data->fps));
	mlx_string_put(data->prog->mlx, data->prog->win, 15, 30, 0x000000, moves);
	free(moves);
	moves = get_fps(ft_itoa(data->fps));
	mlx_string_put(data->prog->mlx, data->prog->win, 15, 30, 0xFFFFFF, moves);
	free(moves);
}