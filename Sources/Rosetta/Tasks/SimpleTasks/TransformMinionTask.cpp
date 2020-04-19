// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/TransformMinionTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
TransformMinionTask::TransformMinionTask(EntityType entityType, int costChange)
    : ITask(entityType), m_costChange(costChange)
{
    // Do nothing
}

TaskStatus TransformMinionTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    const FormatType format = player->game->GetFormatType();

    std::vector<Card*> minionCards;
    if (format == FormatType::STANDARD)
    {
        for (auto& card : Cards::GetAllStandardCards())
        {
            if (card->GetCardType() == CardType::MINION)
            {
                minionCards.emplace_back(card);
            }
        }
    }
    else
    {
        for (auto& card : Cards::GetAllWildCards())
        {
            if (card->GetCardType() == CardType::MINION)
            {
                minionCards.emplace_back(card);
            }
        }
    }

    for (auto& playable : playables)
    {
        std::vector<Card*> cards;
        for (auto& card : minionCards)
        {
            if (card->GetCost() == playable->card->GetCost() + m_costChange)
            {
                cards.emplace_back(card);
            }
        }

        if (!cards.empty())
        {
            const auto idx = Random::get<std::size_t>(0, cards.size() - 1);
            Generic::ChangeEntity(m_player, playable, cards[idx], true);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> TransformMinionTask::CloneImpl()
{
    return std::make_unique<TransformMinionTask>(m_entityType, m_costChange);
}
}  // namespace RosettaStone::SimpleTasks
