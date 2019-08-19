/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:36:23 by aorji             #+#    #+#             */
/*   Updated: 2019/08/19 16:51:44 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha384_512.h"

void sha384_output(t_input *input, uint64_t H[])
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