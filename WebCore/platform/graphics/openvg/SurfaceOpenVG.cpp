/*
 * Copyright (C) Research In Motion Limited 2009-2010. All rights reserved.
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
 */

#include "config.h"
#include "SurfaceOpenVG.h"

#include "IntSize.h"
#include "PainterOpenVG.h"

#if PLATFORM(EGL)
#include "EGLDisplayOpenVG.h"
#include "EGLUtils.h"
#endif

#include <wtf/Assertions.h>
#include <wtf/UnusedParam.h>

namespace WebCore {

SurfaceOpenVG* SurfaceOpenVG::currentSurface()
{
#if PLATFORM(EGL)
    return EGLDisplayOpenVG::currentSurface();
#else
    ASSERT_NOT_REACHED();
    return 0;
#endif
}

#if PLATFORM(EGL)
SurfaceOpenVG::SurfaceOpenVG(const IntSize& size, const EGLDisplay& display, EGLConfig* confPtr)
    : m_eglDisplay(display)
    , m_eglSurface(EGL_NO_SURFACE)
    , m_eglContext(EGL_NO_CONTEXT)
{
    ASSERT(m_eglDisplay != EGL_NO_DISPLAY);

    EGLDisplayOpenVG* displayManager = EGLDisplayOpenVG::forDisplay(m_eglDisplay);
    EGLConfig config = confPtr ? (*confPtr) : displayManager->defaultPbufferConfig();
    m_eglSurface = displayManager->createPbufferSurface(size, config);

    if (m_eglSurface == EGL_NO_SURFACE)
        return;

    m_eglContext = displayManager->contextForSurface(m_eglSurface);
    EGLDisplayOpenVG::registerPlatformSurface(this);
}

SurfaceOpenVG::SurfaceOpenVG(EGLNativeWindowType window, const EGLDisplay& display, EGLConfig* confPtr)
    : m_eglDisplay(display)
    , m_eglSurface(EGL_NO_SURFACE)
    , m_eglContext(EGL_NO_CONTEXT)
{
    ASSERT(m_eglDisplay != EGL_NO_DISPLAY);

    EGLDisplayOpenVG* displayManager = EGLDisplayOpenVG::forDisplay(m_eglDisplay);
    EGLConfig config = confPtr ? (*confPtr) : displayManager->defaultWindowConfig();
    m_eglSurface = displayManager->surfaceForWindow(window, config);

    if (m_eglSurface == EGL_NO_SURFACE)
        return;

    m_eglContext = displayManager->contextForSurface(m_eglSurface);
    EGLDisplayOpenVG::registerPlatformSurface(this);
}

// Constructor only accessible to EGLDisplayOpenVG for shared context
// initialization. The parameter types might define to void* like in the
// window surface constructor, so it can't be overloaded with all the required
// arguments and EGLDisplayOpenVG basically implements the constructor
// by itself.
SurfaceOpenVG::SurfaceOpenVG()
    : m_eglDisplay(EGL_NO_DISPLAY)
    , m_eglSurface(EGL_NO_SURFACE)
    , m_eglContext(EGL_NO_CONTEXT)
{
}
#endif

SurfaceOpenVG::~SurfaceOpenVG()
{
    if (!isValid())
        return;

#if PLATFORM(EGL)
    EGLDisplayOpenVG::forDisplay(m_eglDisplay)->destroySurface(m_eglSurface);
    EGLDisplayOpenVG::unregisterPlatformSurface(this);
#else
    ASSERT_NOT_REACHED();
#endif
}

bool SurfaceOpenVG::isValid() const
{
#if PLATFORM(EGL)
    return (m_eglSurface != EGL_NO_SURFACE);
#else
    ASSERT_NOT_REACHED();
    return false;
#endif
}

int SurfaceOpenVG::width() const
{
#if PLATFORM(EGL)
    ASSERT(m_eglSurface != EGL_NO_SURFACE);

    EGLint width;
    eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_WIDTH, &width);
    ASSERT_EGL_NO_ERROR();
    return width;
#else
    ASSERT_NOT_REACHED();
    return 0;
#endif
}

int SurfaceOpenVG::height() const
{
#if PLATFORM(EGL)
    ASSERT(m_eglSurface != EGL_NO_SURFACE);

    EGLint height;
    eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_HEIGHT, &height);
    ASSERT_EGL_NO_ERROR();
    return height;
#else
    ASSERT_NOT_REACHED();
    return 0;
#endif
}

SurfaceOpenVG* SurfaceOpenVG::sharedSurface() const
{
#if PLATFORM(EGL)
    ASSERT(m_eglSurface != EGL_NO_SURFACE);
    return EGLDisplayOpenVG::forDisplay(m_eglDisplay)->sharedPlatformSurface();
#else
    ASSERT_NOT_REACHED();
    return 0;
#endif
}

void SurfaceOpenVG::makeCurrent(MakeCurrentMode mode)
{
#if PLATFORM(EGL)
    ASSERT(m_eglSurface != EGL_NO_SURFACE);

    eglBindAPI(EGL_OPENVG_API);
    ASSERT_EGL_NO_ERROR();
    EGLSurface currentSurface = eglGetCurrentSurface(EGL_DRAW);
    ASSERT_EGL_NO_ERROR();

    if (currentSurface != m_eglSurface) {
        eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
        ASSERT_EGL_NO_ERROR();
    }
#else
    UNUSED_PARAM(mode);
#endif
}

void SurfaceOpenVG::makeCompatibleCurrent()
{
#if PLATFORM(EGL)
    ASSERT(m_eglSurface != EGL_NO_SURFACE);

    eglBindAPI(EGL_OPENVG_API);
    ASSERT_EGL_NO_ERROR();
    EGLSurface currentSurface = eglGetCurrentSurface(EGL_DRAW);
    ASSERT_EGL_NO_ERROR();

    if (currentSurface != m_eglSurface
        && !EGLDisplayOpenVG::forDisplay(m_eglDisplay)->surfacesCompatible(currentSurface, m_eglSurface)) {
        eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
        ASSERT_EGL_NO_ERROR();
    }
    // else: surfaces compatible, no need to switch contexts
#endif
}

void SurfaceOpenVG::flush()
{
#if PLATFORM(EGL)
    ASSERT(m_eglSurface != EGL_NO_SURFACE);

    eglSwapBuffers(m_eglDisplay, m_eglSurface);
    ASSERT_EGL_NO_ERROR();
#endif
}

}
