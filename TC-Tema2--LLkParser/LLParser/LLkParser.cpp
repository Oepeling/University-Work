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
                continue;
            } else {
                // production.Length() == 2
                std::vector<GrammarSymbol> aux = production.GetRhsAsVector();
                auto B = aux[0], C = aux[1], A = symbol->second;
                Fo[Terminals(B)] += Fi[Terminals(C)];
                Fo[Terminals(C)] += Fo[Terminals(A)];
                if (Fi[Terminals(C)].Contains(Terminals())) {
                    Fo[Terminals(B)] += Fo[Terminals(A)];
                }
            }
        }

        if (FoCopy == Fo) { break; }
    }
}

void LLkParser::BuildFi() {
    Fil[{Terminals(), 0}] = TerminalsSet(Terminals());
    for (const auto& symbol : cfgEngine.symbolMap) {
        if (symbol.second.IsTerminal()) {
            Fil[{Terminals(symbol.second), 1}] = TerminalsSet(Terminals(symbol.second));
        }
    }

    while (true) {
        auto FilCopy = Fil;

        for (auto it : cfgEngine.productions) {
            auto symbol = cfgEngine.symbolMap.find(it.first);
            auto production = it.second;

            if (production.IsEpsilonProduction()) {
                Fil[{Terminals(symbol->second), 0}] += (TerminalsSet(Terminals()));
            } else if (production.Length() == 1) {
                Fil[{Terminals(symbol->second), 1}] += Fil[{Terminals(*production.GetRhs().front()), 1}];
            } else {
                // production.Length() == 2
                std::vector<GrammarSymbol> aux = production.GetRhsAsVector();
                for (int i = 0; i <= K; i++) {
                    for (int j = 0; j <= i; j++) {
//                        if (symbol->first == cfgEngine.startSymbol->Value() && i == 1) {
//                            std::cerr << "linia 66: " << aux[0] << ' ' << j << ' ' << Fil[{Terminals(aux[0]), j}] << '\n';
//                            std::cerr << "linia 67: " << aux[1] << ' ' << i - j << ' ' << Fil[{Terminals(aux[1]), i - j}] << '\n';
//                            std::cerr << "linia 68: " << (Fil[{Terminals(aux[0]), j}] * Fil[{Terminals(aux[1]), i - j}]) << '\n';
//                        }
                        Fil[{Terminals(aux), i}] +=
                                (Fil[{Terminals(aux[0]), j}] * Fil[{Terminals(aux[1]), i - j}]);
                    }
                    Fil[{Terminals(symbol->second), i}] += Fil[{Terminals(aux), i}];
//                    std::cerr << symbol->second << ' ' << i << ' ' << Fil[{Terminals(symbol->second), i}] << '\n';
                }
            }
        }

        if (FilCopy == Fil) { break; }
    }

    for (auto it : Fil) {
        Fi[it.first.first] += it.second;
//        std::cerr << it.first.first << ' ' << it.first.second << ' ' << it.second << '\n';
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
//        std::cerr << "Linia 98: " << symbol.Value() << ' ' << '\n';
//        std::cerr << "Linia 99: " << Fi[Terminals(production.GetRhsAsVector())] << '\n';
//        std::cerr << "Linia 100: " << Fo[symbol] << '\n';
        TerminalsSet aux = Fi[Terminals(production.GetRhsAsVector())] * Fo[symbol];
//        std::cerr << aux << '\n';
//        if (symbol == *cfgEngine.startSymbol) {
//            std::cerr << "Linia 98: " << symbol.IsTerminal() << ' ' << symbol.Value() << ' ' << '\n';
//            std::cerr << aux << '\n';
//        }
        for (const auto& terminals : aux.GetTerminalsSet()) {
            parsingTable[{symbol, terminals}].push_back(production);
        }
    }
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
//        std::cerr << "Input: " << currentTerminals << '\n';
//        std::cerr << "Simboluri: ";
//        for (auto it : currentProductions) {
//            std::cerr << it.Value() << ' ';
//        }
//        std::cerr << '\n';

        auto current_symbol = currentProductions[0];
        if (current_symbol.IsTerminal()) {
//            std::cerr << "!!!!\n";
//            std::cerr << current_symbol.Value() << ' ' << currentTerminals.Front().Value() << '\n';
//            std::cerr << current_symbol.IsTerminal() << ' ' << currentTerminals.Front().IsTerminal() << '\n';
            if (current_symbol == currentTerminals.Front()) {
                currentProductions.erase(currentProductions.begin());
                currentTerminals.PopFront();
            } else {
                return false;
            }
        } else {
            if (parsingTable.find({current_symbol, currentTerminals.Prefix(K)}) == parsingTable.end()) {
//                std::cerr << "!!!!\n";
//                std::cerr << current_symbol.IsTerminal() << ' ' << current_symbol.Value() << ' ' << currentTerminals.Prefix((K)) << '\n';
//                std::cerr << currentTerminals.Prefix((K)).Size() << '\n';
                parsingTable[{current_symbol, currentTerminals.Prefix(K)}].push_back(Production(current_symbol));
//                for (auto it : parsingTable) {
//                    std::cerr << "Symbol: " << it.first.first.Value() << '\n';
//                    std::cerr << "Terminals: " << it.first.second << '\n';
//                    std::cerr << "Production: " << it.second[0] << "\n\n";
//                }

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

    return (currentTerminals.Empty() && currentProductions.empty());
}
