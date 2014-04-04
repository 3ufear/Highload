
#ifndef HTTP_ANSWER_PARSER_
#define HTTP_ANSWER_PARSER_

#include "httpanswer.hpp"

class http_answer_parser {
public:
	http_answer_parser(std::string doc_root) {
		document_root = doc_root;
	}
	std::string document_root;
    void handle(std::string url, std::string method, httpanswer& answer);
    std::string  get_content_type(std::string type);
    std::string get_type(std::string url);
};

#endif /*HTTP_ANSWER_PARSER_*/
