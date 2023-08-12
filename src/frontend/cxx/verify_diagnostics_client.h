#// Copyright (c) 2023 Roberto Raggi <roberto.raggi@gmail.com>
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

#include <cxx/diagnostics_client.h>
#include <cxx/preprocessor.h>

#include <list>
#include <regex>
#include <string>
#include <string_view>

namespace cxx {

struct ExpectedDiagnostic {
  Severity severity = Severity::Error;
  std::string_view fileName;
  std::string message;
  unsigned line = 0;
};

class VerifyDiagnosticsClient : public DiagnosticsClient,
                                public CommentHandler {
  std::regex rx{
      R"(^//\s*expected-(error|warning)(?:@([+-]?\d+))?\s*\{\{(.+)\}\})"};

  std::list<Diagnostic> reportedDiagnostics_;
  std::list<ExpectedDiagnostic> expectedDiagnostics_;
  bool verify_ = false;

 public:
  [[nodiscard]] auto hasErrors() const -> bool;

  [[nodiscard]] auto verify() const -> bool { return verify_; }
  void setVerify(bool verify) { verify_ = verify; }

  [[nodiscard]] auto reportedDiagnostics() const
      -> const std::list<Diagnostic>& {
    return reportedDiagnostics_;
  }

  void report(const Diagnostic& diagnostic) override;

  [[nodiscard]] auto expectedDiagnostics() const
      -> const std::list<ExpectedDiagnostic>& {
    return expectedDiagnostics_;
  }

  void handleComment(Preprocessor* preprocessor, const Token& token) override;

  void verifyExpectedDiagnostics();

 private:
  [[nodiscard]] auto findDiagnostic(const ExpectedDiagnostic& expected) const
      -> std::list<Diagnostic>::const_iterator;
};

}  // namespace cxx