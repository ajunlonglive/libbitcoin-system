/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "../test.hpp"
#include <cstring>
#include <stdexcept>
#include <vector>

BOOST_AUTO_TEST_SUITE(unicode_tests)

#ifdef WITH_ICU

// data

BOOST_AUTO_TEST_CASE(unicode__ideographic_space__utf32__expected)
{
    BOOST_REQUIRE_EQUAL(ideographic_space.size(), 3u);
    BOOST_REQUIRE_EQUAL(to_utf32(ideographic_space)[0], 0x00003000);
}

BOOST_AUTO_TEST_CASE(unicode__separators__utf32__expected)
{
    BOOST_REQUIRE_EQUAL(unicode_separators.size(), 17u);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[0])[0], 0x00000020);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[1])[0], 0x000000a0);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[2])[0], 0x00001680);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[3])[0], 0x00002000);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[4])[0], 0x00002001);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[5])[0], 0x00002002);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[6])[0], 0x00002003);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[7])[0], 0x00002004);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[8])[0], 0x00002005);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[9])[0], 0x00002006);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[10])[0], 0x00002007);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[11])[0], 0x00002008);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[12])[0], 0x00002009);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[13])[0], 0x0000200a);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[14])[0], 0x0000202f);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[15])[0], 0x0000205f);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_separators[16])[0], 0x00003000);
}

BOOST_AUTO_TEST_CASE(unicode__whitespace__utf32__expected)
{
    BOOST_REQUIRE_EQUAL(unicode_whitespace.size(), 25u);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[0])[0], 0x00000009);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[1])[0], 0x0000000a);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[2])[0], 0x0000000b);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[3])[0], 0x0000000c);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[4])[0], 0x0000000d);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[5])[0], 0x00000020);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[6])[0], 0x000000a0);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[7])[0], 0x00001680);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[8])[0], 0x00002000);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[9])[0], 0x00002001);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[10])[0], 0x00002002);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[11])[0], 0x00002003);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[12])[0], 0x00002004);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[13])[0], 0x00002005);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[14])[0], 0x00002006);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[15])[0], 0x00002007);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[16])[0], 0x00002008);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[17])[0], 0x00002009);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[18])[0], 0x0000200a);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[19])[0], 0x0000202f);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[20])[0], 0x0000205f);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[21])[0], 0x00003000);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[22])[0], 0x00000085);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[23])[0], 0x00002028);
    BOOST_REQUIRE_EQUAL(to_utf32(unicode_whitespace[24])[0], 0x00002029);
}

// to_lower

BOOST_AUTO_TEST_CASE(unicode__to_lower__empty__empty)
{
    BOOST_REQUIRE(to_lower("").empty());
}

BOOST_AUTO_TEST_CASE(unicode__to_lower__lower_ascii__unchanged)
{
    const std::string lower = "abcdefghijklmnopqrstuvwxyz";
    const std::string expected = "abcdefghijklmnopqrstuvwxyz";
    BOOST_REQUIRE_EQUAL(to_lower(lower), expected);
}

BOOST_AUTO_TEST_CASE(unicode__to_lower__upper_ascii__lowered)
{
    const std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string expected = "abcdefghijklmnopqrstuvwxyz";
    BOOST_REQUIRE_EQUAL(to_lower(upper), expected);
}

BOOST_AUTO_TEST_CASE(unicode__to_lower__mixed_ascii__lowered)
{
    const std::string upper = "AbCdEfGhIjKlMnOpQrStUvWxYz";
    const std::string expected = "abcdefghijklmnopqrstuvwxyz";
    BOOST_REQUIRE_EQUAL(to_lower(upper), expected);
}

// This fails on Windows, may be an invalid case, kinda complex/obscure.
////BOOST_AUTO_TEST_CASE(unicode__to_lower__denormalized_upper__lowered)
////{
////    // unicode.org/reports/tr21/tr21-5.html
////    const std::string upper = "J◌̌◌";
////    const std::string expected = "ǰ◌̱";
////    BOOST_REQUIRE_EQUAL(to_lower(upper), expected);
////}

