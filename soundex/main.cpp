// soundex.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

#include "gmock/gmock.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleMock(&argc, argv);
	auto res = RUN_ALL_TESTS();
	getchar();
    return res;
}
