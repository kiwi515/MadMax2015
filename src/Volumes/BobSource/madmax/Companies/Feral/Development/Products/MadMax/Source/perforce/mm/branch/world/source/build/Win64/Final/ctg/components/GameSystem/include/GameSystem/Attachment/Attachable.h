#ifndef COMPONENT_ATTACHABLE_H
#define COMPONENT_ATTACHABLE_H

#include "build/Win64/Final/engine/AvaCore/main/AvaCore/Math/Matrix.h"
#include "build/Win64/Final/ctg/components/GameSystem/include/GameSystem/Attachment/Attachee.h"

class CAttachable {
    protected:
    CAttachee* m_Attachee;
    CMatrix4f m_AttachOffset;
    const CMatrix4f* m_AttachMatrix;
};

#endif