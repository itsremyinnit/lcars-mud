// /d/Avakuma/guild/obj/backpack.c
#include <mudlib.h>
inherit CONTAINER;

void create() {
    ::create();
    set("id", ({ "backpack", "pack", "a backpack" }));
    set("short", "a backpack");
    set_open_long(@EndText
    Made out of sturdy green canvas, this standard explorer's
backpack is perfect for keeping the odd item or two out of the
way. Two woven straps hang off of the backpack, enabling it
to be worn upon the back.
EndText
    );
    set("bulk", 60);
    set("mass", 120);
    set("capacity", 900);
    set("volume", 260);
    set("wear_slot", "back");
    set("value", ({ 34, "gold" }));
}

// Worn on the back. CONTAINER and ARMOR both descend from OBJECT and
// FluffOS will not share the duplicate, so inheriting both fails to
// compile ("Illegal to redefine nomask function"). The wear verbs are
// added directly instead. A worn pack still takes no hands.
void init() {
    ::init();
    add_action("do_wear", "wear");
    add_action("do_unwear", "unwear");
    add_action("do_unwear", "remove");
}

int do_wear(string str) {
    if (!str || !id(str)) return 0;
    if (environment() != this_player()) {
        notify_fail("You are not carrying that.\n");
        return 0;
    }
    if (query("worn")) {
        write("You are already wearing it.\n");
        return 1;
    }
    // One pack at a time. ARMOR would give us slots for free, but it
    // cannot be inherited alongside CONTAINER (see the note above), so
    // the check is by hand: anything else on us claiming the back.
    {
        object *inv;
        int i;

        inv = all_inventory(this_player());
        for (i = 0; i < sizeof(inv); i++)
            if (inv[i] && inv[i] != this_object() && inv[i]->query("worn") &&
                inv[i]->query("wear_slot") == "back") {
                write("You are already wearing a pack on your back.\n");
                return 1;
            }
    }
    set("worn", 1);
    write("You shoulder the backpack.\n");
    say((string)this_player()->query("cap_name") + " shoulders a backpack.\n");
    return 1;
}

int do_unwear(string str) {
    if (!str || !id(str)) return 0;
    if (!query("worn")) {
        write("You are not wearing it.\n");
        return 1;
    }
    set("worn", 0);
    write("You take the backpack off.\n");
    say((string)this_player()->query("cap_name") + " takes off a backpack.\n");
    return 1;
}
