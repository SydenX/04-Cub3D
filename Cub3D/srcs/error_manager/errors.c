/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:10:07 by jetol             #+#    #+#             */
/*   Updated: 2024/04/17 17:54:12 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	exit_error(char *error, t_prog *prog, void *toFree, void *toFree2)
{
	if (toFree)
		free(toFree);
	if (toFree2)
		free(toFree2);
	if (prog != NULL)
	{
		if (prog->mlx != NULL && prog->win != NULL)
		{
			mlx_clear_window(prog->mlx, prog->win);
			mlx_destroy_window(prog->mlx, prog->win);
		}
	}
	ft_printf("Error\n%s\n", error);
	exit(0);
}

void	error_inputfile(void *toFree, void *toFree2)
{
	exit_error("Unable to read the input file.", NULL, toFree, toFree2);
}

void	error_notformatted(void *toFree, void *toFree2)
{
	exit_error("File is not correctly formatted.", NULL, toFree, toFree2);
}

void	error_notcorrectinterest(void *toFree, void *toFree2)
{
	exit_error("Map doesn't contains the interest points needed.",
		NULL, toFree, toFree2);
}

void	error_nopathfound(void *toFree, void *toFree2)
{
	exit_error("Map collectibles or exit not reachable.",
		NULL, toFree, toFree2);
}