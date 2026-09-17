// /d/Nexus/boards/hearth_board.c: notices by the fire
inherit "/std/board/bboard";

void create() {
    bboard::create();
    set_attic_dir("/d/Nexus/data/attic");
    set_save_dir("/d/Nexus/data");
    set_save_file("hearth");
    set_location("/d/Nexus/rooms/kindled_hearth");
    set("short.text", "Hearthside notice board");
}
