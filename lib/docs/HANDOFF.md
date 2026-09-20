# Nexus-96: Shattered Sector — Project Handoff

A living orientation doc for anyone (human or AI) picking up this project. It is the **map and the traps**, not a code dump. Read the actual repo files for detail.

> **Before you build anything:** check the source of truth, not this document's paraphrase of it. Read the actual `.c` file. If the task is "make it like The Two Towers," log into t2tmud.org and look. Two separate sessions have now burned hours building from this doc's wording instead of from the thing itself.

---

## 1. What this is

A private, self-hosted MUD recreating the feel of **The Two Towers** (t2tmud.org), the LPMUD that Jeremy and his friend **Jarrod** played and later wizarded on. It runs the **TMI-2 mudlib** on the modern **FluffOS** driver. It's a **shared sandbox** for the two of them to build in and goof off together, reached through a themed hub called the **Nexus** (branded "Nexus-96: Shattered Sector").

Admin characters: **Trelane** and **Parallax**, both in `(root)`. GitHub: **itsremyinnit/lcars-mud** (currently public).

---

## 2. Infrastructure map

**The VM (`LCARS-MUD`)** — Ubuntu Server, hostname `lcars-mud`, `192.168.4.33` (static DHCP reservation, `lcars.local` A/PTR records). Runs on Hyper-V host **LCARS-SRV** (`192.168.4.41`).

- Isolated by Hyper-V ACLs: can reach the internet and LCARS-SRV/router, but **not** the rest of the LAN. IPv6 disabled.
- SSH only from LCARS-SRV (key-only).

**Ports (public via Eero forward + ufw `limit`):**
- `5555` — plain telnet, **local only**
- `5556` — telnet + TLS (Mudlet: host `mud.mettech.org`, port 5556, "secure")
- `5557` — TLS websocket, the **browser web client** at `https://mud.mettech.org:5557/`

**Service accounts on the VM:**
- `mud` — owns and runs the driver (systemd service `lcars-mud`). Sandboxed. **All lib files should be owned by `mud`.**
- `mudgit` — owns the git repo and runs the 10-minute auto-sync; holds a single-repo GitHub **deploy key**. In the `mud` group.
- `mudbackup` — forced-command SSH key; LCARS-SRV pulls the nightly data archive.
- `mudcert` — forced-command SSH key; LCARS-SRV pushes renewed TLS certs.

**LCARS-SRV side (Windows, scheduled tasks as Administrator):**
- `LCARS-MUD-Backup-Pull` (1:30 AM) → `D:\Backup\LCARS-MUD`, Rclone to OneDrive at 2:00 AM.
- `LCARS-MUD-Cert-Renew` (3:00 AM) — Posh-ACME, GoDaddy DNS validation, deploys to the VM.
- `LCARS-GoDaddy-DDNS` — keeps `vpn.mettech.org` (and via CNAME `mud.mettech.org`) pointed at home.

**On the VM:**
- Driver binary: `/opt/mud/bin/driver` (root-owned, `mud`-group, 750)
- Mudlib: `/opt/mud/lib`
- Config: `/opt/mud/etc/config.tmi2`
- TLS certs: `/opt/mud/etc/tls/` (ACL-granted read for `mud`; see §4)
- Compiled binaries: `/opt/mud/lib/data/binaries` (see §8)
- FluffOS source: `~/src/fluffos` under `lcars_admin`; recipe in `~/src/fluffos-build-notes.txt`
- Weekly maintenance restart: Sundays 4:00 AM Pacific. **This is how renewed certs get loaded.**

---

## 2a. Helper commands — USE THESE

Three wrappers on the VM, plus PowerShell shortcuts on LCARS-SRV. They exist so nobody has to reconstruct the git invocation from memory again.

- `mud-git <subcommand>` — git against the split layout (see §2b)
- `mud-commit "message"` — stops the sync timer, **normalises file ownership**, adds, commits, fetches, rebases, pushes, restarts the timer
- `mud-restart` — pre-flights the boot-only files (§3a), prompts, restarts, verifies ports/cert/NRestarts

On LCARS-SRV, in `$PROFILE`: `mud` (ssh in), `mudlog` (last 50 driver log lines), `mudstat` (service states).

**These scripts live in `/usr/local/bin`, which is outside the repo and outside the nightly backup.** If the VM is rebuilt they are gone. Copies belong in `lib/docs/tools/`.

---

## 2b. Git layout — READ THIS BEFORE ANY GIT COMMAND

**This is a split layout. There is no `.git` directory anywhere in the work tree.**

