#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "json_spirit_reader_template.h"
#include "json_spirit_writer_template.h"

#include "json2map.h"

namespace json {

  // some helper function defined (implementatiot at the end)
  void indent(unsigned int ind);
  void prettyPrint(unsigned int ind, json_spirit::Value value);
  void printValue(json_spirit::Value value);

  // constructors

  json2map::json2map(std::string fileName) {
    std::ifstream is(fileName.c_str());
    json_spirit::Value value;
    json_spirit::read_stream(is, value);
    is.close();
    root_ = value;
    init(value);
  }

  json2map::json2map(json_spirit::Value value) {
    root_ = value;
    init(value);
  }

  // Public

  // get value as json_spirit::Value (first the shortcuts))

  json_spirit::Value json2map::getValue(std::string val1) {
    std::vector<std::string> stack;
    stack.push_back(val1);
    return getValue(stack);
  }

  json_spirit::Value json2map::getValue(std::string val2, std::string val1) {
    std::vector<std::string> stack;
    stack.push_back(val2);
    stack.push_back(val1);
    return getValue(stack);
  }

  json_spirit::Value json2map::getValue(std::vector<std::string> stack) {
    if (stack.size() == 0) {
      return getRoot();
    } else {
      std::string value = stack.at(stack.size() - 1);
      stack.pop_back();
      return json_[value]->getValue(stack);
    }
  }

  json_spirit::Value_type json2map::getValueType(std::string val1) {
    std::vector<std::string> stack;
    stack.push_back(val1);
    return getValueType(stack);
  }

  json_spirit::Value_type json2map::getValueType(std::string val2, std::string val1) {
    std::vector<std::string> stack;
    stack.push_back(val2);
    stack.push_back(val1);
    return getValueType(stack);
  }

  json_spirit::Value_type json2map::getValueType(std::vector<std::string> stack) {
    if (stack.size() == 0) {
      return getRoot().type();
    } else {
      std::string value = stack.at(stack.size() - 1);
      stack.pop_back();
      return json_[value]->getValueType(stack);
    }
  }
  
  // check if keys exist

  bool json2map::keyExists(std::string val1) {
    std::vector<std::string> stack;
    stack.push_back(val1);
    return keyExists(stack);
  }

  bool json2map::keyExists(std::string val2, std::string val1) {
    std::vector<std::string> stack;
    stack.push_back(val2);
    stack.push_back(val1);
    return keyExists(stack);
  }

  bool json2map::keyExists(std::vector<std::string> stack) {
    if (stack.size() == 0) {
      return true;
    } else {
      std::string value = stack.at(stack.size() - 1);
      stack.pop_back();
      if (json_.find(value) == json_.end()) {
        return false;
      } else {
        return json_[value]->keyExists(stack);
      }
    }

  }

  // printer

  void json2map::prettyPrint() {
    unsigned int indent = 0;
    prettyPrint(indent);
    std::cout << std::endl;
  }

  // destructor, free memory

  json2map::~json2map() {
    if (!hasValue_) {
      typedef std::map<std::string, json::json2map*>::iterator it_type;
      for (it_type iterator = json_.begin(); iterator != json_.end(); iterator++) {
        delete iterator->second;
      }
    }
  }

  /*
   * Private   
   */
  
  json_spirit::Value json2map::getRoot() {
    return root_;
  }

  void json2map::prettyPrint(unsigned int ind) {
    unsigned int newInd = ind + 2;
    if (hasValue_) {
      switch (value_.type()) {
        case json_spirit::array_type:
          json::prettyPrint(ind, value_);
          break;
        default:
          printValue(value_);
          // with object type one shouldn't be here because then hasValue_ is false
      }
    } else {
      // iterate to the next level
      std::cout << "{" << std::endl;
      typedef std::map<std::string, json::json2map*>::iterator it_type;
      bool isFirst = true;
      for (it_type iterator = json_.begin(); iterator != json_.end(); iterator++) {
        if (!isFirst) {
          std::cout << "," << std::endl;
        }
        isFirst = false;
        indent(newInd);
        std::cout << "\"" << iterator->first << "\": ";
        iterator->second->prettyPrint(newInd);
      }
      std::cout << std::endl;
      indent(ind);
      std::cout << "}";
    }
  }

  void json2map::init(json_spirit::Value value) {
    if (value.type() == json_spirit::obj_type) {
      json_spirit::Object variables = value.get_obj();
      hasValue_ = false;
      for (unsigned int i = 0; i < variables.size(); ++i) {
        json::json2map *json = new json::json2map(variables[i].value_);
        json_[variables[i].name_] = json;
      }
    } else {
      hasValue_ = true;
      value_ = value;
    }
  }

  // Other methods

  void indent(unsigned int ind) {
    for (unsigned int i = 0; i < ind; ++i) {
      std::cout << " ";
    }
  }

  void prettyPrint(unsigned int ind, json_spirit::Value value) {
    unsigned int newInd = ind + 2;
    switch (value.type()) {
      case json_spirit::array_type:
      {
        std::cout << "[" << std::endl;
        json_spirit::Array arr = value.get_array();
        for (unsigned int i = 0; i < arr.size(); ++i) {
          if (i > 0) {
            std::cout << "," << std::endl;
          }
          indent(newInd);
          prettyPrint(newInd, arr[i]);
        }
        std::cout << std::endl;
        indent(ind);
        std::cout << "]";
        break;
      }
      case json_spirit::obj_type:
      {
        std::cout << "{ " << std::endl;
        json_spirit::Object obj = value.get_obj();
        for (unsigned int i = 0; i < obj.size(); ++i) {
          if (i > 0) {
            std::cout << "," << std::endl;
          }
          indent(newInd);
          std::cout << "\"" << obj[i].name_ << "\": ";
          prettyPrint(newInd, obj[i].value_);
        }
        std::cout << std::endl;
        indent(ind);
        std::cout << "}";
        break;
      }
      default:
        printValue(value);
    }
  }

  void printValue(json_spirit::Value value) {
    switch (value.type()) {
      case json_spirit::str_type:
        std::cout << "\"";
        std::cout << value.get_value<std::string>();
        std::cout << "\"";
        break;
      case json_spirit::bool_type:
        if (value.get_value<bool>()) {
          std::cout << "true";
        } else {
          std::cout << "false";
        }
        break;
      case json_spirit::int_type:
        std::cout << value.get_value<int>();
        break;
      case json_spirit::real_type:
        std::cout << value.get_value<double>();
        break;
      case json_spirit::null_type:
        std::cout << "null";
        break;
      default:
        std::cout << "One should not use this with array or object!";
    }
  }
}