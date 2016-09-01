#ifndef _SOCKETS_Base64_H
#define _SOCKETS_Base64_H

#include <stdio.h>
#include <string>

class Base64
{
public:
	Base64();

	void encode(FILE *, std::string& , bool add_crlf = true);
	void encode(const std::string&, std::string& , bool add_crlf = true);
	void encode(const char *, size_t, std::string& , bool add_crlf = true);
	void encode(const unsigned char *, size_t, std::string& , bool add_crlf = true);

	void decode(const std::string&, std::string& );
	void decode(const std::string&, unsigned char *, size_t&);

	size_t decode_length(const std::string& );

private:
	Base64(const Base64& ) {}
	Base64& operator=(const Base64& ) { return *this; }
static	const char *bstr;
static	const char rstr[128];
};


#endif // _SOCKETS_Base64_H

