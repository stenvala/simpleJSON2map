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
        // or then this can have just one value which might be an array or object 
        bool hasValue_;
        json_spirit::Value value_;      
        json_spirit::Value root_;
        void init(json_spirit::Value value);      
        void prettyPrint(unsigned int ind, json_spirit::Value value);
    public:
        json2map(std::string fileName);
        json2map(json_spirit::Value value);
        void prettyPrint();
        void prettyPrint(unsigned int indent);
        json_spirit::Value getRoot();
        json_spirit::Value getValue(std::string val1);
        json_spirit::Value getValue(std::string val2, std::string val1);
        json_spirit::Value getValue(std::vector<std::string> stack);
        bool keyExists(std::string val1);
        bool keyExists(std::string val1,std::string val2);
        bool keyExists(std::vector<std::string> stack);
        // functions with templates need to be in header file
        // short cuts for value getters
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
        
        std::string getFileName();
        virtual ~json2map();
    };
}

#endif
