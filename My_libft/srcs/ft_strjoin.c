/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:54:12 by hrouchy           #+#    #+#             */
/*   Updated: 2025/05/13 11:03:29 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (dest[i] != '\0')
		i++;
	while (src[e] != '\0')
	{
		dest[i] = src[e];
		e++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str_join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str_join)
		return (NULL);
	str_join[0] = '\0';
	ft_strcat(str_join, s1);
	ft_strcat(str_join, s2);
	return (str_join);
}

// #include <stdio.h>

// int	main(void)
// {
//     char *str1 = "lorem ipsum ";
//     char *str2 = "dolor sit amet";
// 	printf("%s", ft_strjoin(str1,str2));
// }
