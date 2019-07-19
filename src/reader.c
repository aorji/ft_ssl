/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:48:11 by aorji             #+#    #+#             */
/*   Updated: 2019/07/19 16:43:10 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

t_input *read_message_from_stdin(t_input *input)
{
    char    buf[BUFSIZE];
    size_t  input_size = 0;
    char    *resulting_str = (char *)malloc(sizeof(char) * input_size);
    resulting_str[0] = '\0';

    while ( 1 )
    {
        if (fgets(buf, sizeof buf, stdin))
        {
            input_size += ft_strlen(buf);
            resulting_str = (char *)realloc(resulting_str, input_size); 
            ft_strcat(resulting_str, buf);
            if ( resulting_str[input_size - 1] == '\n')
                break;
            continue;
        }
        break;
    }
    push_back(&input->message, resulting_str);
    return input;
}

t_input *read_message_from_file(t_input *input)
{
    char    buf[BUFSIZE + 1];
    size_t  input_size = 0;

    for (int i = 2; i < input->ac; ++i)
    {
        char    *resulting_str = (char *)malloc(sizeof(char) * input_size);
        resulting_str[0] = '\0';
        FILE *file = fopen((input->av)[i], "r");

        if ( !file )
        {
            ft_printf("%s", "ft_ssl: Error while opening the file\n");
            input->error = INVALIDE_FILE;
            return input;
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
                    input->error = INVALIDE_FILE;
                    return input;
                }
                break;
            }
        }
        push_back(&input->message, resulting_str);
        fclose(file);
    }
    return input;  
}


    // int filedesc = open(filename, O_RDONLY);

    // if (filedesc < 0)
    // {
    //     ft_printf("%s%s\n", "ft_ssl: Error opening file: ", strerror( errno ));
    //     input->error = INVALIDE_FILE;
    //     return input;
    // }