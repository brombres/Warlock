# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What This Is

**Warlock** is a Rogue-based game framework by Brom Bresenham (`github.com/brombres/Warlock`). It is *not* a standalone app — it is consumed as a vendored dependency at `Libraries/Warlock` inside parent game projects (e.g. the surrounding TombSweeper repo). Source files use the `.rogue` extension. The Rogue compiler/runtime is `github.com/brombres/Rogue`.

## Build Workflow — Critical

**`rogo` will refuse to run from inside this folder.** `BuildWarlock.rogue` checks for itself in the cwd and exits with `ERROR: Rogo should not be run directly in the Warlock library folder.` (see `BuildWarlock.rogue` `routine deps`). The intended workflow when modifying Warlock is:

1. Edit files here (`Libraries/Rogue/Warlock/**`, `Libraries/Framework/**`, `Platforms/**`, etc.).
2. `cd` to the parent project (the one that has `Libraries/Warlock` as a subfolder) and run `rogo macos` / `rogo ios` / `rogo android` / `rogo web` from there.

The parent project's top-level `BuildCore.rogue` is a *copy* of `BuildCore.rogue` here — it bootstraps by cloning Warlock into the parent's `Libraries/`, then `BuildWarlock.rogue` (which lives only here) is pulled in as a `#$ DEPENDENCIES` line. `rogo update_buildcore` re-syncs the parent's copy from this one when this file changes.

There is no test suite. Iteration is: edit Rogue → `rogo <platform>` from the parent → run.

## Repo Layout

- `BuildCore.rogue` — bootstrap shim. Copied verbatim into consumer projects on first install (and kept in sync via `rogo update_buildcore`). Adds `BuildWarlock.rogue` as a dependency, defines `Build.resolve_platform`, clones Warlock into `Libraries/Warlock` if missing, and dispatches `rogo deps` / `rogo help`.
- `BuildWarlock.rogue` — the real build implementation. Defines all the `rogo_*` routines (`assets`, `shaders`, `macos`, `ios`, `android`/`and`, `web`, `clean`, `deps`, `build`, `*_open`, `xcode_deep_clean`, …). Each routine has a `# SYNTAX: …` comment that `rogo help` reads.
- `Source/Main.rogue` — starter template. `check_rogue_starter` copies this into a consumer's `Source/Main.rogue` *only if missing*; consumers extend `WarlockController` here.
- `Libraries/Rogue/Warlock/` — the actual framework Rogue source. `Warlock.rogue` is the library root; subfolders are `Audio`, `Control`, `Data`, `Display`, `Entity`, `FileIO`, `Framework`, `Geometry`, `Graphics`, `OS`, `Platform`, `UI`, `Utility`. `Macros.rogue` defines build-time macros.
- `Libraries/Rogue/AssetCompiler/` — separate Rogue program built and run during `rogo assets`. Parses `Assets/AssetConfig.asc` (the `.asc` DSL) into compiled asset bundles.
- `Libraries/Framework/` — native glue: `C/Utilities.[ch]`, `C/stb_image*.h`, `ObjC/RogueInterface.mm`, `ObjC/WarlockInterface.mm` (bridge between Rogue runtime and Apple platforms), and `Assets/Font-System-17.png` (default font).
- `Libraries/Shaders/` — stock bgfx shader pairs (`*-VS.sc` / `*-FS.sc`) and `varying.def.sc`. `rogo shaders` falls back to these when the consumer has no `Assets/Shaders/varying.def.sc`.
- `Platforms/Xcode/`, `Platforms/Android/` (and `Libraries/Framework/Web/` → consumer `Platforms/Web/`) — project templates copied into consumer projects by `check_platform_xcode` / `check_platform_android`. `com.developer.warlockapp` / `com/developer/warlockapp` placeholders are rewritten to the consumer's bundle/package ID. Some files copy *only if missing* (templates the consumer customizes — `Info.plist`, gradle scripts, `JSONData.java`, `Message*.java`, `app/src/main/cpp/**`); the rest are overwritten on every `rogo deps` run.
- Native deps cloned into `Libraries/` on demand by `rogo deps`: `bgfx`, `bimg`, `bx`, `SDL` (pinned to `release-3.2.x`), `spine-runtimes`, `stb`, `libtess2`, `miniaudio`. SDL3 Android lib is downloaded prebuilt (`.aar`) from libsdl-org releases; bgfx is built locally via `build_bgfx`.
- **Web target** (`rogo web`, Emscripten): compiles Rogue with `--target=Web` into `Build/Web/Source/`, builds bgfx for wasm via genie (`build_bgfx_web` → `Libraries/bgfx/.build/wasm/bin/*.a`, no `lib` prefix), then `compile_web` runs `make -C Platforms/Web CONFIG=release|debug`. `Platforms/Web/` (Makefile, `Warlock.cpp` SDL3-callbacks entry point, `MiniAudio.cpp`, `index.html` shell with a progress bar that is byte-accurate during download and then compositor-animated during the app's blocking startup using the startup time saved in `localStorage` on the previous load, `pre.js` which mounts an IDBFS at `/persistent`) is copied *only if missing* from `Libraries/Framework/Web/` by `check_platform_web`, so consumers may edit it. The Makefile builds SDL3 with `emcmake`, compiles spine-cpp/libtess2/miniaudio/Utilities, and links to `Build/Web/App/index.{html,js,wasm,data}` with `Build/Web/Assets` preloaded at `/Assets`. `rogo web_open` serves it with `emrun`. `check_emscripten` prints install instructions if `emcc` is missing. Web-specific runtime gates: `$target("Web")` / `ROGUE_TARGET_WEB` in `BGFX.rogue` (canvas `#canvas`, OpenGL ES renderer), `AssetManager.rogue`, `Spine.rogue` (stdio file read; spine-cpp's default is compiled out on Emscripten), `SDL.rogue` (browser tab hidden/shown and page unload map to suspend/resume), and `Platform/Web.rogue` (`Web` singleton: `application_data_folder`/`user_data_folder` under `/persistent`, `cache_folder` in MEMFS, `sync_persistent_storage` = `FS.syncfs`, called by `WarlockController.save_state`). The Makefile patches `__WARLOCK_TOTAL_BYTES__` in the linked `index.html` so the progress bar knows the download size, and exports `callMain` because `index.html` sets `noInitialRun` and runs `main()` itself once the startup animation is committed to the compositor; `Warlock.cpp` calls `Module.onFirstFrame()` after the first `SDL_AppIterate` so the page can measure startup time and reveal the game.

