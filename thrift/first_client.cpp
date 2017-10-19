#include <iostream>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "first.h"
#include "first_types.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int main() {
  boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  //boost::shared_ptr<TProtocol> protocol(new TJSONProtocol(transport));
  firstClient client(protocol);

  try {
    transport->open();

    client.ping();
    cout << "ping()" << endl;

    int64_t sum = client.add(1, 2);
    cout << "1 + 2 = " << sum << endl;;

    req_struct req;
    req.uid = 10000000;
    req.__set_nickname("nickname");
//    for (int i=0; i<10; i++) {
//        req.nums.push_back(i+1024);
//    }
    req.printTo(cout);
    cout << endl;

    rsp_struct resp;
    client.structure(resp, req);

    cout << "structure resp: " << resp.uid << " " << resp.total << endl;
    

    transport->close();
  } catch (TException& tx) {
    cout << "ERROR: " << tx.what() << endl;
  }
}
