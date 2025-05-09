/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:48:36 by acaes             #+#    #+#             */
/*   Updated: 2024/12/03 17:21:21 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t l)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (find[0] == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] && i < l)
	{
		j = 0;
		while ((str[i + j] == find[j]) && ((i + j) < l))
		{
			if (find[j + 1] == '\0')
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
