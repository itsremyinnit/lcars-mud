// /d/Avakuma/guild/conference.c
// The wanted poster is a real notice board in the original, carrying
// fifteen years of posts. Described here; the board object is seeded
// separately.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A conference room");
    set("long", @EndText
    Through the enormous double doors is the grand conference room of
the guild, where the important arguments were had, from guild rules to
the politics of dealing with other towns. A gigantic triangular table
dominates the room with dozens of cushioned chairs around it. Banners
bearing the guild seal hang on the wooden walls, and tapestries between
them showing the glory of the profession. A tray sits at the centre of
the table.
EndText
    );
    set("item_desc", ([
        "table" : @EndText
    As flagrantly oversized as the doors. An equilateral triangle
twenty-five feet to a side, built for grand committees with delegations
from across the Eotheod.
EndText
        ,
        "chairs" : @EndText
    Strong wood under ivory-coloured leather, stuffed with mounds of
cotton and riveted at the seams.
EndText
        ,
        "banners" : @EndText
    Fixed at the top of the wall and hanging to the floor in a variety
of colours, every one bearing the seal of the sheriff's guild.
EndText
        ,
        "tapestries" : @EndText
    Set between the banners, showing episodes of valour by sheriffs from
across Arda. Some hang here from as far away as Meduseld and Minas
Tirith.
EndText
        ,
        "walls" : @EndText
    Large and intricately carved, and fashioned out of some beautiful
wood.
EndText
        ,
        "tray" : @EndText
    Silver, and sized to suit the table it stands on, with rows of cups
around a large silver pot.
EndText
        ,
        "poster" : @EndText
    Tacked to one of the longer walls, newly made on fine vellum. The
old board was lost in a fire and this one was commissioned in its place.
EndText
        ,
        "doors" : @EndText
    Enormous, rising to a rounded crest almost at the ceiling, and the
wood a foot thick. For all that, they swing easily, which hints at
dwarven work. There is fresh work on the locks. They have been changed
recently.
EndText
        ,
    ]));
    set("exits", ([
        "west" : "/d/Avakuma/guild/hallway_2",
    ]));
    set("exit_order", ({ "west" }));
    create_door("west", "east", "A heavy door", "closed");
}
