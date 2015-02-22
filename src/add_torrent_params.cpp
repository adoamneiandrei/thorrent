#include <v8.h>
#include <node.h>

#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/torrent_info.hpp>

#include "add_torrent_params.hpp"
#include "torrent_info.hpp"

using namespace v8;
using namespace node;


namespace nodelt {
  libtorrent::add_torrent_params add_torrent_params_from_object(Local<Object> obj) {
    HandleScope scope;
    libtorrent::add_torrent_params p;

    if (obj->Has(String::NewSymbol("ti"))) {
      Local<Object> ti = obj->Get(String::NewSymbol("ti"))->ToObject();
      p.ti = new libtorrent::torrent_info(*TorrentInfoWrap::Unwrap(ti));
    }
    if (obj->Has(String::NewSymbol("trackers"))) {
      Local<Array> trackers = Array::Cast(*obj->Get(String::NewSymbol("trackers")));
      for (uint32_t i = 0, e = trackers->Length(); i < e; ++i)
        p.trackers.push_back(*String::Utf8Value(trackers->Get(i)));
    }
    if (obj->Has(String::NewSymbol("dht_nodes"))) {
      Local<Array> dht_nodes = Array::Cast(*obj->Get(String::NewSymbol("dht_nodes")));
      for (uint32_t i = 0, e = dht_nodes->Length(); i < e; ++i) {
        Local<Array> node = Array::Cast(*dht_nodes->Get(i));
        p.dht_nodes.push_back(std::make_pair(
          *String::Utf8Value(node->Get(0)),
          node->Get(1)->Int32Value()));
      }
    }
    if (obj->Has(String::NewSymbol("info_hash"))) {
      String::AsciiValue info_hash(obj->Get(String::NewSymbol("info_hash"))->ToString());
      libtorrent::from_hex(*info_hash, 40, (char*)&p.info_hash[0]);
    }
    if (obj->Has(String::NewSymbol("name")))
      p.name = std::string(*String::Utf8Value(obj->Get(String::NewSymbol("name"))));
    p.save_path = std::string(*String::Utf8Value(obj->Get(String::NewSymbol("save_path"))));
    if (obj->Has(String::NewSymbol("resume_data"))) {
      String::AsciiValue data(obj->Get(String::NewSymbol("resume_data"))->ToString());
      std::vector<char> rd(data.length());
      std::memcpy(&rd[0], *data, rd.size());
      p.resume_data = rd;
    }
    if (obj->Has(String::NewSymbol("storage_mode")))
      p.storage_mode = (libtorrent::storage_mode_t) obj->Get(String::NewSymbol("storage_mode"))->Int32Value();
    if (obj->Has(String::NewSymbol("file_priorities"))) {
      Local<Array> data = Array::Cast(*obj->Get(String::NewSymbol("file_priorities")));
      std::vector<boost::uint8_t> fp;
      for (uint32_t i = 0, e = data->Length(); i < e; ++i)
        fp.push_back(data->Get(i)->Int32Value());
      p.file_priorities = fp;
    }
    if (obj->Has(String::NewSymbol("trackerid")))
      p.trackerid = std::string(*String::Utf8Value(obj->Get(String::NewSymbol("trackerid"))));
    if (obj->Has(String::NewSymbol("url")))
      p.url = std::string(*String::Utf8Value(obj->Get(String::NewSymbol("url"))));
    if (obj->Has(String::NewSymbol("uuid")))
      p.uuid = std::string(*String::Utf8Value(obj->Get(String::NewSymbol("uuid"))));
    if (obj->Has(String::NewSymbol("source_feed_url")))
      p.source_feed_url = std::string(*String::Utf8Value(obj->Get(String::NewSymbol("source_feed_url"))));
    if (obj->Has(String::NewSymbol("flags")))
      p.flags = obj->Get(String::NewSymbol("flags"))->IntegerValue();

    return p;
  }

  void bind_add_torrent_params(Handle<Object> target) {
    // add_torrent_params::flags_t
    Local<Object> flags_t = Object::New();
    flags_t->Set(String::NewSymbol("flag_seed_mode"),
      Integer::New(libtorrent::add_torrent_params::flag_seed_mode));
    flags_t->Set(String::NewSymbol("flag_override_resume_data"),
      Integer::New(libtorrent::add_torrent_params::flag_override_resume_data));
    flags_t->Set(String::NewSymbol("flag_upload_mode"),
      Integer::New(libtorrent::add_torrent_params::flag_upload_mode));
    flags_t->Set(String::NewSymbol("flag_share_mode"),
      Integer::New(libtorrent::add_torrent_params::flag_share_mode));
    flags_t->Set(String::NewSymbol("flag_apply_ip_filter"),
      Integer::New(libtorrent::add_torrent_params::flag_apply_ip_filter));
    flags_t->Set(String::NewSymbol("flag_paused"),
      Integer::New(libtorrent::add_torrent_params::flag_paused));
    flags_t->Set(String::NewSymbol("flag_auto_managed"),
      Integer::New(libtorrent::add_torrent_params::flag_auto_managed));
    flags_t->Set(String::NewSymbol("flag_duplicate_is_error"),
      Integer::New(libtorrent::add_torrent_params::flag_duplicate_is_error));
    flags_t->Set(String::NewSymbol("flag_merge_resume_trackers"),
      Integer::New(libtorrent::add_torrent_params::flag_merge_resume_trackers));
    flags_t->Set(String::NewSymbol("flag_update_subscribe"),
      Integer::New(libtorrent::add_torrent_params::flag_update_subscribe));
    flags_t->Set(String::NewSymbol("default_flags"),
      Integer::New(libtorrent::add_torrent_params::default_flags));
    target->Set(String::NewSymbol("add_torrent_params_flags_t"), flags_t);
  };
}; // namespace nodelt
