#include"vehicle.h"

vehicle::vehicle(){
    this->ejection_seat = false;
    this-> helmet = false;
    this-> seatbelt = false;
    this-> airbag = false;
    this->driver = person{};
}

vehicle::vehicle(person arg_person, bool arg_ejection_seat, bool arg_helmet,bool arg_seatbelt, bool arg_airbag){
    if (arg_ejection_seat == true){
        this->ejection_seat = true;
    }else{
        this->ejection_seat = false;
    }
    if (arg_helmet == true){
        this-> helmet = true;
    }else{
        this-> helmet = false;
    }
    if (arg_seatbelt == true){
        this-> seatbelt = true;
    }else{
        this-> seatbelt = false;
    }
    if (arg_airbag == true){
        this-> airbag = true;
    }else{
        this-> airbag = false;
    }
    
    this->driver = arg_person;
    // std::cout<<"vehicle create success"<< endl;
}

Json::Value
vehicle::dump2JSON
(void)
{
  Json::Value result { };

if (this->ejection_seat != true)
    {
    result["ejection seat"] = false;
    } 
else 
    {
    result["ejection seat"] = true;
    }

if (this->helmet != true)
    {
    result["helmet"] = false;
    } 
else 
    {
    result["helmet"] = true;
    }

if (this->seatbelt != true)
    {
    result["seatbelt"] = false;
    } 
else 
    {
    result["seatbelt"] = true;
    }

if (this->airbag != true)
    {
    result["airbag"] = false;
    } 
else 
    {
    result["airbag"] = true;
    }

  Json::Value jv_result;

  jv_result = (this->driver).dump2JSON();
  result["driver"] = jv_result;

  // std::cout << jv_result.toStyledString() << std::endl;

  return result;
}

bool
vehicle::JSON2Object
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

  if (((arg_jv["ejection seat"]).isNull() == true) ||
      ((arg_jv["ejection seat"]).isBool() != true))
    {
      return false;
    }

    if (((arg_jv["helmet"]).isNull() == true) ||
      ((arg_jv["helmet"]).isBool() != true))
    {
      return false;
    }

    if (((arg_jv["seatbelt"]).isNull() == true) ||
      ((arg_jv["seatbelt"]).isBool() != true))
    {
      return false;
    }

    if (((arg_jv["airbag"]).isNull() == true) ||
      ((arg_jv["airbag"]).isBool() != true))
    {
      return false;
    }

  this->ejection_seat = (arg_jv["ejection seat"]).asBool();
  this->helmet = (arg_jv["helmet"]).asBool();
  this->seatbelt = (arg_jv["seatbelt"]).asBool();
  this->airbag = (arg_jv["airbag"]).asBool();


  if (((arg_jv["driver"]).isNull() == true) ||
      ((arg_jv["driver"]).isObject() != true))
    {
      return false;
    }

  (this->driver).JSON2Object(arg_jv["driver"]);

  return true;
}
