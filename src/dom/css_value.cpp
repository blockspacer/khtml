/*
 * This file is part of the DOM implementation for KDE.
 *
 * Copyright 1999 Lars Knoll (knoll@kde.org)
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

#include "dom/css_rule.h"
#include "dom/dom_exception.h"

#include "css/css_renderstyledeclarationimpl.h"
#include "css/css_valueimpl.h"

namespace DOM
{

CSSStyleDeclaration::CSSStyleDeclaration()
{
    impl = nullptr;
}

CSSStyleDeclaration::CSSStyleDeclaration(const CSSStyleDeclaration &other)
{
    impl = other.impl;
    if (impl) {
        impl->ref();
    }
}

CSSStyleDeclaration::CSSStyleDeclaration(CSSStyleDeclarationImpl *i)
{
    impl = i;
    if (impl) {
        impl->ref();
    }
}

CSSStyleDeclaration &CSSStyleDeclaration::operator = (const CSSStyleDeclaration &other)
{
    if (impl != other.impl) {
        if (impl) {
            impl->deref();
        }
        impl = other.impl;
        if (impl) {
            impl->ref();
        }
    }
    return *this;
}

CSSStyleDeclaration::~CSSStyleDeclaration()
{
    if (impl) {
        impl->deref();
    }
}

DOMString CSSStyleDeclaration::cssText() const
{
    if (!impl) {
        return DOMString();
    }
    return static_cast<CSSStyleDeclarationImpl *>(impl)->cssText();
}

void CSSStyleDeclaration::setCssText(const DOMString &value)
{
    if (!impl) {
        return;
    }
    impl->setCssText(value);
}

DOMString CSSStyleDeclaration::getPropertyValue(const DOMString &propertyName) const
{
    if (!impl) {
        return DOMString();
    }
    return static_cast<CSSStyleDeclarationImpl *>(impl)->getPropertyValue(propertyName);
}

CSSValue CSSStyleDeclaration::getPropertyCSSValue(const DOMString &propertyName) const
{
    if (!impl) {
        return nullptr;
    }
    return static_cast<CSSStyleDeclarationImpl *>(impl)->getPropertyCSSValue(propertyName);
}

DOMString CSSStyleDeclaration::removeProperty(const DOMString &propertyName)
{
    if (!impl) {
        return DOMString();
    }
    return static_cast<CSSStyleDeclarationImpl *>(impl)->removeProperty(propertyName);
}

DOMString CSSStyleDeclaration::getPropertyPriority(const DOMString &propertyName) const
{
    if (!impl) {
        return DOMString();
    }
    return impl->getPropertyPriority(propertyName);
}

void CSSStyleDeclaration::setProperty(const DOMString &propName, const DOMString &value, const DOMString &priority)
{
    if (!impl) {
        return;
    }
    if (value.isEmpty()) {
        static_cast<CSSStyleDeclarationImpl *>(impl)->removeProperty(propName);
        return;
    }
    static_cast<CSSStyleDeclarationImpl *>(impl)->setProperty(propName, value, priority);
}

unsigned long CSSStyleDeclaration::length() const
{
    if (!impl) {
        return 0;
    }
    return static_cast<CSSStyleDeclarationImpl *>(impl)->length();
}

DOMString CSSStyleDeclaration::item(unsigned long index) const
{
    if (!impl) {
        return DOMString();
    }
    return static_cast<CSSStyleDeclarationImpl *>(impl)->item(index);
}
CSSRule CSSStyleDeclaration::parentRule() const
{
    if (!impl) {
        return nullptr;
    }
    return static_cast<CSSStyleDeclarationImpl *>(impl)->parentRule();
}

CSSStyleDeclarationImpl *CSSStyleDeclaration::handle() const
{
    return impl;
}

bool CSSStyleDeclaration::isNull() const
{
    return (impl == nullptr);
}

// ----------------------------------------------------------

CSSValue::CSSValue()
{
    impl = nullptr;
}

CSSValue::CSSValue(const CSSValue &other)
{
    impl = other.impl;
    if (impl) {
        impl->ref();
    }
}

CSSValue::CSSValue(CSSValueImpl *i)
{
    impl = i;
    if (impl) {
        impl->ref();
    }
}

CSSValue &CSSValue::operator = (const CSSValue &other)
{
    if (impl != other.impl) {
        if (impl) {
            impl->deref();
        }
        impl = other.impl;
        if (impl) {
            impl->ref();
        }
    }
    return *this;
}

CSSValue::~CSSValue()
{
    if (impl) {
        impl->deref();
    }
}

DOMString CSSValue::cssText() const
{
    if (!impl) {
        return DOMString();
    }
    return ((CSSValueImpl *)impl)->cssText();
}

void CSSValue::setCssText(const DOMString &value)
{
    if (!impl) {
        return;
    }
    ((CSSValueImpl *)impl)->setCssText(value);
}

unsigned short CSSValue::cssValueType() const
{
    if (!impl) {
        return 0;
    }
    return ((CSSValueImpl *)impl)->cssValueType();
}

bool CSSValue::isCSSValueList() const
{
    if (!impl) {
        return false;
    }
    return ((CSSValueImpl *)impl)->isValueList();
}

bool CSSValue::isCSSPrimitiveValue() const
{
    if (!impl) {
        return false;
    }
    return ((CSSValueImpl *)impl)->isPrimitiveValue();
}

CSSValueImpl *CSSValue::handle() const
{
    return impl;
}

bool CSSValue::isNull() const
{
    return (impl == nullptr);
}

// ----------------------------------------------------------

CSSValueList::CSSValueList() : CSSValue()
{
}

CSSValueList::CSSValueList(const CSSValueList &other) : CSSValue(other)
{
}

CSSValueList::CSSValueList(const CSSValue &other)
{
    impl = nullptr;
    operator=(other);
}

CSSValueList::CSSValueList(CSSValueListImpl *impl) : CSSValue(impl)
{
}

CSSValueList &CSSValueList::operator = (const CSSValueList &other)
{
    if (impl != other.impl) {
        if (impl) {
            impl->deref();
        }
        impl = other.handle();
        if (impl) {
            impl->ref();
        }
    }
    return *this;
}

CSSValueList &CSSValueList::operator = (const CSSValue &other)
{
    CSSValueImpl *ohandle = other.handle();
    if (impl != ohandle) {
        if (impl) {
            impl->deref();
        }
        if (!other.isNull() && !other.isCSSValueList()) {
            impl = nullptr;
        } else {
            impl = ohandle;
            if (impl) {
                impl->ref();
            }
        }
    }
    return *this;
}

CSSValueList::~CSSValueList()
{
}

unsigned long CSSValueList::length() const
{
    if (!impl) {
        return 0;
    }
    return ((CSSValueListImpl *)impl)->length();
}

CSSValue CSSValueList::item(unsigned long index)
{
    if (!impl) {
        return nullptr;
    }
    return ((CSSValueListImpl *)impl)->item(index);
}

// ----------------------------------------------------------

CSSPrimitiveValue::CSSPrimitiveValue() : CSSValue()
{
}

CSSPrimitiveValue::CSSPrimitiveValue(const CSSPrimitiveValue &other) : CSSValue(other)
{
}

CSSPrimitiveValue::CSSPrimitiveValue(const CSSValue &other) : CSSValue(other)
{
    impl = nullptr;
    operator=(other);
}

CSSPrimitiveValue::CSSPrimitiveValue(CSSPrimitiveValueImpl *impl) : CSSValue(impl)
{
}

CSSPrimitiveValue &CSSPrimitiveValue::operator = (const CSSPrimitiveValue &other)
{
    if (impl != other.impl) {
        if (impl) {
            impl->deref();
        }
        impl = other.handle();
        if (impl) {
            impl->ref();
        }
    }
    return *this;
}

CSSPrimitiveValue &CSSPrimitiveValue::operator = (const CSSValue &other)
{
    CSSValueImpl *ohandle = other.handle();
    if (impl != ohandle) {
        if (impl) {
            impl->deref();
        }
        if (!other.isNull() && !other.isCSSPrimitiveValue()) {
            impl = nullptr;
        } else {
            impl = ohandle;
            if (impl) {
                impl->ref();
            }
        }
    }
    return *this;
}

CSSPrimitiveValue::~CSSPrimitiveValue()
{
}

unsigned short CSSPrimitiveValue::primitiveType() const
{
    if (!impl) {
        return 0;
    }
    return ((CSSPrimitiveValueImpl *)impl)->primitiveType();
}

void CSSPrimitiveValue::setFloatValue(unsigned short unitType, float floatValue)
{
    if (!impl) {
        return;
    }
    int exceptioncode = 0;
    ((CSSPrimitiveValueImpl *)impl)->setFloatValue(unitType, floatValue, exceptioncode);
    if (exceptioncode >= CSSException::_EXCEPTION_OFFSET) {
        throw CSSException(exceptioncode - CSSException::_EXCEPTION_OFFSET);
    }
    if (exceptioncode) {
        throw DOMException(exceptioncode);
    }
}

float CSSPrimitiveValue::getFloatValue(unsigned short unitType) const
{
    if (!impl) {
        return 0;
    }
    // ### add unit conversion
    if (primitiveType() != unitType) {
        throw CSSException(CSSException::SYNTAX_ERR);
    }
    return ((CSSPrimitiveValueImpl *)impl)->floatValue(unitType);
}

void CSSPrimitiveValue::setStringValue(unsigned short stringType, const DOMString &stringValue)
{
    int exceptioncode = 0;
    if (impl) {
        ((CSSPrimitiveValueImpl *)impl)->setStringValue(stringType, stringValue, exceptioncode);
    }
    if (exceptioncode >= CSSException::_EXCEPTION_OFFSET) {
        throw CSSException(exceptioncode - CSSException::_EXCEPTION_OFFSET);
    }
    if (exceptioncode) {
        throw DOMException(exceptioncode);
    }

}

DOMString CSSPrimitiveValue::getStringValue() const
{
    if (!impl) {
        return DOMString();
    }
    return ((CSSPrimitiveValueImpl *)impl)->getStringValue();
}

Counter CSSPrimitiveValue::getCounterValue() const
{
    if (!impl) {
        return Counter();
    }
    return ((CSSPrimitiveValueImpl *)impl)->getCounterValue();
}

Rect CSSPrimitiveValue::getRectValue() const
{
    if (!impl) {
        return Rect();
    }
    return ((CSSPrimitiveValueImpl *)impl)->getRectValue();
}

RGBColor CSSPrimitiveValue::getRGBColorValue() const
{
    // ###
    return RGBColor();
    //if(!impl) return RGBColor();
    //return ((CSSPrimitiveValueImpl *)impl)->getRGBColorValue(  );
}

// -------------------------------------------------------------------

Counter::Counter()
{
}

Counter::Counter(const Counter &/*other*/)
{
    impl = nullptr;
}

