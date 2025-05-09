/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexlow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:39:33 by acaes             #+#    #+#             */
/*   Updated: 2025/01/13 14:39:33 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ptf.h"

int	ft_printhexlow(unsigned long n)
{
	int		i;

	if (n == 0)
		return (ft_securchar('0'));
	i = 0;
	if (n >= 16)
	{
		i += ft_printhexlow(n / 16);
		if (i < 0)
			return (-1);
	}
	if (ft_securchar("0123456789abcdef"[n % 16]) < 0)
		return (-1);
	i++;
	return (i);
}
