/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:10:07 by jetol             #+#    #+#             */
/*   Updated: 2024/06/24 13:11:47 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	clear(t_data *data, void *toFree, void *toFree2)
{
	if (data)
	{
		if (data->mousex)
			free(data->mousex);
		if (data->mousey)
			free(data->mousey);
		data = NULL;
	}
	if (toFree)
	{
		free(toFree);
		toFree = NULL;
	}
	if (toFree2)
	{
		free(toFree2);
		toFree2 = NULL;
	}
}

void	exit_error(char *error, t_data *data, void *toFree, void *toFree2)
{
	clear(data, toFree, toFree2);
	ft_printf("Error\n%s\n", error);
	//system("leaks cub3d");
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
	//system("leaks cub3d");
	exit(0);
}
