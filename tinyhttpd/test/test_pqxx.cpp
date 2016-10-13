#include <iostream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
    try{
        connection C("dbname=db_user_info user=db_user password=111111 \
                hostaddr=192.168.20.128 port=5432");
        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            return 1;
        }
        C.disconnect ();
    }catch (const std::exception &e){
        cerr << e.what() << std::endl;
        return 1;
    }
}
