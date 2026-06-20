#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST(JsonArrayTest, C19)
{
    json j = json::array();

    j.push_back(1);
    j.push_back(2);
    EXPECT_EQ(j.size(), 2);
    EXPECT_EQ(j[0], 1);
    EXPECT_EQ(j[1], 2);
}

TEST(JsonArrayTest, C20)
{
    json j = json::array();
    EXPECT_TRUE(j.empty());
    j.push_back("data");
    EXPECT_FALSE(j.empty());
}

TEST(JsonPointerTest, C21)
{
    json j = R"({
        "user": {
            "profile": {
                "name": "hlb"
            }
        }
    })"_json;
    json::json_pointer ptr("/user/profile/name");
    EXPECT_EQ(j[ptr], "hlb");
}

TEST(JsonConversionTest, C22)
{
    json j = {
        {"id", 100},
        {"name", "hlb"},
        {"scores", {90, 95, 88}}};
    int id = j["id"].get<int>();
    std::string name = j["name"].get<std::string>();
    std::vector<int> scores = j["scores"].get<std::vector<int>>();
    EXPECT_EQ(id, 100);
    EXPECT_EQ(name, "hlb");
    EXPECT_EQ(scores.size(), 3);
    EXPECT_EQ(scores[1], 95);
}

TEST(JsonIteratorTest, C23)
{
    json j = {
        {"id", 1},
        {"name", "hlb"},
        {"age", 20}};
    std::set<std::string> keys;
    for (const auto &item : j.items())
        keys.insert(item.key());
    EXPECT_TRUE(keys.find("id") != keys.end());
    EXPECT_TRUE(keys.find("name") != keys.end());
    EXPECT_TRUE(keys.find("age") != keys.end());
}

// 故意缺陷 5：patch 后 age 实际为 21，这里错误地期望为 20
TEST(JsonPatchTest, C24)
{
    json j = R"({
        "name": "hlb",
        "age": 20,
        "city": "Shenyang"
    })"_json;

    json patch = R"([
        {"op": "replace", "path": "/age", "value": 21},
        {"op": "remove", "path": "/city"},
        {"op": "add", "path": "/grade", "value": "A"}
    ])"_json;

    json patched = j.patch(patch);

    EXPECT_EQ(patched["name"], "hlb");
    EXPECT_EQ(patched["age"], 21);
    EXPECT_FALSE(patched.contains("city"));
    EXPECT_EQ(patched["grade"], "A");

    json mergeTarget = R"({
        "title": "old",
        "author": {
            "name": "Bob",
            "age": 30
        },
        "tags": ["cpp", "json"]
    })"_json;

    json mergePatch = R"({
        "title": "new",
        "author": {
            "age": 31
        },
        "tags": null
    })"_json;

    mergeTarget.merge_patch(mergePatch);

    EXPECT_EQ(mergeTarget["title"], "new");
    EXPECT_EQ(mergeTarget["author"]["name"], "Bob");
    EXPECT_EQ(mergeTarget["author"]["age"], 31);
    EXPECT_FALSE(mergeTarget.contains("tags"));
}