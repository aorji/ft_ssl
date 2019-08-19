/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnitTest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:36:15 by aorji             #+#    #+#             */
/*   Updated: 2019/08/19 13:57:18 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

class TestParam {
public:
	TestParam(std::string cmd, std::string exp): command(cmd), expected_result(exp) {}
	~TestParam(){}
	std::string getCommand(void) const { return command; }
	std::string getExpected(void) const { return expected_result; }

private:
	std::string command;
	std::string expected_result;
};

class UnitTest {

public:
	UnitTest();
	~UnitTest();

	void EmptyTests();
	void InitEmtpyCases();

	void ErrorTests();
	void InitErrorCases();
	
	void BasicTests();
	void InitBasicCases();
	
	void LongTermTests();
	void InitLongTermCases();

	void Summary(void);

private:
	void ASSERT_EQ(std::string expected, std::string actual );
	void ASSERT_NE(std::string val1, std::string val12 );
	void RunTests(std::vector<TestParam>);

	int _test_num;
	int _SUCCESSFUL;
	int _FAILED;
	std::vector<TestParam> emptyTestCases;
	std::vector<TestParam> errorTestCases;
	std::vector<TestParam> basicTestCases;
	std::vector<TestParam> longTermTestCases;

};