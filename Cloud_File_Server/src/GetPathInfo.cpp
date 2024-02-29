#include "GetPathInfo.h"
using json = nlohmann::json;
int main()
{
    FCGX_Stream *input, *output, *error;
    FCGX_ParamArray evnp;
    
    while (FCGX_Accept(&input, &output, &error, &evnp) >= 0) // 阻塞
    {
        std::string Get_Client_Data;
        std::string Data;
        char *pRequestMoethod = FCGX_GetParam("REQUEST_METHOD", evnp);
        if (pRequestMoethod == NULL)
        {
            break;
        }
        char *pLenstr = FCGX_GetParam("CONTENT_LENGTH", evnp);
        if (pLenstr == NULL)
        {
            break;
        }
        auto lenght = atoi(pLenstr);
        std::string information;
        char reply[128];
        sprintf(reply,"{\"info\":\"%s\"}",information.c_str());
        // 数据回写
        FCGX_FPrintF(output, "Content-type: application/json\r\n"
                             "Charset: utf-8\r\n"
                             "\r\n"
                             "{""testServer"":""success""}");   
    }
    return 0;
}