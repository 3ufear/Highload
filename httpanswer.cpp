/*
 * httpanswer.cpp
 *
 *  Created on: 02.04.2014
 *      Author: phil
 */

#include "httpanswer.hpp"

httpanswer::httpanswer() {
	content.clear();
	head.clear();
	status=0;
	url.clear();
}

httpanswer::~httpanswer() {
	// TODO Auto-generated destructor stub
}

std::string httpanswer::get_http_status() {
	switch (this->status) {
	case 200:
	    return "HTTP/1.1 200 OK\r\n";
	case 404:
		return "HTTP/1.1 404 Not Found\r\n";
	case 405:
		return "HTTP/1.1 405 Not Allowed\r\n";
	case 403:
		return "HTTP/1.0 403 Forbidden\r\n";
	}
	 return "HTTP/1.1 405 Not Allowed\r\n";
}

namespace my {
	const char crlf[] = {'\r','\n'};
	const char name_value_separator[] = {':',' '};
}

std::vector<boost::asio::const_buffer> httpanswer::to_buf()
{
	std::vector<boost::asio::const_buffer> buffers;

	std::string header;
	header.clear();
	header ="";
	buffers.push_back(boost::asio::buffer(get_http_status()));
	//header = get_http_status();
	std::cout<<get_http_status()<<std::endl;
	//buffers.push_back(boost::asio::buffer(crlf));
	for (std::size_t i = 0; i < head.size(); i++) {
			buffers.push_back(boost::asio::buffer(head[i].name));
			buffers.push_back(boost::asio::buffer(my::name_value_separator));
			buffers.push_back(boost::asio::buffer(head[i].value));
			buffers.push_back(boost::asio::buffer(my::crlf));
	}

	std::cout<<header.length()<<std::endl;
	buffers.push_back(boost::asio::buffer(my::crlf));
	buffers.push_back(boost::asio::buffer(content));

	return buffers;
}
bool httpanswer::is_in_doc_root(std::string url) {
	if (url.rfind("../")==std::string::npos) {
		invalid_path = 1;
	} else {
		invalid_path = 0;
	}
	return invalid_path;
}

