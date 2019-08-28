/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:00:02 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 16:55:09 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha224_256.h"

static void	sha224_output(t_input *input)
{
	int	i;
	int j;

	i = 28;
	j = 0;
	if (input->read_from == FILE_STRING)
		output_before_checksum(input, "SHA224 ");
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
	g_h[0] = 0xc1059ed8;
	g_h[1] = 0x367cd507;
	g_h[2] = 0x3070dd17;
	g_h[3] = 0xf70e5939;
	g_h[4] = 0xffc00b31;
	g_h[5] = 0x68581511;
	g_h[6] = 0x64f98fa7;
	g_h[7] = 0xbefa4fa4;
}

/*
** entry piont
*/

enum e_mode	sha224(t_input *input, char *func_name)
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
		sha224_output(input);
		return (hash_mode = FINISH);
	}
	else
		return (hash_mode = CONTINUE);
}
