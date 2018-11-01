// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Entity.h>

namespace Hearthstonepp
{
Entity::Entity(Card& _card) : card(new Card(_card))
{
    for (auto& mechanic : _card.mechanics)
    {
        Entity::SetGameTag(mechanic, 1);
    }
}

Entity::Entity(const Entity& ent)
{
    FreeMemory();

    card = ent.card;
    m_gameTags = ent.m_gameTags;
}

Entity::~Entity()
{
    FreeMemory();
}

Entity& Entity::operator=(const Entity& ent)
{
    if (this == &ent)
    {
        return *this;
    }

    FreeMemory();

    card = ent.card;
    m_gameTags = ent.m_gameTags;

    return *this;
}

Entity* Entity::Clone() const
{
    return new Entity(*this);
}

int Entity::GetGameTag(GameTag tag)
{
    return m_gameTags[tag];
}

void Entity::SetGameTag(GameTag tag, int value)
{
    m_gameTags.insert_or_assign(tag, value);
}

void Entity::FreeMemory()
{
    m_gameTags.clear();

    delete card;
}
}  // namespace Hearthstonepp