// to_canonical_composition

BOOST_AUTO_TEST_CASE(unicode__to_canonical_composition__empty__empty)
{
    BOOST_REQUIRE(to_canonical_composition("").empty());
}

// github.com/bitcoin/bips/blob/master/bip-0038.mediawiki
BOOST_AUTO_TEST_CASE(unicode__to_canonical_composition__bip38__expected)
{
    data_chunk original;
    BOOST_REQUIRE(decode_base16(original, "cf92cc8100f0909080f09f92a9"));
    std::string original_string(original.begin(), original.end());

    data_chunk normal;
    BOOST_REQUIRE(decode_base16(normal, "cf9300f0909080f09f92a9"));
    std::string expected_normal_string(normal.begin(), normal.end());

    const auto derived_normal_string = to_canonical_composition(original_string);
    BOOST_REQUIRE_EQUAL(expected_normal_string, derived_normal_string);
}

// to_compatibility_demposition

BOOST_AUTO_TEST_CASE(unicode__to_compatibility_demposition__ideographic_space_sandwich__expected)
{
    const auto ascii_space_sandwich = "space-> <-space";
    const auto ideographic_space_sandwich = "space->　<-space";
    const auto normalized = to_compatibility_demposition(ideographic_space_sandwich);
    BOOST_REQUIRE_EQUAL(normalized.c_str(), ascii_space_sandwich);
}

BOOST_AUTO_TEST_CASE(unicode__to_compatibility_demposition__61cc81__c3a1)
{
    const std::string literal_c3a1 = "á";

    // This is pasted from the the BIP39 encoding:
    //// github.com/bitcoin/bips/blob/master/bip-0039/spanish.txt#L93
    const std::string literal_61cc81 = "á";

    const std::string string_c3a1 = "\xc3\xa1";
    const std::string string_61cc81 = "\x61\xcc\x81";
    BOOST_REQUIRE_EQUAL(string_c3a1, literal_c3a1);
    BOOST_REQUIRE_EQUAL(string_61cc81, literal_61cc81);

    const auto normalized_c3a1 = to_compatibility_demposition(string_c3a1);
    const auto normalized_61cc81 = to_compatibility_demposition(string_61cc81);
    BOOST_REQUIRE_EQUAL(normalized_61cc81.c_str(), string_61cc81);
    BOOST_REQUIRE_EQUAL(normalized_c3a1.c_str(), string_61cc81);
}

// to_unaccented_form

BOOST_AUTO_TEST_CASE(unicode__to_unaccented_form__empty__empty)
{
    BOOST_REQUIRE(to_unaccented_form("").empty());
}

BOOST_AUTO_TEST_CASE(unicode__to_unaccented_form__ascii_only__unchanged)
{
    const std::u32string ascii{ 0x42, 0x43 };
    const std::string expected{ 0x42, 0x43 };
    BOOST_REQUIRE_EQUAL(to_unaccented_form(to_utf8(ascii)), expected);
}

BOOST_AUTO_TEST_CASE(unicode__to_unaccented_form__circumflex_accent_only__empty)
{
    const std::u32string circumflex_accent{ 0x0000005e };
    BOOST_REQUIRE(to_unaccented_form(to_utf8(circumflex_accent)).empty());
}

BOOST_AUTO_TEST_CASE(unicode__to_unaccented_form__bassa_vah_tones_only__empty)
{
    const std::u32string bassa_vah{ 0x00016af1, 0x00016af2, 0x00016af3 };
    BOOST_REQUIRE(to_unaccented_form(to_utf8(bassa_vah)).empty());
}

