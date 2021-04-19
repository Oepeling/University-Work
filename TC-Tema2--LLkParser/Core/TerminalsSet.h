#ifndef CFG_TERMINALSSET_H
#define CFG_TERMINALSSET_H

#include <vector>
#include <set>
#include "GrammarSymbol.h"

class Terminals {
    std::vector<GrammarSymbol> terminals;

public:
    const Terminals operator + (const Terminals& other) const;
    bool operator < (const Terminals& other) const;
    bool operator == (const Terminals& other) const {
        return !(((*this) < other) || (other < (*this)));
    }
    [[nodiscard]] const Terminals Prefix (int length) const;

    Terminals(const Terminals& other) : terminals(other.terminals) {}
    Terminals(const std::vector<GrammarSymbol>& content) : terminals(content) {}
    Terminals(const GrammarSymbol& symbol) { this->terminals.push_back(symbol); }
    Terminals() {}
};

class TerminalsSet {
    std::set<Terminals> terminalsSet;

public:
    bool operator == (const TerminalsSet& other) const;
    const TerminalsSet& operator = (const TerminalsSet& other);
    const TerminalsSet operator + (const TerminalsSet& other) const;
    const TerminalsSet operator - (const TerminalsSet& other) const;
    const TerminalsSet operator * (const TerminalsSet& other) const;
    const TerminalsSet& operator += (const TerminalsSet& other);
    bool Contains (const Terminals& item) const;
    const std::set<Terminals>& GetTerminalsSet() const { return terminalsSet; }

    TerminalsSet() : terminalsSet() {};
    explicit TerminalsSet(const std::set<Terminals>& content) : terminalsSet(content) {}
    TerminalsSet(const Terminals& terminals) { terminalsSet.insert(terminals); }
    TerminalsSet(const TerminalsSet& other) = default;
};


#endif //CFG_TERMINALSSET_H
