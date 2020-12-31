g++ is_lock_free.cpp -o is_lock_free -std=c++11 -latomic

g++ store_load.cpp -o store_load -std=c++11 -latomic -lpthread

g++ exchange.cpp -o exchange -std=c++11 -latomic -lpthread

