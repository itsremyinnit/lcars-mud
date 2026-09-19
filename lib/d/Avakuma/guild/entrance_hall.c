// /d/Avakuma/guild/entrance_hall.c
// North is the jail, and the guild guard stands in the way of it.
//
// Wearing a ring of the green corps, you are staff: the guard stands aside
// and you walk in. Otherwise he warns you once, and if you insist he
// obliges you with a cell. The corps check goes through RING_D rather than
// naming Calenmir, so other corps can be given their own reactions later
// without touching this room.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

#define RING_D "/d/Nexus/adm/ring_d"
#define JAIL   "/d/Avakuma/guild/jail"

void create() {
    ::create();
    set("short", "The guild entrance hall");
    set("long", @EndText
    The magnificent entrance hall to the guild of the Rim-Ainacam. Tall
marble columns rise to a huge vaulted ceiling, and the walls are cut
granite, which lends the room a good deal of power and strength. Shields
and banners hang along them. A gigantic red carpet covers the centre of
the floor. Beyond the columns the hall is clear of furniture and of
anything else that might get in a man's way.
EndText
    );
    set("item_desc", ([
        "columns" : @EndText
    Tall marble, with decorative fluted tops meeting the great
cross-beams that carry the ceiling.
EndText
        ,
        "ceiling" : @EndText
    Highly polished marble tiles fixed to the roof by some means not
apparent from down here. The light comes off the canted surfaces and
gives the whole ceiling a sparkle.
EndText
        ,
        "walls" : @EndText
    Finely cut granite blocks. The masons went to considerable trouble
grinding the tiny bits of ivory that run through the mortar between them.
EndText
        ,
        "shields" : @EndText
    Shields bearing many different crests, hung with colourful banners
about them, and between them they make the hall regal. The crests are
the personal insignia of every Guildmaster who came before.
EndText
        ,
        "banners" : @EndText
    Red through blue to purple, hanging along the walls with the shields
of the Guildmasters. They show battles against the darkness, and the
honour of bringing brigands and other such ruffians to justice.
EndText
        ,
        "carpet" : @EndText
    Thick and plush and red, covering the centre of the floor, bordered
in a gold strip with the crest of the Rim-Ainacam worked into the middle.
EndText
        ,
        "crest" : @EndText
    The crest of the Rim-Ainacam, worked into the centre of the carpet
and carved into half the furniture in the building.
EndText
        ,
        "guard" : @EndText
    A guard of the Rim-Ainacam, standing where he can see the north door
and everyone who looks at it.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/Avakuma/guild/jail",
        "east"  : "/d/Avakuma/guild/hallway_1",
        "south" : "/d/Avakuma/guild/guild_bar",
        "west"  : "/d/Avakuma/guild/outside",
    ]));
    set("exit_order", ({ "north", "east", "south", "west" }));
    set("pre_exit_func/north", "guard_north");
}

int guard_north() {
    object who = this_player();
    string corps;

    corps = (string)RING_D->query_worn_corps(who);

    if (corps == "green") {
        write(
"\n    You raise your hand without breaking stride. The stone on your\n"
"finger answers: a slow green light wells up through the cracks in it\n"
"and lies along your knuckles like something breathing.\n"
"    The guard's eyes go to it, and then away, and he is already\n"
"standing aside before he has finished deciding to. He does not salute.\n"
"Whatever the ring means to him, it is not the sort of thing you salute.\n\n");
        // Staff are not prisoners. Walking in under the ring ends any
        // sentence still hanging over you.
        who->delete("avakuma_jailed");
        say((string)who->query("cap_name") +
            " raises a hand, and green light wells up through the stone on it.\n"
            "The guard stands aside.\n");
        return 0;
    }

    if (who->query("avakuma_warned")) {
        who->delete("avakuma_warned");
        write("Guardian says to you: Okay!\n"
              "The guard shrugs, opens the door, and tosses you inside.\n");
        JAIL->sentence(who);
        return 0;
    }

    who->set("avakuma_warned", 1);
    write(
"\n    The guard looks you up and down, trying to discern what your\n"
"intention could be in visiting the jail of Framsburg.  After a\n"
"long pause, he curtly tells you that if you really want to find\n"
"out what it's like in there, he'd be glad to accomodate you.\n\n");
    return 1;
}
