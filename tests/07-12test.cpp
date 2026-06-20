#include<gtest/gtest.h>
#include<nlohmann/json.hpp>
#include<string>

using json = nlohmann::json;

// C07: operator[] 新增或修改字段
TEST(JsonModifyTest, C07_OperatorBracket) {
    json j = {{"id", 1}};
    j["name"] = "Bob";      // 新增字段
    j["id"] = 2;            // 修改字段
    EXPECT_EQ(j["name"], "Bob");
    EXPECT_EQ(j["id"], 2);
}

// C08: value() 不存在字段时返回默认值
TEST(JsonAccessTest, C08_ValueDefault) {
    json j = {{"id", 1}};
    EXPECT_EQ(j.value("id", 0), 1);            // 存在字段返回实际值
    EXPECT_EQ(j.value("price", -1), -1);        // 不存在字段返回默认值
    EXPECT_EQ(j.value("name", "unknown"), "unknown");
}

// C09: push_back() 向数组追加元素
TEST(JsonArrayTest, C09_PushBack) {
    json arr = json::array();
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back("three");
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], "three");
}

// C10: erase() 删除对象字段或数组元素
TEST(JsonModifyTest, C10_Erase) {
    // 删除对象字段
    json obj = {{"id", 1}, {"name", "Alice"}, {"age", 20}};
    EXPECT_EQ(obj.size(), 3);
    obj.erase("name");
    EXPECT_EQ(obj.size(), 2);
    EXPECT_FALSE(obj.contains("name"));

    // 删除数组元素
    json arr = json::array({10, 20, 30, 40});
    arr.erase(1);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
    EXPECT_EQ(arr[2], 40);
}

// C11: size() 返回对象/数组元素数量
TEST(JsonQueryTest, C11_Size) {
    json obj = {{"a", 1}, {"b", 2}, {"c", 3}};
    EXPECT_EQ(obj.size(), 3);

    json arr = json::array({1, 2});
    EXPECT_EQ(arr.size(), 2);
}

// C12: empty() 判断对象/数组是否为空
TEST(JsonQueryTest, C12_Empty) {
    json empty_obj = json::object();
    json obj = {{"id", 1}};
    EXPECT_TRUE(empty_obj.empty());
    EXPECT_FALSE(obj.empty());

    json empty_arr = json::array();
    json arr = json::array({1, 2});
    EXPECT_TRUE(empty_arr.empty());
    EXPECT_FALSE(arr.empty());
}
