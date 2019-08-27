/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:06:17 by aorji             #+#    #+#             */
/*   Updated: 2019/08/27 17:57:17 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft-ft_printf/ft_printf.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/mman.h>
# include <sys/stat.h>

#define FLAG_NUM 4

uint32_t g_buffsize, g_max_message_len;

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
    INVALIDE_FLAG = 3,
	INVALIDE_PARAM
};

enum    cmd_type
{
    NO_TYPE,
    MD5,
    SHA224,
    SHA256,
    SHA384,
    SHA512,
	NUM_OF_CMD
};

typedef	struct		s_input
{
    int             ac;
    char            **av;

    int             position;
	enum cmd_type   cmd_opts;
    enum error_type error;
    enum input_type read_from;

    uint8_t         flags_opt[FLAG_NUM];
    uint8_t         flags_set[FLAG_NUM];

    uint8_t         message[256];
    size_t          message_size;
    char            *message_name;

    size_t          total_size;
}					t_input;

enum    mode
{
    CONTINUE = 0,
    START = 1,
    FINISH = 1
};

void            reset_arr(uint8_t dst[], char src[], int dstlen, int srclen);

enum mode  md5(t_input *input, char *func_name);
enum mode  sha224(t_input *input, char *func_name);
enum mode  sha256(t_input *input, char *func_name);
enum mode  sha384(t_input *input, char *func_name);
enum mode  sha512(t_input *input, char *func_name);
enum mode  call_hashing_algorithm(t_input *input, char *func_name);
static enum mode  (*hashing_algorithm[])(t_input *input, char *func_name) = { &md5, &sha224, &sha256, &sha384, &sha512 };

/*  structure_processing.c  */
t_input         *init_input(int ac, char **av);
void            set_message(t_input *input, char *message, char *message_name, int size);
void            set_flag(t_input *input, char flag, int i);
uint8_t             get_flag(t_input *input, char c);

void            validate_input(t_input *input);
void            error_output(t_input *input, char *filename, char *error_str);

/*  flags_processing.c      */
void            process_flags(t_input *input);

/*  message_processing.c    */
void            process_stdin_files(t_input *input);
void            process_message_from_stdin(t_input *input);
void            process_message_from_file(t_input *input);
void            process_message_from_string(t_input *input, int pos);

/*  file_validation.c       */
size_t          get_filesize(const char *filename);
size_t          is_dir(const char *filename);
int             validate_file(t_input *input, int fd);

/*	hash_output			*/
void			output_after_checksum(t_input *input);
void			output_before_checksum(t_input *input, const char *cmd_name);
char			*fstrjoin(char const *s1, char const *s2, size_t len1, size_t len2);

/*	message_padding			*/
void			append_padding(uint8_t message[], size_t from, size_t to);
void			append_lenght_bigend(uint8_t message[], size_t from, size_t len, int padding_size);
void			append_lenght(uint8_t message[], size_t from, size_t len, int padding_size);

uint64_t		lit_to_bigendian64(uint64_t word);
uint32_t		lit_to_bigendian(uint32_t word);

#endif