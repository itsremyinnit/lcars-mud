// /d/Avakuma/framsburg/pub.c
// Arrival point through the Towers Arch, and the only way into the
// Sheriff's Guild. "push board" opens the passage; the board itself is
// examinable and carries the hint.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A ruined pub");
    set("long", @EndText
PLACEHOLDER. The ruined pub. Holed roof, a floor that creaks, broken
tables and chairs. The bar is still in one piece. On the far wall the
once-ominously nailed wooden boards have degraded since.
EndText
    );
    set("item_desc", ([
        "board" : @EndText
    There is nothing special about the old, nailed board, perhaps
save for some text roughly cut with a knife into a corner of the
board.  You read "Death to the sheriffs!".  Hmm... it seems like
some vandal had some problems with the law.  The nails no longer
look at strong as they once were.  You wonder what would happen
if you tried pushing the board again...
EndText
        ,
        "boards" : @EndText
    There is nothing special about the old, nailed board, perhaps
save for some text roughly cut with a knife into a corner of the
board.  You read "Death to the sheriffs!".  Hmm... it seems like
some vandal had some problems with the law.  The nails no longer
look at strong as they once were.  You wonder what would happen
if you tried pushing the board again...
EndText
        ,
    ]));
    set("exits", ([
        "west" : "/d/Avakuma/framsburg/road_north",
    ]));
    set("exit_order", ({ "west" }));
}

void init() {
    add_action("push_board", "push");
}

int push_board(string str) {
    object dest;

    if (str != "board" && str != "boards") {
        notify_fail("Push what?\n");
        return 0;
    }
    dest = find_object_or_load(GUILD_OUTSIDE);
    if (!dest) {
        write("The board does not budge.\n");
        return 1;
    }
    if (this_player()->query("avakuma_board_seen")) {
        write("You pop the loose board with your hand again and slip through.\n");
    } else {
        this_player()->set("avakuma_board_seen", 1);
        write(
"    You push on the out of place board and right in front of you a \n"
"large doorway opens. Your curiosity overwhelms you as you venture \n"
"forth into the unknown. Once you are on the other side of the door\n"
"it closes.\n");
    }
    this_player()->move_player(dest, "$N pushes against the far wall and is gone.\n");
    return 1;
}
