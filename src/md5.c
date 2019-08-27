/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/08/27 14:21:23 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/md5.h"

static void md5_output(t_input *input)
{
    if (input->read_from == FILE_STRING) output_before_checksum(input, "MD5 ");
    int i = 16;
    while(i--)
    {
        ft_printf("%.2x", (uint8_t)H[0]);
        H[0] >>= 8;
        if (i == 4) H[0] = H[3];
        else if (i == 8) H[0] = H[2];
        else if (i == 12) H[0] = H[1];
    }
    if (input->read_from == FILE_STRING) output_after_checksum(input);
    ft_printf("\n");
}

static void fill_working_variables(char c)
{
	if (c == '<')
	{
		HH[0] = H[0];
        HH[1] = H[1];
        HH[2] = H[2];
        HH[3] = H[3];
	}
	else if (c == '>')
	{
		H[0] += HH[0];
        H[1] += HH[1];
        H[2] += HH[2];
        H[3] += HH[3];
	}
}

static void init_magic_num()
{
    H[0] = 0x67452301;
    H[1] = 0xefcdab89;
    H[2] = 0x98badcfe;
    H[3] = 0x10325476;
}
    
/*
 * step 3
 */
static void calculation_procedure(void *message, int times)
{
    int offset = 0;
    while ( times-- )
    {
        uint32_t *X = (uint32_t *)(message) + offset;
        fill_working_variables('<');
        for (int j = 0; j < 64; ++j)
        {
            if (j < 16)
                HH[0] += F(HH[1], HH[2], HH[3]);
            else if (j < 32)
                HH[0] += G(HH[1], HH[2], HH[3]);
            else if (j < 48)
                HH[0] += H(HH[1], HH[2], HH[3]);
            else
                HH[0] += I(HH[1], HH[2], HH[3]);
            uint32_t tmp = HH[0] + T[j] + X[x[j]];
            HH[0] = HH[3];
            HH[3] = HH[2];
            HH[2] = HH[1];
            HH[1] = HH[1] + ROTATE_LEFT(tmp, s[j]);
        }
        fill_working_variables('>');
        offset += 16;
    }
}

/*
 * entry piont
 */
enum mode md5(t_input *input, char *func_name)
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
            append_lenght(input->message, g_max_message_len, input->total_size * BIT_NUM, LEN_SIZE);
            calculation_procedure(input->message, 2);
            md5_output(input);
            return hash_mode = FINISH;
        }
        append_padding(input->message, input->message_size, a);
        append_lenght(input->message, a, input->total_size * BIT_NUM, LEN_SIZE);
        calculation_procedure(input->message, 1);
        md5_output(input);
        return hash_mode = FINISH;
    }
    else
    {
        calculation_procedure(input->message, 1);
        return hash_mode = CONTINUE;
    }
}