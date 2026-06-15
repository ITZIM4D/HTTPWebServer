#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

/**
 * @brief Representation of the Request Method of the message
 */
enum RequestMethod {
    GET,
    HEAD,
    PUT,
    CONNECT,
    OPTIONS,
    TRACE,
    POST,
    PATCH,
    DELETE,
    NONE = 0
};

/**
 * @class HTTPMessage
 *
 * @brief Object to represent an HTTP Message
 */
class HTTPMessage {
    public:
        /**
         * @brief Sets the method the HTTP message object is using
         *
         * @param[in]
         */
        void setRequestMethod(RequestMethod method) {requestMethod = method;}       

        /**
         * @brief Gets the method the HTTP message object is using
         *
         * @return The objects request method
         */
        RequestMethod getRequestMethod() {return requestMethod;}

    private:
        RequestMethod requestMethod = NONE;
};

#endif
