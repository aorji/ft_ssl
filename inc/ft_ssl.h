/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:06:17 by aorji             #+#    #+#             */
/*   Updated: 2019/08/09 15:35:00 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft-ft_printf/ft_printf.h"

# include <fcntl.h>
# include <errno.h>
# include <sys/mman.h>
# include <sys/stat.h>

#define    BUFFSIZE 64
#define flags_num 4

// typedef long double		t_vector __attribute__((vector_size(sizeof(LD)*3))); 

enum    input_type
{
    STDIN = 0,
    FILE_STRING = 1
};

enum    error_type
{
    NO_ERROR = 0,
    NO_CMD = 1,
    INVALIDE_CMD = 2,
    INVALIDE_FLAG = 3
};

enum    cmd_type
{
    NO_TYPE = 0,
    MD5 = 1,
    SHA256 = 2
};

typedef	struct		s_input
{
    int             ac;
    char            **av;
    int             position;
	enum cmd_type   cmd_opts;
    enum error_type error;
    enum input_type read_from;
    char    *flags_opt;
    char    *flags_set;
    void            *message;
    size_t          message_size;
    char            *message_name;
    size_t total_size;
}					t_input;

enum    hash_mode
{
    CONTINUE = 0,
    START = 1,
    FINISH = 1
};

enum hash_mode  md5(t_input *input);
enum hash_mode sha256(t_input *input);
enum hash_mode call_hashing_algorithm(t_input *input);

static      enum hash_mode (*hashing_algorithm[])(t_input *input) = { &md5, &sha256 };

t_input *init_input(int ac, char **av);
void    set_message(t_input *input, void *message, char *message_name, int size);
void    set_flag(t_input *input, char flag, int i);
int     get_flag(t_input *input, char c);

void    validate_input(t_input *input);
void    print_error(enum cmd_type cmd, char *filename, char *error_str);
void    process_flags(t_input *input);

void    process_stdin_files(t_input *input);
void    read_message_from_stdin(t_input *input);
void    read_message_from_file(t_input *input);
void    read_message_from_string(t_input *input, int pos);

size_t  get_filesize(const char *filename);
size_t  is_dir(const char *filename);
int     validate_file(t_input *input, int fd);

// void        print_bitset(uint8_t *, size_t);
// void        print_xset(uint8_t *, size_t);

#endif
