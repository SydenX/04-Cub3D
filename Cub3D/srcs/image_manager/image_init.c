/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:50:27 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/24 12:48:26 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_img	*get_player_image(t_data *data)
{
	t_img	*cpy;
	int		i;

	i = 0;
	cpy = data->imgs;
	while (cpy->type != NULLT)
	{
		if (cpy->type == SPAWN)
			return (&data->imgs[i]);
		i++;
		cpy++;
	}
	return (data->imgs);
}

t_img	*get_img_at(t_img *list, int x, int y, int isfloor)
{
	t_img	*cpy;
	int		i;

	i = 0;
	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->x == x && cpy->y == y)
		{
			if (cpy->type == FLOOR && isfloor)
				return (&list[i]);
			else if (cpy->type != FLOOR)
				return (&list[i]);
		}
		i++;
		cpy++;
	}
	return (list);
}

void	*get_image(t_prog *prog, t_type type)
{
	int	img_width;
	int	img_height;

	if (type == WALL)
		return (mlx_xpm_file_to_image(prog->mlx,
				"img/MegaTree.xpm", &img_width, &img_height));
	if (type == WALL)
		return (mlx_xpm_file_to_image(prog->mlx,
				"img/Bush.xpm", &img_width, &img_height));
	if (type == SPAWN)
		return (mlx_xpm_file_to_image(prog->mlx,
				"img/Player.xpm", &img_width, &img_height));
	if (type == NULLT)
		return (NULL);
	return (mlx_xpm_file_to_image(prog->mlx,
			"img/Grass.xpm", &img_width, &img_height));
}

t_img	create_image(int x, int y, t_type type, t_prog *prog)
{
	t_img	new;

	new.x = x;
	new.y = y;
	new.type = type;
	new.img = get_image(prog, type);
	return (new);
}

t_img	*load_images(t_img *imgs, t_node *list, t_prog *prog)
{
	t_node	*cpy;
	int		i;

	cpy = list;
	i = 0;
	while (cpy->type != NULLT)
	{
		imgs[i++] = create_image(cpy->x, cpy->y, FLOOR, prog);
		cpy++;
	}
	cpy = list;
	while (cpy->type != NULLT)
	{
		imgs[i++] = create_image(cpy->x, cpy->y, cpy->type, prog);
		cpy++;
	}
	imgs[i] = create_image(0, 0, NULLT, prog);
	return (imgs);
}