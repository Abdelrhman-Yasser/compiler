/*
 * KeyWordRule.cpp
 * Created on: Mar 17, 2018
 * Author: Amr Hendy
 */

#include "../../../header/LexcialAnalyzer/RuleExtractor/KeyWordRule.h"
#include <sstream>

KeyWordRule::KeyWordRule()
{
    // TODO Auto-generated constructor stub

}

KeyWordRule::~KeyWordRule()
{
    // TODO Auto-generated destructor stub
}

// we send the string including {}
void KeyWordRule::appendkeyWords(string rule)
{
    string rule_str = rule.substr(1, rule.length() - 2);
    stringstream ss(rule_str);
    string keyWord;
    while(ss >> keyWord)
    {
        keyWords.push_back({keyWord,1});
    }
}