- **Bare repo:** `/var/lib/mudgit/lcars-mud.git`
- **Work tree:** `/opt/mud` (the parent of `lib/`, **not** `lib/` itself)
- **Runs as:** `mudgit`
- **Remote:** `origin` is GitHub directly over SSH. One hop, no mirror.

`git -C /opt/mud <anything>` fails with "not a git repository." That is expected.

**Symptom of getting the work tree wrong:** passing `--work-tree=/opt/mud/lib` does **not** error. Git looks for `lib/...` underneath `lib/`, finds nothing, and reports **every tracked file as deleted** while listing the real directories as untracked. Hundreds of ` D ` lines means the work-tree argument is wrong, not that the lib was wiped.

Use `mud-git`. If you must do it by hand:

```bash
sudo -u mudgit sh -c 'cd /opt/mud && git --git-dir=/var/lib/mudgit/lcars-mud.git --work-tree=/opt/mud <subcommand>'
```

Running as `mudgit` from `/` emits harmless `.mailmap` and `.gitattributes` permission warnings. `cd /opt/mud` first and they go away.

**Ignore rules live outside the repo.** There is no `.gitignore` in the checkout. Exclusions (driver binary, `*.o` saves, logs, tmp, TLS, compiled binaries) are in `/var/lib/mudgit/lcars-mud.git/info/exclude`, invisible on GitHub. The sync does `add -A` over the whole work tree, so **anything new that writes runtime output needs a rule added there first**, or it gets pushed to a public repo.

**Auto-sync:** `/usr/local/sbin/lcars-mud-sync` runs as `mudgit` every 10 minutes. It commits as "In-game edits \<timestamp\>", then fetch / rebase / push. It will usually beat you to a commit, which is why `mud-commit` stops the timer first.

**Never `reset --hard`** here. It discards uncommitted in-game `ed` edits that exist only in the nightly backup.

---

## 3. How to work on it

- **Two shells:** PowerShell on LCARS-SRV and a bash SSH session on the VM. Label every command block with where it runs.
- **Editing LPC:** change the file on disk, then `update /path/to/file` **in-game**. Warnings are fine; `error:` is not. Errors also go to `/u/<u>/<user>/log`.
- **`update` is safe on an occupied room.** `_update.c` moves users to the void, reloads, and moves them back.
- **Changing an inherited base does nothing on its own.** After editing `/d/Avakuma/std/avakuma_room.c`, run `dupdate /d/Avakuma/<area>` for each area.
- **`update` does NOT change existing clones.** This has bitten us three times with the ring: after editing `calenmir.c`, anyone already carrying one keeps the old program and old properties until they **relog**. Symptom: a new property reads as 0 on a ring that visibly exists.
- **Restart vs update:** most changes load with `update`. Boot-only: the master's `groups`/`access`, the config file, the preload list. Use `mud-restart`.
- **Player saves survive restarts.** Runtime data (`.o`, logs) is **not** in Git. Nightly backup only.
- **Colors:** `%^COLOR%^` codes (names in `/adm/daemons/terminal.c`), translated per-client for a logged-in player. Pre-login text (the welcome screen) has no player to translate for, so it uses **raw ANSI escapes**.
- **Room descriptions are stored pre-wrapped** via `@EndText` heredocs at ~72 columns. Nothing re-wraps at output time.

### In-game command quirks
- `do cmd1, cmd2, cmd3` runs a sequence. Over roughly 20 commands it prints "Large command count! Forcing 'brief' mode", which suppresses room descriptions.
- **`do` cannot wrap `call`.** It works by forcing, and `call` counts as an illegal force attempt. Type `call` on its own line.
- `do` runs every command unconditionally. One failed movement and the rest execute in the wrong room. Keep routes short.

---

## 3a. Boot integrity — what a restart can silently break

`groups` and `access` are **not** parsed at `epilog()`. They load lazily on the first `valid_read`/`valid_write`, and on failure `master.c` calls `shutdown()` directly. A parse failure looks like the service dying a second into boot with systemd restarting it in a loop. Check `systemctl is-active` after 15 seconds, not immediately.

**The silent one.** `groups.c` verifies each bare username has a save file at `/data/std/connection/<first-letter>/<name>.o`. Missing, and the parser prints "Continuing parse" and **drops the name**. `(root)` feeds `admin`, `adminaccess`, `conveners`, `socket`, `www`, and `nexus`. If a root member's `.o` is absent at boot, the MUD comes up healthy, serves TLS, and has **no admin**. Because `.o` files are not in Git, a rebuild from the repo alone produces exactly that. Restore runtime data from the nightly backup.

