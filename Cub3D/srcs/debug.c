/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:53:03 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/25 08:57:07 by jtollena         ###   ########.fr       */
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
		usleep(250000);
		int newframe = data->frame;
		data->fps = (newframe - oldframe)*4;
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
