#pragma once

#include "LibsHeaders.h"

#include "GUIObject.h"

namespace Beryll
{
    class DemoImGUI : public GUIObject
    {
    public:
        DemoImGUI();
        ~DemoImGUI();

        virtual void updateBeforePhysics() override;
        virtual void updateAfterPhysics() override;
        virtual void draw() override;
        virtual void playSound() override;
    };
}

