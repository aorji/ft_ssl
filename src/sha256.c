/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:49:01 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 16:58:05 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha224_256.h"

static void	sha256_output(t_input *input)
{
	int	i;
	int	j;

	i = 32;
	j = 0;
	if (input->read_from == FILE_STRING)
		output_before_checksum(input, "SHA256 ");
	g_h[0] = lit_to_bigendian(g_h[0]);
	while (i--)
	{
		ft_printf("%.2x", (uint8_t)g_h[0]);
		g_h[0] >>= 8;
		if (i % 4 == 0)
			g_h[0] = lit_to_bigendian(g_h[++j]);
	}
	if (input->read_from == FILE_STRING)
		output_after_checksum(input);
	ft_printf("\n");
}

static void	init_magic_num(void)
{
	g_h[0] = 0x6a09e667;
	g_h[1] = 0xbb67ae85;
	g_h[2] = 0x3c6ef372;
	g_h[3] = 0xa54ff53a;
	g_h[4] = 0x510e527f;
	g_h[5] = 0x9b05688c;
	g_h[6] = 0x1f83d9ab;
	g_h[7] = 0x5be0cd19;
}

/*
** entry piont
*/

enum e_mode	sha256(t_input *input, char *func_name)
{
	static enum e_mode	hash_mode = START;
	int					block_num;

	if (func_name && input->error)
		write(2, __func__, ft_strlen(__func__));
	if (func_name)
		return (ft_strcmp(__func__, func_name));
	(hash_mode == START) ? init_magic_num() : 0;
	block_num = add_padding_bigend(input, g_n, g_a, LEN_SIZE);
	calculation_procedure_32(input->message, block_num, g_h);
	if (input->message_size < g_n)
	{
		sha256_output(input);
		return (hash_mode = FINISH);
	}
	else
		return (hash_mode = CONTINUE);
}
