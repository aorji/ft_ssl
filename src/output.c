/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:19:47 by aorji             #+#    #+#             */
/*   Updated: 2019/07/26 13:49:15 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void print_bitset(uint8_t *str, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        ft_printf("%s ", ft_itoa_base((int)(str[i]), 2));
        i++;
    }
    ft_printf("\n");
}

void print_xset(uint8_t *str, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        ft_printf("%x ", (int)(str[i]));
        i++;
    }
    ft_printf("\n");
}