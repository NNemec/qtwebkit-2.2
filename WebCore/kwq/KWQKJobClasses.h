/*
 * Copyright (C) 2004, 2006 Apple Computer, Inc.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
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

#ifndef JOBCLASSES_H_
#define JOBCLASSES_H_

#include "PlatformString.h"
#include "TransferJobClient.h" // for PlatformResponse
#include <kxmlcore/HashMap.h>

#if __APPLE__
#ifdef __OBJC__
@class KWQResourceLoader;
#else
class KWQResourceLoader;
#endif
#endif

class KURL;

namespace WebCore {

class FormData;
class TransferJobPrivate;
class DocLoader;

class TransferJob {
public:
    TransferJob(TransferJobClient*, const String& method, const KURL&);
    TransferJob(TransferJobClient*, const String& method, const KURL&, const FormData& postData);
    ~TransferJob();

    bool start(DocLoader*);

    int error() const;
    void setError(int);
    QString errorText() const;
    bool isErrorPage() const;
    QString queryMetaData(const QString& key) const;
    void addMetaData(const QString& key, const QString& value);
    void addMetaData(const HashMap<String, String>&);
    void kill();

    KURL url() const;
    String method() const;
    FormData postData() const;

#if __APPLE__
    void setLoader(KWQResourceLoader*);
#endif

    void cancel();
    
    TransferJobClient* client() const;

    void receivedResponse(PlatformResponse);

private:
    void assembleResponseHeaders() const;
    void retrieveCharset() const;

    TransferJobPrivate* d;
};

}

#endif