Counter &Counter::operator = (const Counter &other)
{
    if (impl != other.impl) {
        if (impl) {
            impl->deref();
        }
        impl = other.impl;
        if (impl) {
            impl->ref();
        }
    }
    return *this;
}

Counter::Counter(CounterImpl *i)
{
    impl = i;
    if (impl) {
        impl->ref();
    }
}

Counter::~Counter()
{
    if (impl) {
        impl->deref();
    }
}

DOMString Counter::identifier() const
{
    if (!impl) {
        return DOMString();
    }
    return impl->identifier();
}

DOMString Counter::listStyle() const
{
    if (!impl) {
        return DOMString();
    }
    return khtml::stringForListStyleType((khtml::EListStyleType)impl->listStyle());
}

DOMString Counter::separator() const
{
    if (!impl) {
        return DOMString();
    }
    return impl->separator();
}

CounterImpl *Counter::handle() const
{
    return impl;
}

bool Counter::isNull() const
{
    return (impl == nullptr);
}

// --------------------------------------------------------------------

RGBColor::RGBColor()
{
}

RGBColor::RGBColor(const RGBColor &other)
{
    m_color = other.m_color;
}

RGBColor::RGBColor(QRgb color)
{
    m_color = color;
}

RGBColor &RGBColor::operator = (const RGBColor &other)
{
    m_color = other.m_color;
    return *this;
}

