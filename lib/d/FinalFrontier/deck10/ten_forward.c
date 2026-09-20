// /d/FinalFrontier/deck10/ten_forward.c
// Arrival point from the Nexus. The arch puts you here rather than on the
// bridge: you come aboard as a guest, not as crew.
#include "/d/FinalFrontier/frontier.h"
inherit FF_ROOM;

void create() {
    ::create();
    set("short", "Ten-Forward");
    set("long", @EndText
    The whole forward wall is window, curving away to either side, and
the stars beyond it are the brightest thing in the room by a wide margin.
Tables in ones and twos, low chairs, a long bar to port with bottles
behind it that no replicator made. The lighting has been set low enough
to be a decision. A handful of people are here, none of them in a hurry,
and the room is doing the thing it was built to do, which is absorb the
day off a crew that has had several too many of them.
EndText
    );
    set("item_desc", ([
        "window" : @EndText
    It runs the entire curve of the forward hull, floor to ceiling. At
this hour half the room is sitting facing it and not talking.
EndText
        ,
        "bar" : @EndText
    Long, dark, and polished by use rather than by machine. The bottles
behind it are real glass with real labels, most of them from places you
have never heard of.
EndText
        ,
        "bottles" : @EndText
    Ranked along the back wall, and not one of them a replicator pattern.
Several have no label at all, which seems less like an oversight than a
policy.
EndText
        ,
        "tables" : @EndText
    Small, round, set in ones and twos rather than rows. Nobody has been
seated anywhere by anybody.
EndText
        ,
        "chairs" : @EndText
    Low, soft, and angled toward the window without exception.
EndText
        ,
        "stars" : @EndText
    Unhurried and very bright. Whatever is happening out there is
happening slowly enough to watch with a drink in your hand.
EndText
        ,
        "people" : @EndText
    Crew, off duty, in ones and twos. One table has a card game that
appears to have been going for some hours. Nobody looks up when you come
in, which is the room working as intended.
EndText
        ,
        "lighting" : @EndText
    Low, warm, and nothing like the rest of the ship. Somebody argued for
this once and won.
EndText
        ,
    ]));
    set("exits", ([
        "aft" : "/d/FinalFrontier/deck10/corridor_ten",
    ]));
    set("exit_order", ({ "aft" }));
}
