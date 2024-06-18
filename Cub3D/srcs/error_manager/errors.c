/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:10:07 by jetol             #+#    #+#             */
/*   Updated: 2024/06/18 14:42:12 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	clear(t_data *data, void *toFree, void *toFree2){
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
		// while(data->nodes->type != ENDL)
		// {
		// 	free(data->nodes);
		// 	data->nodes++;
		// }
		// free(data->nodes);
		
		if (data->mousex)
			free(data->mousex);
		if (data->mousey)
			free(data->mousey);
		data = NULL;
		free(data);
	}
	if (toFree)
	{
		toFree = NULL;
		free(toFree);
	}
	if (toFree2)
	{
		toFree2 = NULL;
		free(toFree2);
	}
}

void	exit_error(char *error, t_data *data, void *toFree, void *toFree2)
{
	clear(data, toFree, toFree2);
	ft_printf("Error\n%s\n", error);
	system("leaks cub3d");
	exit(0);
}

void	error_filedonotexist(void *path, void *toFree2, t_data *data)
{
	clear(data, path, toFree2);
	ft_printf("Error\nFile '%s' do not exist.\n", path);
	// system("leaks cub3d");
	exit(0);
}

void	error_fileerror(void *path, void *toFree2, t_data *data)
{
	clear(data, path, toFree2);
	ft_printf("Error\nError while trying to read the file '%s'.\n", path);
	// system("leaks cub3d");
	exit(0);
}

void	error_texturefileincorect(void *path, void *toFree2, t_data *data)
{
	clear(data, path, toFree2);
	ft_printf("Error\nError while trying to read the texture file '%s'.\n", path);
	system("leaks cub3d");
	exit(0);
}