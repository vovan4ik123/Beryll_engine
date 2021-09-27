#pragma once

#include "CppHeaders.h"

#include "GameState.h"

namespace Beryll
{
    class GameStateMachine
    {
    public:
        GameStateMachine() = delete;
        ~GameStateMachine() = delete;

        static void updateBeforePhysics();
        static void updateAfterPhysics();
        static void draw();
        static void playSound();

        static void pushState(std::shared_ptr<GameState> state);
        static void changeState(std::shared_ptr<GameState> state);
        static void popState();

        static int getStatesCount() { return m_gameStates.size(); }

        static const GameStateID getStateID()
        {
            if(!m_gameStates.empty()) return m_gameStates.back()->ID;
            else return GameStateID::NO_STATE;
        }

    private:
        static std::vector<std::shared_ptr<GameState>> m_gameStates;
        static std::vector<std::shared_ptr<GameState>> m_gameStatesForDelete;
    };
}