BOOST_AUTO_TEST_CASE(unicode__to_unaccented_form__bassa_vah_tones_ascii_sandwich__stripped)
{
    const std::string expected{ 0x42, 0x43 };
    const std::u32string bassa_vah{ 0x42, 0x00016af1, 0x00016af2, 0x00016af3, 0x43 };
    BOOST_REQUIRE_EQUAL(to_unaccented_form(to_utf8(bassa_vah)), expected);
}

BOOST_AUTO_TEST_CASE(unicode__to_unaccented_form__circumflex_accent_and_bassa_vah_tones_and_ascii_mix__stripped)
{
    const std::string expected{ 0x42, 0x43, 0x44 };
    const std::u32string bassa_vah{ 0x00016af1, 0x42, 0x43, 0x0000005e, 0x00016af2, 0x44, 0x00016af3 };
    BOOST_REQUIRE_EQUAL(to_unaccented_form(to_utf8(bassa_vah)), expected);
}

// to_compressed_cjk_form

BOOST_AUTO_TEST_CASE(unicode__to_compressed_cjk_form__empty__empty)
{
    BOOST_REQUIRE(to_compressed_cjk_form("").empty());
}

BOOST_AUTO_TEST_CASE(unicode__to_compressed_cjk_form__ascii_with_spaces__unchanged)
{
    const auto value = " foo  bar  baz ";
    const auto result = to_compressed_cjk_form(value);
    BOOST_REQUIRE_EQUAL(result.c_str(), value);
}

BOOST_AUTO_TEST_CASE(unicode__to_compressed_cjk__cjk_unified_ideograph_only__unchanged)
{
    const std::u32string cjk_unified_ideograph{ 0x00004e00 };
    const auto utf8 = to_utf8(cjk_unified_ideograph);
    BOOST_REQUIRE_EQUAL(to_compressed_cjk_form(utf8), utf8);
}

BOOST_AUTO_TEST_CASE(unicode__to_compressed_cjk__cjk_unified_ideograph_sandwich__stripped)
{
    const std::u32string expected{ 0x00004e00, 0x00004e00 };
    const std::u32string cjk_unified_ideograph_sandwich{ 0x00004e00, 0x20, 0x00004e00 };
    const auto utf8 = to_utf8(cjk_unified_ideograph_sandwich);
    BOOST_REQUIRE_EQUAL(to_compressed_cjk_form(utf8), to_utf8(expected));
}

BOOST_AUTO_TEST_CASE(unicode__to_compressed_cjk__cjk_unified_ideograph_right__unchanged)
{
    const std::u32string expected{ 0x20, 0x00004e00, 0x00004e00 };
    const std::u32string cjk_unified_ideograph_right{ 0x20, 0x00004e00, 0x00004e00 };
    const auto utf8 = to_utf8(cjk_unified_ideograph_right);
    BOOST_REQUIRE_EQUAL(to_compressed_cjk_form(utf8), to_utf8(expected));
}

BOOST_AUTO_TEST_CASE(unicode__to_compressed_cjk__cjk_unified_ideograph_left__unchanged)
{
    const std::u32string expected{ 0x00004e00, 0x00004e00, 0x20 };
    const std::u32string cjk_unified_ideograph_left{ 0x00004e00, 0x00004e00, 0x20 };
    const auto utf8 = to_utf8(cjk_unified_ideograph_left);
    BOOST_REQUIRE_EQUAL(to_compressed_cjk_form(utf8), to_utf8(expected));
}

BOOST_AUTO_TEST_CASE(unicode__to_compressed_cjk__cjk_unified_ideograph_both__unchanged)
{
    const std::u32string expected{ 0x20, 0x00004e00, 0x00004e00, 0x20 };
    const std::u32string cjk_unified_ideograph_both{ 0x20, 0x00004e00, 0x00004e00, 0x20 };
    const auto utf8 = to_utf8(cjk_unified_ideograph_both);
    BOOST_REQUIRE_EQUAL(to_compressed_cjk_form(utf8), to_utf8(expected));
}

