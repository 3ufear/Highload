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
	int invalid_path;
	http_head();
	bool parse(std::string head);
	std::string get_valid_url();
	bool url_is_valid();
	//std::string get_value_dimension();
	std::string get_method() {
		return type_encoded;
	}
	bool is_in_doc_root(std::string url);

};

#endif /* HTTPHEAD_HPP_ */
