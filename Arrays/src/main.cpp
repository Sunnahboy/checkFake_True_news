#include <iostream>
#include <limits>
#include "Interface.cpp"

using namespace std;
int main(){ 
    Interface interface;
    
    string msg=interface.msg(4);
    interface.columns();
    cout <<string(26, ' ') << msg;
    cout <<endl;
    interface.columns();

    return 0;
}