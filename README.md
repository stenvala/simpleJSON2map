simpleJSON2map
==============

json_spirit is awesome library for dealing with JSON files in C++. 
However, very often one requires just basic functionality: 
initialize variables from JSON and test if keys exists, maybe objects are nested to depth of two only,
there might be array of objects etc. 
Also, JSON files might not be terribly large.
This library uses json_spirit to offer such basic functionality (and something more). 
It converts JSON files to a recursive map structure and offers basic functionality and allows one to do whatever they want with json_spirit.  
Most of the stuff here could be done easily with mValue, but some methods here might be easier to use and when you just need JSON to configure your program easily, this might work for you.

Basic functionality (see main.cpp for further examples):

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
You may go down as many nested levels as you want with the vector. If there is array, you cannot index it but you need to retrieve it. Or from an array, you can initialize a vector of json2map objects.

You can retrieve the basic variable with the same syntax as testing the keys from the object

```
double value = json->getValue<double>("number","subcell");
```

Or you can fetch a vector

```
std::vector<int> temp = json->getVector<int>("array","subcell")
```

But all the values in the vector needs to be of same type. However, you can also ask for json_value::Value type variable.

If you have an array of different types, or objects, you can retrieve it with

```
json_spirit::Value value = json->getValue("something","subcell");
```

The data stored in JSON is dislayed with

```
json->prettyPrint();
```