#ifndef CFG_TERMINALSSET_H
#define CFG_TERMINALSSET_H

#include <vector>
#include <set>
#include "GrammarSymbol.h"

class Terminals {
    std::vector<GrammarSymbol> terminals;

public:
    const Terminals& operator = (const Terminals& other);
    const Terminals operator + (const Terminals& other) const;
    const Terminals& operator += (const Terminals& other);
    const Terminals& operator += (const GrammarSymbol& other);
    bool operator < (const Terminals& other) const;
    bool operator == (const Terminals& other) const;

    Terminals(const Terminals& other) : terminals(other.terminals) {}
    Terminals(const std::vector<GrammarSymbol>& content) : terminals(content) {}
    Terminals(const GrammarSymbol& symbol) { this->terminals.push_back(symbol); }
    Terminals() {}

    std::string ToString() const;
    bool Empty() const { return terminals.empty(); }
    int Size() const { return terminals.size(); }
    const GrammarSymbol Front() const { return terminals.front(); }
    void PopFront() { terminals.erase(terminals.begin()); }
    Terminals Prefix (int length);
    void Trim(int length);
    std::vector<GrammarSymbol> AsVector() { return terminals; }
};

class TerminalsSet {
    std::set<Terminals> terminalsSet;

public:
    bool operator == (const TerminalsSet& other) const;
    const TerminalsSet& operator = (const TerminalsSet& other);
    const TerminalsSet operator + (const TerminalsSet& other) const;
    const TerminalsSet operator - (const TerminalsSet& other) const;
    TerminalsSet operator * (const TerminalsSet& other) const;
    const TerminalsSet& operator += (const TerminalsSet& other);
    bool Contains (const Terminals& item) const;
    const std::set<Terminals>& GetTerminalsSet() const { return terminalsSet; }
    const TerminalsSet Trim(const int length);

    TerminalsSet() : terminalsSet() {};
    explicit TerminalsSet(const std::set<Terminals>& content) : terminalsSet(content) {}
    TerminalsSet(const Terminals& terminals) { terminalsSet.insert(terminals); }
    TerminalsSet(const TerminalsSet& other) = default;

    std::string ToString() const;
};

std::ostream& operator << (std::ostream& out, const Terminals& to_print);
std::ostream& operator << (std::ostream& out, const TerminalsSet& to_print);

const Terminals Epsilon = Terminals();

#endif //CFG_TERMINALSSET_H
