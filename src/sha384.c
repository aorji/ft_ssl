/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 14:36:10 by aorji             #+#    #+#             */
/*   Updated: 2019/08/27 14:15:29 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha384_512.h"

static void sha384_output(t_input *input)
{
    if (input->read_from == FILE_STRING) output_before_checksum(input, "SHA384 ");
    int i = 48;
	H[0] = lit_to_bigendian64(H[0]);
    while(i--)
    {
        ft_printf("%.2x", (uint8_t)H[0]);
        H[0] >>= 8;
        if (i == 8) H[0] = lit_to_bigendian64(H[5]);
        else if (i == 16) H[0] = lit_to_bigendian64(H[4]);
        else if (i == 24) H[0] = lit_to_bigendian64(H[3]);
        else if (i == 32) H[0] = lit_to_bigendian64(H[2]);
        else if (i == 40) H[0] = lit_to_bigendian64(H[1]);
    }
    if (input->read_from == FILE_STRING) output_after_checksum(input);
    ft_printf("\n");
}

static void init_magic_num()
{
	H[0] = 0xcbbb9d5dc1059ed8;
	H[1] = 0x629a292a367cd507;
	H[2] = 0x9159015a3070dd17;
	H[3] = 0x152fecd8f70e5939;
	H[4] = 0x67332667ffc00b31;
	H[5] = 0x8eb44a8768581511;
	H[6] = 0xdb0c2e0d64f98fa7;
	H[7] = 0x47b5481dbefa4fa4;
}

/*
 * entry piont
 */
enum mode sha384(t_input *input, char *func_name)
{
	if (func_name)
		return (ft_strcmp(__func__, func_name));
	static enum mode hash_mode = START;
    (hash_mode == START) ? init_magic_num() : 0;
    if (input->message_size < n)
    {
        if (input->message_size >= a)
        {
            append_padding(input->message, input->message_size, g_max_message_len);
            append_lenght_bigend(input->message, g_max_message_len, input->total_size * BIT_NUM, LEN_SIZE);
            calculation_procedure64(input->message, 2, H);
            sha384_output(input);
            return hash_mode = FINISH;
        }
        append_padding(input->message, input->message_size, a);
        append_lenght_bigend(input->message, a, input->total_size * BIT_NUM, LEN_SIZE);
		calculation_procedure64(input->message, 1, H);
        sha384_output(input);
        return hash_mode = FINISH;
    }
    else
    {
        calculation_procedure64(input->message, 1, H);
        return hash_mode = CONTINUE;
    }
}