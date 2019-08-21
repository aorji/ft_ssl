/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitTestCases.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 20:15:05 by aorji             #+#    #+#             */
/*   Updated: 2019/08/21 15:13:20 by aorji            ###   ########.fr       */
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
			("./ft_ssl md5 test_ssl/test_files/empty", "MD5 (test_ssl/test_files/empty) = d41d8cd98f00b204e9800998ecf8427e\n"));
	/*
	**	sha256
	*/
	emptyTestCases.push_back(TestParam\
			("./ft_ssl sha256 -s \"\"", "SHA256 (\"\") = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\n"));
	emptyTestCases.push_back(TestParam\
			("./ft_ssl sha256 test_ssl/test_files/empty", "SHA256 (test_ssl/test_files/empty) = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\n"));
	/*
	**	sha224
	*/
	emptyTestCases.push_back(TestParam\
			("./ft_ssl sha224 -s \"\"", "SHA224 (\"\") = d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f\n"));
	emptyTestCases.push_back(TestParam\
			("./ft_ssl sha224 test_ssl/test_files/empty", "SHA224 (test_ssl/test_files/empty) = d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f\n"));
	/*
	**	sha384
	*/
	emptyTestCases.push_back(TestParam\
			("./ft_ssl sha384 -s \"\"", "SHA384 (\"\") = 38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b\n"));
	emptyTestCases.push_back(TestParam\
			("./ft_ssl sha384 test_ssl/test_files/empty", "SHA384 (test_ssl/test_files/empty) = 38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b\n"));
	/*
	**	sha512
	*/
	emptyTestCases.push_back(TestParam\
			("./ft_ssl sha512 -s \"\"", "SHA512 (\"\") = cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e\n"));
	emptyTestCases.push_back(TestParam\
			("./ft_ssl sha512 test_ssl/test_files/empty", "SHA512 (test_ssl/test_files/empty) = cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e\n"));
}

void
UnitTest::InitErrorCases()
{
	errorTestCases.push_back(TestParam("./ft_ssl md4", ""));
	errorTestCases.push_back(TestParam("./ft_ssl s2hak", ""));
	/*
	**	md5
	*/
	errorTestCases.push_back(TestParam("./ft_ssl md5 -sh -s", "MD5 (\"h\") = 2510c39011c5be704182423e3a695e91\n"));
	errorTestCases.push_back(TestParam("./ft_ssl md5 -d", ""));
	errorTestCases.push_back(TestParam("./ft_ssl", "usage: ft_ssl command [command opts] [command args]\n"));
	errorTestCases.push_back(TestParam("./ft_ssl md5 -r test_ssl/test_files/67.txt -q test_ssl/test_files/test_with_nonewline.c", "148c0ad822a6b9020256b3e5482eab00 *test_ssl/test_files/67.txt\n\
bab8b3201b99cbabedd725597d545804 *test_ssl/test_files/test_with_nonewline.c\n"));
	/*
	**	sha256
	*/
	errorTestCases.push_back(TestParam("./ft_ssl sha256 -sh -s", "SHA256 (\"h\") = aaa9402664f1a41f40ebbc52c9993eb66aeb366602958fdfaa283b71e64db123\n"));
	errorTestCases.push_back(TestParam("./ft_ssl sha256 -d", ""));
	/*
	**	sha224
	*/
	errorTestCases.push_back(TestParam("./ft_ssl sha224 -sh -s", "SHA224 (\"h\") = e0ccaeadfef916630c35576679e4cd4b438e7fc95a60b7361705f708\n"));
	errorTestCases.push_back(TestParam("./ft_ssl sha224 -d", ""));
	/*
	**	sha384
	*/
	errorTestCases.push_back(TestParam("./ft_ssl sha384 -sh -s", "SHA384 (\"h\") = a4eb0778c79fce94c02126543cba398d645b2fd4c6ff6a02eecc026bbe0cc0dd666279722b7615bc15b4c9126b941c04\n"));
	errorTestCases.push_back(TestParam("./ft_ssl sha384 -d", ""));
	/*
	**	sha512
	*/
	errorTestCases.push_back(TestParam("./ft_ssl sha512 -sh -s", "SHA512 (\"h\") = 2241bc8fc70705b42efead371fd4982c5ba69917e5b4b895810002644f0386da9c3131793458c2bf47608480d64a07278133c99912e0ba2daf23098f3520eb97\n"));
	errorTestCases.push_back(TestParam("./ft_ssl sha512 -d", ""));
}

