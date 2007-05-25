/*
 * Copyright (C) 2007 Apple Computer, Inc.  All rights reserved.
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

#include "config.h"
#include "HTMLParserErrorCodes.h"

namespace WebCore {

const char* htmlParserErrorMessageTemplate(HTMLParserErrorCode errorCode)
{
    static const char* const errors[] = { 
        "%tag1 is not allowed inside %tag2.  Moving %tag1 into the nearest enclosing <table>.",
        "<head> must be a child of <html>.  Content ignored.",
        "Extra %tag1 encountered.  Migrating attributes back to the original %tag1 element and ignoring the tag.",
        "%tag1 is not allowed inside <object>. Skipping all content until </object> is encountered.",
        "<area> is not allowed inside %tag1. Moving the <area> into the nearest enclosing <map>.",
        "%tag1 is not allowed inside %tag2. Content ignored.",
        "%tag1 is not allowed in a <frameset> page. Content ignored.",
        "%tag1 is not allowed inside %tag2. Closing %tag2 and trying the insertion again.",
        "%tag1 is not allowed inside <caption>. Closing the <caption> and trying the insertion again.",
        "<table> is not allowed inside %tag1. Closing the current <table> and inserting the new <table> as a sibling.",
        "%tag1 is not allowed inside %tag2. Inserting %tag1 before the <table> instead.",
        "%tag1 misplaced in <table>. Creating %tag2 and putting %tag1 inside it.",
        "</br> encountered.  Converting </br> into <br>.",
        "XML self-closing tag syntax used on %tag1. The tag will not be closed.",
        "Unmatched </p> encountered.  Converting </p> into <p></p>.",
        "Unmatched %tag1 encountered.  Ignoring tag.",
        "%tag1 misnested or not properly closed.  Cloning %tag1 in order to preserve the styles applied by it.",
        "<form> cannot act as a container inside %tag1 without disrupting the table.  The children of the <form> will be placed inside the %tag1 instead.",
        "XML self-closing tag syntax used on <script>.  The tag will be closed by WebKit, but not all browsers do this.  Change to <script></script> instead for best cross-browser compatibility."
    };
     
    if (errorCode >= MisplacedTablePartError && errorCode <= IncorrectXMLCloseScriptWarning)
        return errors[errorCode];
    return 0;
}

bool isWarning(HTMLParserErrorCode code)
{
    return code >= IncorrectXMLCloseScriptWarning;
}

}
