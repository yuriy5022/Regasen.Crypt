#if defined crypt_included
	#endinput
#endif
#define crypt_included

native CaesarCrypt(string[], step, len = sizeof(string));
native CaesarDeCrypt(string[], step, len = sizeof(string));