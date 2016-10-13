#include "json/json.h"
#include <string>
#include <iostream>

using namespace std;

int test_null_in_str()
{
    char lszBuff[] = "Test123";
    lszBuff[2] = 0;
    std::string str(lszBuff, 5);
    cout << str << endl;
    Json::Value loMsg;
    loMsg["test1"] = Json::Value(lszBuff, lszBuff+5);
    loMsg["test2"] = Json::Value(str);

    Json::FastWriter writer;
    std::cout << writer.write(loMsg) << std::endl;

    return 0;
}

int main()
{
    string test ="{\"20\": 1,\"40\":\"kurama\"}";
    Json::Reader reader;
    Json::Value value;

    if (reader.parse(test, value))
    {
        if (!value["ids"].isNull())
        {
            cout<<value["id"].asInt()<<endl;
            cout<<value["name"].asString()<<endl;
        }
    }

    Json::Value root;
    Json::Value arrayObj;
    Json::Value item;

    for (int i = 0; i < 2; i ++)
    {
        item["key"] = i;
        item["value"] = i;
        arrayObj.append(item);
    }

    //root["key1"] = "key1";
    //root["key1"] = "";
    //root["key2"] = "value2";
    //root["array"] = arrayObj;
    /*
       std::cout << root << std::endl;
       std::cout << "***************************" << std::endl;

       std::string out = root.toStyledString();
       std::cout << "***************************" << std::endl;
       std::cout << out << std::endl;
     */
    Json::FastWriter writer;
    std::cout << writer.write(arrayObj) << std::endl;
//    root.removeMember("key1");
//    std::cout << writer.write(root) << std::endl;


 //   cout << endl << endl;
//    test_null_in_str();
    return 0;
}
