#include "person.h"
#include "vehicle.h"

int main()
{
    bool ejection_seat = true;
    bool helmet = true;
    bool seatbelt = true;
    bool airbag = true;

    bool NO_ejection_seat = false;
    bool NO_helmet = false;
    bool NO_seatbelt = false;
    bool NO_airbag = false;

    person driver1("Keanu Reeves",58);
    person driver2("Tom Cruise",60);
    vehicle motor1(driver1,ejection_seat,NO_helmet,NO_seatbelt,airbag);
    vehicle motor2(driver2,NO_ejection_seat,helmet,NO_seatbelt,NO_airbag);

    return 0;

}