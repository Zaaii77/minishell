/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:45:03 by acaes             #+#    #+#             */
/*   Updated: 2024/12/03 17:13:59 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t nbr, size_t size)
{
	size_t	n;
	void	*str;

	if (size != 0 && (nbr * size) / size != nbr)
		return (NULL);
	n = (nbr * size);
	str = (void *)malloc(sizeof(char) * n);
	if (!str)
		return (NULL);
	ft_bzero(str, n);
	return (str);
}
