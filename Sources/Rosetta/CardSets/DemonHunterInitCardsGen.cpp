﻿// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/DemonHunterInitCardsGen.hpp>
#include <Rosetta/Enchants/Enchants.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddCardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;

namespace RosettaStone
{
void DemonHunterInitCardsGen::AddDemonHunter(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_173] Command the Illidari - COST:5
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon six 1/1 Illidari with <b>Rush</b>.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("BT_036t", 6));
    cards.emplace("BT_173", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_175] Twin Slice - COST:0
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your hero +1 Attack this turn.
    //       Add 'Second Slice' to your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_175e", EntityType::HERO));
    power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "BT_175t", 1));
    cards.emplace("BT_175", CardDef(power));
}

void DemonHunterInitCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [BT_175e] Twin Slice (*) - COST:0
    // - Set: Demon Hunter Initiate
    // --------------------------------------------------------
    // Text: Your hero has +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("BT_175e"));
    cards.emplace("BT_175e", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [BT_175t] Second Slice - COST:0
    // - Set: Demon Hunter Initiate, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your hero +1 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_175e", EntityType::HERO));
    cards.emplace("BT_175t", CardDef(power));
}

void DemonHunterInitCardsGen::AddAll(std::map<std::string, CardDef>& cards)
{
    AddDemonHunter(cards);
    AddDemonHunterNonCollect(cards);
}
}  // namespace RosettaStone
