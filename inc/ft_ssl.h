/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:06:17 by aorji             #+#    #+#             */
/*   Updated: 2019/07/16 20:06:54 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include "../libft-ft_printf/ft_printf.h"
#include <fcntl.h>
#include <errno.h>
# define BUFSIZE 2

enum error_type 
{
    NO_ERROR = 0,
    NO_CMD = 1,
    INVALIDE_CMD = 2,
    INVALIDE_FILE = 3
};

enum cmd_type 
{
    MD5 = 0,
    SHA256 = 1
};

typedef	struct		s_input
{
    char            *message;
	enum cmd_type   cmd_opts;
    enum error_type error;
}					t_input;

t_input     *read_message_from_stdin(t_input *);
t_input     *read_message_from_file(t_input *, char *);

int         run_md5(t_input *);
int         run_sha256(t_input *);

t_input     *validate_input(int, char **);
#endif