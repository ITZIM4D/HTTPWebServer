#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

enum RequestMethod {
    GET,
    HEAD,
    PUT,
    CONNECT,
    OPTIONS,
    TRACE,
    POST,
    PATCH,
    DELETE
};

/**
 * @class HTTPMessage
 */
class HTTPMessage {
    public:
        /**
         * @brief Sets the method the HTTP message object is using
         */
        void setRequestMethod(RequestMethod method);        
    private:
        RequestMethod requestMethod;
}

#endif
