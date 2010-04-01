# Copyright (c) 2010 Google Inc. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#     * Neither the name of Google Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

from webkitpy.common.checkout.changelog import view_source_url
from webkitpy.tool.bot.queueengine import TerminateQueue
from webkitpy.common.system.executive import ScriptError

# FIXME: Merge with Command?
class IRCCommand(object):
    def execute(self, args, tool, sheriff):
        raise NotImplementedError, "subclasses must implement"


class LastGreenRevision(IRCCommand):
    def execute(self, args, tool, sheriff):
        return view_source_url(tool.buildbot.last_green_revision())


class Restart(IRCCommand):
    def execute(self, args, tool, sheriff):
        tool.irc().post("Restarting...")
        raise TerminateQueue()


class Rollout(IRCCommand):
    def execute(self, args, tool, sheriff):
        if len(args) < 2:
            tool.irc().post("Usage: SVN_REVISION REASON")
            return
        svn_revision = args[0]
        rollout_reason = " ".join(args[1:])
        tool.irc().post("Preparing rollout for r%s..." % svn_revision)
        try:
            bug_id = sheriff.post_rollout_patch(svn_revision, rollout_reason)
            bug_url = tool.bugs.bug_url_for_bug_id(bug_id)
            tool.irc().post("Created rollout: %s" % bug_url)
        except ScriptError, e:
            tool.irc().post("Failed to create rollout patch:")
            tool.irc().post("%s" % e)


class Hi(IRCCommand):
    def execute(self, args, tool, sheriff):
        return '"Only you can prevent forest fires." -- Smokey the Bear'
