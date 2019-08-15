/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:30:56 by aorji             #+#    #+#             */
/*   Updated: 2019/08/15 19:14:47 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha256.h"

void sha256_output(t_input *input __unused, uint32_t H0, uint32_t H1, uint32_t H2, uint32_t H3,\
 uint32_t H4, uint32_t H5, uint32_t H6, uint32_t H7)
{
    int i = 32;
    while(i--)
    {
        ft_printf("%.2x", (uint8_t)H0);
        H0 >>= 8;
        if (i == 4){ H0 = H7;
			ft_printf("	");}
        else if (i == 8){ H0 = H6;
					ft_printf("	");}
        else if (i == 12) {H0 = H5;
					ft_printf("	");}
        else if (i == 16) {H0 = H4;
					ft_printf("	");}
        else if (i == 20) {H0 = H3;
					ft_printf("	");}
        else if (i == 24) {H0 = H2;
					ft_printf("	");}
        else if (i == 28) {H0 = H1;
					ft_printf("	");}
    }
    ft_printf("\n");
}