`Backbone` and `News` failing that check is **normal** (pseudo-uids, no save).

**Adding an admin** means adding the name to `(root)` in `/adm/etc/groups`, colon-separated, *after* that character exists and has a save file, and then restarting with the pre-flight. Keep more than one name in `(root)` as insurance.

Undefined groups in `access` (`tmi`, `adm`, `lima`, `teachers`, `spells`) are dead entries, not errors. Related: `check_access()` hands any `/d/<Domain>/...` path to that domain's `d_master` before consulting the access mapping, so `(/d/Nexus)` lines in `access` never fire. Edit `d_master.c` for domain permissions.

---

## 4. FluffOS-vs-1990s-mudlib gotchas (the expensive ones)

- **`static` is gone.** Old `static` on a variable → `nosave`; on a function → `protected`. `private static` → just `private`.
- **`export_uid()` is a no-op if the target already has an euid.** Have the object `seteuid(0)` on itself first.
- **Variable declarations must be at the top of a function.** Mid-block gives confusing `Left argument of -> is not a class` errors.
- **`RNAME` etc. are macros**, not properties.
- **Virtual objects:** TMI-2's `virtual_d` routing expects paths **without** a leading slash; FluffOS passes them **with** one.
- **`external_start` / FFI are disabled.** `valid_ffi()` returns 0; `PACKAGE_EXTERNAL=OFF`; noexec sandbox.
- **`PACKAGE_PCRE=OFF`.**
- **The prompt is NOT set via the driver.** `set_prompt()` is a stub. The driver calls the interactive's `write_prompt()`. Ours lives in `/std/user/tsh.c` → `update_prompt()` in `/std/user.c`, reading the **`myprompt`** env var.
- **`%^RESET%^` gets appended** to some env vars by `_set.c`; strip it when reading back.
- **A domain needs a `d_master.c`** before its `[Domain]` entry goes in `groups`, or the parse fails and the master shuts the MUD down at boot.
- **`test -r` cannot see ACL-granted permissions.** `/opt/mud/etc/tls/` grants `mud` by ACL, and `sudo -u mud test -r` returns false anyway. Verify with a real read (`sudo -u mud head -c 32 <file>`). A false negative here sends you chasing a cert failure that does not exist.
- **Unsudoed commands after sudoed ones.** `lcars_admin` cannot descend into `/opt/mud/lib` or `/opt/mud/etc`. A glob expands *before* sudo runs. Put the whole thing under `sudo`.
- **Inherited programs are compiled into the child, all the way down.**
  Updating a base does nothing for anything that inherits it until the
  children are recompiled too. `/std/user.c` inherits `LIVING` inherits
  `/std/body.c`, so `update /std/body` left every player on the old body
  code and a new function on it reported as "does not contain". Update the
  whole chain: `update /std/body, update /std/living, update /std/user`,
  then relog.
- **Two mudlib bases that share an ancestor cannot be combined.** FluffOS
  does not share the duplicate: the second copy tries to redefine the
  shared ancestor's `nomask` property functions (`set`, `query`, `_set`,
  `_query`, `query_temp`) and the compile fails with "Illegal to redefine
  nomask function". Hit twice so far: `AVAKUMA_ROOM` + `/std/shop` (both
  ROOM), and `CONTAINER` + `ARMOR` (both OBJECT). The workaround both
  times was to inherit one and add the other's verbs by hand.
- **`/std/body.c` and `/std/user.c` are load-bearing for login.** Breaking
  either locks every player out including you, and there is no in-game
  route back: it takes a `checkout` on the VM and a `mud-restart`. Commit
  before editing them, and test with `update` while still logged in, so a
  failure leaves your running program intact.
- **Function definitions must be at file scope.** Inserting them inside an
  existing function body gives `syntax error, unexpected '('` pointing at
  your new function. This is how `/std/body.c` got broken: a patch
  anchored on a line that happened to be inside `init_setup()`.
