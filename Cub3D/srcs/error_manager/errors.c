/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:10:07 by jetol             #+#    #+#             */
/*   Updated: 2024/04/19 14:04:07 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	exit_error(char *error, t_data *data, void *toFree, void *toFree2)
{
	if (data != NULL)
	{
		if (data->prog != NULL)
		{
			if (data->prog->mlx != NULL && data->prog->win != NULL)
			{
				mlx_clear_window(data->prog->mlx, data->prog->win);
				mlx_destroy_window(data->prog->mlx, data->prog->win);
			}
		}
		if (data->txt_path_north)
			free(data->txt_path_north);
		if (data->txt_path_east)
			free(data->txt_path_east);
		if (data->txt_path_south)
			free(data->txt_path_south);
		if (data->txt_path_west)
			free(data->txt_path_west);
	}
	if (toFree)
		free(toFree);
	if (toFree2)
		free(toFree2);
	ft_printf("Error\n%s\n", error);
	system("leaks cub3d");
	exit(0);
}

void	error_inputfile(void *toFree, void *toFree2, t_data *data)
{
	exit_error("Unable to read the input file.", data, toFree, toFree2);
}

void	error_notformatted(void *toFree, void *toFree2, t_data *data)
{
	exit_error("File is not correctly formatted.", data, toFree, toFree2);
}

void	error_notcorrectinterest(void *toFree, void *toFree2, t_data *data)
{
	exit_error("Map doesn't contains the interest points needed.",
		data, toFree, toFree2);
}

void	error_nopathfound(void *toFree, void *toFree2, t_data *data)
{
	exit_error("Map collectibles or exit not reachable.",
		data, toFree, toFree2);
}

void	error_notsurrounded(void *toFree, void *toFree2, t_data *data)
{
	exit_error("Map must be surrounded by walls.",
		data, toFree, toFree2);
}

void	error_allocation(void *toFree, void *toFree2, t_data *data)
{
	exit_error("Error during allocation.",
		data, toFree, toFree2);
}