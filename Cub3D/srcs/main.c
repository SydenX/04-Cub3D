/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2024/04/19 10:26:21 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	init_list(char **argv, char *reader, int fileChars, t_data *data)
{
	t_node	*list;

	list = malloc((node_size(argv[1]) + 1) * sizeof(t_node));
	if (!list)
	{
		free(reader);
		exit_error("Failed malloc allocation", NULL, NULL, NULL);
	}
	data->nodes = malloc(sizeof(t_node *));
	data->nodes = &list;
	// data->f = malloc(sizeof(t_rgb));
	// data->c = malloc(sizeof(t_rgb));
	list = read_map(get_fd(argv[1], (void *)list, (void *)reader),
			fileChars, reader, data);
}

int	main(int argc, char **argv)
{
	int		filechars;
	char	*reader;
	t_prog	prog;
	t_data	data;

	if (argc != 2)
		exit_error("You must put a map path as argument.", NULL, NULL, NULL);
	filechars = file_chars(argv[1]);
	reader = malloc((filechars + 1) * sizeof(char));
	if (!reader)
		exit_error("Failed malloc allocation", NULL, NULL, NULL);
	reader[filechars] = 0;
	init_list(argv, reader, filechars, &data);
	return (argc);
}
