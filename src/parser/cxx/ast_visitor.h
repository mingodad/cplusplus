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

#include <cxx/ast_fwd.h>

namespace cxx {

class ASTVisitor {
 public:
  virtual ~ASTVisitor() = default;

  // UnitAST
  virtual void visit(TranslationUnitAST* ast) = 0;
  virtual void visit(ModuleUnitAST* ast) = 0;

  // DeclarationAST
  virtual void visit(SimpleDeclarationAST* ast) = 0;
  virtual void visit(AsmDeclarationAST* ast) = 0;
  virtual void visit(NamespaceAliasDefinitionAST* ast) = 0;
  virtual void visit(UsingDeclarationAST* ast) = 0;
  virtual void visit(UsingEnumDeclarationAST* ast) = 0;
  virtual void visit(UsingDirectiveAST* ast) = 0;
  virtual void visit(StaticAssertDeclarationAST* ast) = 0;
  virtual void visit(AliasDeclarationAST* ast) = 0;
  virtual void visit(OpaqueEnumDeclarationAST* ast) = 0;
  virtual void visit(FunctionDefinitionAST* ast) = 0;
  virtual void visit(TemplateDeclarationAST* ast) = 0;
  virtual void visit(ConceptDefinitionAST* ast) = 0;
  virtual void visit(DeductionGuideAST* ast) = 0;
  virtual void visit(ExplicitInstantiationAST* ast) = 0;
  virtual void visit(ExportDeclarationAST* ast) = 0;
  virtual void visit(ExportCompoundDeclarationAST* ast) = 0;
  virtual void visit(LinkageSpecificationAST* ast) = 0;
  virtual void visit(NamespaceDefinitionAST* ast) = 0;
  virtual void visit(EmptyDeclarationAST* ast) = 0;
  virtual void visit(AttributeDeclarationAST* ast) = 0;
  virtual void visit(ModuleImportDeclarationAST* ast) = 0;
  virtual void visit(ParameterDeclarationAST* ast) = 0;
  virtual void visit(AccessDeclarationAST* ast) = 0;
  virtual void visit(ForRangeDeclarationAST* ast) = 0;
  virtual void visit(StructuredBindingDeclarationAST* ast) = 0;
  virtual void visit(AsmOperandAST* ast) = 0;
  virtual void visit(AsmQualifierAST* ast) = 0;
  virtual void visit(AsmClobberAST* ast) = 0;
  virtual void visit(AsmGotoLabelAST* ast) = 0;

  // StatementAST
  virtual void visit(LabeledStatementAST* ast) = 0;
  virtual void visit(CaseStatementAST* ast) = 0;
  virtual void visit(DefaultStatementAST* ast) = 0;
  virtual void visit(ExpressionStatementAST* ast) = 0;
  virtual void visit(CompoundStatementAST* ast) = 0;
  virtual void visit(IfStatementAST* ast) = 0;
  virtual void visit(ConstevalIfStatementAST* ast) = 0;
  virtual void visit(SwitchStatementAST* ast) = 0;
  virtual void visit(WhileStatementAST* ast) = 0;
  virtual void visit(DoStatementAST* ast) = 0;
  virtual void visit(ForRangeStatementAST* ast) = 0;
  virtual void visit(ForStatementAST* ast) = 0;
  virtual void visit(BreakStatementAST* ast) = 0;
  virtual void visit(ContinueStatementAST* ast) = 0;
  virtual void visit(ReturnStatementAST* ast) = 0;
  virtual void visit(CoroutineReturnStatementAST* ast) = 0;
  virtual void visit(GotoStatementAST* ast) = 0;
  virtual void visit(DeclarationStatementAST* ast) = 0;
  virtual void visit(TryBlockStatementAST* ast) = 0;

