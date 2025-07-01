/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:58:49 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/01 16:19:06 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "My_libft/headers/ft_printf.h"
// #include "libft.h"
#include "so_long.h"
#include <stdarg.h>
#include <stdlib.h>


char	*ft_sprintf(const char *format, ...)
{
	va_list	args;
	int		i = 0, j = 0;
	char	*res = malloc(1024);
	char	*tmp;

	if (!res)
		return (NULL);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == 'i')
		{
			tmp = ft_itoa(va_arg(args, int));
			int k = 0;
			while (tmp[k])
				res[j++] = tmp[k++];
			free(tmp);
			i += 2;
		}
		else
			res[j++] = format[i++];
	}
	res[j] = '\0';
	va_end(args);
	return (res);
}
