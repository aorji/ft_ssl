/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnitTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:38:14 by aorji             #+#    #+#             */
/*   Updated: 2019/08/19 14:03:08 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_hpp/UnitTest.hpp"

UnitTest::UnitTest(){
	_SUCCESSFUL = 0;
	_FAILED = 0;
	_test_num = 0;
}

UnitTest::~UnitTest(){}

void
UnitTest::ASSERT_EQ(std::string expected, std::string actual )
{
	_test_num++;
	if (expected == actual)
	{
		_SUCCESSFUL++;
		std::cout << "\033[32m[ ✔ ]\033[0m	#"  <<  _test_num << std::endl;
	}
	else
	{
		_FAILED++;		
		std::cout <<"exp:" << expected << "\nact:"<< actual << "\n";
		std::cout << "\033[31m[ × ]\033[0m	#"  << _test_num << std::endl;
	}
}

void
UnitTest::ASSERT_NE(std::string val1, std::string val12 )
{
	_test_num++;
	if (val1 != val12)
	{
		_SUCCESSFUL++;
		std::cout << "\033[32m[ ✔ ]\033[0m	#"  << _test_num << std::endl;
	}
	else
	{
		_FAILED++;
		std::cout << "\033[31m[ × ]\033[0m	#"  << _test_num << std::endl;
	}
}

void
UnitTest::RunTests(std::vector<TestParam> cases)
{
	FILE *buf;

	for(auto const& v: cases)
	{
		char res[400];
		std::string s = "";
		buf = popen(v.getCommand().c_str(), "r");
		while(!feof(buf))
		{
			if (fgets(res, 400, buf))
				s += std::string(res);
		}
		ASSERT_EQ(v.getExpected(), s);
		pclose(buf);
	}
}

void
UnitTest::EmptyTests()
{
	std::cout << "\nEMPTY TESTS" << std::endl;
	this->InitEmtpyCases();
	this->RunTests(emptyTestCases);
}

void
UnitTest::ErrorTests()
{
	std::cout << "\nERROR TESTS" << std::endl;
	this->InitErrorCases();
	this->RunTests(errorTestCases);
}

void
UnitTest::BasicTests()
{
	this->InitBasicCases();

	std::cout << "\nBASIC TESTS" << std::endl;
	this->RunTests(basicTestCases);
}

void
UnitTest::LongTermTests()
{
	this->InitLongTermCases();

	std::cout << "\nLONG TERM TESTS" << std::endl;
	this->RunTests(longTermTestCases);
}

void
UnitTest::Summary()
{
	std::cout << "\n" << _SUCCESSFUL << "\t\033[32mSUCCESSFUL\033[0m" << std::endl;
	std::cout << _FAILED << "\t\033[31mFAILED\033[0m" << std::endl;
}