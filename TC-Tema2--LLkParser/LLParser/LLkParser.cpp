#include <iostream>
#include "LLkParser.h"

void LLkParser::BuildFo() {
    for (auto symbol : cfgEngine.symbolMap) {
        if (!symbol.second.IsTerminal()) {
            Fo[Terminals(symbol.second)] = TerminalsSet();
        }
    }
    Fo[Terminals(*cfgEngine.GetStartSymbol())] =
            TerminalsSet(Terminals(
                    std::vector<GrammarSymbol>()));

    while (true) {
        auto FoCopy = Fo;

        for (auto it : cfgEngine.productions) {
            auto symbol = cfgEngine.symbolMap.find(it.first);
            auto production = it.second;

            if (production.IsEpsilonProduction()) {
                continue;
            } else if (production.Length() == 1) {
                auto A = Terminals(symbol-> second);
                auto B = Terminals(production.GetRhsAsVector()[0]);
                Fo[B] += Fo[A];
            } else {
                std::vector<GrammarSymbol> aux = production.GetRhsAsVector();
                Terminals C = aux;

                for (auto it : aux) {
                    C.PopFront();
                    if (it.IsTerminal()) { continue; }
                    auto B = Terminals(it);
                    auto A = Terminals(symbol->second);
                    Fo[B] += Fi[C];
                    Fo[C] += Fo[A];
                    if (Fi[C].Contains(Epsilon)) {
                        Fo[B] += Fo[A];
                    }
                }
            }
        }

        if (FoCopy == Fo) { break; }
    }
}

void LLkParser::BuildFi() {
    Fil[{Epsilon, 0}] = TerminalsSet(Epsilon);
    for (const auto& symbol : cfgEngine.symbolMap) {
        if (symbol.second.IsTerminal()) {
            Fil[{Terminals(symbol.second), 1}] = TerminalsSet(Terminals(symbol.second));
        }
    }

    while (true) {
        auto FilCopy = Fil;

        for (auto symbol : cfgEngine.nullableSymbols) {
            Fil[{Terminals(*symbol), 0}] += (TerminalsSet(Epsilon));
        }
        for (auto it : cfgEngine.productions) {
            auto symbol = cfgEngine.symbolMap.find(it.first);
            auto production = it.second;

            if (production.Length() == 1) {
                Fil[{Terminals(symbol->second), 1}] += Fil[{Terminals(*production.GetRhs().front()), 1}];
            } else {
                std::vector<GrammarSymbol> aux = production.GetRhsAsVector();
                Terminals left(aux[0]);
                Terminals right(aux); right.PopFront();
                while (!right.Empty()) {
                    for (int i = 0; i <= K; i++) {
                        for (int j = 0; j <= i; j++) {
                            Fil[{Terminals(aux), i}] +=
                                    (Fil[{left, j}] * Fil[{right, i - j}]);
                        }
                        Fil[{Terminals(symbol->second), i}] += Fil[{Terminals(aux), i}];
                    }
                    left += right.Front();
                    right.PopFront();
                }
            }
        }

        if (FilCopy == Fil) { break; }
    }

    for (auto it : Fil) {
        Fi[it.first.first] += it.second;
    }
}

void LLkParser::Build() {
    BuildFi();
    BuildFo();
    BuildTable();
}

void LLkParser::BuildTable() {
    for (auto it : cfgEngine.productions) {
        auto production = it.second;
        auto symbol = cfgEngine.symbolMap[it.first];
        TerminalsSet aux = Fi[Terminals(production.GetRhsAsVector())] * Fo[symbol];
        aux.Trim(K);
        for (const auto& terminals : aux.GetTerminalsSet()) {
            parsingTable[{symbol, terminals}].push_back(production);
        }
    }

//    for (auto it : parsingTable) {
//        std::cerr << "Symbol: " << it.first.first.Value() << '\n';
//        std::cerr << "Terminals: " << it.first.second << '\n';
//        std::cerr << "Production: " << it.second[0] << "\n\n";
//    }
}

bool LLkParser::IsLLk() const {
    for (auto it : parsingTable) {
        if (it.second.size() > 1) {
            return false;
        }
    }
    return true;
}

bool LLkParser::Accepted(const std::string &input) {
    std::vector<GrammarSymbol> aux;
    for (int i = 0; i < input.size(); i++) {
        aux.push_back(GrammarSymbol(true, input.substr(i, 1)));
    }
    Terminals currentTerminals(aux);

    std::vector<GrammarSymbol> currentProductions;
    currentProductions.push_back(*cfgEngine.startSymbol);

    while (!currentTerminals.Empty() && !currentProductions.empty()) {
        auto current_symbol = currentProductions[0];
        if (current_symbol.IsTerminal()) {
            if (current_symbol == currentTerminals.Front()) {
                currentProductions.erase(currentProductions.begin());
                currentTerminals.PopFront();
            } else {
                return false;
            }
        } else {
            if (parsingTable.find({current_symbol, currentTerminals.Prefix(K)}) == parsingTable.end()) {
                parsingTable[{current_symbol, currentTerminals.Prefix(K)}].push_back(Production(current_symbol));
                return false;
            } else {
                auto current_production = parsingTable[{current_symbol, currentTerminals.Prefix(K)}][0];
                currentProductions.erase(currentProductions.begin());
                aux = current_production.GetRhsAsVector();
                for (int i = aux.size() - 1; i >= 0; i--) {
                    currentProductions.insert(currentProductions.begin(), aux[i]);
                }
            }
        }
    }

    while (!currentProductions.empty()) {
        if (currentProductions.front().IsTerminal()) {
            return false;
        } else if (!cfgEngine.IsNullable(currentProductions.front())) {
            return false;
        } else {
            currentProductions.erase(currentProductions.begin());
        }
    }

    return (currentTerminals.Empty() && currentProductions.empty());
}
