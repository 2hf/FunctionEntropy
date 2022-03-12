	class c_function {
	public:
		void* m_nFunc;
		DWORD m_dwSize;
		c_function(void* func, void* stub) {
			this->m_nFunc = func;
#ifdef DEBUG
			std::cout << "{+} got function\n";
#endif
			this->m_dwSize = get_size(func, stub);
#ifdef DEBUG
			std::cout << "{+} got function size\n";
#endif
		}

		DWORD get_size(void* Function, void* Stub) {
			DWORD dwFuncSize = 0, dwOldProtect;
			DWORD* fnA, * fnB;
			fnA = (DWORD*)Function;
			fnB = (DWORD*)Stub;
			dwFuncSize = fnB - fnA;
			VirtualProtect(fnA, dwFuncSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
			return dwFuncSize;
		}
	};

	class c_entropy {
	public:
		std::deque<c_function> m_arrFunctions;
		void add_element(c_function x) {
			m_arrFunctions.push_back(x);
#ifdef DEBUG
			std::cout << "{+} added function to array\n";
#endif
		}
		void erase_functions() {
			if (!m_arrFunctions.size())
				return;
			for (auto at : m_arrFunctions) {
#ifdef DEBUG
				std::cout << "{+} function addr: " << at.m_nFunc << std::endl;
#endif
				* (byte*)at.m_nFunc = 0xC3;
#ifdef DEBUG
				std::cout << "{+} inserted retn to function\n";
#endif
				DWORD oldProtect;
				VirtualProtect(at.m_nFunc, at.m_dwSize, PAGE_EXECUTE_READWRITE, &oldProtect);
				memset(at.m_nFunc, 0xcc, at.m_dwSize);
#ifdef DEBUG
				std::cout << "{+} erased function\n";
#endif
			}
		}
	};
};
