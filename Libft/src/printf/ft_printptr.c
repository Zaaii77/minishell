/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:37:43 by acaes             #+#    #+#             */
/*   Updated: 2025/01/13 14:37:43 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ptf.h"

int	ft_printptr(void *ptr)
{
	int	i;

	if (!ptr)
		return (ft_printstr(NULL_PTR));
	i = 0;
	i += ft_printstr("0x");
	if (i < 0)
		return (-1);
	return (i + ft_printhexlow((unsigned long)ptr));
}
