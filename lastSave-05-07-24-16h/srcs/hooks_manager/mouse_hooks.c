/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:04:36 by jtollena          #+#    #+#             */
/*   Updated: 2024/07/05 11:50:43 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

// Dans le menu, detecter le clic gauche pour interagir avec les bouttons
int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	if (keycode == 1 && data->in_menu)
	{
		if (x > 100 && x < 180 && y > 100 && y < 150)
			data->player.sensivity--;
		else if (x > 200 && x < 280 && y > 100 && y < 150)
			data->player.sensivity = 11;
		else if (x > 300 && x < 380 && y > 100 && y < 150)
			data->player.sensivity++;
	}
	return (0);
}

//Obtenir la position de la souris pour modifier le yaw en fonction de sa position
//Tp de la souris au centre de la fenetre de jeu
void	get_mouse_move(t_data *data)
{
	mlx_mouse_get_pos(data->win, (data->mousex), (data->mousey));

	//GESTION YAW
	if ((*data->mousex) > (WIDTH / 2))
	{
		data->player.righting_yaw = (limitor(*data->mousex, WIDTH)
				- (WIDTH / 2)) / data->player.sensivity;
		data->player.lefting_yaw = 0;
	}
	else if ((*data->mousex) < (WIDTH / 2))
	{
		data->player.lefting_yaw = ((-1 * (limitor(*data->mousex, - (WIDTH))
						- (WIDTH / 2)))) / data->player.sensivity;
		data->player.righting_yaw = 0;
	}
	else if ((*data->mousex) >= (WIDTH / 2)
		&& (*data->mousex) <= (WIDTH / 2))
	{
		data->player.righting_yaw = 0;
		data->player.lefting_yaw = 0;
	}

	//GESTION PITCH
	if ((*data->mousey) > (HEIGHT / 2))
	{
		data->player.downing_pitch = ((limitor(*data->mousey, HEIGHT)
				- (HEIGHT / 2)) / (data->player.sensivity / 10));
		data->player.upping_pitch = 0;
	}
	else if ((*data->mousey) < (HEIGHT / 2))
	{
		data->player.upping_pitch = (((-1 * (limitor(*data->mousey, - (HEIGHT))
						- (HEIGHT / 2)))) / (data->player.sensivity / 10));
		data->player.downing_pitch = 0;
	}
	else if ((*data->mousey) >= (HEIGHT / 2)
		&& (*data->mousey) <= (HEIGHT / 2))
	{
		data->player.downing_pitch = 0;
		data->player.upping_pitch = 0;
	}
	mlx_mouse_move(data->win, (WIDTH / 2), (HEIGHT / 2));
}
