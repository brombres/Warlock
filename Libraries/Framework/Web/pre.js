// pre.js - prepended to index.js; runs before the Emscripten runtime starts.
//
// Copied from Libraries/Warlock/Libraries/Framework/Web/pre.js into
// Platforms/Web/ - yours to modify; 'rogo deps' will not overwrite it.
//
// Mounts an IndexedDB-backed filesystem (IDBFS) at /persistent so files
// written there survive page reloads. Warlock keeps save state and user data
// under it (see Warlock's Platform/Web.rogue) and flushes it with
// FS.syncfs(false) after saving. Loading it back is registered as a run
// dependency so main() does not start until the data is available.
if (typeof Module.preRun == 'function') Module.preRun = [ Module.preRun ];
Module.preRun = Module.preRun || [];
Module.preRun.push( function() {
  FS.mkdir( '/persistent' );
  FS.mount( IDBFS, {}, '/persistent' );
  addRunDependency( 'warlock-idbfs' );
  FS.syncfs( true, function(err) {
    if (err) console.error( '[Warlock] Failed to load persistent storage: ' + err );
    removeRunDependency( 'warlock-idbfs' );
  });
});
