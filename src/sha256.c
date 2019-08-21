/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:49:01 by aorji             #+#    #+#             */
/*   Updated: 2019/08/21 20:14:30 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha224_256.h"

static void sha256_output(t_input *input)
{
    if (input->read_from == FILE_STRING) output_before_checksum(input, "SHA256 ");
    int i = 32;
	H[0] = lit_to_bigendian(H[0]);
    while(i--)
    {
        ft_printf("%.2x", (uint8_t)H[0]);
        H[0] >>= 8;
        if (i == 4) H[0] = lit_to_bigendian(H[7]);
        else if (i == 8) H[0] = lit_to_bigendian(H[6]);
        else if (i == 12) H[0] = lit_to_bigendian(H[5]);
        else if (i == 16) H[0] = lit_to_bigendian(H[4]);
        else if (i == 20) H[0] = lit_to_bigendian(H[3]);
        else if (i == 24) H[0] = lit_to_bigendian(H[2]);
        else if (i == 28) H[0] = lit_to_bigendian(H[1]);
    }
    if (input->read_from == FILE_STRING) output_after_checksum(input);
    ft_printf("\n");
}

static void init_magic_num()
{
	H[0] = 0x6a09e667;
	H[1] = 0xbb67ae85;
	H[2] = 0x3c6ef372;
	H[3] = 0xa54ff53a;
	H[4] = 0x510e527f;
	H[5] = 0x9b05688c;
	H[6] = 0x1f83d9ab;
	H[7] = 0x5be0cd19;
}

/*
 * entry piont
 */
enum mode sha256(t_input *input)
{
	static enum mode hash_mode = START;
    (hash_mode == START) ? init_magic_num() : 0;
    if (input->message_size < n)
    {
        if (input->message_size >= a)
        {
            append_padding(input->message, input->message_size, g_max_message_len);
            append_lenght_bigend(input->message, g_max_message_len, input->total_size * BIT_NUM, LEN_SIZE);
            calculation_procedure32(input->message, 2, H);
            sha256_output(input);
            return hash_mode = FINISH;
        }
        append_padding(input->message, input->message_size, a);
        append_lenght_bigend(input->message, a, input->total_size * BIT_NUM, LEN_SIZE);
        calculation_procedure32(input->message, 1, H);
        sha256_output(input);
        return hash_mode = FINISH;
    }
    else
    {
        calculation_procedure32(input->message, 1, H);
        return hash_mode = CONTINUE;
    }
}