/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:07:29 by aorji             #+#    #+#             */
/*   Updated: 2019/08/19 14:25:56 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha.h"

void sha224_output(t_input *input, uint32_t H[])
{
    if (input->read_from == FILE_STRING) output_before_checksum(input, "SHA224 ");
    int i = 28;
	H[0] = lit_to_bigendian(H[0]);
    while(i--)
    {
        ft_printf("%.2x", (uint8_t)H[0]);
        H[0] >>= 8;
        if (i == 4) H[0] = lit_to_bigendian(H[6]);
        else if (i == 8) H[0] = lit_to_bigendian(H[5]);
        else if (i == 12) H[0] = lit_to_bigendian(H[4]);
        else if (i == 16) H[0] = lit_to_bigendian(H[3]);
        else if (i == 20) H[0] = lit_to_bigendian(H[2]);
        else if (i == 24) H[0] = lit_to_bigendian(H[1]);
    }
    if (input->read_from == FILE_STRING) output_after_checksum(input);
    ft_printf("\n");
}