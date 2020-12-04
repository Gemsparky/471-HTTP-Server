#define RESPONSE_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

namespace server{
	class Response{
	public:
		Response(const Request req);
		Response(const Response& orig);
        virtual ~Response();
	private:
		int _status;
	}
}
