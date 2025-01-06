/*  Name: Jacob Sherlin
    Date: 11 November 2024
    Course: CSCI-4160-001
    Project: Project #5
    Project Description: Use symbol tables to detect basic semantic errors, including undefined type/variable/function names and redefined type/variable names. 
*/ 

#include "TypeChecking.h"
#include "Absyn.h"

using namespace absyn;

namespace semantics
{
	const types::Type*  TypeChecking::visit_student(const SimpleVar* v)
	{
		//your implementation here
		/* check if the variable is defined by looking up the symbol table*/
        if (!env.getVarEnv()->contains(v->getName())){
            error(v, "undefined variable");
        }
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const SubscriptVar* v)
	{
		//your implementation here
		/* check both the variable and index */
        const types::Type* var = visit(v->getVar());
        const types::Type* index = var ? visit(v->getIndex()) : nullptr;
        if (!var || !index)
            return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const OpExp* e)
	{
        //your implementation here
		/* check both operands */
    	for (const Exp* side : {e->getLeft(), e->getRight()}){
            if (side != nullptr){
                const types::Type* type = visit(side);
            }
        }
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const VarExp* e)
	{
		//your implementation here
		/* check the variable */
		if (const Var* var = e->getVar()){
            visit(var);
        }
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const NilExp* e)
	{
		//don't need to do anything
		return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const IntExp* e)
	{
		//don't need to do anything
		return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const StringExp* e)
	{
		//don't need to do anything
		return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const CallExp* e)
	{
		//your implementation here
		/*
			step 1: check the function name
			step 2: check every argument expression
		*/
		string function = e->getFunc();
        stringstream errorStream;
        //step 1, check function name
        if (!env.getVarEnv()->contains(function)){
            errorStream << "undefined function name";
            error(e, errorStream.str());
        }
        //step 2, check every argument expression
        for (const ExpList* args = e->getArgs(); args != nullptr; args = args->getRest()){
            if (const Exp* head = args->getHead()){
                visit(head);
            }
        }

        return nullptr;
    }

	const types::Type*  TypeChecking::visit_student(const SeqExp* e)
	{
		//your implementation here
		/*	check every expression in the sequence */
        for (const ExpList* expList = e->getList(); expList != nullptr; expList = expList->getRest()){
            if (const Exp* head = expList->getHead()){
                visit(head);
            }
        }
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const AssignExp* e)
	{
		//your implementation here
		/* check both variable and expression */
        //check variable
        if (const Var* var = e->getVar()){
            visit(var);
        }
    
        //check expression
        if (const Exp* exp = e->getExp()){
            visit(exp);
        }
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const IfExp* e)
	{
		//your implementation here
		/* check test condition, then-clause, and else-clause (if exists) */
		for (const Exp* clause : {e->getTest(), e->getThenClause(), e->getElseClause()}){
            if (clause){
                visit(clause);
            }
        }
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const WhileExp* e)
	{
		//your implementation here
		/* check both the test condition and loop-body expression */
		for (const Exp* element : {e->getTest(), e->getBody()}){
            if (element) {
                visit(element);
            }
        }
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const ForExp* e)
	{
		//your implementation here
		/*
			step 1: begin a new scope for variable
			step 2: check var declaration, upper bound expression, and loop-body
			step 3: end the scope
		*/
        //begin new scope
		env.getVarEnv()->beginScope();
        //check the variable declaration
        if (const VarDec* var = e->getVar()){
            visit(var);
        }
    
        //check the upper bound expression
        if (const Exp* hi = e->getHi()){
            visit(hi);
        }
    
        //check the loop body
        if (const Exp* body = e->getBody()){
            visit(body);
        }
    
        //end scope
        env.getVarEnv()->endScope();
        
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const BreakExp* e)
	{
		//don't need to do anything
		return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const LetExp* e)
	{
		//your implementation here
		/*
			step 1: begin a new scope for type and variable/function symbol tables
			step 2: check every declaraion in the decl list
			step 3: check the body expression
			step 4: end the scope for both symbol tables
		*/
        //begin new scope
		env.getTypeEnv()->beginScope();
        env.getVarEnv()->beginScope();
        //check every declaration in decl list
        for (const DecList* decList = e->getDecs(); decList != nullptr; decList = decList->getRest()){
            if (const Dec* head = decList->getHead()){
                visit(head);
            }
        }
        //check body
        if (const Exp* body = e->getBody()){
            visit(body);
        }
        //end scope
        env.getVarEnv()->endScope();
        env.getTypeEnv()->endScope();
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const ArrayExp* e)
	{
		//your implementation here
		/*
			step 1: check the type of the array by looking up the type symbol table
			step 2: check the size expression
			step 3: check the initial expression
		*/
        //check type of array by looking up type symbol table
        string type = e->getType();
        if (!env.getTypeEnv()->contains(type)){
            error(e, "undefined array type");
        }
    
        //check size expression
        if (const Exp* size = e->getSize()){
            const types::Type* sizeType = visit(size);
        }
        //check the initial expression
        if (const Exp* init = e->getInit()){
            visit(init);
        }
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const VarDec* d)
	{
		//your implementation here
		/*
			step 1: insert the variable to the var/function symbol table
			step 2: if the type information is provided, check the type
			step 3: check the initial expression
		*/
        //insert variable into variable/function symbol table
        auto* entry = new symbol::SymTabEntry();
    
        //set members
        entry->node = d;
        entry->level = env.getVarEnv()->getLevel();
        entry->info = nullptr;
        insertVar(d->getName(), *entry);
    
        //if type information is provided check type
        if (const NameTy* type = d->getType()){
            visit(type);
        }
        
        //check the initial expression
        if (const Exp* init = d->getInit()){
            visit(init);
        }
    
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const TypeDec* d)
	{
		//your implementation here
		/*
			step 1: insert the name of the new type to the type symbol table
			step 2: check the type information of the new type
		*/
        //insert name of new type into type symbol table
        for (const TypeDec* current = d; current != nullptr; current = current->getNext()){
            auto* entry = new symbol::SymTabEntry(); 
    
            //assign values to members of the entry
            entry->node = current;
            entry->level = env.getTypeEnv()->getLevel();
            entry->info = nullptr;
    
            insertType(current->getName(), *entry);
        
            //check type information of new type
            if (const Ty* ty = current->getTy()){
                visit(ty);
            }
        }
    
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const NameTy* t)
	{
		//your implementation here
		/*
			step 1: check if the type name is defined by looking up the type symbol table
		*/
        string type = t->getName();
        if (!env.getTypeEnv()->contains(type)){
            error(t, "undefined type name");
        }
        return nullptr;
	}

	const types::Type*  TypeChecking::visit_student(const ArrayTy* t)
	{
		//your implementation here
		/*
			step 1: Check the name of the array type by looking up the type symbol table
		*/
		string type = t->getName();
        if (!env.getTypeEnv()->contains(type)){
            error(t, "undefined array type name");
        }
        return nullptr;

	}
} // end of namespace semantics
