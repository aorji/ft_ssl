/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitTestCases.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 20:15:05 by aorji             #+#    #+#             */
/*   Updated: 2019/08/16 21:23:00 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_hpp/UnitTest.hpp"


void
UnitTest::InitEmtpyCases()
{
	/*
	**	md5
	*/
	emptyTestCases.push_back(\
			TestParam("./ft_ssl md5 -s \"\"", "MD5 (\"\") = d41d8cd98f00b204e9800998ecf8427e\n"));
	emptyTestCases.push_back(TestParam\
			("./ft_ssl md5 test_files/empty", "MD5 (test_files/empty) = d41d8cd98f00b204e9800998ecf8427e\n"));
	/*
	**	sha256
	*/
	emptyTestCases.push_back(TestParam\
			("./ft_ssl sha256 -s \"\"", "SHA256 (\"\") = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\n"));
	emptyTestCases.push_back(TestParam\
			("./ft_ssl sha256 test_files/empty", "SHA256 (test_files/empty) = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\n"));
}

void
UnitTest::InitErrorCases()
{
	/*
	**	md5
	*/
	errorTestCases.push_back(TestParam("./ft_ssl md5 -sh -s", "MD5 (\"h\") = 2510c39011c5be704182423e3a695e91\n"));
	errorTestCases.push_back(TestParam("./ft_ssl md5 -d", ""));
	errorTestCases.push_back(TestParam("./ft_ssl", "usage: ft_ssl command [command opts] [command args]\n"));
	errorTestCases.push_back(TestParam("./ft_ssl md5 -r test_files/67.txt -q test_files/test_with_nonewline.c", "148c0ad822a6b9020256b3e5482eab00 test_files/67.txt\n\
bab8b3201b99cbabedd725597d545804 test_files/test_with_nonewline.c\n"));
	/*
	**	sha256
	*/
	errorTestCases.push_back(TestParam("./ft_ssl sha256 -sh -s", "SHA256 (\"h\") = aaa9402664f1a41f40ebbc52c9993eb66aeb366602958fdfaa283b71e64db123\n"));
	errorTestCases.push_back(TestParam("./ft_ssl sha256 -d", ""));
}

void
UnitTest::InitBasicCases()
{
	/*
	**	md5
	*/
	/* string */
	basicTestCases.push_back(TestParam("./ft_ssl md5 -shellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll -s world",\
	"MD5 (\"hellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll\") = 9bed0076f30c767a6cfc66a27304fce9\n\
MD5 (\"world\") = 7d793037a0760186574b0282f2f435e7\n"));
	basicTestCases.push_back(TestParam("./ft_ssl md5 -shello -qs world",\
	"MD5 (\"hello\") = 5d41402abc4b2a76b9719d911017c592\n\
7d793037a0760186574b0282f2f435e7\n"));
	/* flags */
	basicTestCases.push_back(TestParam("./ft_ssl md5 -r test_files/67.txt", "148c0ad822a6b9020256b3e5482eab00 test_files/67.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl md5 -rq test_files/br.txt", "3e58b3eb125c5f235d0f1462a347906d\n"));
	basicTestCases.push_back(TestParam("./ft_ssl md5 -qr test_files/chmod000", "d41d8cd98f00b204e9800998ecf8427e\n"));
	/* stdin */
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl md5 -r test_files/f1.txt", "9edf73a4ea9967d6de52b03e3a31e6fc test_files/f1.txt\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl md5", "b1946ac92492d2347c6235b4d2611184\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl md5 -r", "b1946ac92492d2347c6235b4d2611184\n"));
	basicTestCases.push_back(TestParam("echo \"h\" | ./ft_ssl md5 -r", "01fbdc44ef819db6273bc30965a23814\n"));
	basicTestCases.push_back(TestParam("cat test_files/rich_poor_chapt1.txt | ./ft_ssl md5 -r", "d39d4f0b51697154e1a136749ee86509\n"));
	basicTestCases.push_back(TestParam("cat test_files/rich_poor_chapt1.txt | ./ft_ssl md5 -rq", "d39d4f0b51697154e1a136749ee86509\n"));
	/*
	**	sha256
	*/
	basicTestCases.push_back(TestParam("./ft_ssl sha256 -shellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll -s world",\
	"SHA256 (\"hellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll\") = dbb085e9de2c35e6ce2ac4d1f37253a67b181d5ab049b8f063e941903831f182\n\
SHA256 (\"world\") = 486ea46224d1bb4fb680f34f7c9ad96a8f24ec88be73ea8e5a6c65260e9cb8a7\n"));
	/* flags */
	basicTestCases.push_back(TestParam("./ft_ssl sha256 -r test_files/67.txt", "1375293b850e5a37605c9de4d7355783deccfaa16a553b6c0821e13082aa2d96 *test_files/67.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha256 -rq test_files/br.txt", "d438ebf3636abd6c029bbfd48845ab6b6c99328419bc281e88cd64c05c2b0479\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha256 -qr test_files/chmod000", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\n"));
	/* stdin */
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha256 -r test_files/f1.txt", "8ff33124853e07eea7a6a0a4241e55b831d6680beeb8221f4037b4bf70597ee3 *test_files/f1.txt\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha256", "5891b5b522d5df086d0ff0b110fbd9d21bb4fc7163af34d08286a2e846f6be03\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha256 -r", "5891b5b522d5df086d0ff0b110fbd9d21bb4fc7163af34d08286a2e846f6be03\n"));
	basicTestCases.push_back(TestParam("echo \"h\" | ./ft_ssl sha256 -r", "91ee5e9f42ba3d34e414443b36a27b797a56a47aad6bb1e4c1769e69c77ce0ca\n"));
	basicTestCases.push_back(TestParam("cat test_files/rich_poor_chapt1.txt | ./ft_ssl sha256 -r", "5ea5ad1f378c2da7ff81b11f222323b48b430d1cf00995ffda5f219996ffc13b\n"));
	basicTestCases.push_back(TestParam("cat test_files/rich_poor_chapt1.txt | ./ft_ssl sha256 -rq", "5ea5ad1f378c2da7ff81b11f222323b48b430d1cf00995ffda5f219996ffc13b\n"));
}

void
UnitTest::InitLongTermCases()
{
	/*
	**	md5
	*/
	longTermTestCases.push_back(TestParam("./ft_ssl md5 test_files/Xsizefile", "MD5 (test_files/Xsizefile) = 8e6e18dfb1e22d75bafc597f06cf202a\n"));
	/*
	**	sha256
	*/
	longTermTestCases.push_back(TestParam("./ft_ssl sha256 test_files/Xsizefile", "SHA256 (test_files/Xsizefile) = 5bb0f523f99f93fa91559393216a6ffa499ac76ea95f6b3550d43fa80f4dfe0f\n"));
}