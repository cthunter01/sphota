#include <iostream>
#include <sstream>

//#include <stdlib.h>
#include <unistd.h> // close(), why is that not defined in the same place as open()?
#include "Lexer/Lexer.h"
#include "Logger.h"
#include "Parser/Parser.h"
#include "Parser/Visitor.h"
#include "Lexer/Token.h"
#include "SourceFile.h"

//#include "Visitor.h"

int main(int argc, char **argv) {
    // Open test file for reading/parsing
    if(argc < 2)
    {
        std::cout << "File path not given\n";
        exit(0);
    }
    
    SourceFile* sourceFile = new SourceFile(argv[1]);

    Lexer* lexer = new Lexer;
    lexer->init(sourceFile->getCharBuffer());
    std::vector<Token> tokens = lexer->lex();
    
    /*
    for(auto& i : tokens)
    {
        std::stringstream msg;

        msg << "TOKEN(" << i.getTypeAsString() << ", " << i.getType() << ", \"" << i.getValue() << "\")";
        Logger::getInstance()->log(std::cout, msg.str());
    }
    */
    
    Parser parser(tokens);
    AST* rootNode = parser.parse();
    
    //std::cout << "Root node type: " << rootNode->type << std::endl;
    //std::cout << "Root Compound size: " << rootNode->compound_size << std::endl;
    
    Visitor visitor;
    visitor.visit(rootNode);
    delete sourceFile;
    /*
    lexer.lex();
    
    std::pair<std::vector<Token>::const_iterator, std::vector<Token>::const_iterator> tokenIterators = lexer.getTokenVectorIterators();
    
    delete sourceFile;

    for(std::vector<Token>::const_iterator i = tokenIterators.first; i < tokenIterators.second; ++i)
    {
        std::stringstream msg;

        msg << "TOKEN(" << i->getTypeAsString() << ", " << i->getType() << ", \"" << i->getValue() << "\")";
        Logger::getInstance()->log(std::cout, msg.str());
    }

    */
}
