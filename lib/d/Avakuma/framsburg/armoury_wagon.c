// /d/Avakuma/framsburg/armoury_wagon.c
// Plain room for now. Shop mechanics deferred.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The armoury wagon");
    set("long", @EndText
PLACEHOLDER. Inside the armoury wagon: weapons, armours, a partition
and a sign. Not yet a working shop.
EndText
    );
    set("exits", ([
        "out" : "/d/Avakuma/framsburg/armoury_house",
    ]));
    set("exit_order", ({ "out" }));
}
