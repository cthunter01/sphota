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

#include "Lexer.h"

#include "Lexer.h"
#include "../Logger.h"
#include "LexerError.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>

Lexer::Lexer()
{
    keywords_.push_back("var");
    keywords_.push_back("struct");
}

Lexer::~Lexer()
{
}

std::pair<std::vector<Token>::const_iterator, std::vector<Token>::const_iterator> Lexer::getTokenVectorIterators()
{
    std::vector<Token>::const_iterator first = tokens_.begin();
    std::vector<Token>::const_iterator last = tokens_.end();

    return std::make_pair(first, last);
}


void Lexer::init(const char* contents)
{

    loc_ = 0;
    contents_ = contents;
    len_ = strlen(contents);
    c_ = contents_[0];
}

std::vector<Token> Lexer::lex()
{
    Token token = getNextToken();
    while(token.getType() != Token::TOKEN_END)
    {
        try
        {
            token = getNextToken();
        }
        catch(const LexerError&)
        {
            Logger::getInstance()->log("There was an error in the Lexer\n");
        }
    }
    return tokens_;
}

void Lexer::advance()
{
    if (c_ != '\0' && loc_ < len_)
    {
        loc_++;
        c_ = contents_[loc_];
    }
}

void Lexer::skipWhitespace()
{
    while(c_ == ' ' || c_ == '\n' || c_ == '\t')
    {
        advance();
    }
}

char Lexer::peekNext() const
{
    if(loc_ < len_-1)
        return contents_[loc_+1];
    else
        return '\0';
}

Token Lexer::getNextToken()
{
    Token tok(Token::TOKEN_END, std::string(""));
    
    //Skip over any skipWhitespace
    skipWhitespace();
    if(c_ != '\0' && loc_ < len_)
    {

        if(isdigit(c_))
        {
            tok = collectNumber();
        }
        
        else if(isalnum(c_))
        {
            tok = collectIdOrKeyword();
        }

        else if(c_ == '"')
        {
            tok = collectString();
        }
        

        else switch(c_)
        {
            case ',': tok = advanceWithToken(Token(Token::TOKEN_COMMA, ",")); break;
            case '.': tok = advanceWithToken(Token(Token::TOKEN_DOT, ".")); break;
            case '=': tok = advanceWithToken(Token(Token::TOKEN_EQUALS, "=")); break;
            case ';': tok = advanceWithToken(Token(Token::TOKEN_SEMI, ";")); break;
            case '(': tok = advanceWithToken(Token(Token::TOKEN_LPAREN, "(")); break;
            case ')': tok = advanceWithToken(Token(Token::TOKEN_RPAREN, getCurrentCharAsString())); break;
            case '{': tok = advanceWithToken(Token(Token::TOKEN_LCURLYBRACE, getCurrentCharAsString())); break;
            case '}': tok = advanceWithToken(Token(Token::TOKEN_RCURLYBRACE, getCurrentCharAsString())); break;
            case '-':
                lexDash(tok);
                break;
            case '+':
                lexPlus(tok);
                break;
            default:
                throw LexerError();
        }

    }
    tokens_.push_back(tok);
    return tok;
}

void Lexer::lexDash(Token& tok)
{
    if('-' == peekNext())
    {
        tok = advanceWithToken(Token(Token::TOKEN_MINUS_MINUS, "--"));
        advance();
    }
    else
    {
        tok = advanceWithToken(Token(Token::TOKEN_MINUS, "-"));
    }
}

void Lexer::lexPlus(Token& tok)
{
    if('+' == peekNext())
    {
        tok = advanceWithToken(Token(Token::TOKEN_PLUS_PLUS, "++"));
        advance();
    }
    else
    {
        tok = advanceWithToken(Token(Token::TOKEN_PLUS, getCurrentCharAsString()));
    }
}

Token Lexer::collectNumber() const
{
    return Token(Token::TOKEN_END, "");
}

Token Lexer::collectString()
{
    // Skip "
    advance();

    std::string value("");

    while(c_ != '"')
    {
        value.append(getCurrentCharAsString());
        advance();
    }

    // ignore closing "
    advance();
    return Token(Token::TOKEN_STRING, value);
}

Token Lexer::collectIdOrKeyword()
{
    std::string value("");

    while(isalnum(c_))
    {
        value.append(getCurrentCharAsString());
        advance();
    }
    
    if(std::find(keywords_.begin(), keywords_.end(), value) != keywords_.end())
    {
        return Token(Token::TOKEN_KEYWORD, std::string(value));
    }
    else
    {
        return Token(Token::TOKEN_ID, std::string(value));
    }
}

Token Lexer::advanceWithToken(const Token& token)
{
    advance();

    return token;
}

std::string Lexer::getCurrentCharAsString() const
{
    std::string str(1, c_);
    return str;
}

std::vector<Token> Lexer::getTokens()
{
    // Returns a copy
    return tokens_;
}
