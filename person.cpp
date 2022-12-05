#include "person.h"

person::person (){
    this->person_name = "";
    this->person_age = -1;
}

person::person(std::string arg_name, int arg_age){
    this->person_name = arg_name;
    this->person_age = arg_age;
}

int person::getage(){
    return this->person_age;
}

std::string person::getname(){
    return this->person_name;
}

Json::Value
person::dump2JSON
(void)
{
  Json::Value result { };

  if (this->person_name != "")
    {
      result["name"] = this->person_name;
    }

  if (this->person_age != -1)
    {
      result["age"] = this->person_age;
    }

  return result;
}

bool
person::JSON2Object
(Json::Value arg_jv)
{
  if ((arg_jv.isNull() == true) ||
      (arg_jv.isObject() != true))
    {
      if (arg_jv.isNull() != true)
	{
	  cout << arg_jv.toStyledString() << std::endl;
	}
      return false;
    }

  if (((arg_jv["name"]).isNull() == true) ||
      ((arg_jv["name"]).isString() != true))
    {
      return false;
    }

  if (((arg_jv["age"]).isNull() == true) ||
      ((arg_jv["age"]).isInt() != true))
    {
      return false;
    }

  this->person_name = (arg_jv["name"]).asString();
  this->person_age = (arg_jv["age"]).asInt();

  return true;
}
