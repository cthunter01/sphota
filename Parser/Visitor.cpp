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

#include "Visitor.h"
#include <iostream> 

AST* Visitor::builtin_function_print(AST** args, std::size_t args_size)
{
    AST* visited_ast;
    for(int i = 0; i < args_size; ++i)
    {
        visited_ast = visit(args[i]);
        std::cout << visited_ast->string_value << std::endl;
    }
    return visited_ast;
}

AST* Visitor::visit(AST* node)
{
    switch(node->type)
    {
        case AST::AST_FUNCTION_CALL: return visit_function_call(node);
        case AST::AST_VARIABLE_DEFINITION: return visit_variable_definition(node);
        case AST::AST_VARIABLE: return visit_variable(node);
        case AST::AST_STRING: return visit_string(node);
        case AST::AST_COMPOUND: return visit_compound(node);
        default:
            std::cout << "Unhandled statement of type " << node->type << std::endl;
            exit(EXIT_FAILURE);
    }
    return new AST(AST::AST_NOOP);
}

AST* Visitor::visit_function_call(AST* node)
{
    functions_list.push_back(node);
    
    if(node->function_call_name == "print")
    {
        return builtin_function_print(node->function_call_arguments, node->function_call_arguments_size);
    }
    else
    {
        std::cout << "Undefined method\n";
        exit(EXIT_FAILURE);
    }
    return node; // new AST(AST::AST_NOOP);
}

AST* Visitor::visit_variable_definition(AST* node)
{
    variables_list.push_back(node);
    return node; // new AST(AST::AST_NOOP);
}

AST* Visitor::visit_variable(AST* node)
{
    for(int i = 0; i < variables_list.size(); ++i)
    {
        if(node->variable_name == variables_list[i]->variable_definition_variable_name)
        {
            return visit(variables_list[i]->variable_definition_value);
        }
    }
    return node; // new AST(AST::AST_NOOP);
}

AST* Visitor::visit_string(AST* node)
{
    return node; // new AST(AST::AST_NOOP);
}

AST* Visitor::visit_compound(AST* node)
{
    for(int i = 0; i < node->compound_size; ++i)
    {
        visit(node->compound_value[i]);
    }
    return node; // new AST(AST::AST_NOOP);
}
