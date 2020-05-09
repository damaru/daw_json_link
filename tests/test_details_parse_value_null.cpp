// The MIT License (MIT)
//
// Copyright (c) Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and / or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <daw/json/daw_json_link.h>
#include <daw/json/impl/daw_iterator_range.h>
#include <daw/json/impl/daw_json_parse_common.h>

#include <daw/daw_benchmark.h>

#include <iostream>
#include <optional>
#include <string_view>

bool test_null_literal_untrusted( ) {
	using namespace daw::json;
	using namespace daw::json::json_details;

	using my_number = json_number_null<no_name, std::optional<int>>;
	constexpr std::string_view sv = "null,";
	auto rng = IteratorRange( sv.data( ), sv.data( ) + sv.size( ) );
	auto v = parse_value<my_number>( ParseTag<JsonParseTypes::Null>{ }, rng );
	return not v;
}

bool test_null_literal_known( ) {
	using namespace daw::json;
	using namespace daw::json::json_details;

	using my_number = json_number_null<no_name, std::optional<int>>;
	auto rng = IteratorRange<char const *, false>( );
	auto v =
	  parse_value<my_number, true>( ParseTag<JsonParseTypes::Null>{ }, rng );
	return not v;
}

bool test_null_number_untrusted( ) {
	using namespace daw::json;
	using namespace daw::json::json_details;

	using my_number = json_number_null<no_name, std::optional<int>>;
	constexpr std::string_view sv = "5,";
	auto rng = IteratorRange( sv.data( ), sv.data( ) + sv.size( ) );
	auto v = parse_value<my_number>( ParseTag<JsonParseTypes::Null>{ }, rng );
	return v and *v == 5;
}

bool test_null_number_trusted( ) {
	using namespace daw::json;
	using namespace daw::json::json_details;

	using my_number = json_number_null<no_name, std::optional<int>>;
	constexpr std::string_view sv = "5,";
	auto rng =
	  IteratorRange<char const *, true>( sv.data( ), sv.data( ) + sv.size( ) );
	auto v = parse_value<my_number>( ParseTag<JsonParseTypes::Null>{ }, rng );
	return v and *v == 5;
}

bool test_null_number_untrusted_known( ) {
	using namespace daw::json;
	using namespace daw::json::json_details;

	using my_number = json_number_null<no_name, std::optional<int>>;
	constexpr std::string_view sv = "5,";
	auto rng = IteratorRange( sv.data( ), sv.data( ) + sv.size( ) );
	auto v =
	  parse_value<my_number, true>( ParseTag<JsonParseTypes::Null>{ }, rng );
	return v and *v == 5;
}

#define do_test( ... )                                                         \
	try {                                                                        \
		daw::expecting_message( __VA_ARGS__, "" #__VA_ARGS__ );                    \
	} catch( daw::json::json_exception const &jex ) {                            \
		std::cerr << "Unexpected exception thrown by parser in test '"             \
		          << "" #__VA_ARGS__ << "': " << jex.reason( ) << std::endl;       \
	}                                                                            \
	do {                                                                         \
	} while( false )

int main( int, char ** ) try {
	do_test( test_null_literal_untrusted( ) );
	do_test( test_null_literal_known( ) );
	do_test( test_null_number_untrusted( ) );
	do_test( test_null_number_trusted( ) );
	do_test( test_null_number_untrusted_known( ) );
} catch( daw::json::json_exception const &jex ) {
	std::cerr << "Exception thrown by parser: " << jex.reason( ) << std::endl;
	exit( 1 );
}
