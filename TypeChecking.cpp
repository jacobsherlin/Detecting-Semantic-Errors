#include "TypeChecking.h"
#include "Absyn.h"

#define student_version visit_student
#define teacher_version visit_teacher

namespace semantics
{
	const string			TypeChecking::breakSign = "breaksign";

	const types::INT*		TypeChecking::int_type = new types::INT();
	const types::STRING*	TypeChecking::str_type = new types::STRING();
	const types::NIL*		TypeChecking::nil_type = new types::NIL();
	const types::VOID*		TypeChecking::void_type = new types::VOID();

	void TypeChecking::error(const Absyn* a, string msg)
	{
		errormsg->error(a->getLineno(), a->getColno(), msg);
		errorFlag = true;
	}

	bool TypeChecking::hasSemanticError() const
	{
		return errorFlag;
	}

	void TypeChecking::checkInt(const types::Type* et, const Absyn* a) {
		if (!et->coerceTo(int_type))
			error(a, "int required");
	}

	//insert a variable into the var/function symbol table
	void TypeChecking::insertVar(string name, symbol::SymTabEntry entry)
	{
		string			msg;
		stringstream	ss(msg);

		if (env.getVarEnv()->localContains(name))
		{
			symbol::SymTabEntry		old = env.getVarEnv()->lookup(name);
			ss << "variable " << name << " is already defined at line " << old.node->getLineno();
			error(entry.node, ss.str());

		}
		else
			env.getVarEnv()->insert(name, entry);
	}

	//insert a function into the var/function symbol table
	void TypeChecking::insertFunc(string name, symbol::SymTabEntry entry)
	{
		string			msg;
		stringstream	ss(msg);

		if (env.getVarEnv()->localContains(name))
		{
			symbol::SymTabEntry		old = env.getVarEnv()->lookup(name);
			ss << "function " << name << " is already defined at line " << old.node->getLineno();
			error(entry.node, ss.str());

		}
		else
			env.getVarEnv()->insert(name, entry);
	}

	//insert a type into the type symbol table
	void TypeChecking::insertType(string name, symbol::SymTabEntry entry)
	{
		string			msg;
		stringstream	ss(msg);

		if (env.getTypeEnv()->localContains(name))
		{
			symbol::SymTabEntry		old = env.getTypeEnv()->lookup(name);
			ss << "variable " << name << " is already defined at line " << old.node->getLineno();
			error(entry.node, ss.str());

		}
		else
			env.getTypeEnv()->insert(name, entry);
	}

	const types::Type* TypeChecking::visit(const Absyn* v)
	{
		if (dynamic_cast<const Exp*>(v) != NULL)
			visit(dynamic_cast<const Exp*>(v));
		else if (dynamic_cast<const Var*>(v) != NULL)
			visit(dynamic_cast<const Var*>(v));
		else if (dynamic_cast<const Dec*>(v) != NULL)
			visit(dynamic_cast<const Dec*>(v));
		else
			throw runtime_error("invalid node");
	}

	const types::Type* TypeChecking::visit(const Exp* e)
	{
		if (dynamic_cast<const OpExp*>(e) != NULL)			visit((const OpExp*)e);
		else if (dynamic_cast<const VarExp*>(e) != NULL)	visit((const VarExp*)e);
		else if (dynamic_cast<const NilExp*>(e) != NULL)	visit((const NilExp*)e);
		else if (dynamic_cast<const IntExp*>(e) != NULL)	visit((const IntExp*)e);
		else if (dynamic_cast<const StringExp*>(e) != NULL) visit((const StringExp*)e);
		else if (dynamic_cast<const CallExp*>(e) != NULL)	visit((const CallExp*)e);
//		else if (dynamic_cast<const RecordExp*>(e) != NULL) visit((const RecordExp*)e);
		else if (dynamic_cast<const SeqExp*>(e) != NULL)	visit((const SeqExp*)e);
		else if (dynamic_cast<const AssignExp*>(e) != NULL) visit((const AssignExp*)e);
		else if (dynamic_cast<const IfExp*>(e) != NULL)		visit((const IfExp*)e);
		else if (dynamic_cast<const WhileExp*>(e) != NULL)	visit((const WhileExp*)e);
		else if (dynamic_cast<const ForExp*>(e) != NULL)	visit((const ForExp*)e);
		else if (dynamic_cast<const BreakExp*>(e) != NULL)	visit((const BreakExp*)e);
		else if (dynamic_cast<const LetExp*>(e) != NULL)	visit((const LetExp*)e);
		else if (dynamic_cast<const ArrayExp*>(e) != NULL)	visit((const ArrayExp*)e);
		else throw new runtime_error("TypeChecking.visit(Exp*)");
	}

	const types::Type* TypeChecking::visit(const Var* v)
	{
		if (dynamic_cast<const SimpleVar*>(v) != NULL)			visit((const SimpleVar*)v);
//		else if (dynamic_cast<const FieldVar*>(v) != NULL)		visit((const FieldVar*)v);
		else if (dynamic_cast<const SubscriptVar*>(v) != NULL) visit((const SubscriptVar*)v);
		else throw new runtime_error("TypeChecking.visit(Var*)");
	}

	const types::Type* TypeChecking::visit(const Dec* d)
	{
		if (dynamic_cast<const TypeDec*>(d) != NULL)			visit((const TypeDec*)d);
		else if (dynamic_cast<const VarDec*>(d) != NULL)		visit((const VarDec*)d);
//		else if (dynamic_cast<const FunctionDec*>(d) != NULL)	visit((const FunctionDec*)d);
		else throw new runtime_error("TypeChecking.visit(Dec*)");
	}

	const types::Type* TypeChecking::visit(const Ty* t)
	{
		if (dynamic_cast<const NameTy*>(t) != NULL)			visit((const NameTy*)t);
		else if (dynamic_cast<const ArrayTy*>(t) != NULL)		visit((const ArrayTy*)t);
//		else if (dynamic_cast<const RecordTy*>(t) != NULL)		visit((const RecordTy*)t);
		else throw new runtime_error("TypeChecking.visit(Ty*)");
	}

	//The following functions decides which version will be used.

	const types::Type* TypeChecking::visit(const SimpleVar* v)
	{
		return student_version(v);
	}


	const types::Type* TypeChecking::visit(const SubscriptVar* v)
	{
		return student_version(v);
	}

	const types::Type* TypeChecking::visit(const OpExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const VarExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const NilExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const IntExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const StringExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const CallExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const SeqExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const AssignExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const IfExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const WhileExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const ForExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const BreakExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const LetExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const ArrayExp* e)
	{
		return student_version(e);
	}

	const types::Type* TypeChecking::visit(const VarDec* d)
	{
		return student_version(d);
	}

	const types::Type* TypeChecking::visit(const TypeDec* d)
	{
		return student_version(d);
	}

	const types::Type* TypeChecking::visit(const NameTy* t)
	{
		return student_version(t);
	}

	const types::Type* TypeChecking::visit(const ArrayTy* t)
	{
		return student_version(t);
	}


} // end of namespace semantics
