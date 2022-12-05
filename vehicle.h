#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include "person.h"
#include "ecs36b_Common.h"

class vehicle{
    public:
        //bool ejection_seat;
        //bool helmet;
        bool seatbelt;
        bool airbag;
        person driver;
        
    // public:
    //     vehicle();
    //     vehicle(person, bool, bool, bool, bool);
    //     virtual Json::Value dump2JSON();
    //     virtual bool JSON2Object(Json::Value);
    //     //double CAL_SURVIVING_SCORE(Json::Value);
    //     //bool operator==(vehicle&);
};
#endif /* _VEHICLE_H_ */