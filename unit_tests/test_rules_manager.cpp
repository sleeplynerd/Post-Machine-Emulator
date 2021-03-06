#include "gtest/gtest.h"
#include <iostream>

#include "rules_manager.h"
using namespace std;

#define INIT__() \
    Symbol_Container symbols("D:/TemporaryFiles/Post-Machine-Emulator/unit_tests/input_files/SYMBOLS"); \
    Symbol_Container variables("D:/TemporaryFiles/Post-Machine-Emulator/unit_tests/input_files/VARIABLES"); \
    Symbol_Container axioms("D:/TemporaryFiles/Post-Machine-Emulator/unit_tests/input_files/AXIOMS"); \
    Rules_Manager    mgr(symbols, variables, axioms);

TEST( format_spec_char, _ ) {
    INIT__();
    std::string to_compare("\\+");
    EXPECT_EQ(0, mgr.format_spec_char('+').compare(to_compare));
}

TEST( format_serial, _ ) {
    INIT__();
    std::string to_compare("$4");
    EXPECT_EQ(0, mgr.format_serial(4).compare(to_compare));
}

TEST( markup_expr, ONE_PARAMETER ) {
    INIT__();
    std::string to_markup("111xy+=x");
    std::string to_compare("[1*+=]*111([1]*)([1]*)\\+=([1]*)[1*+=]*");
    std::string result(mgr.markup_expr(to_markup));
    std::cout << "RESULT__:" << result << std::endl;
    EXPECT_EQ(0, result.compare(to_compare));
}

TEST( form_serials, _ ) {
    INIT__();
    std::string string_in("111x=x");
    std::map<char, std::list<int>> serials_to_form;
    mgr.form_serials(string_in, serials_to_form);
    for (auto it = serials_to_form['x'].begin(); it != serials_to_form['x'].end(); ++it )
        std::cout << *it << std::endl;
    EXPECT_TRUE(serials_to_form['x'].front() == 1 && serials_to_form['x'].back() == 2);
}

TEST( form_serials_combs, _ ) {
    INIT__();
    map<char, list<int>> serials;
    list<map<char,int>>  combs_to_form;
    string               string_in("111x1y=x+y");
    bool                 flag = true;

    mgr.form_serials(string_in, serials);
    for (auto it = serials.begin()->second.begin(); it != serials.begin()->second.end(); ++it) {
        map<char, int> container;
        container.emplace(serials.begin()->first, *it);
        mgr.form_serials_combs(serials, combs_to_form, container);
    }

    cout << "RESULT__: X IS EITHER 1 OR 3, Y IS EITHER 2 OR 4" << endl;
    for (auto combs_iter = combs_to_form.begin(); combs_iter != combs_to_form.end(); ++combs_iter) {
        for (auto map_iter = combs_iter->begin(); map_iter != combs_iter->end(); ++map_iter) {
            // Logical implication: a->b == !a||b
            flag *= (!(map_iter->first=='x') || (map_iter->second==1 || map_iter->second==3));
            flag *= (!(map_iter->first=='y') || (map_iter->second==2 || map_iter->second==4));
            cout << map_iter->first << "   " << map_iter->second << "  |  ";
        }
        cout << endl;
    }
    EXPECT_TRUE(flag);
}

TEST( markup_expr, TWO_PARAMETERS ) {
    INIT__();
    string string_in("xstring_yinx");
    map<char,int> var_serials;
    string string_in_mkup;

    var_serials.emplace('x',2);
    var_serials.emplace('y',1);
    string_in_mkup.assign(mgr.markup_expr(string_in, var_serials));

    cout << "RESULT_:" << string_in_mkup << endl;
    EXPECT_EQ(0, string_in_mkup.compare("$2string_$1in$2"));
}

TEST( get_pairs, _ ) {
    INIT__();
    string rule_in("+y=");
    string rule_out("=y");
    list<Rules_Manager::Regex_Pair> regpairs = mgr.get_pairs(rule_in, rule_out);
    EXPECT_TRUE(
        regpairs.front().regex_in.compare("+$1=") == 0 &&
        regpairs.front().regex_out.compare("=$1") == 0
    );
}

TEST( execute, Executable ) {
    INIT__();
    string rule_in("+y=");
    string rule_out("=y");
    string to_exec("1111*1111+111=");

    mgr.push_rule(rule_in, rule_out);
    EXPECT_TRUE(mgr.execute(to_exec) && to_exec.compare("1111*1111=111")==0);
    cout << to_exec << endl;
}

TEST( execute, Executable_2 ) {
    INIT__();
    string to_exec("1111*1111+111=");

    mgr.push_rule(string("+y="), string("=y"));
    mgr.push_rule(string("1*x=y"), string("*x=yx"));
    mgr.execute(to_exec);
    mgr.execute(to_exec);
    EXPECT_TRUE(to_exec.compare("111*1111=1111111")==0);
    cout << to_exec << endl;
}

TEST( execute, Non_executable ) {
    INIT__();
    string to_exec("*1111=");

    mgr.push_rule(string("+y="), string("=y"));
    mgr.push_rule(string("1*x=y"), string("*x=yx"));
    EXPECT_FALSE(mgr.execute(to_exec));
}
