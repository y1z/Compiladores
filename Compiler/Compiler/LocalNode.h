namespace Compiler {

	/*!
	\brief this class contains the following values 
	local_vars
	parameters
	*/

	class LocalNode
	{
	public:
		LocalNode();
		~LocalNode();

	public:// functions 
		std::string GetFunctionName();
		std::string GetType(); 
		string GetSymbol() const;
		SymbolCategory GetSymbolCategory();
		int32_t GetDimension();
		uint32_t GetLineNum();
		void * GetVal();
		LocalNode *GetLocalNode();

		string TraslateSymbolCategory(SymbolCategory SymCat);
		string GetDataForCompiler();
		// all setters 
		void	SetFunctionName(const char *Symblo);
		void	SetSymbol(const char *Symblo);
		void	SetType(const char *TypeName);
		void	SetSymbolCategory(SymbolCategory SymbolCategory);
		void	SetDimension(int32_t Dim);
		void	SetLineNum(uint32_t Num);
		void	SetValPtr(void *ptr);
		void	SetLocalNode(LocalNode *ptr);
	private:// variables 
		//! holds the symbol
		string m_Function;
		//! can by param or local_var 
		string m_Symbol;
		//! to know the type of var/function that being held  
		string m_Type;
		//! to know which symbol
		SymbolCategory m_SymbolCategory;
		//! how many elements an array has.
		int32_t m_Dimension = 0;
		//! where the symbol is found 
		uint32_t m_LineNum = 0;
		//! will be used to hold the value 
		void * mptr_Val;
		//! used to for keeping track of var in a function or thing not the global scope
		LocalNode *mptr_NextNode = nullptr;

	};

}