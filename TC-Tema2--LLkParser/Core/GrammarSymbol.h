//
// Created by swqd on 4/10/21.
//

#ifndef CFG_GRAMMARSYMBOL_H
#define CFG_GRAMMARSYMBOL_H

#include <string>

class GrammarSymbol {
    bool isTerminal;
    std::string value;

public:
    [[nodiscard]] bool IsTerminal() const { return isTerminal; };
    [[nodiscard]] std::string const& Value() const { return value; }

    bool operator == (const GrammarSymbol& other) const {
        return (isTerminal == other.isTerminal && value == other.value);
    }
    bool operator != (const GrammarSymbol& other) const {
        return !((*this) == other);
    }
    bool operator < (const GrammarSymbol& other) const {
        if (isTerminal == other.isTerminal) {
            return (value < other.value);
        } else {
            return (isTerminal < other.isTerminal);
        }
    }

    GrammarSymbol() : isTerminal(), value() {}
    GrammarSymbol(bool isTerminal, std::string const& value) : isTerminal(isTerminal), value(value) {}
    GrammarSymbol(const GrammarSymbol& other) : isTerminal(other.isTerminal), value(other.value) {}
};


#endif //CFG_GRAMMARSYMBOL_H
