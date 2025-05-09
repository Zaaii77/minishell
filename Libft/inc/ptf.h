/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:00:09 by acaes             #+#    #+#             */
/*   Updated: 2025/01/13 15:00:09 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTF_H
# define PTF_H

# include <stdarg.h>
# include "libft.h"

# ifdef __linux__
#  define NULL_STR "(null)"
#  define NULL_PTR "(nil)"
# else
#  define NULL_STR "(null)"
#  define NULL_PTR "0x0"
# endif

int				ft_printf(const char *format, ...);
int				ft_securchar(char c);
int				ft_printstr(char *s);
int				ft_printptr(void *ptr);
ssize_t			ft_printnbr(int n);
int				ft_printunsigned(unsigned int n);
int				ft_printhexlow(unsigned long n);
int				ft_printhexup(unsigned long n);

#endif
