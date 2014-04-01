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

http_head::http_head() {
	host = "";
	type_encoded = "";
	path_encoded = "";
	protocol = "";
	// TODO Auto-generated constructor stub
}

void http_head::parse(std::string str) {

	std::stringstream bufer(str);
	std::string line;
	getline(bufer,line);
	int i=1;
	char * pch;
	pch = strtok((char*) line.c_str()," ");
	while (pch != NULL) {
		if (i==1) {
			type_encoded=pch;
		} else if (i==2) {
			path_encoded=pch;
		} else if (i==3) {
			protocol=pch;
		}
		i++;
		pch = strtok (NULL, " ");
	}
	std::vector<std::string> tokens;

	 while(getline(bufer,line)) {
	//	std::cout<<line<<std::endl;//добавить обработку остальных
		 boost::split(tokens, line, boost::is_any_of(":"));
		 std::cout<<tokens.size()<<std::endl;
	}
	std::vector<std::string>::iterator it = tokens.begin();
    get_valid_url();

}

bool http_head::url_is_valid() {
	 boost::regex reg("/[0-9a-zA-Z_%\./\!\"#\&\'\*\,\:\;\<\=\>\?\[\|\^\`\{\|\}-]*");//\"#\&\'\*\,\:\;\<\=\>\?\[\]\^\`\{\|
	 bool b1 = boost::regex_match(path_encoded, reg);
	 return b1;
}

std::string http_head::get_valid_url() {
	std::cout<<"!!!!!!!!!!"<<url_is_valid()<<std::endl;
	std::string valid_url;
	if (url_is_valid()) {
		char *ptr;
		ptr = (char*)path_encoded.c_str();
		int i=0;
		while (i < (int)path_encoded.length()) {
			if (*ptr == '%') {
				std::string symbol;
				symbol.push_back(*(++ptr));
				symbol.push_back(*(++ptr));
				std::cout<<"!!!!!!!!!!!"<<std::endl;
				std::cout<<symbol<<std::endl;
				valid_url.push_back((strtol(symbol.c_str(), 0, 16)));
				std::cout<<symbol<<std::endl;
				ptr++;
			} else {
			valid_url.push_back(*ptr);
			std::cout<<valid_url<<std::endl;
			i++;
			ptr++;
			}
		}

	} else
		valid_url = "";
	return valid_url;
}
