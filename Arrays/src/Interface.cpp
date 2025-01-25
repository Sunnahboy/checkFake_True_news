#include <iostream>
#include <limits>

using namespace std;
class Interface
{   
    public:
        void rows(){}
        void columns(){
            for(int i=0; i<=80; i++){
                cout << "="<<left;
            }
            cout <<endl;
        }
        void prinTable(){}

        string msg(int o){
            switch(o){
                case 1:
                    return "Data Filtering";
                    break;
                case 2:
                    return "Sort Data";
                    break;
                case 3:
                    return "Search Data";
                    break;
                case 4:
                    return "ARRAYS MANAGEMENT";
                    break;
                default:
                    return "none";
                    break;
            }
        }
};
