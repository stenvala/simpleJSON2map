simpleJSON2map
==============

json_spirit is awesome library for dealing with JSON files in C++. 
However, very often one requires just basic functionality: 
initialize variables from JSON and test if keys exists, maybe objects are nested to depth of two only. 
This library uses json_spirit to offer such basic functionality (and something more). 
It converts JSON files to a recursive map structure and offers basic functionality and allows one to do whatever they want with json_spirit.  Most of the stuff here could be done easily with mValue, but some things here might be easier to use.

Basic functionality:

Init

```
json::json2map *json = new json::json2map(inputFile);  
```

inputFile is a fileName, but you may as well construct the object with json_spirit::Value type variable.


Three ways to test if key exists

```
json->keyExists("key1")
json->keyExists("key2","key1")

std::vector<std::string> stack;
stack.push_back("key3");
stack.push_back("key2");
stack.push_back("key1");
json->keyExists(stack);

```
You may go down as many nested levels as you want with the vector. If there is array, you cannot index it but you need to retrieve it.

Then, you can retrieve the basic variable with the same syntax from the object

```
double value = json->getValue<double>("number","subcell");
```

Or you can fetch a vector

```
std::vector<int> temp = json->getVector<int>("array","subcell")
```

But all the values in the vector needs to be of same type. If you want to have the json_spirit::Value call

```
json->getRoot();
```

If you have array of different types, or objects, you can retrieve it with

```
json_spirit::Value value = json->getValue("something","subcell");
```

The data stored in json is dislayed with

```
json->prettyPrint();
```