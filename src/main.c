/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 13:03:37 by aorji             #+#    #+#             */
/*   Updated: 2019/08/10 21:03:00 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

enum hash_mode call_hashing_algorithm(t_input *input)
{
    return (*hashing_algorithm[input->cmd_opts - 1])(input);
}

int main(int ac, char **av)
{
    t_input *input = init_input(ac, av);

    validate_input(input);
    process_flags(input);

    if (input->error)
        return 0;
    
    process_stdin_files(input);
    free(input);
    // system ("leaks a.out");
    return 0;
}