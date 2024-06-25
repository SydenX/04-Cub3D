/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:53:57 by jtollena          #+#    #+#             */
/*   Updated: 2024/06/18 14:39:23 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		limitor(int	tolimit, int limit)
{
	if (limit >= 0)
	{
		if (tolimit > limit)
			return limit;
		else
			return tolimit;
	}
	if (tolimit < limit)
		return limit;
	else
		return tolimit;
}

int		ulimitor(int	tolimit, int limit)
{
	if (limit >= 0)
	{
		if (tolimit < limit)
			return limit;
		else
			return tolimit;
	}
	if (tolimit > limit)
		return limit;
	else
		return tolimit;
}