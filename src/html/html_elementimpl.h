/*
 * This file is part of the DOM implementation for KDE.
 *
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
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
#ifndef HTML_ELEMENTIMPL_H
#define HTML_ELEMENTIMPL_H

#include "xml/dom_elementimpl.h"

namespace DOM
{

class DOMString;
class DocumentFragment;

class HTMLElementImpl : public ElementImpl
{
public:
    HTMLElementImpl(DocumentImpl *doc);

    virtual ~HTMLElementImpl();

    bool isHTMLElement() const Q_DECL_OVERRIDE
    {
        return true;
    }

    bool isInline() const Q_DECL_OVERRIDE;

    Id id() const Q_DECL_OVERRIDE = 0;
    DOMString namespaceURI() const Q_DECL_OVERRIDE;

    void parseAttribute(AttributeImpl *token) Q_DECL_OVERRIDE;

    void addCSSLength(int id, const DOMString &value, bool numOnly = false, bool multiLength = false);
    void addCSSProperty(int id, const DOMString &value);
    void addCSSProperty(int id, int value);
    void addHTMLColor(int id, const DOMString &c);
    void removeCSSProperty(int id);

    void recalcStyle(StyleChange) Q_DECL_OVERRIDE;

    DOMString innerHTML() const;
    DOMString innerText() const;
    DocumentFragment createContextualFragment(const DOMString &html);
    void setInnerHTML(const DOMString &html, int &exceptioncode);
    void setInnerText(const DOMString &text, int &exceptioncode);

    virtual DOMString contentEditable() const;
    virtual void setContentEditable(AttributeImpl *attr);
    virtual void setContentEditable(const DOMString &enabled);

    DOMString toString() const Q_DECL_OVERRIDE;

protected:
    // for IMG, OBJECT and APPLET
    void addHTMLAlignment(DOMString alignment);
};

class HTMLGenericElementImpl : public HTMLElementImpl
{
public:
    HTMLGenericElementImpl(DocumentImpl *doc, ushort i);
    HTMLGenericElementImpl(DocumentImpl *doc, LocalName name);

    virtual ~HTMLGenericElementImpl();

    Id id() const Q_DECL_OVERRIDE
    {
        return m_localName.id();
    }

protected:
    LocalName m_localName;
};

} //namespace

#endif
