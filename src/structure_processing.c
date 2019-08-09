/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:29:29 by aorji             #+#    #+#             */
/*   Updated: 2019/08/09 21:48:49 by aorji            ###   ########.fr       */
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
    input->message = NULL;
    input->message_name = NULL;
    input->flags_set = (char *)malloc(sizeof(char) * FLAG_NUM);
    ft_bzero(input->flags_set, FLAG_NUM);
    input->flags_opt = "pqrs";
    input->total_size = 0;
    return (input);
}

void clear_input(t_input *input __unused)
{
    // free(input->flags_set);
    // free(input);
}

void set_message(t_input *input, void *message, char *message_name, int size)
{
    input->message = ft_strdup(message);
    input->message_name = message_name;
    input->message_size = size;
}

void set_flag(t_input *input, char flag, int i)
{
    (input->flags_set)[flag % (input->flags_opt)[0]] = i;
}

int get_flag(t_input *input, char c)
{
    if ((input->flags_set)[c % (input->flags_opt)[0]] == 1)
        return 1;
    return 0;
}