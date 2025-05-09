/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:38:12 by acaes             #+#    #+#             */
/*   Updated: 2025/01/13 14:38:12 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ptf.h"

ssize_t	ft_printnbr(int n)
{
	ssize_t	i;

	if (n == -2147483648)
		return (ft_printstr("-2147483648"));
	i = 0;
	if (n < 0)
	{
		if (ft_securchar('-') < 0)
			return (-1);
		n = -n;
		i++;
	}
	if (n >= 10)
	{
		i += ft_printnbr(n / 10);
		if (i < 0)
			return (-1);
	}
	if (ft_securchar("0123456789"[n % 10]) < 0)
		return (-1);
	i++;
	return (i);
}
