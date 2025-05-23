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

#pragma once

#include <cxx/cxx_fwd.h>

#include <iosfwd>

namespace cxx {

#define CXX_FOR_EACH_SYMBOL(V) \
  V(Namespace)                 \
  V(Concept)                   \
  V(Class)                     \
  V(Enum)                      \
  V(ScopedEnum)                \
  V(Function)                  \
  V(TypeAlias)                 \
  V(Variable)                  \
  V(Field)                     \
  V(Parameter)                 \
  V(ParameterPack)             \
  V(Enumerator)                \
  V(FunctionParameters)        \
  V(TemplateParameters)        \
  V(Block)                     \
  V(Lambda)                    \
  V(TypeParameter)             \
  V(NonTypeParameter)          \
  V(TemplateTypeParameter)     \
  V(ConstraintTypeParameter)   \
  V(OverloadSet)               \
  V(BaseClass)                 \
  V(UsingDeclaration)

class Symbol;
class ScopedSymbol;
class Scope;

template <typename S>
struct TemplateSpecialization;

template <typename S>
class TemplateInfo;

#define PROCESS_SYMBOL(S) class S##Symbol;
CXX_FOR_EACH_SYMBOL(PROCESS_SYMBOL)
#undef PROCESS_SYMBOL

#define PROCESS_SYMBOL(S) k##S,
enum class SymbolKind { CXX_FOR_EACH_SYMBOL(PROCESS_SYMBOL) };
#undef PROCESS_SYMBOL

enum class AccessSpecifier {
  kPublic,
  kProtected,
  kPrivate,
};

void dump(std::ostream& out, Symbol* symbol, int depth = 0);

auto operator<<(std::ostream& out, Symbol* symbol) -> std::ostream&;

}  // namespace cxx
