/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_input_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:56:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/02 02:49:17 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	correct_format(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_input_valid(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		write(1, "wrong number of arguments\n", 27);
		return (0);
	}
	if (!correct_format(argc, argv))
	{
		write(1, "poorly formatted input\n", 24);
		return (0);
	}
	return (1);
}
