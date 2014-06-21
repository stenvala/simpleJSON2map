/* 
 * Test file for testing json2map class 
 * 
 */

#include <cstdlib>
#include "json2map.h"

int main(int argc, char **argv) {
  if (argc < 2){
    std::cout << "Call this as ./main json-inputfile" << std::endl;
    return EXIT_SUCCESS;
  }  
  std::string inputFile = std::string(argv[1]);
  // init json2map structure
  json::json2map *json = new json::json2map(inputFile);      
  // exaple of testing keys
  if (!json->keyExists("notDefined","subcell")){
    std::cout << "Given key does not exists" << std::endl;
  }  
  if (json->keyExists("subcell")){
    std::cout << "Given key exists" << std::endl;
  }
  // examples for getting values  
  std::cout << "Double: " << json->getValue<double>("number","subcell") << std::endl;
  std::cout << "String: " << json->getValue<std::string>("string","subcell") << std::endl;
  std::cout << "Bool: " << json->getValue<bool>("boolValue") << std::endl;
  std::cout << std::endl << std::endl;
  std::vector<int> temp = json->getVector<int>("array","subcell");
  // fails
  //std::vector<int> temp2 = json->getVector<int>("array");
  // example for printing the contents of json file
  json->prettyPrint();
  delete json;
  return EXIT_SUCCESS;
}

