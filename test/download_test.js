var lt, main, s, th, ti;

lt = require("../index");

s = new lt.session();

s.start_dht();
s.listen_on([6881, 6889]);

var magnet = "magnet:?xt=urn:btih:ae73e63a3341868e68af4bf33c4733905755aa81&dn=Suits.S04E14.HDTV.x264-ASAP%5Bettv%5D&tr=udp%3A%2F%2Fopen.demonii.com%3A1337&tr=udp%3A%2F%2Ftracker.coppersurfer.tk%3A6969&tr=udp%3A%2F%2Ftracker.leechers-paradise.org%3A6969&tr=udp%3A%2F%2Fexodus.desync.com%3A6969";

var data = th = s.add_torrent({
    url: magnet,
    save_path: "./test_magnet",
    seed_mode:0
});
console.log(data);
main = function() {
    var st;
    st = th.status();
    console.log("" + (st.progress * 100) + " complete (down: " + (st.download_rate / 1000) + " kb/s | up: " + (st.upload_rate / 1000) + " kB/s | peers: " + st.num_peers + ")");
    var alerts = s.pop_alerts();
    if( alerts.length ) console.log(alerts);
    return setTimeout(main, 500);
};

//main();