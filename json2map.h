#ifndef _JSON2MAP_H_
#define _JSON2MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "json_spirit_reader_template.h"
#include "json_spirit_writer_template.h"

namespace json {

    class json2map {
    private:        
        // recursive map
        std::map<std::string, json::json2map*> json_;        
        bool hasOnlyValue_; // if recursive map isn't there, then hasValue_ = true
        json_spirit::Value value_; // and this is the value                    
        void init(json_spirit::Value value);      
        void prettyPrint(unsigned int indent);        
    public:
        json2map(std::string fileName);
        json2map(json_spirit::Value value);        
        // see template getValue and getVector below
        json_spirit::Value getValue();
        json_spirit::Value getValue(std::string val1);
        json_spirit::Value getValue(std::string val2, std::string val1);
        json_spirit::Value getValue(std::vector<std::string> stack);
        json_spirit::Value_type getValueType(std::string val1);
        json_spirit::Value_type getValueType(std::string val2, std::string val1);
        json_spirit::Value_type getValueType(std::vector<std::string> stack);
        std::vector<json::json2map*> getVector();
        std::vector<json::json2map*> getVector(std::string val1);
        std::vector<json::json2map*> getVector(std::string val2, std::string val1);
        std::vector<json::json2map*> getVector(std::vector<std::string> stack);
        bool keyExists(std::string val1);
        bool keyExists(std::string val1,std::string val2);
        bool keyExists(std::vector<std::string> stack);
        void prettyPrint();                        
        // functions with templates need to be in header file
        // shortcuts for value getters
        template<typename Type>
        Type getValue(std::string val1){
            std::vector<std::string> stack;
            stack.push_back(val1);    
            return getValue<Type>(stack);
        }
        template<typename Type>
        Type getValue(std::string val2,std::string val1){
            std::vector<std::string> stack;
            stack.push_back(val2);
            stack.push_back(val1);
            return getValue<Type>(stack);
        }
        template<typename Type>
        std::vector<Type> getVector(std::string val1){
            std::vector<std::string> stack;
            stack.push_back(val1);
            return getVector<Type>(stack);
        }
        template<typename Type>
        std::vector<Type> getVector(std::string val2,std::string val1){
            std::vector<std::string> stack;
            stack.push_back(val2);
            stack.push_back(val1);
            return getVector<Type>(stack);
        }     
        // these are the actual value getter
        template<typename Type>
        Type getValue(std::vector<std::string> stack) {
            if (stack.size() == 0) {
                return value_.get_value<Type>();
            } else {
                std::string value = stack.at(stack.size() - 1);
                stack.pop_back();
                return json_[value]->getValue<Type>(stack);
            }
        }
        template<typename Type>
        std::vector<Type> getVector(std::vector<std::string> stack) {
            if (stack.size() == 0) {
                // if this is not array, then it is the fault of user
                json_spirit::Array arr = value_.get_array();
                std::vector<Type> val;
                for (unsigned int j = 0; j < arr.size(); ++j) {
                    val.push_back(arr[j].get_value<Type>());
                }
                return val;
            } else {
                std::string value = stack.at(stack.size() - 1);
                stack.pop_back();
                return json_[value]->getVector<Type>(stack);
            }
        }                
        virtual ~json2map();
    };
}

#endif
