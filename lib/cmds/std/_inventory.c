/*
// This file is part of the TMI Distribution Mudlib.
// Please include this header if you use this code.
// Slick Ace, 01/02/91
// Help added by Brian (1/28/92)
// Rewritten by Buddha to show equipped items properly (2/3/92)
// Changed by Mobydick@TMI-2 (9/16/92) to capitalize short descriptions
// and to handle the new equipping system.
// Replaced the hardcoded weight limit with included #defines. Moby, 4-26-93
//
// LCARS-MUD: reformatted to match T2T. Gold and encumbrance on the header
// line, the carried list tagged (worn)/(wielded)/(concealed), and a
// separate section for what is inside containers. Encumbrance is not yet
// modelled, so the level always reads "unencumbered"; when it is built,
// only query_encumbrance() below needs to change.
*/

#include <move.h>
#include <user2.h>
#include <mudlib.h>

inherit DAEMON ;

// Placeholder until encumbrance is a real system. T2T bases it on weight
// against strength, counts bulk only for things carried in the hands, and
// weighs gold at 10 coins to the pound.
private string query_encumbrance(object who) {
    return "unencumbered";
}

private string tag_for(object ob) {
    string tmp;

    tmp = (string)ob->query("short");
    if (!tmp) return 0;
    // One state tag only: a thing is wielded, or worn, or neither.
    if (ob->query("wielded"))
        tmp += " (wielded)";
    else if (ob->query("equipped") || ob->query("worn"))
        tmp += " (worn)";
    if (ob->query("concealed"))  tmp += " (concealed)";
    if (ob->query("invisible"))  tmp += " (invisible)";
    return tmp;
}

int cmd_inventory() {
    object *items, *inside, me;
    string result, tmp;
    int i, j, gold;

    me = this_player();
    me->block_attack(4);

    items = all_inventory(me);
    gold = (int)me->query("wealth/gold");

    result = sprintf("Gold: %-18d Encumbrance: %s\n",
                     gold, query_encumbrance(me));

    tmp = "";
    for (i = 0; i < sizeof(items); i++) {
        if (!items[i]) continue;
        if (tag_for(items[i]))
            tmp += " " + capitalize(tag_for(items[i])) + ".\n";
    }
    if (tmp == "")
        result += "You are carrying nothing.\n";
    else
        result += "You are carrying the following on your person:\n" + tmp;

    // Anything inside a container gets its own section, the way T2T does.
    tmp = "";
    for (i = 0; i < sizeof(items); i++) {
        if (!items[i]) continue;
        inside = all_inventory(items[i]);
        for (j = 0; j < sizeof(inside); j++)
            if (inside[j] && inside[j]->query("short"))
                tmp += " " + capitalize((string)inside[j]->query("short")) + "\n";
    }
    if (tmp != "")
        result += "You go through your containers and find:\n" + tmp;

    write(result);
    return 1;
}

string help() {
   return("Syntax: inventory\n\n"+
      "This command gives you a list of the items\n"+
      "contained in your inventory, what is inside anything you are\n"+
      "carrying, your gold, and your encumbrance.\n");
}
/* EOF */
