/*
 * httpanswer.cpp
 *
 *  Created on: 02.04.2014
 *      Author: phil
 */

#include "httpanswer.hpp"

httpanswer::httpanswer() {

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
		return "HTPP/1.1 405 Not Allowed\r\n";
	}
	 return "HTPP/1.1 405 Not Allowed\r\n";
}
/*
std::vector<boost::asio::const_buffer> httpanswer::to_buf() {
	std::vector<boost::asio::const_buffer> buffers;
	const char symbols[] = {':', ' ', '\n', '\r'};
	const char name_value_separator[] = { ':', ' ' };
	const char crlf[] = { '\r', '\n' };

	buffers.push_back(boost::asio::buffer(get_http_status()));

	for (std::size_t i = 0; i < head.size(); i++)
	{
		buffers.push_back(boost::asio::buffer(head[i].name));
		buffers.push_back(boost::asio::buffer(name_value_separator));
		buffers.push_back(boost::asio::buffer(head[i].value));
		buffers.push_back(boost::asio::buffer(crlf));
	}

	buffers.push_back(boost::asio::buffer(crlf));
	buffers.push_back(boost::asio::buffer(content));
	return buffers;
}*/

std::vector<boost::asio::const_buffer> httpanswer::to_buf()
{
	std::vector<boost::asio::const_buffer> buffers;

//buffers.push_back(boost::asio::buffer(_response.status_string));

//std::size_t n = _response.headers.size();

	const char crlf[] = { '\r', '\n' };
	const char name_value_separator[] = { ':', ' ' };
//const char crlf[] = "\r\n";
//const char name_value_separator[] = ": ";
	buffers.push_back(boost::asio::buffer(get_http_status()));
	std::cout<<get_http_status()<<std::endl;
	//buffers.push_back(boost::asio::buffer(crlf));
	for (std::size_t i = 0; i < head.size(); i++) {
			buffers.push_back(boost::asio::buffer(head[i].name));
			buffers.push_back(boost::asio::buffer(name_value_separator));
			buffers.push_back(boost::asio::buffer(head[i].value));
			buffers.push_back(boost::asio::buffer(crlf));
	}

	buffers.push_back(boost::asio::buffer(crlf));;
//buffer.push_back(boost::asio::buffer("\n"));
	buffers.push_back(boost::asio::buffer(content));

	return buffers;
}

void httpanswer::parse_from_url() {
	/*std::string url = http.get_valid_url();
	if (url == "") {
		status = "405";
	} else {

	}*/
}

