/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_bits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:20:54 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/02 11:23:27 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	ft_reverse_bits(unsigned char octet)
{
	int				idx;
	unsigned char	bit;

	idx = 8;
	while (idx--)
	{
		bit = ((bit * 2) + (octet % 2));
		octet /= 2;
	}
	return (bit);
}