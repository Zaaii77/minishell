/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:26:15 by acaes             #+#    #+#             */
/*   Updated: 2024/12/03 17:15:50 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	ft_len(long nbr)
{
	int	l;

	l = 0;
	if (nbr <= 0)
		l++;
	while (nbr != 0)
	{
		nbr /= 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int			len;
	long		nbr;
	char		*result;

	nbr = n;
	len = ft_len(nbr);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len--] = '\0';
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		result[len--] = ((nbr % 10) + 48);
		nbr /= 10;
	}
	return (result);
}