  // ExpressionAST
  virtual void visit(GeneratedLiteralExpressionAST* ast) = 0;
  virtual void visit(CharLiteralExpressionAST* ast) = 0;
  virtual void visit(BoolLiteralExpressionAST* ast) = 0;
  virtual void visit(IntLiteralExpressionAST* ast) = 0;
  virtual void visit(FloatLiteralExpressionAST* ast) = 0;
  virtual void visit(NullptrLiteralExpressionAST* ast) = 0;
  virtual void visit(StringLiteralExpressionAST* ast) = 0;
  virtual void visit(UserDefinedStringLiteralExpressionAST* ast) = 0;
  virtual void visit(ThisExpressionAST* ast) = 0;
  virtual void visit(NestedStatementExpressionAST* ast) = 0;
  virtual void visit(NestedExpressionAST* ast) = 0;
  virtual void visit(IdExpressionAST* ast) = 0;
  virtual void visit(LambdaExpressionAST* ast) = 0;
  virtual void visit(FoldExpressionAST* ast) = 0;
  virtual void visit(RightFoldExpressionAST* ast) = 0;
  virtual void visit(LeftFoldExpressionAST* ast) = 0;
  virtual void visit(RequiresExpressionAST* ast) = 0;
  virtual void visit(VaArgExpressionAST* ast) = 0;
  virtual void visit(SubscriptExpressionAST* ast) = 0;
  virtual void visit(CallExpressionAST* ast) = 0;
  virtual void visit(TypeConstructionAST* ast) = 0;
  virtual void visit(BracedTypeConstructionAST* ast) = 0;
  virtual void visit(SpliceMemberExpressionAST* ast) = 0;
  virtual void visit(MemberExpressionAST* ast) = 0;
  virtual void visit(PostIncrExpressionAST* ast) = 0;
  virtual void visit(CppCastExpressionAST* ast) = 0;
  virtual void visit(BuiltinBitCastExpressionAST* ast) = 0;
  virtual void visit(BuiltinOffsetofExpressionAST* ast) = 0;
  virtual void visit(TypeidExpressionAST* ast) = 0;
  virtual void visit(TypeidOfTypeExpressionAST* ast) = 0;
  virtual void visit(SpliceExpressionAST* ast) = 0;
  virtual void visit(GlobalScopeReflectExpressionAST* ast) = 0;
  virtual void visit(NamespaceReflectExpressionAST* ast) = 0;
  virtual void visit(TypeIdReflectExpressionAST* ast) = 0;
  virtual void visit(ReflectExpressionAST* ast) = 0;
  virtual void visit(UnaryExpressionAST* ast) = 0;
  virtual void visit(AwaitExpressionAST* ast) = 0;
  virtual void visit(SizeofExpressionAST* ast) = 0;
  virtual void visit(SizeofTypeExpressionAST* ast) = 0;
  virtual void visit(SizeofPackExpressionAST* ast) = 0;
  virtual void visit(AlignofTypeExpressionAST* ast) = 0;
  virtual void visit(AlignofExpressionAST* ast) = 0;
  virtual void visit(NoexceptExpressionAST* ast) = 0;
  virtual void visit(NewExpressionAST* ast) = 0;
  virtual void visit(DeleteExpressionAST* ast) = 0;
  virtual void visit(CastExpressionAST* ast) = 0;
  virtual void visit(ImplicitCastExpressionAST* ast) = 0;
  virtual void visit(BinaryExpressionAST* ast) = 0;
  virtual void visit(ConditionalExpressionAST* ast) = 0;
  virtual void visit(YieldExpressionAST* ast) = 0;
  virtual void visit(ThrowExpressionAST* ast) = 0;
  virtual void visit(AssignmentExpressionAST* ast) = 0;
  virtual void visit(PackExpansionExpressionAST* ast) = 0;
  virtual void visit(DesignatedInitializerClauseAST* ast) = 0;
  virtual void visit(TypeTraitExpressionAST* ast) = 0;
  virtual void visit(ConditionExpressionAST* ast) = 0;
  virtual void visit(EqualInitializerAST* ast) = 0;
  virtual void visit(BracedInitListAST* ast) = 0;
  virtual void visit(ParenInitializerAST* ast) = 0;

