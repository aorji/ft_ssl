/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:23:30 by aorji             #+#    #+#             */
/*   Updated: 2019/07/17 15:39:28 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

t_input *create_input( void )
{
    t_input *input = (t_input *)malloc(sizeof(t_input));
    input->message = NULL;
    input->cmd_opts = 0;
    input->error = 0;
    return input;
}