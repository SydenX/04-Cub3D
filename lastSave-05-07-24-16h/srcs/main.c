/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caymard <caymard@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2024/07/04 15:35:01 by caymard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		exit_error("You must put a map file path (.cub) as argument.", NULL, NULL, NULL);
	if (data_init(&data, av))
		return (1);
	debugfps(&data);
	init_hooks(&data);
	// visual(&data);
	// mlx_events(&data);
	system("leaks cub3d");
	return (0);
}
