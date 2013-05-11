
#include "charset.h"
using namespace std;

Charset getCharset(ifstream& file) {
	Charset charset = lireBOM(file);
	if(charset > CHARSET_BOM_NOT_FIND) {
		return charset;
	}
	return findCharset(file);
}

Charset lireBOM(ifstream& file) {
	unsigned char c1 = file.get(), c2 = file.get();
	// UTF-16 Big Endian	FE FF
	if(c1 == 0xfe && c2 == 0xff) {
		return CHARSET_UTF16;
	}
	// UTF-16 Little Endian	FF FE
	else if(c1 == 0xff && c2 == 0xfe) {
		return CHARSET_UTF16;
	}

	unsigned char c3 = file.get();
	// UTF-8	EF BB BF
	if(c1 == 0xef && c2 == 0xbb && c3 == 0xbf) {
		return CHARSET_UTF8;
	}
	// SCSU	0E FE FF
	else if(c1 == 0x0e && c2 == 0xfe && c3 == 0xff) {
		return CHARSET_SCSU;
	}
	// UTF-7	2B 2F 76
	else if(c1 == 0x2b && c2 == 0x2f && c3 == 0x76) {
		return CHARSET_UTF7;
	}
	// BOCU-1	FB EE 28
	else if(c1 == 0xfb && c2 == 0xee && c3 == 0x28) {
		return CHARSET_BOCU1;
	}

	unsigned char c4 = file.get();
	// UTF-32 Big Endian	00 00 FE FF
	if(c1 == 0x00 && c2 == 0x00 && c3 == 0xfe && c4 == 0xff) {
		return CHARSET_UTF32;
	}
	// UTF-32 Little Endian	FF FE 00 00
	else if(c1 == 0xff && c2 == 0xfe && c3 == 0x00 && c4 == 0x00) {
		return CHARSET_UTF32;
	}
	// UTF-EBCDIC	DD 73 66 73
	else if(c1 == 0xdd && c2 == 0x73 && c3 == 0x66 && c4 == 0x73) {
		return CHARSET_UTF_EBCDIC;
	}

	file.seekg(0, ios::beg);
	// Fichier sans BOM
	return CHARSET_BOM_NOT_FIND;
}

Charset findCharset(ifstream& file) {
	const unsigned char UTF8_1ST_OF_1 = 0; // 0xxx xxxx
	const unsigned char UTF8_1ST_OF_2 = 0xc0; // 110x xxxx
	const unsigned char UTF8_1ST_OF_3 = 0xe0; // 1110 xxxx
	const unsigned char UTF8_TRAIL = 0x80; // 10xx xxxx
	char getC;
	unsigned char c;
	bool ascii = true;
	unsigned char inChar = 0;
	int i, l;

	file.seekg(0, ios::end);
	l = file.tellg();
	file.seekg(0, ios::beg);
	for(i = 0; i < l; ++i) {
		file.get(getC);
		c = getC;
		// Caractère non ASCII, peut être UTF-8 ou latin1(ou 9)
		if(c >= UTF8_TRAIL) {
			ascii = false;
			if(c >= UTF8_1ST_OF_2) {
				if(inChar > 0) {
					file.seekg(0, ios::beg);
					return CHARSET_ISO_8859;
				}
				else if(c >= UTF8_1ST_OF_3) {
					inChar++;
				}
				inChar++;
			}
			else if(inChar > 0) {
				inChar--;
			}
			else {
				file.seekg(0, ios::beg);
				return CHARSET_ISO_8859;
			}
		}
		else if(inChar > 0) {
			file.seekg(0, ios::beg);
			return CHARSET_ISO_8859;
		}
	}
	file.seekg(0, ios::beg);
	if(ascii) {
		return CHARSET_ASCII;
	}
	else {
		return CHARSET_UTF8;
	}
}

/**
	* Functions to Convert beetween different charset
	* author Julien Folly (2006)
	* edited by Frédéric Turpin (2011.12.25)
	* version C++ 1.0
	*/
// ISO-8859-15 -> UTF-8
string iso8859ToUtf8(string capSrc) {
	const unsigned char ISO_8859 = 0xff; // 8 Bits
	const unsigned char UTF8_MAX_IN_1 = 0x7f; // 7 bits (2^7-1)
	const unsigned short UTF8_MAX_IN_2 = 0x7ff; // 11 bits (2^11-1)
	const unsigned int  UTF8_MAX_IN_3 = 0xffff; // 16 bits (2^16-1)
	const unsigned char UTF8_1ST_OF_1 = 0; // 0xxx xxxx
	const unsigned char UTF8_1ST_OF_2 = 0xc0; // 110x xxxx
	const unsigned char UTF8_1ST_OF_3 = 0xe0; // 1110 xxxx
	const unsigned char UTF8_TRAIL = 0x80; // 10xx xxxx
	unsigned int i;
	unsigned int iSrcLen = capSrc.size(); // Longueur de la chaîne latin1
	vector<unsigned short> wcapSrc; // Chaîne Unicode
	string capDest = ""; // Chaîne UTF-8

	for(i = 0 ; i < iSrcLen ; ++i) {
		wcapSrc.push_back(capSrc[i] & ISO_8859);
		// Found 1 bits sequence (ASCII)
		if(wcapSrc[i] <= UTF8_MAX_IN_1) {
			capDest.push_back(wcapSrc[i]);
		}
		// Found 2 bits sequence
		else if(wcapSrc[i] <= UTF8_MAX_IN_2) {
			capDest.push_back(UTF8_1ST_OF_2 | (wcapSrc[i] >> 6 ));
			capDest.push_back(UTF8_TRAIL | (wcapSrc[i] & 0x3F));
		}
		// Found 3 bits sequence
		else {
			capDest.push_back(UTF8_1ST_OF_3 | (wcapSrc[i] >> 12));
			capDest.push_back(UTF8_TRAIL | ((wcapSrc[i] >> 6) & 0x3F));
			capDest.push_back(UTF8_TRAIL | (wcapSrc[i] & 0x3F));
		}
	}
	return capDest;
}

