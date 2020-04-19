// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/ApplyEffectTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
ApplyEffectTask::ApplyEffectTask(EntityType entityType,
                                 std::vector<std::shared_ptr<IEffect>> effects)
    : ITask(entityType), m_effects(std::move(effects))
{
    // Do nothing
}

TaskStatus ApplyEffectTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        for (auto& effect : m_effects)
        {
            effect->ApplyTo(playable);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ApplyEffectTask::CloneImpl()
{
    return std::make_unique<ApplyEffectTask>(m_entityType, m_effects);
}
}  // namespace RosettaStone::SimpleTasks
