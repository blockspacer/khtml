/*
 * This file is part of the DOM implementation for KDE.
 *
 * Copyright (C) 2000 Peter Kelly (pmk@post.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef _XML_Tokenizer_h_
#define _XML_Tokenizer_h_

#include <qxml.h>
#include <QStack>
#include <QLinkedList>
#include <QMap>
#include <QObject>
#include "misc/loader_client.h"
#include "misc/stringit.h"

class KHTMLView;

namespace khtml
{
class CachedObject;
class CachedScript;
}

namespace DOM
{
class DocumentImpl;
class NodeImpl;
class HTMLScriptElementImpl;
class DocumentImpl;
class HTMLScriptElementImpl;
}

namespace khtml
{

class XMLHandler : public QXmlDefaultHandler
{
public:
    XMLHandler(DOM::DocumentImpl *_doc, KHTMLView *_view);
    virtual ~XMLHandler();

    // return the error protocol if parsing failed
    QString errorProtocol();

    // overloaded handler functions
    bool startDocument() override;
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts) override;
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName) override;
    bool startCDATA() override;
    bool endCDATA() override;
    bool characters(const QString &ch) override;
    bool comment(const QString &ch) override;
    bool processingInstruction(const QString &target, const QString &data) override;
    bool startDTD(const QString &name, const QString &publicId, const QString &systemId) override;
    bool endDTD() override;

    // namespace handling, to workaround problem in QXML where some attributes
    // do not get the namespace resolved properly
    bool startPrefixMapping(const QString &prefix, const QString &uri) override;
    bool endPrefixMapping(const QString &prefix) override;
    void fixUpNSURI(QString &uri, const QString &qname);
    QMap<QString, QStack<QString> > namespaceInfo;

    // from QXmlDeclHandler
    bool attributeDecl(const QString &eName, const QString &aName, const QString &type, const QString &valueDefault, const QString &value) override;
    bool externalEntityDecl(const QString &name, const QString &publicId, const QString &systemId) override;
    bool internalEntityDecl(const QString &name, const QString &value) override;

    // from QXmlDTDHandler
    bool notationDecl(const QString &name, const QString &publicId, const QString &systemId) override;
    bool unparsedEntityDecl(const QString &name, const QString &publicId, const QString &systemId, const QString &notationName) override;

    bool enterText();
    void exitText();

    QString errorString() const override;

    bool fatalError(const QXmlParseException &exception) override;

    int errorLine;
    int errorCol;

private:
    void pushNode(DOM::NodeImpl *node);
    DOM::NodeImpl *popNode();
    DOM::NodeImpl *currentNode() const;
private:
    QString errorProt;
    DOM::DocumentImpl *m_doc;
    KHTMLView *m_view;
    QStack<DOM::NodeImpl *> m_nodes;
    DOM::NodeImpl *m_rootNode;

    enum State {
        StateInit,
        StateDocument,
        StateQuote,
        StateLine,
        StateHeading,
        StateP
    };
    State state;
};

class Tokenizer : public QObject
{
    Q_OBJECT
public:
    virtual void begin() = 0;
    // script output must be prepended, while new data
    // received during executing a script must be appended, hence the
    // extra bool to be able to distinguish between both cases. document.write()
    // always uses false, while khtmlpart uses true
    virtual void write(const TokenizerString &str, bool appendData) = 0;
    virtual void end() = 0;
    virtual void finish() = 0;
    virtual void setOnHold(bool /*_onHold*/) {}
    virtual bool isWaitingForScripts() const = 0;
    virtual bool isExecutingScript() const = 0;
    virtual void setNormalYieldDelay() {}
    virtual void abort() {}

    virtual void executeScriptsWaitingForStylesheets() = 0;

Q_SIGNALS:
    void finishedParsing();

};

class XMLIncrementalSource : public QXmlInputSource
{
public:
    XMLIncrementalSource();
    void fetchData() override;
    QChar next() override;
    void setData(const QString &str) override;
    void setData(const QByteArray &data) override;
    QString data() const override;

    void appendXML(const QString &str);
    void setFinished(bool);

    inline void setPaused(bool paused = true)
    {
        m_paused = paused;
    }

private:
    QString      m_data;
    int          m_pos;
    const QChar *m_unicode;
    bool         m_finished;
    bool         m_paused; // if waiting for scripts
};

class XMLTokenizer : public Tokenizer, public khtml::CachedObjectClient
{
public:
    XMLTokenizer(DOM::DocumentImpl *, KHTMLView * = nullptr);
    virtual ~XMLTokenizer();
    void begin() override;
    void write(const TokenizerString &str, bool) override;
    void end() override;
    void finish() override;

    // from CachedObjectClient
    void notifyFinished(khtml::CachedObject *finishedObj) override;

    void executeScriptsWaitingForStylesheets() override {}

    bool isWaitingForScripts() const override;
    bool isExecutingScript() const override
    {
        return m_executingScript;
    }

    // execute script in place, if it contains src attribute we stop parsing till it's downloaded
    void executeScript(DOM::NodeImpl *n);

protected:
    DOM::DocumentImpl *m_doc;
    KHTMLView *m_view;

    khtml::CachedScript *m_cachedScript;

    QString m_bufferedData;

    XMLHandler m_handler;
    QXmlSimpleReader m_reader;
    XMLIncrementalSource m_source;
    bool m_noErrors;
    bool m_executingScript;
    bool m_explicitFinishParsingNeeded;
    bool m_insideWrite;
};

} // end namespace

#endif
