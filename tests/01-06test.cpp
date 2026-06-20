#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include <string>
#include <vector>
#include <set>

using json = nlohmann::json;

// =======================
// 组长：C01-C06
// =======================

TEST(JsonParseTest, C01_ParseValidJsonObject) {
    std::string text = R"({"name":"Tom","age":20})";

    json j = json::parse(text);

    EXPECT_EQ(j["name"], "Tom");
    EXPECT_EQ(j["age"], 20);
}

TEST(JsonParseTest, C02_ParseInvalidJsonThrows) {
    std::string text = R"({"name":"Tom",)";

    EXPECT_THROW(json::parse(text), json::parse_error);
}

TEST(JsonDumpTest, C03_DumpCompactJsonString) {
    json j = {
        {"id", 1},
        {"title", "book"}
    };

    std::string result = j.dump();

    EXPECT_NE(result.find("\"id\":1"), std::string::npos);
    EXPECT_NE(result.find("\"title\":\"book\""), std::string::npos);
}

TEST(JsonDumpTest, C04_DumpFormattedJsonString) {
    json j = {
        {"name", "Tom"},
        {"age", 20}
    };

    std::string result = j.dump(4);

    EXPECT_NE(result.find("\n"), std::string::npos);
    EXPECT_NE(result.find("    "), std::string::npos);
}

TEST(JsonObjectTest, C05_ContainsExistingField) {
    json j = {
        {"id", 1},
        {"name", "Tom"}
    };

    EXPECT_TRUE(j.contains("id"));
    EXPECT_TRUE(j.contains("name"));
}

TEST(JsonObjectTest, C06_AtExistingField) {
    json j = {
        {"id", 1},
        {"name", "Tom"}
    };

    EXPECT_EQ(j.at("id"), 1);
    EXPECT_EQ(j.at("name"), "Tom");
}

// =======================
// 组员1：C07-C12
// =======================

TEST(JsonObjectTest, C07_AtMissingFieldThrows) {
    json j = {
        {"id", 1}
    };

    EXPECT_THROW(j.at("price"), json::out_of_range);
}

TEST(JsonObjectTest, C08_OperatorBracketAddField) {
    json j = {
        {"id", 1}
    };

    j["name"] = "Tom";

    EXPECT_TRUE(j.contains("name"));
    EXPECT_EQ(j["name"], "Tom");
}

TEST(JsonObjectTest, C09_OperatorBracketModifyField) {
    json j = {
        {"id", 1},
        {"name", "Tom"}
    };

    j["name"] = "Jerry";

    EXPECT_EQ(j["name"], "Jerry");
}

TEST(JsonObjectTest, C10_ValueMissingFieldReturnsDefaultValue) {
    json j = {
        {"id", 1}
    };

    std::string name = j.value("name", "unknown");

    EXPECT_EQ(name, "unknown");
}

TEST(JsonObjectTest, C11_EraseObjectField) {
    json j = {
        {"id", 1},
        {"name", "Tom"}
    };

    j.erase("name");

    EXPECT_FALSE(j.contains("name"));
    EXPECT_TRUE(j.contains("id"));
}

TEST(JsonObjectTest, C12_SizeOfObject) {
    json j = {
        {"id", 1},
        {"name", "Tom"},
        {"age", 20}
    };

    EXPECT_EQ(j.size(), 3);
}

// =======================
// 组员2：C13-C18
// =======================

TEST(JsonTypeTest, C13_IsObject) {
    json j = {
        {"id", 1}
    };

    EXPECT_TRUE(j.is_object());
}

TEST(JsonTypeTest, C14_IsArray) {
    json j = json::array({1, 2, 3});

    EXPECT_TRUE(j.is_array());
}

TEST(JsonTypeTest, C15_IsString) {
    json j = "hello";

    EXPECT_TRUE(j.is_string());
}

TEST(JsonTypeTest, C16_IsNumber) {
    json j = 100;

    EXPECT_TRUE(j.is_number());
}

TEST(JsonTypeTest, C17_IsBoolean) {
    json j = true;

    EXPECT_TRUE(j.is_boolean());
}

TEST(JsonTypeTest, C18_IsNull) {
    json j = nullptr;

    EXPECT_TRUE(j.is_null());
}

// =======================
// 组员3：C19-C24
// =======================

TEST(JsonArrayTest, C19_PushBackArrayElement) {
    json arr = json::array();

    arr.push_back(1);
    arr.push_back(2);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(JsonArrayTest, C20_EmptyArray) {
    json arr = json::array();

    EXPECT_TRUE(arr.empty());

    arr.push_back("data");

    EXPECT_FALSE(arr.empty());
}

TEST(JsonPointerTest, C21_AccessNestedFieldByJsonPointer) {
    json j = R"({
        "user": {
            "profile": {
                "name": "Alice"
            }
        }
    })"_json;

    json::json_pointer ptr("/user/profile/name");

    EXPECT_EQ(j[ptr], "Alice");
}

TEST(JsonConversionTest, C22_GetCppTypeFromJsonValue) {
    json j = {
        {"id", 100},
        {"name", "Tom"},
        {"scores", {90, 95, 88}}
    };

    int id = j["id"].get<int>();
    std::string name = j["name"].get<std::string>();
    std::vector<int> scores = j["scores"].get<std::vector<int>>();

    EXPECT_EQ(id, 100);
    EXPECT_EQ(name, "Tom");
    EXPECT_EQ(scores.size(), 3);
    EXPECT_EQ(scores[1], 95);
}

TEST(JsonIteratorTest, C23_IterateObjectItems) {
    json j = {
        {"id", 1},
        {"name", "Tom"},
        {"age", 20}
    };

    std::set<std::string> keys;

    for (const auto& item : j.items()) {
        keys.insert(item.key());
    }

    EXPECT_TRUE(keys.contains("id"));
    EXPECT_TRUE(keys.contains("name"));
    EXPECT_TRUE(keys.contains("age"));
}

TEST(JsonPatchTest, C24_JsonPatchAndMergePatch) {
    json j = R"({
        "name": "Tom",
        "age": 20,
        "city": "Shenyang"
    })"_json;

    json patch = R"([
        {"op": "replace", "path": "/age", "value": 21},
        {"op": "remove", "path": "/city"},
        {"op": "add", "path": "/grade", "value": "A"}
    ])"_json;

    json patched = j.patch(patch);

    EXPECT_EQ(patched["name"], "Tom");
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
