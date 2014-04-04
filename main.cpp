#include "server.hpp"
#include "iostream"

using namespace std;

int main(int argc, char* argv[]) {
	std::string host = "localhost";
	std::string port = "80";
	std::string doc_root = "/home/phil/nginx/download";

	if (argc != 4) {
		cout<<"Usage host port doc_root"<<endl;
	} else {
        host = "localhost";
        port = "80";
        doc_root = "/home/phil/nginx/download";
	}
	server server(host,port,doc_root);



	return 1;
}
