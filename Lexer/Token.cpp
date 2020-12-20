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

#include <cstdlib>

#include "Token.h"

Token::Token(Token::Type type, const std::string& value) :
    type_(type),
    value_(value)
{
}

std::string Token::getTypeAsString() const
{
    return getTypeAsString(type_);
}

std::string Token::getTypeAsString(Type type)
{
    std::string retVal;
    switch(type)
    {
        case TOKEN_COMMA:
            retVal.append("TOKEN_COMMA");
            break;
        case TOKEN_DOT:
            retVal.append("TOKEN_DOT");
            break;
        case TOKEN_EQUALS:
            retVal.append("TOKEN_EQUALS");
            break;
        case TOKEN_KEYWORD:
            retVal.append("TOKEN_KEYWORD");
            break;
        case TOKEN_ID:
            retVal.append("TOKEN_ID");
            break;
        case TOKEN_LCURLYBRACE:
            retVal.append("TOKEN_LCURLYBRACE");
            break;
        case TOKEN_LPAREN:
            retVal.append("TOKEN_LPAREN");
            break;
        case TOKEN_MINUS:
            retVal.append("TOKEN_MINUS");
            break;
        case TOKEN_MINUS_MINUS:
            retVal.append("TOKEN_MINUS_MINUS");
            break;
        case TOKEN_NUMBER_LITERAL:
            retVal.append("TOKEN_NUMBER_LITERAL");
            break;
        case TOKEN_PLUS:
            retVal.append("TOKEN_PLUS");
            break;
        case TOKEN_PLUS_PLUS:
            retVal.append("TOKEN_PLUS_PLUS");
            break;
        case TOKEN_RCURLYBRACE:
            retVal.append("TOKEN_RCURLYBRACE");
            break;
        case TOKEN_RPAREN:
            retVal.append("TOKEN_RPAREN");
            break;
        case TOKEN_SEMI:
            retVal.append("TOKEN_SEMI");
            break;
        case TOKEN_STRING:
            retVal.append("TOKEN_STRING");
            break;
        case TOKEN_END:
            retVal.append("TOKEN_END");
            break;
            
    }
    return retVal;
}
