/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:19:47 by aorji             #+#    #+#             */
/*   Updated: 2019/08/19 14:26:15 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void md5_output(t_input *input, uint32_t H[])
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