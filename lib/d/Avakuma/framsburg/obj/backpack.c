#include <mudlib.h>
inherit CONTAINER;
void create() {
    ::create();
    set("id", ({ "backpack", "pack" }));
    set("short", "a backpack");
    set_open_long(@EndText
    Made out of sturdy green canvas, this standard explorer's
backpack is perfect for keeping the odd item or two out of the
way. Two woven straps hang off of the backpack, enabling it
to be worn upon the back.
EndText
    );
    set("bulk", 60); set("mass", 120);
    set("capacity", 900); set("volume", 260);
    set("value", ({ 32, "gold" }));
}
