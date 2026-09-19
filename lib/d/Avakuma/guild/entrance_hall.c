// /d/Avakuma/guild/entrance_hall.c
// North is the jail, reached by the guild guard seizing you rather than
// by walking. Deferred: the north exit is deliberately absent until that
// mechanic exists. exit_order keeps its slot for when it returns.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

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
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/guild/hallway_1",
        "south" : "/d/Avakuma/guild/guild_bar",
        "west"  : "/d/Avakuma/guild/outside",
    ]));
    set("exit_order", ({ "north", "east", "south", "west" }));
}
