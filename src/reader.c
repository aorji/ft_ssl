/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:48:11 by aorji             #+#    #+#             */
/*   Updated: 2019/08/01 17:43:11 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void read_message_from_stdin(t_input *input)
{
    char    buf[BUFSIZE];
    size_t  input_size = 0;
    char    *resulting_str = (char *)malloc(sizeof(char));
    resulting_str[0] = '\0';

    while ( 1 )
    {
        if (fgets(buf, sizeof buf, stdin))
        {
            input_size += ft_strlen(buf);
            resulting_str = (char *)realloc(resulting_str, input_size); 
            ft_strcat(resulting_str, buf);
            continue;
        }
        break;
    }
    set_message(input, resulting_str, resulting_str);
    call_hashing_algorithm(input);
    free(resulting_str);
}

static void read_message_from_file(t_input *input)
{
    char    buf[BUFSIZE + 1];
    size_t  input_size = 0;

    for (; input->position < input->ac; ++(input->position))
    {
        char    *resulting_str = (char *)malloc(sizeof(char));
        resulting_str[0] = '\0';
        FILE *file = fopen((input->av)[input->position], "r");

        if ( !file )
        {
            ft_printf("%s: %s: %s", "ft_ssl", (input->av)[input->position], "Error while opening the file\n");
            // input->error = INVALIDE_FILE;
            continue;
        }
        while ( 1 )
        {
            if (fgets(buf, sizeof buf, file))
            {
                input_size += sizeof buf;
                resulting_str = (char *)realloc(resulting_str, input_size);
                ft_strcat(resulting_str, buf);
                if ( resulting_str[input_size - 1] == '\n')
                    break;
            }
            else
            {
                if (ferror(stdin))  //return 0 if an error occurred
                {
                    ft_printf("%s", "ft_ssl: Error while reading the file\n");
                    // input->error = INVALIDE_FILE;
                    continue;
                }
                break;
            }
        }
        set_message(input, resulting_str, (input->av)[input->position]);
        call_hashing_algorithm(input);
        free(resulting_str);
        fclose(file);
    }
}
 
void process_stdin_files(t_input *input)
{
    if(input->read_from == STDIN)
        read_message_from_stdin(input);
    if (input->read_from == FILE_STRING)
        read_message_from_file(input);
}


    // int filedesc = open(filename, O_RDONLY);

    // if (filedesc < 0)
    // {
    //     ft_printf("%s%s\n", "ft_ssl: Error opening file: ", strerror( errno ));
    //     input->error = INVALIDE_FILE;
    //     return input;
    // }