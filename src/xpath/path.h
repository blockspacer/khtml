/*
 * path.h - Copyright 2005 Frerich Raabe <raabe@kde.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef PATH_H
#define PATH_H

#include "expression.h"
#include "step.h"

#include <QList>

int khtmlxpathyyparse();

namespace khtml
{
namespace XPath
{

class Filter : public Expression
{
public:
    Filter(Expression *expr,
           const QList<Predicate *> &predicates = QList<Predicate *>());
    virtual ~Filter();

    QString dump() const override;

private:
    Value doEvaluate() const override;

    Expression *m_expr;
    QList<Predicate *> m_predicates;
};

class LocationPath : public Expression
{
    friend int ::khtmlxpathyyparse();
public:
    LocationPath();
    virtual ~LocationPath();

    void optimize();
    QString dump() const override;

private:
    Value doEvaluate() const override;

    QList<Step *> m_steps;
    bool m_absolute;
};

class Path : public Expression
{
public:
    Path(Filter *filter, LocationPath *path);
    virtual ~Path();

    QString dump() const override;

private:
    Value doEvaluate() const override;

    Filter *m_filter;
    LocationPath *m_path;
};

} // namespace XPath

} // namespace khtml

#endif // PATH_H

