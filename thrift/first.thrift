
struct req_struct {
1: required i64 uid;
2: optional string nickname;
3: required list<i64> nums;
}

struct rsp_struct {
1: required i64 uid;
2: required i64 total;
}

service first {
    void ping();
    i64 add(1:i64 x, 2:i64 y);
    string connect(1:string first, 2:string second);

    rsp_struct structure(1:req_struct req);   
}
