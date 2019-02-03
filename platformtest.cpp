#include <iostream>
#include "platform.h"

using namespace std;

int main(){
    cout<<"platform test"<<endl;
    //PhidgetDCMotorHandle ch;
    //PhidgetReturnCode prc = PhidgetDCMotor_create(&ch);

    platform::CPlatform platform;
    platform.Build();
    platform.Test();
    cout << "Press Enter to Continue" << endl;
    cin.ignore();
    return 0;
}