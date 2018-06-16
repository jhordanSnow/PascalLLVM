#include <headders/ast.h>
#include<string>
#include<list>

// Node
Node::Node(){};

// program
Program::Program(ProgramHeading* programHeading, Block* block) : Node() {
   this->programHeading = programHeading;
   this->block = block;
}

// program heading
ProgramHeading::ProgramHeading(std::string identifier) : Node() {
   this->identifier = identifier;
}


// block
Block::Block(DeclarationPart* declarationPart, StatementPart* statementPart) : Node() {
   this->declarationPart = declarationPart;
   this->statementPart = statementPart;
}

// declarationPart
DeclarationPart::DeclarationPart(TypeDefinitionPart* typeDefinitionPart) : Node() {
   this->typeDefinitionPart = typeDefinitionPart;
}

DeclarationPart::DeclarationPart(VariableDeclarationPart* variableDeclarations) : Node() {
   this->variableDeclarations = variableDeclarations;
}

DeclarationPart::DeclarationPart(ProcFuncDeclarationPart*  procFuncDeclarationPart) : Node() {
   this->procFuncDeclarationPart = procFuncDeclarationPart;
}

// procedure and function declaration part
ProcFuncDeclarationPart::ProcFuncDeclarationPart(std::list<ProcFuncDeclaration>* procFuncDeclarations) : Node() {
   this->procFuncDeclarations = procFuncDeclarations;
}

// Varaible declaration part
VariableDeclarationPart::VariableDeclarationPart(std::list<VariableDeclaration>* variableDeclarations) : Node() {
   this->variableDeclarations = variableDeclarations;
}

//Type definition part
TypeDefinitionPart::TypeDefinitionPart(std::list<TypeDefinition>* typeDefinitions) : Node(){
   this->typeDefinitions = typeDefinitions;
}

// Procedure and Function Declaration
ProcFuncDeclaration::ProcFuncDeclaration(ProcDeclaration* procDeclaration) : Node(){
   this->procDeclaration = procDeclaration;
}

ProcFuncDeclaration::ProcFuncDeclaration(FuncDeclaration* funcDeclaration) : Node(){
   this->funcDeclaration = funcDeclaration;
}

// Procedure Declaration
ProcDeclaration::ProcDeclaration(ProcHeading* procHeading, ProcBody* procBody) : Node(){
   this->procHeading = procHeading;
   this->procBody = procBody;
}

// Function Declaration
FuncDeclaration::FuncDeclaration(FunctionHeading* functionHeading, FunctionBody* functionBody) : Node(){
   this->functionHeading = functionHeading;
   this->functionBody = functionBody;
}

// Type Definition
TypeDefinition::TypeDefinition(std::string identifier, DataType* dataType) : Node(){
   this->identifier = identifier;
   this->dataType = dataType;
}

// VariableDeclaration
VariableDeclaration::VariableDeclaration(std::list<std::string>* identifierList, DataType* dataType) : Node(){
   this->identifierList = identifierList;
   this->dataType = dataType;
}

// Proc Body
ProcBody::ProcBody(Block* block) : Node(){
   this->block = block;
}

// Proc Heading
ProcHeading::ProcHeading(std::string identifier, FormalParameterList* parameterList) : Node() {
   this->identifier = identifier;
   this->parameterList = parameterList;
}

ProcHeading::ProcHeading(std::string identifier) : Node() {
   this->identifier = identifier;
}

// function body
FunctionBody::FunctionBody(Block* block) : Node() {
   this->block = block;
}

// function headding
FunctionHeading::FunctionHeading(std::string identifier, FormalParameterList* parameterList, ResultType* resultType) : Node() {
   this->identifier = identifier;
   this->parameterList = parameterList;
   this->resultType = resultType;
}

FunctionHeading::FunctionHeading(std::string identifier, ResultType* resultType) : Node() {
   this->identifier = identifier;
   this->resultType = resultType;
}

// Formal Parameter List
FormalParameterList::FormalParameterList(std::list<FormalParameterSection>* formalParameterSection) : Node() {
   this->formalParameterSection = formalParameterSection;
}

// Formal Parameter Section
FormalParameterSection::FormalParameterSection(ValueParameterSection* valueParameterSection) : Node() {
   this->valueParameterSection = valueParameterSection;
}

// Value Parameter Section
ValueParameterSection::ValueParameterSection(std::list<std::string> identifierList, ConformantArraySchema* conformantArraySchema) : Node() {
   this->identifierList = identifierList;
   this->conformantArraySchema = conformantArraySchema;
}

// Result Type
ResultType::ResultType(std::string typeIdentifier) : Node() {
   this->typeIdentifier = typeIdentifier;
}

// Parameter Type
ParameterType::ParameterType(ConformantArraySchema* conformantArraySchema) : Node() {
   this->conformantArraySchema = conformantArraySchema;
}

ParameterType::ParameterType(std::string typeIdentifier) : Node() {
   this->typeIdentifier = typeIdentifier;
}

// Conformant Array Schema
ConformantArraySchema::ConformantArraySchema(ArraySchema*  arraySchema) : Node() {
   this->arraySchema = arraySchema;
}

ArraySchema::ArraySchema(std::string typeIdentifier) : Node() {
   this->typeIdentifier = typeIdentifier;
}

ArraySchema::ArraySchema(ConformantArraySchema* conformantArraySchema) : Node() {
   this->conformantArraySchema = conformantArraySchema;
}

ArraySchema::ArraySchema(BoundSpecification* boundSpecification, std::string typeIdentifier) : Node() {
   this->boundSpecification = boundSpecification;
   this->typeIdentifier = typeIdentifier;
}

ArraySchema::ArraySchema(BoundSpecification* boundSpecification, ConformantArraySchema* conformantArraySchema) : Node() {
   this->boundSpecification = boundSpecification;
   this->conformantArraySchema = conformantArraySchema;
}

//Bound Specification
BoundSpecification::BoundSpecification(std::string identifier1, std::string identifier2, std::string ordinalTypeIdentifier) : Node() {
   this->identifier1 = identifier1;
   this->identifier2 = identifier2;
   this->ordinalTypeIdentifier = ordinalTypeIdentifier;
}

#if false
//macros
//^yiwPa::f;s {
//kf(yi)jVp:s/, /\n/€kb€kbr/g€kbeVi}^:normal daWVi}^:normal yaWA = pA;Vi{^I	this->
#endif
