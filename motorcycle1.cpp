// ecs36b first program

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "finalclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include "finalserver.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

// ecs36b
#include "person.h"
#include "motorcycle.h"
#include "car_general.h"

using namespace jsonrpc;
using namespace std;

int
main()
{
  
    car car;
    
    bool ejection_seat = true;
    bool helmet = true;
    bool seatbelt = true;
    bool airbag = true;

    bool NO_ejection_seat = false;
    bool NO_helmet = false;
    bool NO_seatbelt = false;
    bool NO_airbag = false;

    person driver1("Keanu Reeves", 58);
    motorcycle motor1(driver1, ejection_seat, NO_helmet, NO_seatbelt, airbag);

  HttpClient httpclient("http://127.0.0.1:7374");
  finalclient myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  // move
  try {
    myv = myClient.move("move", "motorcycle",
			(motor1.dump2JSON()), //.toStyledString(),
			(car.dump2JSON()), //.toStyledString(),
			"motor1");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  //std::cout << myv.toStyledString() << std::endl;

  cout << "Sending motorcycle 1 info to car..." << endl; 
  if (myv["status"] == "successful"){
    cout << "Success! Info has been sent. \n" << endl;
  }

  return 0;
}