BOOST_AUTO_TEST_CASE(unicode__to_compressed_cjk__cjk_unified_ideograph_all__middle_stripped)
{
    const std::u32string expected{ 0x20, 0x00004e00, 0x00004e00, 0x20 };
    const std::u32string cjk_unified_ideograph_all{ 0x20, 0x00004e00, 0x0c, 0x00004e00, 0x20 };
    const auto utf8 = to_utf8(cjk_unified_ideograph_all);
    BOOST_REQUIRE_EQUAL(to_compressed_cjk_form(utf8), to_utf8(expected));
}

BOOST_AUTO_TEST_CASE(unicode__to_compressed_cjk__single_and_double_contained_whitespace__single_stripped)
{
    const std::u32string expected
    {
        0x20, 0x00004e00, 0x00004e00, 0x20,
        0x20, 0x00004e00, 0x00004e00, 0x20,
        0x20, 0x00004e00, 0x00004e00, 0x20,
        0x20, 0x00004e00, 0x00004e00, 0x20,
        0x20, 0x00004e00, 0x00004e00, 0x20,
        0x20, 0x00004e00, 0x00004e00, 0x20
    };
    const std::u32string single_and_double_contained
    {
        0x20, 0x00004e00, 0x20, 0x00004e00, 0x20,
        0x20, 0x00004e00, 0x0c, 0x00004e00, 0x20,
        0x20, 0x00004e00, 0x0a, 0x00004e00, 0x20,
        0x20, 0x00004e00, 0x0d, 0x00004e00, 0x20,
        0x20, 0x00004e00, 0x09, 0x00004e00, 0x20,
        0x20, 0x00004e00, 0x0b, 0x00004e00, 0x20
    };
    const auto utf8 = to_utf8(single_and_double_contained);
    BOOST_REQUIRE_EQUAL(to_compressed_cjk_form(utf8), to_utf8(expected));
}

BOOST_AUTO_TEST_CASE(unicode__to_compressed_cjk__alternating_single_contained_whitespace__contained_stripped)
{
    const std::u32string expected
    {
        0x20, 
        0x00004e00, 0x00004e00,
        0x00004e00, 0x00004e00,
        0x00004e00, 0x00004e00,
        0x00004e00, 0x00004e00,
        0x00004e00, 0x00004e00,
        0x00004e00, 0x00004e00,
        0x20
    };
    const std::u32string alternating_single_contained
    {
        0x20, 0x00004e00, 0x20, 0x00004e00,
        0x20, 0x00004e00, 0x20, 0x00004e00,
        0x20, 0x00004e00, 0x20, 0x00004e00,
        0x20, 0x00004e00, 0x20, 0x00004e00,
        0x20, 0x00004e00, 0x20, 0x00004e00,
        0x20, 0x00004e00, 0x20, 0x00004e00,
        0x20
    };
    const auto utf8 = to_utf8(alternating_single_contained);
    BOOST_REQUIRE_EQUAL(to_compressed_cjk_form(utf8), to_utf8(expected));
}

#endif

// to_utf8 (u32string)

// Use of U is not recommended as it will only work for ascii when
// the source file does not have a BOM (which we avoid for other reasons).
BOOST_AUTO_TEST_CASE(unicode__to_utf8_32__empty__empty)
{
    BOOST_REQUIRE(to_utf8(U"").empty());
}

// Use of U is not recommended as it will only work for ascii when
// the source file does not have a BOM (which we avoid for other reasons).
BOOST_AUTO_TEST_CASE(unicode__to_utf8_32__ascii__expected)
{
    const auto utf8_ascii = "ascii";
    const auto utf32_ascii = U"ascii";
    const auto converted = to_utf8(utf32_ascii);
    BOOST_REQUIRE_EQUAL(converted, utf8_ascii);
}

// to_utf8 (wstring)

// Use of L is not recommended as it will only work for ascii when
// the source file does not have a BOM (which we avoid for other reasons).
BOOST_AUTO_TEST_CASE(unicode__to_utf8_16__empty__empty)
{
    BOOST_REQUIRE(to_utf8(L"").empty());
}

