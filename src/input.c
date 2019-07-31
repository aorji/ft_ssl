/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:23:30 by aorji             #+#    #+#             */
/*   Updated: 2019/07/31 17:29:55 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

t_input *create_input(int ac, char **av)
{
    t_input *input;

    input = (t_input *)malloc(sizeof(t_input));
    input->ac = ac;
    input->av = av;
    input->position = 0;
    input->cmd_opts = NO_TYPE;
    input->error = NO_ERROR;
    input->read_from = STDIN;
    input->message = NULL;
    input->message_name = NULL;
    input->flag = (t_flag *)malloc(sizeof(t_flag));
    input->flag->flags_set = (char *)malloc(sizeof(char) * no_arg_flag_num);
    ft_bzero(input->flag->flags_set, no_arg_flag_num);
    input->flag->flags_opt = "pqrs";
    return (input);
}
