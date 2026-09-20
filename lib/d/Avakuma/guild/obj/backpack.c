// /d/Avakuma/guild/obj/backpack.c
#include <mudlib.h>
inherit CONTAINER;

void create() {
    ::create();
    set("id", ({ "backpack", "pack", "a backpack" }));
    set("short", "a backpack");
    set_open_long(@EndText
    A canvas pack with broad shoulder straps, built to carry a good deal
without the weight of it hanging off one shoulder.
EndText
    );
    set("bulk", 60);
    set("mass", 120);
    set("capacity", 900);
    set("volume", 260);
    set("value", ({ 34, "gold" }));
}
