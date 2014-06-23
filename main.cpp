// See the LICENSE file for license information. 
//
// Created by Antti Stenvall <antti@stenvall.fi>.
//
// This is test file for testing json2map class. This works out as a tutorial too!
// 

#include <cstdlib>
#include "json2map.h"

int main(int argc, char **argv) {
  if (argc < 2){
    std::cout << "Call this as ./main json-inputfile" << std::endl;
    return EXIT_SUCCESS;
  }  
  // read JSON file name from command line parameter (test.json included in the repo)
  std::string inputFile = std::string(argv[1]);
  // init json2map structure
  json::json2map *json = new json::json2map(inputFile);      
  // print all that is inside the json
  json->prettyPrint();
  std::cout << std::endl << std::endl;
  // exaple of testing keys
  if (!json->keyExists("notDefined")){
    std::cout << "Given key does not exists" << std::endl;
  }  
  if (json->keyExists("pi","data")){    
    // init double from json to a variable
    double d = json->getValue<double>("pi","data");
    std::cout << "Double: " << d << std::endl;
  }  
  if (json->keyExists("firstNumbers","data")){
    // retrieve vector of values
    std::vector<int> temp = json->getVector<int>("firstNumbers","data");
    std::cout << "Array" << std::endl;
    for (unsigned int i=0;i<temp.size();i++){
      std::cout << "Value " << i << ": " << temp.at(i) << std::endl;
    }
  }    
  // test value types
  std::vector<std::string> empty;
  std::cout << "Value type of root is: " << json->getValueType(empty) << std::endl;
  if (json->keyExists("temp")){
    std::cout << "Value type of temp is: " << json->getValueType("temp") << std::endl;
  }
  if (json->keyExists("name")){
    std::cout << "Value type of name is: " << json->getValueType("name") << std::endl;
  }
  // init vector of json2maps from an existing value in json2map, note the valueType comparison
  if (json->keyExists("characters") && 
          json->getValueType("characters") == json_spirit::array_type){
    std::vector<json::json2map*> jsonV = json->getVector("characters");
    for (unsigned int i=0; i < jsonV.size(); i++){
      // be loose with existence
      std::cout << "Value " << i << ":" <<
              " name: " << jsonV.at(i)->getValue<std::string>("name") <<
              " born: " <<  jsonV.at(i)->getValue<int>("born") <<
              std::endl;
    }
    // delete array
    while (jsonV.size() > 0){
      delete jsonV.at(jsonV.size()-1);
      jsonV.pop_back();
    }
  }  
  delete json;
  return EXIT_SUCCESS;
}
