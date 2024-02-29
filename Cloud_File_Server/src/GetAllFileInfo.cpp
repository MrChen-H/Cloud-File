#include "GetAllFileInfo.h"

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

        std::string res_info = GetPathInfo(lenght,input,information);
        char reply[1024];
        if(res_info.empty())
        {
            FCGX_FPrintF(output, "Content-type: application/json\r\n"
                             "Charset: utf-8\r\n"
                             "\r\n"
                             "{\"file_name\":\"null\"}");   
        }
        // 数据回写
        FCGX_FPrintF(output, "Content-type: application/json\r\n"
                             "Charset: utf-8\r\n"
                             "\r\n"
                             "%s",res_info.c_str());   
    }
    return 0;
}