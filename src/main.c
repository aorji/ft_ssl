/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 13:03:37 by aorji             #+#    #+#             */
/*   Updated: 2019/08/01 16:29:25 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

// norminette -R CheckForbiddenSourceHeader <filename>

void call_hashing_algorithm(t_input *input)
{
    (*hashing_algorithm[input->cmd_opts - 1])(input);
}

int main(int ac, char **av)
{
    t_input *input = set_input(ac, av);

    validate_input(input);
    process_flags(input);

    if (input->error)
        return 0;
    
    process_stdin_files(input);
    //free input
    // system ("leaks a.out");

    return 0;
}