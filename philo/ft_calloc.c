/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:49:31 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/30 22:11:47 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ar_cpy;
	void			*ar;
	size_t			tot_size;

	tot_size = size * nmemb;
	if (!tot_size)
		tot_size = 1;
	if (tot_size > (size_t) INT_MAX)
		return (NULL);
	ar = malloc(tot_size);
	if (!ar)
		return (NULL);
	ar_cpy = ar;
	while (tot_size--)
	{
		*ar_cpy = 0;
		ar_cpy++;
	}
	return (ar);
}
