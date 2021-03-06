///> [Serializable]
#ifndef EXECUTIONHISTORY_H
#define EXECUTIONHISTORY_H

#include "ExecutionTrial.h"
#include "ConditionEx.h"
#include "EngineObject.h"

namespace IStrategizer
{
    ///> class=ExecutionHistory
    class ExecutionHistory : public EngineObject
    {
		OBJECT_SERIALIZABLE(ExecutionHistory, &m_history);
    public:
        double GetFailureProbability() const;
        void Add(ExecutionStateType state);
        void Add(ExecutionStateType state, ConditionEx* failedAliveCondition);
        void AddRange(ExecutionHistory other);
        ConditionEx* GetMostVulnerableAliveCondition() const;
        bool IsEmpty() const { return m_history.empty(); }
        int TrialCount () const { return (int)m_history.size(); }

    private:
        ExecutionTrial::List FailedTrials() const;
        ///> type=vector(ExecutionTrial)
        ExecutionTrial::List m_history;
    };
}

#endif // EXECUTIONHISTORY_H