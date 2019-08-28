/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 18:16:12 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/md5.h"

static void	md5_output(t_input *input)
{
	int	i;
	int	j;

	i = 16;
	j = 0;
	if (input->read_from == FILE_STRING)
		output_before_checksum(input, "MD5 ");
	while (i--)
	{
		ft_printf("%.2x", (uint8_t)g_h[0]);
		g_h[0] >>= 8;
		if (i % 4 == 0)
			g_h[0] = g_h[++j];
	}
	if (input->read_from == FILE_STRING)
		output_after_checksum(input);
	ft_printf("\n");
}

static void	init_magic_num(void)
{
	g_h[0] = 0x67452301;
	g_h[1] = 0xefcdab89;
	g_h[2] = 0x98badcfe;
	g_h[3] = 0x10325476;
}

/*
**	entry point
*/

enum e_mode	md5(t_input *input, char *func_name)
{
	static enum e_mode	hash_mode = START;
	int					block_num;

	if (func_name && input->error)
		write(2, __func__, ft_strlen(__func__));
	if (func_name)
		return (ft_strcmp(__func__, func_name));
	(hash_mode == START) ? init_magic_num() : 0;
	block_num = add_padding(input, g_n, g_a, LEN_SIZE);
	calculation_procedure(input->message, block_num, g_h);
	if (input->message_size < g_n)
	{
		md5_output(input);
		return (hash_mode = FINISH);
	}
	else
		return (hash_mode = CONTINUE);
}
