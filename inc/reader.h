/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 13:09:57 by aorji             #+#    #+#             */
/*   Updated: 2019/08/08 18:31:51 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

#include "../inc/ft_ssl.h"

# include <fcntl.h>
# include <errno.h>
# include <sys/mman.h>
# include <sys/stat.h>

# define    BUFFSIZE 64
// # define    BUFSIZE 64

void        read_message_from_stdin(t_input *);
void        read_message_from_file(t_input *);

#endif