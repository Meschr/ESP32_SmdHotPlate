#ifndef _DATALOGSTATEMACHINE_hf
#define _DATALOGSTATEMACHINE_hf

#include <atomic>
#include <fstream>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "LogData.h"

#include "MAX6675.h"

class CDataLogStateMachine
{
public:
    enum ELogState
    {
        LogStateInactive = 0,
        LogStateLogging
    };

    static void CreateInstance(void);
    static CDataLogStateMachine* GetInstance(void);
    ~CDataLogStateMachine(void);

    void Init(void);
    void Receive(void);
    void Send(void);

    bool IsLogging(void) { return (mLogState.load() == LogStateLogging); }

private:
    CDataLogStateMachine(void);
    CDataLogStateMachine(CDataLogStateMachine const&);  // Don't implement
    void operator=(CDataLogStateMachine const&);        // Don't implement

    static CDataLogStateMachine* mspDataLogStateMachine;

    QueueHandle_t           mQueueHdl;
    MAX6675*                mpTempMeasurement;
    std::atomic<ELogState>  mLogState;
    std::atomic_bool        mMarker;
};

#endif // #ifndef _DATALOGSTATEMACHINE_hf
