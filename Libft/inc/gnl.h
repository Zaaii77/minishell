/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:59:52 by acaes             #+#    #+#             */
/*   Updated: 2025/01/13 14:59:52 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <fcntl.h>
# include "libft.h"

# define MAXINT 2147483647

# ifndef FD_MAX
#  define FD_MAX 256
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char		*ft_free(char **ptr);
char		*fill_line(int fd, char *left);
char		*set_line(char *line);
char		*get_next_line(int fd);

#endif
