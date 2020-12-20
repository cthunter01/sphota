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

#ifndef AST_H
#define AST_H

#include <string>

/**
 * @todo write docs
 */
class AST
{
public:
    
    typedef enum
    {
        AST_FUNCTION_CALL,
        AST_VARIABLE_DEFINITION,
        AST_VARIABLE,
        AST_STRING,
        AST_COMPOUND,
        AST_NOOP
    } Type;
    
    AST(Type type);
    
    Type type;
    
    // AST_VARIABLE_DEFINITION
    std::string variable_definition_variable_name;
    AST* variable_definition_value;
    
    // AST_VARIABLE
    std::string variable_name;
    
    // AST_FUNCTION_CALL
    std::string function_call_name;
    AST** function_call_arguments;
    std::size_t function_call_arguments_size;
    
    // AST_STRING
    std::string string_value;
    
    // AST_COMPOUND
    AST** compound_value;
    std::size_t compound_size;
    
};

#endif // AST_H
