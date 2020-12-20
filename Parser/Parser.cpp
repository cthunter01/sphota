/*
 * Copyright (c) 2020, <copyright holder> <email>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Parser.h"
#include <algorithm>

//#include "nullptr.h"
#include "Parser.h"
//#include "../Logger.h"
#include <iostream>

Parser::Parser(std::vector<Token> toks) :
    tokens(toks.begin(), toks.end()),
    currentTokenIterator(tokens.begin())
{
}

void Parser::eat(Token::Type type)
{
    if(currentTokenIterator->getType() == type)
    {
        currentTokenIterator++; // = lexer->getNextToken();
    }
    else
    {
        std::cout << "Expected Token " << Token::getTypeAsString(type) << ", but received " << currentTokenIterator->getTypeAsString() << "\n";
        exit(EXIT_FAILURE);
    }
}

AST* Parser::parse()
{
    return parse_statements();
}

AST* Parser::parse_statement()
{
    AST* retVal;
    switch(currentTokenIterator->getType())
    {
        case Token::TOKEN_ID:
            retVal = parse_id();
            break;
        case Token::TOKEN_KEYWORD:
            retVal = parse_keyword();
            break;
        case Token::TOKEN_DOT:
        case Token::TOKEN_EQUALS:
        case Token::TOKEN_LCURLYBRACE:
        case Token::TOKEN_LPAREN:
        case Token::TOKEN_MINUS:
        case Token::TOKEN_MINUS_MINUS:
        case Token::TOKEN_NUMBER_LITERAL:
        case Token::TOKEN_PLUS:
        case Token::TOKEN_PLUS_PLUS:
        case Token::TOKEN_RCURLYBRACE:
        case Token::TOKEN_RPAREN:
        case Token::TOKEN_SEMI:
        case Token::TOKEN_STRING:
        case Token::TOKEN_END:
        default:
            retVal = new AST(AST::AST_NOOP);
            break;
    }
    return retVal;
}

AST* Parser::parse_statements()
{
    AST* compound = new AST(AST::AST_COMPOUND);
    compound->compound_value = static_cast<AST**>(calloc(1, sizeof(AST*)));
    AST* ast_statement = parse_statement();
    compound->compound_value[0] = ast_statement;
    compound->compound_size += 1;
    
    while(currentTokenIterator->getType() == Token::TOKEN_SEMI)
    {
        eat(Token::TOKEN_SEMI);
        ast_statement = parse_statement();
        if(ast_statement->type != AST::AST_NOOP)
        {
            compound->compound_size += 1;
            compound->compound_value = static_cast<AST**>(realloc(
                compound->compound_value,
                compound->compound_size * sizeof(AST*)));
            compound->compound_value[compound->compound_size - 1] = ast_statement;
        }
    }
    return compound;
//    return nullptr;
}

AST* Parser::parse_expression()
{
    switch(currentTokenIterator->getType())
    {
        case Token::TOKEN_STRING: return parse_string();
        case Token::TOKEN_ID: return parse_id();
        default:
            return nullptr;
    }
}

AST* Parser::parse_factor()
{
    return nullptr;
}

AST* Parser::parse_term()
{
    return nullptr;
}

AST* Parser::parse_function_call()
{
    AST* functionCall = new AST(AST::AST_FUNCTION_CALL);
    functionCall->function_call_name = currentTokenIterator->getValue();
    eat(Token::TOKEN_ID);
    eat(Token::TOKEN_LPAREN);
    
    if(currentTokenIterator->getType() != Token::TOKEN_RPAREN)
    {
        functionCall->function_call_arguments = static_cast<AST**>(calloc(1, sizeof(AST*)));
        AST* expr = parse_expression();
        functionCall->function_call_arguments[0] = expr;
        functionCall->function_call_arguments_size += 1;
        while(currentTokenIterator->getType() == Token::TOKEN_COMMA)
        {
            eat(Token::TOKEN_COMMA);
            expr = parse_expression();
            functionCall->function_call_arguments_size += 1;
            functionCall->function_call_arguments = static_cast<AST**>(realloc(
                functionCall->function_call_arguments,
                functionCall->function_call_arguments_size * sizeof(AST*)));
            functionCall->function_call_arguments[functionCall->function_call_arguments_size - 1] = expr;
        }
    }
    eat(Token::TOKEN_RPAREN);
    return functionCall;
}

AST* Parser::parse_variable()
{
    std::string tokenValue = currentTokenIterator->getValue();
    eat(Token::TOKEN_ID); // variable name or function call
    AST* variable = new AST(AST::AST_VARIABLE);
    variable->variable_name = tokenValue;
    return variable;
}


AST* Parser::parse_variable_definition()
{
    eat(Token::TOKEN_KEYWORD);
    std::string variable_definition_variable_name = currentTokenIterator->getValue();
    eat(Token::TOKEN_ID);
    eat(Token::TOKEN_EQUALS);
    
    AST* variable_definition_value = parse_expression();
    
    AST* variable_definition = new AST(AST::AST_VARIABLE_DEFINITION);
    
    variable_definition->variable_definition_variable_name = variable_definition_variable_name;
    variable_definition->variable_definition_value = variable_definition_value;
    
    return variable_definition;
}

AST* Parser::parse_string()
{
    AST* astString = new AST(AST::AST_STRING);
    astString->string_value = currentTokenIterator->getValue();
    eat(Token::TOKEN_STRING);
    return astString;
}

AST* Parser::parse_id()
{
    if((currentTokenIterator+1)->getType() == Token::TOKEN_LPAREN)
    {
        return parse_function_call();
    }
    else
    {
        
        return parse_variable();
    }
}

AST* Parser::parse_keyword()
{
    if(currentTokenIterator->getValue() == "var")
    {
        return parse_variable_definition();
    }
    return nullptr;
}
