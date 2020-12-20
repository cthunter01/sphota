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

#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>

#include "Token.h"
/**
 * @todo write docs
 */
class Lexer
{
public:
    /**
     * Default constructor
     */
    Lexer();

    /**
     * Destructor
     */
    ~Lexer();

    void init(const char* contents);
    
    std::vector<Token> lex();

    Token getNextToken();
    


    std::pair<std::vector<Token>::const_iterator, std::vector<Token>::const_iterator> getTokenVectorIterators();
    
    std::vector<Token> getTokens();
    
    Lexer ( const Lexer& other ) = delete;
    Lexer& operator= ( const Lexer& other ) = delete;

private:

    void advance();

    void skipWhitespace();
    
    char peekNext() const;

    Token collectNumber() const;

    Token collectString();

    Token collectIdOrKeyword();

    Token advanceWithToken(const Token& token);
    void lexDash(Token& tok);
    void lexPlus(Token& tok);
    std::string getCurrentCharAsString() const;

    char c_;

    unsigned int loc_;

    const char* contents_;

    std::size_t len_;
    
    std::vector<Token> tokens_;
    
    std::vector<std::string> keywords_;
};

#endif // LEXER_H
