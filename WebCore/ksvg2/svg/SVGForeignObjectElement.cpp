/*
    Copyright (C) 2006 Apple Computer, Inc.

    This file is part of the WebKit project

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include "config.h"
#ifdef SVG_SUPPORT

#include "SVGForeignObjectElement.h"

#include "SVGNames.h"
#include "SVGHelper.h"
#include "SVGLength.h"
#include "RenderForeignObject.h"

#include <wtf/Assertions.h>

#include "CSSPropertyNames.h"

namespace WebCore {

SVGForeignObjectElement::SVGForeignObjectElement(const QualifiedName& tagName, Document *doc)
    : SVGStyledTransformableElement(tagName, doc)
    , SVGTests()
    , SVGLangSpace()
    , SVGExternalResourcesRequired()
    , m_x(new SVGLength(this, LM_WIDTH, viewportElement()))
    , m_y(new SVGLength(this, LM_HEIGHT, viewportElement()))
    , m_width(new SVGLength(this, LM_WIDTH, viewportElement()))
    , m_height(new SVGLength(this, LM_HEIGHT, viewportElement()))
{
}

SVGForeignObjectElement::~SVGForeignObjectElement()
{
}

ANIMATED_PROPERTY_DEFINITIONS(SVGForeignObjectElement, SVGLength*, Length, length, X, x, SVGNames::xAttr.localName(), m_x.get())
ANIMATED_PROPERTY_DEFINITIONS(SVGForeignObjectElement, SVGLength*, Length, length, Y, y, SVGNames::yAttr.localName(), m_y.get())
ANIMATED_PROPERTY_DEFINITIONS(SVGForeignObjectElement, SVGLength*, Length, length, Width, width, SVGNames::widthAttr.localName(), m_width.get())
ANIMATED_PROPERTY_DEFINITIONS(SVGForeignObjectElement, SVGLength*, Length, length, Height, height, SVGNames::heightAttr.localName(), m_height.get())

void SVGForeignObjectElement::parseMappedAttribute(MappedAttribute *attr)
{
    const AtomicString& value = attr->value();
    if (attr->name() == SVGNames::xAttr)
        xBaseValue()->setValueAsString(value);
    else if (attr->name() == SVGNames::yAttr)
        yBaseValue()->setValueAsString(value);
    else if (attr->name() == SVGNames::widthAttr) {
        widthBaseValue()->setValueAsString(value);
        addCSSProperty(attr, CSS_PROP_WIDTH, value);
    } else if (attr->name() == SVGNames::heightAttr) {
        heightBaseValue()->setValueAsString(value);
        addCSSProperty(attr, CSS_PROP_HEIGHT, value);
    } else {
        if (SVGTests::parseMappedAttribute(attr))
            return;
        if (SVGLangSpace::parseMappedAttribute(attr))
            return;
        if (SVGExternalResourcesRequired::parseMappedAttribute(attr))
            return;
        SVGStyledTransformableElement::parseMappedAttribute(attr);
    }
}

RenderObject *SVGForeignObjectElement::createRenderer(RenderArena *arena, RenderStyle *style)
{
    return new (arena) RenderForeignObject(this);
}

bool SVGForeignObjectElement::childShouldCreateRenderer(Node *child) const
{
    // Skip over SVG rules which disallow non-SVG kids
    return StyledElement::childShouldCreateRenderer(child);
}

} // namespace WebCore

// vim:ts=4:noet
#endif // SVG_SUPPORT

