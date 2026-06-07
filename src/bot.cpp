#include "../include/bot.h"

// bool Bot::make_play(std::array<tile_place_t, 7> play) {
//         std::vector<struct Word> formed_words = Board::make_play(play);
//
//         if (formed_words.size() == 0) {
//                 return false;
//         }
//
//         for (struct Word word : formed_words) {
//                 std::vector<uint32_t> prefix_allowed_letters{};
//                 std::vector<uint32_t> suffix_allowed_letters{};
//
//                 auto exts = extensions.find(word.word);
//                 if(exts == extensions.end()){
//                         return true;
//                 }
//
//                 for (auto affix : exts->second) {
//                         // add prefix letters as options
//                         size_t prefix_len = affix.first.size();
//                         for (size_t i = 0; i < prefix_len; i++) {
//                                 if (i >= prefix_allowed_letters.size()) {
//                                         prefix_allowed_letters.push_back(0);
//                                 }
//                                 prefix_allowed_letters[i] |=
//                                     (1 << ((affix.first[prefix_len - 1 - i]) -
//                                            64));
//                                 // add prefix letter as option
//                         }
//
//                         size_t suffix_len = affix.second.size();
//                         for (size_t i = 0; i < suffix_len; i++) {
//                                 if (i >= suffix_allowed_letters.size()) {
//                                         suffix_allowed_letters.push_back(0);
//                                 }
//                                 suffix_allowed_letters[i] |=
//                                     (1 << ((affix.second[i]) - 64));
//                                 // add suffix letter as option
//                         }
//                 }
//
//                 coords_t coords = get_xy(word.start);
//                 int x_coord = coords.first;
//                 int y_coord = coords.second;
//
//                 if (word.is_vertical) {
//                         for (size_t i = 0; i < prefix_allowed_letters.size();
//                              i++) {
//                                 y_coord--;
//                                 if (y_coord < 0) {
//                                         break;
//                                 }
//
//                                 position_t pos = get_pos(x_coord, y_coord);
//
//                                 vert_move_opts[pos] &=
//                                     prefix_allowed_letters[i];
//                         }
//
//                         y_coord = coords.second;
//
//                         for (size_t i = 0; i < suffix_allowed_letters.size();
//                              i++) {
//                                 y_coord++;
//                                 if (y_coord >= 15) {
//                                         break;
//                                 }
//
//                                 position_t pos = get_pos(x_coord, y_coord);
//
//                                 vert_move_opts[pos] &=
//                                     suffix_allowed_letters[i];
//                         }
//
//                         y_coord = coords.second;
//                 }
//
//                 else {
//                         for (size_t i = 0; i < prefix_allowed_letters.size();
//                              i++) {
//                                 x_coord--;
//                                 if (x_coord < 0) {
//                                         break;
//                                 }
//
//                                 position_t pos = get_pos(x_coord, y_coord);
//
//                                 vert_move_opts[pos] &=
//                                     prefix_allowed_letters[i];
//                         }
//
//                         x_coord = coords.first;
//
//                         for (size_t i = 0; i < suffix_allowed_letters.size();
//                              i++) {
//                                 x_coord++;
//                                 if (x_coord >= 15) {
//                                         break;
//                                 }
//
//                                 position_t pos = get_pos(x_coord, y_coord);
//
//                                 vert_move_opts[pos] &=
//                                     suffix_allowed_letters[i];
//                         }
//                 }
//         }
//         return true;
// }

// Bot::Bot(std::string wordlist_file_path, std::string trie_file_path,
//          std::string ext_file_path)
//     : Board( trie_file_path, ext_file_path) {
//         for (int i = 0; i < 225; i++) {
//                 horiz_move_opts.push_back(0xFFFFFFFF);
//                 vert_move_opts.push_back(0xFFFFFFFF);
//         }
// }
