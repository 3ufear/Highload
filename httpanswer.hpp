/*
 * hhtpanswer.hpp
 *
 *  Created on: 02.04.2014
 *      Author: phil
 */

#ifndef HHTPANSWER_HPP_
#define HHTPANSWER_HPP_

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "httphead.hpp"

struct header {
	std::string name;
	std::string value;
};

class httpanswer {
	std::string url;
public:

	httpanswer();
	int status;
	std::vector<header> head;
	std::string content;
	std::vector<boost::asio::const_buffer> to_buf();
	void parse_from_url();
	std::string get_http_status();
	virtual ~httpanswer();
};

#endif /* HHTPANSWER_HPP_ */
