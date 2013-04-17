#include "stdafx.h"
#include "ipu.h"

void IPU::updateLog(void*)
{
    IPU::getInstance().m_logThreadActive=true;
    for(;IPU::getInstance().m_logThreadExitSign==false;)
    {
        {
            AutoCS(&IPU::getInstance().m_csLog);

            if(0<IPU::getInstance().m_logString.str().size())
            {

                if(IsWindow(IPU::getInstance().m_hLog))
                {
                    SendMessage(IPU::getInstance().m_hLog,EM_SETSEL,-2,-1);
                    SendMessage(IPU::getInstance().m_hLog,EM_REPLACESEL,FALSE,(LPARAM)IPU::getInstance().m_logString.str().c_str());
                    IPU::getInstance().m_logString.str(L"");
                }
            }
        }

        Sleep(1000);

    }
    IPU::getInstance().m_logThreadActive=false;
    _endthread();
}
