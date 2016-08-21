#include <gtest/gtest.h>

#include "Params.h"

TEST(Params, Basics)
{
    ParamsHolder params;

    const int ARGC = 3;
    const char* argv_data[ARGC] = {"-var", "var2=text", "var3=3"};

    // argv should be mutable
    char** argv = new char*[ARGC];
    for (int i = 0; i < ARGC; ++i)
    {
        int length = strlen(argv_data[i]);
        argv[i] = new char[length];
        strcpy(argv[i], argv_data[i]);
    }

    params.ParseParams(3, argv);
    ASSERT_TRUE(params.GetParamBool("-var"));
    ASSERT_TRUE(params.GetParamBool("var2"));
    ASSERT_TRUE(params.GetParamBool("var3"));
    ASSERT_FALSE(params.GetParamBool("do_not_exist"));

    ASSERT_EQ(params.GetParam<std::string>("-var"), "");
    ASSERT_EQ(params.GetParam<int>("-var"), 0);
    ASSERT_EQ(params.GetParam<std::string>("var2"), "text");
    ASSERT_EQ(params.GetParam<std::string>("var3"), "3");
    ASSERT_EQ(params.GetParam<int>("var3"), 3);
    ASSERT_EQ(params.GetParam<std::string>("donot"), "");
    ASSERT_EQ(params.GetParam<int>("donot"), 0);

    for (int i = 0; i < ARGC; ++i)
    {
        delete[] argv[i];
    }
    delete[] argv;
}
