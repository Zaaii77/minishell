/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:46:59 by acaes             #+#    #+#             */
/*   Updated: 2024/12/03 17:19:51 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	l;
	char	*dst;

	if (!s)
	{
		dst = (char *)malloc(sizeof(char));
		if (!dst)
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	l = ft_strlen(s);
	dst = (char *)malloc(sizeof(char) * l + 1);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s, l);
	dst[l] = '\0';
	return (dst);
}
