#include "PidControllerStateMachine.h"
#include "esp_log.h"

#include "MAX6675.h"

CDataLogStateMachine* CDataLogStateMachine::mspDataLogStateMachine = NULL;
static const char* TAG = "StateMachine:";

CDataLogStateMachine::CDataLogStateMachine(void)
    : mLogState(LogStateInactive)
{
    mQueueHdl = xQueueCreate(100, sizeof(SLogData));
    mpTempMeasurement = new MAX6675(5);
}

void CDataLogStateMachine::CreateInstance(void)
{
    if (mspDataLogStateMachine == NULL) mspDataLogStateMachine = new CDataLogStateMachine();
}

CDataLogStateMachine* CDataLogStateMachine::GetInstance(void)
{
    return mspDataLogStateMachine;
}

CDataLogStateMachine::~CDataLogStateMachine()
{
    delete mspDataLogStateMachine;
    mspDataLogStateMachine = NULL;
}

void CDataLogStateMachine::Init()
{

}

void CDataLogStateMachine::Receive()
{
    switch (mLogState.load())
    {
    case LogStateLogging:
        {
            std::string dataString;
            char newElement[64];
            SLogData logData;

            while(xQueueReceive(mQueueHdl, &logData, (TickType_t)0))
            {
                 //todo hier später tcp auswerten der Daten
            }
        }
        break;
 
    case LogStateInactive:
    default:
        break;
    }
}

void CDataLogStateMachine::Send()
{
    static SLogData logData;

    switch (mLogState.load())
    {
    case LogStateLogging:
        {
            if (mpTempMeasurement)       
                {logData.actualTemp  = mpTempMeasurement->ReadTemperatureCelcius();
                ESP_LOGI(TAG,"SEND");}

            if (mQueueHdl)
            {
                xQueueSend(mQueueHdl, (void *)&logData, (TickType_t) 0);
            }
        }
        break;
    default: break;
    }
}
