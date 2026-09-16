// Onboarding security test: every attempt below should fail.
void create() {
    mixed err;

    err = catch(ffi_load("libc.so.6"));
    write("ffi_load:       " + (err ? "BLOCKED " + err : "ALLOWED (PROBLEM)\n"));

    err = catch(external_start(1, "id", (: 0 :), (: 0 :)));
    write("external_start: " + (err ? "BLOCKED " + err : "ALLOWED (PROBLEM)\n"));

    err = catch(write("read_file:      " +
        (read_file("/../etc/config.tmi2") ? "READ SUCCEEDED (PROBLEM)\n" : "BLOCKED\n")));
    if (err) write("read_file:      BLOCKED " + err);

    err = catch(write("write_file:     " +
        (write_file("/adm/etc/hacked", "x") ? "WROTE (PROBLEM)\n" : "BLOCKED\n")));
    if (err) write("write_file:     BLOCKED " + err);
}
