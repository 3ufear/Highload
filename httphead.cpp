/*
 * httphead.cpp
 *
 *  Created on: 31.03.2014
 *      Author: phil
 */

#include "httphead.hpp"
#include <iostream>
#include <string.h>
#include <sstream>
#include <ctype.h>
#include <boost/regex.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <ctype.h>

http_head::http_head() {
	host = "";
	type_encoded = "";
	path_encoded = "";
	protocol = "";
}

bool http_head::parse(std::string str) {

	std::stringstream bufer(str);
	std::string line;
	getline(bufer,line);
	std::vector<std::string> headers;
	int len = line.length()-1;
	while(len>0) {
		if (!isprint(line[len])) {
			std::cout<<"deleting"<<line[len]<<std::endl;
			line[len] = '\0';
		} else {
			break;
		}
		len--;
	}
	std::cout<<line<<std::endl;
	boost::split(headers, line, boost::is_any_of(" \n\r"));
	std::vector<std::string>::iterator it = headers.begin();
    type_encoded = *it;
    std::cout<<type_encoded<<std::endl;
    it++;
    std::cout<<"SECIND"<<*it<<std::endl;
    std::vector<std::string>::iterator it_e = headers.end();
    it_e--;
    it_e--;
    if (type_encoded=="HEAD") {
    	std::cout<<"SIZE: "<<headers.size()<<std::endl;
    }
    if (*it_e != "HTTP/1.1") {
    	it_e++;
    }
    bool first_time=1;
    while (it != it_e) {
    	if (first_time) {
    		first_time = 0;
    	} else {
    		path_encoded.append("%20");
    	}
     	path_encoded.append(*it);
    	it++;
    	std::cout<<path_encoded<<"QQQ"<<std::endl;
   }
	std::vector<std::string> tokens;
	 while(getline(bufer,line)) {
		 boost::split(tokens, line, boost::is_any_of(":"));
	}
    get_valid_url();

    return 1;
}

bool http_head::url_is_valid() {
	 boost::regex reg("/[0-9a-zA-Z_%\./\!\"#\&\'\*\,\:\;\<\=\>\?\[\|\^\`\{\|\}-]*");//\"#\&\'\*\,\:\;\<\=\>\?\[\]\^\`\{\|
	 bool b1 = boost::regex_match(path_encoded, reg);
	 return b1;
}

std::string http_head::get_valid_url() {
	std::string valid_url;
		char *ptr;
		ptr = (char*)path_encoded.c_str();
		int i=0;
		bool flag_sl=0;
		int vhogd=0;
		int flag_point = 0;
		bool point = 0;
		while (i < (int)path_encoded.length()) {
			/*if (*ptr == '/'){
				if (flag_sl) {
					ptr++;
				} else {
					vhogd+=1;
					flag_sl=1;
				}
			} else {
				flag_sl=0;
			}

			if (*ptr == '.') {
				if (flag_point) {
					ptr++;
					if (*ptr == '/') {
						flag_point += 1;
						ptr++;
					}
				}

				flag_point = 1;

			} else {
				flag_point = 0;
			}*/
			if (*ptr == '?') {
				break;
			}
			if (*ptr == '%') {
				std::string symbol;
				symbol.push_back(*(++ptr));
				symbol.push_back(*(++ptr));
				std::cout<<"httphead"<<std::endl;
				//std::cout<<symbol<<std::endl;
				valid_url.push_back((strtol(symbol.c_str(), 0, 16)));
				//std::cout<<symbol<<std::endl;
				ptr++;
			} else {
				valid_url.push_back(*ptr);
				i++;
				ptr++;
			}
		}
	path_encoded = valid_url;
	return valid_url;
}

bool http_head::is_in_doc_root(std::string url) {
	if (url.rfind("../")) {
		invalid_path = 0;
	} else {
		invalid_path = 1;
	}
	return invalid_path;
}
