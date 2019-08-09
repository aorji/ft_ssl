/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:29:29 by aorji             #+#    #+#             */
/*   Updated: 2019/08/09 15:37:08 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

// norminette -R CheckForbiddenSourceHeader <filename>

void set_message(t_input *input, void *message, char *message_name, int size)
{
    input->message = ft_strdup(message);
    input->message_name = message_name;
    input->message_size = size;
}

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
    input->flags_set = (char *)malloc(sizeof(char) * flags_num);
    ft_bzero(input->flags_set, flags_num);
    input->flags_opt = "pqrs";
    input->total_size = 0;
    return (input);
}

void set_flag(t_input *input, char flag, int i)                                    /* set 1 insted of 0 in flaf_set array */
{
    (input->flags_set)[flag % (input->flags_opt)[0]] = i;
}

int get_flag(t_input *input, char c)
{
    if ((input->flags_set)[c % (input->flags_opt)[0]] == 1)
        return 1;
    return 0;
}