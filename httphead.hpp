/*
 * httphead.hpp
 *
 *  Created on: 31.03.2014
 *      Author: phil
 */

#ifndef HTTPHEAD_HPP_
#define HTTPHEAD_HPP_

#include <string>

class http_head {
private:
	std::string path_encoded;
	std::string type_encoded;
	std::string host;
	std::string protocol;
public:
	http_head();
	void parse(std::string head);
	std::string get_valid_url();
	bool url_is_valid();

};

#endif /* HTTPHEAD_HPP_ */
