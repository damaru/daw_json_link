// Code auto generated from json file '/Users/dwright/Downloads/canada.json'

#pragma once

#include <cstdint>
#include <daw/json/daw_json_link.h>
#include <string_view>
#include <tuple>
#include <vector>

struct properties_t {
	std::string_view name;
}; // properties_t

auto describe_json_class( properties_t ) {
	using namespace daw::json;
	static constexpr char const name[] = "name";
	return daw::json::class_description_t<json_string<name, std::string_view>>{};
}

auto to_json_data( properties_t const &value ) {
	return std::forward_as_tuple( value.name );
}

struct geometry_t {
	std::string_view type;
	std::vector<std::vector<std::array<double, 2>>> coordinates;
}; // geometry_t

template<typename T>
struct array_appender {
	T *ptr;

	template<size_t N>
	constexpr array_appender( std::array<T, N> &ary ) noexcept
	  : ptr( ary.data( ) ) {}

	template<typename U>
	constexpr void operator( )( U &&item ) noexcept {
		*ptr++ = std::forward<U>( item );
	}
};

auto describe_json_class( geometry_t ) {
	using namespace daw::json;
	static constexpr char const type[] = "type";
	static constexpr char const coordinates[] = "coordinates";
	return daw::json::class_description_t<
	  json_string<type, std::string_view>,
	  json_array<coordinates, std::vector<std::vector<std::array<double, 2>>>,
	             json_array<no_name, std::vector<std::array<double, 2>>,
	                        json_array<no_name, std::array<double, 2>,
	                                   json_number<no_name>,
	                                   daw::construct_a<std::array<double, 2>>,
	                                   array_appender<double>>>>>{};
}

auto to_json_data( geometry_t const &value ) {
	return std::forward_as_tuple( value.type, value.coordinates );
}

struct features_element_t {
	std::string_view type;
	properties_t properties;
	geometry_t geometry;
}; // features_element_t

auto describe_json_class( features_element_t ) {
	using namespace daw::json;
	static constexpr char const type[] = "type";
	static constexpr char const properties[] = "properties";
	static constexpr char const geometry[] = "geometry";
	return daw::json::class_description_t<json_string<type, std::string_view>,
	                                      json_class<properties, properties_t>,
	                                      json_class<geometry, geometry_t>>{};
}

auto to_json_data( features_element_t const &value ) {
	return std::forward_as_tuple( value.type, value.properties, value.geometry );
}

struct canada_object_t {
	std::string_view type;
	std::vector<features_element_t> features;
}; // root_object_t

auto describe_json_class( canada_object_t ) {
	using namespace daw::json;
	static constexpr char const type[] = "type";
	static constexpr char const features[] = "features";
	return daw::json::class_description_t<
	  json_string<type, std::string_view>,
	  json_array<features, std::vector<features_element_t>,
	             json_class<no_name, features_element_t>>>{};
}

auto to_json_data( canada_object_t const &value ) {
	return std::forward_as_tuple( value.type, value.features );
}
