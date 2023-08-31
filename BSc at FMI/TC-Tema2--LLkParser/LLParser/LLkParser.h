#ifndef CFG_LLKPARSER_H
#define CFG_LLKPARSER_H


#include <map>
#include "../Core/CFG_Engine.h"
#include "../Core/TerminalsSet.h"

class LLkParser {
    CFG_Engine cfgEngine;
    const int K;

    std::map<std::pair<Terminals, int>, TerminalsSet> Fil;
    std::map<Terminals, TerminalsSet> Fi;
    std::map<Terminals, TerminalsSet> Fo;
    std::map<std::pair<GrammarSymbol, Terminals>, std::vector<Production>> parsingTable;

    void BuildFi();
    void BuildFo();
    void BuildTable();
    void Build();

public:
    LLkParser(const int k, const CFG_Engine &cfgEngine1) : K(k), cfgEngine(cfgEngine1) { Build(); };

    bool Accepted(const std::string& input);
    bool IsLLk() const;
    const int GetK() const { return K; }
};


#endif //CFG_LLKPARSER_H
