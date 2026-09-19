// /d/Avakuma/framsburg/pub.c
// Arrival point through the Towers Arch, and the only way into the
// Sheriff's Guild. "push board" opens the passage; the loose board is
// examinable and carries the hint. "boards" describes the wall generally.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A ruined pub");
    set("long", @EndText
    This was a fine pub once. So much of the roof has come down that
what remains hardly deserves the name, and what fell lies where it
landed, among the broken tables and chairs. The floor bends underfoot
and creaks with every step. The bar has come through whole, though the
shelves behind it were emptied long ago of anything worth carrying off.
The far wall was boarded over in a hurry by someone who meant it to
hold. The nails have had years to loosen since.
EndText
    );
    set("item_desc", ([
        "bar" : @EndText
    A long slab of dark wood, waist-high, running the whole length of
the room. Whoever built it built it to last. The shelves behind held
bottles once; what was not carried off was broken where it stood, and
there is room enough behind the bar for something to have been left.
EndText
        ,
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
    Weathered grey and splitting along the grain. One of them sits
loose in its nails.
EndText
        ,
        "roof" : @EndText
    Twenty feet up, where it survives at all. The wood rotted through
and came down in sections under its own weight, leaving gaps wide
enough to stand in.
EndText
        ,
        "tables" : @EndText
    Built for four, and heavy enough that nobody troubled to haul them
off. Not one of them still stands on four legs.
EndText
        ,
        "chairs" : @EndText
    They matched the tables, and they have come to the same end,
scattered and broken across the floor.
EndText
        ,
        "floor" : @EndText
    The boards have gone soft with damp. They give underfoot, and there
is no crossing this room quietly.
EndText
        ,
        "holes" : @EndText
    Wide enough to let in the light, and the weather with it.
EndText
        ,
        "bottles" : @EndText
    Gone, every one. A few necks and bases still catch the light in the
dust behind the bar.
EndText
        ,
        "wall" : @EndText
    The far wall, boarded over from this side. The timbers were nailed
across at angles by someone working quickly.
EndText
        ,
        "nails" : @EndText
    Hand-forged, and rusted to much the same colour as the wood they
hold. Several stand proud of the timber.
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
