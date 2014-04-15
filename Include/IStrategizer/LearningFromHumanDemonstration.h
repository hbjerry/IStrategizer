#ifndef LEARNINGFROMHUMANDEMONSTRATION_H
#define LEARNINGFROMHUMANDEMONSTRATION_H

#include <vector>
#include <map>
#include "EngineData.h"
#include "CompositeExpression.h"
#include "CaseLearningHelper.h"
#include "RtsGame.h"

namespace IStrategizer
{
    class GameTrace;
    class Action;
    class RetainerEx;

    const int TIME_STAMP_SIZE_EX = 1;

    typedef std::vector<PlanStepEx*> SequentialPlan;

    class RawPlanEx
    {
    public:
        GoalEx* Goal;
        SequentialPlan sPlan;

        RawPlanEx(){}
        RawPlanEx(GoalEx* p_goal, SequentialPlan p_sPlan): Goal(p_goal), sPlan(p_sPlan){}
    };

    class RawCaseEx
    {
    public:
        RawPlanEx rawPlan;
        RtsGame* gameState;

        RawCaseEx() {}
        RawCaseEx(RawPlanEx p_rawPlan, RtsGame* p_gameState): rawPlan(p_rawPlan), gameState(p_gameState) {}
    };

    class CookedPlan
    {
    public:
        GoalEx* Goal;
        RtsGame* gameState;
        OlcbpPlan* pPlan;

        CookedPlan(){}
        CookedPlan(GoalEx* p_goal, OlcbpPlan* p_pPlan, RtsGame* p_gameState): Goal(p_goal), pPlan(p_pPlan), gameState(p_gameState) {}
    };

    class CookedCase
    {
    public:
        RawCaseEx* rawCase;
        OlcbpPlan* plan;

        CookedCase(){}
        CookedCase(RawCaseEx* p_rawCase, OlcbpPlan* p_plan): rawCase(p_rawCase), plan(p_plan) {}
    };

    class LearningFromHumanDemonstration
    {
    private:
        CaseLearningHelper* _helper;
        RetainerEx* _retainer;

        void AddAction(RawCaseEx* p_case, ActionType p_action, const PlanStepParameters& p_params, int p_traceId);
        void NecessaryStepsExtraction(OlcbpPlan* p_graph, unsigned p_sIndex, SequentialPlan& p_fSteps, const SequentialPlan& p_steps);
        void UnnecessaryStepsElimination(CookedCase* p_case);
        void HierarchicalComposition(CookedPlan* p_plan, const std::vector<CookedPlan*>& p_plans, unsigned p_index);
        void RetainLearntCases(std::vector<CookedPlan*>& p_cookedPlans);
        bool Depends(CompositeExpression* p_candidateNode, CompositeExpression* p_dependentNode, std::vector<Expression*>& p_matchedConditions);
        bool IdenticalSequentialPlan(SequentialPlan left, SequentialPlan right);
        CookedPlan* PlanParallelization(OlcbpPlan* p_graph, RawPlanEx* p_steps);
        CookedCase* DependencyGraphGeneration(RawCaseEx* p_rawCases);
        vector<RawCaseEx*> LearnRawCases(GameTrace::List p_traces);

    public:
        LearningFromHumanDemonstration(PlayerType p_player, PlayerType p_enemy);
        virtual ~LearningFromHumanDemonstration();
        void Learn();
    };
}

#endif // LEARNINGFROMHUMANDEMONSTRATION_H
