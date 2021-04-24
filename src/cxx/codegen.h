// Copyright (c) 2021 Roberto Raggi <roberto.raggi@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <cxx/condition_codegen.h>
#include <cxx/expression_codegen.h>
#include <cxx/ir_builder.h>
#include <cxx/ir_fwd.h>
#include <cxx/recursive_ast_visitor.h>
#include <cxx/statement_codegen.h>

#include <memory>

namespace cxx {

class TranslationUnit;

class Codegen final : RecursiveASTVisitor {
 public:
  Codegen(const Codegen&) = delete;
  Codegen& operator=(const Codegen&) = delete;

  Codegen();
  ~Codegen();

  std::unique_ptr<ir::Module> operator()(TranslationUnit* unit);

  ir::Expr* expression(ExpressionAST* ast);

  void condition(ExpressionAST* ast, ir::Block* iftrue, ir::Block* iffalse);

  void statement(StatementAST* ast);

  ir::IRFactory* irFactory();

  ir::Block* createBlock();

  void place(ir::Block* block);

  ir::IRBuilder& ir() { return ir_; }

 private:
  using RecursiveASTVisitor::visit;

  void visit(FunctionDefinitionAST* ast) override;

 private:
  ExpressionCodegen expression_{this};
  ConditionCodegen condition_{this};
  StatementCodegen statement_{this};

  TranslationUnit* unit_ = nullptr;
  std::unique_ptr<ir::Module> module_;
  ir::IRBuilder ir_;
  ir::Function* function_ = nullptr;
  ir::Block* entryBlock_ = nullptr;
  ir::Block* exitBlock_ = nullptr;
};

}  // namespace cxx