- **A command refusal must `write()` and `return 1`, not `notify_fail()`
  and `return 0`.** Returning 0 means "not a match, keep looking", so the
  parser exhausts its options and reports a parse failure ("Put what in
  what?") while your message is discarded.
- **An object cannot destroy an object it does not own.**
  `/adm/simul_efun/overrides.c` permits `destruct()` only when the
  caller's euid matches the target's, or the caller is root or an admin.
  And `valid_seteuid()` only lets an object claim an euid it already owns,
  so a domain object cannot elevate itself out of the problem. Anything
  that needs to destroy across uids (a trash can, a cleanup routine) has
  to go through a daemon under `/adm`, which carries the root uid. See
  `/adm/daemons/disposal_d.c`.
- **Two bases that both inherit ROOM cannot be combined.** FluffOS does
  not share the duplicate; the second copy tries to redefine ROOM's
  `nomask` property functions and the compile fails. This is why Avakuma's
  shops cannot inherit its room base.
- **`OBJECT` defines no `create()`.** An object inheriting it must not
  call `::create()`. `CONTAINER`, `ARMOR` and `WEAPON` are fine.
- **NPC and room ids are `set("id", ({ ... }))`,** not `set_id()`, which
  does not exist here.
- **`sudo -u mudgit tee` produces `644 mudgit:mud`.** Everything else in the lib is `664 mud:mud`. Files written that way need `chown mud:mud` and `chmod g+w`, or the driver cannot write into a domain's `data/`. `mud-commit` normalises this automatically.
- **Patch scripts need an idempotency guard, not just a uniqueness assert.** If the replacement text contains the anchor, re-running the block stacks another copy and the assert still passes. This produced three copies of a function in `calenmir.c` (fatal) and three in `user.c` (harmless but wrong). Every patch script should check whether it has already applied and skip.

---

## 5. What's built

### The Nexus (`/d/Nexus/`)
Wizards arrive at the **Threshold** on login; players still start in the TMI-2 quad.

- **Rooms:** a north-south spine (Threshold → Grand Concourse → Commons → Crafthall → Hall of Banners → Concourse of Arches → Far Concourse) with side rooms. Base: `/d/Nexus/std/nexus_room.c`.
- **Arches:** ring-gated exits via `pre_exit_func/<dir>`, enforced on `go`, `sneak` and ghost movement alike. `add_arch(dir, dest, sigil, sealed, passage)` — the optional fifth argument is custom passage text.
- **Sealed arches appear in the exits line on purpose.** Accepted as flavor; do not "fix" it.
- **The Towers Arch (west from the Concourse of Arches) now opens onto Framsburg**, into `/d/Avakuma/framsburg/pub`, with an inky-portal passage. **One-way by design:** the pub has no arch on its side. The ring's `recall` is the way back. This also leaves Framsburg usable as a standalone start point.
- **Calenmîr, the focus ring** (`/d/Nexus/obj/calenmir.c`): bound to its bearer, keyed with a per-owner rune, has a voice (`ask ring about ...`). **Does not autoload** — the login re-forge is the single source. On quit it announces itself and destructs (see §4 re: clones).
- **`recall`** (`/d/Nexus/adm/recall_d.c`): from anywhere outside the Nexus, ~15 seconds of narration spent in the Between, ending at the Threshold. Refuses inside the Nexus.
- **Willpower gate:** wizard-folder commands require the worn ring. Admins exempt.
- **Ring ceremony, quarters, legend/finger/story/register, banish/unbanish** — see the files under `/d/Nexus/adm/`.
- **Hearthside notice board** at `/d/Nexus/boards/hearth_board.c`.
- **Welcome screen** (`/adm/news/welcome`): raw-ANSI Space Needle, Rainier, and a Nexus-style rift. **`NO_LOGIN_PAUSE`** is defined in `config.h`, so there is no "[Press ENTER to continue]".

### Avakuma (`/d/Avakuma/`) — the Tolkien domain

> **See `docs/AVAKUMA.md` for all of it.** The room, NPC and shop bases
> and why they differ, spawning, wandering, dialogue, both shops, the
> objects, the wanted poster, the jail and the corps hook, what is
> deferred, and every mudlib change made for it.

A standalone domain, deliberately not under `/d/Nexus/`, holding the
reconstruction of Framsburg, its guard barracks, the Sheriff's Guild and
the orc newbie dungeon. 38 rooms with finished prose, 26 NPCs, two working
shops. Reached from the Nexus through the Towers Arch, which is one-way;
the ring's `recall` is the way back.

### Hand slots

TMI-2 tracked `weapon1`/`weapon2` and nothing else, so a player could
carry any number of open drinks and torches. `/std/body.c` now has:

- `hands_used()` / `hands_free()`, out of `MAX_HANDS` 2.
- An object declares `set("hands", n)` if it must be held. A wielded
  weapon takes one, or two if it sets `nosecond`. A worn shield takes one.
  Everything else is carried freely, which matches T2T: only the drinks
  and the torch ever showed as "in hands".
- `receive_object()` refuses anything needing a hand when there is not one
  to spare. Only objects declaring `hands` are checked, so nothing else
  changes.
- `/cmds/std/_hands.c` reports what is in each.

**Anything new that must be held needs `set("hands", 1)` on it.** Nothing
infers it.

Related: `/std/container.c` honours `no_container` on an object that
cannot sensibly be packed away, for open-topped things that would spill.
The Framsburg beer and whiskey set it; the lidded stew bowl does not,
which is why stew can be carried off and the drinks cannot.

**Not modelled:** drunkenness. T2T tracks it, garbles your `score`
readout while you are drunk, and prints "You can see straight again" and
"The world finally stops spinning" as it wears off.

### Rings and corps

`/d/Nexus/adm/ring_d.c` answers `query_worn_corps(who)` and `wearing_corps(who, corps)`. Rings declare a `corps` property; Calenmîr sets `"green"`. NPCs react to the *corps*, never to a named object, so a new corps is a data change rather than a code change. The guild guard is the first consumer: green gets a wordless deference, anything else gets warned once and then jailed.

**Wizard powers stay keyed to Calenmîr specifically**, in `cmd_hook` in `/std/user.c`. The intent is that other corps confer no wizardry at all. Do not widen that check to "wearing a ring."

### Board dates

`get_time()` in `/std/board/bboard.c` was changed from the stock `"Wed Jun 30"` to `MM/DD/YY HH:MM`, matching T2T. Affects every board.

The **wanted poster** (`/d/Avakuma/guild/boards/wanted_poster.c`) is seeded with the twelve notes that stood on the original board from 2011 to 2026, with their real posters and dates, `locked` so the archiver never ages them off. The seed runs only when the board comes up empty. The `*` beside each note in the listing marks it locked; that is the visible difference from T2T and the price of permanence.

---

## 6. Deferred, and honest about it

- **Shops:** the armoury wagon, the guild shop, and Meryne's food-and-drink menu in the Framsburg kitchen. All three have readable signs or menus already; none of them trade.
- **The dart game** in the guild bar. A real playable game in the original with a persistent scoreboard. Ours preserves the original board verbatim as a plaque under `read scoreboard`, twenty names and their throw counts. A live game would want its own board starting empty.
- **NPCs.** Roughly thirty across the three areas, none built. Partially catalogued: the intimidating guard, large and gruff soldiers, the little boy, the cute little girl, the injured soldiers, the tired nurse (a **functional healer** in the original — heals and revives), the father, Meryne the mother, the men's leader, Malcolm and Belinda the shopkeepers, Tarlyn the trainer, Eomon, Dano, Dalin, Dorgy, the orcs and their chieftain. **Clark**, the roughly-dressed sheriff in the Guildmaster's office, is a weathered elf officer working a problem in a dead man's office; build him early.
- **Functional objects** that are not scenery: the trash cans (destroy on insert), the supply room chest and badges, the scribe's bundle on the Guildmaster's desk.
- **The Framsburg barracks locked south door.** Answers neither knock nor bang.
- **The river and the ford.** The Anduin runs southwest and southeast of the town entrance and the ford lies south. Described but not modelled; no water exits, no swim daemon. The entrance's south is sealed as a future expansion; east and west out of town are omitted entirely.
- **The Lobby** beyond the Bell Arch, still a placeholder, waiting on high school photos.
- **Bringing Jarrod in.** `mailreg jarrod`, a starter password delivered separately, a connection note, then `makewiz jarrod`. Note that **no `builders` group exists yet** — `(nexus)` in `groups` resolves to `(admin)` only, so adding him there would make him an admin rather than a builder. Creating a real `builders` group means editing `groups`, which is boot-critical.

---

## 7. Checkpoints & safety

Hyper-V checkpoints mark milestones. Everything is committed to GitHub, backed up nightly to OneDrive, and runs as a self-restarting service. It is always safe to stop.

**Morning health check:** `mudstat` from LCARS-SRV, and confirm the backup-pull and cert-renew tasks last ran with result 0.

**OS updates:** the driver is built from source against system libraries, so a library bump can leave it unable to start, which you would otherwise discover at the Sunday restart. Apply updates, then run `mud-restart` the same day. `unattended-upgrades` handles security patches with `Automatic-Reboot "false"`; kernels and everything else stay manual.

---

## 8. Compiled binaries

`/opt/mud/lib/data/binaries` is runtime output (per `save binaries directory` in `config.tmi2`), owned by `mud`, excluded from Git via `lib/data/binaries/` in the bare repo's `info/exclude`. If the directory goes missing, FluffOS silently recompiles the entire lib at every boot. Slow, not an error, and nothing will tell you.
