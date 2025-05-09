/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:50:42 by flash19           #+#    #+#             */
/*   Updated: 2025/04/04 16:04:28 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	is_flag_n(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

/* Vérifie les arguments de la commande echo pour l'option -n */
static int	check_args(char **args, int *start)
{
	int	i;

	i = 1;
	while (args[i] && is_flag_n(args[i]))
		i++;
	*start = i;
	if (i > 1)
		return (0);
	return (1);
}

/* Écrit les arguments de la commande echo avec ou sans retour à la ligne */
static void	write_args(char **args, int start, int newline)
{
	int	i;

	i = start;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
}

/* Fonction principale de la commande echo */
int	ft_echo(int ac, char **av)
{
	int	newline;
	int	start;

	start = 1;
	if (ac < 2)
	{
		ft_printf("\n");
		return (0);
	}
	newline = check_args(av, &start);
	write_args(av, start, newline);
	return (g_exit_status = 0, 0);
}
