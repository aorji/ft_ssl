/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_padding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:23:37 by aorji             #+#    #+#             */
/*   Updated: 2019/08/21 20:23:50 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

/*
 * step 1
 */
void append_padding(uint8_t message[], size_t from, size_t to)
{
	// uint8_t PADDING[padding_size] = { 0x80 };
	message[from] = 0x80;
    while(++from < to)
        message[from] = 0;
}

/*
 * step 2
 */
void append_lenght_bigend(uint8_t message[], size_t from, size_t len, int padding_size)
{
	int i = padding_size - 1;
    while(i >= 0)
    {
        message[from + i] = (uint8_t)(len);
        len = len >> 8;
		--i;
    }
}

void append_lenght(uint8_t message[], size_t from, size_t len, int padding_size)
{
    for(int i = 0; i < padding_size; ++i)
    {
        message[from + i] = (uint8_t)(len);
        len = len >> 8;
    }
}