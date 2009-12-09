/*
 * Copyright (C) 2009 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"

#if USE(ACCELERATED_COMPOSITING)

#include "WKCACFLayer.h"

#include "WKCACFContextFlusher.h"

#include <stdio.h>
#include <QuartzCore/CACFContext.h>
#include <QuartzCore/CARender.h>

#pragma comment(lib, "QuartzCore")

namespace WebCore {

using namespace std;

static void displayInContext(CACFLayerRef layer, CGContextRef context)
{
    ASSERT_ARG(layer, WKCACFLayer::layer(layer));
    WKCACFLayer::layer(layer)->display(context);
}

// FIXME: It might be good to have a way of ensuring that all WKCACFLayers eventually
// get destroyed in debug builds. A static counter could accomplish this pretty easily.

WKCACFLayer::WKCACFLayer(CFStringRef className, GraphicsLayerCACF* owner)
    : m_layer(AdoptCF, CACFLayerCreate(className))
    , m_needsDisplayOnBoundsChange(false)
    , m_owner(owner)
{
    CACFLayerSetUserData(layer(), this);
    CACFLayerSetDisplayCallback(layer(), displayInContext);
}

WKCACFLayer::~WKCACFLayer()
{
    // Our superlayer should be holding a reference to us, so there should be no way for us to be destroyed while we still have a superlayer.
    ASSERT(!superlayer());

    CACFLayerSetUserData(layer(), 0);
    CACFLayerSetDisplayCallback(layer(), 0);
}

void WKCACFLayer::display(PlatformGraphicsContext* context)
{
    if (!m_owner)
        return;

    CGContextSaveGState(context);

    CGRect layerBounds = bounds();
    if (m_owner->contentsOrientation() == WebCore::GraphicsLayer::CompositingCoordinatesTopDown) {
        CGContextScaleCTM(context, 1, -1);
        CGContextTranslateCTM(context, 0, -layerBounds.size.height);
    }

    if (m_owner->client()) {
        GraphicsContext graphicsContext(context);

        // It's important to get the clip from the context, because it may be significantly
        // smaller than the layer bounds (e.g. tiled layers)
        CGRect clipBounds = CGContextGetClipBoundingBox(context);
        IntRect clip(enclosingIntRect(clipBounds));
        m_owner->paintGraphicsLayerContents(graphicsContext, clip);
    }
#ifndef NDEBUG
    else {
        ASSERT_NOT_REACHED();

        // FIXME: ideally we'd avoid calling -setNeedsDisplay on a layer that is a plain color,
        // so CA never makes backing store for it (which is what -setNeedsDisplay will do above).
        CGContextSetRGBFillColor(context, 0.0f, 1.0f, 0.0f, 1.0f);
        CGContextFillRect(context, layerBounds);
    }
#endif

    if (m_owner->showRepaintCounter()) {
        char text[16]; // that's a lot of repaints
        _snprintf(text, sizeof(text), "%d", m_owner->incrementRepaintCount());

        CGContextSaveGState(context);
        CGContextSetRGBFillColor(context, 1.0f, 0.0f, 0.0f, 0.8f);
        
        CGRect aBounds = layerBounds;

        aBounds.size.width = 10 + 12 * strlen(text);
        aBounds.size.height = 25;
        CGContextFillRect(context, aBounds);
        
        CGContextSetRGBFillColor(context, 0.0f, 0.0f, 0.0f, 1.0f);

        CGContextSetTextMatrix(context, CGAffineTransformMakeScale(1.0f, -1.0f));
        CGContextSelectFont(context, "Helvetica", 25, kCGEncodingMacRoman);
        CGContextShowTextAtPoint(context, aBounds.origin.x + 3.0f, aBounds.origin.y + 20.0f, text, strlen(text));
        
        CGContextRestoreGState(context);        
    }

    CGContextRestoreGState(context);
}

void WKCACFLayer::becomeRootLayerForContext(CACFContextRef context)
{
    CACFContextSetLayer(context, layer());
    setNeedsCommit();
}

void WKCACFLayer::setNeedsCommit()
{
    CACFContextRef context = CACFLayerGetContext(rootLayer()->layer());

    // The context might now be set yet. This happens if a property gets set
    // before placing the layer in the tree. In this case we don't need to 
    // worry about remembering the context because we will when the layer is
    // added to the tree.
    if (context)
        WKCACFContextFlusher::shared().addContext(context);

    // Call notifySyncRequired(), which in this implementation plumbs through to
    // call setRootLayerNeedsDisplay() on the WebView, which causes the CACFRenderer
    // to render a frame.
    if (m_owner)
        m_owner->notifySyncRequired();
}

void WKCACFLayer::addSublayer(PassRefPtr<WKCACFLayer> sublayer)
{
    insertSublayer(sublayer, numSublayers());
}

void WKCACFLayer::insertSublayer(PassRefPtr<WKCACFLayer> sublayer, size_t index)
{
    index = min(index, numSublayers());
    CACFLayerInsertSublayer(layer(), sublayer->layer(), index);
    setNeedsCommit();
}

void WKCACFLayer::insertSublayerAboveLayer(PassRefPtr<WKCACFLayer> sublayer, const WKCACFLayer* reference)
{
    if (!reference) {
        insertSublayer(sublayer, 0);
        return;
    }

    int referenceIndex = indexOfSublayer(reference);
    if (referenceIndex == -1) {
        addSublayer(sublayer);
        return;
    }

    insertSublayer(sublayer, referenceIndex + 1);
}

void WKCACFLayer::insertSublayerBelowLayer(PassRefPtr<WKCACFLayer> sublayer, const WKCACFLayer* reference)
{
    if (!reference) {
        insertSublayer(sublayer, 0);
        return;
    }

    int referenceIndex = indexOfSublayer(reference);
    if (referenceIndex == -1) {
        addSublayer(sublayer);
        return;
    }

    insertSublayer(sublayer, referenceIndex);
}

void WKCACFLayer::replaceSublayer(WKCACFLayer* reference, PassRefPtr<WKCACFLayer> newLayer)
{
    ASSERT_ARG(reference, reference);
    ASSERT_ARG(reference, reference->superlayer() == this);

    if (reference == newLayer)
        return;

    if (!newLayer) {
        removeSublayer(reference);
        return;
    }

    newLayer->removeFromSuperlayer();

    int referenceIndex = indexOfSublayer(reference);
    ASSERT(referenceIndex != -1);
    if (referenceIndex == -1)
        return;

    // FIXME: Can we make this more efficient? The current CACF API doesn't seem to give us a way to do so.
    reference->removeFromSuperlayer();
    insertSublayer(newLayer, referenceIndex);
}

void WKCACFLayer::removeFromSuperlayer()
{
    WKCACFLayer* superlayer = this->superlayer();
    if (!superlayer)
        return;

    superlayer->removeSublayer(this);
    CACFLayerRemoveFromSuperlayer(layer());
    superlayer->setNeedsCommit();
}

void WKCACFLayer::removeSublayer(const WKCACFLayer* sublayer)
{
    int foundIndex = indexOfSublayer(sublayer);
    if (foundIndex == -1)
        return;

    CACFLayerRemoveFromSuperlayer(sublayer->layer());
    setNeedsCommit();
}

int WKCACFLayer::indexOfSublayer(const WKCACFLayer* reference)
{
    CACFLayerRef ref = reference->layer();
    if (!ref)
        return -1;

    CFArrayRef sublayers = CACFLayerGetSublayers(layer());
    size_t n = CFArrayGetCount(sublayers);

    for (size_t i = 0; i < n; ++i)
        if (CFArrayGetValueAtIndex(sublayers, i) == ref)
            return i;

    return -1;
}

WKCACFLayer* WKCACFLayer::ancestorOrSelfWithSuperlayer(WKCACFLayer* superlayer) const
{
    WKCACFLayer* layer = const_cast<WKCACFLayer*>(this);
    for (WKCACFLayer* ancestor = this->superlayer(); ancestor; layer = ancestor, ancestor = ancestor->superlayer()) {
        if (ancestor == superlayer)
            return layer;
    }
    return 0;
}

void WKCACFLayer::setBounds(const CGRect& rect)
{
    if (CGRectEqualToRect(rect, bounds()))
        return;

    CACFLayerSetBounds(layer(), rect);
    setNeedsCommit();

    if (m_needsDisplayOnBoundsChange)
        setNeedsDisplay();
}

void WKCACFLayer::setFrame(const CGRect& rect)
{
    CGRect oldFrame = frame();
    if (CGRectEqualToRect(rect, oldFrame))
        return;

    CACFLayerSetFrame(layer(), rect);
    setNeedsCommit();

    if (m_needsDisplayOnBoundsChange)
        setNeedsDisplay();
}

WKCACFLayer* WKCACFLayer::rootLayer() const
{
    WKCACFLayer* layer = const_cast<WKCACFLayer*>(this);
    for (WKCACFLayer* superlayer = layer->superlayer(); superlayer; layer = superlayer, superlayer = superlayer->superlayer()) { }
    return layer;
}

void WKCACFLayer::removeAllSublayers()
{
    CACFLayerSetSublayers(layer(), 0);
    setNeedsCommit();
}

void WKCACFLayer::setSublayers(const Vector<RefPtr<WKCACFLayer> >& sublayers)
{
    if (sublayers.isEmpty())
        CACFLayerSetSublayers(layer(), 0);
    else {
        // Create a vector of CACFLayers.
        Vector<const void*> layers;
        for (size_t i = 0; i < sublayers.size(); i++)
            layers.append(sublayers[i]->layer());
    
        RetainPtr<CFArrayRef> layersArray(AdoptCF, CFArrayCreate(0, layers.data(), layers.size(), 0));
        CACFLayerSetSublayers(layer(), layersArray.get());
    }
    
    setNeedsCommit();
}

void WKCACFLayer::moveSublayers(WKCACFLayer* fromLayer, WKCACFLayer* toLayer)
{
    if (!fromLayer || !toLayer)
        return;

    CACFLayerSetSublayers(toLayer->layer(), CACFLayerGetSublayers(fromLayer->layer()));
    fromLayer->setNeedsCommit();
    toLayer->setNeedsCommit();
}

WKCACFLayer* WKCACFLayer::superlayer() const
{
    CACFLayerRef super = CACFLayerGetSuperlayer(layer());
    if (!super)
        return 0;
    return WKCACFLayer::layer(super);
}

void WKCACFLayer::setNeedsDisplay(const CGRect& dirtyRect)
{
    if (m_owner)
        CACFLayerSetNeedsDisplay(layer(), &dirtyRect);
    setNeedsCommit();
}

void WKCACFLayer::setNeedsDisplay()
{
    if (m_owner)
        CACFLayerSetNeedsDisplay(layer(), 0);
    setNeedsCommit();
}


}

#endif // USE(ACCELERATED_COMPOSITING)
