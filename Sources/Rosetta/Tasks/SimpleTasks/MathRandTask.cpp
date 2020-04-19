// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/MathRandTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
MathRandTask::MathRandTask(int min, int max) : m_min(min), m_max(max)
{
    // Do nothing
}

TaskStatus MathRandTask::Impl(Player* player)
{
    player->game->taskStack.num[0] = Random::get<int>(m_min, m_max);
    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> MathRandTask::CloneImpl()
{
    return std::make_unique<MathRandTask>(m_min, m_max);
}
}  // namespace RosettaStone::SimpleTasks