## Architecture

**Singletons.** `Warlock` (the library entry — `essential singleton` in `Libraries/Rogue/Warlock/Warlock.rogue`) owns `windows`, `actions`, `controller`, and the tick loop entry points called from native code (`tick`, `handle_event`, `configure`, `handle_dock_icon_click`, …). `Window` is also a singleton (`Libraries/Rogue/Warlock/Display/Window.rogue`) — `Window = this` in `init` makes the most recently created window the active one.

**WarlockController.** Subclassed by the consumer in `Source/Main.rogue`. Handles app lifecycle (`handle_app_pause/resume/exit`, `handle_focus_*`, `on_save_state`/`on_restore_state`, `create_default_window`). Configurable via property overrides (`app_name`, `launch_state`, `phone_orientations`, `tablet_orientations`).

**Layered state machine.** Each `Window` owns a `ControlStates` map keyed by layer ID. `Window.define_control_states` registers the default five layers in this draw order: `<background>`, `<scene>`, `<screen>`, `<overlay>`, `<state>` (consumers can augment-replace this method to add layers — TombSweeper inserts a `<message>` layer between `<overlay>` and `<state>`). Each layer has a typed `ControlState` subclass: `BackgroundState`, `SceneState`, `ScreenState`, `OverlayState`, `State`. New `State`s are pushed via `Window.add_state(...)` / `change_state(...)`; the `+` operator chains states sequentially and `|` runs them concurrently (see `ControlState<<>>` global `operator+` / `operator|`). Within a layer, multiple concurrent states are sorted by `display_order`.

**Event dispatch.** `ControlState.handle( e )` walks `concurrent_state` first, then `on(e)`, then attached `UI`, then `dispatch( e )` to the underlying layer. `Window.dispatch( e, underlying_layer(layer_id) )` walks down through layers in reverse, so e.g. an `<overlay>` consuming a tap stops it from reaching `<screen>`.

**Render pipeline.** `Display.modify_view_projection` / `Display.modify_object_transform` signals are wired to `Renderer.flush` / `Renderer.apply_object_transform` in `Warlock.init`. Drawing under bgfx, audio under miniaudio, windowing/input under SDL3 — `compile_rogue` invokes `roguec` with targets `C++,Warlock,<platform>,SDL,bgfx` (plus `ObjC` on Apple).

**AssetManager.** Loaded by `WarlockController.configure`. `Warlock.find_asset( name )`, `find_audio_file`, `find_data_file`, `load_asset_bytes` resolve via the asset manifest written by `rogo_update_asset_manifest`. `application_data_folder` / `cache_folder` / `user_data_folder` are platform-gated with `$target("ObjC")` / `$target("Android")`.

## Conventions

- **Platform-gated code.** Use `$target("iOS")`, `$target("Android")`, `$target("macOS")`, `$target("ObjC")` blocks rather than runtime checks where possible.
- **Augment-replace for customization.** Consumers override behavior by augmenting Warlock classes (`Window`, `WarlockController`, etc.) — see how `Window.define_control_states` is documented "Augment-replace in your app to customize."
- **Rogue source files in `Libraries/Rogue/Warlock/` are auto-discovered** by the build (`compile_rogue` globs `Libraries/Warlock/Libraries/Rogue/**.rogue`). Drop a new `.rogue` file into the appropriate subfolder and `$include` it (or have its containing `Warlock/<Subdir>` be `$include`d from `Warlock.rogue`). Library declarations at the top of each file (`library Warlock`) put symbols in the right namespace.
- **Don't break the `BuildCore.rogue` shim.** The version here is the source of truth; consumers receive copies. Keep it minimal — heavy logic belongs in `BuildWarlock.rogue`.
- **Platform template edits.** Files in `Platforms/Xcode/**` and `Platforms/Android/**` propagate to consumers on `rogo deps`. Files matched by `reclassify_file` patterns (Pods/MiniAudio/Utilities/SDL bridge files; Android cpp/JSONData/Message*.java/gradle*) copy **only if missing** so consumer customizations aren't clobbered; everything else is overwritten on every deps run. When adding a file consumers must be free to edit, add it to a `reclassify_file` call in `check_platform_xcode` / `check_platform_android`.
