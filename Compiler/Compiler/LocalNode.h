
namespace Compiler {

	/*!
	local_vars
	parameters
	*/

	class LocalNode
	{
	public:// functions 
		std::string GetSymblo();
		std::string GetType();
		SymbolCategory GetSymbolCategory();
		uint32_t GetDimension();
		void * GetVal();
		LocalNode *GetLocalNode();
		// all setters 
		void	SetSymbol(const char *Symblo);
		void	SetType(const char *TypeName);
		void	SetSymbolCategory(SymbolCategory SymbolCategory);
		void	SetDimension(uint32_t Dim);
		void	SetValPtr(void *ptr);
		void	SetLocalNode(LocalNode *ptr);
	private:// variables 
		//! holds the symbol
		string m_Symbol;
		//! to know the type of var/function that being held  
		string m_Type;
		//! to know which symbol
		SymbolCategory m_SymbolCategory;
		//! Dimension
		uint32_t m_Dimension = 0;
		//! will be used to hold the value 
		void * mptr_Val;
		//! used to for keeping track of var in a function or thing not the global scope
		LocalNode *mptr_NextNode = nullptr;
	};

}