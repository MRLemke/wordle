#include <cstdio>
#include <string>

using namespace std;

string execute (const string & cmd)
{
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe)
	return "ERROR";
    char buffer[128];
    string result = "";
    while (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    pclose(pipe);
    return result;
}
