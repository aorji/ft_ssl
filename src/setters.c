/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:29:29 by aorji             #+#    #+#             */
/*   Updated: 2019/08/01 17:21:02 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

// norminette -R CheckForbiddenSourceHeader <filename>

void set_message(t_input *input, char *message, char *message_name)
{
    input->message = ft_strdup(message);
    input->message_name = message_name;
    input->message_size = ft_strlen(message);
}

t_input *set_input(int ac, char **av)
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
    input->flag = (t_flag *)malloc(sizeof(t_flag));
    input->flag->flags_set = (char *)malloc(sizeof(char) * no_arg_flag_num);
    ft_bzero(input->flag->flags_set, no_arg_flag_num);
    input->flag->flags_opt = "pqrs";
    return (input);
}

void set_flag(t_input *input, char flag, int i)                                    /* set 1 insted of 0 in flaf_set array */
{
    (input->flag->flags_set)[flag % (input->flag->flags_opt)[0]] = i;
}

int get_flag(t_input *input, char c)
{
    if ((input->flag->flags_set)[c % (input->flag->flags_opt)[0]] == 1)
        return 1;
    return 0;
}