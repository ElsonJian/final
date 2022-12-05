#ifndef _CAR_GENERAL_H_
#define _CAR_GENERAL_H_

#include "vehicle.h"
#include "ecs36b_Common.h"

class car: public vehicle{
    private:
        // bool ejection_seat;
        // bool helmet;
        // bool seatbelt;
        // // bool airbag;
        // // person driver;
        
    public:
        car();
        car(person, bool, bool);
        virtual Json::Value dump2JSON();
        virtual bool JSON2Object(Json::Value);
};
#endif /* _CAR_GENERAL_H_ */