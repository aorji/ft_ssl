/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 16:07:51 by aorji             #+#    #+#             */
/*   Updated: 2019/08/21 20:14:04 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha384_512.h"

static void sha512_output(t_input *input)
{
    if (input->read_from == FILE_STRING) output_before_checksum(input, "SHA512 ");
    int i = 64;
	H[0] = lit_to_bigendian64(H[0]);
    while(i--)
    {
        ft_printf("%.2x", (uint8_t)H[0]);
        H[0] >>= 8;
        if (i == 8) H[0] = lit_to_bigendian64(H[7]);
        else if (i == 16) H[0] = lit_to_bigendian64(H[6]);
        else if (i == 24) H[0] = lit_to_bigendian64(H[5]);
        else if (i == 32) H[0] = lit_to_bigendian64(H[4]);
        else if (i == 40) H[0] = lit_to_bigendian64(H[3]);
        else if (i == 48) H[0] = lit_to_bigendian64(H[2]);
        else if (i == 56) H[0] = lit_to_bigendian64(H[1]);
    }
    if (input->read_from == FILE_STRING) output_after_checksum(input);
    ft_printf("\n");
}

static void init_magic_num()
{
	H[0] = 0x6a09e667f3bcc908;
	H[1] = 0xbb67ae8584caa73b;
	H[2] = 0x3c6ef372fe94f82b;
	H[3] = 0xa54ff53a5f1d36f1;
	H[4] = 0x510e527fade682d1;
	H[5] = 0x9b05688c2b3e6c1f;
	H[6] = 0x1f83d9abfb41bd6b;
	H[7] = 0x5be0cd19137e2179;
}

/*
 * entry piont
 */
enum mode sha512(t_input *input)
{
	static enum mode hash_mode = START;
    (hash_mode == START) ? init_magic_num() : 0;
    if (input->message_size < n)
    {
        if (input->message_size >= a)
        {
            append_padding(input->message, input->message_size, n);
            append_lenght_bigend(input->message, g_max_message_len, input->total_size * BIT_NUM, LEN_SIZE);
            calculation_procedure64(input->message, 2, H);
            sha512_output(input);
            return hash_mode = FINISH;
        }
        append_padding(input->message, input->message_size, a);
        append_lenght_bigend(input->message, a, input->total_size * BIT_NUM, LEN_SIZE);
		calculation_procedure64(input->message, 1, H);
        sha512_output(input);
        return hash_mode = FINISH;
    }
    else
    {
        calculation_procedure64(input->message, 1, H);
        return hash_mode = CONTINUE;
    }
}