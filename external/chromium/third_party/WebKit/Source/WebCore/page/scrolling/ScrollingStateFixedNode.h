/*
 * Copyright (C) 2012 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ScrollingStateFixedNode_h
#define ScrollingStateFixedNode_h

#if ENABLE(THREADED_SCROLLING)

#include "ScrollingConstraints.h"
#include "ScrollingStateNode.h"

#include <wtf/Forward.h>

namespace WebCore {

class FixedPositionViewportConstraints;

class ScrollingStateFixedNode : public ScrollingStateNode {
public:
    static PassOwnPtr<ScrollingStateFixedNode> create(ScrollingStateTree*, ScrollingNodeID);

    virtual PassOwnPtr<ScrollingStateNode> clone();

    virtual ~ScrollingStateFixedNode();

    enum ChangedPropertyForFixed {
        ViewportConstraints = 1 << 0
    };

    virtual unsigned changedProperties() const OVERRIDE { return m_changedProperties; }

    void updateConstraints(const FixedPositionViewportConstraints&);
    const FixedPositionViewportConstraints& viewportConstraints() const { return m_constraints; }

private:
    ScrollingStateFixedNode(ScrollingStateTree*, ScrollingNodeID);
    ScrollingStateFixedNode(const ScrollingStateFixedNode&);

    virtual bool isFixedNode() OVERRIDE { return true; }

    virtual bool hasChangedProperties() const OVERRIDE { return m_changedProperties; }
    virtual void resetChangedProperties() OVERRIDE { m_changedProperties = 0; }

    virtual void dumpProperties(TextStream&, int indent) const OVERRIDE;

    FixedPositionViewportConstraints m_constraints;
    unsigned m_changedProperties;
};

inline ScrollingStateFixedNode* toScrollingStateFixedNode(ScrollingStateNode* node)
{
    ASSERT(!node || node->isFixedNode());
    return static_cast<ScrollingStateFixedNode*>(node);
}
    
// This will catch anyone doing an unnecessary cast.
void toScrollingStateFixedNode(const ScrollingStateFixedNode*);

} // namespace WebCore

#endif // ENABLE(THREADED_SCROLLING)

#endif // ScrollingStateFixedNode_h
