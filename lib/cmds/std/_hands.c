// _hands.c
// LCARS-MUD: report what is occupying the player's hands.
#include <mudlib.h>
inherit DAEMON;

string help();

int cmd_hands(string str) {
    object *inv, me;
    int i, free, shown, h;
    string what;

    me = this_player();
    inv = all_inventory(me);
    shown = 0;

    write("You have two hands.\n");
    for (i = 0; i < sizeof(inv); i++) {
        if (!inv[i]) continue;
        what = 0;

        h = (int)inv[i]->query("hands");
        if (h) what = "(in hands)";
        else if (inv[i]->query("wielded")) what = "(wielded)";
        else if (inv[i]->query("equipped") && inv[i]->query("type") == "shield")
            what = "(shield)";

        if (!what) continue;
        write(sprintf("You are holding %-38s %s\n",
              lower_case((string)inv[i]->query("short")), what));
        shown++;
    }

    free = (int)me->hands_free();
    if (!free) write("You have no free hands.\n");
    else if (free == 1) write("You have one free hand.\n");
    else write("You have two free hands.\n");
    return 1;
}

string help() {
return(@HELP
Syntax: hands

Shows what your hands are occupied with: things held, weapons wielded,
and a shield if you are carrying one.
HELP
  );
}
