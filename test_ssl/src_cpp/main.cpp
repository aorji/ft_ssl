/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:34:35 by aorji             #+#    #+#             */
/*   Updated: 2019/08/16 21:23:14 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_hpp/UnitTest.hpp"

int main()
{
	UnitTest test;

	test.EmptyTests();
	test.BasicTests();
	test.LongTermTests();
	test.ErrorTests();
}