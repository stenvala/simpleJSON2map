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
  json->prettyPrint();
  std::cout << std::endl << std::endl;
  // exaple of testing keys
  if (!json->keyExists("notDefined","subcell")){
    std::cout << "Given key does not exists" << std::endl;
  }  
  if (json->keyExists("number","subcell")){    
    std::cout << "Double: " << json->getValue<double>("number","subcell") << std::endl;
  }
  if (json->keyExists("array","subcell")){
    std::vector<double> temp = json->getVector<double>("array","subcell");
    std::cout << "Array" << std::endl;
    for (unsigned int i=0;i<temp.size();i++){
      std::cout << "Value " << i << ": " << temp.at(i) << std::endl;
    }
  }    
  std::vector<std::string> empty;
  std::cout << "Value type of root is: " << json->getValueType(empty) << std::endl;
  if (json->keyExists("temp")){
    std::cout << "Value type of temp is: " << json->getValueType("temp") << std::endl;
  }
  if (json->keyExists("name")){
    std::cout << "Value type of name is: " << json->getValueType("name") << std::endl;
  }
  delete json;
  return EXIT_SUCCESS;
}

