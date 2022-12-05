#ifndef _MOTORCYCLE_H_
#define _MOTORCYCLE_H_

#include "vehicle.h"
#include "ecs36b_Common.h"

class motorcycle: public vehicle{
    private:
        bool ejection_seat;
        bool helmet;
        // bool seatbelt;
        // bool airbag;
        // person driver;
        
    public:
        motorcycle();
        motorcycle(person, bool, bool, bool, bool);
        virtual Json::Value dump2JSON();
        virtual bool JSON2Object(Json::Value);
};
#endif /* _MOTORCYCLE_H_ */