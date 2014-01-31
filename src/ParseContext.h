// Copyright (c) 2014 Roberto Raggi <roberto.raggi@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef PARSECONTEXT_H
#define PARSECONTEXT_H

#include "Globals.h"
#include "Types.h"

struct ParseContext {
  TranslationUnit* unit{nullptr};

  ParseContext() = default;

  struct Specs {
    Specs() = default;
    QualType type;
    TokenKind storageSpec{T_EOF_SYMBOL};
    union {
      unsigned _flags{0};
      struct {
        unsigned isInline: 1;
        unsigned isTypedef: 1;
        unsigned isVirtual: 1;
        unsigned isFriend: 1;
        unsigned isExplicit: 1;
        unsigned isConstexpr: 1;
      };
    };
  };

  struct Decl {
    Specs specs;
    const Name* name{nullptr};
    std::vector<const Name*> actuals;

    const Type* operator->() const {
      return *specs.type;
    }

    void setType(const Type* type) {
      specs.type.setType(type);
    }

    void setUnsigned(bool isUnsigned) {
      specs.type.setUnsigned(isUnsigned);
    }

    void setConst(bool isConst) {
      specs.type.setConst(isConst);
    }

    void setVolatile(bool isVolatile) {
      specs.type.setVolatile(isVolatile);
    }
  };

  const Name* name(NameAST* ast);
  Specs specifiers(List<SpecifierAST*>* specifiers);
  Decl declarator(const Specs& specs, DeclaratorAST* decl);
  QualType finish(QualType type);

  class ProcessName;
  class ProcessDeclarator;
};

#endif // PARSECONTEXT_H


