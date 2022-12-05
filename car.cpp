// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "finalserver.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "finalclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "person.h"
#include "motorcycle.h"
#include "car_general.h"


using namespace jsonrpc;
using namespace std;

// std::map (key, value pairs)
std::map<std::string, motorcycle *> motorcycle_Map;

// my location
car process_here;

//survival score
int currentprocess;
double motor1score;
double motor2score;

class MyfinalServer : public finalserver
{
public:
  MyfinalServer(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value move(const std::string& action,
			   const std::string& class_id,
			   const Json::Value& json_object,
			   const Json::Value& location,
			   const std::string& object_id);
};

MyfinalServer::MyfinalServer(AbstractServerConnector &connector, serverVersion_t type)
  : finalserver(connector, type)
{
  std::cout << "MyfinalServer Object created" << std::endl;
}

double CAL_SURVIVING_SCORE(Json::Value arg_jv){
    double survive_score = 10;
    cout << "Initial Survival Score = " << survive_score << endl;
    if ((arg_jv["ejection_seat"]).asBool() == true){
     survive_score = survive_score + 40;
        cout<< (arg_jv["driver"]["name"]).asString() <<" has ejection seat, +40 to SS! Current SS = "<< survive_score<<endl;
    }
    if ((arg_jv["helmet"]).asBool() == true){
     survive_score = survive_score + 15;
        cout<< (arg_jv["driver"]["name"]).asString() << " has helmet, +15 to SS! Current SS = "<< survive_score<<endl;
    }
    if ((arg_jv["seatbelt"]).asBool() == true){
     survive_score = survive_score + 10;
        cout<< (arg_jv["driver"]["name"]).asString() <<" has seatbelt, +10 to SS! Current SS= "<< survive_score<<endl;
    }
    if ((arg_jv["airbag"]).asBool() == true){
         survive_score = survive_score + 20;
         cout<< (arg_jv["driver"]["name"]).asString() <<" has airbag, +20 to SS! current SS = "<< survive_score<<endl;
    }

    int age = (arg_jv["driver"]["age"]).asInt();

    if (age <= 16){
        cout<< (arg_jv["driver"]["name"]).asString() <<" age is " << age << ", -20 to SS" << endl;
        survive_score = survive_score -20;
    }
    else if ((age >= 16)&(age <= 35)){
        
        cout<< (arg_jv["driver"]["name"]).asString() <<" age is " << age << ", +10 to SS" << endl;
        survive_score = survive_score+10;
    }
    else if ((age < 35)&(age<55)){
        cout<< (arg_jv["driver"]["name"]).asString() <<" age is " << age << endl;
        survive_score = survive_score;
    }
    else if ((age>=55)&(age<70)){
         cout<< (arg_jv["driver"]["name"]).asString() <<" age is " << age << ", -10 to SS" << endl;
         survive_score = survive_score - 10;
    }
    else if (arg_jv[age]>=55){
        cout<< (arg_jv["driver"]["name"]).asString() <<" age is " << age << ", -20 to SS" << endl;
        survive_score = survive_score - 20;
    }

    // cout<< (arg_jv["driver"]["name"]).asString() <<" Survive_rate = "<< survive_score<<endl;
    return survive_score;
}


// member functions


Json::Value
MyfinalServer::move
(const std::string& action, const std::string& class_id,
 const Json::Value& json_object, const Json::Value& location,
 const std::string& object_id)
{
  int error_code = 0;

  Json::Value result;
  std::string strJson;

  if (class_id != "motorcycle")
    {
      result["status"] = "failed";
      strJson = ( "class " + class_id + " unknown");
      result["reason"] = strJson;
      error_code = -1;
    }

  if (object_id.empty())
    {
      result["status"] = "failed";
      strJson = ( "object_id null ");
      result["reason"] = strJson;
      error_code = -2;
    }

  car incoming_location;
  if ((location.isNull() == true) ||
      (location.isObject() == false))
    {
      result["status"] = "failed";
      strJson = ( "location parsing error " );
      result["reason"] = strJson;
      error_code = -3;
    }

  if ((json_object.isNull() == true) ||
      (json_object.isObject() == false))
    {
      result["status"] = "failed";
      strJson = ( "person parsing error " );
      result["reason"] = strJson;
      error_code = -4;
    }

  if (error_code == 0)
    {
    //   incoming_location.JSON2Object(location);
      if (!((process_here.dump2JSON()).toStyledString() == (incoming_location.dump2JSON()).toStyledString()))
	{
	  result["status"] = "failed";
	  strJson = ( "location mismatched" );
	  result["reason"] = strJson;
	  error_code = -5;
	}
      else
	{
    if (object_id == "motor1"){
    currentprocess = 1;
    cout << "\nMotorcycle 1 details have been received" << endl;
	  motorcycle * lv_motorcycle_ptr;
	  if (motorcycle_Map.find(object_id) != motorcycle_Map.end())
	    {
	      lv_motorcycle_ptr = motorcycle_Map[object_id];
	    }
	  else
	    {
	      lv_motorcycle_ptr = new motorcycle {};
	      motorcycle_Map[object_id] = lv_motorcycle_ptr;
	    }
	  lv_motorcycle_ptr->JSON2Object(json_object);
    result["status"] = "successful";

    // result = json_object;                            //test to see if object moved
    // cout << result.toStyledString() << endl;

    cout << "Calculating score of motorcycle 1..." << endl;
    motor1score = CAL_SURVIVING_SCORE(json_object);
    cout << "Final score of motorcycle 1 is " << motor1score << "\n" << endl; 
    }
    
    if (object_id == "motor2"){
    currentprocess = 2;
    cout << "Motorcycle 2 details have been received" << endl;
	  motorcycle * lv_motorcycle_ptr;
	  if (motorcycle_Map.find(object_id) != motorcycle_Map.end())
	    {
	      lv_motorcycle_ptr = motorcycle_Map[object_id];
	    }
	  else
	    {
	      lv_motorcycle_ptr = new motorcycle {};
	      motorcycle_Map[object_id] = lv_motorcycle_ptr;
	    }
	  lv_motorcycle_ptr->JSON2Object(json_object);
    result["status"] = "successful";

    cout << "Calculating score of motorcycle 2..." << endl;
    motor2score = CAL_SURVIVING_SCORE(json_object);
    cout << "Final score of motorcycle 2 is " << motor2score << "\n" << endl; 
    currentprocess = 3;
   }
}

if (currentprocess == 3){
  if (motor1score > motor2score){
  Json::Value alert;
  alert["status"] = true;

  cout << "The survival score for motorcycle 1 is higher than motorcycle 2" << endl;
  cout << "Alerting motorcycle 1..." << endl;

} else{
  cout << "The survival score for motorcycle 2 is higher than motorcycle 1" << endl;
  cout << "Alerting motorcycle 2..." << endl;
}

return result;
}
}
}



int main()
{

    car car;
    
    // set location here
    process_here = car;

    bool ejection_seat = true;
    bool helmet = true;
    bool seatbelt = true;
    bool airbag = true;

    bool NO_ejection_seat = false;
    bool NO_helmet = false;
    bool NO_seatbelt = false;
    bool NO_airbag = false;

    person driver1("Keanu Reeves",58);
    motorcycle motor1(driver1,ejection_seat,NO_helmet,NO_seatbelt,airbag);
    person driver2("Tom Cruise",60);
    motorcycle motor2(driver2,NO_ejection_seat,helmet,NO_seatbelt,NO_airbag);
    
    // double test = CAL_SURVIVING_SCORE(motor2.dump2JSON());
    // cout << "test score: " << test << endl; 

  int rc;
  char name_buf[256];
  bzero(name_buf, 256);
  snprintf(name_buf, 256, "./json_objects/%s.json", "Motorcycle1");
  // "./json_objects/motorcycle_00000001.json"
  Json::Value jv = motor1.dump2JSON();
  rc = myJSON2File(name_buf, &jv);
  if (rc != 0)
      {
      std::cout << "myJSON2File error " << rc << std::endl;
      exit(-1);
      }

  Json::Value motorcycle1;
  rc = myFile2JSON(name_buf, &motorcycle1);
  if (rc != 0)
    {
      std::cout << "myJSON2File error " << rc << std::endl;
      exit(-1);
    }
  
  motorcycle new_motor1 {};
  new_motor1.JSON2Object(motorcycle1);
  //std::cout << (new_motor1.dump2JSON()).toStyledString() << std::endl;


  bzero(name_buf, 256);
  snprintf(name_buf, 256, "./json_objects/%s.json", "Motorcycle2");
  Json::Value jv_2 = motor2.dump2JSON();
  rc = myJSON2File(name_buf, &jv_2);
  if (rc != 0)
    {
      std::cout << "myJSON2File error " << rc << std::endl;
      exit(-1);
    }

  Json::Value motorcycle2;
  rc = myFile2JSON(name_buf, &motorcycle2);
  if (rc != 0)
    {
      std::cout << "myJSON2File error " << rc << std::endl;
      exit(-1);
    }
  
  motorcycle new_motor2 {};
  new_motor2.JSON2Object(motorcycle2);
  //std::cout << (new_motor2.dump2JSON()).toStyledString() << std::endl;


  HttpServer httpserver(7374);
  MyfinalServer s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}

