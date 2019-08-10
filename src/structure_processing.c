/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:29:29 by aorji             #+#    #+#             */
/*   Updated: 2019/08/10 20:46:44 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

t_input *init_input(int ac, char **av)
{
    t_input *input;

    input = (t_input *)malloc(sizeof(t_input));
    input->ac = ac;
    input->av = av;
    input->read_from = STDIN;
    input->position = 2;
    input->cmd_opts = NO_TYPE;
    input->error = NO_ERROR;
    input->message_name = NULL;
    reset_arr(input->flags_set, "", FLAG_NUM, 0);
    reset_arr(input->flags_opt, "pqrs", FLAG_NUM, FLAG_NUM);
    input->total_size = 0;
    return (input);
}

void set_message(t_input *input, char *message, char *message_name, int size)
{
    reset_arr(input->message, message, MAX_HASH_MESSAGE_LEN, size);
    input->message_name = message_name;
    input->message_size = size;
}

void set_flag(t_input *input, char flag, int i)
{
    (input->flags_set)[flag % (input->flags_opt)[0]] = i;
}

uint8_t get_flag(t_input *input, char c)
{
    return (input->flags_set)[c % (input->flags_opt)[0]];
}

void reset_arr(uint8_t dst[], char src[], int dstlen, int srclen)
{
    int i = 0;
    while(i < srclen)
    {
        dst[i] = src[i];
        i++;
    }
    while(i < dstlen)
    {
        dst[i] = 0;
        i++;
    }
}
