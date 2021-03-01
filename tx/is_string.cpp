#include <iostream>
#include <string>

bool is_string_literal(const std::string& str) {
    if (str.empty() && str[0] != '"') {
        return false;
    }

    bool has_prefix = true;
    for (auto i=1; i<str.size(); i++) {
        if (str[i] != '"' || ('"' == str[i] && '\'' == str[i-1])) {
            continue;
        }
        has_prefix = !has_prefix;
    }

    return !has_prefix;
}

int main(int argc, char** argv)
{
    std::cout << std::boolalpha << is_string_literal("\"Hello world\"") << std::endl;
    std::cout << is_string_literal("\"Hello\"\" world\"") << std::endl;
    std::cout << is_string_literal("\"Hello world") << std::endl;
    std::cout << is_string_literal("\"Hello\" world\"") << std::endl;
    std::cout << is_string_literal("Hello\" world\"") << std::endl;
    std::cout << is_string_literal("Hello world\"") << std::endl;

    std::cout << is_string_literal(argv[1]) << std::endl;

    return 0;
}

