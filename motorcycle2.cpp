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

    person driver2("Tom Cruise",60);
    motorcycle motor2(driver2,NO_ejection_seat,helmet,NO_seatbelt,NO_airbag);

  HttpClient httpclient("http://127.0.0.1:7374");
  finalclient myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  // move
  try {
    myv = myClient.move("move", "motorcycle",
			(motor2.dump2JSON()),
			(car.dump2JSON()),
			"motor2");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  //std::cout << myv.toStyledString() << std::endl;

  cout << "Sending motorcycle 2 info to car..." << endl; 
  if (myv["status"] == "successful"){
    cout << "Success! Info has been sent. \n" << endl;
  }

  return 0;
}