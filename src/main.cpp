#include <string>
#include <iostream>

#include "..\lib\SDK\amx\amx.h"
#include "..\lib\SDK\plugincommon.h"

using namespace std;

typedef void(*logprintf_t)(char* format, ...);


logprintf_t logprintf;
extern void *pAMXFunctions;

cell AMX_NATIVE_CALL CaesarCrypt(AMX * amx, cell * params)
{
	int len;
	int step = params[2];
	int fAlph;
	cell *string;

	char fChar;

	amx_GetAddr(amx, params[1], &string);
	amx_StrLen(string, &len);

	char * input = "";
	input = new char[len + 1];

	amx_GetString(input, string, 0, len + 1);

	for (int i = 0; i < len; i++) {
		if (input[i] == ' ' || input[i] == '!' || input[i] == '@' || input[i] == '-' || input[i] == '_' || input[i] == '+' || input[i] == '=' || input[i] == '.' || input[i] == ',') continue;
		if (input[i] >= 'A' && input[i] <= 'Z') {
			fChar = 'A';
			fAlph = 26;
		}
		else if (input[i] >= 'a' && input[i] <= 'z') {
			fChar = 'a';
			fAlph = 26;
		}
		else if ((input[i] >= 'À' && input[i] <= 'ß') || input[i] == '¨') {
			fChar = 'À';
			fAlph = 32;
		}
		else if ((input[i] >= 'à' && input[i] <= 'ÿ') || input[i] == '¸') {
			fChar = 'à';
			fAlph = 32;
		}
		else {
			continue;
		}

		if (!(step % fAlph)) {
			continue;
		}
		input[i] = (fChar + (input[i] - fChar + step) % fAlph);
	}
	std::string str = std::string(input);
	amx_SetString(string, str.c_str(), 0, 0, params[3]);

	return 1;
}

cell AMX_NATIVE_CALL CaesarDeCrypt(AMX * amx, cell * params)
{
	int len;
	int step = params[2];
	int fAlph;
	cell *string;

	char fChar;

	amx_GetAddr(amx, params[1], &string);
	amx_StrLen(string, &len);

	char * input = "";
	input = new char[len + 1];

	amx_GetString(input, string, 0, len + 1);


	for (int i = 0; i < len; i++) {
		if (input[i] == ' ' || input[i] == '!' || input[i] == '@' || input[i] == '-' || input[i] == '_' || input[i] == '+' || input[i] == '=' || input[i] == '.' || input[i] == ',') continue;
		if (input[i] >= 'A' && input[i] <= 'Z') {
			fChar = 'A';
			fAlph = 26;
		}
		else if (input[i] >= 'a' && input[i] <= 'z') {
			fChar = 'a';
			fAlph = 26;
		}
		else if ((input[i] >= 'À' && input[i] <= 'ß') || input[i] == '¨') {
			fChar = 'À';
			fAlph = 32;
		}
		else if ((input[i] >= 'à' && input[i] <= 'ÿ') || input[i] == '¸') {
			fChar = 'à';
			fAlph = 32;
		}
		else {
			continue;
		}

		if (!(step % fAlph)) {
			continue;
		}
		input[i] = (fChar + (input[i] - fChar - step) % fAlph);
	}

	std::string str = std::string(input);
	amx_SetString(string, str.c_str(), 0, 0, params[3]);

	return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf(" * Regasen.Crypt was loaded.");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf(" * Regasen.Crypt was unloaded.");
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "CaesarCrypt", CaesarCrypt },
	{ "CaesarDeCrypt", CaesarDeCrypt },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
