#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include <string>

namespace Keyboard {
	struct Key {
//		constexpr Key() : raw(0x00) {}
		constexpr Key() :
			is_print(false), alt(false), ctrl(false), shift(false), fn(false), extend(false), c(0x00) {}
		constexpr Key(bool is_print, bool alt, bool ctrl, bool shift, bool fn, bool extend, char c) : 
			is_print(is_print), alt(alt), ctrl(ctrl), shift(shift), fn(fn), extend(extend), c(c){}
		constexpr operator int() const { return (is_print<<12 | alt <<11 | ctrl<<10 | fn<<9 | extend<<8 | c); }

		struct {
			bool is_print;
			bool alt, ctrl, shift;
			bool fn;
			bool extend;
			char c;
		};
	};

	namespace ext {
		enum : char {
			Up = 0x01,
			Down,
			Right,
			Left,
			Insert,
			Delete,
			PgUp,
			PgDown,
			End,
			Home,
		};
	}

	constexpr Key gen_extkey(char c){
		return Key(false, false, false, false, false, true, c);
	}
	Key read_key();
	std::string key2str(const Key &k);

	//			is_print, alt,   ctrl,  shift, fn,    extend, c
	constexpr Key Tab	= Key(true,  false, false, false, false, false, 0x09);
	constexpr Key Enter	= Key(false, false, false, false, false, false, 0x0d);
	constexpr Key BackSpace	= Key(false, false, false, false, false, false, 0x7f);
	constexpr Key Esc	= Key(false, false, false, false, false, false, 0x1b);
	constexpr Key Up	= gen_extkey(ext::Up);
	constexpr Key Down	= gen_extkey(ext::Down);
	constexpr Key Right	= gen_extkey(ext::Right);
	constexpr Key Left	= gen_extkey(ext::Left);
	constexpr Key Insert	= gen_extkey(ext::Insert);
	constexpr Key Delete	= gen_extkey(ext::Delete);
	constexpr Key PgUp	= gen_extkey(ext::PgUp);
	constexpr Key PgDown	= gen_extkey(ext::PgDown);
	constexpr Key End	= gen_extkey(ext::End);
	constexpr Key Home	= gen_extkey(ext::Home);
}

#endif
