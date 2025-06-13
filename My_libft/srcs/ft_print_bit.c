/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:18:43 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/02 10:41:05 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_bit(unsigned char octet)
{
	int index;
	unsigned char bit;

	index = 8;
	int mask = 1;
	while (index -- > 0)
	{
		bit = (((octet >> index) & mask) + '0');
		ft_putchar(bit);
	}
}

