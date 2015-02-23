##Thorrent
node.js bindings for rasterbar's libbtorrent (www.libtorrent.org)

##Example
```
var libTorrent = require("../index");
var session = new libTorrent.session();

session.start_dht();
session.listen_on([6881, 6889]);

var magnet = "magnet:?xt=urn:btih:ae73e63a3341868e68af4bf33c4733905755aa81&dn=Suits.S04E14.HDTV.x264-ASAP%5Bettv%5D&tr=udp%3A%2F%2Fopen.demonii.com%3A1337&tr=udp%3A%2F%2Ftracker.coppersurfer.tk%3A6969&tr=udp%3A%2F%2Ftracker.leechers-paradise.org%3A6969&tr=udp%3A%2F%2Fexodus.desync.com%3A6969";

var torrentHandler = session.add_torrent({
    url: magnet,
    save_path: "./test_magnet",
    seed_mode:0
});
main = function() {

    var status = torrentHandler.status();
    console.log("" + (status.progress * 100) + " complete (down: " + (status.download_rate / 1000) + " kb/s | up: " + (status.upload_rate / 1000) + " kB/s | peers: " + status.num_peers + ")");
    var alerts = session.pop_alerts();
    if( alerts.length ) console.log(alerts);
    return setTimeout(main, 500);
};

main();
```