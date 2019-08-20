/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 16:06:16 by aorji             #+#    #+#             */
/*   Updated: 2019/08/20 16:15:03 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha384_512.h"

void sha512_output(t_input *input, uint64_t H[])
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