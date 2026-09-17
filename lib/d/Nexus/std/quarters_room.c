// /d/Nexus/std/quarters_room.c: a wizard's private quarters.
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

#define QUARTERS_D "/d/Nexus/adm/quarters_d"

string owner;

void setup_quarters(string o) {
    string rune;
    owner = o;
    rune = (string)NEXUS_RING->rune_for(o);
    set("owner", o);
    set("short", capitalize(o) + "'s Quarters");
    set("long", wrap(
        "These quarters are warm and unhurried, with a low ceiling of dark beams, a bed heaped " +
        "with quilts, a writing desk beneath a round window, and a fire murmuring in a small stone " +
        "grate. Carved into the stone above the mantel is " + rune + ", the mark of " +
        capitalize(o) + ". The room feels less decorated than waiting to become someone's. " +
        "The door leads back out to the corridor."));
    set("item_desc", ([
        "bed" : "Heaped with quilts in greens and golds. It looks like a very good place to be tired.\n",
        "desk" : "A writing desk with a blotter, an inkwell, and a drawer that sticks just slightly.\n",
        "window" : "Round, like a porthole, looking out on soft light and nowhere in particular.\n",
        "fire" : "Small, steady, and entirely content to keep you company.\n",
    ]));
    set("exits", ([ "out" : (string)QUARTERS_D->segment_path(o), "south" : (string)QUARTERS_D->segment_path(o) ]));
    set("pre_exit_func/out", "leaving");
    set("pre_exit_func/south", "leaving");
}

void init() {
    object who = this_player();
    add_action("do_invite", "invite");
    add_action("do_grant", "grant");
    add_action("do_revoke", "revoke");
    add_action("do_guests", "guests");
    if (who && !QUARTERS_D->may_enter(owner, (string)who->query("name")))
        call_out("eject", 0, who);
}

void eject(object who) {
    if (!who || environment(who) != this_object()) return;
    tell_object(who, "The quarters gently decline to have you, and you find yourself back in the corridor.\n");
    who->move_player((string)QUARTERS_D->segment_path(owner), (string)who->query("cap_name") + " is shown back into the corridor");
}

int leaving() {
    string name = (string)this_player()->query("name");
    if (name != owner) QUARTERS_D->clear_invite(owner, name);
    return 0;
}

private int owner_here() {
    return this_player() && (string)this_player()->query("name") == owner;
}

int do_invite(string str) {
    object who;
    if (!owner_here()) return 0;
    if (!str) { write("Invite whom?\n"); return 1; }
    str = lower_case(str);
    if (!(who = find_player(str))) {
        write(capitalize(str) + " isn't here to receive an invitation.\n");
        return 1;
    }
    QUARTERS_D->add_invite(owner, str);
    write("You send an invitation to " + capitalize(str) + ".\n");
    tell_object(who, capitalize(owner) + " invites you to their quarters in the " +
        capitalize((string)QUARTERS_D->query_wing(owner)) + " Wing of the Inn.\n");
    return 1;
}

int do_grant(string str) {
    if (!owner_here()) return 0;
    if (!str) { write("Grant entry to whom?\n"); return 1; }
    str = lower_case(str);
    if (!user_exists(str)) { write("There is no one by that name.\n"); return 1; }
    QUARTERS_D->add_grant(owner, str);
    write(capitalize(str) + " may now enter your quarters whenever they like.\n");
    return 1;
}

int do_revoke(string str) {
    object who;
    if (!owner_here()) return 0;
    if (!str) { write("Revoke entry for whom?\n"); return 1; }
    str = lower_case(str);
    if (!QUARTERS_D->remove_guest(owner, str)) {
        write(capitalize(str) + " wasn't on your guest list.\n");
        return 1;
    }
    write(capitalize(str) + " is no longer welcome in your quarters.\n");
    if ((who = present(str, this_object())) && interactive(who)) eject(who);
    return 1;
}

int do_guests(string str) {
    mapping g;
    if (!owner_here()) return 0;
    g = (mapping)QUARTERS_D->query_guests(owner);
    write("Invited (for now): " + (sizeof(g["invited"]) ? implode(map_array(g["invited"], (: capitalize :)), ", ") : "no one") + "\n");
    write("Granted (standing): " + (sizeof(g["granted"]) ? implode(map_array(g["granted"], (: capitalize :)), ", ") : "no one") + "\n");
    return 1;
}
