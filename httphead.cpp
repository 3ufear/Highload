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

http_head::http_head() {
	host = "";
	type_encoded = "";
	path_encoded = "";
	protocol = "";
	// TODO Auto-generated constructor stub
}

void http_head::parse(std::string str) {
	std::cout<<str<<std::endl;
	//char * pch;
	//pch = strtok((char*) str.c_str()," ");

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
	//std::cout<<"PAAAATH"<<path_encoded<<std::endl;
	 boost::regex reg("/[0-9a-zA-Z_%\./-]*");
	  bool b1 = boost::regex_match(path_encoded, reg);
	  std::cout<<"!!!!!!!!"<<path_encoded<<std::endl;
	  std::cout<<"!!!!!!!!"<<b1<<std::endl;
	 // bool b2 = boost::regex_match("A  expression is.", reg);
	while(getline(bufer,line)) {

	//	std::cout<<line<<std::endl;
	}


	//while (pch != NULL)
	//{
	 // std::cout<<pch<<std::endl;
	  //if (strcmp(pch,"GET")) {
		//  cout
//	  }
//	  pch = strtok (NULL, " ");
//	}



}


