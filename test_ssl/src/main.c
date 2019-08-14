/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 14:27:03 by aorji             #+#    #+#             */
/*   Updated: 2019/08/14 21:00:59 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/test_ssl.h"

#define EXIT(s) { ft_printf("%s\n", s); exit(1); }

char *njoin(int test_case, int param_num)
{
	char *res;
	size_t len = 0;
	int i = 0;
	size_t j = 0;
	size_t k = 0;
	
	while (i < param_num)
	{
		len += ft_strlen(test_cases[test_case][i]);
		i++;
	}
	len += param_num - 1; // for spaces between words

	//concatination
	res = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < param_num)
	{
		j = 0;
		if (!test_cases[test_case][i])
		{
			i++;
			continue;
		}
		len = ft_strlen(test_cases[test_case][i]);
		while (j < len)
		{
			res[k] = test_cases[test_case][i][j];
			j++;
			k++;
		}

		res[k] = ' ';
		k++;
		i++;
	}
	res[k - 1] = '\0';
	return res;
}

static int validate_result(FILE *first, FILE *second)
{
	int ch1 = getc(first);
	int ch2 = getc(second);
 
	while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2))
	{
		ch1 = getc(first);
		ch2 = getc(second);
	}
	fclose(first);
	fclose(second);
	if (ch1 == ch2)
		return 1;
	return 0;
}

static void run_test(char *cmd)
{
	FILE *first;
	FILE *second;
	char *cmd_recode;

	first = popen(cmd, "r");

	cmd_recode = ft_strjoin("./ft_ssl ", cmd);
	second = popen(cmd_recode, "r");
	ft_strdel(&cmd_recode);

	if (!first || !second)
		EXIT("Faild to create pipe");
	
	if (validate_result(first, second))
		ft_printf("\033[32m[ ✔ ]\033[0m	");
	else
		ft_printf("\033[31m[ × ]\033[0m	");

	pclose(first);
	pclose(second);

}

int main(int ac, char **av)
{
	int i = 0;
	int test_cases_num = sizeof(test_cases)/sizeof(test_cases[0]);
	int param_num = sizeof(test_cases[0])/sizeof(test_cases[0][0]);

	if (ac == 2)
		i = ft_atoi(av[1]) - 1;
	else if (ac < 2)
	{
		ft_printf("%s %d %s\n", "You have available", test_cases_num, "test cases");
		ft_printf("%s",\
		"usage: ./test_ssl <test num from which to start>\n");
		return 0;
	}
	while (i < test_cases_num)
	{
		char *test_cmd = njoin(i, param_num);
		run_test(test_cmd);
		ft_strdel(&test_cmd);
		ft_printf("#%d\n", i + 1);
		i++;
	}
	return 0;
}