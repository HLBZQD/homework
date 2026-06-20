#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST(JsonTypeTest, C13_IsObject)
{
    json j = {
        {"id", 1}};

    EXPECT_TRUE(j.is_object());
}

TEST(JsonTypeTest, C14_IsArray)
{
    json j = json::array({1, 2, 3});

    EXPECT_TRUE(j.is_array());
}

TEST(JsonTypeTest, C15_IsString)
{
    json j = "hello";

    EXPECT_TRUE(j.is_string());
}

TEST(JsonTypeTest, C16_IsNumber)
{
    json j = 100;

    EXPECT_TRUE(j.is_number());
}

TEST(JsonTypeTest, C17_IsBoolean)
{
    json j = true;

    EXPECT_TRUE(j.is_boolean());
}

TEST(JsonTypeTest, C18_IsNull)
{
    json j = nullptr;

    EXPECT_TRUE(j.is_null());
}