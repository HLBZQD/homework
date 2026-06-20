#include<gtest/gtest.h>
#include<nlohmann/json.hpp>
#include<string>

using json =nlohmann::json;

/*C01*/
TEST(JsonParseTest,C01_ParseValidJsonObject){
    std::string text=R"({"name":"Tom","age":"20"})";
    json j=json::parse(text);
    EXPECT_EQ(j["name"],"Tom");
    EXPECT_EQ(j["age"],"20");
}
/*C02*/
TEST(JsonParseTest,C02_ParseInvalidJsonThrows){
    std::string text=R"({"name":"Tom",)";
    EXPECT_THROW(json::parse(text), json::parse_error);
}
/*C03*/
TEST(JsonDumpTest,C03_DumoCompactJsonString){
    json j={{"id",1},{"title","book"}};
    std::string result=j.dump();
    EXPECT_NE(result.find("\"id\":1"),std::string::npos);
    EXPECT_NE(result.find("\"title\":\"book\""),std::string::npos);
}
/*C04*/
TEST(JsonDumpTest,C04_DumpFormattedJsonString){
    json j={{"name","Tom"},{"age",20}};
    std::string result=j.dump(4);
    EXPECT_NE(result.find("\n"),std::string::npos);
    EXPECT_NE(result.find("    "),std::string::npos);
}
/*C05*/
TEST(JsonObjectTest,C05_ContainsExistingField){
    json j={{"id",1},{"name","Tom"}};
    EXPECT_TRUE(j.contains("id"));
    EXPECT_TRUE(j.contains("name"));
}
/*C06*/
TEST(JsonObjectTest,C06_AtExistingField){
    json j={{"id",1},{"name","Tom"}};
    EXPECT_EQ(j.at("id"),1);
    EXPECT_EQ(j.at("name"),"Tom");
}
