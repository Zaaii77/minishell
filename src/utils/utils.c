/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:53:33 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/11 18:39:44 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char *s)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
	return (0);
}

/* Vérifie si un chemin est un répertoire */
int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

t_cmd	*create_new_command(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
	{
		ft_putstr_fd("minishell: memory allocation error\n", STDERR_FILENO);
		return (NULL);
	}
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->next = NULL;
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->heredoc_file = NULL;
	return (cmd);
}

char	**ft_tabjoin(char **tab, char *new_elem)
{
	int		len;
	int		i;
	char	**new_tab;

	len = 0;
	i = 0;
	if (tab)
		while (tab[len])
			len++;
	new_tab = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_tab)
		return (free_tab(tab), free(new_elem), NULL);
	while (i < len)
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[len] = ft_strdup(new_elem);
	if (!new_tab[len])
		return (free(new_tab), free_tab(tab), NULL);
	free(new_elem);
	new_tab[len + 1] = NULL;
	return (free(tab), new_tab);
}