void
UnitTest::InitBasicCases()
{
	basicTestCases.push_back(TestParam("./ft_ssl", "usage: ft_ssl command [command opts] [command args]\n"));
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
	basicTestCases.push_back(TestParam("./ft_ssl md5 -r test_ssl/test_files/56.txt", "99a21be1ed3bf2e80d072807702787e6 *test_ssl/test_files/56.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl md5 -r test_ssl/test_files/67.txt", "148c0ad822a6b9020256b3e5482eab00 *test_ssl/test_files/67.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl md5 -rq test_ssl/test_files/br.txt", "3e58b3eb125c5f235d0f1462a347906d\n"));
	basicTestCases.push_back(TestParam("./ft_ssl md5 -qr test_ssl/test_files/chmod000", "d41d8cd98f00b204e9800998ecf8427e\n"));
	/* stdin */
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl md5 -r test_ssl/test_files/f1.txt", "9edf73a4ea9967d6de52b03e3a31e6fc *test_ssl/test_files/f1.txt\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl md5", "b1946ac92492d2347c6235b4d2611184\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl md5 -r", "b1946ac92492d2347c6235b4d2611184\n"));
	basicTestCases.push_back(TestParam("echo \"h\" | ./ft_ssl md5 -r", "01fbdc44ef819db6273bc30965a23814\n"));
	basicTestCases.push_back(TestParam("cat test_ssl/test_files/rich_poor_chapt1.txt | ./ft_ssl md5 -r", "d39d4f0b51697154e1a136749ee86509\n"));
	basicTestCases.push_back(TestParam("cat test_ssl/test_files/rich_poor_chapt1.txt | ./ft_ssl md5 -rq", "d39d4f0b51697154e1a136749ee86509\n"));
	/*
	**	sha256
	*/
	basicTestCases.push_back(TestParam("./ft_ssl sha256 -shellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll -s world",\
	"SHA256 (\"hellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll\") = dbb085e9de2c35e6ce2ac4d1f37253a67b181d5ab049b8f063e941903831f182\n\
SHA256 (\"world\") = 486ea46224d1bb4fb680f34f7c9ad96a8f24ec88be73ea8e5a6c65260e9cb8a7\n"));
	/* flags */
	basicTestCases.push_back(TestParam("./ft_ssl sha256 -r test_ssl/test_files/56.txt", "36abf9de432d0af648eaefc894d549b8de18caed37308749a2f6373b6f6060b9 *test_ssl/test_files/56.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha256 -r test_ssl/test_files/67.txt", "1375293b850e5a37605c9de4d7355783deccfaa16a553b6c0821e13082aa2d96 *test_ssl/test_files/67.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha256 -rq test_ssl/test_files/br.txt", "d438ebf3636abd6c029bbfd48845ab6b6c99328419bc281e88cd64c05c2b0479\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha256 -qr test_ssl/test_files/chmod000", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\n"));
	/* stdin */
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha256 -r test_ssl/test_files/f1.txt", "8ff33124853e07eea7a6a0a4241e55b831d6680beeb8221f4037b4bf70597ee3 *test_ssl/test_files/f1.txt\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha256", "5891b5b522d5df086d0ff0b110fbd9d21bb4fc7163af34d08286a2e846f6be03\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha256 -r", "5891b5b522d5df086d0ff0b110fbd9d21bb4fc7163af34d08286a2e846f6be03\n"));
	basicTestCases.push_back(TestParam("echo \"h\" | ./ft_ssl sha256 -r", "91ee5e9f42ba3d34e414443b36a27b797a56a47aad6bb1e4c1769e69c77ce0ca\n"));
	basicTestCases.push_back(TestParam("cat test_ssl/test_files/rich_poor_chapt1.txt | ./ft_ssl sha256 -r", "5ea5ad1f378c2da7ff81b11f222323b48b430d1cf00995ffda5f219996ffc13b\n"));
	basicTestCases.push_back(TestParam("cat test_ssl/test_files/rich_poor_chapt1.txt | ./ft_ssl sha256 -rq", "5ea5ad1f378c2da7ff81b11f222323b48b430d1cf00995ffda5f219996ffc13b\n"));
	/*
	**	sha224
	*/
	basicTestCases.push_back(TestParam("./ft_ssl sha224 -shellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll -s world",\
	"SHA224 (\"hellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll\") = a61bbacfaa10d48e8a674bf591d8b9e7eff6bffc360042fd1b49603b\n\
SHA224 (\"world\") = 06d2dbdb71973e31e4f1df3d7001fa7de268aa72fcb1f6f9ea37e0e5\n"));
	/* flags */
	basicTestCases.push_back(TestParam("./ft_ssl sha224 -r test_ssl/test_files/56.txt", "22263c21fd956a62f2376db9aaa00f8baae7d0055dcba60817475074 *test_ssl/test_files/56.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha224 -r test_ssl/test_files/67.txt", "5f63ffad5d9d23106321d750e0e209668ef6da4dddaf6621fc9ceb3d *test_ssl/test_files/67.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha224 -rq test_ssl/test_files/br.txt", "aec4924a9e720e31541cf0a81f232977fbc1eceaa70300ef2ae7903a\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha224 -qr test_ssl/test_files/chmod000", "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f\n"));
	/* stdin */
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha224 -r test_ssl/test_files/f1.txt", "dc99c1e557e513c245354966d11aa9142adee9fc2b3401a5554d2264 *test_ssl/test_files/f1.txt\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha224", "2d6d67d91d0badcdd06cbbba1fe11538a68a37ec9c2e26457ceff12b\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha224 -r", "2d6d67d91d0badcdd06cbbba1fe11538a68a37ec9c2e26457ceff12b\n"));
	basicTestCases.push_back(TestParam("echo \"h\" | ./ft_ssl sha224 -r", "1b0f7d0d9a271633f41a70fcef38f33ddecf42decfc95d27b25bfe41\n"));
	basicTestCases.push_back(TestParam("cat test_ssl/test_files/rich_poor_chapt1.txt | ./ft_ssl sha224 -r", "4585bdd1da449430a8ba54dcf512f7da47082c10e8cb2250d7782abd\n"));
	basicTestCases.push_back(TestParam("cat test_ssl/test_files/rich_poor_chapt1.txt | ./ft_ssl sha224 -rq", "4585bdd1da449430a8ba54dcf512f7da47082c10e8cb2250d7782abd\n"));
	/*
	**	sha384
	*/
	basicTestCases.push_back(TestParam("./ft_ssl sha384 -r test_ssl/test_files/112len.txt", "09330c33f71147e83d192fc782cd1b4753111b173b3b05d22fa08086e3b0f712fcc7c71a557e2db966c3e9fa91746039 *test_ssl/test_files/112len.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha384 -shellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll -s world",\
	"SHA384 (\"hellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll\") = 3d35c0e936c2d8a60c2ac247100f5687a32504bd89781f8a888c7ad8227a627bf3636ba341d177102260b9a7a710c9e7\n\
SHA384 (\"world\") = a4d102bb2a39b6f1d9e481ef1a16b8948a0df2b594fd031bad6f201fbd6b0656846a6e58a30aa57ff34d912e7d3ea185\n"));
	/* flags */
	basicTestCases.push_back(TestParam("./ft_ssl sha384 -r test_ssl/test_files/56.txt", "9ad13cb6ca830725996bd531435c1bfc82bee0b246d98efb256aef58f55a30bb6f81bf379ad040c09db7cdb33f880afa *test_ssl/test_files/56.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha384 -r test_ssl/test_files/67.txt", "c7f806947249b299e76280f1e4043161e17e1caba5c9664b737d56fdf763bb9650fe7b56a98af3ea156bf346ca593ae7 *test_ssl/test_files/67.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha384 -rq test_ssl/test_files/br.txt", "f93ac2db751d07c4d24346a4db72cc20d80078f960ff8651d1c142ae565f7847bbd8953efd3d71068ebd817ec98dcd23\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha384 -qr test_ssl/test_files/chmod000", "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b\n"));
	/* stdin */
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha384 -r test_ssl/test_files/f1.txt", "637c79bf8af37a0910015c0bb7f7a16cbbe2d74da8bb1bf00a1a652bc4ac3163bd1acd026a108841ab824c5e48a738a3 *test_ssl/test_files/f1.txt\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha384", "1d0f284efe3edea4b9ca3bd514fa134b17eae361ccc7a1eefeff801b9bd6604e01f21f6bf249ef030599f0c218f2ba8c\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha384 -r", "1d0f284efe3edea4b9ca3bd514fa134b17eae361ccc7a1eefeff801b9bd6604e01f21f6bf249ef030599f0c218f2ba8c\n"));
	basicTestCases.push_back(TestParam("echo \"h\" | ./ft_ssl sha384 -r", "0943268fbf64f4e645a8e56b6b45336ddd39cbba524e0f9664e99417b9d0ee8dd36090e5a0fa2302e4a534cb46c6f3b8\n"));
	basicTestCases.push_back(TestParam("cat test_ssl/test_files/rich_poor_chapt1.txt | ./ft_ssl sha384 -r", "a6607591ecadc7cc677d40e714b78956a10e7c75ce9077d5b8f4c61b6d9a7154f460d905c9790ca8113835900bd3bb34\n"));
	basicTestCases.push_back(TestParam("cat test_ssl/test_files/rich_poor_chapt1.txt | ./ft_ssl sha384 -rq", "a6607591ecadc7cc677d40e714b78956a10e7c75ce9077d5b8f4c61b6d9a7154f460d905c9790ca8113835900bd3bb34\n"));
	/*
	**	sha512
	*/
	basicTestCases.push_back(TestParam("./ft_ssl sha512 -r test_ssl/test_files/112len.txt", "8e959b75dae313da8cf4f72814fc143f8f7779c6eb9f7fa17299aeadb6889018501d289e4900f7e4331b99dec4b5433ac7d329eeb6dd26545e96e55b874be909 *test_ssl/test_files/112len.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha512 -shellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll -s world",\
	"SHA512 (\"hellllllllllllllllllloshellllllllllllllllllloshellllllllllllllll\") = 6ac2cd94fd9b7ec954361da63e40614e41f800370bc3ef7030cdc4523214924e79f804b6b3e3c585c88b80901dcc6ee0ef953f7b71efe357e66f5989e53fa32d\n\
SHA512 (\"world\") = 11853df40f4b2b919d3815f64792e58d08663767a494bcbb38c0b2389d9140bbb170281b4a847be7757bde12c9cd0054ce3652d0ad3a1a0c92babb69798246ee\n"));
	/* flags */
	basicTestCases.push_back(TestParam("./ft_ssl sha512 -r test_ssl/test_files/56.txt", "2c834fcf7d05e01b9286202cd8cb011518a832ddc8e4f0f9c11cd9f0df554d7bb70468d16e332b04f9017fed9d8778a75294e0e8c7fdeab623ea240bd38ea95f *test_ssl/test_files/56.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha512 -r test_ssl/test_files/67.txt", "597fd9e01e05e0b6d3c84d9bf4c29bb73fdb0a2312e623101d473a1fb3fd51cc2f96441ce05987d31b7154beb32f18fc0e3cc51fa02c8b0f9ea4547a62b212dd *test_ssl/test_files/67.txt\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha512 -rq test_ssl/test_files/br.txt", "98ba486a3b6cfad53bbb2920c4426e21eb7889fc73d5866cc2498e773a3721052bbdf33f961914d7b4f552e084b31535e81bf44ace61df8b3bff6b7371232a2b\n"));
	basicTestCases.push_back(TestParam("./ft_ssl sha512 -qr test_ssl/test_files/chmod000", "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e\n"));
	/* stdin */
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha512 -r test_ssl/test_files/f1.txt", "e5d9b02d3aad1a53fa499f7bb9d995c035195aad8b246a2d62f39b0945c527c847ca9be467df38f290e89909741ebe1c63e688e390762e27756d72f17e6dc1e9 *test_ssl/test_files/f1.txt\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha512", "e7c22b994c59d9cf2b48e549b1e24666636045930d3da7c1acb299d1c3b7f931f94aae41edda2c2b207a36e10f8bcb8d45223e54878f5b316e7ce3b6bc019629\n"));
	basicTestCases.push_back(TestParam("echo \"hello\" | ./ft_ssl sha512 -r", "e7c22b994c59d9cf2b48e549b1e24666636045930d3da7c1acb299d1c3b7f931f94aae41edda2c2b207a36e10f8bcb8d45223e54878f5b316e7ce3b6bc019629\n"));
	basicTestCases.push_back(TestParam("echo \"h\" | ./ft_ssl sha512 -r", "d144eab783229d18de6282e07c4c5ee69032fc9562f577dcdc079fa70a5efc8cd6a6731abaafeabf0b0a7248f6c9723a6be0a08a1bf0baabee3eee63dc52295a\n"));
	basicTestCases.push_back(TestParam("cat test_ssl/test_files/rich_poor_chapt1.txt | ./ft_ssl sha512 -r", "399fb16553f8ef414884e3c1cc468936ebecef6cfb595bc9585b6818c5100fedc1e78b8bb3c0063ff8e337474e1c4c02e9f97a52c24547ff0ee77a6eb6ae2e70\n"));
	basicTestCases.push_back(TestParam("cat test_ssl/test_files/rich_poor_chapt1.txt | ./ft_ssl sha512 -rq", "399fb16553f8ef414884e3c1cc468936ebecef6cfb595bc9585b6818c5100fedc1e78b8bb3c0063ff8e337474e1c4c02e9f97a52c24547ff0ee77a6eb6ae2e70\n"));
}

void
UnitTest::InitLongTermCases()
{
	/*
	**	md5
	*/
	longTermTestCases.push_back(TestParam("./ft_ssl md5 test_ssl/test_files/Xsizefile", "MD5 (test_ssl/test_files/Xsizefile) = 8e6e18dfb1e22d75bafc597f06cf202a\n"));
	/*
	**	sha256
	*/
	longTermTestCases.push_back(TestParam("./ft_ssl sha256 test_ssl/test_files/Xsizefile", "SHA256 (test_ssl/test_files/Xsizefile) = 5bb0f523f99f93fa91559393216a6ffa499ac76ea95f6b3550d43fa80f4dfe0f\n"));
	/*
	**	sha224
	*/
	longTermTestCases.push_back(TestParam("./ft_ssl sha224 test_ssl/test_files/Xsizefile", "SHA224 (test_ssl/test_files/Xsizefile) = 3d8a65e4e753c86da623627e2fefa69e152b63f141e1794d083f5fea\n"));
	/*
	**	sha384
	*/
	longTermTestCases.push_back(TestParam("./ft_ssl sha384 test_ssl/test_files/Xsizefile", "SHA384 (test_ssl/test_files/Xsizefile) = 33b5dbc2d9c65ad62022b235f23fe30a70ae313417837cb381f9578385f88356535c3e0ae67aa1bb2c0fa5e392007a42\n"));
	/*
	**	sha512
	*/
	longTermTestCases.push_back(TestParam("./ft_ssl sha512 test_ssl/test_files/Xsizefile", "SHA512 (test_ssl/test_files/Xsizefile) = 0b52ee6ffebf8e3751355111656ddf1744931453fdaad4b1c881a9554170f321a7558da09169ae240ad1617821237890e6cd8de1f563b04ef6815ad019327024\n"));
}