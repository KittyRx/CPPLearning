#include <iostream>
#include <string>
#include <memory>

/***
Example functions demonstating various C++ features.The nested functions are turned to strings for visual aid when explaining but actual nested functions are not allowed in C++.
This is also writen in a ".cpp" file to indicate the language, make use of the C++ standard library and show the syntax highlighting as well as the correction of code snippets.
***/

// Namespace (allows reusing of entities with same name by using accesing namespaces; kinda wraping them in an object).
namespace alpha
{
	int value = 5;
};

namespace beta
{
	int value = 10;
};

void exampleNamespace()
{

	int value = 2;

	// Not declaring namespace will use "local" value.
	std::cout << "Printed value: " << value << std::endl;

	// But declaring namespace will use that "namespace's value".
	std::cout << "Printed value: " << alpha::value << std::endl;

	// Can also declare what "namespace" is used for definitions. Loading the prefix|package before its useage which is later infered by what members are accessed.
	using namespace std;

	/***
	Or, preferably to avoid naming conflicts and unnecessary renaming or memory overhead,
	We can load a specific member of the "namespace" akin to accessing a json file.
	***/
	using std::string;
};

void exampleTypeRenaming()
{

	/***
	The "typedef" is used to rename existing data types or give them "nicknames";
	So here "type_standard" of string is renamed to "str_t"; t used to indicate its a type.
	***/
	typedef std::string strTypeDef_t;

	// But the common way of doing it has now changed to "using" for type renaming. Because it also works with templates.
	using strUsing_t = std::string;

	// So here all denominations represent the same type.
	std::string fluff1 = "fluff";
	strTypeDef_t fluff2 = "fluff";
	strUsing_t fluff3 = "fluff";
};

void exampleInputAndOutput()
{

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

	// For further sanitization we use "ignore" to clear the buffer of unwanted characters. The 2 parameters are number of characters to flush OR everything until "\n" is found, hopefuly at the end of the input.
	std::cin.ignore(10000, '\n');

	// And for an even clearer way instead of using an arbitrary number we can define the size of the numeric limits to the maximum stream size, which means everything in the buffer.
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// The "fflush" command forces "cout" to push whatever is inside the buffer before doing anything else. Not recommended for INPUT sanitization.
	std::fflush(stdout);

	// For OUTPUT sanitization we can simply use "endl" to add a new line and flush the buffer.
	std::cout << "output" << std::endl;
};

// But, instead of declaring it like 3 different functions with the same name but different signatures (  name + parameters  ), we can use templates.
template <typename T>

void exampleOverloadingAndTemplates()
{

	// As opposed to TS, where you can declare different optional arguments to overload a function, the cpp overload is:
	std::string example = "int function(int argument) {}";
	std::string example = "std::string function(std::string argument) {}";
	std::string example = "double function(double argument) {}";

	/***
	Here "T" is fulfilling the role of a placeholder for the type of argument passed to the function.
	Which will be defined once the function is called with a specific type.
	***/
	std::string example = "dataType function(T argument) {}";

	// We can either do type comparisons without defining when the type is known, be it at compile time or runtime.
	if (std::is_same_v<T, int typeExpected>)
	{
		std::string example = "return dataType Logic";
	};

	/***
	Or we can use "constexpr" and tell the compiler to only compile if something matches the if condition.
	Meaning it can clean overhead at compile time but can break if used with runtime data checks.
	***/
	if constexpr (std::is_same_v<T, int typeExpected>)
	{
		std::string example = "return dataType Logic";
	}

	/***
	Either way, we then access the type comparison "is_same" and pass parameters of T (type of passed argument) with the expected type.
	And it compares the two data types and creates a boolean value, which we can access as a result with "_v".
	***/

	/***
	Or for multiple types we can use several "typename", since "T" is instanced for local scope of each function (T is different for each different function),
	but not instanced per variable, where ( argument1, argument2 ) might be different types.
	***/
	template <typename S, typename U, typename V>
	std::string example = "dataType function(S argument1, U argument2, V argument3) {}";

	// And then run comparison and logic based on types inside.
	if (std::is_same_v<S, int typeExpected>)
	{
		std::string example = "return Logic";
	};

	// There is also the alternative of using "auto" for type deduction, but it is compile deduced and not as flexible, its basically lazy typing and slightly safer than using "any" in typescript.
	auto variable = randomType();
};

void exampleArrays()
{

	// Arrays can be declared statically or dynamically. And the array can be initialized with values or they can be added later.
	int arrayStaticValues[5] = {1, 2, 3, 4, 5};

	// Declaring values after initializing array with set size.
	int arrayStaticNoValues[5] = {};
	int arrayStaticNoValues[5] = {1, 2, 3, 4, 5};

	// Dynamic arrays are allocated memory on the heap at runtime and require dealocation.
	int n = std::cin.get();
	int *arrayDynamic = new int[n];

	// To avoid manual memory management use of smart pointers is recommended.
	std::unique_ptr<int[]> arrayName(new int[n]);

	// Can use "sizeof" to determine the size of array in bytes.
	sizeof(arrayStaticValues);

	// This can also be used to determine the number of elements in a static array.
	std::string strings[] = {"one", "two", "three"};
	sizeof(strings) / sizeof(std::string);
	sizeof(strings) / sizeof(strings[0]);

	// When passing an array to a function it decays to a pointer so the sizeof does not work as expected.
	std::string example = "std::string function(std::string strings[]){}";

	// Minimal detail I never use when looping
	for (std::string string : strings)
	{
	};

	// Arrays can also be multi dimensional, akin to matrixes.
	std::string elements[3][3] = {
		{"one", "two", "three"},
		{"four", "five", "six"},
		{"seven", "eight", "nine"}};

	// Which can be used similarly to an ECS system for entity component storage or movement logic.
	enum ComponentIndex
	{
		POS_X,
		POS_Y,
		POS_Z,
		VEL_X,
		VEL_Y,
		VEL_Z,
		COUNT
	};

	// We might want to also declare this dynamically later on but for now its a static value to showcase the concept.
	const int ENTITY_COUNT = 2;

	// We can either declare "component_count" or use the safer "count" method and access it as a member of the enum.
	float movementLogic[ENTITY_COUNT][ComponentIndex::COUNT] = {
		{1.0f, 2.0f, 3.0f, 0.1f, 0.2f, 0.3f}, // Entity 0
		{4.0f, 5.0f, 6.0f, 0.4f, 0.5f, 0.6f}, // Entity 1
	};

	// So here accesing position of entity 1 on the Y axis would be:
	float entity1POS_Y = movementLogic[1][ComponentIndex::POS_Y]; // Outputs 5.0f

	// And if we really wanted to create a key value sort of system in multidimensional arrays we can always just use 2 enums.
	enum entityIndex
	{
		ENTITY_0,
		ENTITY_1,
	};

	// And then access it accordingly.
	float entity0POS_Z = movementLogic[entityIndex::ENTITY_0][ComponentIndex::POS_Z]; // Outputs 3.0f
};

void memory()
{

	// Memory can be accessed with &.
	int age = 99;

	// Like so.
	std::cout << &age << std::endl;

	/***
	Pasing arguments to a function is usually done by value which copies the original values of the arguments.
	In order to change the original values, we pass by reference "&value" or by pointer.
	***/ 
	std::string name = "NameCreative";

	//  "*" dereferencing value and pointing at its address "&".
	std::string *pName = &name;

	// Always initialize manual pointers even if its with "nullptr" and check if the pointer was assigned an address before "*" dereferencing.
	int *pointer = nullptr;
};
