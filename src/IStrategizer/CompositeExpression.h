///> [Serializable]
#ifndef COMPOSITEEXPRESSION_H
#define COMPOSITEEXPRESSION_H

#include "Expression.h"

namespace IStrategizer
{
    ///> class=CompositeExpression
    ///> parent=Expression
    class CompositeExpression : public Expression
    {
		OBJECT_SERIALIZABLE_P(CompositeExpression, Expression, &_expressions, &_shortCircuit);
    protected:
        ///> type=vector(Expression*)
        Serialization::SVector<Expression*> _expressions;
        ///> type=bool
        bool _shortCircuit;

        Expression* GetTermAux(int p_currentIndex, int p_targetIndex);

    public:
        CompositeExpression() {}
        CompositeExpression(const std::vector<Expression*>& p_expressions) : Expression(EXPRESSION_Composite), _expressions(p_expressions), _shortCircuit(true) {}
        CompositeExpression(Expression* p_expression) : Expression(EXPRESSION_Composite), _shortCircuit(true) { _expressions.push_back(p_expression); }
		~CompositeExpression();
        bool AddExpression(Expression* p_expression);
        bool RemoveExpression(Expression* p_expression);
        bool Equals(const Expression* p_rhs) const;
        bool PartiallyEqualsAux(const Expression* p_rhs, MatchSide p_anchor, std::vector<std::pair<Expression*,Expression*>>& p_matchedLeafs) const;
        bool ShortCircuit() const { return _shortCircuit; }
        void ShortCircuit(bool val) { _shortCircuit = val; }
        const std::vector<Expression*>& Expressions() const { return _expressions; }
        void Clear();
        Expression* operator[](int p_index);
        Expression* At(int p_index);
        void Copy(IClonable* p_dest);
    };
}

#endif // _H
