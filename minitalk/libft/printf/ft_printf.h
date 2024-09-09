/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:07:29 by riporth           #+#    #+#             */
/*   Updated: 2023/12/01 16:07:40 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_printf(const char *str, ...);
int	cases(const char *str, int i, va_list args);
int	printchar(int c);
int	printint(int n, int ct);
int	printuint(unsigned int n, int ct);
int	printhex(unsigned int n, int ct);
int	printhexu(unsigned int n, int ct);
int	printaddr(unsigned long long int n, int ct);
int	printstr(char *chr);
#endif