#include "UpLoadFile.h"

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
        ERROR_TYPE getError;
        bool statue = testFunc(lenght,input,getError);
        char reply[1024];
        if(statue == false)
        {
            FCGX_FPrintF(output, "Content-type: application/json\r\n"
                            "Charset: utf-8\r\n"
                            "\r\n"
                            "{\"upload_status\":\"Failed\"}");  
        }
        else
        {
            FCGX_FPrintF(output, "Content-type: application/json\r\n"
                            "Charset: utf-8\r\n"
                            "\r\n"
                            "{\"upload_status\":\"Success\"}");       
        }
    }
    return 0;
}