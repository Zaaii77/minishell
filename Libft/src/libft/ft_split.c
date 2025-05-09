/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:00:16 by acaes             #+#    #+#             */
/*   Updated: 2025/04/11 19:30:51 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	word_count(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_copy(const char *s, char c)
{
	char	*word;
	int		i;
	int		l;	

	i = 0;
	l = 0;
	while (s[l] && s[l] != c)
		l++;
	word = (char *)malloc(sizeof(char) * (l + 1));
	if (!word)
		return (NULL);
	while (i < l)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*free_split(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			tab[j] = ft_copy(s, c);
			if (!tab[j])
				return (free_split(tab, j));
			j++;
		}
		while (*s != c && *s)
			s++;
	}
	tab[j] = (NULL);
	return (tab);
}
