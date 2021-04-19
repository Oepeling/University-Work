#include "LLkParser.h"

void LLkParser::BuildFo() {
    Fo[Terminals(*cfgEngine.GetStartSymbol())] =
            TerminalsSet(Terminals(
                    std::vector<GrammarSymbol>(K, GrammarSymbol(true, "$"))));
    for (auto symbol : cfgEngine.symbolMap) {
        if (!symbol.second.IsTerminal()) {
            Fo[Terminals(symbol.second)] = TerminalsSet();
        }
    }

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
                        Fil[{Terminals(aux), i}] +=
                                (Fil[{Terminals(aux[0]), j}] * Fil[{Terminals(aux[1]), i - j}]);
                    }
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
