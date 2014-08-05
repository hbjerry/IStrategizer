#ifndef ISTRATEGIZEREX_H
#define ISTRATEGIZEREX_H

#include "RtsAiEngine.h"
#include "MetaData.h"
#include "IMessagePumpObserver.h"
#include "WorldClock.h"
#include "CombatManager.h"
#include "WorkersManager.h"
#include "ScoutManager.h"
#include "EngineDefs.h"
#include <vector>
#include <memory>

extern std::string ENGINE_IO_READ_DIR;
extern std::string ENGINE_IO_WRITE_DIR;

namespace IStrategizer
{
    class MessagePump;
    class GameTrace;
    class CaseBaseEx;
    class LearningFromHumanDemonstration;
    class OnlineCaseBasedPlannerEx;
    class RtsGame;
    class BotStatistics;

    class IStrategizerEx : public EngineObject, public IRtsAiEngine
    {
    public:
        static const int BordersRadius = 1024;
        static const int ReviseSituationInterval = 16;

        IStrategizerEx(const EngineParams &param, RtsGame* pGame);
        void Update();
        bool Init();
        void NotifyMessegeSent(Message* pMsg);
        const OnlineCaseBasedPlannerEx* Planner() const { return &*m_pPlanner; }
        OnlineCaseBasedPlannerEx* Planner() { return &*m_pPlanner; }
        WorkersManager& WorkersMgr() { return m_workersMgr; }
        ScoutManager& ScoutMgr() { return m_scoutMgr; }
        Vector2F BaseHeadDirection() const { return m_baseFaceDir; }
        SituationType Situation() const { return m_situation; }
        void ReviseSituation();
        ~IStrategizerEx();

        void SendEngineMessage(_In_ MessageType msgTypeId);
        void SendEngineEntityMessage(_In_ MessageType msgTypeId, _In_ const EntityMessageData& msgData);
        void SetEngineReadWriteDir(_In_ const char* pReadPath, _In_ const char* pWritePath);

    private:
        DISALLOW_COPY_AND_ASSIGN(IStrategizerEx);

        const unsigned ScoutStartFrame = 2000;
        void DebugDraw();
        void SelectNextStrategyGoal();

        bool m_isFirstUpdate;
        std::shared_ptr<LearningFromHumanDemonstration> m_pCaseLearning;
        EngineParams m_param;
        std::shared_ptr<BotStatistics> m_pStatistics;

        std::shared_ptr<OnlineCaseBasedPlannerEx> m_pPlanner;
        CombatManager m_combatMgr;
        ScoutManager m_scoutMgr;
        WorkersManager m_workersMgr;
        Vector2F m_baseFaceDir;
        SituationType m_situation;
        Circle2 m_borders;
        StrategySelectorPtr m_pConsultant;
    };
}

extern IStrategizer::IStrategizerEx* g_Engine;

#endif // ISTRATEGIZEREX_H