#include <iostream>
#include "Core/CFG_Engine.h"
#include "CNF/CNF_Converter.h"
#include "LLParser/LLkParser.h"

int main() {
    try{
        CFG_Engine engine { "S" };

        engine.AddProduction("S", {"A"});
        engine.AddProduction("A", {"a"});
        engine.AddProduction("A", {"B", "C"});
        engine.AddEpsilonProduction("C");
        engine.AddProduction("B", {"a"});
        engine.AddProduction("C", {"b"});

//        engine.AddProduction("S", {"D", "A"});
//        engine.AddProduction("S", {"a", "B"});
//        engine.AddProduction("A", {"a"});
//        engine.AddProduction("A", {"B", "D"});
//        engine.AddProduction("A", {"b", "D", "A", "B"});
//        engine.AddProduction("B", {"b"});
//        engine.AddProduction("B", {"B", "A"});
//        engine.AddProduction("D", {"B", "A"});
//        engine.AddProduction("C", {"B", "A"});
//        engine.AddEpsilonProduction("D");

        CNF_Converter converter { engine };
        LLkParser parser(4, converter.GetEngine());
        bool is_llk = parser.IsLLk();
        std::cout << is_llk << std::endl;
        if (is_llk) {
            std::cout << parser.Accepted("ab");
        }
    }
    catch (SymbolFormatError &err){
        std::cerr << err.what();
    }

    return 0;
}
