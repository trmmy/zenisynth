#include "stdafx.h"
#include "ipu.h"
void IPU::addLog(std::wstring& str)
{
    AutoCS(&IPU::getInstance().m_csLog);
    IPU::getInstance().m_logString<<str;
}