RGBColor::~RGBColor()
{
}

CSSPrimitiveValue RGBColor::red() const
{
    return new CSSPrimitiveValueImpl(float(qAlpha(m_color) ? qRed(m_color) : 0), CSSPrimitiveValue::CSS_DIMENSION);
}

CSSPrimitiveValue RGBColor::green() const
{
    return new CSSPrimitiveValueImpl(float(qAlpha(m_color) ? qGreen(m_color) : 0), CSSPrimitiveValue::CSS_DIMENSION);
}

CSSPrimitiveValue RGBColor::blue() const
{
    return new CSSPrimitiveValueImpl(float(qAlpha(m_color) ? qBlue(m_color) : 0), CSSPrimitiveValue::CSS_DIMENSION);
}

// ---------------------------------------------------------------------

Rect::Rect()
{
    impl = nullptr;
}

Rect::Rect(const Rect &other)
{
    impl = other.impl;
    if (impl) {
        impl->ref();
    }
}

Rect::Rect(RectImpl *i)
{
    impl = i;
    if (impl) {
        impl->ref();
    }
}

Rect &Rect::operator = (const Rect &other)
{
    if (impl != other.impl) {
        if (impl) {
            impl->deref();
        }
        impl = other.impl;
        if (impl) {
            impl->ref();
        }
    }
    return *this;
}

Rect::~Rect()
{
    if (impl) {
        impl->deref();
    }
}

CSSPrimitiveValue Rect::top() const
{
    if (!impl) {
        return nullptr;
    }
    return impl->top();
}

CSSPrimitiveValue Rect::right() const
{
    if (!impl) {
        return nullptr;
    }
    return impl->right();
}

CSSPrimitiveValue Rect::bottom() const
{
    if (!impl) {
        return nullptr;
    }
    return impl->bottom();
}

CSSPrimitiveValue Rect::left() const
{
    if (!impl) {
        return nullptr;
    }
    return impl->left();
}

RectImpl *Rect::handle() const
{
    return impl;
}

bool Rect::isNull() const
{
    return (impl == nullptr);
}

} // namespace

