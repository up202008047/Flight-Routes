//
// Created by bruno on 12/28/22.
//

#include "Airlines.h"

Airlines::Airlines(string code, string name, string callsign, string country) {
    code= move(code);
    name= move(name);
    callsign= move(callsign);
    country= move(country);
}

string Airlines::getCode()const {
    return code;
}
string Airlines::getCallSign()const {
    return callsign;
}
string Airlines::getName()const {
    return name;
}
string Airlines::getCountry()const {
    return country;
}

