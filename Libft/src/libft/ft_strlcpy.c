/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:47:36 by acaes             #+#    #+#             */
/*   Updated: 2024/12/03 17:20:40 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	len;

	len = ft_strlen(src);
	if (n > 0)
	{
		if ((len + 1) < n)
			ft_memcpy(dst, src, len + 1);
		else
		{
			ft_memcpy(dst, src, n - 1);
			dst[n - 1] = '\0';
		}
	}
	return (len);
}
