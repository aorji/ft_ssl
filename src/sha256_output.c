/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:30:56 by aorji             #+#    #+#             */
/*   Updated: 2019/08/16 21:11:40 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha256.h"

static void after_checksum(t_input *input)
{
    if (!get_flag(input, 'p') && !get_flag(input, 'q') && get_flag(input, 'r'))
    {
        if (get_flag(input, 's'))
        {
            ft_printf(" \"%s\"", input->message_name);;
            set_flag(input, 's', 0);   
        }
        else
            ft_printf(" *%s", input->message_name);
    }
}

static void before_checksum(t_input *input)
{
    if (!get_flag(input, 'p') && !get_flag(input, 'q') && !get_flag(input, 'r'))
    {
        if (get_flag(input, 's'))
        {
            ft_printf("SHA256 (\"%s\") = ", input->message_name);;
            set_flag(input, 's', 0);   
        }
        else
            ft_printf("SHA256 (%s) = ", input->message_name);
    }
}

void sha256_output(t_input *input, uint32_t H[])
{
    if (input->read_from == FILE_STRING) before_checksum(input);
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
    if (input->read_from == FILE_STRING) after_checksum(input);
    ft_printf("\n");
}