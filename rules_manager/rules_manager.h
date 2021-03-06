#ifndef RULES_MANAGER_H
#define RULES_MANAGER_H

#include "symbol_container.h"
#include "err_unknown_symbol.h"

#ifndef ITERATOR_H
#define ITERATOR_H
#include <iterator>
#endif /* end of include guard: ITERATOR_H */


#ifndef LIST_H
#define LIST_H
#include <list>
#endif /* end of include guard: LIST_H */

#ifndef STRING_H
#define STRING_H
#include <string>
#endif /* end of include guard: STRING_H */

#ifndef REGEX_H
#define REGEX_H
#include <regex>
#endif /* end of include guard: REGEX_H */

#ifndef MAP_H
#define MAP_H
#include <map>
#endif /* end of include guard: MAP_H */

#include "original_rule.h"

class Rules_Manager {
protected:

    struct Rule;
    struct Regex_Pair;
private:

    std::list<Regex_Pair> get_pairs(
        const std::string& string_in,
        const std::string& string_out );
    void form_serials(
        const std::string&              string_in,
        std::map<char, std::list<int>>& serials_to_form );
    void form_serials_combs(
        const std::map<char, std::list<int>>& serials,
        std::list<std::map<char, int>>& combs_to_form,
        std::map<char, int>& temp_container,
        unsigned iter_from_begin = 1 );
    void validate_rule( const std::string& in ) throw(Err_Unknown_Symbol);
    std::string markup_expr( const std::string& string_in );
    std::string markup_expr(
        const std::string& string_in,
        const std::map<char, int>& var_serials );
    std::string format_serial( int serial );
    std::string format_spec_char( char symb );

    Rules_Manager();

    const Symbol_Container& m_symbols;
    const Symbol_Container& m_variables;
    const Symbol_Container& m_axioms;
    Symbol_Container        m_spec_chars;
    std::list<Rule>         m_rules;
    std::string             m_any_symbols;
    std::string             m_any_axioms;

public:
    void push_rule( const std::string& rule_in, const std::string& rule_out );
    void push_rule( const Original_Rule& original_rule );
    bool execute( std::string& input, Original_Rule& used_rule );
    bool execute( std::string& input );
    Rules_Manager(
        const Symbol_Container& symbols,
        const Symbol_Container& variables,
        const Symbol_Container& axioms );
};


// ----------------------------
struct Rules_Manager::Rule {
    Original_Rule                        original_rule;
    std::string                          regex_marked_up;
    std::list<Rules_Manager::Regex_Pair> regex_pairs;
    const Rule operator=( const Rule& rule );
    Rule();
    Rule( const Rule& rule );
    Rule(
        const std::string& regex_marked_up,
        const std::list<Rules_Manager::Regex_Pair>& regex_pairs,
        const Original_Rule& original_rule );
};
// ----------------------------
struct Rules_Manager::Regex_Pair {
    std::string regex_in;
    std::string regex_out;
    const Regex_Pair operator=( const Regex_Pair& regex_pair );
    Regex_Pair();
    Regex_Pair(
        const std::string& regex_in,
        const std::string& regex_out );
};

#endif /* end of include guard: RULES_MANAGER_H */
