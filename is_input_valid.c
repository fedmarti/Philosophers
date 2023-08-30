/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_input_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:56:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/30 22:05:36 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	correct_format(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i <= argc)
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
	if (argc != 4 || argc != 5)
	{
		printf("wrong number of arguments\n");
		return (0);
	}
	if (!correct_format(argc, argv))
	{
		printf("poorly formatted input\n");
		return (0);
	}
	return (1);
}
