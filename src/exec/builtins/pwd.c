/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:30:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/04 11:24:13 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/* Affiche le répertoire de travail actuel */
int	ft_pwd(void)
{
	char	path[4096];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_printf("%s\n", path);
		return (0);
	}
	else
	{
		perror("getcwd");
		ft_printf("minishell: pwd: %s\n", strerror(errno));
		return (1);
	}
}
