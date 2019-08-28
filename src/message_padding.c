/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_padding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:23:37 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 14:48:19 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

/*
** step 1
*/

void	append_padding(uint8_t message[], size_t from, size_t to)
{
	message[from] = 0x80;
	while (++from < to)
		message[from] = 0;
}

/*
** step 2
*/

void	append_lenght_bigend(uint8_t message[], size_t from,\
size_t len, int padding_size)
{
	int i;

	i = padding_size - 1;
	while (i >= 0)
	{
		message[from + i] = (uint8_t)(len);
		len = len >> 8;
		--i;
	}
}

void	append_lenght(uint8_t message[], size_t from, size_t len,\
int padding_size)
{
	int i;

	i = 0;
	while (i < padding_size)
	{
		message[from + i] = (uint8_t)(len);
		len = len >> 8;
		i++;
	}
}

/*
** return number of blocks
*/

int		add_padding_bigend(t_input *input, size_t n, size_t a, int len_size)
{
	if (input->message_size < n)
	{
		if (input->message_size >= a)
		{
			append_padding(input->message, input->message_size,
			g_max_message_len);
			append_lenght_bigend(input->message, g_max_message_len,
			input->total_size * BIT_NUM, len_size);
			return (2);
		}
		append_padding(input->message, input->message_size, a);
		append_lenght_bigend(input->message, a,
		input->total_size * BIT_NUM, len_size);
		return (1);
	}
	return (1);
}

int		add_padding(t_input *input, size_t n, size_t a, int len_size)
{
	if (input->message_size < n)
	{
		if (input->message_size >= a)
		{
			append_padding(input->message, input->message_size,
			g_max_message_len);
			append_lenght(input->message, g_max_message_len,
			input->total_size * BIT_NUM, len_size);
			return (2);
		}
		append_padding(input->message, input->message_size, a);
		append_lenght(input->message, a,
		input->total_size * BIT_NUM, len_size);
		return (1);
	}
	return (1);
}
