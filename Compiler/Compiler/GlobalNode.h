#include "stdafx.h"
#include "LocalNode.h"
namespace Compiler {

	/*!
		contains 
		functions and global vars 
	*/

	class GlobalNode
	{
	public:// constructors 
		GlobalNode();
		~GlobalNode();
	public:// functions

		std::string GetSymblo();
		std::string GetType();
		SymbolCategory GetSymbolCategory();
		int32_t GetDimension();
		uint32_t GetLineNum();
		void * GetVal();
		LocalNode *GetLocalNode();

		string TraslateSymbolCategory(SymbolCategory SymCat);

		string GetDataForCompiler();

		void AddLocalNode(LocalNode *Node);

		//! to see if a symbol already exist 
		bool Search(const string &Symbol);
		// all setters 
		void	SetSymbol(const char *Symblo);
		void	SetType(const char *TypeName);
		void	SetSymbolCategory(SymbolCategory SymbolCategory);
		void	SetDimension(int32_t Dim);
		void	SetValPtr(void *ptr);
		void	SetLocalNode(LocalNode *ptr);
		void	SetLineNum(uint32_t Num);
	private:// variables 
		//! holds the symbol
		string m_Symbol;
		//! to know the type of var/function that being held  
		string m_Type;
		//! to know which symbol
		SymbolCategory m_SymbolCategory;
		//! Dimension
		int32_t m_Dimension = 0;
		//! will be used to hold the value 
		void * mptr_Val;
		//! used to for keeping track of var in a function or thing not the global scope
		LocalNode *mptr_LocalNode = nullptr;
		//! line where the symbol is found 
		uint32_t m_LineNum = 0;
	};

}