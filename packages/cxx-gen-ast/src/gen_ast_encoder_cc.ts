// Copyright (c) 2025 Roberto Raggi <roberto.raggi@gmail.com>
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

import { groupNodesByBaseType } from "./groupNodesByBaseType.ts";
import type { AST, Attribute } from "./parseAST.ts";
import { cpy_header } from "./cpy_header.ts";
import * as fs from "fs";

export function gen_ast_encoder_cc({
  ast,
  output,
}: {
  ast: AST;
  output: string;
}) {
  const code: string[] = [];
  const emit = (line = "") => code.push(line);

  const by_base = groupNodesByBaseType(ast);

  const makeClassName = (name: string) =>
    name != "AST" ? name.slice(0, -3) : name;

  const toSnakeName = (name: string) =>
    name.replace(/([A-Z])/g, "_$1").toLocaleLowerCase();

  const emitLiteral = (
    m: Attribute,
    table: string,
    finalizers: (() => void)[],
  ) => {
    const fieldName = toSnakeName(m.name);

    emit(`    flatbuffers::Offset<flatbuffers::String> ${m.name};`);
    emit(`    if (ast->${m.name}) {`);
    emit(`       if (${table}.contains(ast->${m.name})) {`);
    emit(`         ${m.name} = ${table}.at(ast->${m.name});`);
    emit(`       } else {`);
    emit(`         ${m.name} = fbb_.CreateString(`);
    emit(`             ast->${m.name}->value());`);
    emit(`         ${table}.emplace(ast->${m.name}, ${m.name});`);
    emit(`       }`);
    emit(`    }`);
    finalizers.push(() => {
      emit(`  if (ast->${m.name}) {`);
      emit(`    builder.add_${fieldName}(${m.name});`);
      emit(`  }`);
    });
  };

  by_base.forEach((_nodes, base) => {
    if (base === "AST") return;
    const className = makeClassName(base);
    emit();
    emit(
      `  auto ASTEncoder::accept${className}(${base}* ast) -> std::tuple<flatbuffers::Offset<>, std::uint32_t> {`,
    );
    emit(`    if (!ast) return {};`);
    emit(`    flatbuffers::Offset<> offset;`);
    emit(`    std::uint32_t type = 0;`);
    emit(`    std::swap(offset, offset_);`);
    emit(`    std::swap(type, type_);`);
    emit(`    ast->accept(this);`);
    emit(`    std::swap(offset, offset_);`);
    emit(`    std::swap(type, type_);`);
    emit(`    return {offset, type};`);
    emit(`  }`);
  });

  by_base.forEach((nodes, base) => {
    nodes.forEach(({ name, members }) => {
      const className = makeClassName(name);

      emit();
      emit(`void ASTEncoder::visit(${name}* ast) {`);
      const finalizers: Array<() => void> = [];

      members.forEach((m) => {
        const fieldName = toSnakeName(m.name);

        emit();
        if (m.kind === "node" && !by_base.has(m.type)) {
          emit(`const auto ${m.name} = accept(ast->${m.name});`);
          finalizers.push(() => {
            emit(`  builder.add_${fieldName}(${m.name}.o);`);
          });
        } else if (m.kind === "node" && by_base.has(m.type)) {
          const className = makeClassName(m.type);
          emit(`const auto [${m.name}, ${m.name}Type] =`);
          emit(`  accept${className}(ast->${m.name});`);
          finalizers.push(() => {
            emit(`  builder.add_${fieldName}(${m.name});`);
            emit(`  builder.add_${fieldName}_type(`);
            emit(`    static_cast<io::${className}>(${m.name}Type));`);
          });
        } else if (m.kind === "node-list" && !by_base.has(m.type)) {
          const className = makeClassName(m.type);
          emit(`  std::vector<flatbuffers::Offset<io::${className}>>`);
          emit(`    ${m.name}Offsets;`);
          emit(`  for (auto node : ListView{ast->${m.name}}) {`);
          emit(`     if (!node) continue;`);
          emit(`     ${m.name}Offsets.emplace_back(accept(node).o);`);
          emit(`  }`);
          emit();
          emit(`  auto ${m.name}OffsetsVector = fbb_.CreateVector(`);
          emit(`    ${m.name}Offsets);`);
          finalizers.push(() => {
            emit(`    builder.add_${fieldName}(${m.name}OffsetsVector);`);
          });
        } else if (m.kind === "node-list" && by_base.has(m.type)) {
          const className = makeClassName(m.type);
          emit(`  std::vector<flatbuffers::Offset<>> ${m.name}Offsets;`);
          emit(`  std::vector<std::underlying_type_t<io::${className}>>`);
          emit(`    ${m.name}Types;`);
          emit();
          emit(`  for (auto node : ListView{ast->${m.name}}) {`);
          emit(`    if (!node) continue;`);
          emit(`    const auto [offset, type] = accept${className}(`);
          emit(`      node);`);
          emit(`    ${m.name}Offsets.push_back(offset);`);
          emit(`    ${m.name}Types.push_back(type);`);
          emit(`  }`);
          emit();
          emit(`  auto ${m.name}OffsetsVector = fbb_.CreateVector(`);
          emit(`    ${m.name}Offsets);`);
          emit(`  auto ${m.name}TypesVector = fbb_.CreateVector(`);
          emit(`    ${m.name}Types);`);

          finalizers.push(() => {
            emit(`  builder.add_${fieldName}(${m.name}OffsetsVector);`);
            emit(`  builder.add_${fieldName}_type(${m.name}TypesVector);`);
          });
        } else if (m.kind === "attribute" && m.type.endsWith("Literal")) {
          switch (m.type) {
            case "CharLiteral":
              emitLiteral(m, "charLiterals_", finalizers);
              break;
            case "StringLiteral":
              emitLiteral(m, "stringLiterals_", finalizers);
              break;
            case "IntegerLiteral":
              emitLiteral(m, "integerLiterals_", finalizers);
              break;
            case "FloatLiteral":
              emitLiteral(m, "floatLiterals_", finalizers);
              break;
            default:
              break;
          } // switch
        } else if (m.kind === "attribute" && m.type === "Identifier") {
          emitLiteral(m, "identifiers_", finalizers);
        } else if (m.kind === "attribute" && m.type === "TokenKind") {
          finalizers.push(() => {
            emit(`  builder.add_${fieldName}(`);
            emit(`    static_cast<std::uint32_t>(ast->${m.name}));`);
          });
        } else if (m.kind == "token") {
          finalizers.push(() => {
            emit(`  builder.add_${fieldName}(ast->${m.name}.index());`);
          });
        }
      });

      emit();
      emit(`  io::${className}::Builder builder{fbb_};`);
      finalizers.forEach((f) => f());
      emit();
      emit(`  offset_ = builder.Finish().Union();`);
      if (base != "AST") {
        const baseClassName = makeClassName(base);
        emit(`  type_ = io::${baseClassName}_${className};`);
      }
      emit(`}`);
    });
  });

  const out = `// Generated file by: gen_ast_encoder_cc.ts
${cpy_header}
#include <cxx/private/ast_encoder.h>

// cxx
#include <cxx-ast-flatbuffers/ast_generated.h>
#include <cxx/ast.h>
#include <cxx/literals.h>
#include <cxx/names.h>
#include <cxx/translation_unit.h>
#include <cxx/preprocessor.h>

#include <format>
#include <algorithm>

namespace cxx {

auto ASTEncoder::operator()(TranslationUnit* unit) -> std::span<const std::uint8_t> {
  if (!unit) return {};
  Table<Identifier> identifiers;
  Table<CharLiteral> charLiterals;
  Table<StringLiteral> stringLiterals;
  Table<IntegerLiteral> integerLiterals;
  Table<FloatLiteral> floatLiterals;

  std::swap(unit_, unit);
  std::swap(identifiers_, identifiers);
  std::swap(charLiterals_, charLiterals);
  std::swap(stringLiterals_, stringLiterals);
  std::swap(integerLiterals_, integerLiterals);
  std::swap(floatLiterals_, floatLiterals);

  std::vector<flatbuffers::Offset<io::Source>> sources;
  for (const auto& source : unit_->preprocessor()->sources()) {
    auto file_name = fbb_.CreateString(source.fileName);
    auto line_offsets =
        fbb_.CreateVector(source.lineOffsets.data(), source.lineOffsets.size());
    sources.push_back(io::CreateSource(fbb_, file_name, line_offsets));
  }

  auto source_list = fbb_.CreateVector(sources);

  std::vector<std::uint64_t> tokens;
  for (std::uint32_t i = 0; i < unit_->tokenCount(); ++i) {
    const auto& token = unit_->tokenAt(SourceLocation(i));
    tokens.push_back(token.raw());
  }

  auto token_list = fbb_.CreateVector(tokens);

  auto [unitOffset, unitType] = acceptUnit(unit_->ast());

  auto file_name = fbb_.CreateString(unit_->fileName());

  io::SerializedUnitBuilder builder{fbb_};
  builder.add_unit(unitOffset);
  builder.add_unit_type(static_cast<io::Unit>(unitType));
  builder.add_file_name(file_name);
  builder.add_source_list(source_list);
  builder.add_token_list(token_list);

  std::swap(unit_, unit);
  std::swap(identifiers_, identifiers);
  std::swap(charLiterals_, charLiterals);
  std::swap(stringLiterals_, stringLiterals);
  std::swap(integerLiterals_, integerLiterals);
  std::swap(floatLiterals_, floatLiterals);

  fbb_.Finish(builder.Finish(), io::SerializedUnitIdentifier());

  return std::span{fbb_.GetBufferPointer(), fbb_.GetSize()};
}

auto ASTEncoder::accept(AST* ast) -> flatbuffers::Offset<> {
  if (!ast) return {};
  flatbuffers::Offset<> offset;
  std::swap(offset_, offset);
  ast->accept(this);
  std::swap(offset_, offset);
  return offset;
}

${code.join("\n")}

} // namespace cxx
`;

  fs.writeFileSync(output, out);
}
