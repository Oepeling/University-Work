#include <iostream>
#include <fstream>
#include "Core/CFG_Engine.h"
#include "CNF/CNF_Converter.h"
#include "LLParser/LLkParser.h"

LLkParser readGrammar(const std::string& input_file) {
    std::ifstream in(input_file);

    int k; in >> k;

    std::string start_symbol; in >> start_symbol;
    CFG_Engine engine { start_symbol };

    int n; in >> n;
    for (int i = 0; i < n; i++) {
        std::string left; in >> left;
        std::string right; in >> right >> right;

        if (right == "$") {
            engine.AddEpsilonProduction(left);
            continue;
        }

        std::vector<std::string> right_vector;
        for (int i = 0; i < right.size(); i++) {
            right_vector.push_back(right.substr(i, 1));
        }
        engine.AddProduction(left, right_vector);
    }

    in.close();

    CNF_Converter converter { engine };
    LLkParser parser(k, converter.GetEngine());

    return parser;
}

void startTesting(LLkParser& parser) {
    std::string to_test;
    while (std::cin >> to_test) {
        if (parser.Accepted(to_test)) {
            std::cout << "Gramatica accepta stringul \"" << to_test << "\"\n";
        } else {
            std::cout << "Gramatica nu accepta stringul \"" << to_test << "\"\n";
        }
    }
}

int main() {
    try {
        LLkParser parser = readGrammar("input.txt");

        bool is_llk = parser.IsLLk();
        if (is_llk) {
            std::cout << "Gramatica este LL(" << parser.GetK() << ")\n";
            startTesting(parser);
        } else {
            std::cout << "Gramatica nu este LL(k)\n";
        }
    }
    catch (SymbolFormatError &err){
        std::cerr << err.what();
    }

    return 0;
}
