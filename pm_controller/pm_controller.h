#ifndef PM_CONTROLLER_H
#define PM_CONTROLLER_H

#include "pm_record.h"
#include "rules_manager.h"
#include "symbol_container.h"
#include "err_unknown_symbol.h"

class Pm_Controller {
private:

    void erase_journal();
    Symbol_Container     m_symbols;
    Symbol_Container     m_variables;
    Symbol_Container     m_axioms;
    Rules_Manager        m_rules_manager;
    std::list<Pm_Record> m_journal;
public:
    const std::list<Pm_Record>& get_journal();
    const std::list<Pm_Record>& get_journal( const std::string& input );
    const std::list<Pm_Record>& get_journal( const char* file_input );
    Pm_Controller( const char* file_symbols, const char* file_variables,
        const char* file_axioms, const char* file_rules );
    Pm_Controller( const std::string& symbols, const std::string& variables,
        const std::string& axioms, const std::list<Original_Rule>& rules );

};

#endif /* end of include guard: PM_CONTROLLER_H */
