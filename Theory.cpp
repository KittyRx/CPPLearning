#include <iostream>
#include <string>
#include <memory>

/***
Example functions demonstating various C++ features.The nested functions are turned to strings for visual aid when explaining but actual nested functions are not allowed in C++.
This is also writen in a ".cpp" file to indicate the language, make use of the C++ standard library and show the syntax highlighting as well as the correction of code snippets.
***/

void exampleNamespace() {

	//Namespace (allows reusing of entities with same name by using accesing namespaces; kinda wraping them in an object).
	namespace alpha {
		int value = 5;
	};

	namespace beta {
		int value = 10;
	};

	int value = 2;

	//Not declaring namespace will use "local" value.
	std::cout << "Printed value: " << value << std::endl;

	//But declaring namespace will use that "namespace's value".
	std::cout << "Printed value: " << alpha::value << std::endl;

	//Can also declare what "namespace" is used for definitions. Loading the prefix|package before its useage which is later infered by what members are accessed.
	using namespace std;

	/***
	Or, preferably to avoid naming conflicts and unnecessary renaming or memory overhead,
	We can load a specific member of the "namespace" akin to accessing a json file.
	***/
	using std::string;

};

void exampleTypeRenaming() {

	/***
	The "typedef" is used to rename existing data types or give them "nicknames";
	So here "type_standard" of string is renamed to "str_t"; t used to indicate its a type.
	***/
	typedef std::string strTypeDef_t;

	//But the common way of doing it has now changed to "using" for type renaming. Because it also works with templates.
	using strUsing_t = std::string;

	//So here all denominations represent the same type.
	std::string fluff1 = "fluff";
	strTypeDef_t fluff2 = "fluff";
	strUsing_t fluff3 = "fluff";

};

void exampleInputAndOutput() {

	// '::' scope resolution operator; kind of like '.something' in object accessing .
	std::string input;

	// User input assigned to the input variable.
	std::cin >> input;

	// After the user inputs wrong data, we should use "clear" to reset the error flags on input and continue reading.
	std::cin.clear();

	/***
	For longer strings "getline" can be used, if "cin" is preceeding "getline" the "\n" character after user input will be passed on to the second cin inside "getline" user input because of buffering.
	This happens because "cin" reads until the white space character and does not consume the "\n" token at the end which ends up being buffered to the next input operation.
	( Unlike "cin" , "getline" consumes the new line character at the end of the input ).
	To avoid that we can use "ws" to clear the buffer of whitespace characters, before checking for new user input.
	***/
	std::getline(std::cin >> std::ws, input);

	//For further sanitization we use "ignore" to clear the buffer of unwanted characters. The 2 parameters are number of characters to flush OR everything until "\n" is found, hopefuly at the end of the input.
	std::cin.ignore(10000, '\n');

	//And for an even clearer way instead of using an arbitrary number we can define the size of the numeric limits to the maximum stream size, which means everything in the buffer.
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//The "fflush" command forces "cout" to push whatever is inside the buffer before doing anything else. Not recommended for INPUT sanitization.
	std::fflush(stdout);

	//For OUTPUT sanitization we can simply use "endl" to add a new line and flush the buffer.
	std::cout << "output" << std::endl;

};

void exampleOverloadingAndTemplates() {

	//As opposed to TS, where you can declare different optional arguments to overload a function, the cpp overload is:
	std::string "function(int argument) {}";
	std::string "function(std::string argument) {}";
	std::string "function(double argument) {}";

	//But, instead of declaring it like 3 different functions with the same name but different signatures (  name + parameters  ), we can use templates.
	template<typename T>

	/***
	Here "T" is fulfilling the role of a placeholder for the type of argument passed to the function.
	Which will be defined once the function is called with a specific type.
	***/
	std::string "function(T argument) {}";

	//We can either do type comparisons without defining when the type is known, be it at compile time or runtime.
	if (std::is_same_v< T, int typeExpected>) {
		std::string "returnLogic";
	};

	/***
	Or we can use "constexpr" and tell the compiler to only compile if something matches the if condition.
	Meaning it can clean overhead at compile time but can break if used with runtime data checks.
	***/
	if constexpr (std::is_same_v< T, int typeExpected>) {
		std::string "returnLogic";
	}

	/***
	Either way, we then access the type comparison "is_same" and pass parameters of T (type of passed argument) with the expected type.
	And it compares the two data types and creates a boolean value, which we can access as a result with "_v".
	***/

	/***
	Or for multiple types we can use several "typename", since "T" is instanced for local scope of each function (T is different for each different function),
	but not instanced per variable, where ( argument1, argument2 ) might be different types.
	***/
	template<typename S, typename U, typename V>
	std::string "function(S argument1, U argument2, V argument3) {}";

	//And then run comparison and logic based on types inside.
	if (std::is_same_v< S, int typeExpected>) {
		std::string "returnLogic";
	};

	// There is also the alternative of using "auto" for type deduction, but it is compile deduced and not as flexible, its basically lazy typing and slightly safer than using "any" in typescript.
	auto variable = randomType();

};

void exampleArrays() {
	//Arrays can be declared statically or dynamically. And the array can be initialized with values or they can be added later.
	int arrayStaticValues[5] = { 1,2,3,4,5 };

	//Declaring values after initializing array with set size.
	int arrayStaticNoValues[5];
	int arrayStaticNoValues = { 1,2,3,4,5 };

	//Dynamic arrays are allocated memory on the heap at runtime and require dealocation.
	int n = std::cin.get();
	int* arrayDynamic = new int[n];

	//To avoid manual memory management use of smart pointers is recommended.
	std::unique_ptr<int[]> arrayName(new int[n]);
};
