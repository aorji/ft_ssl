/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 14:36:10 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 17:07:52 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha384_512.h"

static void	sha384_output(t_input *input)
{
	int i;
	int j;

	i = 48;
	j = 0;
	if (input->read_from == FILE_STRING)
		output_before_checksum(input, "SHA384 ");
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
	g_h[0] = 0xcbbb9d5dc1059ed8;
	g_h[1] = 0x629a292a367cd507;
	g_h[2] = 0x9159015a3070dd17;
	g_h[3] = 0x152fecd8f70e5939;
	g_h[4] = 0x67332667ffc00b31;
	g_h[5] = 0x8eb44a8768581511;
	g_h[6] = 0xdb0c2e0d64f98fa7;
	g_h[7] = 0x47b5481dbefa4fa4;
}

/*
** entry piont
*/

enum e_mode	sha384(t_input *input, char *func_name)
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
		sha384_output(input);
		return (hash_mode = FINISH);
	}
	else
		return (hash_mode = CONTINUE);
}
