#ifndef HTTP_H
#define HTTP_H

#define HTTP_METHOD_GET_SIZE	3
#define HTTP_METHOD_POST_SIZE	4
#define HTTP_METHOD_RESPONSE	8

enum HTTPMethods {
	HTTP_Method_UNKNOWN = 0,
	HTTP_Method_GET = HTTP_METHOD_GET_SIZE,
	HTTP_Method_POST = HTTP_METHOD_POST_SIZE,
	HTTP_RESPONSE = HTTP_METHOD_RESPONSE,
};

enum HTTPStatusCode {
	HTTP_XXX,
	HTTP_1XX,
	HTTP_2XX,
	HTTP_200,
	HTTP_204,
	HTTP_3XX,
	HTTP_4XX,
	HTTP_401,
	HTTP_5XX,
};

#endif
