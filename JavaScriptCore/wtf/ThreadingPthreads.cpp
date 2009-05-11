/*
 * Copyright (C) 2007, 2009 Apple Inc. All rights reserved.
 * Copyright (C) 2007 Justin Haygood (jhaygood@reaktix.com)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution. 
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "Threading.h"

#if USE(PTHREADS)

#include "CurrentTime.h"
#include "HashMap.h"
#include "MainThread.h"
#include "RandomNumberSeed.h"
#include "StdLibExtras.h"
#include "UnusedParam.h"
#include <errno.h>
#include <limits.h>
#include <sys/time.h>

#if PLATFORM(ANDROID)
#include "jni_utility.h"
#endif

namespace WTF {

bool ThreadIdentifier::operator==(const ThreadIdentifier& another) const
{
    return pthread_equal(m_platformId, another.m_platformId);
}

bool ThreadIdentifier::operator!=(const ThreadIdentifier& another) const
{
    return !pthread_equal(m_platformId, another.m_platformId);
}

static Mutex* atomicallyInitializedStaticMutex;

#if !PLATFORM(DARWIN) || PLATFORM(CHROMIUM)
static ThreadIdentifier mainThreadIdentifier; // The thread that was the first to call initializeThreading(), which must be the main thread.
#endif

void initializeThreading()
{
    if (!atomicallyInitializedStaticMutex) {
        atomicallyInitializedStaticMutex = new Mutex;
        initializeRandomNumberGenerator();
#if !PLATFORM(DARWIN) || PLATFORM(CHROMIUM)
        mainThreadIdentifier = currentThread();
#endif
        initializeMainThread();
    }
}

void lockAtomicallyInitializedStaticMutex()
{
    ASSERT(atomicallyInitializedStaticMutex);
    atomicallyInitializedStaticMutex->lock();
}

void unlockAtomicallyInitializedStaticMutex()
{
    atomicallyInitializedStaticMutex->unlock();
}

#if PLATFORM(ANDROID)
// On the Android platform, threads must be registered with the VM before they run.
struct ThreadData {
    ThreadFunction entryPoint;
    void* arg;
};

static void* runThreadWithRegistration(void* arg)
{
    ThreadData* data = static_cast<ThreadData*>(arg);
    JavaVM* vm = JSC::Bindings::getJavaVM();
    JNIEnv* env;
    void* ret = 0;
    if (vm->AttachCurrentThread(&env, 0) == JNI_OK) {
        ret = data->entryPoint(data->arg);
        vm->DetachCurrentThread();
    }
    delete data;
    return ret;
}

ThreadIdentifier createThreadInternal(ThreadFunction entryPoint, void* data, const char*)
{
    pthread_t threadHandle;
    ThreadData* threadData = new ThreadData();
    threadData->entryPoint = entryPoint;
    threadData->arg = data;

    if (pthread_create(&threadHandle, 0, runThreadWithRegistration, static_cast<void*>(threadData))) {
        LOG_ERROR("Failed to create pthread at entry point %p with data %p", entryPoint, data);
        return ThreadIdentifier();
    }
    return ThreadIdentifier(threadHandle);
}
#else
ThreadIdentifier createThreadInternal(ThreadFunction entryPoint, void* data, const char*)
{
    pthread_t threadHandle;
    if (pthread_create(&threadHandle, 0, entryPoint, data)) {
        LOG_ERROR("Failed to create pthread at entry point %p with data %p", entryPoint, data);
        return ThreadIdentifier();
    }

    return ThreadIdentifier(threadHandle);
}
#endif

void setThreadNameInternal(const char* threadName)
{
#if PLATFORM(DARWIN) && !defined(BUILDING_ON_TIGER) && !defined(BUILDING_ON_LEOPARD)
    pthread_setname_np(threadName);
#else
    UNUSED_PARAM(threadName);
#endif
}

int waitForThreadCompletion(ThreadIdentifier threadID, void** result)
{
    ASSERT(threadID.isValid());
    
    pthread_t pthreadHandle = threadID.platformId();
 
    int joinResult = pthread_join(pthreadHandle, result);
    if (joinResult == EDEADLK)
        LOG_ERROR("ThreadIdentifier %p was found to be deadlocked trying to quit", pthreadHandle);
        
    return joinResult;
}

void detachThread(ThreadIdentifier threadID)
{
    ASSERT(threadID.isValid());
    
    pthread_t pthreadHandle = threadID.platformId();
    
    pthread_detach(pthreadHandle);
}

ThreadIdentifier currentThread()
{
    return ThreadIdentifier(pthread_self());
}

bool isMainThread()
{
#if PLATFORM(DARWIN) && !PLATFORM(CHROMIUM)
    return pthread_main_np();
#else
    return currentThread() == mainThreadIdentifier;
#endif
}

Mutex::Mutex()
{
    pthread_mutex_init(&m_mutex, NULL);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void Mutex::lock()
{
    int result = pthread_mutex_lock(&m_mutex);
    ASSERT_UNUSED(result, !result);
}
    
bool Mutex::tryLock()
{
    int result = pthread_mutex_trylock(&m_mutex);
    
    if (result == 0)
        return true;
    if (result == EBUSY)
        return false;

    ASSERT_NOT_REACHED();
    return false;
}

void Mutex::unlock()
{
    int result = pthread_mutex_unlock(&m_mutex);
    ASSERT_UNUSED(result, !result);
}

ThreadCondition::ThreadCondition()
{ 
    pthread_cond_init(&m_condition, NULL);
}

ThreadCondition::~ThreadCondition()
{
    pthread_cond_destroy(&m_condition);
}
    
void ThreadCondition::wait(Mutex& mutex)
{
    int result = pthread_cond_wait(&m_condition, &mutex.impl());
    ASSERT_UNUSED(result, !result);
}

bool ThreadCondition::timedWait(Mutex& mutex, double absoluteTime)
{
    if (absoluteTime < currentTime())
        return false;

    if (absoluteTime > INT_MAX) {
        wait(mutex);
        return true;
    }

    int timeSeconds = static_cast<int>(absoluteTime);
    int timeNanoseconds = static_cast<int>((absoluteTime - timeSeconds) * 1E9);

    timespec targetTime;
    targetTime.tv_sec = timeSeconds;
    targetTime.tv_nsec = timeNanoseconds;

    return pthread_cond_timedwait(&m_condition, &mutex.impl(), &targetTime) == 0;
}

void ThreadCondition::signal()
{
    int result = pthread_cond_signal(&m_condition);
    ASSERT_UNUSED(result, !result);
}

void ThreadCondition::broadcast()
{
    int result = pthread_cond_broadcast(&m_condition);
    ASSERT_UNUSED(result, !result);
}

// Derecated function. Safari 4 beta, until recompiled next time, uses ThreadIdentifier as uint32_t.
// pthread_t is a pointer. So they get a pointer casted into uint32_t from CurrentThread()
// and then pass it here. We cast it back to pointer. This is an ugly hack which is very temporary
// and will be removed once next public build of Safari 4 is released.
// Some versions of GCC require a prototype before a function with external linkage, so we have to
// add a declaration here before defining the function.
int waitForThreadCompletion(uint32_t, void**);
int waitForThreadCompletion(uint32_t threadID, void** result)
{
    pthread_t pthreadHandle = reinterpret_cast<pthread_t>(threadID);

    int joinResult = pthread_join(pthreadHandle, result);
    if (joinResult == EDEADLK)
        LOG_ERROR("ThreadIdentifier %p was found to be deadlocked trying to quit", pthreadHandle);

    return joinResult;
}

} // namespace WTF

#endif // USE(PTHREADS)
