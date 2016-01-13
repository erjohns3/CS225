/**
 * @file parser.cpp
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include "parser.h"
#include "operation.h"
#include "number.h"
#include "terminal.h"
#include "binary_op.h"
#include "unary_op.h"
#include <iostream>

namespace cs225
{

/**
 * A "private class" for helping us parse expressions. Maintains all of the
 * state necessary to perform Dijkstra's shunting-yard algorithm.
 *
 * @see https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */
    class parser
    {
      public:
        /**
         * @param tokens The tokens to parse
         * @return the root of the parse tree for that expression
         */

         
        std::unique_ptr<node> parse(queue<std::unique_ptr<token>>& tokens);

      private:
        // add lots of other helper methods here!

        void push_op(std::unique_ptr<token>& op);

        void isValid(queue<std::unique_ptr<token>>& tokens);
        /**
         * The stack to hold the operator tokens encountered. This is the "side
         * rail" in the shunting yard algorithm.
         */
        stack<std::unique_ptr<token>> ops_;

        /**
         * What is this for? It is a mystery (and a hint)!
         */
        stack<std::unique_ptr<node>> nodes_;
    };

    std::unique_ptr<node> parse(queue<std::unique_ptr<token>>& tokens)
    {
        parser p;
        p.isValid(tokens);
        return p.parse(tokens);
    }

    std::unique_ptr<node> parser::parse(queue<std::unique_ptr<token>>& tokens)
    {

        /*
        while (!tokens.empty()){
            auto& tok = tokens.front();
            /// @todo handle the token

            if(tok->type() == token_type::NUMBER){
                nodes_.push(make_term(tok->as_number()->value()));
            }
            else if(tok->type() == token_type::OPERATION){
                while(!ops_.empty() && ((tok->as_operation()->associativity() == associativity::LEFT && tok->as_operation()->precedence() <= ops_.top()->as_operation()->precedence()) || (tok->as_operation()->associativity() == associativity::RIGHT && tok->as_operation()->precedence() < ops_.top()->as_operation()->precedence()))){
                    push_op(ops_.top());
                    ops_.pop();
                }
                ops_.push(tok);
            }else if(tok->type() == token_type::TEXT){
                if(tok->text().compare("(") == 0){
                    ops_.push(tok);
                }else if(tok->text().compare(")") == 0){
                    while(ops_.top()->text().compare("(") != 0){
                        if(ops_.empty())
                            throw std::runtime_error("");
                        push_op(ops_.top());
                        ops_.pop();
                    }
                    ops_.pop();
                }
            }
            tokens.pop();
        }
        while (!ops_.empty()){
            if(ops_.top()->text().compare("(") == 0)
                throw std::runtime_error("");
            push_op(ops_.top());
            ops_.pop();
        }
        */

        /// @todo clean up remaining operators
        /// @todo return the root of your tree
    }

    void parser::push_op(std::unique_ptr<token>& op)
    {
        /*
        if(op->as_operation()->args() == 1){
            std::unique_ptr<node> tmp {make_term(make_unary_op(op->text(), std::move(nodes_.top()))->value())};
            nodes_.pop();
            nodes_.push(tmp);
        }else if(op->as_operation()->args() == 2){
            std::unique_ptr<node> tmp0;
            tmp0.swap(nodes_.top());
            nodes_.pop();
            std::unique_ptr<node> tmp {make_term(make_binary_op(op->text(), std::move(nodes_.top()), std::move(tmp0))->value())};
            nodes_.pop();
            nodes_.push(tmp);
        }

        */
    }

    /*
    void parser::isValid(queue<std::unique_ptr<token>>& tokens){
        //int ops = 0;
        //int nums = 0;
        int lp = 0;
        int rp = 0;
        while (!tokens.empty()){
            auto& tok = tokens.front();
            
            if(tok->type() == token_type::NUMBER){
                nodes_.push(make_term(tok->as_number()->value()));
            }
            else if(tok->type() == token_type::OPERATION){
                if(){

                }
                
            }
            
            if(tok->text().compare("(") == 0){
                lp++;
            }else if(tok->text().compare(")") == 0){
                rp++;
            }
            tokens.push(std::move(tok));
            tokens.pop();
        }
        if(lp != rp){
            throw std::runtime_error("");
        }
    }
    */
}
