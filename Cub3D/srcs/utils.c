/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:53:57 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/24 12:48:03 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	exit_win(char *msg, t_data *data, char *prefix)
{
	ft_printf("%s\n%s\nNumber of moves: %d\n", prefix, msg, data->moves + 1);
}

int	absolute(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}