// Use of L is not recommended as it will only work for ascii when
// the source file does not have a BOM (which we avoid for other reasons).
BOOST_AUTO_TEST_CASE(unicode__to_utf8_16__ascii__expected)
{
    const auto utf8_ascii = "ascii";
    const auto utf16_ascii = L"ascii";
    const auto converted = to_utf8(utf16_ascii);
    BOOST_REQUIRE_EQUAL(converted, utf8_ascii);
}

// to_utf16 (string)

BOOST_AUTO_TEST_CASE(unicode__to_utf16__empty__empty)
{
    BOOST_REQUIRE(to_utf16("").empty());
}

// Use of L is not recommended as it will only work for ascii when
// the source file does not have a BOM (which we avoid for other reasons).
BOOST_AUTO_TEST_CASE(unicode__to_utf16__ascii__expected)
{
    const auto utf8_ascii = "ascii";
    const auto utf16_ascii = L"ascii";
    const auto converted = to_utf16(utf8_ascii);
    BOOST_REQUIRE_EQUAL(converted.c_str(), utf16_ascii);
}

// to_utf32 (string)

BOOST_AUTO_TEST_CASE(unicode__to_utf32__empty__empty)
{
    BOOST_REQUIRE(to_utf32("").empty());
}

// Use of U is not recommended as it will only work for ascii when
// the source file does not have a BOM (which we avoid for other reasons).
BOOST_AUTO_TEST_CASE(unicode__to_utf32__ascii__expected)
{
    const auto utf8_ascii = "ascii";
    const auto utf32_ascii = U"ascii";
    const auto converted = to_utf8(utf32_ascii);
    BOOST_REQUIRE_EQUAL(converted, utf8_ascii);
}

// to_utf16 (string) / to_utf8 (wstring)

BOOST_AUTO_TEST_CASE(unicode__to_utf16__to_utf8_ascii_round_trip__unchanged)
{
    const auto utf8_ascii = "ascii";
    const auto converted = to_utf8(to_utf16(utf8_ascii));
    BOOST_REQUIRE_EQUAL(converted, utf8_ascii);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf16__to_utf8_japanese_round_trip__unchanged)
{
    const auto utf8 = "テスト";
    const auto converted = to_utf8(to_utf16(utf8));
    BOOST_REQUIRE_EQUAL(converted, utf8);
}

// Use of L is not recommended as it will only work for ascii when
// the source file does not have a BOM (which we avoid for other reasons).
BOOST_AUTO_TEST_CASE(unicode__to_utf16__round_trip__narraow_and_wide_japanese_literals__expected)
{
    const auto utf8 = "テスト";
    const auto utf16 = L"テスト";

    const auto widened = to_utf16(utf8);
    const auto narrowed = to_utf8(utf16);

#ifdef _MSC_VER
    // This confirms that the L prefix does not work with non-ascii text when
    // the source file does not have a BOM (which we avoid for other reasons).
    BOOST_REQUIRE_NE(widened.c_str(), utf16);
    BOOST_REQUIRE_NE(narrowed, utf8);
#else
    BOOST_REQUIRE_EQUAL(widened.c_str(), utf16);
    BOOST_REQUIRE_EQUAL(narrowed, utf8);
#endif
}

// to_utf8 (wchar_t[])

