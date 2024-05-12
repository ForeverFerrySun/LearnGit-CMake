/*******************************************************************************
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 * 
 * Base64
 *	Base64 is a group of similar binary-to-text encoding schemes that represent 
 * binary data in an ASCII string format by translating it into a radix-64 
 * representation. The term Base64 originates from a specific MIME content 
 * transfer encoding.
 *
 * http://en.wikipedia.org/wiki/Base64
 ******************************************************************************/

#ifndef _CBASE64F_H_
#define _CBASE64F_H_


#include <iostream>
#include <string>
#include <string.h>

namespace alg {
	class CBase64 {
		public:
			static std::string encodeBase64(unsigned char *input , int input_len) ;

			static std::string decodeBase64(std::string input);

			static int indexOfCode(const char c);
	};
}

#endif
