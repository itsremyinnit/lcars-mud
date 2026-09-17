// /cmds/adm/_unwiz.c: return a wizard to player status. LCARS-MUD
#include <mudlib.h>
#include <config.h>
#include <uid.h>
#include "/d/Nexus/nexus.h"
inherit DAEMON;

#define SYNTAX     "Syntax: unwiz <wizard>\n"
#define QUARTERS_D "/d/Nexus/adm/quarters_d"

private void ring_departs(object player) {
    object *inv;
    string cap;
    int i;

    if (!player) return;
    cap = (string)player->query("cap_name");
    inv = all_inventory(player);
    for (i = 0; i < sizeof(inv); i++) {
        if (base_name(inv[i]) != NEXUS_RING) continue;
        if (inv[i]->query("equipped")) inv[i]->unequip(1);
        if (interactive(player)) {
            tell_object(player,
                "\nCalenmîr stirs on your hand. Its green flame turns away from you, toward\n" +
                "some distant place, as if hearing a call no one else can. The ring rises,\n" +
                "hangs a moment in the air, and murmurs: \"A new bearer has been chosen.\"\n" +
                "Then it streaks away as a line of green light, and is gone.\n\n");
            if (environment(player))
                tell_room(environment(player),
                    "Calenmîr rises from " + cap + "'s hand, its green flame turning toward some\n" +
                    "distant place. \"A new bearer has been chosen,\" it murmurs, and streaks away\n" +
                    "as a line of green light.\n", ({ player }));
        }
        destruct(inv[i]);
    }
}

int cmd_unwiz(string str) {
    object player, link;
    int online;

    if (!adminp(geteuid(previous_object()))) {
        write("Illegal attempt at unwiz by " + file_name(previous_object()) + "\n");
        return 1;
    }
    seteuid(ROOT_UID);

    notify_fail(SYNTAX);
    if (!str || str == "") return 0;
    str = lower_case(str);

    if (!user_exists(str)) { write("Unwiz: No such player.\n"); return 1; }
    if (adminp(str)) {
        write("Unwiz: " + capitalize(str) + " is an admin. Remove them from the admin group first.\n");
        return 1;
    }

    player = find_player(str);
    online = player && interactive(player);

    if (player) {
        link = player->query_link();
    } else {
        link = new(CONNECTION);
        link->clear_euid();  // LCARS-MUD: lets export_uid() work on FluffOS
        seteuid(str);
        export_uid(link);
        seteuid(ROOT_UID);
        link->set("name", str);
        if (!link->restore()) {
            write("Unwiz: Could not load " + capitalize(str) + ".\n");
            link->remove();
            return 1;
        }
        link->restore_body();
        player = link->query("body_ob");
    }

    if (!link || !link->query("wizard")) {
        write("Unwiz: " + capitalize(str) + " is not a wizard.\n");
        if (!online) { if (player) player->remove(); if (link) link->remove(); }
        return 1;
    }

    ring_departs(player);
    link->set("wizard", 0);
    if (player) {
        player->set("PATH", USER_CMDS);
        player->delete("nexus_ceremony");
    }
    QUARTERS_D->vacate(str);

    if (player) player->save_data();
    link->save_data();

    write("Unwiz: " + capitalize(str) + " is no longer a wizard.\n");
    if (online) tell_object(player, "You are no longer a wizard.\n");
    else { if (player) player->remove(); link->remove(); }
    return 1;
}

string help() {
    return SYNTAX + "\nReturns a wizard to player status. Their ring departs, their quarters\n" +
           "become vacant, and their home folder is left untouched.\n";
}
