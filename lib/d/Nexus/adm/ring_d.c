// /d/Nexus/adm/ring_d.c
// What corps, if any, is this person wearing a ring of?
//
// This is the interface NPCs use to react to ring bearers. It deliberately
// reports the corps rather than the object, so an NPC never needs to know
// about Calenmir specifically and a new corps is a data change rather than
// a code change.
//
// Note: this has nothing to do with wizard powers. Those are gated on
// Calenmir itself in /std/user.c's cmd_hook. A ring of some other corps
// confers no wizardry and must never be made to.
#include <mudlib.h>
inherit DAEMON;

void create() { seteuid(getuid()); }
void clean_up() { }

// The corps of the ring this person is wearing, or 0 for none.
string query_worn_corps(object who) {
    object *inv;
    int i;

    if (!who) return 0;
    inv = all_inventory(who);
    for (i = 0; i < sizeof(inv); i++)
        if (inv[i]->query("corps") && inv[i]->query("equipped"))
            return (string)inv[i]->query("corps");
    return 0;
}

// Convenience: is this person wearing a ring of the named corps?
int wearing_corps(object who, string corps) {
    return query_worn_corps(who) == corps;
}
