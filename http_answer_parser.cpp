

#include "http_answer_parser.hpp"
#include <fstream>

void http_answer_parser::handle(std::string url, httpanswer& answer){
	if (url == "/")
		url.append("index.html");
	if (url != "") {
		std::string full_path = document_root + url;
		std::ifstream fin(full_path.c_str(),std::fstream::in | std::fstream::binary);
		if (fin.is_open()) {
			char buf[5000];
			while(fin.read(buf,5000).gcount()>0) {
				answer.content.append(buf,fin.gcount());
				//answer.content.append("");
			}
			fin.close();
			char str[200];
			sprintf(str, "%ld", answer.content.size());
			answer.head.push_back({"Content-Length", str});
			answer.head.push_back({"Connection","close"});
			answer.head.push_back({"Content-Type", get_content_type(get_type(url))});
			std::cout<<"AAAAAAAAAAAAAAAAAAA "<<get_content_type(get_type(url))<<" BBBBBBBBBB "<<get_type(url)<<"QQQQ"<<std::endl;

			answer.head.push_back({"Server","Phil-server"});
			answer.status = 200;
		} else {
			answer.status = 404;
			std::cout<<"!!!!!!!!!!!!1"<<std::endl;
			answer.head.push_back({"Content-Length", "0"});
			answer.head.push_back({"Connection","close"});
			answer.head.push_back({"Content-Type", "text/html"});
			answer.head.push_back({"Server","Phil-server"});
			answer.content.append("<html><head></head><body><h1>404 NOT FOUND</h1></body></html>");
		}
	} else {
		answer.status = 405;
		answer.head.push_back({"Content-Length", "0"});
		answer.head.push_back({"Connection","close"});
		answer.head.push_back({"Content-Type", "text/html"});
		answer.head.push_back({"Server","Phil-server"});
		answer.content.append("<html><head></head><body><h1>405 NOT ALLOWED</h1></body></html>");
	}
	//std::cout<<answer.content<<std::endl;
}
std::string http_answer_parser::get_type(std::string url) {
	int i=url.length();
	std::string type="";
	while (url[i] != '/') {
		if (url[i] == '.') {
			for (int j=1;j<url.length()-i;j++)
			    type += url[i+j];
			break;
		}
		i--;
	}
	return type;
}

std::string http_answer_parser::get_content_type(std::string type) {
	if (type == "jpg") {
        return "image/jpg";
	} else if(type == "jpeg") {
		return "image/jpeg";
	} else if(type == "gif") {
		return "image/gif";
	} else if(type == "png") {
		return "image/png";
	} else if(type == "swf") {
		return "application/x-shockwave-flash";
	} else if(type == "js") {
		return "application/javascript";
	} else if(type == "css") {
		return "text/css";
	} else if(type == "html") {
		return "text/html";
	} else if(type == "htm") {
		return "text/html";
	} else {
		return "application/octet- stream";
	}
}
