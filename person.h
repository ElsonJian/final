#ifndef _PERSON_H_
#define _PERSON_H_

#include "ecs36b_Common.h"

using namespace std;

class person {
    private:
        std::string person_name;
        int person_age;

    public:
        person();
        person(std::string, int);
        virtual Json::Value dump2JSON();
        virtual bool JSON2Object(Json::Value);
        std::string getname();
        int getage();
};

#endif /* _PERSON_H_ */