  // AST
  virtual void visit(SplicerAST* ast) = 0;
  virtual void visit(GlobalModuleFragmentAST* ast) = 0;
  virtual void visit(PrivateModuleFragmentAST* ast) = 0;
  virtual void visit(ModuleDeclarationAST* ast) = 0;
  virtual void visit(ModuleNameAST* ast) = 0;
  virtual void visit(ModuleQualifierAST* ast) = 0;
  virtual void visit(ModulePartitionAST* ast) = 0;
  virtual void visit(ImportNameAST* ast) = 0;
  virtual void visit(InitDeclaratorAST* ast) = 0;
  virtual void visit(DeclaratorAST* ast) = 0;
  virtual void visit(UsingDeclaratorAST* ast) = 0;
  virtual void visit(EnumeratorAST* ast) = 0;
  virtual void visit(TypeIdAST* ast) = 0;
  virtual void visit(HandlerAST* ast) = 0;
  virtual void visit(BaseSpecifierAST* ast) = 0;
  virtual void visit(RequiresClauseAST* ast) = 0;
  virtual void visit(ParameterDeclarationClauseAST* ast) = 0;
  virtual void visit(TrailingReturnTypeAST* ast) = 0;
  virtual void visit(LambdaSpecifierAST* ast) = 0;
  virtual void visit(TypeConstraintAST* ast) = 0;
  virtual void visit(AttributeArgumentClauseAST* ast) = 0;
  virtual void visit(AttributeAST* ast) = 0;
  virtual void visit(AttributeUsingPrefixAST* ast) = 0;
  virtual void visit(NewPlacementAST* ast) = 0;
  virtual void visit(NestedNamespaceSpecifierAST* ast) = 0;

  // TemplateParameterAST
  virtual void visit(TemplateTypeParameterAST* ast) = 0;
  virtual void visit(NonTypeTemplateParameterAST* ast) = 0;
  virtual void visit(TypenameTypeParameterAST* ast) = 0;
  virtual void visit(ConstraintTypeParameterAST* ast) = 0;

  // SpecifierAST
  virtual void visit(GeneratedTypeSpecifierAST* ast) = 0;
  virtual void visit(TypedefSpecifierAST* ast) = 0;
  virtual void visit(FriendSpecifierAST* ast) = 0;
  virtual void visit(ConstevalSpecifierAST* ast) = 0;
  virtual void visit(ConstinitSpecifierAST* ast) = 0;
  virtual void visit(ConstexprSpecifierAST* ast) = 0;
  virtual void visit(InlineSpecifierAST* ast) = 0;
  virtual void visit(StaticSpecifierAST* ast) = 0;
  virtual void visit(ExternSpecifierAST* ast) = 0;
  virtual void visit(ThreadLocalSpecifierAST* ast) = 0;
  virtual void visit(ThreadSpecifierAST* ast) = 0;
  virtual void visit(MutableSpecifierAST* ast) = 0;
  virtual void visit(VirtualSpecifierAST* ast) = 0;
  virtual void visit(ExplicitSpecifierAST* ast) = 0;
  virtual void visit(AutoTypeSpecifierAST* ast) = 0;
  virtual void visit(VoidTypeSpecifierAST* ast) = 0;
  virtual void visit(SizeTypeSpecifierAST* ast) = 0;
  virtual void visit(SignTypeSpecifierAST* ast) = 0;
  virtual void visit(VaListTypeSpecifierAST* ast) = 0;
  virtual void visit(IntegralTypeSpecifierAST* ast) = 0;
  virtual void visit(FloatingPointTypeSpecifierAST* ast) = 0;
  virtual void visit(ComplexTypeSpecifierAST* ast) = 0;
  virtual void visit(NamedTypeSpecifierAST* ast) = 0;
  virtual void visit(AtomicTypeSpecifierAST* ast) = 0;
  virtual void visit(UnderlyingTypeSpecifierAST* ast) = 0;
  virtual void visit(ElaboratedTypeSpecifierAST* ast) = 0;
  virtual void visit(DecltypeAutoSpecifierAST* ast) = 0;
  virtual void visit(DecltypeSpecifierAST* ast) = 0;
  virtual void visit(PlaceholderTypeSpecifierAST* ast) = 0;
  virtual void visit(ConstQualifierAST* ast) = 0;
  virtual void visit(VolatileQualifierAST* ast) = 0;
  virtual void visit(RestrictQualifierAST* ast) = 0;
  virtual void visit(EnumSpecifierAST* ast) = 0;
  virtual void visit(ClassSpecifierAST* ast) = 0;
  virtual void visit(TypenameSpecifierAST* ast) = 0;
  virtual void visit(SplicerTypeSpecifierAST* ast) = 0;

  // PtrOperatorAST
  virtual void visit(PointerOperatorAST* ast) = 0;
  virtual void visit(ReferenceOperatorAST* ast) = 0;
  virtual void visit(PtrToMemberOperatorAST* ast) = 0;

