/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:36:08 by acaes             #+#    #+#             */
/*   Updated: 2025/01/13 14:36:08 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ptf.h"

int	ft_printunsigned(unsigned int n)
{
	ssize_t	i;

	i = 0;
	if (n > 9)
	{
		i += ft_printunsigned(n / 10);
		if (i < 0)
			return (-1);
	}
	if (ft_securchar("0123456789"[n % 10]) < 0)
		return (-1);
	i++;
	return (i);
}
