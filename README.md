# FunctionEntropy
Erases all function instructions in memory after usage, used to improve program security and make the life of reverse engineers more annoying.

You will have to create a stub function the same type as the real function. The stub function will have to be declared before the real function. 

example:

```cpp
void importantFunctionStub(){}
void importantFunction(){int x = 0; std::cout << x+1 << std::endl;}
int main() {
	 // Get function sizes and memory addresses
	thunderbolt::c_function function(importantFunction, importantFunctionStub);
	thunderbolt::c_entropy entropy;
	 // Add to entropy clear list
	entropy.add_element(function);
	 // Call function
	importantFunction();
	 // Erase function
	entropy.erase_functions();
	Sleep(5000);
	return 0;
}
```