  // CoreDeclaratorAST
  virtual void visit(BitfieldDeclaratorAST* ast) = 0;
  virtual void visit(ParameterPackAST* ast) = 0;
  virtual void visit(IdDeclaratorAST* ast) = 0;
  virtual void visit(NestedDeclaratorAST* ast) = 0;

  // DeclaratorChunkAST
  virtual void visit(FunctionDeclaratorChunkAST* ast) = 0;
  virtual void visit(ArrayDeclaratorChunkAST* ast) = 0;

  // UnqualifiedIdAST
  virtual void visit(NameIdAST* ast) = 0;
  virtual void visit(DestructorIdAST* ast) = 0;
  virtual void visit(DecltypeIdAST* ast) = 0;
  virtual void visit(OperatorFunctionIdAST* ast) = 0;
  virtual void visit(LiteralOperatorIdAST* ast) = 0;
  virtual void visit(ConversionFunctionIdAST* ast) = 0;
  virtual void visit(SimpleTemplateIdAST* ast) = 0;
  virtual void visit(LiteralOperatorTemplateIdAST* ast) = 0;
  virtual void visit(OperatorFunctionTemplateIdAST* ast) = 0;

  // NestedNameSpecifierAST
  virtual void visit(GlobalNestedNameSpecifierAST* ast) = 0;
  virtual void visit(SimpleNestedNameSpecifierAST* ast) = 0;
  virtual void visit(DecltypeNestedNameSpecifierAST* ast) = 0;
  virtual void visit(TemplateNestedNameSpecifierAST* ast) = 0;

  // FunctionBodyAST
  virtual void visit(DefaultFunctionBodyAST* ast) = 0;
  virtual void visit(CompoundStatementFunctionBodyAST* ast) = 0;
  virtual void visit(TryStatementFunctionBodyAST* ast) = 0;
  virtual void visit(DeleteFunctionBodyAST* ast) = 0;

  // TemplateArgumentAST
  virtual void visit(TypeTemplateArgumentAST* ast) = 0;
  virtual void visit(ExpressionTemplateArgumentAST* ast) = 0;

  // ExceptionSpecifierAST
  virtual void visit(ThrowExceptionSpecifierAST* ast) = 0;
  virtual void visit(NoexceptSpecifierAST* ast) = 0;

  // RequirementAST
  virtual void visit(SimpleRequirementAST* ast) = 0;
  virtual void visit(CompoundRequirementAST* ast) = 0;
  virtual void visit(TypeRequirementAST* ast) = 0;
  virtual void visit(NestedRequirementAST* ast) = 0;

  // NewInitializerAST
  virtual void visit(NewParenInitializerAST* ast) = 0;
  virtual void visit(NewBracedInitializerAST* ast) = 0;

  // MemInitializerAST
  virtual void visit(ParenMemInitializerAST* ast) = 0;
  virtual void visit(BracedMemInitializerAST* ast) = 0;

  // LambdaCaptureAST
  virtual void visit(ThisLambdaCaptureAST* ast) = 0;
  virtual void visit(DerefThisLambdaCaptureAST* ast) = 0;
  virtual void visit(SimpleLambdaCaptureAST* ast) = 0;
  virtual void visit(RefLambdaCaptureAST* ast) = 0;
  virtual void visit(RefInitLambdaCaptureAST* ast) = 0;
  virtual void visit(InitLambdaCaptureAST* ast) = 0;

  // ExceptionDeclarationAST
  virtual void visit(EllipsisExceptionDeclarationAST* ast) = 0;
  virtual void visit(TypeExceptionDeclarationAST* ast) = 0;

  // AttributeSpecifierAST
  virtual void visit(CxxAttributeAST* ast) = 0;
  virtual void visit(GccAttributeAST* ast) = 0;
  virtual void visit(AlignasAttributeAST* ast) = 0;
  virtual void visit(AlignasTypeAttributeAST* ast) = 0;
  virtual void visit(AsmAttributeAST* ast) = 0;

  // AttributeTokenAST
  virtual void visit(ScopedAttributeTokenAST* ast) = 0;
  virtual void visit(SimpleAttributeTokenAST* ast) = 0;
};

}  // namespace cxx
