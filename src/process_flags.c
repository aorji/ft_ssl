/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:41:54 by aorji             #+#    #+#             */
/*   Updated: 2019/08/08 19:30:44 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static void add_flag(t_input *input)
{
    size_t j = 1;
    while ((input->av)[input->position][j])
    {
        if ((input->av)[input->position][j] < input->flag->flags_opt[0] || (input->av)[input->position][j] > input->flag->flags_opt[no_arg_flag_num - 1])
        {
            ft_printf("%s%c%s\n", "md5: illegal option -- ", (input->av)[input->position][j], "\nusage: md5 [-pqr] [-s string] [files ...]");
            input->error = INVALIDE_FLAG;
            return;
        }
        set_flag(input, (input->av)[input->position][j], 1);
        if ((input->av)[input->position][j] == 's')
        {
            input->read_from = FILE_STRING;
            read_message_from_string(input, j);
            return;
        }
        else if ((input->av)[input->position][j] == 'p')
        {
            read_message_from_stdin(input);
        }
        j++;
    }
}

void process_flags(t_input *input)
{
    while (input->position < input->ac && (input->av)[input->position][0] == '-' && !(input->error))
    {
        add_flag(input);
        input->position++;
    }
    if (input->position < input->ac)
        input->read_from = FILE_STRING;
}
