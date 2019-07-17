/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 13:03:37 by aorji             #+#    #+#             */
/*   Updated: 2019/07/17 13:20:36 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

//run:  ./ft_ssl

int main(int ac, char **av) {

    // validate input
    t_input *input = validate_input(ac, av);
    if (input->error)
        return 0;
    
    // read message
    (ac > 2) ? read_message_from_file(input, av[2]) : read_message_from_stdin(input);
    if (input->error)
        return 0;

    // run requested hashing algorithm
    int (*hashing_algorithm[])(t_input *) = {md5, sha256}; 
    (*hashing_algorithm[input->cmd_opts])(input);

    // system ("leaks a.out");

    return 0;
}