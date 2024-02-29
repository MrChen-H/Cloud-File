#include "globalstatus.h"


GlobalStatus* GlobalStatus::Instance = new GlobalStatus();

GlobalStatus::GlobalStatus(QObject *parent)
    : QObject{parent}
{

}

GlobalStatus *GlobalStatus::getInstance()
{
    return Instance;
}