BOOST_AUTO_TEST_CASE(unicode__to_utf8_array__null_out__zero)
{
    const wchar_t* in = L"";
    BOOST_REQUIRE_EQUAL(to_utf8(nullptr, 42, in, 42), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf8_array__null_in__zero)
{
    char out[42];
    BOOST_REQUIRE_EQUAL(to_utf8(out, 42, nullptr, 42), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf8_array__zero_in__zero)
{
    char out[42];
    const wchar_t* in = L"";
    BOOST_REQUIRE_EQUAL(to_utf8(out, 42, in, 0), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf8_array__zero_out__zero)
{
    char out[42];
    const wchar_t* in = L"";
    BOOST_REQUIRE_EQUAL(to_utf8(out, 0, in, 42), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf8_array__ascii__test)
{
    char utf8[20];

    // Text buffer provides null termination for test comparison.
    memset(utf8, 0, sizeof(utf8) / sizeof(char));

    // Use of L is not recommended as it will only work for ascii.
    const std::wstring utf16(L"ascii");
    const std::string expected_utf8("ascii");

    const auto size = to_utf8(utf8, sizeof(utf8), utf16.c_str(), (int)utf16.size());
    BOOST_REQUIRE_EQUAL(utf8, expected_utf8);
    BOOST_REQUIRE_EQUAL(size, expected_utf8.size());
}

BOOST_AUTO_TEST_CASE(unicode__to_utf8_array__non_ascii__test)
{
    char utf8[36];

    // Text buffer provides null termination for test comparison.
    memset(utf8, 0, sizeof(utf8) / sizeof(char));

    const std::string expected_utf8("テスト");
    const auto utf16 = to_utf16(expected_utf8);

    const auto size = to_utf8(utf8, sizeof(utf8), utf16.c_str(), (int)utf16.size());

    BOOST_REQUIRE_EQUAL(utf8, expected_utf8);
    BOOST_REQUIRE_EQUAL(size, expected_utf8.size());
}

// to_utf16 (char[])

BOOST_AUTO_TEST_CASE(unicode__to_utf16_array__null_truncated__zero)
{
    size_t truncated;
    const auto in = "";
    BOOST_REQUIRE_EQUAL(to_utf16(truncated, nullptr, 42, in, 42), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf16_array__null_out__zero)
{
    size_t truncated;
    const auto in = "";
    BOOST_REQUIRE_EQUAL(to_utf16(truncated, nullptr, 42, in, 42), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf16_array__null_in__zero)
{
    size_t truncated;
    wchar_t out[42];
    BOOST_REQUIRE_EQUAL(to_utf16(truncated, out, 42, nullptr, 42), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf16_array__zero_in__zero)
{
    size_t truncated;
    wchar_t out[42];
    const auto in = "";
    BOOST_REQUIRE_EQUAL(to_utf16(truncated, out, 42, in, 0), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf16_array__zero_out__zero)
{
    size_t truncated;
    wchar_t* out = nullptr;
    const auto in = "";
    BOOST_REQUIRE_EQUAL(to_utf16(truncated, out, 0, in, 42), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf16_array__ascii__expected)
{
    const auto length = 20u;
    wchar_t utf16[length];

    // Text buffer provides null termination for test comparison.
    wmemset(utf16, 0, length);

    // Use of L is not recommended as it will only work for ascii.
    const std::wstring expected_utf16(L"ascii");
    const std::string utf8("ascii");

    size_t truncated;
    const auto size = to_utf16(truncated, utf16, length, utf8.c_str(), utf8.length());

    BOOST_REQUIRE_EQUAL(utf16, expected_utf16.c_str());
    BOOST_REQUIRE_EQUAL(size, expected_utf16.size());
    BOOST_REQUIRE_EQUAL(truncated, 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf16_array__non_ascii__expected)
{
    const auto length = 36u;
    wchar_t utf16[length];

    // Text buffer provides null termination for test comparison.
    wmemset(utf16, 0, length);

    const std::string utf8("テスト");
    const auto expected_utf16 = to_utf16(utf8);

    size_t truncated;
    const auto size = to_utf16(truncated, utf16, length, utf8.c_str(), utf8.length());

    BOOST_REQUIRE_EQUAL(utf16, expected_utf16.c_str());
    BOOST_REQUIRE_EQUAL(size, expected_utf16.size());
    BOOST_REQUIRE_EQUAL(truncated, 0u);
}

BOOST_AUTO_TEST_CASE(unicode__to_utf16_array__non_ascii_truncation1__expected)
{
    const auto length = 36u;
    wchar_t utf16[length];

    // Text buffer provides null termination for test comparison.
    wmemset(utf16, 0, length);

    std::string utf8("テスト");
    auto expected_utf16 = to_utf16(utf8);

    // Lop off last byte, which will split the last character.
    const auto drop_bytes = 1u;
    utf8.resize(utf8.size() - drop_bytes);

    // Expect the loss of the last wide character.
    expected_utf16.resize(expected_utf16.size() - 1u);

    // Expect the truncation of the remaining bytes of the last character.
    const auto expected_truncated = strlen("ト") - 1u;

    size_t truncated;
    const auto size = to_utf16(truncated, utf16, length, utf8.c_str(), utf8.length());

    BOOST_REQUIRE_EQUAL(truncated, expected_truncated);
    BOOST_REQUIRE_EQUAL(utf16, expected_utf16.c_str());
    BOOST_REQUIRE_EQUAL(size, expected_utf16.size());
}

BOOST_AUTO_TEST_CASE(unicode__to_utf16_array__non_ascii_truncation2__expected)
{
    const auto length = 36u;
    wchar_t utf16[length];

    // Text buffer provides null termination for test comparison.
    wmemset(utf16, 0, length);

    std::string utf8("テスト");
    auto expected_utf16 = to_utf16(utf8);

    // Lop off last two bytes, which will split the last character.
    const auto drop_bytes = 2u;
    utf8.resize(utf8.size() - drop_bytes);

    // Expect the loss of the last wide character.
    expected_utf16.resize(expected_utf16.size() - 1u);

    // Expect the truncation of the remaining bytes of the last character.
    const auto expected_truncated = strlen("ト") - drop_bytes;

    size_t truncated;
    const auto size = to_utf16(truncated, utf16, length, utf8.c_str(), utf8.length());

    BOOST_REQUIRE_EQUAL(truncated, expected_truncated);
    BOOST_REQUIRE_EQUAL(utf16, expected_utf16.c_str());
    BOOST_REQUIRE_EQUAL(size, expected_utf16.size());
}

// allocate_environment (vars) / free_environment

#ifdef _MSC_VER

BOOST_AUTO_TEST_CASE(unicode__allocate_environment_vars__ascii__expected)
{
    std::vector<const wchar_t*> wide_environment = { L"ascii", nullptr };
    auto variables = const_cast<wchar_t**>(&wide_environment[0]);
    auto narrow_environment = allocate_environment(variables);
    BOOST_REQUIRE_EQUAL(narrow_environment[0], "ascii");
    free_environment(narrow_environment);
}

BOOST_AUTO_TEST_CASE(unicode__allocate_environment_vars__utf16__expected)
{
    // We cannot use L for literal encoding of non-ascii text on Windows.
    auto utf16 = to_utf16("テスト");
    auto non_literal_utf16 = utf16.c_str();
    std::vector<const wchar_t*> wide_environment = { L"ascii", non_literal_utf16, nullptr };
    auto variables = const_cast<wchar_t**>(&wide_environment[0]);
    auto narrow_environment = allocate_environment(variables);
    BOOST_REQUIRE_EQUAL(narrow_environment[0], "ascii");
    BOOST_REQUIRE_EQUAL(narrow_environment[1], "テスト");
    free_environment(narrow_environment);
}

BOOST_AUTO_TEST_CASE(unicode__allocate_environment_vars__null_termination__expected)
{
    std::vector<const wchar_t*> wide_environment = { L"ascii", nullptr };
    auto variables = const_cast<wchar_t**>(&wide_environment[0]);
    auto expected_count = static_cast<int>(wide_environment.size()) - 1u;
    auto narrow_environment = allocate_environment(variables);

    // Each argument is a null terminated string.
    const auto length = strlen(narrow_environment[0]);
    auto variable_terminator = narrow_environment[0][length];
    BOOST_REQUIRE_EQUAL(variable_terminator, '\0');

    // The argument vector is a null terminated array.
    auto environment_terminator = narrow_environment[expected_count];
    BOOST_REQUIRE_EQUAL(environment_terminator, (char*)nullptr);
    free_environment(narrow_environment);
}

// allocate_environment (args) / free_environment

BOOST_AUTO_TEST_CASE(unicode__allocate_environment_args__ascii__expected)
{
    std::vector<const wchar_t*> wide_args = { L"ascii", nullptr };
    auto argv = const_cast<wchar_t**>(&wide_args[0]);
    auto argc = static_cast<int>(wide_args.size()) - 1u;
    auto narrow_args = allocate_environment(argc, argv);
    BOOST_REQUIRE_EQUAL(narrow_args[0], "ascii");
    free_environment(narrow_args);
}

BOOST_AUTO_TEST_CASE(unicode__allocate_environment_args__utf16__expected)
{
    // We cannot use L for literal encoding of non-ascii text on Windows.
    auto utf16 = to_utf16("テスト");
    auto non_literal_utf16 = utf16.c_str();
    std::vector<const wchar_t*> wide_args = { L"ascii", non_literal_utf16, nullptr };
    auto argv = const_cast<wchar_t**>(&wide_args[0]);
    auto argc = static_cast<int>(wide_args.size()) - 1u;
    auto narrow_args = allocate_environment(argc, argv);
    BOOST_REQUIRE_EQUAL(narrow_args[0], "ascii");
    BOOST_REQUIRE_EQUAL(narrow_args[1], "テスト");
    free_environment(narrow_args);
}

BOOST_AUTO_TEST_CASE(unicode__allocate_environment_args__null_termination__expected)
{
    std::vector<const wchar_t*> wide_args = { L"ascii", nullptr };
    auto argv = const_cast<wchar_t**>(&wide_args[0]);
    auto argc = static_cast<int>(wide_args.size()) - 1u;
    auto narrow_args = allocate_environment(argc, argv);

    // Each argument is a null terminated string.
    const auto length = strlen(narrow_args[0]);
    auto arg_terminator = narrow_args[0][length];
    BOOST_REQUIRE_EQUAL(arg_terminator, '\0');

    // The argument vector is a null terminated array.
    auto argv_terminator = narrow_args[argc];
    BOOST_REQUIRE_EQUAL(argv_terminator, (char*)nullptr);
    free_environment(narrow_args);
}

// utf8_remainder_size

BOOST_AUTO_TEST_CASE(unicode__utf8_remainder_size__empty_zero)
{
    BOOST_REQUIRE_EQUAL(utf8_remainder_size(nullptr, 0), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__utf8_remainder_size__ascii_bytes___zero)
{
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("a", 1), 0u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("ab", 2), 0u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("abc", 3), 0u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("abcd", 4), 0u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("abcde", 5), 0u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("abcdef", 6), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__utf8_remainder_size__whole_characters___zero)
{
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xDF\xbf", 2), 0u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xEF\xbf\xbf", 3), 0u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xF7\xbf\xbf\xbf", 4), 0u);
}

BOOST_AUTO_TEST_CASE(unicode__utf8_remainder_size__truncated_trailing_bytes___expected)
{
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xDF", 1), 1u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xEF", 1), 1u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xEF\xbf", 2), 2u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xF7", 1), 1u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xF7\xbf", 2), 2u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xF7\xbf\xbf", 3), 3u);
}

BOOST_AUTO_TEST_CASE(unicode__utf8_remainder_size__invalid_leading_bytes___zero)
{
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xbf", 1), 0u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xbf\xbf", 2), 0u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xbf\xbf\xbf", 3), 0u);
    BOOST_REQUIRE_EQUAL(utf8_remainder_size("\xbf\xbf\xbf\xbf", 4), 0u);
}

#endif

BOOST_AUTO_TEST_SUITE_END()
