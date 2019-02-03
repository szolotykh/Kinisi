#include <iostream>
#include "mqttworker.h"

using namespace std;

int main(){
    cout<<"Robot"<<endl;
    
    robot::connection_settings_t stConnectionSettings{
        "",
        "",
        ""
    };
    robot::CMQTTWorker MQTTWorker(stConnectionSettings);

    cout << "Press Enter to Continue" << endl;
    cin.ignore();
    MQTTWorker.Stop();
    return 0;
}