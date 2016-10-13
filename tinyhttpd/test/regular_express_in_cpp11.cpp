#include <iostream>
#include <iterator>
#include <string>
#include <regex>

int example()
{
    std::string s = "Some people, when confronted with a problem, think "
        "\"I know, I'll use regular expressions.\" "
        "Now they have two problems.";

    std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::ECMAScript | std::regex_constants::icase);
    if (std::regex_search(s, self_regex)) {
        std::cout << "Text contains the phrase 'regular expressions'\n";
    }

    std::regex word_regex("(\\S+)");
    auto words_begin = 
        std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Found "
        << std::distance(words_begin, words_end)
        << " words\n";

    const int N = 6;
    std::cout << "Words longer than " << N << " characters:\n";
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (match_str.size() > N) {
            std::cout << "  " << match_str << '\n';
        }
    }

    std::regex long_word_regex("(\\w{7,})");
    std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
    std::cout << new_s << '\n';
}

int study()
{
    std::string str = "users/11231244213/relationships";
    std::regex self_regex("users/[0-9]+/relationships", std::regex_constants::ECMAScript | std::regex_constants::icase);
    if (std::regex_search(str, self_regex)) {
        std::cout << " text dont contains \"test\"\n" ;
    }

    // std::regex words_regex("\d+");
    // auto words_begin
}

int main()
{

    study();
    return 0;
}
