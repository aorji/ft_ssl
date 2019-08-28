/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 16:07:51 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 17:08:50 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha384_512.h"

static void	sha512_output(t_input *input)
{
	int i;
	int j;

	i = 64;
	j = 0;
	if (input->read_from == FILE_STRING)
		output_before_checksum(input, "SHA512 ");
	g_h[0] = lit_to_bigendian64(g_h[0]);
	while (i--)
	{
		ft_printf("%.2x", (uint8_t)g_h[0]);
		g_h[0] >>= 8;
		if (i % 8 == 0)
			g_h[0] = lit_to_bigendian64(g_h[++j]);
	}
	if (input->read_from == FILE_STRING)
		output_after_checksum(input);
	ft_printf("\n");
}

static void	init_magic_num(void)
{
	g_h[0] = 0x6a09e667f3bcc908;
	g_h[1] = 0xbb67ae8584caa73b;
	g_h[2] = 0x3c6ef372fe94f82b;
	g_h[3] = 0xa54ff53a5f1d36f1;
	g_h[4] = 0x510e527fade682d1;
	g_h[5] = 0x9b05688c2b3e6c1f;
	g_h[6] = 0x1f83d9abfb41bd6b;
	g_h[7] = 0x5be0cd19137e2179;
}

/*
** entry piont
*/

enum e_mode	sha512(t_input *input, char *func_name)
{
	static enum e_mode	hash_mode = START;
	int					block_num;

	if (func_name && input->error)
		write(2, __func__, ft_strlen(__func__));
	if (func_name)
		return (ft_strcmp(__func__, func_name));
	(hash_mode == START) ? init_magic_num() : 0;
	block_num = add_padding_bigend(input, g_n, g_a, LEN_SIZE);
	calculation_procedure_64(input->message, block_num, g_h);
	if (input->message_size < g_n)
	{
		sha512_output(input);
		return (hash_mode = FINISH);
	}
	else
		return (hash_mode = CONTINUE);
}
