# Detecting-Semantic-Errors
Use symbol tables to detect the following basic semantic errors: undefined type/variable/function names and redefined type/variable names.

Classes in this project
Several classes are defined in different namespace for various purposes. Here is a short explanation of
each class.
• Class absyn::Absyn and all its children are used to define types of nodes in the abstract syntax
tree.
• Class template symbol::SymbolTable provides the implementation of symbol tables used in
this course.
• Class types::Type and all its children represent types supported by tiger languages. We are not
going to use them in this project. But we need them to ensure the syntax is correct, and no
change is needed for the next project.
• Structure symbol::SymTabEntry provides information that should be tied with a
variable/function/type name in the SymbolTable. The SymTabEntry contains three
information: the level of the associated name in the source program, a pointer to the type
information of the name, and a pointer to the AST node that contains the
variable/function/type.
• Class symbol::Env provides the compile environment for Tiger language. It has two member
data of symbol::SymbolTable<SymTabEntry>, one to store variable/function information,
and one to store type information as specified by Tiger language manual. Its constructor will
insert all global functions like print, ord into variable symbol table, and built-in data types
like int, and string into type symbol table.
• Class semantics::TypeChecking provides functions to check semantic errors at each node in
the abstract syntax tree..
