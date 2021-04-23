#include "TerminalsSet.h"
#include "../Utility/VectorUtility.h"

bool TerminalsSet::operator==(const TerminalsSet &other) const {
    return this->terminalsSet == other.terminalsSet;
}

const TerminalsSet TerminalsSet::operator+(const TerminalsSet &other) const {
    TerminalsSet result = (*this);
    result.terminalsSet.insert(other.terminalsSet.begin(), other.terminalsSet.end());
    return result;
}

const TerminalsSet TerminalsSet::operator-(const TerminalsSet &other) const {
    TerminalsSet result = (*this);
    for (auto it : other.terminalsSet) {
        result.terminalsSet.erase(it);
    }
    return result;
}

bool TerminalsSet::Contains(const Terminals &item) const {
    return (this->terminalsSet.find(item) != this->terminalsSet.end());
}

const TerminalsSet& TerminalsSet::operator=(const TerminalsSet &other) {
    this->terminalsSet = other.terminalsSet;
    return other;
}

TerminalsSet TerminalsSet::operator*(const TerminalsSet &other) const {
    TerminalsSet result;
    for (auto a : this->terminalsSet) {
        for (auto b : other.terminalsSet) {
            result.terminalsSet.insert(a + b);
        }
    }
    return result;
}

const TerminalsSet &TerminalsSet::operator+=(const TerminalsSet &other) {
    this->terminalsSet.insert(other.terminalsSet.begin(), other.terminalsSet.end());
    return (*this);
}

std::string TerminalsSet::ToString() const {
    std::string ans = "";
    for (auto it : terminalsSet) {
        ans += (it.ToString() + "\n");
    }
    return ans;
}

const TerminalsSet TerminalsSet::Trim(const int length) {
    std::set<Terminals> newTerminalsSet;
    for (auto it : terminalsSet) {
        newTerminalsSet.insert(it.Prefix(length));
    }
    terminalsSet = newTerminalsSet;
    return (*this);
}

const Terminals Terminals::operator+(const Terminals &other) const {
    Terminals result = (*this);
    VectorMerge(result.terminals, other.terminals);
    return result;
}

Terminals Terminals::Prefix(int length) {
    Terminals result = (*this);
    if (length < result.terminals.size()) {
        result.terminals.resize(length);
    }
    return result;
}

bool Terminals::operator<(const Terminals &other) const {
    if (this->terminals.size() != other.terminals.size()) {
        return (this->terminals.size() < other.terminals.size());
    } else {
        for (int i = 0; i < this->terminals.size(); i++) {
            if (this->terminals[i] != other.terminals[i]) {
                return (this->terminals[i] < other.terminals[i]);
            }
        }
        return false;
    }
}

std::string Terminals::ToString() const {
    std::string ans = "";
    for (auto it : terminals) {
        ans += (it.Value() + " ");
    }
    ans += std::to_string(terminals.size());
    return ans;
}

bool Terminals::operator==(const Terminals &other) const {
    if (this->terminals.size() != other.terminals.size()) {
        return false;
    }
    for (int i = 0; i < this->terminals.size(); i++) {
        if (this->terminals[i] != other.terminals[i]) {
            return false;
        }
    }
    return true;
}

const Terminals& Terminals::operator+=(const Terminals& other) {
    VectorMerge(this->terminals, other.terminals);
    return (*this);
}

const Terminals &Terminals::operator+=(const GrammarSymbol& other) {
    this->terminals.push_back(other);
    return (*this);
}

const Terminals& Terminals::operator=(const Terminals &other) {
    this->terminals = other.terminals;
    return (*this);
}

void Terminals::Trim(int length) {
    if (length < this->terminals.size()) {
        this->terminals.resize(length);
    }
}

std::ostream& operator << (std::ostream& out, const Terminals& to_print) {
    out << to_print.ToString();
    return out;
}

std::ostream& operator << (std::ostream& out, const TerminalsSet& to_print) {
    out << to_print.ToString();
    return out;
}