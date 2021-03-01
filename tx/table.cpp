#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <functional>
using namespace std;

struct kv {
    string key;
    string value;
};

void ifelse(vector<kv> &conf) {
    bool add_top_weight;
    bool add_newhot_weight;
    bool is_create_time_surpress;
    int create_time_surpress_day;

    for (int i=0; i<conf.size(); i++) {
        if (conf[i].key == "add_top_weight") {
            if (conf[i].value == "enable") {
                add_top_weight = true;                            
            }
        } else if (conf[i].key == "add_newhot_weight") {
            if (conf[i].value == "enable") {                
                add_newhot_weight = true;                       
            }
        }  
        else if(conf[i].key == "create_time_surpress") {         
            if (conf[i].value == "enable") 
                is_create_time_surpress = true;                          
        }                      
        else if(conf[i].key == "create_time_surpress_day") {
            create_time_surpress_day = atoi(conf[i].value.c_str());
        }                                                       

    }

    cout << "add_top_weight: " << add_top_weight << endl
        << "add_newhot_weight: " << add_newhot_weight << endl
        << "is_create_time_surpress: " << is_create_time_surpress << endl
        << "create_time_surpress_day: " << create_time_surpress_day << endl;
}

template <class T>
void parseValue(const string& value, T &t) {
    return ;
}

template <>
void parseValue(const string& value, string& str) {
    str = value;
    return ;
}

template <>
void parseValue(const string& value, int& i) {
    i = atoi(value.c_str());
    return ;
}

template <>
void parseValue(const string& value, bool& b) {
    b = false;
    if (value == "enable") {
        b = true;
    }
    return ;
}

template <class T>
struct dealValue {
    void* func_;
    T& t_;
    dealValue(void* f, T& t): func_(f), t_(t){}
};

struct st {
    bool add_top_weight;
    bool add_newhot_weight;
    bool is_create_time_surpress;
    int create_time_surpress_day;
};


class Value {
public:
    virtual void parse(std::string& value) = 0;
};

class BoolValue : public Value{
public:
    BoolValue(bool& b) : value_(b){}
    virtual void parse(std::string& value) {
        value_ = false;
        if (value == "enable") {
            value_ = true;
        }
    }

    bool &value_;
};

class StringValue : public Value{
public:
    StringValue(string& str) : value_(str) {}
    virtual void parse(std::string& value) {
        value_ = value;
    }
    std::string &value_;
};

class IntValue : public Value{
public:
    IntValue(int& i) : value_(i) {}
    virtual void parse(std::string& value) {
        value_ = atoi(value.c_str());
    }
    int &value_;
};

void table(vector<kv> &conf) {
    bool add_top_weight;
    bool add_newhot_weight;
    bool is_create_time_surpress;
    int create_time_surpress_day;

    map<string, Value*> table = {
        {"add_top_weight", &BoolValue(add_top_weight)},
        {"add_newhot_weight", &BoolValue(add_newhot_weight)},
        {"create_time_surpress", &BoolValue(is_create_time_surpress)},
        {"create_time_surpress_day", &IntValue(create_time_surpress_day)},
    };

    for (int i=0; i<conf.size(); i++) {
        auto it = table.find(conf[i].key);
        if (it == table.end()) {
            continue;
        }
        it->second->parse(conf[i].value);
    }
    cout << "add_top_weight: " << add_top_weight << endl
        << "add_newhot_weight: " << add_newhot_weight << endl
        << "is_create_time_surpress: " << is_create_time_surpress << endl
        << "create_time_surpress_day: " << create_time_surpress_day << endl;
}

auto main() -> int {
    vector<kv> confs = {
        kv{.key="add_top_weight", .value="enable"},
        kv{.key="add_newhot_weight", .value="enable"},
        kv{.key="create_time_surpress", .value="enable"},
        kv{.key="create_time_surpress_day", .value="111111"}
    };

//    ifelse(confs);
    table(confs);
}

