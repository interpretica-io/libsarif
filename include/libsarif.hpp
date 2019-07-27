//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Libsarif data = nlohmann::json::parse(jsonString);

#pragma once

#include "json.hpp"

#include <optional>
#include <stdexcept>
#include <regex>

#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER
namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json & j, const std::shared_ptr<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json & j) {
            if (j.is_null()) return std::unique_ptr<T>(); else return std::unique_ptr<T>(new T(j.get<T>()));
        }
    };
}
#endif

namespace libsarif {
    using nlohmann::json;

    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }

    template <typename T>
    inline std::shared_ptr<T> get_optional(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template <typename T>
    inline std::shared_ptr<T> get_optional(const json & j, std::string property) {
        return get_optional<T>(j, property.data());
    }

    enum class PurpleType : int { BOOLEAN, INTEGER, NUMBER, STRING };

    class PuneHedgehog {
        public:
        PuneHedgehog() = default;
        virtual ~PuneHedgehog() = default;

        private:
        std::string description;
        PurpleType type;
        double minimum;
        std::shared_ptr<double> pune_hedgehog_default;
        std::shared_ptr<double> maximum;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const PurpleType & get_type() const { return type; }
        PurpleType & get_mutable_type() { return type; }
        void set_type(const PurpleType & value) { this->type = value; }

        const double & get_minimum() const { return minimum; }
        double & get_mutable_minimum() { return minimum; }
        void set_minimum(const double & value) { this->minimum = value; }

        std::shared_ptr<double> get_pune_hedgehog_default() const { return pune_hedgehog_default; }
        void set_pune_hedgehog_default(std::shared_ptr<double> value) { this->pune_hedgehog_default = value; }

        std::shared_ptr<double> get_maximum() const { return maximum; }
        void set_maximum(std::shared_ptr<double> value) { this->maximum = value; }
    };

    class TartuGecko {
        public:
        TartuGecko() = default;
        virtual ~TartuGecko() = default;

        private:
        std::string description;
        PurpleType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const PurpleType & get_type() const { return type; }
        PurpleType & get_mutable_type() { return type; }
        void set_type(const PurpleType & value) { this->type = value; }
    };

    class LivingstoneSouthernWhiteFacedOwl {
        public:
        LivingstoneSouthernWhiteFacedOwl() = default;
        virtual ~LivingstoneSouthernWhiteFacedOwl() = default;

        private:
        std::string description;
        std::string ref;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_ref() const { return ref; }
        std::string & get_mutable_ref() { return ref; }
        void set_ref(const std::string & value) { this->ref = value; }
    };

    class AddressProperties {
        public:
        AddressProperties() = default;
        virtual ~AddressProperties() = default;

        private:
        PuneHedgehog absolute_address;
        TartuGecko relative_address;
        TartuGecko length;
        TartuGecko kind;
        TartuGecko name;
        TartuGecko fully_qualified_name;
        TartuGecko offset_from_parent;
        PuneHedgehog index;
        PuneHedgehog parent_index;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const PuneHedgehog & get_absolute_address() const { return absolute_address; }
        PuneHedgehog & get_mutable_absolute_address() { return absolute_address; }
        void set_absolute_address(const PuneHedgehog & value) { this->absolute_address = value; }

        const TartuGecko & get_relative_address() const { return relative_address; }
        TartuGecko & get_mutable_relative_address() { return relative_address; }
        void set_relative_address(const TartuGecko & value) { this->relative_address = value; }

        const TartuGecko & get_length() const { return length; }
        TartuGecko & get_mutable_length() { return length; }
        void set_length(const TartuGecko & value) { this->length = value; }

        const TartuGecko & get_kind() const { return kind; }
        TartuGecko & get_mutable_kind() { return kind; }
        void set_kind(const TartuGecko & value) { this->kind = value; }

        const TartuGecko & get_name() const { return name; }
        TartuGecko & get_mutable_name() { return name; }
        void set_name(const TartuGecko & value) { this->name = value; }

        const TartuGecko & get_fully_qualified_name() const { return fully_qualified_name; }
        TartuGecko & get_mutable_fully_qualified_name() { return fully_qualified_name; }
        void set_fully_qualified_name(const TartuGecko & value) { this->fully_qualified_name = value; }

        const TartuGecko & get_offset_from_parent() const { return offset_from_parent; }
        TartuGecko & get_mutable_offset_from_parent() { return offset_from_parent; }
        void set_offset_from_parent(const TartuGecko & value) { this->offset_from_parent = value; }

        const PuneHedgehog & get_index() const { return index; }
        PuneHedgehog & get_mutable_index() { return index; }
        void set_index(const PuneHedgehog & value) { this->index = value; }

        const PuneHedgehog & get_parent_index() const { return parent_index; }
        PuneHedgehog & get_mutable_parent_index() { return parent_index; }
        void set_parent_index(const PuneHedgehog & value) { this->parent_index = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Address {
        public:
        Address() = default;
        virtual ~Address() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        AddressProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const AddressProperties & get_properties() const { return properties; }
        AddressProperties & get_mutable_properties() { return properties; }
        void set_properties(const AddressProperties & value) { this->properties = value; }
    };

    class AdditionalProperties {
        public:
        AdditionalProperties() = default;
        virtual ~AdditionalProperties() = default;

        private:
        PurpleType type;

        public:
        const PurpleType & get_type() const { return type; }
        PurpleType & get_mutable_type() { return type; }
        void set_type(const PurpleType & value) { this->type = value; }
    };

    class Hashes {
        public:
        Hashes() = default;
        virtual ~Hashes() = default;

        private:
        std::string description;
        std::string type;
        AdditionalProperties additional_properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const AdditionalProperties & get_additional_properties() const { return additional_properties; }
        AdditionalProperties & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const AdditionalProperties & value) { this->additional_properties = value; }
    };

    enum class Format : int { DATE_TIME, URI, URI_REFERENCE };

    class Schema {
        public:
        Schema() = default;
        virtual ~Schema() = default;

        private:
        std::string description;
        PurpleType type;
        Format format;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const PurpleType & get_type() const { return type; }
        PurpleType & get_mutable_type() { return type; }
        void set_type(const PurpleType & value) { this->type = value; }

        const Format & get_format() const { return format; }
        Format & get_mutable_format() { return format; }
        void set_format(const Format & value) { this->format = value; }
    };

    class MimeType {
        public:
        MimeType() = default;
        virtual ~MimeType() = default;

        private:
        std::string description;
        PurpleType type;
        std::string pattern;
        std::shared_ptr<std::string> mime_type_default;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const PurpleType & get_type() const { return type; }
        PurpleType & get_mutable_type() { return type; }
        void set_type(const PurpleType & value) { this->type = value; }

        const std::string & get_pattern() const { return pattern; }
        std::string & get_mutable_pattern() { return pattern; }
        void set_pattern(const std::string & value) { this->pattern = value; }

        std::shared_ptr<std::string> get_mime_type_default() const { return mime_type_default; }
        void set_mime_type_default(std::shared_ptr<std::string> value) { this->mime_type_default = value; }
    };

    class RolesItems {
        public:
        RolesItems() = default;
        virtual ~RolesItems() = default;

        private:
        std::vector<std::string> items_enum;

        public:
        const std::vector<std::string> & get_items_enum() const { return items_enum; }
        std::vector<std::string> & get_mutable_items_enum() { return items_enum; }
        void set_items_enum(const std::vector<std::string> & value) { this->items_enum = value; }
    };

    enum class FluffyType : int { ARRAY };

    class Roles {
        public:
        Roles() = default;
        virtual ~Roles() = default;

        private:
        std::string description;
        FluffyType type;
        std::shared_ptr<int64_t> min_items;
        bool unique_items;
        std::vector<std::string> roles_default;
        RolesItems items;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const FluffyType & get_type() const { return type; }
        FluffyType & get_mutable_type() { return type; }
        void set_type(const FluffyType & value) { this->type = value; }

        std::shared_ptr<int64_t> get_min_items() const { return min_items; }
        void set_min_items(std::shared_ptr<int64_t> value) { this->min_items = value; }

        const bool & get_unique_items() const { return unique_items; }
        bool & get_mutable_unique_items() { return unique_items; }
        void set_unique_items(const bool & value) { this->unique_items = value; }

        const std::vector<std::string> & get_roles_default() const { return roles_default; }
        std::vector<std::string> & get_mutable_roles_default() { return roles_default; }
        void set_roles_default(const std::vector<std::string> & value) { this->roles_default = value; }

        const RolesItems & get_items() const { return items; }
        RolesItems & get_mutable_items() { return items; }
        void set_items(const RolesItems & value) { this->items = value; }
    };

    class ArtifactProperties {
        public:
        ArtifactProperties() = default;
        virtual ~ArtifactProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl description;
        LivingstoneSouthernWhiteFacedOwl location;
        PuneHedgehog parent_index;
        PuneHedgehog offset;
        PuneHedgehog length;
        Roles roles;
        MimeType mime_type;
        LivingstoneSouthernWhiteFacedOwl contents;
        TartuGecko encoding;
        TartuGecko source_language;
        Hashes hashes;
        Schema last_modified_time_utc;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_description() const { return description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_description() { return description; }
        void set_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->description = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_location() const { return location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_location() { return location; }
        void set_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->location = value; }

        const PuneHedgehog & get_parent_index() const { return parent_index; }
        PuneHedgehog & get_mutable_parent_index() { return parent_index; }
        void set_parent_index(const PuneHedgehog & value) { this->parent_index = value; }

        const PuneHedgehog & get_offset() const { return offset; }
        PuneHedgehog & get_mutable_offset() { return offset; }
        void set_offset(const PuneHedgehog & value) { this->offset = value; }

        const PuneHedgehog & get_length() const { return length; }
        PuneHedgehog & get_mutable_length() { return length; }
        void set_length(const PuneHedgehog & value) { this->length = value; }

        const Roles & get_roles() const { return roles; }
        Roles & get_mutable_roles() { return roles; }
        void set_roles(const Roles & value) { this->roles = value; }

        const MimeType & get_mime_type() const { return mime_type; }
        MimeType & get_mutable_mime_type() { return mime_type; }
        void set_mime_type(const MimeType & value) { this->mime_type = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_contents() const { return contents; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_contents() { return contents; }
        void set_contents(const LivingstoneSouthernWhiteFacedOwl & value) { this->contents = value; }

        const TartuGecko & get_encoding() const { return encoding; }
        TartuGecko & get_mutable_encoding() { return encoding; }
        void set_encoding(const TartuGecko & value) { this->encoding = value; }

        const TartuGecko & get_source_language() const { return source_language; }
        TartuGecko & get_mutable_source_language() { return source_language; }
        void set_source_language(const TartuGecko & value) { this->source_language = value; }

        const Hashes & get_hashes() const { return hashes; }
        Hashes & get_mutable_hashes() { return hashes; }
        void set_hashes(const Hashes & value) { this->hashes = value; }

        const Schema & get_last_modified_time_utc() const { return last_modified_time_utc; }
        Schema & get_mutable_last_modified_time_utc() { return last_modified_time_utc; }
        void set_last_modified_time_utc(const Schema & value) { this->last_modified_time_utc = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Artifact {
        public:
        Artifact() = default;
        virtual ~Artifact() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ArtifactProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ArtifactProperties & get_properties() const { return properties; }
        ArtifactProperties & get_mutable_properties() { return properties; }
        void set_properties(const ArtifactProperties & value) { this->properties = value; }
    };

    class AdditionalPropertiesClass {
        public:
        AdditionalPropertiesClass() = default;
        virtual ~AdditionalPropertiesClass() = default;

        private:
        std::string ref;

        public:
        const std::string & get_ref() const { return ref; }
        std::string & get_mutable_ref() { return ref; }
        void set_ref(const std::string & value) { this->ref = value; }
    };

    class HammerfestPonies {
        public:
        HammerfestPonies() = default;
        virtual ~HammerfestPonies() = default;

        private:
        std::string description;
        FluffyType type;
        int64_t min_items;
        std::shared_ptr<bool> unique_items;
        AdditionalPropertiesClass items;
        std::shared_ptr<std::vector<nlohmann::json>> hammerfest_ponies_default;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const FluffyType & get_type() const { return type; }
        FluffyType & get_mutable_type() { return type; }
        void set_type(const FluffyType & value) { this->type = value; }

        const int64_t & get_min_items() const { return min_items; }
        int64_t & get_mutable_min_items() { return min_items; }
        void set_min_items(const int64_t & value) { this->min_items = value; }

        std::shared_ptr<bool> get_unique_items() const { return unique_items; }
        void set_unique_items(std::shared_ptr<bool> value) { this->unique_items = value; }

        const AdditionalPropertiesClass & get_items() const { return items; }
        AdditionalPropertiesClass & get_mutable_items() { return items; }
        void set_items(const AdditionalPropertiesClass & value) { this->items = value; }

        std::shared_ptr<std::vector<nlohmann::json>> get_hammerfest_ponies_default() const { return hammerfest_ponies_default; }
        void set_hammerfest_ponies_default(std::shared_ptr<std::vector<nlohmann::json>> value) { this->hammerfest_ponies_default = value; }
    };

    class ArtifactChangeProperties {
        public:
        ArtifactChangeProperties() = default;
        virtual ~ArtifactChangeProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl artifact_location;
        HammerfestPonies replacements;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_artifact_location() const { return artifact_location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_artifact_location() { return artifact_location; }
        void set_artifact_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->artifact_location = value; }

        const HammerfestPonies & get_replacements() const { return replacements; }
        HammerfestPonies & get_mutable_replacements() { return replacements; }
        void set_replacements(const HammerfestPonies & value) { this->replacements = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ArtifactChange {
        public:
        ArtifactChange() = default;
        virtual ~ArtifactChange() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ArtifactChangeProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ArtifactChangeProperties & get_properties() const { return properties; }
        ArtifactChangeProperties & get_mutable_properties() { return properties; }
        void set_properties(const ArtifactChangeProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ArtifactContentProperties {
        public:
        ArtifactContentProperties() = default;
        virtual ~ArtifactContentProperties() = default;

        private:
        TartuGecko text;
        TartuGecko binary;
        LivingstoneSouthernWhiteFacedOwl rendered;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_text() const { return text; }
        TartuGecko & get_mutable_text() { return text; }
        void set_text(const TartuGecko & value) { this->text = value; }

        const TartuGecko & get_binary() const { return binary; }
        TartuGecko & get_mutable_binary() { return binary; }
        void set_binary(const TartuGecko & value) { this->binary = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_rendered() const { return rendered; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_rendered() { return rendered; }
        void set_rendered(const LivingstoneSouthernWhiteFacedOwl & value) { this->rendered = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ArtifactContent {
        public:
        ArtifactContent() = default;
        virtual ~ArtifactContent() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        ArtifactContentProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const ArtifactContentProperties & get_properties() const { return properties; }
        ArtifactContentProperties & get_mutable_properties() { return properties; }
        void set_properties(const ArtifactContentProperties & value) { this->properties = value; }
    };

    class ArtifactLocationProperties {
        public:
        ArtifactLocationProperties() = default;
        virtual ~ArtifactLocationProperties() = default;

        private:
        Schema uri;
        TartuGecko uri_base_id;
        PuneHedgehog index;
        LivingstoneSouthernWhiteFacedOwl description;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const Schema & get_uri() const { return uri; }
        Schema & get_mutable_uri() { return uri; }
        void set_uri(const Schema & value) { this->uri = value; }

        const TartuGecko & get_uri_base_id() const { return uri_base_id; }
        TartuGecko & get_mutable_uri_base_id() { return uri_base_id; }
        void set_uri_base_id(const TartuGecko & value) { this->uri_base_id = value; }

        const PuneHedgehog & get_index() const { return index; }
        PuneHedgehog & get_mutable_index() { return index; }
        void set_index(const PuneHedgehog & value) { this->index = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_description() const { return description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_description() { return description; }
        void set_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->description = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ArtifactLocation {
        public:
        ArtifactLocation() = default;
        virtual ~ArtifactLocation() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ArtifactLocationProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ArtifactLocationProperties & get_properties() const { return properties; }
        ArtifactLocationProperties & get_mutable_properties() { return properties; }
        void set_properties(const ArtifactLocationProperties & value) { this->properties = value; }
    };

    class AttachmentProperties {
        public:
        AttachmentProperties() = default;
        virtual ~AttachmentProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl description;
        LivingstoneSouthernWhiteFacedOwl artifact_location;
        HammerfestPonies regions;
        HammerfestPonies rectangles;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_description() const { return description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_description() { return description; }
        void set_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->description = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_artifact_location() const { return artifact_location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_artifact_location() { return artifact_location; }
        void set_artifact_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->artifact_location = value; }

        const HammerfestPonies & get_regions() const { return regions; }
        HammerfestPonies & get_mutable_regions() { return regions; }
        void set_regions(const HammerfestPonies & value) { this->regions = value; }

        const HammerfestPonies & get_rectangles() const { return rectangles; }
        HammerfestPonies & get_mutable_rectangles() { return rectangles; }
        void set_rectangles(const HammerfestPonies & value) { this->rectangles = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Attachment {
        public:
        Attachment() = default;
        virtual ~Attachment() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        AttachmentProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const AttachmentProperties & get_properties() const { return properties; }
        AttachmentProperties & get_mutable_properties() { return properties; }
        void set_properties(const AttachmentProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class CodeFlowProperties {
        public:
        CodeFlowProperties() = default;
        virtual ~CodeFlowProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl message;
        HammerfestPonies thread_flows;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_message() const { return message; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_message() { return message; }
        void set_message(const LivingstoneSouthernWhiteFacedOwl & value) { this->message = value; }

        const HammerfestPonies & get_thread_flows() const { return thread_flows; }
        HammerfestPonies & get_mutable_thread_flows() { return thread_flows; }
        void set_thread_flows(const HammerfestPonies & value) { this->thread_flows = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class CodeFlow {
        public:
        CodeFlow() = default;
        virtual ~CodeFlow() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        CodeFlowProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const CodeFlowProperties & get_properties() const { return properties; }
        CodeFlowProperties & get_mutable_properties() { return properties; }
        void set_properties(const CodeFlowProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ConfigurationOverrideProperties {
        public:
        ConfigurationOverrideProperties() = default;
        virtual ~ConfigurationOverrideProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl configuration;
        LivingstoneSouthernWhiteFacedOwl descriptor;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_configuration() const { return configuration; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_configuration() { return configuration; }
        void set_configuration(const LivingstoneSouthernWhiteFacedOwl & value) { this->configuration = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_descriptor() const { return descriptor; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_descriptor() { return descriptor; }
        void set_descriptor(const LivingstoneSouthernWhiteFacedOwl & value) { this->descriptor = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ConfigurationOverride {
        public:
        ConfigurationOverride() = default;
        virtual ~ConfigurationOverride() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        ConfigurationOverrideProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const ConfigurationOverrideProperties & get_properties() const { return properties; }
        ConfigurationOverrideProperties & get_mutable_properties() { return properties; }
        void set_properties(const ConfigurationOverrideProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ConversionProperties {
        public:
        ConversionProperties() = default;
        virtual ~ConversionProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl tool;
        LivingstoneSouthernWhiteFacedOwl invocation;
        HammerfestPonies analysis_tool_log_files;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_tool() const { return tool; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_tool() { return tool; }
        void set_tool(const LivingstoneSouthernWhiteFacedOwl & value) { this->tool = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_invocation() const { return invocation; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_invocation() { return invocation; }
        void set_invocation(const LivingstoneSouthernWhiteFacedOwl & value) { this->invocation = value; }

        const HammerfestPonies & get_analysis_tool_log_files() const { return analysis_tool_log_files; }
        HammerfestPonies & get_mutable_analysis_tool_log_files() { return analysis_tool_log_files; }
        void set_analysis_tool_log_files(const HammerfestPonies & value) { this->analysis_tool_log_files = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Conversion {
        public:
        Conversion() = default;
        virtual ~Conversion() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ConversionProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ConversionProperties & get_properties() const { return properties; }
        ConversionProperties & get_mutable_properties() { return properties; }
        void set_properties(const ConversionProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class EdgeProperties {
        public:
        EdgeProperties() = default;
        virtual ~EdgeProperties() = default;

        private:
        TartuGecko id;
        LivingstoneSouthernWhiteFacedOwl label;
        TartuGecko source_node_id;
        TartuGecko target_node_id;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_id() const { return id; }
        TartuGecko & get_mutable_id() { return id; }
        void set_id(const TartuGecko & value) { this->id = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_label() const { return label; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_label() { return label; }
        void set_label(const LivingstoneSouthernWhiteFacedOwl & value) { this->label = value; }

        const TartuGecko & get_source_node_id() const { return source_node_id; }
        TartuGecko & get_mutable_source_node_id() { return source_node_id; }
        void set_source_node_id(const TartuGecko & value) { this->source_node_id = value; }

        const TartuGecko & get_target_node_id() const { return target_node_id; }
        TartuGecko & get_mutable_target_node_id() { return target_node_id; }
        void set_target_node_id(const TartuGecko & value) { this->target_node_id = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Edge {
        public:
        Edge() = default;
        virtual ~Edge() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        EdgeProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const EdgeProperties & get_properties() const { return properties; }
        EdgeProperties & get_mutable_properties() { return properties; }
        void set_properties(const EdgeProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class FinalState {
        public:
        FinalState() = default;
        virtual ~FinalState() = default;

        private:
        std::string description;
        std::string type;
        AdditionalPropertiesClass additional_properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const AdditionalPropertiesClass & get_additional_properties() const { return additional_properties; }
        AdditionalPropertiesClass & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const AdditionalPropertiesClass & value) { this->additional_properties = value; }
    };

    class EdgeTraversalProperties {
        public:
        EdgeTraversalProperties() = default;
        virtual ~EdgeTraversalProperties() = default;

        private:
        TartuGecko edge_id;
        LivingstoneSouthernWhiteFacedOwl message;
        FinalState final_state;
        PuneHedgehog step_over_edge_count;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_edge_id() const { return edge_id; }
        TartuGecko & get_mutable_edge_id() { return edge_id; }
        void set_edge_id(const TartuGecko & value) { this->edge_id = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_message() const { return message; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_message() { return message; }
        void set_message(const LivingstoneSouthernWhiteFacedOwl & value) { this->message = value; }

        const FinalState & get_final_state() const { return final_state; }
        FinalState & get_mutable_final_state() { return final_state; }
        void set_final_state(const FinalState & value) { this->final_state = value; }

        const PuneHedgehog & get_step_over_edge_count() const { return step_over_edge_count; }
        PuneHedgehog & get_mutable_step_over_edge_count() { return step_over_edge_count; }
        void set_step_over_edge_count(const PuneHedgehog & value) { this->step_over_edge_count = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class EdgeTraversal {
        public:
        EdgeTraversal() = default;
        virtual ~EdgeTraversal() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        EdgeTraversalProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const EdgeTraversalProperties & get_properties() const { return properties; }
        EdgeTraversalProperties & get_mutable_properties() { return properties; }
        void set_properties(const EdgeTraversalProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ExceptionProperties {
        public:
        ExceptionProperties() = default;
        virtual ~ExceptionProperties() = default;

        private:
        TartuGecko kind;
        TartuGecko message;
        LivingstoneSouthernWhiteFacedOwl stack;
        HammerfestPonies inner_exceptions;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_kind() const { return kind; }
        TartuGecko & get_mutable_kind() { return kind; }
        void set_kind(const TartuGecko & value) { this->kind = value; }

        const TartuGecko & get_message() const { return message; }
        TartuGecko & get_mutable_message() { return message; }
        void set_message(const TartuGecko & value) { this->message = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_stack() const { return stack; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_stack() { return stack; }
        void set_stack(const LivingstoneSouthernWhiteFacedOwl & value) { this->stack = value; }

        const HammerfestPonies & get_inner_exceptions() const { return inner_exceptions; }
        HammerfestPonies & get_mutable_inner_exceptions() { return inner_exceptions; }
        void set_inner_exceptions(const HammerfestPonies & value) { this->inner_exceptions = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Exception {
        public:
        Exception() = default;
        virtual ~Exception() = default;

        private:
        std::string type;
        ExceptionProperties properties;

        public:
        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ExceptionProperties & get_properties() const { return properties; }
        ExceptionProperties & get_mutable_properties() { return properties; }
        void set_properties(const ExceptionProperties & value) { this->properties = value; }
    };

    class Version {
        public:
        Version() = default;
        virtual ~Version() = default;

        private:
        std::string description;
        std::vector<std::string> version_enum;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::vector<std::string> & get_version_enum() const { return version_enum; }
        std::vector<std::string> & get_mutable_version_enum() { return version_enum; }
        void set_version_enum(const std::vector<std::string> & value) { this->version_enum = value; }
    };

    class ExternalPropertiesProperties {
        public:
        ExternalPropertiesProperties() = default;
        virtual ~ExternalPropertiesProperties() = default;

        private:
        Schema schema;
        Version version;
        MimeType guid;
        MimeType run_guid;
        LivingstoneSouthernWhiteFacedOwl conversion;
        HammerfestPonies graphs;
        LivingstoneSouthernWhiteFacedOwl externalized_properties;
        HammerfestPonies artifacts;
        HammerfestPonies invocations;
        HammerfestPonies logical_locations;
        HammerfestPonies thread_flow_locations;
        HammerfestPonies results;
        HammerfestPonies taxonomies;
        LivingstoneSouthernWhiteFacedOwl driver;
        HammerfestPonies extensions;
        HammerfestPonies policies;
        HammerfestPonies translations;
        HammerfestPonies addresses;
        HammerfestPonies web_requests;
        HammerfestPonies web_responses;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const Schema & get_schema() const { return schema; }
        Schema & get_mutable_schema() { return schema; }
        void set_schema(const Schema & value) { this->schema = value; }

        const Version & get_version() const { return version; }
        Version & get_mutable_version() { return version; }
        void set_version(const Version & value) { this->version = value; }

        const MimeType & get_guid() const { return guid; }
        MimeType & get_mutable_guid() { return guid; }
        void set_guid(const MimeType & value) { this->guid = value; }

        const MimeType & get_run_guid() const { return run_guid; }
        MimeType & get_mutable_run_guid() { return run_guid; }
        void set_run_guid(const MimeType & value) { this->run_guid = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_conversion() const { return conversion; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_conversion() { return conversion; }
        void set_conversion(const LivingstoneSouthernWhiteFacedOwl & value) { this->conversion = value; }

        const HammerfestPonies & get_graphs() const { return graphs; }
        HammerfestPonies & get_mutable_graphs() { return graphs; }
        void set_graphs(const HammerfestPonies & value) { this->graphs = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_externalized_properties() const { return externalized_properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_externalized_properties() { return externalized_properties; }
        void set_externalized_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->externalized_properties = value; }

        const HammerfestPonies & get_artifacts() const { return artifacts; }
        HammerfestPonies & get_mutable_artifacts() { return artifacts; }
        void set_artifacts(const HammerfestPonies & value) { this->artifacts = value; }

        const HammerfestPonies & get_invocations() const { return invocations; }
        HammerfestPonies & get_mutable_invocations() { return invocations; }
        void set_invocations(const HammerfestPonies & value) { this->invocations = value; }

        const HammerfestPonies & get_logical_locations() const { return logical_locations; }
        HammerfestPonies & get_mutable_logical_locations() { return logical_locations; }
        void set_logical_locations(const HammerfestPonies & value) { this->logical_locations = value; }

        const HammerfestPonies & get_thread_flow_locations() const { return thread_flow_locations; }
        HammerfestPonies & get_mutable_thread_flow_locations() { return thread_flow_locations; }
        void set_thread_flow_locations(const HammerfestPonies & value) { this->thread_flow_locations = value; }

        const HammerfestPonies & get_results() const { return results; }
        HammerfestPonies & get_mutable_results() { return results; }
        void set_results(const HammerfestPonies & value) { this->results = value; }

        const HammerfestPonies & get_taxonomies() const { return taxonomies; }
        HammerfestPonies & get_mutable_taxonomies() { return taxonomies; }
        void set_taxonomies(const HammerfestPonies & value) { this->taxonomies = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_driver() const { return driver; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_driver() { return driver; }
        void set_driver(const LivingstoneSouthernWhiteFacedOwl & value) { this->driver = value; }

        const HammerfestPonies & get_extensions() const { return extensions; }
        HammerfestPonies & get_mutable_extensions() { return extensions; }
        void set_extensions(const HammerfestPonies & value) { this->extensions = value; }

        const HammerfestPonies & get_policies() const { return policies; }
        HammerfestPonies & get_mutable_policies() { return policies; }
        void set_policies(const HammerfestPonies & value) { this->policies = value; }

        const HammerfestPonies & get_translations() const { return translations; }
        HammerfestPonies & get_mutable_translations() { return translations; }
        void set_translations(const HammerfestPonies & value) { this->translations = value; }

        const HammerfestPonies & get_addresses() const { return addresses; }
        HammerfestPonies & get_mutable_addresses() { return addresses; }
        void set_addresses(const HammerfestPonies & value) { this->addresses = value; }

        const HammerfestPonies & get_web_requests() const { return web_requests; }
        HammerfestPonies & get_mutable_web_requests() { return web_requests; }
        void set_web_requests(const HammerfestPonies & value) { this->web_requests = value; }

        const HammerfestPonies & get_web_responses() const { return web_responses; }
        HammerfestPonies & get_mutable_web_responses() { return web_responses; }
        void set_web_responses(const HammerfestPonies & value) { this->web_responses = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ExternalProperties {
        public:
        ExternalProperties() = default;
        virtual ~ExternalProperties() = default;

        private:
        std::string type;
        ExternalPropertiesProperties properties;

        public:
        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ExternalPropertiesProperties & get_properties() const { return properties; }
        ExternalPropertiesProperties & get_mutable_properties() { return properties; }
        void set_properties(const ExternalPropertiesProperties & value) { this->properties = value; }
    };

    class Of {
        public:
        Of() = default;
        virtual ~Of() = default;

        private:
        std::vector<std::string> required;

        public:
        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ExternalPropertyFileReferenceProperties {
        public:
        ExternalPropertyFileReferenceProperties() = default;
        virtual ~ExternalPropertyFileReferenceProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl location;
        MimeType guid;
        PuneHedgehog item_count;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_location() const { return location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_location() { return location; }
        void set_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->location = value; }

        const MimeType & get_guid() const { return guid; }
        MimeType & get_mutable_guid() { return guid; }
        void set_guid(const MimeType & value) { this->guid = value; }

        const PuneHedgehog & get_item_count() const { return item_count; }
        PuneHedgehog & get_mutable_item_count() { return item_count; }
        void set_item_count(const PuneHedgehog & value) { this->item_count = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ExternalPropertyFileReference {
        public:
        ExternalPropertyFileReference() = default;
        virtual ~ExternalPropertyFileReference() = default;

        private:
        std::string type;
        ExternalPropertyFileReferenceProperties properties;
        std::vector<Of> any_of;

        public:
        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ExternalPropertyFileReferenceProperties & get_properties() const { return properties; }
        ExternalPropertyFileReferenceProperties & get_mutable_properties() { return properties; }
        void set_properties(const ExternalPropertyFileReferenceProperties & value) { this->properties = value; }

        const std::vector<Of> & get_any_of() const { return any_of; }
        std::vector<Of> & get_mutable_any_of() { return any_of; }
        void set_any_of(const std::vector<Of> & value) { this->any_of = value; }
    };

    class ExternalPropertyFileReferencesProperties {
        public:
        ExternalPropertyFileReferencesProperties() = default;
        virtual ~ExternalPropertyFileReferencesProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl conversion;
        HammerfestPonies graphs;
        LivingstoneSouthernWhiteFacedOwl externalized_properties;
        HammerfestPonies artifacts;
        HammerfestPonies invocations;
        HammerfestPonies logical_locations;
        HammerfestPonies thread_flow_locations;
        HammerfestPonies results;
        HammerfestPonies taxonomies;
        HammerfestPonies addresses;
        LivingstoneSouthernWhiteFacedOwl driver;
        HammerfestPonies extensions;
        HammerfestPonies policies;
        HammerfestPonies translations;
        HammerfestPonies web_requests;
        HammerfestPonies web_responses;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_conversion() const { return conversion; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_conversion() { return conversion; }
        void set_conversion(const LivingstoneSouthernWhiteFacedOwl & value) { this->conversion = value; }

        const HammerfestPonies & get_graphs() const { return graphs; }
        HammerfestPonies & get_mutable_graphs() { return graphs; }
        void set_graphs(const HammerfestPonies & value) { this->graphs = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_externalized_properties() const { return externalized_properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_externalized_properties() { return externalized_properties; }
        void set_externalized_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->externalized_properties = value; }

        const HammerfestPonies & get_artifacts() const { return artifacts; }
        HammerfestPonies & get_mutable_artifacts() { return artifacts; }
        void set_artifacts(const HammerfestPonies & value) { this->artifacts = value; }

        const HammerfestPonies & get_invocations() const { return invocations; }
        HammerfestPonies & get_mutable_invocations() { return invocations; }
        void set_invocations(const HammerfestPonies & value) { this->invocations = value; }

        const HammerfestPonies & get_logical_locations() const { return logical_locations; }
        HammerfestPonies & get_mutable_logical_locations() { return logical_locations; }
        void set_logical_locations(const HammerfestPonies & value) { this->logical_locations = value; }

        const HammerfestPonies & get_thread_flow_locations() const { return thread_flow_locations; }
        HammerfestPonies & get_mutable_thread_flow_locations() { return thread_flow_locations; }
        void set_thread_flow_locations(const HammerfestPonies & value) { this->thread_flow_locations = value; }

        const HammerfestPonies & get_results() const { return results; }
        HammerfestPonies & get_mutable_results() { return results; }
        void set_results(const HammerfestPonies & value) { this->results = value; }

        const HammerfestPonies & get_taxonomies() const { return taxonomies; }
        HammerfestPonies & get_mutable_taxonomies() { return taxonomies; }
        void set_taxonomies(const HammerfestPonies & value) { this->taxonomies = value; }

        const HammerfestPonies & get_addresses() const { return addresses; }
        HammerfestPonies & get_mutable_addresses() { return addresses; }
        void set_addresses(const HammerfestPonies & value) { this->addresses = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_driver() const { return driver; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_driver() { return driver; }
        void set_driver(const LivingstoneSouthernWhiteFacedOwl & value) { this->driver = value; }

        const HammerfestPonies & get_extensions() const { return extensions; }
        HammerfestPonies & get_mutable_extensions() { return extensions; }
        void set_extensions(const HammerfestPonies & value) { this->extensions = value; }

        const HammerfestPonies & get_policies() const { return policies; }
        HammerfestPonies & get_mutable_policies() { return policies; }
        void set_policies(const HammerfestPonies & value) { this->policies = value; }

        const HammerfestPonies & get_translations() const { return translations; }
        HammerfestPonies & get_mutable_translations() { return translations; }
        void set_translations(const HammerfestPonies & value) { this->translations = value; }

        const HammerfestPonies & get_web_requests() const { return web_requests; }
        HammerfestPonies & get_mutable_web_requests() { return web_requests; }
        void set_web_requests(const HammerfestPonies & value) { this->web_requests = value; }

        const HammerfestPonies & get_web_responses() const { return web_responses; }
        HammerfestPonies & get_mutable_web_responses() { return web_responses; }
        void set_web_responses(const HammerfestPonies & value) { this->web_responses = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ExternalPropertyFileReferences {
        public:
        ExternalPropertyFileReferences() = default;
        virtual ~ExternalPropertyFileReferences() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ExternalPropertyFileReferencesProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ExternalPropertyFileReferencesProperties & get_properties() const { return properties; }
        ExternalPropertyFileReferencesProperties & get_mutable_properties() { return properties; }
        void set_properties(const ExternalPropertyFileReferencesProperties & value) { this->properties = value; }
    };

    class FixProperties {
        public:
        FixProperties() = default;
        virtual ~FixProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl description;
        HammerfestPonies artifact_changes;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_description() const { return description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_description() { return description; }
        void set_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->description = value; }

        const HammerfestPonies & get_artifact_changes() const { return artifact_changes; }
        HammerfestPonies & get_mutable_artifact_changes() { return artifact_changes; }
        void set_artifact_changes(const HammerfestPonies & value) { this->artifact_changes = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Fix {
        public:
        Fix() = default;
        virtual ~Fix() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        FixProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const FixProperties & get_properties() const { return properties; }
        FixProperties & get_mutable_properties() { return properties; }
        void set_properties(const FixProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class GraphProperties {
        public:
        GraphProperties() = default;
        virtual ~GraphProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl description;
        HammerfestPonies nodes;
        HammerfestPonies edges;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_description() const { return description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_description() { return description; }
        void set_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->description = value; }

        const HammerfestPonies & get_nodes() const { return nodes; }
        HammerfestPonies & get_mutable_nodes() { return nodes; }
        void set_nodes(const HammerfestPonies & value) { this->nodes = value; }

        const HammerfestPonies & get_edges() const { return edges; }
        HammerfestPonies & get_mutable_edges() { return edges; }
        void set_edges(const HammerfestPonies & value) { this->edges = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Graph {
        public:
        Graph() = default;
        virtual ~Graph() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        GraphProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const GraphProperties & get_properties() const { return properties; }
        GraphProperties & get_mutable_properties() { return properties; }
        void set_properties(const GraphProperties & value) { this->properties = value; }
    };

    class GraphTraversalProperties {
        public:
        GraphTraversalProperties() = default;
        virtual ~GraphTraversalProperties() = default;

        private:
        PuneHedgehog run_graph_index;
        PuneHedgehog result_graph_index;
        LivingstoneSouthernWhiteFacedOwl description;
        FinalState initial_state;
        FinalState immutable_state;
        HammerfestPonies edge_traversals;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const PuneHedgehog & get_run_graph_index() const { return run_graph_index; }
        PuneHedgehog & get_mutable_run_graph_index() { return run_graph_index; }
        void set_run_graph_index(const PuneHedgehog & value) { this->run_graph_index = value; }

        const PuneHedgehog & get_result_graph_index() const { return result_graph_index; }
        PuneHedgehog & get_mutable_result_graph_index() { return result_graph_index; }
        void set_result_graph_index(const PuneHedgehog & value) { this->result_graph_index = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_description() const { return description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_description() { return description; }
        void set_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->description = value; }

        const FinalState & get_initial_state() const { return initial_state; }
        FinalState & get_mutable_initial_state() { return initial_state; }
        void set_initial_state(const FinalState & value) { this->initial_state = value; }

        const FinalState & get_immutable_state() const { return immutable_state; }
        FinalState & get_mutable_immutable_state() { return immutable_state; }
        void set_immutable_state(const FinalState & value) { this->immutable_state = value; }

        const HammerfestPonies & get_edge_traversals() const { return edge_traversals; }
        HammerfestPonies & get_mutable_edge_traversals() { return edge_traversals; }
        void set_edge_traversals(const HammerfestPonies & value) { this->edge_traversals = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class GraphTraversal {
        public:
        GraphTraversal() = default;
        virtual ~GraphTraversal() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        GraphTraversalProperties properties;
        std::vector<Of> one_of;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const GraphTraversalProperties & get_properties() const { return properties; }
        GraphTraversalProperties & get_mutable_properties() { return properties; }
        void set_properties(const GraphTraversalProperties & value) { this->properties = value; }

        const std::vector<Of> & get_one_of() const { return one_of; }
        std::vector<Of> & get_mutable_one_of() { return one_of; }
        void set_one_of(const std::vector<Of> & value) { this->one_of = value; }
    };

    class Arguments {
        public:
        Arguments() = default;
        virtual ~Arguments() = default;

        private:
        std::string description;
        FluffyType type;
        std::shared_ptr<int64_t> min_items;
        bool unique_items;
        AdditionalProperties items;
        std::shared_ptr<std::vector<std::string>> arguments_default;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const FluffyType & get_type() const { return type; }
        FluffyType & get_mutable_type() { return type; }
        void set_type(const FluffyType & value) { this->type = value; }

        std::shared_ptr<int64_t> get_min_items() const { return min_items; }
        void set_min_items(std::shared_ptr<int64_t> value) { this->min_items = value; }

        const bool & get_unique_items() const { return unique_items; }
        bool & get_mutable_unique_items() { return unique_items; }
        void set_unique_items(const bool & value) { this->unique_items = value; }

        const AdditionalProperties & get_items() const { return items; }
        AdditionalProperties & get_mutable_items() { return items; }
        void set_items(const AdditionalProperties & value) { this->items = value; }

        std::shared_ptr<std::vector<std::string>> get_arguments_default() const { return arguments_default; }
        void set_arguments_default(std::shared_ptr<std::vector<std::string>> value) { this->arguments_default = value; }
    };

    class InvocationProperties {
        public:
        InvocationProperties() = default;
        virtual ~InvocationProperties() = default;

        private:
        TartuGecko command_line;
        Arguments arguments;
        HammerfestPonies response_files;
        Schema start_time_utc;
        Schema end_time_utc;
        TartuGecko exit_code;
        HammerfestPonies rule_configuration_overrides;
        HammerfestPonies notification_configuration_overrides;
        HammerfestPonies tool_execution_notifications;
        HammerfestPonies tool_configuration_notifications;
        TartuGecko exit_code_description;
        TartuGecko exit_signal_name;
        TartuGecko exit_signal_number;
        TartuGecko process_start_failure_message;
        TartuGecko execution_successful;
        TartuGecko machine;
        TartuGecko account;
        TartuGecko process_id;
        LivingstoneSouthernWhiteFacedOwl executable_location;
        LivingstoneSouthernWhiteFacedOwl working_directory;
        Hashes environment_variables;
        LivingstoneSouthernWhiteFacedOwl stdin;
        LivingstoneSouthernWhiteFacedOwl stdout;
        LivingstoneSouthernWhiteFacedOwl stderr;
        LivingstoneSouthernWhiteFacedOwl stdout_stderr;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_command_line() const { return command_line; }
        TartuGecko & get_mutable_command_line() { return command_line; }
        void set_command_line(const TartuGecko & value) { this->command_line = value; }

        const Arguments & get_arguments() const { return arguments; }
        Arguments & get_mutable_arguments() { return arguments; }
        void set_arguments(const Arguments & value) { this->arguments = value; }

        const HammerfestPonies & get_response_files() const { return response_files; }
        HammerfestPonies & get_mutable_response_files() { return response_files; }
        void set_response_files(const HammerfestPonies & value) { this->response_files = value; }

        const Schema & get_start_time_utc() const { return start_time_utc; }
        Schema & get_mutable_start_time_utc() { return start_time_utc; }
        void set_start_time_utc(const Schema & value) { this->start_time_utc = value; }

        const Schema & get_end_time_utc() const { return end_time_utc; }
        Schema & get_mutable_end_time_utc() { return end_time_utc; }
        void set_end_time_utc(const Schema & value) { this->end_time_utc = value; }

        const TartuGecko & get_exit_code() const { return exit_code; }
        TartuGecko & get_mutable_exit_code() { return exit_code; }
        void set_exit_code(const TartuGecko & value) { this->exit_code = value; }

        const HammerfestPonies & get_rule_configuration_overrides() const { return rule_configuration_overrides; }
        HammerfestPonies & get_mutable_rule_configuration_overrides() { return rule_configuration_overrides; }
        void set_rule_configuration_overrides(const HammerfestPonies & value) { this->rule_configuration_overrides = value; }

        const HammerfestPonies & get_notification_configuration_overrides() const { return notification_configuration_overrides; }
        HammerfestPonies & get_mutable_notification_configuration_overrides() { return notification_configuration_overrides; }
        void set_notification_configuration_overrides(const HammerfestPonies & value) { this->notification_configuration_overrides = value; }

        const HammerfestPonies & get_tool_execution_notifications() const { return tool_execution_notifications; }
        HammerfestPonies & get_mutable_tool_execution_notifications() { return tool_execution_notifications; }
        void set_tool_execution_notifications(const HammerfestPonies & value) { this->tool_execution_notifications = value; }

        const HammerfestPonies & get_tool_configuration_notifications() const { return tool_configuration_notifications; }
        HammerfestPonies & get_mutable_tool_configuration_notifications() { return tool_configuration_notifications; }
        void set_tool_configuration_notifications(const HammerfestPonies & value) { this->tool_configuration_notifications = value; }

        const TartuGecko & get_exit_code_description() const { return exit_code_description; }
        TartuGecko & get_mutable_exit_code_description() { return exit_code_description; }
        void set_exit_code_description(const TartuGecko & value) { this->exit_code_description = value; }

        const TartuGecko & get_exit_signal_name() const { return exit_signal_name; }
        TartuGecko & get_mutable_exit_signal_name() { return exit_signal_name; }
        void set_exit_signal_name(const TartuGecko & value) { this->exit_signal_name = value; }

        const TartuGecko & get_exit_signal_number() const { return exit_signal_number; }
        TartuGecko & get_mutable_exit_signal_number() { return exit_signal_number; }
        void set_exit_signal_number(const TartuGecko & value) { this->exit_signal_number = value; }

        const TartuGecko & get_process_start_failure_message() const { return process_start_failure_message; }
        TartuGecko & get_mutable_process_start_failure_message() { return process_start_failure_message; }
        void set_process_start_failure_message(const TartuGecko & value) { this->process_start_failure_message = value; }

        const TartuGecko & get_execution_successful() const { return execution_successful; }
        TartuGecko & get_mutable_execution_successful() { return execution_successful; }
        void set_execution_successful(const TartuGecko & value) { this->execution_successful = value; }

        const TartuGecko & get_machine() const { return machine; }
        TartuGecko & get_mutable_machine() { return machine; }
        void set_machine(const TartuGecko & value) { this->machine = value; }

        const TartuGecko & get_account() const { return account; }
        TartuGecko & get_mutable_account() { return account; }
        void set_account(const TartuGecko & value) { this->account = value; }

        const TartuGecko & get_process_id() const { return process_id; }
        TartuGecko & get_mutable_process_id() { return process_id; }
        void set_process_id(const TartuGecko & value) { this->process_id = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_executable_location() const { return executable_location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_executable_location() { return executable_location; }
        void set_executable_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->executable_location = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_working_directory() const { return working_directory; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_working_directory() { return working_directory; }
        void set_working_directory(const LivingstoneSouthernWhiteFacedOwl & value) { this->working_directory = value; }

        const Hashes & get_environment_variables() const { return environment_variables; }
        Hashes & get_mutable_environment_variables() { return environment_variables; }
        void set_environment_variables(const Hashes & value) { this->environment_variables = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_stdin() const { return stdin; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_stdin() { return stdin; }
        void set_stdin(const LivingstoneSouthernWhiteFacedOwl & value) { this->stdin = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_stdout() const { return stdout; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_stdout() { return stdout; }
        void set_stdout(const LivingstoneSouthernWhiteFacedOwl & value) { this->stdout = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_stderr() const { return stderr; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_stderr() { return stderr; }
        void set_stderr(const LivingstoneSouthernWhiteFacedOwl & value) { this->stderr = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_stdout_stderr() const { return stdout_stderr; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_stdout_stderr() { return stdout_stderr; }
        void set_stdout_stderr(const LivingstoneSouthernWhiteFacedOwl & value) { this->stdout_stderr = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Invocation {
        public:
        Invocation() = default;
        virtual ~Invocation() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        InvocationProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const InvocationProperties & get_properties() const { return properties; }
        InvocationProperties & get_mutable_properties() { return properties; }
        void set_properties(const InvocationProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class LocationProperties {
        public:
        LocationProperties() = default;
        virtual ~LocationProperties() = default;

        private:
        PuneHedgehog id;
        LivingstoneSouthernWhiteFacedOwl physical_location;
        HammerfestPonies logical_locations;
        LivingstoneSouthernWhiteFacedOwl message;
        HammerfestPonies annotations;
        HammerfestPonies relationships;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const PuneHedgehog & get_id() const { return id; }
        PuneHedgehog & get_mutable_id() { return id; }
        void set_id(const PuneHedgehog & value) { this->id = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_physical_location() const { return physical_location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_physical_location() { return physical_location; }
        void set_physical_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->physical_location = value; }

        const HammerfestPonies & get_logical_locations() const { return logical_locations; }
        HammerfestPonies & get_mutable_logical_locations() { return logical_locations; }
        void set_logical_locations(const HammerfestPonies & value) { this->logical_locations = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_message() const { return message; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_message() { return message; }
        void set_message(const LivingstoneSouthernWhiteFacedOwl & value) { this->message = value; }

        const HammerfestPonies & get_annotations() const { return annotations; }
        HammerfestPonies & get_mutable_annotations() { return annotations; }
        void set_annotations(const HammerfestPonies & value) { this->annotations = value; }

        const HammerfestPonies & get_relationships() const { return relationships; }
        HammerfestPonies & get_mutable_relationships() { return relationships; }
        void set_relationships(const HammerfestPonies & value) { this->relationships = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Location {
        public:
        Location() = default;
        virtual ~Location() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        LocationProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const LocationProperties & get_properties() const { return properties; }
        LocationProperties & get_mutable_properties() { return properties; }
        void set_properties(const LocationProperties & value) { this->properties = value; }
    };

    class LocationRelationshipProperties {
        public:
        LocationRelationshipProperties() = default;
        virtual ~LocationRelationshipProperties() = default;

        private:
        PuneHedgehog target;
        Arguments kinds;
        LivingstoneSouthernWhiteFacedOwl description;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const PuneHedgehog & get_target() const { return target; }
        PuneHedgehog & get_mutable_target() { return target; }
        void set_target(const PuneHedgehog & value) { this->target = value; }

        const Arguments & get_kinds() const { return kinds; }
        Arguments & get_mutable_kinds() { return kinds; }
        void set_kinds(const Arguments & value) { this->kinds = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_description() const { return description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_description() { return description; }
        void set_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->description = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class LocationRelationship {
        public:
        LocationRelationship() = default;
        virtual ~LocationRelationship() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        LocationRelationshipProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const LocationRelationshipProperties & get_properties() const { return properties; }
        LocationRelationshipProperties & get_mutable_properties() { return properties; }
        void set_properties(const LocationRelationshipProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class LogicalLocationProperties {
        public:
        LogicalLocationProperties() = default;
        virtual ~LogicalLocationProperties() = default;

        private:
        TartuGecko name;
        PuneHedgehog index;
        TartuGecko fully_qualified_name;
        TartuGecko decorated_name;
        PuneHedgehog parent_index;
        TartuGecko kind;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_name() const { return name; }
        TartuGecko & get_mutable_name() { return name; }
        void set_name(const TartuGecko & value) { this->name = value; }

        const PuneHedgehog & get_index() const { return index; }
        PuneHedgehog & get_mutable_index() { return index; }
        void set_index(const PuneHedgehog & value) { this->index = value; }

        const TartuGecko & get_fully_qualified_name() const { return fully_qualified_name; }
        TartuGecko & get_mutable_fully_qualified_name() { return fully_qualified_name; }
        void set_fully_qualified_name(const TartuGecko & value) { this->fully_qualified_name = value; }

        const TartuGecko & get_decorated_name() const { return decorated_name; }
        TartuGecko & get_mutable_decorated_name() { return decorated_name; }
        void set_decorated_name(const TartuGecko & value) { this->decorated_name = value; }

        const PuneHedgehog & get_parent_index() const { return parent_index; }
        PuneHedgehog & get_mutable_parent_index() { return parent_index; }
        void set_parent_index(const PuneHedgehog & value) { this->parent_index = value; }

        const TartuGecko & get_kind() const { return kind; }
        TartuGecko & get_mutable_kind() { return kind; }
        void set_kind(const TartuGecko & value) { this->kind = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class LogicalLocation {
        public:
        LogicalLocation() = default;
        virtual ~LogicalLocation() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        LogicalLocationProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const LogicalLocationProperties & get_properties() const { return properties; }
        LogicalLocationProperties & get_mutable_properties() { return properties; }
        void set_properties(const LogicalLocationProperties & value) { this->properties = value; }
    };

    class MessageProperties {
        public:
        MessageProperties() = default;
        virtual ~MessageProperties() = default;

        private:
        TartuGecko text;
        TartuGecko markdown;
        TartuGecko id;
        Arguments arguments;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_text() const { return text; }
        TartuGecko & get_mutable_text() { return text; }
        void set_text(const TartuGecko & value) { this->text = value; }

        const TartuGecko & get_markdown() const { return markdown; }
        TartuGecko & get_mutable_markdown() { return markdown; }
        void set_markdown(const TartuGecko & value) { this->markdown = value; }

        const TartuGecko & get_id() const { return id; }
        TartuGecko & get_mutable_id() { return id; }
        void set_id(const TartuGecko & value) { this->id = value; }

        const Arguments & get_arguments() const { return arguments; }
        Arguments & get_mutable_arguments() { return arguments; }
        void set_arguments(const Arguments & value) { this->arguments = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Message {
        public:
        Message() = default;
        virtual ~Message() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        MessageProperties properties;
        std::vector<Of> any_of;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const MessageProperties & get_properties() const { return properties; }
        MessageProperties & get_mutable_properties() { return properties; }
        void set_properties(const MessageProperties & value) { this->properties = value; }

        const std::vector<Of> & get_any_of() const { return any_of; }
        std::vector<Of> & get_mutable_any_of() { return any_of; }
        void set_any_of(const std::vector<Of> & value) { this->any_of = value; }
    };

    class MultiformatMessageStringProperties {
        public:
        MultiformatMessageStringProperties() = default;
        virtual ~MultiformatMessageStringProperties() = default;

        private:
        TartuGecko text;
        TartuGecko markdown;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_text() const { return text; }
        TartuGecko & get_mutable_text() { return text; }
        void set_text(const TartuGecko & value) { this->text = value; }

        const TartuGecko & get_markdown() const { return markdown; }
        TartuGecko & get_mutable_markdown() { return markdown; }
        void set_markdown(const TartuGecko & value) { this->markdown = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class MultiformatMessageString {
        public:
        MultiformatMessageString() = default;
        virtual ~MultiformatMessageString() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        MultiformatMessageStringProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const MultiformatMessageStringProperties & get_properties() const { return properties; }
        MultiformatMessageStringProperties & get_mutable_properties() { return properties; }
        void set_properties(const MultiformatMessageStringProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class NodeProperties {
        public:
        NodeProperties() = default;
        virtual ~NodeProperties() = default;

        private:
        TartuGecko id;
        LivingstoneSouthernWhiteFacedOwl label;
        LivingstoneSouthernWhiteFacedOwl location;
        HammerfestPonies children;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_id() const { return id; }
        TartuGecko & get_mutable_id() { return id; }
        void set_id(const TartuGecko & value) { this->id = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_label() const { return label; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_label() { return label; }
        void set_label(const LivingstoneSouthernWhiteFacedOwl & value) { this->label = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_location() const { return location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_location() { return location; }
        void set_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->location = value; }

        const HammerfestPonies & get_children() const { return children; }
        HammerfestPonies & get_mutable_children() { return children; }
        void set_children(const HammerfestPonies & value) { this->children = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Node {
        public:
        Node() = default;
        virtual ~Node() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        NodeProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const NodeProperties & get_properties() const { return properties; }
        NodeProperties & get_mutable_properties() { return properties; }
        void set_properties(const NodeProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class Level {
        public:
        Level() = default;
        virtual ~Level() = default;

        private:
        std::string description;
        std::string level_default;
        std::vector<std::string> level_enum;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_level_default() const { return level_default; }
        std::string & get_mutable_level_default() { return level_default; }
        void set_level_default(const std::string & value) { this->level_default = value; }

        const std::vector<std::string> & get_level_enum() const { return level_enum; }
        std::vector<std::string> & get_mutable_level_enum() { return level_enum; }
        void set_level_enum(const std::vector<std::string> & value) { this->level_enum = value; }
    };

    class NotificationProperties {
        public:
        NotificationProperties() = default;
        virtual ~NotificationProperties() = default;

        private:
        HammerfestPonies locations;
        LivingstoneSouthernWhiteFacedOwl message;
        Level level;
        TartuGecko thread_id;
        Schema time_utc;
        LivingstoneSouthernWhiteFacedOwl exception;
        LivingstoneSouthernWhiteFacedOwl descriptor;
        LivingstoneSouthernWhiteFacedOwl associated_rule;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const HammerfestPonies & get_locations() const { return locations; }
        HammerfestPonies & get_mutable_locations() { return locations; }
        void set_locations(const HammerfestPonies & value) { this->locations = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_message() const { return message; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_message() { return message; }
        void set_message(const LivingstoneSouthernWhiteFacedOwl & value) { this->message = value; }

        const Level & get_level() const { return level; }
        Level & get_mutable_level() { return level; }
        void set_level(const Level & value) { this->level = value; }

        const TartuGecko & get_thread_id() const { return thread_id; }
        TartuGecko & get_mutable_thread_id() { return thread_id; }
        void set_thread_id(const TartuGecko & value) { this->thread_id = value; }

        const Schema & get_time_utc() const { return time_utc; }
        Schema & get_mutable_time_utc() { return time_utc; }
        void set_time_utc(const Schema & value) { this->time_utc = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_exception() const { return exception; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_exception() { return exception; }
        void set_exception(const LivingstoneSouthernWhiteFacedOwl & value) { this->exception = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_descriptor() const { return descriptor; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_descriptor() { return descriptor; }
        void set_descriptor(const LivingstoneSouthernWhiteFacedOwl & value) { this->descriptor = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_associated_rule() const { return associated_rule; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_associated_rule() { return associated_rule; }
        void set_associated_rule(const LivingstoneSouthernWhiteFacedOwl & value) { this->associated_rule = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Notification {
        public:
        Notification() = default;
        virtual ~Notification() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        NotificationProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const NotificationProperties & get_properties() const { return properties; }
        NotificationProperties & get_mutable_properties() { return properties; }
        void set_properties(const NotificationProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class PhysicalLocationProperties {
        public:
        PhysicalLocationProperties() = default;
        virtual ~PhysicalLocationProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl address;
        LivingstoneSouthernWhiteFacedOwl artifact_location;
        LivingstoneSouthernWhiteFacedOwl region;
        LivingstoneSouthernWhiteFacedOwl context_region;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_address() const { return address; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_address() { return address; }
        void set_address(const LivingstoneSouthernWhiteFacedOwl & value) { this->address = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_artifact_location() const { return artifact_location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_artifact_location() { return artifact_location; }
        void set_artifact_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->artifact_location = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_region() const { return region; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_region() { return region; }
        void set_region(const LivingstoneSouthernWhiteFacedOwl & value) { this->region = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_context_region() const { return context_region; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_context_region() { return context_region; }
        void set_context_region(const LivingstoneSouthernWhiteFacedOwl & value) { this->context_region = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class PhysicalLocation {
        public:
        PhysicalLocation() = default;
        virtual ~PhysicalLocation() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        PhysicalLocationProperties properties;
        std::vector<Of> any_of;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const PhysicalLocationProperties & get_properties() const { return properties; }
        PhysicalLocationProperties & get_mutable_properties() { return properties; }
        void set_properties(const PhysicalLocationProperties & value) { this->properties = value; }

        const std::vector<Of> & get_any_of() const { return any_of; }
        std::vector<Of> & get_mutable_any_of() { return any_of; }
        void set_any_of(const std::vector<Of> & value) { this->any_of = value; }
    };

    class PropertyBagProperties {
        public:
        PropertyBagProperties() = default;
        virtual ~PropertyBagProperties() = default;

        private:
        Arguments tags;

        public:
        const Arguments & get_tags() const { return tags; }
        Arguments & get_mutable_tags() { return tags; }
        void set_tags(const Arguments & value) { this->tags = value; }
    };

    class PropertyBag {
        public:
        PropertyBag() = default;
        virtual ~PropertyBag() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        PropertyBagProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const PropertyBagProperties & get_properties() const { return properties; }
        PropertyBagProperties & get_mutable_properties() { return properties; }
        void set_properties(const PropertyBagProperties & value) { this->properties = value; }
    };

    class RectangleProperties {
        public:
        RectangleProperties() = default;
        virtual ~RectangleProperties() = default;

        private:
        TartuGecko top;
        TartuGecko left;
        TartuGecko bottom;
        TartuGecko right;
        LivingstoneSouthernWhiteFacedOwl message;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_top() const { return top; }
        TartuGecko & get_mutable_top() { return top; }
        void set_top(const TartuGecko & value) { this->top = value; }

        const TartuGecko & get_left() const { return left; }
        TartuGecko & get_mutable_left() { return left; }
        void set_left(const TartuGecko & value) { this->left = value; }

        const TartuGecko & get_bottom() const { return bottom; }
        TartuGecko & get_mutable_bottom() { return bottom; }
        void set_bottom(const TartuGecko & value) { this->bottom = value; }

        const TartuGecko & get_right() const { return right; }
        TartuGecko & get_mutable_right() { return right; }
        void set_right(const TartuGecko & value) { this->right = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_message() const { return message; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_message() { return message; }
        void set_message(const LivingstoneSouthernWhiteFacedOwl & value) { this->message = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Rectangle {
        public:
        Rectangle() = default;
        virtual ~Rectangle() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        RectangleProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const RectangleProperties & get_properties() const { return properties; }
        RectangleProperties & get_mutable_properties() { return properties; }
        void set_properties(const RectangleProperties & value) { this->properties = value; }
    };

    class RegionProperties {
        public:
        RegionProperties() = default;
        virtual ~RegionProperties() = default;

        private:
        PuneHedgehog start_line;
        PuneHedgehog start_column;
        PuneHedgehog end_line;
        PuneHedgehog end_column;
        PuneHedgehog char_offset;
        PuneHedgehog char_length;
        PuneHedgehog byte_offset;
        PuneHedgehog byte_length;
        LivingstoneSouthernWhiteFacedOwl snippet;
        LivingstoneSouthernWhiteFacedOwl message;
        TartuGecko source_language;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const PuneHedgehog & get_start_line() const { return start_line; }
        PuneHedgehog & get_mutable_start_line() { return start_line; }
        void set_start_line(const PuneHedgehog & value) { this->start_line = value; }

        const PuneHedgehog & get_start_column() const { return start_column; }
        PuneHedgehog & get_mutable_start_column() { return start_column; }
        void set_start_column(const PuneHedgehog & value) { this->start_column = value; }

        const PuneHedgehog & get_end_line() const { return end_line; }
        PuneHedgehog & get_mutable_end_line() { return end_line; }
        void set_end_line(const PuneHedgehog & value) { this->end_line = value; }

        const PuneHedgehog & get_end_column() const { return end_column; }
        PuneHedgehog & get_mutable_end_column() { return end_column; }
        void set_end_column(const PuneHedgehog & value) { this->end_column = value; }

        const PuneHedgehog & get_char_offset() const { return char_offset; }
        PuneHedgehog & get_mutable_char_offset() { return char_offset; }
        void set_char_offset(const PuneHedgehog & value) { this->char_offset = value; }

        const PuneHedgehog & get_char_length() const { return char_length; }
        PuneHedgehog & get_mutable_char_length() { return char_length; }
        void set_char_length(const PuneHedgehog & value) { this->char_length = value; }

        const PuneHedgehog & get_byte_offset() const { return byte_offset; }
        PuneHedgehog & get_mutable_byte_offset() { return byte_offset; }
        void set_byte_offset(const PuneHedgehog & value) { this->byte_offset = value; }

        const PuneHedgehog & get_byte_length() const { return byte_length; }
        PuneHedgehog & get_mutable_byte_length() { return byte_length; }
        void set_byte_length(const PuneHedgehog & value) { this->byte_length = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_snippet() const { return snippet; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_snippet() { return snippet; }
        void set_snippet(const LivingstoneSouthernWhiteFacedOwl & value) { this->snippet = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_message() const { return message; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_message() { return message; }
        void set_message(const LivingstoneSouthernWhiteFacedOwl & value) { this->message = value; }

        const TartuGecko & get_source_language() const { return source_language; }
        TartuGecko & get_mutable_source_language() { return source_language; }
        void set_source_language(const TartuGecko & value) { this->source_language = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Region {
        public:
        Region() = default;
        virtual ~Region() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        RegionProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const RegionProperties & get_properties() const { return properties; }
        RegionProperties & get_mutable_properties() { return properties; }
        void set_properties(const RegionProperties & value) { this->properties = value; }
    };

    class ReplacementProperties {
        public:
        ReplacementProperties() = default;
        virtual ~ReplacementProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl deleted_region;
        LivingstoneSouthernWhiteFacedOwl inserted_content;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_deleted_region() const { return deleted_region; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_deleted_region() { return deleted_region; }
        void set_deleted_region(const LivingstoneSouthernWhiteFacedOwl & value) { this->deleted_region = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_inserted_content() const { return inserted_content; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_inserted_content() { return inserted_content; }
        void set_inserted_content(const LivingstoneSouthernWhiteFacedOwl & value) { this->inserted_content = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Replacement {
        public:
        Replacement() = default;
        virtual ~Replacement() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ReplacementProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ReplacementProperties & get_properties() const { return properties; }
        ReplacementProperties & get_mutable_properties() { return properties; }
        void set_properties(const ReplacementProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class Enabled {
        public:
        Enabled() = default;
        virtual ~Enabled() = default;

        private:
        std::string description;
        PurpleType type;
        bool enabled_default;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const PurpleType & get_type() const { return type; }
        PurpleType & get_mutable_type() { return type; }
        void set_type(const PurpleType & value) { this->type = value; }

        const bool & get_enabled_default() const { return enabled_default; }
        bool & get_mutable_enabled_default() { return enabled_default; }
        void set_enabled_default(const bool & value) { this->enabled_default = value; }
    };

    class ReportingConfigurationProperties {
        public:
        ReportingConfigurationProperties() = default;
        virtual ~ReportingConfigurationProperties() = default;

        private:
        Enabled enabled;
        Level level;
        PuneHedgehog rank;
        LivingstoneSouthernWhiteFacedOwl parameters;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const Enabled & get_enabled() const { return enabled; }
        Enabled & get_mutable_enabled() { return enabled; }
        void set_enabled(const Enabled & value) { this->enabled = value; }

        const Level & get_level() const { return level; }
        Level & get_mutable_level() { return level; }
        void set_level(const Level & value) { this->level = value; }

        const PuneHedgehog & get_rank() const { return rank; }
        PuneHedgehog & get_mutable_rank() { return rank; }
        void set_rank(const PuneHedgehog & value) { this->rank = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_parameters() const { return parameters; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_parameters() { return parameters; }
        void set_parameters(const LivingstoneSouthernWhiteFacedOwl & value) { this->parameters = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ReportingConfiguration {
        public:
        ReportingConfiguration() = default;
        virtual ~ReportingConfiguration() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        ReportingConfigurationProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const ReportingConfigurationProperties & get_properties() const { return properties; }
        ReportingConfigurationProperties & get_mutable_properties() { return properties; }
        void set_properties(const ReportingConfigurationProperties & value) { this->properties = value; }
    };

    class DeprecatedGuidsItems {
        public:
        DeprecatedGuidsItems() = default;
        virtual ~DeprecatedGuidsItems() = default;

        private:
        PurpleType type;
        std::string pattern;

        public:
        const PurpleType & get_type() const { return type; }
        PurpleType & get_mutable_type() { return type; }
        void set_type(const PurpleType & value) { this->type = value; }

        const std::string & get_pattern() const { return pattern; }
        std::string & get_mutable_pattern() { return pattern; }
        void set_pattern(const std::string & value) { this->pattern = value; }
    };

    class DeprecatedGuids {
        public:
        DeprecatedGuids() = default;
        virtual ~DeprecatedGuids() = default;

        private:
        std::string description;
        FluffyType type;
        int64_t min_items;
        bool unique_items;
        DeprecatedGuidsItems items;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const FluffyType & get_type() const { return type; }
        FluffyType & get_mutable_type() { return type; }
        void set_type(const FluffyType & value) { this->type = value; }

        const int64_t & get_min_items() const { return min_items; }
        int64_t & get_mutable_min_items() { return min_items; }
        void set_min_items(const int64_t & value) { this->min_items = value; }

        const bool & get_unique_items() const { return unique_items; }
        bool & get_mutable_unique_items() { return unique_items; }
        void set_unique_items(const bool & value) { this->unique_items = value; }

        const DeprecatedGuidsItems & get_items() const { return items; }
        DeprecatedGuidsItems & get_mutable_items() { return items; }
        void set_items(const DeprecatedGuidsItems & value) { this->items = value; }
    };

    class ReportingDescriptorProperties {
        public:
        ReportingDescriptorProperties() = default;
        virtual ~ReportingDescriptorProperties() = default;

        private:
        TartuGecko id;
        Arguments deprecated_ids;
        MimeType guid;
        DeprecatedGuids deprecated_guids;
        TartuGecko name;
        Arguments deprecated_names;
        LivingstoneSouthernWhiteFacedOwl short_description;
        LivingstoneSouthernWhiteFacedOwl full_description;
        FinalState message_strings;
        LivingstoneSouthernWhiteFacedOwl default_configuration;
        Schema help_uri;
        LivingstoneSouthernWhiteFacedOwl help;
        HammerfestPonies relationships;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_id() const { return id; }
        TartuGecko & get_mutable_id() { return id; }
        void set_id(const TartuGecko & value) { this->id = value; }

        const Arguments & get_deprecated_ids() const { return deprecated_ids; }
        Arguments & get_mutable_deprecated_ids() { return deprecated_ids; }
        void set_deprecated_ids(const Arguments & value) { this->deprecated_ids = value; }

        const MimeType & get_guid() const { return guid; }
        MimeType & get_mutable_guid() { return guid; }
        void set_guid(const MimeType & value) { this->guid = value; }

        const DeprecatedGuids & get_deprecated_guids() const { return deprecated_guids; }
        DeprecatedGuids & get_mutable_deprecated_guids() { return deprecated_guids; }
        void set_deprecated_guids(const DeprecatedGuids & value) { this->deprecated_guids = value; }

        const TartuGecko & get_name() const { return name; }
        TartuGecko & get_mutable_name() { return name; }
        void set_name(const TartuGecko & value) { this->name = value; }

        const Arguments & get_deprecated_names() const { return deprecated_names; }
        Arguments & get_mutable_deprecated_names() { return deprecated_names; }
        void set_deprecated_names(const Arguments & value) { this->deprecated_names = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_short_description() const { return short_description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_short_description() { return short_description; }
        void set_short_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->short_description = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_full_description() const { return full_description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_full_description() { return full_description; }
        void set_full_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->full_description = value; }

        const FinalState & get_message_strings() const { return message_strings; }
        FinalState & get_mutable_message_strings() { return message_strings; }
        void set_message_strings(const FinalState & value) { this->message_strings = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_default_configuration() const { return default_configuration; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_default_configuration() { return default_configuration; }
        void set_default_configuration(const LivingstoneSouthernWhiteFacedOwl & value) { this->default_configuration = value; }

        const Schema & get_help_uri() const { return help_uri; }
        Schema & get_mutable_help_uri() { return help_uri; }
        void set_help_uri(const Schema & value) { this->help_uri = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_help() const { return help; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_help() { return help; }
        void set_help(const LivingstoneSouthernWhiteFacedOwl & value) { this->help = value; }

        const HammerfestPonies & get_relationships() const { return relationships; }
        HammerfestPonies & get_mutable_relationships() { return relationships; }
        void set_relationships(const HammerfestPonies & value) { this->relationships = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ReportingDescriptor {
        public:
        ReportingDescriptor() = default;
        virtual ~ReportingDescriptor() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ReportingDescriptorProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ReportingDescriptorProperties & get_properties() const { return properties; }
        ReportingDescriptorProperties & get_mutable_properties() { return properties; }
        void set_properties(const ReportingDescriptorProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ReportingDescriptorReferenceProperties {
        public:
        ReportingDescriptorReferenceProperties() = default;
        virtual ~ReportingDescriptorReferenceProperties() = default;

        private:
        TartuGecko id;
        PuneHedgehog index;
        MimeType guid;
        LivingstoneSouthernWhiteFacedOwl tool_component;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_id() const { return id; }
        TartuGecko & get_mutable_id() { return id; }
        void set_id(const TartuGecko & value) { this->id = value; }

        const PuneHedgehog & get_index() const { return index; }
        PuneHedgehog & get_mutable_index() { return index; }
        void set_index(const PuneHedgehog & value) { this->index = value; }

        const MimeType & get_guid() const { return guid; }
        MimeType & get_mutable_guid() { return guid; }
        void set_guid(const MimeType & value) { this->guid = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_tool_component() const { return tool_component; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_tool_component() { return tool_component; }
        void set_tool_component(const LivingstoneSouthernWhiteFacedOwl & value) { this->tool_component = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ReportingDescriptorReference {
        public:
        ReportingDescriptorReference() = default;
        virtual ~ReportingDescriptorReference() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        ReportingDescriptorReferenceProperties properties;
        std::vector<Of> any_of;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const ReportingDescriptorReferenceProperties & get_properties() const { return properties; }
        ReportingDescriptorReferenceProperties & get_mutable_properties() { return properties; }
        void set_properties(const ReportingDescriptorReferenceProperties & value) { this->properties = value; }

        const std::vector<Of> & get_any_of() const { return any_of; }
        std::vector<Of> & get_mutable_any_of() { return any_of; }
        void set_any_of(const std::vector<Of> & value) { this->any_of = value; }
    };

    class ReportingDescriptorRelationshipProperties {
        public:
        ReportingDescriptorRelationshipProperties() = default;
        virtual ~ReportingDescriptorRelationshipProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl target;
        Arguments kinds;
        LivingstoneSouthernWhiteFacedOwl description;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_target() const { return target; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_target() { return target; }
        void set_target(const LivingstoneSouthernWhiteFacedOwl & value) { this->target = value; }

        const Arguments & get_kinds() const { return kinds; }
        Arguments & get_mutable_kinds() { return kinds; }
        void set_kinds(const Arguments & value) { this->kinds = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_description() const { return description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_description() { return description; }
        void set_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->description = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ReportingDescriptorRelationship {
        public:
        ReportingDescriptorRelationship() = default;
        virtual ~ReportingDescriptorRelationship() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        ReportingDescriptorRelationshipProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const ReportingDescriptorRelationshipProperties & get_properties() const { return properties; }
        ReportingDescriptorRelationshipProperties & get_mutable_properties() { return properties; }
        void set_properties(const ReportingDescriptorRelationshipProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class WorkItemUrisItems {
        public:
        WorkItemUrisItems() = default;
        virtual ~WorkItemUrisItems() = default;

        private:
        PurpleType type;
        Format format;

        public:
        const PurpleType & get_type() const { return type; }
        PurpleType & get_mutable_type() { return type; }
        void set_type(const PurpleType & value) { this->type = value; }

        const Format & get_format() const { return format; }
        Format & get_mutable_format() { return format; }
        void set_format(const Format & value) { this->format = value; }
    };

    class WorkItemUris {
        public:
        WorkItemUris() = default;
        virtual ~WorkItemUris() = default;

        private:
        std::string description;
        FluffyType type;
        int64_t min_items;
        bool unique_items;
        WorkItemUrisItems items;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const FluffyType & get_type() const { return type; }
        FluffyType & get_mutable_type() { return type; }
        void set_type(const FluffyType & value) { this->type = value; }

        const int64_t & get_min_items() const { return min_items; }
        int64_t & get_mutable_min_items() { return min_items; }
        void set_min_items(const int64_t & value) { this->min_items = value; }

        const bool & get_unique_items() const { return unique_items; }
        bool & get_mutable_unique_items() { return unique_items; }
        void set_unique_items(const bool & value) { this->unique_items = value; }

        const WorkItemUrisItems & get_items() const { return items; }
        WorkItemUrisItems & get_mutable_items() { return items; }
        void set_items(const WorkItemUrisItems & value) { this->items = value; }
    };

    class ResultProperties {
        public:
        ResultProperties() = default;
        virtual ~ResultProperties() = default;

        private:
        TartuGecko rule_id;
        PuneHedgehog rule_index;
        LivingstoneSouthernWhiteFacedOwl rule;
        Level kind;
        Level level;
        LivingstoneSouthernWhiteFacedOwl message;
        LivingstoneSouthernWhiteFacedOwl analysis_target;
        HammerfestPonies locations;
        MimeType guid;
        MimeType correlation_guid;
        PuneHedgehog occurrence_count;
        Hashes partial_fingerprints;
        Hashes fingerprints;
        HammerfestPonies stacks;
        HammerfestPonies code_flows;
        HammerfestPonies graphs;
        HammerfestPonies graph_traversals;
        HammerfestPonies related_locations;
        HammerfestPonies suppressions;
        Version baseline_state;
        PuneHedgehog rank;
        HammerfestPonies attachments;
        Schema hosted_viewer_uri;
        WorkItemUris work_item_uris;
        LivingstoneSouthernWhiteFacedOwl provenance;
        HammerfestPonies fixes;
        HammerfestPonies taxa;
        LivingstoneSouthernWhiteFacedOwl web_request;
        LivingstoneSouthernWhiteFacedOwl web_response;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_rule_id() const { return rule_id; }
        TartuGecko & get_mutable_rule_id() { return rule_id; }
        void set_rule_id(const TartuGecko & value) { this->rule_id = value; }

        const PuneHedgehog & get_rule_index() const { return rule_index; }
        PuneHedgehog & get_mutable_rule_index() { return rule_index; }
        void set_rule_index(const PuneHedgehog & value) { this->rule_index = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_rule() const { return rule; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_rule() { return rule; }
        void set_rule(const LivingstoneSouthernWhiteFacedOwl & value) { this->rule = value; }

        const Level & get_kind() const { return kind; }
        Level & get_mutable_kind() { return kind; }
        void set_kind(const Level & value) { this->kind = value; }

        const Level & get_level() const { return level; }
        Level & get_mutable_level() { return level; }
        void set_level(const Level & value) { this->level = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_message() const { return message; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_message() { return message; }
        void set_message(const LivingstoneSouthernWhiteFacedOwl & value) { this->message = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_analysis_target() const { return analysis_target; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_analysis_target() { return analysis_target; }
        void set_analysis_target(const LivingstoneSouthernWhiteFacedOwl & value) { this->analysis_target = value; }

        const HammerfestPonies & get_locations() const { return locations; }
        HammerfestPonies & get_mutable_locations() { return locations; }
        void set_locations(const HammerfestPonies & value) { this->locations = value; }

        const MimeType & get_guid() const { return guid; }
        MimeType & get_mutable_guid() { return guid; }
        void set_guid(const MimeType & value) { this->guid = value; }

        const MimeType & get_correlation_guid() const { return correlation_guid; }
        MimeType & get_mutable_correlation_guid() { return correlation_guid; }
        void set_correlation_guid(const MimeType & value) { this->correlation_guid = value; }

        const PuneHedgehog & get_occurrence_count() const { return occurrence_count; }
        PuneHedgehog & get_mutable_occurrence_count() { return occurrence_count; }
        void set_occurrence_count(const PuneHedgehog & value) { this->occurrence_count = value; }

        const Hashes & get_partial_fingerprints() const { return partial_fingerprints; }
        Hashes & get_mutable_partial_fingerprints() { return partial_fingerprints; }
        void set_partial_fingerprints(const Hashes & value) { this->partial_fingerprints = value; }

        const Hashes & get_fingerprints() const { return fingerprints; }
        Hashes & get_mutable_fingerprints() { return fingerprints; }
        void set_fingerprints(const Hashes & value) { this->fingerprints = value; }

        const HammerfestPonies & get_stacks() const { return stacks; }
        HammerfestPonies & get_mutable_stacks() { return stacks; }
        void set_stacks(const HammerfestPonies & value) { this->stacks = value; }

        const HammerfestPonies & get_code_flows() const { return code_flows; }
        HammerfestPonies & get_mutable_code_flows() { return code_flows; }
        void set_code_flows(const HammerfestPonies & value) { this->code_flows = value; }

        const HammerfestPonies & get_graphs() const { return graphs; }
        HammerfestPonies & get_mutable_graphs() { return graphs; }
        void set_graphs(const HammerfestPonies & value) { this->graphs = value; }

        const HammerfestPonies & get_graph_traversals() const { return graph_traversals; }
        HammerfestPonies & get_mutable_graph_traversals() { return graph_traversals; }
        void set_graph_traversals(const HammerfestPonies & value) { this->graph_traversals = value; }

        const HammerfestPonies & get_related_locations() const { return related_locations; }
        HammerfestPonies & get_mutable_related_locations() { return related_locations; }
        void set_related_locations(const HammerfestPonies & value) { this->related_locations = value; }

        const HammerfestPonies & get_suppressions() const { return suppressions; }
        HammerfestPonies & get_mutable_suppressions() { return suppressions; }
        void set_suppressions(const HammerfestPonies & value) { this->suppressions = value; }

        const Version & get_baseline_state() const { return baseline_state; }
        Version & get_mutable_baseline_state() { return baseline_state; }
        void set_baseline_state(const Version & value) { this->baseline_state = value; }

        const PuneHedgehog & get_rank() const { return rank; }
        PuneHedgehog & get_mutable_rank() { return rank; }
        void set_rank(const PuneHedgehog & value) { this->rank = value; }

        const HammerfestPonies & get_attachments() const { return attachments; }
        HammerfestPonies & get_mutable_attachments() { return attachments; }
        void set_attachments(const HammerfestPonies & value) { this->attachments = value; }

        const Schema & get_hosted_viewer_uri() const { return hosted_viewer_uri; }
        Schema & get_mutable_hosted_viewer_uri() { return hosted_viewer_uri; }
        void set_hosted_viewer_uri(const Schema & value) { this->hosted_viewer_uri = value; }

        const WorkItemUris & get_work_item_uris() const { return work_item_uris; }
        WorkItemUris & get_mutable_work_item_uris() { return work_item_uris; }
        void set_work_item_uris(const WorkItemUris & value) { this->work_item_uris = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_provenance() const { return provenance; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_provenance() { return provenance; }
        void set_provenance(const LivingstoneSouthernWhiteFacedOwl & value) { this->provenance = value; }

        const HammerfestPonies & get_fixes() const { return fixes; }
        HammerfestPonies & get_mutable_fixes() { return fixes; }
        void set_fixes(const HammerfestPonies & value) { this->fixes = value; }

        const HammerfestPonies & get_taxa() const { return taxa; }
        HammerfestPonies & get_mutable_taxa() { return taxa; }
        void set_taxa(const HammerfestPonies & value) { this->taxa = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_web_request() const { return web_request; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_web_request() { return web_request; }
        void set_web_request(const LivingstoneSouthernWhiteFacedOwl & value) { this->web_request = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_web_response() const { return web_response; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_web_response() { return web_response; }
        void set_web_response(const LivingstoneSouthernWhiteFacedOwl & value) { this->web_response = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Result {
        public:
        Result() = default;
        virtual ~Result() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ResultProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ResultProperties & get_properties() const { return properties; }
        ResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const ResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ResultProvenanceProperties {
        public:
        ResultProvenanceProperties() = default;
        virtual ~ResultProvenanceProperties() = default;

        private:
        Schema first_detection_time_utc;
        Schema last_detection_time_utc;
        MimeType first_detection_run_guid;
        MimeType last_detection_run_guid;
        PuneHedgehog invocation_index;
        HammerfestPonies conversion_sources;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const Schema & get_first_detection_time_utc() const { return first_detection_time_utc; }
        Schema & get_mutable_first_detection_time_utc() { return first_detection_time_utc; }
        void set_first_detection_time_utc(const Schema & value) { this->first_detection_time_utc = value; }

        const Schema & get_last_detection_time_utc() const { return last_detection_time_utc; }
        Schema & get_mutable_last_detection_time_utc() { return last_detection_time_utc; }
        void set_last_detection_time_utc(const Schema & value) { this->last_detection_time_utc = value; }

        const MimeType & get_first_detection_run_guid() const { return first_detection_run_guid; }
        MimeType & get_mutable_first_detection_run_guid() { return first_detection_run_guid; }
        void set_first_detection_run_guid(const MimeType & value) { this->first_detection_run_guid = value; }

        const MimeType & get_last_detection_run_guid() const { return last_detection_run_guid; }
        MimeType & get_mutable_last_detection_run_guid() { return last_detection_run_guid; }
        void set_last_detection_run_guid(const MimeType & value) { this->last_detection_run_guid = value; }

        const PuneHedgehog & get_invocation_index() const { return invocation_index; }
        PuneHedgehog & get_mutable_invocation_index() { return invocation_index; }
        void set_invocation_index(const PuneHedgehog & value) { this->invocation_index = value; }

        const HammerfestPonies & get_conversion_sources() const { return conversion_sources; }
        HammerfestPonies & get_mutable_conversion_sources() { return conversion_sources; }
        void set_conversion_sources(const HammerfestPonies & value) { this->conversion_sources = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ResultProvenance {
        public:
        ResultProvenance() = default;
        virtual ~ResultProvenance() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ResultProvenanceProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ResultProvenanceProperties & get_properties() const { return properties; }
        ResultProvenanceProperties & get_mutable_properties() { return properties; }
        void set_properties(const ResultProvenanceProperties & value) { this->properties = value; }
    };

    class RunProperties {
        public:
        RunProperties() = default;
        virtual ~RunProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl tool;
        HammerfestPonies invocations;
        LivingstoneSouthernWhiteFacedOwl conversion;
        MimeType language;
        HammerfestPonies version_control_provenance;
        FinalState original_uri_base_ids;
        HammerfestPonies artifacts;
        HammerfestPonies logical_locations;
        HammerfestPonies graphs;
        HammerfestPonies results;
        LivingstoneSouthernWhiteFacedOwl automation_details;
        HammerfestPonies run_aggregates;
        MimeType baseline_guid;
        Arguments redaction_tokens;
        TartuGecko default_encoding;
        TartuGecko default_source_language;
        Arguments newline_sequences;
        Version column_kind;
        LivingstoneSouthernWhiteFacedOwl external_property_file_references;
        HammerfestPonies thread_flow_locations;
        HammerfestPonies taxonomies;
        HammerfestPonies addresses;
        HammerfestPonies translations;
        HammerfestPonies policies;
        HammerfestPonies web_requests;
        HammerfestPonies web_responses;
        LivingstoneSouthernWhiteFacedOwl special_locations;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_tool() const { return tool; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_tool() { return tool; }
        void set_tool(const LivingstoneSouthernWhiteFacedOwl & value) { this->tool = value; }

        const HammerfestPonies & get_invocations() const { return invocations; }
        HammerfestPonies & get_mutable_invocations() { return invocations; }
        void set_invocations(const HammerfestPonies & value) { this->invocations = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_conversion() const { return conversion; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_conversion() { return conversion; }
        void set_conversion(const LivingstoneSouthernWhiteFacedOwl & value) { this->conversion = value; }

        const MimeType & get_language() const { return language; }
        MimeType & get_mutable_language() { return language; }
        void set_language(const MimeType & value) { this->language = value; }

        const HammerfestPonies & get_version_control_provenance() const { return version_control_provenance; }
        HammerfestPonies & get_mutable_version_control_provenance() { return version_control_provenance; }
        void set_version_control_provenance(const HammerfestPonies & value) { this->version_control_provenance = value; }

        const FinalState & get_original_uri_base_ids() const { return original_uri_base_ids; }
        FinalState & get_mutable_original_uri_base_ids() { return original_uri_base_ids; }
        void set_original_uri_base_ids(const FinalState & value) { this->original_uri_base_ids = value; }

        const HammerfestPonies & get_artifacts() const { return artifacts; }
        HammerfestPonies & get_mutable_artifacts() { return artifacts; }
        void set_artifacts(const HammerfestPonies & value) { this->artifacts = value; }

        const HammerfestPonies & get_logical_locations() const { return logical_locations; }
        HammerfestPonies & get_mutable_logical_locations() { return logical_locations; }
        void set_logical_locations(const HammerfestPonies & value) { this->logical_locations = value; }

        const HammerfestPonies & get_graphs() const { return graphs; }
        HammerfestPonies & get_mutable_graphs() { return graphs; }
        void set_graphs(const HammerfestPonies & value) { this->graphs = value; }

        const HammerfestPonies & get_results() const { return results; }
        HammerfestPonies & get_mutable_results() { return results; }
        void set_results(const HammerfestPonies & value) { this->results = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_automation_details() const { return automation_details; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_automation_details() { return automation_details; }
        void set_automation_details(const LivingstoneSouthernWhiteFacedOwl & value) { this->automation_details = value; }

        const HammerfestPonies & get_run_aggregates() const { return run_aggregates; }
        HammerfestPonies & get_mutable_run_aggregates() { return run_aggregates; }
        void set_run_aggregates(const HammerfestPonies & value) { this->run_aggregates = value; }

        const MimeType & get_baseline_guid() const { return baseline_guid; }
        MimeType & get_mutable_baseline_guid() { return baseline_guid; }
        void set_baseline_guid(const MimeType & value) { this->baseline_guid = value; }

        const Arguments & get_redaction_tokens() const { return redaction_tokens; }
        Arguments & get_mutable_redaction_tokens() { return redaction_tokens; }
        void set_redaction_tokens(const Arguments & value) { this->redaction_tokens = value; }

        const TartuGecko & get_default_encoding() const { return default_encoding; }
        TartuGecko & get_mutable_default_encoding() { return default_encoding; }
        void set_default_encoding(const TartuGecko & value) { this->default_encoding = value; }

        const TartuGecko & get_default_source_language() const { return default_source_language; }
        TartuGecko & get_mutable_default_source_language() { return default_source_language; }
        void set_default_source_language(const TartuGecko & value) { this->default_source_language = value; }

        const Arguments & get_newline_sequences() const { return newline_sequences; }
        Arguments & get_mutable_newline_sequences() { return newline_sequences; }
        void set_newline_sequences(const Arguments & value) { this->newline_sequences = value; }

        const Version & get_column_kind() const { return column_kind; }
        Version & get_mutable_column_kind() { return column_kind; }
        void set_column_kind(const Version & value) { this->column_kind = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_external_property_file_references() const { return external_property_file_references; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_external_property_file_references() { return external_property_file_references; }
        void set_external_property_file_references(const LivingstoneSouthernWhiteFacedOwl & value) { this->external_property_file_references = value; }

        const HammerfestPonies & get_thread_flow_locations() const { return thread_flow_locations; }
        HammerfestPonies & get_mutable_thread_flow_locations() { return thread_flow_locations; }
        void set_thread_flow_locations(const HammerfestPonies & value) { this->thread_flow_locations = value; }

        const HammerfestPonies & get_taxonomies() const { return taxonomies; }
        HammerfestPonies & get_mutable_taxonomies() { return taxonomies; }
        void set_taxonomies(const HammerfestPonies & value) { this->taxonomies = value; }

        const HammerfestPonies & get_addresses() const { return addresses; }
        HammerfestPonies & get_mutable_addresses() { return addresses; }
        void set_addresses(const HammerfestPonies & value) { this->addresses = value; }

        const HammerfestPonies & get_translations() const { return translations; }
        HammerfestPonies & get_mutable_translations() { return translations; }
        void set_translations(const HammerfestPonies & value) { this->translations = value; }

        const HammerfestPonies & get_policies() const { return policies; }
        HammerfestPonies & get_mutable_policies() { return policies; }
        void set_policies(const HammerfestPonies & value) { this->policies = value; }

        const HammerfestPonies & get_web_requests() const { return web_requests; }
        HammerfestPonies & get_mutable_web_requests() { return web_requests; }
        void set_web_requests(const HammerfestPonies & value) { this->web_requests = value; }

        const HammerfestPonies & get_web_responses() const { return web_responses; }
        HammerfestPonies & get_mutable_web_responses() { return web_responses; }
        void set_web_responses(const HammerfestPonies & value) { this->web_responses = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_special_locations() const { return special_locations; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_special_locations() { return special_locations; }
        void set_special_locations(const LivingstoneSouthernWhiteFacedOwl & value) { this->special_locations = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Run {
        public:
        Run() = default;
        virtual ~Run() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        RunProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const RunProperties & get_properties() const { return properties; }
        RunProperties & get_mutable_properties() { return properties; }
        void set_properties(const RunProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class RunAutomationDetailsProperties {
        public:
        RunAutomationDetailsProperties() = default;
        virtual ~RunAutomationDetailsProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl description;
        TartuGecko id;
        MimeType guid;
        MimeType correlation_guid;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_description() const { return description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_description() { return description; }
        void set_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->description = value; }

        const TartuGecko & get_id() const { return id; }
        TartuGecko & get_mutable_id() { return id; }
        void set_id(const TartuGecko & value) { this->id = value; }

        const MimeType & get_guid() const { return guid; }
        MimeType & get_mutable_guid() { return guid; }
        void set_guid(const MimeType & value) { this->guid = value; }

        const MimeType & get_correlation_guid() const { return correlation_guid; }
        MimeType & get_mutable_correlation_guid() { return correlation_guid; }
        void set_correlation_guid(const MimeType & value) { this->correlation_guid = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class RunAutomationDetails {
        public:
        RunAutomationDetails() = default;
        virtual ~RunAutomationDetails() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        RunAutomationDetailsProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const RunAutomationDetailsProperties & get_properties() const { return properties; }
        RunAutomationDetailsProperties & get_mutable_properties() { return properties; }
        void set_properties(const RunAutomationDetailsProperties & value) { this->properties = value; }
    };

    class SpecialLocationsProperties {
        public:
        SpecialLocationsProperties() = default;
        virtual ~SpecialLocationsProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl display_base;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_display_base() const { return display_base; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_display_base() { return display_base; }
        void set_display_base(const LivingstoneSouthernWhiteFacedOwl & value) { this->display_base = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class SpecialLocations {
        public:
        SpecialLocations() = default;
        virtual ~SpecialLocations() = default;

        private:
        std::string description;
        std::string type;
        SpecialLocationsProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const SpecialLocationsProperties & get_properties() const { return properties; }
        SpecialLocationsProperties & get_mutable_properties() { return properties; }
        void set_properties(const SpecialLocationsProperties & value) { this->properties = value; }
    };

    class StackProperties {
        public:
        StackProperties() = default;
        virtual ~StackProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl message;
        HammerfestPonies frames;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_message() const { return message; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_message() { return message; }
        void set_message(const LivingstoneSouthernWhiteFacedOwl & value) { this->message = value; }

        const HammerfestPonies & get_frames() const { return frames; }
        HammerfestPonies & get_mutable_frames() { return frames; }
        void set_frames(const HammerfestPonies & value) { this->frames = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Stack {
        public:
        Stack() = default;
        virtual ~Stack() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        StackProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const StackProperties & get_properties() const { return properties; }
        StackProperties & get_mutable_properties() { return properties; }
        void set_properties(const StackProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ParametersItems {
        public:
        ParametersItems() = default;
        virtual ~ParametersItems() = default;

        private:
        PurpleType type;
        std::vector<nlohmann::json> items_default;

        public:
        const PurpleType & get_type() const { return type; }
        PurpleType & get_mutable_type() { return type; }
        void set_type(const PurpleType & value) { this->type = value; }

        const std::vector<nlohmann::json> & get_items_default() const { return items_default; }
        std::vector<nlohmann::json> & get_mutable_items_default() { return items_default; }
        void set_items_default(const std::vector<nlohmann::json> & value) { this->items_default = value; }
    };

    class Parameters {
        public:
        Parameters() = default;
        virtual ~Parameters() = default;

        private:
        std::string description;
        FluffyType type;
        int64_t min_items;
        bool unique_items;
        std::vector<nlohmann::json> parameters_default;
        ParametersItems items;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const FluffyType & get_type() const { return type; }
        FluffyType & get_mutable_type() { return type; }
        void set_type(const FluffyType & value) { this->type = value; }

        const int64_t & get_min_items() const { return min_items; }
        int64_t & get_mutable_min_items() { return min_items; }
        void set_min_items(const int64_t & value) { this->min_items = value; }

        const bool & get_unique_items() const { return unique_items; }
        bool & get_mutable_unique_items() { return unique_items; }
        void set_unique_items(const bool & value) { this->unique_items = value; }

        const std::vector<nlohmann::json> & get_parameters_default() const { return parameters_default; }
        std::vector<nlohmann::json> & get_mutable_parameters_default() { return parameters_default; }
        void set_parameters_default(const std::vector<nlohmann::json> & value) { this->parameters_default = value; }

        const ParametersItems & get_items() const { return items; }
        ParametersItems & get_mutable_items() { return items; }
        void set_items(const ParametersItems & value) { this->items = value; }
    };

    class StackFrameProperties {
        public:
        StackFrameProperties() = default;
        virtual ~StackFrameProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl location;
        TartuGecko properties_module;
        TartuGecko thread_id;
        Parameters parameters;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_location() const { return location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_location() { return location; }
        void set_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->location = value; }

        const TartuGecko & get_properties_module() const { return properties_module; }
        TartuGecko & get_mutable_properties_module() { return properties_module; }
        void set_properties_module(const TartuGecko & value) { this->properties_module = value; }

        const TartuGecko & get_thread_id() const { return thread_id; }
        TartuGecko & get_mutable_thread_id() { return thread_id; }
        void set_thread_id(const TartuGecko & value) { this->thread_id = value; }

        const Parameters & get_parameters() const { return parameters; }
        Parameters & get_mutable_parameters() { return parameters; }
        void set_parameters(const Parameters & value) { this->parameters = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class StackFrame {
        public:
        StackFrame() = default;
        virtual ~StackFrame() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        StackFrameProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const StackFrameProperties & get_properties() const { return properties; }
        StackFrameProperties & get_mutable_properties() { return properties; }
        void set_properties(const StackFrameProperties & value) { this->properties = value; }
    };

    class SuppressionProperties {
        public:
        SuppressionProperties() = default;
        virtual ~SuppressionProperties() = default;

        private:
        MimeType guid;
        Version kind;
        Version state;
        TartuGecko justification;
        LivingstoneSouthernWhiteFacedOwl location;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const MimeType & get_guid() const { return guid; }
        MimeType & get_mutable_guid() { return guid; }
        void set_guid(const MimeType & value) { this->guid = value; }

        const Version & get_kind() const { return kind; }
        Version & get_mutable_kind() { return kind; }
        void set_kind(const Version & value) { this->kind = value; }

        const Version & get_state() const { return state; }
        Version & get_mutable_state() { return state; }
        void set_state(const Version & value) { this->state = value; }

        const TartuGecko & get_justification() const { return justification; }
        TartuGecko & get_mutable_justification() { return justification; }
        void set_justification(const TartuGecko & value) { this->justification = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_location() const { return location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_location() { return location; }
        void set_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->location = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Suppression {
        public:
        Suppression() = default;
        virtual ~Suppression() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        SuppressionProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const SuppressionProperties & get_properties() const { return properties; }
        SuppressionProperties & get_mutable_properties() { return properties; }
        void set_properties(const SuppressionProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ThreadFlowProperties {
        public:
        ThreadFlowProperties() = default;
        virtual ~ThreadFlowProperties() = default;

        private:
        TartuGecko id;
        LivingstoneSouthernWhiteFacedOwl message;
        FinalState initial_state;
        FinalState immutable_state;
        HammerfestPonies locations;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_id() const { return id; }
        TartuGecko & get_mutable_id() { return id; }
        void set_id(const TartuGecko & value) { this->id = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_message() const { return message; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_message() { return message; }
        void set_message(const LivingstoneSouthernWhiteFacedOwl & value) { this->message = value; }

        const FinalState & get_initial_state() const { return initial_state; }
        FinalState & get_mutable_initial_state() { return initial_state; }
        void set_initial_state(const FinalState & value) { this->initial_state = value; }

        const FinalState & get_immutable_state() const { return immutable_state; }
        FinalState & get_mutable_immutable_state() { return immutable_state; }
        void set_immutable_state(const FinalState & value) { this->immutable_state = value; }

        const HammerfestPonies & get_locations() const { return locations; }
        HammerfestPonies & get_mutable_locations() { return locations; }
        void set_locations(const HammerfestPonies & value) { this->locations = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ThreadFlow {
        public:
        ThreadFlow() = default;
        virtual ~ThreadFlow() = default;

        private:
        std::string type;
        ThreadFlowProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ThreadFlowProperties & get_properties() const { return properties; }
        ThreadFlowProperties & get_mutable_properties() { return properties; }
        void set_properties(const ThreadFlowProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ThreadFlowLocationProperties {
        public:
        ThreadFlowLocationProperties() = default;
        virtual ~ThreadFlowLocationProperties() = default;

        private:
        PuneHedgehog index;
        LivingstoneSouthernWhiteFacedOwl location;
        LivingstoneSouthernWhiteFacedOwl stack;
        Arguments kinds;
        HammerfestPonies taxa;
        TartuGecko properties_module;
        FinalState state;
        PuneHedgehog nesting_level;
        PuneHedgehog execution_order;
        Schema execution_time_utc;
        Level importance;
        LivingstoneSouthernWhiteFacedOwl web_request;
        LivingstoneSouthernWhiteFacedOwl web_response;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const PuneHedgehog & get_index() const { return index; }
        PuneHedgehog & get_mutable_index() { return index; }
        void set_index(const PuneHedgehog & value) { this->index = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_location() const { return location; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_location() { return location; }
        void set_location(const LivingstoneSouthernWhiteFacedOwl & value) { this->location = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_stack() const { return stack; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_stack() { return stack; }
        void set_stack(const LivingstoneSouthernWhiteFacedOwl & value) { this->stack = value; }

        const Arguments & get_kinds() const { return kinds; }
        Arguments & get_mutable_kinds() { return kinds; }
        void set_kinds(const Arguments & value) { this->kinds = value; }

        const HammerfestPonies & get_taxa() const { return taxa; }
        HammerfestPonies & get_mutable_taxa() { return taxa; }
        void set_taxa(const HammerfestPonies & value) { this->taxa = value; }

        const TartuGecko & get_properties_module() const { return properties_module; }
        TartuGecko & get_mutable_properties_module() { return properties_module; }
        void set_properties_module(const TartuGecko & value) { this->properties_module = value; }

        const FinalState & get_state() const { return state; }
        FinalState & get_mutable_state() { return state; }
        void set_state(const FinalState & value) { this->state = value; }

        const PuneHedgehog & get_nesting_level() const { return nesting_level; }
        PuneHedgehog & get_mutable_nesting_level() { return nesting_level; }
        void set_nesting_level(const PuneHedgehog & value) { this->nesting_level = value; }

        const PuneHedgehog & get_execution_order() const { return execution_order; }
        PuneHedgehog & get_mutable_execution_order() { return execution_order; }
        void set_execution_order(const PuneHedgehog & value) { this->execution_order = value; }

        const Schema & get_execution_time_utc() const { return execution_time_utc; }
        Schema & get_mutable_execution_time_utc() { return execution_time_utc; }
        void set_execution_time_utc(const Schema & value) { this->execution_time_utc = value; }

        const Level & get_importance() const { return importance; }
        Level & get_mutable_importance() { return importance; }
        void set_importance(const Level & value) { this->importance = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_web_request() const { return web_request; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_web_request() { return web_request; }
        void set_web_request(const LivingstoneSouthernWhiteFacedOwl & value) { this->web_request = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_web_response() const { return web_response; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_web_response() { return web_response; }
        void set_web_response(const LivingstoneSouthernWhiteFacedOwl & value) { this->web_response = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ThreadFlowLocation {
        public:
        ThreadFlowLocation() = default;
        virtual ~ThreadFlowLocation() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ThreadFlowLocationProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ThreadFlowLocationProperties & get_properties() const { return properties; }
        ThreadFlowLocationProperties & get_mutable_properties() { return properties; }
        void set_properties(const ThreadFlowLocationProperties & value) { this->properties = value; }
    };

    class ToolProperties {
        public:
        ToolProperties() = default;
        virtual ~ToolProperties() = default;

        private:
        LivingstoneSouthernWhiteFacedOwl driver;
        HammerfestPonies extensions;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const LivingstoneSouthernWhiteFacedOwl & get_driver() const { return driver; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_driver() { return driver; }
        void set_driver(const LivingstoneSouthernWhiteFacedOwl & value) { this->driver = value; }

        const HammerfestPonies & get_extensions() const { return extensions; }
        HammerfestPonies & get_mutable_extensions() { return extensions; }
        void set_extensions(const HammerfestPonies & value) { this->extensions = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Tool {
        public:
        Tool() = default;
        virtual ~Tool() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ToolProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ToolProperties & get_properties() const { return properties; }
        ToolProperties & get_mutable_properties() { return properties; }
        void set_properties(const ToolProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ToolComponentProperties {
        public:
        ToolComponentProperties() = default;
        virtual ~ToolComponentProperties() = default;

        private:
        MimeType guid;
        TartuGecko name;
        TartuGecko organization;
        TartuGecko product;
        TartuGecko product_suite;
        LivingstoneSouthernWhiteFacedOwl short_description;
        LivingstoneSouthernWhiteFacedOwl full_description;
        TartuGecko full_name;
        TartuGecko version;
        TartuGecko semantic_version;
        MimeType dotted_quad_file_version;
        TartuGecko release_date_utc;
        Schema download_uri;
        Schema information_uri;
        FinalState global_message_strings;
        HammerfestPonies notifications;
        HammerfestPonies rules;
        HammerfestPonies taxa;
        HammerfestPonies locations;
        MimeType language;
        Roles contents;
        Enabled is_comprehensive;
        TartuGecko localized_data_semantic_version;
        TartuGecko minimum_required_localized_data_semantic_version;
        LivingstoneSouthernWhiteFacedOwl associated_component;
        LivingstoneSouthernWhiteFacedOwl translation_metadata;
        HammerfestPonies supported_taxonomies;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const MimeType & get_guid() const { return guid; }
        MimeType & get_mutable_guid() { return guid; }
        void set_guid(const MimeType & value) { this->guid = value; }

        const TartuGecko & get_name() const { return name; }
        TartuGecko & get_mutable_name() { return name; }
        void set_name(const TartuGecko & value) { this->name = value; }

        const TartuGecko & get_organization() const { return organization; }
        TartuGecko & get_mutable_organization() { return organization; }
        void set_organization(const TartuGecko & value) { this->organization = value; }

        const TartuGecko & get_product() const { return product; }
        TartuGecko & get_mutable_product() { return product; }
        void set_product(const TartuGecko & value) { this->product = value; }

        const TartuGecko & get_product_suite() const { return product_suite; }
        TartuGecko & get_mutable_product_suite() { return product_suite; }
        void set_product_suite(const TartuGecko & value) { this->product_suite = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_short_description() const { return short_description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_short_description() { return short_description; }
        void set_short_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->short_description = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_full_description() const { return full_description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_full_description() { return full_description; }
        void set_full_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->full_description = value; }

        const TartuGecko & get_full_name() const { return full_name; }
        TartuGecko & get_mutable_full_name() { return full_name; }
        void set_full_name(const TartuGecko & value) { this->full_name = value; }

        const TartuGecko & get_version() const { return version; }
        TartuGecko & get_mutable_version() { return version; }
        void set_version(const TartuGecko & value) { this->version = value; }

        const TartuGecko & get_semantic_version() const { return semantic_version; }
        TartuGecko & get_mutable_semantic_version() { return semantic_version; }
        void set_semantic_version(const TartuGecko & value) { this->semantic_version = value; }

        const MimeType & get_dotted_quad_file_version() const { return dotted_quad_file_version; }
        MimeType & get_mutable_dotted_quad_file_version() { return dotted_quad_file_version; }
        void set_dotted_quad_file_version(const MimeType & value) { this->dotted_quad_file_version = value; }

        const TartuGecko & get_release_date_utc() const { return release_date_utc; }
        TartuGecko & get_mutable_release_date_utc() { return release_date_utc; }
        void set_release_date_utc(const TartuGecko & value) { this->release_date_utc = value; }

        const Schema & get_download_uri() const { return download_uri; }
        Schema & get_mutable_download_uri() { return download_uri; }
        void set_download_uri(const Schema & value) { this->download_uri = value; }

        const Schema & get_information_uri() const { return information_uri; }
        Schema & get_mutable_information_uri() { return information_uri; }
        void set_information_uri(const Schema & value) { this->information_uri = value; }

        const FinalState & get_global_message_strings() const { return global_message_strings; }
        FinalState & get_mutable_global_message_strings() { return global_message_strings; }
        void set_global_message_strings(const FinalState & value) { this->global_message_strings = value; }

        const HammerfestPonies & get_notifications() const { return notifications; }
        HammerfestPonies & get_mutable_notifications() { return notifications; }
        void set_notifications(const HammerfestPonies & value) { this->notifications = value; }

        const HammerfestPonies & get_rules() const { return rules; }
        HammerfestPonies & get_mutable_rules() { return rules; }
        void set_rules(const HammerfestPonies & value) { this->rules = value; }

        const HammerfestPonies & get_taxa() const { return taxa; }
        HammerfestPonies & get_mutable_taxa() { return taxa; }
        void set_taxa(const HammerfestPonies & value) { this->taxa = value; }

        const HammerfestPonies & get_locations() const { return locations; }
        HammerfestPonies & get_mutable_locations() { return locations; }
        void set_locations(const HammerfestPonies & value) { this->locations = value; }

        const MimeType & get_language() const { return language; }
        MimeType & get_mutable_language() { return language; }
        void set_language(const MimeType & value) { this->language = value; }

        const Roles & get_contents() const { return contents; }
        Roles & get_mutable_contents() { return contents; }
        void set_contents(const Roles & value) { this->contents = value; }

        const Enabled & get_is_comprehensive() const { return is_comprehensive; }
        Enabled & get_mutable_is_comprehensive() { return is_comprehensive; }
        void set_is_comprehensive(const Enabled & value) { this->is_comprehensive = value; }

        const TartuGecko & get_localized_data_semantic_version() const { return localized_data_semantic_version; }
        TartuGecko & get_mutable_localized_data_semantic_version() { return localized_data_semantic_version; }
        void set_localized_data_semantic_version(const TartuGecko & value) { this->localized_data_semantic_version = value; }

        const TartuGecko & get_minimum_required_localized_data_semantic_version() const { return minimum_required_localized_data_semantic_version; }
        TartuGecko & get_mutable_minimum_required_localized_data_semantic_version() { return minimum_required_localized_data_semantic_version; }
        void set_minimum_required_localized_data_semantic_version(const TartuGecko & value) { this->minimum_required_localized_data_semantic_version = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_associated_component() const { return associated_component; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_associated_component() { return associated_component; }
        void set_associated_component(const LivingstoneSouthernWhiteFacedOwl & value) { this->associated_component = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_translation_metadata() const { return translation_metadata; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_translation_metadata() { return translation_metadata; }
        void set_translation_metadata(const LivingstoneSouthernWhiteFacedOwl & value) { this->translation_metadata = value; }

        const HammerfestPonies & get_supported_taxonomies() const { return supported_taxonomies; }
        HammerfestPonies & get_mutable_supported_taxonomies() { return supported_taxonomies; }
        void set_supported_taxonomies(const HammerfestPonies & value) { this->supported_taxonomies = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ToolComponent {
        public:
        ToolComponent() = default;
        virtual ~ToolComponent() = default;

        private:
        std::string description;
        bool additional_properties;
        std::string type;
        ToolComponentProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ToolComponentProperties & get_properties() const { return properties; }
        ToolComponentProperties & get_mutable_properties() { return properties; }
        void set_properties(const ToolComponentProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class ToolComponentReferenceProperties {
        public:
        ToolComponentReferenceProperties() = default;
        virtual ~ToolComponentReferenceProperties() = default;

        private:
        TartuGecko name;
        PuneHedgehog index;
        MimeType guid;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_name() const { return name; }
        TartuGecko & get_mutable_name() { return name; }
        void set_name(const TartuGecko & value) { this->name = value; }

        const PuneHedgehog & get_index() const { return index; }
        PuneHedgehog & get_mutable_index() { return index; }
        void set_index(const PuneHedgehog & value) { this->index = value; }

        const MimeType & get_guid() const { return guid; }
        MimeType & get_mutable_guid() { return guid; }
        void set_guid(const MimeType & value) { this->guid = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class ToolComponentReference {
        public:
        ToolComponentReference() = default;
        virtual ~ToolComponentReference() = default;

        private:
        std::string description;
        std::string type;
        ToolComponentReferenceProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const ToolComponentReferenceProperties & get_properties() const { return properties; }
        ToolComponentReferenceProperties & get_mutable_properties() { return properties; }
        void set_properties(const ToolComponentReferenceProperties & value) { this->properties = value; }
    };

    class TranslationMetadataProperties {
        public:
        TranslationMetadataProperties() = default;
        virtual ~TranslationMetadataProperties() = default;

        private:
        TartuGecko name;
        TartuGecko full_name;
        LivingstoneSouthernWhiteFacedOwl short_description;
        LivingstoneSouthernWhiteFacedOwl full_description;
        Schema download_uri;
        Schema information_uri;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const TartuGecko & get_name() const { return name; }
        TartuGecko & get_mutable_name() { return name; }
        void set_name(const TartuGecko & value) { this->name = value; }

        const TartuGecko & get_full_name() const { return full_name; }
        TartuGecko & get_mutable_full_name() { return full_name; }
        void set_full_name(const TartuGecko & value) { this->full_name = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_short_description() const { return short_description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_short_description() { return short_description; }
        void set_short_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->short_description = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_full_description() const { return full_description; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_full_description() { return full_description; }
        void set_full_description(const LivingstoneSouthernWhiteFacedOwl & value) { this->full_description = value; }

        const Schema & get_download_uri() const { return download_uri; }
        Schema & get_mutable_download_uri() { return download_uri; }
        void set_download_uri(const Schema & value) { this->download_uri = value; }

        const Schema & get_information_uri() const { return information_uri; }
        Schema & get_mutable_information_uri() { return information_uri; }
        void set_information_uri(const Schema & value) { this->information_uri = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class TranslationMetadata {
        public:
        TranslationMetadata() = default;
        virtual ~TranslationMetadata() = default;

        private:
        std::string description;
        std::string type;
        TranslationMetadataProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const TranslationMetadataProperties & get_properties() const { return properties; }
        TranslationMetadataProperties & get_mutable_properties() { return properties; }
        void set_properties(const TranslationMetadataProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class VersionControlDetailsProperties {
        public:
        VersionControlDetailsProperties() = default;
        virtual ~VersionControlDetailsProperties() = default;

        private:
        Schema repository_uri;
        TartuGecko revision_id;
        TartuGecko branch;
        TartuGecko revision_tag;
        Schema as_of_time_utc;
        LivingstoneSouthernWhiteFacedOwl mapped_to;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const Schema & get_repository_uri() const { return repository_uri; }
        Schema & get_mutable_repository_uri() { return repository_uri; }
        void set_repository_uri(const Schema & value) { this->repository_uri = value; }

        const TartuGecko & get_revision_id() const { return revision_id; }
        TartuGecko & get_mutable_revision_id() { return revision_id; }
        void set_revision_id(const TartuGecko & value) { this->revision_id = value; }

        const TartuGecko & get_branch() const { return branch; }
        TartuGecko & get_mutable_branch() { return branch; }
        void set_branch(const TartuGecko & value) { this->branch = value; }

        const TartuGecko & get_revision_tag() const { return revision_tag; }
        TartuGecko & get_mutable_revision_tag() { return revision_tag; }
        void set_revision_tag(const TartuGecko & value) { this->revision_tag = value; }

        const Schema & get_as_of_time_utc() const { return as_of_time_utc; }
        Schema & get_mutable_as_of_time_utc() { return as_of_time_utc; }
        void set_as_of_time_utc(const Schema & value) { this->as_of_time_utc = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_mapped_to() const { return mapped_to; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_mapped_to() { return mapped_to; }
        void set_mapped_to(const LivingstoneSouthernWhiteFacedOwl & value) { this->mapped_to = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class VersionControlDetails {
        public:
        VersionControlDetails() = default;
        virtual ~VersionControlDetails() = default;

        private:
        std::string description;
        std::string type;
        bool additional_properties;
        VersionControlDetailsProperties properties;
        std::vector<std::string> required;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const VersionControlDetailsProperties & get_properties() const { return properties; }
        VersionControlDetailsProperties & get_mutable_properties() { return properties; }
        void set_properties(const VersionControlDetailsProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }
    };

    class WebRequestProperties {
        public:
        WebRequestProperties() = default;
        virtual ~WebRequestProperties() = default;

        private:
        PuneHedgehog index;
        TartuGecko protocol;
        TartuGecko version;
        TartuGecko target;
        TartuGecko method;
        Hashes headers;
        Hashes parameters;
        LivingstoneSouthernWhiteFacedOwl body;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const PuneHedgehog & get_index() const { return index; }
        PuneHedgehog & get_mutable_index() { return index; }
        void set_index(const PuneHedgehog & value) { this->index = value; }

        const TartuGecko & get_protocol() const { return protocol; }
        TartuGecko & get_mutable_protocol() { return protocol; }
        void set_protocol(const TartuGecko & value) { this->protocol = value; }

        const TartuGecko & get_version() const { return version; }
        TartuGecko & get_mutable_version() { return version; }
        void set_version(const TartuGecko & value) { this->version = value; }

        const TartuGecko & get_target() const { return target; }
        TartuGecko & get_mutable_target() { return target; }
        void set_target(const TartuGecko & value) { this->target = value; }

        const TartuGecko & get_method() const { return method; }
        TartuGecko & get_mutable_method() { return method; }
        void set_method(const TartuGecko & value) { this->method = value; }

        const Hashes & get_headers() const { return headers; }
        Hashes & get_mutable_headers() { return headers; }
        void set_headers(const Hashes & value) { this->headers = value; }

        const Hashes & get_parameters() const { return parameters; }
        Hashes & get_mutable_parameters() { return parameters; }
        void set_parameters(const Hashes & value) { this->parameters = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_body() const { return body; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_body() { return body; }
        void set_body(const LivingstoneSouthernWhiteFacedOwl & value) { this->body = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class WebRequest {
        public:
        WebRequest() = default;
        virtual ~WebRequest() = default;

        private:
        std::string description;
        std::string type;
        WebRequestProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const WebRequestProperties & get_properties() const { return properties; }
        WebRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const WebRequestProperties & value) { this->properties = value; }
    };

    class WebResponseProperties {
        public:
        WebResponseProperties() = default;
        virtual ~WebResponseProperties() = default;

        private:
        PuneHedgehog index;
        TartuGecko protocol;
        TartuGecko version;
        TartuGecko status_code;
        TartuGecko reason_phrase;
        Hashes headers;
        LivingstoneSouthernWhiteFacedOwl body;
        Enabled no_response_received;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const PuneHedgehog & get_index() const { return index; }
        PuneHedgehog & get_mutable_index() { return index; }
        void set_index(const PuneHedgehog & value) { this->index = value; }

        const TartuGecko & get_protocol() const { return protocol; }
        TartuGecko & get_mutable_protocol() { return protocol; }
        void set_protocol(const TartuGecko & value) { this->protocol = value; }

        const TartuGecko & get_version() const { return version; }
        TartuGecko & get_mutable_version() { return version; }
        void set_version(const TartuGecko & value) { this->version = value; }

        const TartuGecko & get_status_code() const { return status_code; }
        TartuGecko & get_mutable_status_code() { return status_code; }
        void set_status_code(const TartuGecko & value) { this->status_code = value; }

        const TartuGecko & get_reason_phrase() const { return reason_phrase; }
        TartuGecko & get_mutable_reason_phrase() { return reason_phrase; }
        void set_reason_phrase(const TartuGecko & value) { this->reason_phrase = value; }

        const Hashes & get_headers() const { return headers; }
        Hashes & get_mutable_headers() { return headers; }
        void set_headers(const Hashes & value) { this->headers = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_body() const { return body; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_body() { return body; }
        void set_body(const LivingstoneSouthernWhiteFacedOwl & value) { this->body = value; }

        const Enabled & get_no_response_received() const { return no_response_received; }
        Enabled & get_mutable_no_response_received() { return no_response_received; }
        void set_no_response_received(const Enabled & value) { this->no_response_received = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class WebResponse {
        public:
        WebResponse() = default;
        virtual ~WebResponse() = default;

        private:
        std::string description;
        std::string type;
        WebResponseProperties properties;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const WebResponseProperties & get_properties() const { return properties; }
        WebResponseProperties & get_mutable_properties() { return properties; }
        void set_properties(const WebResponseProperties & value) { this->properties = value; }
    };

    class Definitions {
        public:
        Definitions() = default;
        virtual ~Definitions() = default;

        private:
        Address address;
        Artifact artifact;
        ArtifactChange artifact_change;
        ArtifactContent artifact_content;
        ArtifactLocation artifact_location;
        Attachment attachment;
        CodeFlow code_flow;
        ConfigurationOverride configuration_override;
        Conversion conversion;
        Edge edge;
        EdgeTraversal edge_traversal;
        Exception exception;
        ExternalProperties external_properties;
        ExternalPropertyFileReference external_property_file_reference;
        ExternalPropertyFileReferences external_property_file_references;
        Fix fix;
        Graph graph;
        GraphTraversal graph_traversal;
        Invocation invocation;
        Location location;
        LocationRelationship location_relationship;
        LogicalLocation logical_location;
        Message message;
        MultiformatMessageString multiformat_message_string;
        Node node;
        Notification notification;
        PhysicalLocation physical_location;
        PropertyBag property_bag;
        Rectangle rectangle;
        Region region;
        Replacement replacement;
        ReportingDescriptor reporting_descriptor;
        ReportingConfiguration reporting_configuration;
        ReportingDescriptorReference reporting_descriptor_reference;
        ReportingDescriptorRelationship reporting_descriptor_relationship;
        Result result;
        ResultProvenance result_provenance;
        Run run;
        RunAutomationDetails run_automation_details;
        SpecialLocations special_locations;
        Stack stack;
        StackFrame stack_frame;
        Suppression suppression;
        ThreadFlow thread_flow;
        ThreadFlowLocation thread_flow_location;
        Tool tool;
        ToolComponent tool_component;
        ToolComponentReference tool_component_reference;
        TranslationMetadata translation_metadata;
        VersionControlDetails version_control_details;
        WebRequest web_request;
        WebResponse web_response;

        public:
        const Address & get_address() const { return address; }
        Address & get_mutable_address() { return address; }
        void set_address(const Address & value) { this->address = value; }

        const Artifact & get_artifact() const { return artifact; }
        Artifact & get_mutable_artifact() { return artifact; }
        void set_artifact(const Artifact & value) { this->artifact = value; }

        const ArtifactChange & get_artifact_change() const { return artifact_change; }
        ArtifactChange & get_mutable_artifact_change() { return artifact_change; }
        void set_artifact_change(const ArtifactChange & value) { this->artifact_change = value; }

        const ArtifactContent & get_artifact_content() const { return artifact_content; }
        ArtifactContent & get_mutable_artifact_content() { return artifact_content; }
        void set_artifact_content(const ArtifactContent & value) { this->artifact_content = value; }

        const ArtifactLocation & get_artifact_location() const { return artifact_location; }
        ArtifactLocation & get_mutable_artifact_location() { return artifact_location; }
        void set_artifact_location(const ArtifactLocation & value) { this->artifact_location = value; }

        const Attachment & get_attachment() const { return attachment; }
        Attachment & get_mutable_attachment() { return attachment; }
        void set_attachment(const Attachment & value) { this->attachment = value; }

        const CodeFlow & get_code_flow() const { return code_flow; }
        CodeFlow & get_mutable_code_flow() { return code_flow; }
        void set_code_flow(const CodeFlow & value) { this->code_flow = value; }

        const ConfigurationOverride & get_configuration_override() const { return configuration_override; }
        ConfigurationOverride & get_mutable_configuration_override() { return configuration_override; }
        void set_configuration_override(const ConfigurationOverride & value) { this->configuration_override = value; }

        const Conversion & get_conversion() const { return conversion; }
        Conversion & get_mutable_conversion() { return conversion; }
        void set_conversion(const Conversion & value) { this->conversion = value; }

        const Edge & get_edge() const { return edge; }
        Edge & get_mutable_edge() { return edge; }
        void set_edge(const Edge & value) { this->edge = value; }

        const EdgeTraversal & get_edge_traversal() const { return edge_traversal; }
        EdgeTraversal & get_mutable_edge_traversal() { return edge_traversal; }
        void set_edge_traversal(const EdgeTraversal & value) { this->edge_traversal = value; }

        const Exception & get_exception() const { return exception; }
        Exception & get_mutable_exception() { return exception; }
        void set_exception(const Exception & value) { this->exception = value; }

        const ExternalProperties & get_external_properties() const { return external_properties; }
        ExternalProperties & get_mutable_external_properties() { return external_properties; }
        void set_external_properties(const ExternalProperties & value) { this->external_properties = value; }

        const ExternalPropertyFileReference & get_external_property_file_reference() const { return external_property_file_reference; }
        ExternalPropertyFileReference & get_mutable_external_property_file_reference() { return external_property_file_reference; }
        void set_external_property_file_reference(const ExternalPropertyFileReference & value) { this->external_property_file_reference = value; }

        const ExternalPropertyFileReferences & get_external_property_file_references() const { return external_property_file_references; }
        ExternalPropertyFileReferences & get_mutable_external_property_file_references() { return external_property_file_references; }
        void set_external_property_file_references(const ExternalPropertyFileReferences & value) { this->external_property_file_references = value; }

        const Fix & get_fix() const { return fix; }
        Fix & get_mutable_fix() { return fix; }
        void set_fix(const Fix & value) { this->fix = value; }

        const Graph & get_graph() const { return graph; }
        Graph & get_mutable_graph() { return graph; }
        void set_graph(const Graph & value) { this->graph = value; }

        const GraphTraversal & get_graph_traversal() const { return graph_traversal; }
        GraphTraversal & get_mutable_graph_traversal() { return graph_traversal; }
        void set_graph_traversal(const GraphTraversal & value) { this->graph_traversal = value; }

        const Invocation & get_invocation() const { return invocation; }
        Invocation & get_mutable_invocation() { return invocation; }
        void set_invocation(const Invocation & value) { this->invocation = value; }

        const Location & get_location() const { return location; }
        Location & get_mutable_location() { return location; }
        void set_location(const Location & value) { this->location = value; }

        const LocationRelationship & get_location_relationship() const { return location_relationship; }
        LocationRelationship & get_mutable_location_relationship() { return location_relationship; }
        void set_location_relationship(const LocationRelationship & value) { this->location_relationship = value; }

        const LogicalLocation & get_logical_location() const { return logical_location; }
        LogicalLocation & get_mutable_logical_location() { return logical_location; }
        void set_logical_location(const LogicalLocation & value) { this->logical_location = value; }

        const Message & get_message() const { return message; }
        Message & get_mutable_message() { return message; }
        void set_message(const Message & value) { this->message = value; }

        const MultiformatMessageString & get_multiformat_message_string() const { return multiformat_message_string; }
        MultiformatMessageString & get_mutable_multiformat_message_string() { return multiformat_message_string; }
        void set_multiformat_message_string(const MultiformatMessageString & value) { this->multiformat_message_string = value; }

        const Node & get_node() const { return node; }
        Node & get_mutable_node() { return node; }
        void set_node(const Node & value) { this->node = value; }

        const Notification & get_notification() const { return notification; }
        Notification & get_mutable_notification() { return notification; }
        void set_notification(const Notification & value) { this->notification = value; }

        const PhysicalLocation & get_physical_location() const { return physical_location; }
        PhysicalLocation & get_mutable_physical_location() { return physical_location; }
        void set_physical_location(const PhysicalLocation & value) { this->physical_location = value; }

        const PropertyBag & get_property_bag() const { return property_bag; }
        PropertyBag & get_mutable_property_bag() { return property_bag; }
        void set_property_bag(const PropertyBag & value) { this->property_bag = value; }

        const Rectangle & get_rectangle() const { return rectangle; }
        Rectangle & get_mutable_rectangle() { return rectangle; }
        void set_rectangle(const Rectangle & value) { this->rectangle = value; }

        const Region & get_region() const { return region; }
        Region & get_mutable_region() { return region; }
        void set_region(const Region & value) { this->region = value; }

        const Replacement & get_replacement() const { return replacement; }
        Replacement & get_mutable_replacement() { return replacement; }
        void set_replacement(const Replacement & value) { this->replacement = value; }

        const ReportingDescriptor & get_reporting_descriptor() const { return reporting_descriptor; }
        ReportingDescriptor & get_mutable_reporting_descriptor() { return reporting_descriptor; }
        void set_reporting_descriptor(const ReportingDescriptor & value) { this->reporting_descriptor = value; }

        const ReportingConfiguration & get_reporting_configuration() const { return reporting_configuration; }
        ReportingConfiguration & get_mutable_reporting_configuration() { return reporting_configuration; }
        void set_reporting_configuration(const ReportingConfiguration & value) { this->reporting_configuration = value; }

        const ReportingDescriptorReference & get_reporting_descriptor_reference() const { return reporting_descriptor_reference; }
        ReportingDescriptorReference & get_mutable_reporting_descriptor_reference() { return reporting_descriptor_reference; }
        void set_reporting_descriptor_reference(const ReportingDescriptorReference & value) { this->reporting_descriptor_reference = value; }

        const ReportingDescriptorRelationship & get_reporting_descriptor_relationship() const { return reporting_descriptor_relationship; }
        ReportingDescriptorRelationship & get_mutable_reporting_descriptor_relationship() { return reporting_descriptor_relationship; }
        void set_reporting_descriptor_relationship(const ReportingDescriptorRelationship & value) { this->reporting_descriptor_relationship = value; }

        const Result & get_result() const { return result; }
        Result & get_mutable_result() { return result; }
        void set_result(const Result & value) { this->result = value; }

        const ResultProvenance & get_result_provenance() const { return result_provenance; }
        ResultProvenance & get_mutable_result_provenance() { return result_provenance; }
        void set_result_provenance(const ResultProvenance & value) { this->result_provenance = value; }

        const Run & get_run() const { return run; }
        Run & get_mutable_run() { return run; }
        void set_run(const Run & value) { this->run = value; }

        const RunAutomationDetails & get_run_automation_details() const { return run_automation_details; }
        RunAutomationDetails & get_mutable_run_automation_details() { return run_automation_details; }
        void set_run_automation_details(const RunAutomationDetails & value) { this->run_automation_details = value; }

        const SpecialLocations & get_special_locations() const { return special_locations; }
        SpecialLocations & get_mutable_special_locations() { return special_locations; }
        void set_special_locations(const SpecialLocations & value) { this->special_locations = value; }

        const Stack & get_stack() const { return stack; }
        Stack & get_mutable_stack() { return stack; }
        void set_stack(const Stack & value) { this->stack = value; }

        const StackFrame & get_stack_frame() const { return stack_frame; }
        StackFrame & get_mutable_stack_frame() { return stack_frame; }
        void set_stack_frame(const StackFrame & value) { this->stack_frame = value; }

        const Suppression & get_suppression() const { return suppression; }
        Suppression & get_mutable_suppression() { return suppression; }
        void set_suppression(const Suppression & value) { this->suppression = value; }

        const ThreadFlow & get_thread_flow() const { return thread_flow; }
        ThreadFlow & get_mutable_thread_flow() { return thread_flow; }
        void set_thread_flow(const ThreadFlow & value) { this->thread_flow = value; }

        const ThreadFlowLocation & get_thread_flow_location() const { return thread_flow_location; }
        ThreadFlowLocation & get_mutable_thread_flow_location() { return thread_flow_location; }
        void set_thread_flow_location(const ThreadFlowLocation & value) { this->thread_flow_location = value; }

        const Tool & get_tool() const { return tool; }
        Tool & get_mutable_tool() { return tool; }
        void set_tool(const Tool & value) { this->tool = value; }

        const ToolComponent & get_tool_component() const { return tool_component; }
        ToolComponent & get_mutable_tool_component() { return tool_component; }
        void set_tool_component(const ToolComponent & value) { this->tool_component = value; }

        const ToolComponentReference & get_tool_component_reference() const { return tool_component_reference; }
        ToolComponentReference & get_mutable_tool_component_reference() { return tool_component_reference; }
        void set_tool_component_reference(const ToolComponentReference & value) { this->tool_component_reference = value; }

        const TranslationMetadata & get_translation_metadata() const { return translation_metadata; }
        TranslationMetadata & get_mutable_translation_metadata() { return translation_metadata; }
        void set_translation_metadata(const TranslationMetadata & value) { this->translation_metadata = value; }

        const VersionControlDetails & get_version_control_details() const { return version_control_details; }
        VersionControlDetails & get_mutable_version_control_details() { return version_control_details; }
        void set_version_control_details(const VersionControlDetails & value) { this->version_control_details = value; }

        const WebRequest & get_web_request() const { return web_request; }
        WebRequest & get_mutable_web_request() { return web_request; }
        void set_web_request(const WebRequest & value) { this->web_request = value; }

        const WebResponse & get_web_response() const { return web_response; }
        WebResponse & get_mutable_web_response() { return web_response; }
        void set_web_response(const WebResponse & value) { this->web_response = value; }
    };

    class LibsarifProperties {
        public:
        LibsarifProperties() = default;
        virtual ~LibsarifProperties() = default;

        private:
        Schema schema;
        Version version;
        HammerfestPonies runs;
        HammerfestPonies inline_external_properties;
        LivingstoneSouthernWhiteFacedOwl properties;

        public:
        const Schema & get_schema() const { return schema; }
        Schema & get_mutable_schema() { return schema; }
        void set_schema(const Schema & value) { this->schema = value; }

        const Version & get_version() const { return version; }
        Version & get_mutable_version() { return version; }
        void set_version(const Version & value) { this->version = value; }

        const HammerfestPonies & get_runs() const { return runs; }
        HammerfestPonies & get_mutable_runs() { return runs; }
        void set_runs(const HammerfestPonies & value) { this->runs = value; }

        const HammerfestPonies & get_inline_external_properties() const { return inline_external_properties; }
        HammerfestPonies & get_mutable_inline_external_properties() { return inline_external_properties; }
        void set_inline_external_properties(const HammerfestPonies & value) { this->inline_external_properties = value; }

        const LivingstoneSouthernWhiteFacedOwl & get_properties() const { return properties; }
        LivingstoneSouthernWhiteFacedOwl & get_mutable_properties() { return properties; }
        void set_properties(const LivingstoneSouthernWhiteFacedOwl & value) { this->properties = value; }
    };

    class Libsarif {
        public:
        Libsarif() = default;
        virtual ~Libsarif() = default;

        private:
        std::string schema;
        std::string title;
        std::string id;
        std::string description;
        bool additional_properties;
        std::string type;
        LibsarifProperties properties;
        std::vector<std::string> required;
        Definitions definitions;

        public:
        const std::string & get_schema() const { return schema; }
        std::string & get_mutable_schema() { return schema; }
        void set_schema(const std::string & value) { this->schema = value; }

        const std::string & get_title() const { return title; }
        std::string & get_mutable_title() { return title; }
        void set_title(const std::string & value) { this->title = value; }

        const std::string & get_id() const { return id; }
        std::string & get_mutable_id() { return id; }
        void set_id(const std::string & value) { this->id = value; }

        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }

        const LibsarifProperties & get_properties() const { return properties; }
        LibsarifProperties & get_mutable_properties() { return properties; }
        void set_properties(const LibsarifProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const Definitions & get_definitions() const { return definitions; }
        Definitions & get_mutable_definitions() { return definitions; }
        void set_definitions(const Definitions & value) { this->definitions = value; }
    };
}

namespace nlohmann {
    void from_json(const json & j, libsarif::PuneHedgehog & x);
    void to_json(json & j, const libsarif::PuneHedgehog & x);

    void from_json(const json & j, libsarif::TartuGecko & x);
    void to_json(json & j, const libsarif::TartuGecko & x);

    void from_json(const json & j, libsarif::LivingstoneSouthernWhiteFacedOwl & x);
    void to_json(json & j, const libsarif::LivingstoneSouthernWhiteFacedOwl & x);

    void from_json(const json & j, libsarif::AddressProperties & x);
    void to_json(json & j, const libsarif::AddressProperties & x);

    void from_json(const json & j, libsarif::Address & x);
    void to_json(json & j, const libsarif::Address & x);

    void from_json(const json & j, libsarif::AdditionalProperties & x);
    void to_json(json & j, const libsarif::AdditionalProperties & x);

    void from_json(const json & j, libsarif::Hashes & x);
    void to_json(json & j, const libsarif::Hashes & x);

    void from_json(const json & j, libsarif::Schema & x);
    void to_json(json & j, const libsarif::Schema & x);

    void from_json(const json & j, libsarif::MimeType & x);
    void to_json(json & j, const libsarif::MimeType & x);

    void from_json(const json & j, libsarif::RolesItems & x);
    void to_json(json & j, const libsarif::RolesItems & x);

    void from_json(const json & j, libsarif::Roles & x);
    void to_json(json & j, const libsarif::Roles & x);

    void from_json(const json & j, libsarif::ArtifactProperties & x);
    void to_json(json & j, const libsarif::ArtifactProperties & x);

    void from_json(const json & j, libsarif::Artifact & x);
    void to_json(json & j, const libsarif::Artifact & x);

    void from_json(const json & j, libsarif::AdditionalPropertiesClass & x);
    void to_json(json & j, const libsarif::AdditionalPropertiesClass & x);

    void from_json(const json & j, libsarif::HammerfestPonies & x);
    void to_json(json & j, const libsarif::HammerfestPonies & x);

    void from_json(const json & j, libsarif::ArtifactChangeProperties & x);
    void to_json(json & j, const libsarif::ArtifactChangeProperties & x);

    void from_json(const json & j, libsarif::ArtifactChange & x);
    void to_json(json & j, const libsarif::ArtifactChange & x);

    void from_json(const json & j, libsarif::ArtifactContentProperties & x);
    void to_json(json & j, const libsarif::ArtifactContentProperties & x);

    void from_json(const json & j, libsarif::ArtifactContent & x);
    void to_json(json & j, const libsarif::ArtifactContent & x);

    void from_json(const json & j, libsarif::ArtifactLocationProperties & x);
    void to_json(json & j, const libsarif::ArtifactLocationProperties & x);

    void from_json(const json & j, libsarif::ArtifactLocation & x);
    void to_json(json & j, const libsarif::ArtifactLocation & x);

    void from_json(const json & j, libsarif::AttachmentProperties & x);
    void to_json(json & j, const libsarif::AttachmentProperties & x);

    void from_json(const json & j, libsarif::Attachment & x);
    void to_json(json & j, const libsarif::Attachment & x);

    void from_json(const json & j, libsarif::CodeFlowProperties & x);
    void to_json(json & j, const libsarif::CodeFlowProperties & x);

    void from_json(const json & j, libsarif::CodeFlow & x);
    void to_json(json & j, const libsarif::CodeFlow & x);

    void from_json(const json & j, libsarif::ConfigurationOverrideProperties & x);
    void to_json(json & j, const libsarif::ConfigurationOverrideProperties & x);

    void from_json(const json & j, libsarif::ConfigurationOverride & x);
    void to_json(json & j, const libsarif::ConfigurationOverride & x);

    void from_json(const json & j, libsarif::ConversionProperties & x);
    void to_json(json & j, const libsarif::ConversionProperties & x);

    void from_json(const json & j, libsarif::Conversion & x);
    void to_json(json & j, const libsarif::Conversion & x);

    void from_json(const json & j, libsarif::EdgeProperties & x);
    void to_json(json & j, const libsarif::EdgeProperties & x);

    void from_json(const json & j, libsarif::Edge & x);
    void to_json(json & j, const libsarif::Edge & x);

    void from_json(const json & j, libsarif::FinalState & x);
    void to_json(json & j, const libsarif::FinalState & x);

    void from_json(const json & j, libsarif::EdgeTraversalProperties & x);
    void to_json(json & j, const libsarif::EdgeTraversalProperties & x);

    void from_json(const json & j, libsarif::EdgeTraversal & x);
    void to_json(json & j, const libsarif::EdgeTraversal & x);

    void from_json(const json & j, libsarif::ExceptionProperties & x);
    void to_json(json & j, const libsarif::ExceptionProperties & x);

    void from_json(const json & j, libsarif::Exception & x);
    void to_json(json & j, const libsarif::Exception & x);

    void from_json(const json & j, libsarif::Version & x);
    void to_json(json & j, const libsarif::Version & x);

    void from_json(const json & j, libsarif::ExternalPropertiesProperties & x);
    void to_json(json & j, const libsarif::ExternalPropertiesProperties & x);

    void from_json(const json & j, libsarif::ExternalProperties & x);
    void to_json(json & j, const libsarif::ExternalProperties & x);

    void from_json(const json & j, libsarif::Of & x);
    void to_json(json & j, const libsarif::Of & x);

    void from_json(const json & j, libsarif::ExternalPropertyFileReferenceProperties & x);
    void to_json(json & j, const libsarif::ExternalPropertyFileReferenceProperties & x);

    void from_json(const json & j, libsarif::ExternalPropertyFileReference & x);
    void to_json(json & j, const libsarif::ExternalPropertyFileReference & x);

    void from_json(const json & j, libsarif::ExternalPropertyFileReferencesProperties & x);
    void to_json(json & j, const libsarif::ExternalPropertyFileReferencesProperties & x);

    void from_json(const json & j, libsarif::ExternalPropertyFileReferences & x);
    void to_json(json & j, const libsarif::ExternalPropertyFileReferences & x);

    void from_json(const json & j, libsarif::FixProperties & x);
    void to_json(json & j, const libsarif::FixProperties & x);

    void from_json(const json & j, libsarif::Fix & x);
    void to_json(json & j, const libsarif::Fix & x);

    void from_json(const json & j, libsarif::GraphProperties & x);
    void to_json(json & j, const libsarif::GraphProperties & x);

    void from_json(const json & j, libsarif::Graph & x);
    void to_json(json & j, const libsarif::Graph & x);

    void from_json(const json & j, libsarif::GraphTraversalProperties & x);
    void to_json(json & j, const libsarif::GraphTraversalProperties & x);

    void from_json(const json & j, libsarif::GraphTraversal & x);
    void to_json(json & j, const libsarif::GraphTraversal & x);

    void from_json(const json & j, libsarif::Arguments & x);
    void to_json(json & j, const libsarif::Arguments & x);

    void from_json(const json & j, libsarif::InvocationProperties & x);
    void to_json(json & j, const libsarif::InvocationProperties & x);

    void from_json(const json & j, libsarif::Invocation & x);
    void to_json(json & j, const libsarif::Invocation & x);

    void from_json(const json & j, libsarif::LocationProperties & x);
    void to_json(json & j, const libsarif::LocationProperties & x);

    void from_json(const json & j, libsarif::Location & x);
    void to_json(json & j, const libsarif::Location & x);

    void from_json(const json & j, libsarif::LocationRelationshipProperties & x);
    void to_json(json & j, const libsarif::LocationRelationshipProperties & x);

    void from_json(const json & j, libsarif::LocationRelationship & x);
    void to_json(json & j, const libsarif::LocationRelationship & x);

    void from_json(const json & j, libsarif::LogicalLocationProperties & x);
    void to_json(json & j, const libsarif::LogicalLocationProperties & x);

    void from_json(const json & j, libsarif::LogicalLocation & x);
    void to_json(json & j, const libsarif::LogicalLocation & x);

    void from_json(const json & j, libsarif::MessageProperties & x);
    void to_json(json & j, const libsarif::MessageProperties & x);

    void from_json(const json & j, libsarif::Message & x);
    void to_json(json & j, const libsarif::Message & x);

    void from_json(const json & j, libsarif::MultiformatMessageStringProperties & x);
    void to_json(json & j, const libsarif::MultiformatMessageStringProperties & x);

    void from_json(const json & j, libsarif::MultiformatMessageString & x);
    void to_json(json & j, const libsarif::MultiformatMessageString & x);

    void from_json(const json & j, libsarif::NodeProperties & x);
    void to_json(json & j, const libsarif::NodeProperties & x);

    void from_json(const json & j, libsarif::Node & x);
    void to_json(json & j, const libsarif::Node & x);

    void from_json(const json & j, libsarif::Level & x);
    void to_json(json & j, const libsarif::Level & x);

    void from_json(const json & j, libsarif::NotificationProperties & x);
    void to_json(json & j, const libsarif::NotificationProperties & x);

    void from_json(const json & j, libsarif::Notification & x);
    void to_json(json & j, const libsarif::Notification & x);

    void from_json(const json & j, libsarif::PhysicalLocationProperties & x);
    void to_json(json & j, const libsarif::PhysicalLocationProperties & x);

    void from_json(const json & j, libsarif::PhysicalLocation & x);
    void to_json(json & j, const libsarif::PhysicalLocation & x);

    void from_json(const json & j, libsarif::PropertyBagProperties & x);
    void to_json(json & j, const libsarif::PropertyBagProperties & x);

    void from_json(const json & j, libsarif::PropertyBag & x);
    void to_json(json & j, const libsarif::PropertyBag & x);

    void from_json(const json & j, libsarif::RectangleProperties & x);
    void to_json(json & j, const libsarif::RectangleProperties & x);

    void from_json(const json & j, libsarif::Rectangle & x);
    void to_json(json & j, const libsarif::Rectangle & x);

    void from_json(const json & j, libsarif::RegionProperties & x);
    void to_json(json & j, const libsarif::RegionProperties & x);

    void from_json(const json & j, libsarif::Region & x);
    void to_json(json & j, const libsarif::Region & x);

    void from_json(const json & j, libsarif::ReplacementProperties & x);
    void to_json(json & j, const libsarif::ReplacementProperties & x);

    void from_json(const json & j, libsarif::Replacement & x);
    void to_json(json & j, const libsarif::Replacement & x);

    void from_json(const json & j, libsarif::Enabled & x);
    void to_json(json & j, const libsarif::Enabled & x);

    void from_json(const json & j, libsarif::ReportingConfigurationProperties & x);
    void to_json(json & j, const libsarif::ReportingConfigurationProperties & x);

    void from_json(const json & j, libsarif::ReportingConfiguration & x);
    void to_json(json & j, const libsarif::ReportingConfiguration & x);

    void from_json(const json & j, libsarif::DeprecatedGuidsItems & x);
    void to_json(json & j, const libsarif::DeprecatedGuidsItems & x);

    void from_json(const json & j, libsarif::DeprecatedGuids & x);
    void to_json(json & j, const libsarif::DeprecatedGuids & x);

    void from_json(const json & j, libsarif::ReportingDescriptorProperties & x);
    void to_json(json & j, const libsarif::ReportingDescriptorProperties & x);

    void from_json(const json & j, libsarif::ReportingDescriptor & x);
    void to_json(json & j, const libsarif::ReportingDescriptor & x);

    void from_json(const json & j, libsarif::ReportingDescriptorReferenceProperties & x);
    void to_json(json & j, const libsarif::ReportingDescriptorReferenceProperties & x);

    void from_json(const json & j, libsarif::ReportingDescriptorReference & x);
    void to_json(json & j, const libsarif::ReportingDescriptorReference & x);

    void from_json(const json & j, libsarif::ReportingDescriptorRelationshipProperties & x);
    void to_json(json & j, const libsarif::ReportingDescriptorRelationshipProperties & x);

    void from_json(const json & j, libsarif::ReportingDescriptorRelationship & x);
    void to_json(json & j, const libsarif::ReportingDescriptorRelationship & x);

    void from_json(const json & j, libsarif::WorkItemUrisItems & x);
    void to_json(json & j, const libsarif::WorkItemUrisItems & x);

    void from_json(const json & j, libsarif::WorkItemUris & x);
    void to_json(json & j, const libsarif::WorkItemUris & x);

    void from_json(const json & j, libsarif::ResultProperties & x);
    void to_json(json & j, const libsarif::ResultProperties & x);

    void from_json(const json & j, libsarif::Result & x);
    void to_json(json & j, const libsarif::Result & x);

    void from_json(const json & j, libsarif::ResultProvenanceProperties & x);
    void to_json(json & j, const libsarif::ResultProvenanceProperties & x);

    void from_json(const json & j, libsarif::ResultProvenance & x);
    void to_json(json & j, const libsarif::ResultProvenance & x);

    void from_json(const json & j, libsarif::RunProperties & x);
    void to_json(json & j, const libsarif::RunProperties & x);

    void from_json(const json & j, libsarif::Run & x);
    void to_json(json & j, const libsarif::Run & x);

    void from_json(const json & j, libsarif::RunAutomationDetailsProperties & x);
    void to_json(json & j, const libsarif::RunAutomationDetailsProperties & x);

    void from_json(const json & j, libsarif::RunAutomationDetails & x);
    void to_json(json & j, const libsarif::RunAutomationDetails & x);

    void from_json(const json & j, libsarif::SpecialLocationsProperties & x);
    void to_json(json & j, const libsarif::SpecialLocationsProperties & x);

    void from_json(const json & j, libsarif::SpecialLocations & x);
    void to_json(json & j, const libsarif::SpecialLocations & x);

    void from_json(const json & j, libsarif::StackProperties & x);
    void to_json(json & j, const libsarif::StackProperties & x);

    void from_json(const json & j, libsarif::Stack & x);
    void to_json(json & j, const libsarif::Stack & x);

    void from_json(const json & j, libsarif::ParametersItems & x);
    void to_json(json & j, const libsarif::ParametersItems & x);

    void from_json(const json & j, libsarif::Parameters & x);
    void to_json(json & j, const libsarif::Parameters & x);

    void from_json(const json & j, libsarif::StackFrameProperties & x);
    void to_json(json & j, const libsarif::StackFrameProperties & x);

    void from_json(const json & j, libsarif::StackFrame & x);
    void to_json(json & j, const libsarif::StackFrame & x);

    void from_json(const json & j, libsarif::SuppressionProperties & x);
    void to_json(json & j, const libsarif::SuppressionProperties & x);

    void from_json(const json & j, libsarif::Suppression & x);
    void to_json(json & j, const libsarif::Suppression & x);

    void from_json(const json & j, libsarif::ThreadFlowProperties & x);
    void to_json(json & j, const libsarif::ThreadFlowProperties & x);

    void from_json(const json & j, libsarif::ThreadFlow & x);
    void to_json(json & j, const libsarif::ThreadFlow & x);

    void from_json(const json & j, libsarif::ThreadFlowLocationProperties & x);
    void to_json(json & j, const libsarif::ThreadFlowLocationProperties & x);

    void from_json(const json & j, libsarif::ThreadFlowLocation & x);
    void to_json(json & j, const libsarif::ThreadFlowLocation & x);

    void from_json(const json & j, libsarif::ToolProperties & x);
    void to_json(json & j, const libsarif::ToolProperties & x);

    void from_json(const json & j, libsarif::Tool & x);
    void to_json(json & j, const libsarif::Tool & x);

    void from_json(const json & j, libsarif::ToolComponentProperties & x);
    void to_json(json & j, const libsarif::ToolComponentProperties & x);

    void from_json(const json & j, libsarif::ToolComponent & x);
    void to_json(json & j, const libsarif::ToolComponent & x);

    void from_json(const json & j, libsarif::ToolComponentReferenceProperties & x);
    void to_json(json & j, const libsarif::ToolComponentReferenceProperties & x);

    void from_json(const json & j, libsarif::ToolComponentReference & x);
    void to_json(json & j, const libsarif::ToolComponentReference & x);

    void from_json(const json & j, libsarif::TranslationMetadataProperties & x);
    void to_json(json & j, const libsarif::TranslationMetadataProperties & x);

    void from_json(const json & j, libsarif::TranslationMetadata & x);
    void to_json(json & j, const libsarif::TranslationMetadata & x);

    void from_json(const json & j, libsarif::VersionControlDetailsProperties & x);
    void to_json(json & j, const libsarif::VersionControlDetailsProperties & x);

    void from_json(const json & j, libsarif::VersionControlDetails & x);
    void to_json(json & j, const libsarif::VersionControlDetails & x);

    void from_json(const json & j, libsarif::WebRequestProperties & x);
    void to_json(json & j, const libsarif::WebRequestProperties & x);

    void from_json(const json & j, libsarif::WebRequest & x);
    void to_json(json & j, const libsarif::WebRequest & x);

    void from_json(const json & j, libsarif::WebResponseProperties & x);
    void to_json(json & j, const libsarif::WebResponseProperties & x);

    void from_json(const json & j, libsarif::WebResponse & x);
    void to_json(json & j, const libsarif::WebResponse & x);

    void from_json(const json & j, libsarif::Definitions & x);
    void to_json(json & j, const libsarif::Definitions & x);

    void from_json(const json & j, libsarif::LibsarifProperties & x);
    void to_json(json & j, const libsarif::LibsarifProperties & x);

    void from_json(const json & j, libsarif::Libsarif & x);
    void to_json(json & j, const libsarif::Libsarif & x);

    void from_json(const json & j, libsarif::PurpleType & x);
    void to_json(json & j, const libsarif::PurpleType & x);

    void from_json(const json & j, libsarif::Format & x);
    void to_json(json & j, const libsarif::Format & x);

    void from_json(const json & j, libsarif::FluffyType & x);
    void to_json(json & j, const libsarif::FluffyType & x);

    inline void from_json(const json & j, libsarif::PuneHedgehog& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::PurpleType>());
        x.set_minimum(j.at("minimum").get<double>());
        x.set_pune_hedgehog_default(libsarif::get_optional<double>(j, "default"));
        x.set_maximum(libsarif::get_optional<double>(j, "maximum"));
    }

    inline void to_json(json & j, const libsarif::PuneHedgehog & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["minimum"] = x.get_minimum();
        j["default"] = x.get_pune_hedgehog_default();
        j["maximum"] = x.get_maximum();
    }

    inline void from_json(const json & j, libsarif::TartuGecko& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::PurpleType>());
    }

    inline void to_json(json & j, const libsarif::TartuGecko & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, libsarif::LivingstoneSouthernWhiteFacedOwl& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_ref(j.at("$ref").get<std::string>());
    }

    inline void to_json(json & j, const libsarif::LivingstoneSouthernWhiteFacedOwl & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["$ref"] = x.get_ref();
    }

    inline void from_json(const json & j, libsarif::AddressProperties& x) {
        x.set_absolute_address(j.at("absoluteAddress").get<libsarif::PuneHedgehog>());
        x.set_relative_address(j.at("relativeAddress").get<libsarif::TartuGecko>());
        x.set_length(j.at("length").get<libsarif::TartuGecko>());
        x.set_kind(j.at("kind").get<libsarif::TartuGecko>());
        x.set_name(j.at("name").get<libsarif::TartuGecko>());
        x.set_fully_qualified_name(j.at("fullyQualifiedName").get<libsarif::TartuGecko>());
        x.set_offset_from_parent(j.at("offsetFromParent").get<libsarif::TartuGecko>());
        x.set_index(j.at("index").get<libsarif::PuneHedgehog>());
        x.set_parent_index(j.at("parentIndex").get<libsarif::PuneHedgehog>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::AddressProperties & x) {
        j = json::object();
        j["absoluteAddress"] = x.get_absolute_address();
        j["relativeAddress"] = x.get_relative_address();
        j["length"] = x.get_length();
        j["kind"] = x.get_kind();
        j["name"] = x.get_name();
        j["fullyQualifiedName"] = x.get_fully_qualified_name();
        j["offsetFromParent"] = x.get_offset_from_parent();
        j["index"] = x.get_index();
        j["parentIndex"] = x.get_parent_index();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Address& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::AddressProperties>());
    }

    inline void to_json(json & j, const libsarif::Address & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::AdditionalProperties& x) {
        x.set_type(j.at("type").get<libsarif::PurpleType>());
    }

    inline void to_json(json & j, const libsarif::AdditionalProperties & x) {
        j = json::object();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, libsarif::Hashes& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<libsarif::AdditionalProperties>());
    }

    inline void to_json(json & j, const libsarif::Hashes & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
    }

    inline void from_json(const json & j, libsarif::Schema& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::PurpleType>());
        x.set_format(j.at("format").get<libsarif::Format>());
    }

    inline void to_json(json & j, const libsarif::Schema & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["format"] = x.get_format();
    }

    inline void from_json(const json & j, libsarif::MimeType& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::PurpleType>());
        x.set_pattern(j.at("pattern").get<std::string>());
        x.set_mime_type_default(libsarif::get_optional<std::string>(j, "default"));
    }

    inline void to_json(json & j, const libsarif::MimeType & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["pattern"] = x.get_pattern();
        j["default"] = x.get_mime_type_default();
    }

    inline void from_json(const json & j, libsarif::RolesItems& x) {
        x.set_items_enum(j.at("enum").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::RolesItems & x) {
        j = json::object();
        j["enum"] = x.get_items_enum();
    }

    inline void from_json(const json & j, libsarif::Roles& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::FluffyType>());
        x.set_min_items(libsarif::get_optional<int64_t>(j, "minItems"));
        x.set_unique_items(j.at("uniqueItems").get<bool>());
        x.set_roles_default(j.at("default").get<std::vector<std::string>>());
        x.set_items(j.at("items").get<libsarif::RolesItems>());
    }

    inline void to_json(json & j, const libsarif::Roles & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["minItems"] = x.get_min_items();
        j["uniqueItems"] = x.get_unique_items();
        j["default"] = x.get_roles_default();
        j["items"] = x.get_items();
    }

    inline void from_json(const json & j, libsarif::ArtifactProperties& x) {
        x.set_description(j.at("description").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_location(j.at("location").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_parent_index(j.at("parentIndex").get<libsarif::PuneHedgehog>());
        x.set_offset(j.at("offset").get<libsarif::PuneHedgehog>());
        x.set_length(j.at("length").get<libsarif::PuneHedgehog>());
        x.set_roles(j.at("roles").get<libsarif::Roles>());
        x.set_mime_type(j.at("mimeType").get<libsarif::MimeType>());
        x.set_contents(j.at("contents").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_encoding(j.at("encoding").get<libsarif::TartuGecko>());
        x.set_source_language(j.at("sourceLanguage").get<libsarif::TartuGecko>());
        x.set_hashes(j.at("hashes").get<libsarif::Hashes>());
        x.set_last_modified_time_utc(j.at("lastModifiedTimeUtc").get<libsarif::Schema>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ArtifactProperties & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["location"] = x.get_location();
        j["parentIndex"] = x.get_parent_index();
        j["offset"] = x.get_offset();
        j["length"] = x.get_length();
        j["roles"] = x.get_roles();
        j["mimeType"] = x.get_mime_type();
        j["contents"] = x.get_contents();
        j["encoding"] = x.get_encoding();
        j["sourceLanguage"] = x.get_source_language();
        j["hashes"] = x.get_hashes();
        j["lastModifiedTimeUtc"] = x.get_last_modified_time_utc();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Artifact& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ArtifactProperties>());
    }

    inline void to_json(json & j, const libsarif::Artifact & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::AdditionalPropertiesClass& x) {
        x.set_ref(j.at("$ref").get<std::string>());
    }

    inline void to_json(json & j, const libsarif::AdditionalPropertiesClass & x) {
        j = json::object();
        j["$ref"] = x.get_ref();
    }

    inline void from_json(const json & j, libsarif::HammerfestPonies& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::FluffyType>());
        x.set_min_items(j.at("minItems").get<int64_t>());
        x.set_unique_items(libsarif::get_optional<bool>(j, "uniqueItems"));
        x.set_items(j.at("items").get<libsarif::AdditionalPropertiesClass>());
        x.set_hammerfest_ponies_default(libsarif::get_optional<std::vector<json>>(j, "default"));
    }

    inline void to_json(json & j, const libsarif::HammerfestPonies & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["minItems"] = x.get_min_items();
        j["uniqueItems"] = x.get_unique_items();
        j["items"] = x.get_items();
        j["default"] = x.get_hammerfest_ponies_default();
    }

    inline void from_json(const json & j, libsarif::ArtifactChangeProperties& x) {
        x.set_artifact_location(j.at("artifactLocation").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_replacements(j.at("replacements").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ArtifactChangeProperties & x) {
        j = json::object();
        j["artifactLocation"] = x.get_artifact_location();
        j["replacements"] = x.get_replacements();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ArtifactChange& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ArtifactChangeProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::ArtifactChange & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ArtifactContentProperties& x) {
        x.set_text(j.at("text").get<libsarif::TartuGecko>());
        x.set_binary(j.at("binary").get<libsarif::TartuGecko>());
        x.set_rendered(j.at("rendered").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ArtifactContentProperties & x) {
        j = json::object();
        j["text"] = x.get_text();
        j["binary"] = x.get_binary();
        j["rendered"] = x.get_rendered();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ArtifactContent& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::ArtifactContentProperties>());
    }

    inline void to_json(json & j, const libsarif::ArtifactContent & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ArtifactLocationProperties& x) {
        x.set_uri(j.at("uri").get<libsarif::Schema>());
        x.set_uri_base_id(j.at("uriBaseId").get<libsarif::TartuGecko>());
        x.set_index(j.at("index").get<libsarif::PuneHedgehog>());
        x.set_description(j.at("description").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ArtifactLocationProperties & x) {
        j = json::object();
        j["uri"] = x.get_uri();
        j["uriBaseId"] = x.get_uri_base_id();
        j["index"] = x.get_index();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ArtifactLocation& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ArtifactLocationProperties>());
    }

    inline void to_json(json & j, const libsarif::ArtifactLocation & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::AttachmentProperties& x) {
        x.set_description(j.at("description").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_artifact_location(j.at("artifactLocation").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_regions(j.at("regions").get<libsarif::HammerfestPonies>());
        x.set_rectangles(j.at("rectangles").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::AttachmentProperties & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["artifactLocation"] = x.get_artifact_location();
        j["regions"] = x.get_regions();
        j["rectangles"] = x.get_rectangles();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Attachment& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::AttachmentProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Attachment & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::CodeFlowProperties& x) {
        x.set_message(j.at("message").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_thread_flows(j.at("threadFlows").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::CodeFlowProperties & x) {
        j = json::object();
        j["message"] = x.get_message();
        j["threadFlows"] = x.get_thread_flows();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::CodeFlow& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::CodeFlowProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::CodeFlow & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ConfigurationOverrideProperties& x) {
        x.set_configuration(j.at("configuration").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_descriptor(j.at("descriptor").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ConfigurationOverrideProperties & x) {
        j = json::object();
        j["configuration"] = x.get_configuration();
        j["descriptor"] = x.get_descriptor();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ConfigurationOverride& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::ConfigurationOverrideProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::ConfigurationOverride & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ConversionProperties& x) {
        x.set_tool(j.at("tool").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_invocation(j.at("invocation").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_analysis_tool_log_files(j.at("analysisToolLogFiles").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ConversionProperties & x) {
        j = json::object();
        j["tool"] = x.get_tool();
        j["invocation"] = x.get_invocation();
        j["analysisToolLogFiles"] = x.get_analysis_tool_log_files();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Conversion& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ConversionProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Conversion & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::EdgeProperties& x) {
        x.set_id(j.at("id").get<libsarif::TartuGecko>());
        x.set_label(j.at("label").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_source_node_id(j.at("sourceNodeId").get<libsarif::TartuGecko>());
        x.set_target_node_id(j.at("targetNodeId").get<libsarif::TartuGecko>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::EdgeProperties & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["label"] = x.get_label();
        j["sourceNodeId"] = x.get_source_node_id();
        j["targetNodeId"] = x.get_target_node_id();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Edge& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::EdgeProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Edge & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::FinalState& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<libsarif::AdditionalPropertiesClass>());
    }

    inline void to_json(json & j, const libsarif::FinalState & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
    }

    inline void from_json(const json & j, libsarif::EdgeTraversalProperties& x) {
        x.set_edge_id(j.at("edgeId").get<libsarif::TartuGecko>());
        x.set_message(j.at("message").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_final_state(j.at("finalState").get<libsarif::FinalState>());
        x.set_step_over_edge_count(j.at("stepOverEdgeCount").get<libsarif::PuneHedgehog>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::EdgeTraversalProperties & x) {
        j = json::object();
        j["edgeId"] = x.get_edge_id();
        j["message"] = x.get_message();
        j["finalState"] = x.get_final_state();
        j["stepOverEdgeCount"] = x.get_step_over_edge_count();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::EdgeTraversal& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::EdgeTraversalProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::EdgeTraversal & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ExceptionProperties& x) {
        x.set_kind(j.at("kind").get<libsarif::TartuGecko>());
        x.set_message(j.at("message").get<libsarif::TartuGecko>());
        x.set_stack(j.at("stack").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_inner_exceptions(j.at("innerExceptions").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ExceptionProperties & x) {
        j = json::object();
        j["kind"] = x.get_kind();
        j["message"] = x.get_message();
        j["stack"] = x.get_stack();
        j["innerExceptions"] = x.get_inner_exceptions();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Exception& x) {
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ExceptionProperties>());
    }

    inline void to_json(json & j, const libsarif::Exception & x) {
        j = json::object();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Version& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_version_enum(j.at("enum").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Version & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["enum"] = x.get_version_enum();
    }

    inline void from_json(const json & j, libsarif::ExternalPropertiesProperties& x) {
        x.set_schema(j.at("schema").get<libsarif::Schema>());
        x.set_version(j.at("version").get<libsarif::Version>());
        x.set_guid(j.at("guid").get<libsarif::MimeType>());
        x.set_run_guid(j.at("runGuid").get<libsarif::MimeType>());
        x.set_conversion(j.at("conversion").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_graphs(j.at("graphs").get<libsarif::HammerfestPonies>());
        x.set_externalized_properties(j.at("externalizedProperties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_artifacts(j.at("artifacts").get<libsarif::HammerfestPonies>());
        x.set_invocations(j.at("invocations").get<libsarif::HammerfestPonies>());
        x.set_logical_locations(j.at("logicalLocations").get<libsarif::HammerfestPonies>());
        x.set_thread_flow_locations(j.at("threadFlowLocations").get<libsarif::HammerfestPonies>());
        x.set_results(j.at("results").get<libsarif::HammerfestPonies>());
        x.set_taxonomies(j.at("taxonomies").get<libsarif::HammerfestPonies>());
        x.set_driver(j.at("driver").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_extensions(j.at("extensions").get<libsarif::HammerfestPonies>());
        x.set_policies(j.at("policies").get<libsarif::HammerfestPonies>());
        x.set_translations(j.at("translations").get<libsarif::HammerfestPonies>());
        x.set_addresses(j.at("addresses").get<libsarif::HammerfestPonies>());
        x.set_web_requests(j.at("webRequests").get<libsarif::HammerfestPonies>());
        x.set_web_responses(j.at("webResponses").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ExternalPropertiesProperties & x) {
        j = json::object();
        j["schema"] = x.get_schema();
        j["version"] = x.get_version();
        j["guid"] = x.get_guid();
        j["runGuid"] = x.get_run_guid();
        j["conversion"] = x.get_conversion();
        j["graphs"] = x.get_graphs();
        j["externalizedProperties"] = x.get_externalized_properties();
        j["artifacts"] = x.get_artifacts();
        j["invocations"] = x.get_invocations();
        j["logicalLocations"] = x.get_logical_locations();
        j["threadFlowLocations"] = x.get_thread_flow_locations();
        j["results"] = x.get_results();
        j["taxonomies"] = x.get_taxonomies();
        j["driver"] = x.get_driver();
        j["extensions"] = x.get_extensions();
        j["policies"] = x.get_policies();
        j["translations"] = x.get_translations();
        j["addresses"] = x.get_addresses();
        j["webRequests"] = x.get_web_requests();
        j["webResponses"] = x.get_web_responses();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ExternalProperties& x) {
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ExternalPropertiesProperties>());
    }

    inline void to_json(json & j, const libsarif::ExternalProperties & x) {
        j = json::object();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Of& x) {
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Of & x) {
        j = json::object();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ExternalPropertyFileReferenceProperties& x) {
        x.set_location(j.at("location").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_guid(j.at("guid").get<libsarif::MimeType>());
        x.set_item_count(j.at("itemCount").get<libsarif::PuneHedgehog>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ExternalPropertyFileReferenceProperties & x) {
        j = json::object();
        j["location"] = x.get_location();
        j["guid"] = x.get_guid();
        j["itemCount"] = x.get_item_count();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ExternalPropertyFileReference& x) {
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ExternalPropertyFileReferenceProperties>());
        x.set_any_of(j.at("anyOf").get<std::vector<libsarif::Of>>());
    }

    inline void to_json(json & j, const libsarif::ExternalPropertyFileReference & x) {
        j = json::object();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["anyOf"] = x.get_any_of();
    }

    inline void from_json(const json & j, libsarif::ExternalPropertyFileReferencesProperties& x) {
        x.set_conversion(j.at("conversion").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_graphs(j.at("graphs").get<libsarif::HammerfestPonies>());
        x.set_externalized_properties(j.at("externalizedProperties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_artifacts(j.at("artifacts").get<libsarif::HammerfestPonies>());
        x.set_invocations(j.at("invocations").get<libsarif::HammerfestPonies>());
        x.set_logical_locations(j.at("logicalLocations").get<libsarif::HammerfestPonies>());
        x.set_thread_flow_locations(j.at("threadFlowLocations").get<libsarif::HammerfestPonies>());
        x.set_results(j.at("results").get<libsarif::HammerfestPonies>());
        x.set_taxonomies(j.at("taxonomies").get<libsarif::HammerfestPonies>());
        x.set_addresses(j.at("addresses").get<libsarif::HammerfestPonies>());
        x.set_driver(j.at("driver").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_extensions(j.at("extensions").get<libsarif::HammerfestPonies>());
        x.set_policies(j.at("policies").get<libsarif::HammerfestPonies>());
        x.set_translations(j.at("translations").get<libsarif::HammerfestPonies>());
        x.set_web_requests(j.at("webRequests").get<libsarif::HammerfestPonies>());
        x.set_web_responses(j.at("webResponses").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ExternalPropertyFileReferencesProperties & x) {
        j = json::object();
        j["conversion"] = x.get_conversion();
        j["graphs"] = x.get_graphs();
        j["externalizedProperties"] = x.get_externalized_properties();
        j["artifacts"] = x.get_artifacts();
        j["invocations"] = x.get_invocations();
        j["logicalLocations"] = x.get_logical_locations();
        j["threadFlowLocations"] = x.get_thread_flow_locations();
        j["results"] = x.get_results();
        j["taxonomies"] = x.get_taxonomies();
        j["addresses"] = x.get_addresses();
        j["driver"] = x.get_driver();
        j["extensions"] = x.get_extensions();
        j["policies"] = x.get_policies();
        j["translations"] = x.get_translations();
        j["webRequests"] = x.get_web_requests();
        j["webResponses"] = x.get_web_responses();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ExternalPropertyFileReferences& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ExternalPropertyFileReferencesProperties>());
    }

    inline void to_json(json & j, const libsarif::ExternalPropertyFileReferences & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::FixProperties& x) {
        x.set_description(j.at("description").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_artifact_changes(j.at("artifactChanges").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::FixProperties & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["artifactChanges"] = x.get_artifact_changes();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Fix& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::FixProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Fix & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::GraphProperties& x) {
        x.set_description(j.at("description").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_nodes(j.at("nodes").get<libsarif::HammerfestPonies>());
        x.set_edges(j.at("edges").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::GraphProperties & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["nodes"] = x.get_nodes();
        j["edges"] = x.get_edges();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Graph& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::GraphProperties>());
    }

    inline void to_json(json & j, const libsarif::Graph & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::GraphTraversalProperties& x) {
        x.set_run_graph_index(j.at("runGraphIndex").get<libsarif::PuneHedgehog>());
        x.set_result_graph_index(j.at("resultGraphIndex").get<libsarif::PuneHedgehog>());
        x.set_description(j.at("description").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_initial_state(j.at("initialState").get<libsarif::FinalState>());
        x.set_immutable_state(j.at("immutableState").get<libsarif::FinalState>());
        x.set_edge_traversals(j.at("edgeTraversals").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::GraphTraversalProperties & x) {
        j = json::object();
        j["runGraphIndex"] = x.get_run_graph_index();
        j["resultGraphIndex"] = x.get_result_graph_index();
        j["description"] = x.get_description();
        j["initialState"] = x.get_initial_state();
        j["immutableState"] = x.get_immutable_state();
        j["edgeTraversals"] = x.get_edge_traversals();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::GraphTraversal& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::GraphTraversalProperties>());
        x.set_one_of(j.at("oneOf").get<std::vector<libsarif::Of>>());
    }

    inline void to_json(json & j, const libsarif::GraphTraversal & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["oneOf"] = x.get_one_of();
    }

    inline void from_json(const json & j, libsarif::Arguments& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::FluffyType>());
        x.set_min_items(libsarif::get_optional<int64_t>(j, "minItems"));
        x.set_unique_items(j.at("uniqueItems").get<bool>());
        x.set_items(j.at("items").get<libsarif::AdditionalProperties>());
        x.set_arguments_default(libsarif::get_optional<std::vector<std::string>>(j, "default"));
    }

    inline void to_json(json & j, const libsarif::Arguments & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["minItems"] = x.get_min_items();
        j["uniqueItems"] = x.get_unique_items();
        j["items"] = x.get_items();
        j["default"] = x.get_arguments_default();
    }

    inline void from_json(const json & j, libsarif::InvocationProperties& x) {
        x.set_command_line(j.at("commandLine").get<libsarif::TartuGecko>());
        x.set_arguments(j.at("arguments").get<libsarif::Arguments>());
        x.set_response_files(j.at("responseFiles").get<libsarif::HammerfestPonies>());
        x.set_start_time_utc(j.at("startTimeUtc").get<libsarif::Schema>());
        x.set_end_time_utc(j.at("endTimeUtc").get<libsarif::Schema>());
        x.set_exit_code(j.at("exitCode").get<libsarif::TartuGecko>());
        x.set_rule_configuration_overrides(j.at("ruleConfigurationOverrides").get<libsarif::HammerfestPonies>());
        x.set_notification_configuration_overrides(j.at("notificationConfigurationOverrides").get<libsarif::HammerfestPonies>());
        x.set_tool_execution_notifications(j.at("toolExecutionNotifications").get<libsarif::HammerfestPonies>());
        x.set_tool_configuration_notifications(j.at("toolConfigurationNotifications").get<libsarif::HammerfestPonies>());
        x.set_exit_code_description(j.at("exitCodeDescription").get<libsarif::TartuGecko>());
        x.set_exit_signal_name(j.at("exitSignalName").get<libsarif::TartuGecko>());
        x.set_exit_signal_number(j.at("exitSignalNumber").get<libsarif::TartuGecko>());
        x.set_process_start_failure_message(j.at("processStartFailureMessage").get<libsarif::TartuGecko>());
        x.set_execution_successful(j.at("executionSuccessful").get<libsarif::TartuGecko>());
        x.set_machine(j.at("machine").get<libsarif::TartuGecko>());
        x.set_account(j.at("account").get<libsarif::TartuGecko>());
        x.set_process_id(j.at("processId").get<libsarif::TartuGecko>());
        x.set_executable_location(j.at("executableLocation").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_working_directory(j.at("workingDirectory").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_environment_variables(j.at("environmentVariables").get<libsarif::Hashes>());
        x.set_stdin(j.at("stdin").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_stdout(j.at("stdout").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_stderr(j.at("stderr").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_stdout_stderr(j.at("stdoutStderr").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::InvocationProperties & x) {
        j = json::object();
        j["commandLine"] = x.get_command_line();
        j["arguments"] = x.get_arguments();
        j["responseFiles"] = x.get_response_files();
        j["startTimeUtc"] = x.get_start_time_utc();
        j["endTimeUtc"] = x.get_end_time_utc();
        j["exitCode"] = x.get_exit_code();
        j["ruleConfigurationOverrides"] = x.get_rule_configuration_overrides();
        j["notificationConfigurationOverrides"] = x.get_notification_configuration_overrides();
        j["toolExecutionNotifications"] = x.get_tool_execution_notifications();
        j["toolConfigurationNotifications"] = x.get_tool_configuration_notifications();
        j["exitCodeDescription"] = x.get_exit_code_description();
        j["exitSignalName"] = x.get_exit_signal_name();
        j["exitSignalNumber"] = x.get_exit_signal_number();
        j["processStartFailureMessage"] = x.get_process_start_failure_message();
        j["executionSuccessful"] = x.get_execution_successful();
        j["machine"] = x.get_machine();
        j["account"] = x.get_account();
        j["processId"] = x.get_process_id();
        j["executableLocation"] = x.get_executable_location();
        j["workingDirectory"] = x.get_working_directory();
        j["environmentVariables"] = x.get_environment_variables();
        j["stdin"] = x.get_stdin();
        j["stdout"] = x.get_stdout();
        j["stderr"] = x.get_stderr();
        j["stdoutStderr"] = x.get_stdout_stderr();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Invocation& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::InvocationProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Invocation & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::LocationProperties& x) {
        x.set_id(j.at("id").get<libsarif::PuneHedgehog>());
        x.set_physical_location(j.at("physicalLocation").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_logical_locations(j.at("logicalLocations").get<libsarif::HammerfestPonies>());
        x.set_message(j.at("message").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_annotations(j.at("annotations").get<libsarif::HammerfestPonies>());
        x.set_relationships(j.at("relationships").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::LocationProperties & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["physicalLocation"] = x.get_physical_location();
        j["logicalLocations"] = x.get_logical_locations();
        j["message"] = x.get_message();
        j["annotations"] = x.get_annotations();
        j["relationships"] = x.get_relationships();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Location& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::LocationProperties>());
    }

    inline void to_json(json & j, const libsarif::Location & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::LocationRelationshipProperties& x) {
        x.set_target(j.at("target").get<libsarif::PuneHedgehog>());
        x.set_kinds(j.at("kinds").get<libsarif::Arguments>());
        x.set_description(j.at("description").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::LocationRelationshipProperties & x) {
        j = json::object();
        j["target"] = x.get_target();
        j["kinds"] = x.get_kinds();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::LocationRelationship& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::LocationRelationshipProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::LocationRelationship & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::LogicalLocationProperties& x) {
        x.set_name(j.at("name").get<libsarif::TartuGecko>());
        x.set_index(j.at("index").get<libsarif::PuneHedgehog>());
        x.set_fully_qualified_name(j.at("fullyQualifiedName").get<libsarif::TartuGecko>());
        x.set_decorated_name(j.at("decoratedName").get<libsarif::TartuGecko>());
        x.set_parent_index(j.at("parentIndex").get<libsarif::PuneHedgehog>());
        x.set_kind(j.at("kind").get<libsarif::TartuGecko>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::LogicalLocationProperties & x) {
        j = json::object();
        j["name"] = x.get_name();
        j["index"] = x.get_index();
        j["fullyQualifiedName"] = x.get_fully_qualified_name();
        j["decoratedName"] = x.get_decorated_name();
        j["parentIndex"] = x.get_parent_index();
        j["kind"] = x.get_kind();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::LogicalLocation& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::LogicalLocationProperties>());
    }

    inline void to_json(json & j, const libsarif::LogicalLocation & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::MessageProperties& x) {
        x.set_text(j.at("text").get<libsarif::TartuGecko>());
        x.set_markdown(j.at("markdown").get<libsarif::TartuGecko>());
        x.set_id(j.at("id").get<libsarif::TartuGecko>());
        x.set_arguments(j.at("arguments").get<libsarif::Arguments>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::MessageProperties & x) {
        j = json::object();
        j["text"] = x.get_text();
        j["markdown"] = x.get_markdown();
        j["id"] = x.get_id();
        j["arguments"] = x.get_arguments();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Message& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::MessageProperties>());
        x.set_any_of(j.at("anyOf").get<std::vector<libsarif::Of>>());
    }

    inline void to_json(json & j, const libsarif::Message & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["anyOf"] = x.get_any_of();
    }

    inline void from_json(const json & j, libsarif::MultiformatMessageStringProperties& x) {
        x.set_text(j.at("text").get<libsarif::TartuGecko>());
        x.set_markdown(j.at("markdown").get<libsarif::TartuGecko>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::MultiformatMessageStringProperties & x) {
        j = json::object();
        j["text"] = x.get_text();
        j["markdown"] = x.get_markdown();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::MultiformatMessageString& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::MultiformatMessageStringProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::MultiformatMessageString & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::NodeProperties& x) {
        x.set_id(j.at("id").get<libsarif::TartuGecko>());
        x.set_label(j.at("label").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_location(j.at("location").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_children(j.at("children").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::NodeProperties & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["label"] = x.get_label();
        j["location"] = x.get_location();
        j["children"] = x.get_children();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Node& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::NodeProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Node & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::Level& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_level_default(j.at("default").get<std::string>());
        x.set_level_enum(j.at("enum").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Level & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["default"] = x.get_level_default();
        j["enum"] = x.get_level_enum();
    }

    inline void from_json(const json & j, libsarif::NotificationProperties& x) {
        x.set_locations(j.at("locations").get<libsarif::HammerfestPonies>());
        x.set_message(j.at("message").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_level(j.at("level").get<libsarif::Level>());
        x.set_thread_id(j.at("threadId").get<libsarif::TartuGecko>());
        x.set_time_utc(j.at("timeUtc").get<libsarif::Schema>());
        x.set_exception(j.at("exception").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_descriptor(j.at("descriptor").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_associated_rule(j.at("associatedRule").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::NotificationProperties & x) {
        j = json::object();
        j["locations"] = x.get_locations();
        j["message"] = x.get_message();
        j["level"] = x.get_level();
        j["threadId"] = x.get_thread_id();
        j["timeUtc"] = x.get_time_utc();
        j["exception"] = x.get_exception();
        j["descriptor"] = x.get_descriptor();
        j["associatedRule"] = x.get_associated_rule();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Notification& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::NotificationProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Notification & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::PhysicalLocationProperties& x) {
        x.set_address(j.at("address").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_artifact_location(j.at("artifactLocation").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_region(j.at("region").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_context_region(j.at("contextRegion").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::PhysicalLocationProperties & x) {
        j = json::object();
        j["address"] = x.get_address();
        j["artifactLocation"] = x.get_artifact_location();
        j["region"] = x.get_region();
        j["contextRegion"] = x.get_context_region();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::PhysicalLocation& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::PhysicalLocationProperties>());
        x.set_any_of(j.at("anyOf").get<std::vector<libsarif::Of>>());
    }

    inline void to_json(json & j, const libsarif::PhysicalLocation & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["anyOf"] = x.get_any_of();
    }

    inline void from_json(const json & j, libsarif::PropertyBagProperties& x) {
        x.set_tags(j.at("tags").get<libsarif::Arguments>());
    }

    inline void to_json(json & j, const libsarif::PropertyBagProperties & x) {
        j = json::object();
        j["tags"] = x.get_tags();
    }

    inline void from_json(const json & j, libsarif::PropertyBag& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::PropertyBagProperties>());
    }

    inline void to_json(json & j, const libsarif::PropertyBag & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::RectangleProperties& x) {
        x.set_top(j.at("top").get<libsarif::TartuGecko>());
        x.set_left(j.at("left").get<libsarif::TartuGecko>());
        x.set_bottom(j.at("bottom").get<libsarif::TartuGecko>());
        x.set_right(j.at("right").get<libsarif::TartuGecko>());
        x.set_message(j.at("message").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::RectangleProperties & x) {
        j = json::object();
        j["top"] = x.get_top();
        j["left"] = x.get_left();
        j["bottom"] = x.get_bottom();
        j["right"] = x.get_right();
        j["message"] = x.get_message();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Rectangle& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::RectangleProperties>());
    }

    inline void to_json(json & j, const libsarif::Rectangle & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::RegionProperties& x) {
        x.set_start_line(j.at("startLine").get<libsarif::PuneHedgehog>());
        x.set_start_column(j.at("startColumn").get<libsarif::PuneHedgehog>());
        x.set_end_line(j.at("endLine").get<libsarif::PuneHedgehog>());
        x.set_end_column(j.at("endColumn").get<libsarif::PuneHedgehog>());
        x.set_char_offset(j.at("charOffset").get<libsarif::PuneHedgehog>());
        x.set_char_length(j.at("charLength").get<libsarif::PuneHedgehog>());
        x.set_byte_offset(j.at("byteOffset").get<libsarif::PuneHedgehog>());
        x.set_byte_length(j.at("byteLength").get<libsarif::PuneHedgehog>());
        x.set_snippet(j.at("snippet").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_message(j.at("message").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_source_language(j.at("sourceLanguage").get<libsarif::TartuGecko>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::RegionProperties & x) {
        j = json::object();
        j["startLine"] = x.get_start_line();
        j["startColumn"] = x.get_start_column();
        j["endLine"] = x.get_end_line();
        j["endColumn"] = x.get_end_column();
        j["charOffset"] = x.get_char_offset();
        j["charLength"] = x.get_char_length();
        j["byteOffset"] = x.get_byte_offset();
        j["byteLength"] = x.get_byte_length();
        j["snippet"] = x.get_snippet();
        j["message"] = x.get_message();
        j["sourceLanguage"] = x.get_source_language();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Region& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::RegionProperties>());
    }

    inline void to_json(json & j, const libsarif::Region & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ReplacementProperties& x) {
        x.set_deleted_region(j.at("deletedRegion").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_inserted_content(j.at("insertedContent").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ReplacementProperties & x) {
        j = json::object();
        j["deletedRegion"] = x.get_deleted_region();
        j["insertedContent"] = x.get_inserted_content();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Replacement& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ReplacementProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Replacement & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::Enabled& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::PurpleType>());
        x.set_enabled_default(j.at("default").get<bool>());
    }

    inline void to_json(json & j, const libsarif::Enabled & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["default"] = x.get_enabled_default();
    }

    inline void from_json(const json & j, libsarif::ReportingConfigurationProperties& x) {
        x.set_enabled(j.at("enabled").get<libsarif::Enabled>());
        x.set_level(j.at("level").get<libsarif::Level>());
        x.set_rank(j.at("rank").get<libsarif::PuneHedgehog>());
        x.set_parameters(j.at("parameters").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ReportingConfigurationProperties & x) {
        j = json::object();
        j["enabled"] = x.get_enabled();
        j["level"] = x.get_level();
        j["rank"] = x.get_rank();
        j["parameters"] = x.get_parameters();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ReportingConfiguration& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::ReportingConfigurationProperties>());
    }

    inline void to_json(json & j, const libsarif::ReportingConfiguration & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::DeprecatedGuidsItems& x) {
        x.set_type(j.at("type").get<libsarif::PurpleType>());
        x.set_pattern(j.at("pattern").get<std::string>());
    }

    inline void to_json(json & j, const libsarif::DeprecatedGuidsItems & x) {
        j = json::object();
        j["type"] = x.get_type();
        j["pattern"] = x.get_pattern();
    }

    inline void from_json(const json & j, libsarif::DeprecatedGuids& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::FluffyType>());
        x.set_min_items(j.at("minItems").get<int64_t>());
        x.set_unique_items(j.at("uniqueItems").get<bool>());
        x.set_items(j.at("items").get<libsarif::DeprecatedGuidsItems>());
    }

    inline void to_json(json & j, const libsarif::DeprecatedGuids & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["minItems"] = x.get_min_items();
        j["uniqueItems"] = x.get_unique_items();
        j["items"] = x.get_items();
    }

    inline void from_json(const json & j, libsarif::ReportingDescriptorProperties& x) {
        x.set_id(j.at("id").get<libsarif::TartuGecko>());
        x.set_deprecated_ids(j.at("deprecatedIds").get<libsarif::Arguments>());
        x.set_guid(j.at("guid").get<libsarif::MimeType>());
        x.set_deprecated_guids(j.at("deprecatedGuids").get<libsarif::DeprecatedGuids>());
        x.set_name(j.at("name").get<libsarif::TartuGecko>());
        x.set_deprecated_names(j.at("deprecatedNames").get<libsarif::Arguments>());
        x.set_short_description(j.at("shortDescription").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_full_description(j.at("fullDescription").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_message_strings(j.at("messageStrings").get<libsarif::FinalState>());
        x.set_default_configuration(j.at("defaultConfiguration").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_help_uri(j.at("helpUri").get<libsarif::Schema>());
        x.set_help(j.at("help").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_relationships(j.at("relationships").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ReportingDescriptorProperties & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["deprecatedIds"] = x.get_deprecated_ids();
        j["guid"] = x.get_guid();
        j["deprecatedGuids"] = x.get_deprecated_guids();
        j["name"] = x.get_name();
        j["deprecatedNames"] = x.get_deprecated_names();
        j["shortDescription"] = x.get_short_description();
        j["fullDescription"] = x.get_full_description();
        j["messageStrings"] = x.get_message_strings();
        j["defaultConfiguration"] = x.get_default_configuration();
        j["helpUri"] = x.get_help_uri();
        j["help"] = x.get_help();
        j["relationships"] = x.get_relationships();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ReportingDescriptor& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ReportingDescriptorProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::ReportingDescriptor & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ReportingDescriptorReferenceProperties& x) {
        x.set_id(j.at("id").get<libsarif::TartuGecko>());
        x.set_index(j.at("index").get<libsarif::PuneHedgehog>());
        x.set_guid(j.at("guid").get<libsarif::MimeType>());
        x.set_tool_component(j.at("toolComponent").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ReportingDescriptorReferenceProperties & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["index"] = x.get_index();
        j["guid"] = x.get_guid();
        j["toolComponent"] = x.get_tool_component();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ReportingDescriptorReference& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::ReportingDescriptorReferenceProperties>());
        x.set_any_of(j.at("anyOf").get<std::vector<libsarif::Of>>());
    }

    inline void to_json(json & j, const libsarif::ReportingDescriptorReference & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["anyOf"] = x.get_any_of();
    }

    inline void from_json(const json & j, libsarif::ReportingDescriptorRelationshipProperties& x) {
        x.set_target(j.at("target").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_kinds(j.at("kinds").get<libsarif::Arguments>());
        x.set_description(j.at("description").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ReportingDescriptorRelationshipProperties & x) {
        j = json::object();
        j["target"] = x.get_target();
        j["kinds"] = x.get_kinds();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ReportingDescriptorRelationship& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::ReportingDescriptorRelationshipProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::ReportingDescriptorRelationship & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::WorkItemUrisItems& x) {
        x.set_type(j.at("type").get<libsarif::PurpleType>());
        x.set_format(j.at("format").get<libsarif::Format>());
    }

    inline void to_json(json & j, const libsarif::WorkItemUrisItems & x) {
        j = json::object();
        j["type"] = x.get_type();
        j["format"] = x.get_format();
    }

    inline void from_json(const json & j, libsarif::WorkItemUris& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::FluffyType>());
        x.set_min_items(j.at("minItems").get<int64_t>());
        x.set_unique_items(j.at("uniqueItems").get<bool>());
        x.set_items(j.at("items").get<libsarif::WorkItemUrisItems>());
    }

    inline void to_json(json & j, const libsarif::WorkItemUris & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["minItems"] = x.get_min_items();
        j["uniqueItems"] = x.get_unique_items();
        j["items"] = x.get_items();
    }

    inline void from_json(const json & j, libsarif::ResultProperties& x) {
        x.set_rule_id(j.at("ruleId").get<libsarif::TartuGecko>());
        x.set_rule_index(j.at("ruleIndex").get<libsarif::PuneHedgehog>());
        x.set_rule(j.at("rule").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_kind(j.at("kind").get<libsarif::Level>());
        x.set_level(j.at("level").get<libsarif::Level>());
        x.set_message(j.at("message").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_analysis_target(j.at("analysisTarget").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_locations(j.at("locations").get<libsarif::HammerfestPonies>());
        x.set_guid(j.at("guid").get<libsarif::MimeType>());
        x.set_correlation_guid(j.at("correlationGuid").get<libsarif::MimeType>());
        x.set_occurrence_count(j.at("occurrenceCount").get<libsarif::PuneHedgehog>());
        x.set_partial_fingerprints(j.at("partialFingerprints").get<libsarif::Hashes>());
        x.set_fingerprints(j.at("fingerprints").get<libsarif::Hashes>());
        x.set_stacks(j.at("stacks").get<libsarif::HammerfestPonies>());
        x.set_code_flows(j.at("codeFlows").get<libsarif::HammerfestPonies>());
        x.set_graphs(j.at("graphs").get<libsarif::HammerfestPonies>());
        x.set_graph_traversals(j.at("graphTraversals").get<libsarif::HammerfestPonies>());
        x.set_related_locations(j.at("relatedLocations").get<libsarif::HammerfestPonies>());
        x.set_suppressions(j.at("suppressions").get<libsarif::HammerfestPonies>());
        x.set_baseline_state(j.at("baselineState").get<libsarif::Version>());
        x.set_rank(j.at("rank").get<libsarif::PuneHedgehog>());
        x.set_attachments(j.at("attachments").get<libsarif::HammerfestPonies>());
        x.set_hosted_viewer_uri(j.at("hostedViewerUri").get<libsarif::Schema>());
        x.set_work_item_uris(j.at("workItemUris").get<libsarif::WorkItemUris>());
        x.set_provenance(j.at("provenance").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_fixes(j.at("fixes").get<libsarif::HammerfestPonies>());
        x.set_taxa(j.at("taxa").get<libsarif::HammerfestPonies>());
        x.set_web_request(j.at("webRequest").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_web_response(j.at("webResponse").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ResultProperties & x) {
        j = json::object();
        j["ruleId"] = x.get_rule_id();
        j["ruleIndex"] = x.get_rule_index();
        j["rule"] = x.get_rule();
        j["kind"] = x.get_kind();
        j["level"] = x.get_level();
        j["message"] = x.get_message();
        j["analysisTarget"] = x.get_analysis_target();
        j["locations"] = x.get_locations();
        j["guid"] = x.get_guid();
        j["correlationGuid"] = x.get_correlation_guid();
        j["occurrenceCount"] = x.get_occurrence_count();
        j["partialFingerprints"] = x.get_partial_fingerprints();
        j["fingerprints"] = x.get_fingerprints();
        j["stacks"] = x.get_stacks();
        j["codeFlows"] = x.get_code_flows();
        j["graphs"] = x.get_graphs();
        j["graphTraversals"] = x.get_graph_traversals();
        j["relatedLocations"] = x.get_related_locations();
        j["suppressions"] = x.get_suppressions();
        j["baselineState"] = x.get_baseline_state();
        j["rank"] = x.get_rank();
        j["attachments"] = x.get_attachments();
        j["hostedViewerUri"] = x.get_hosted_viewer_uri();
        j["workItemUris"] = x.get_work_item_uris();
        j["provenance"] = x.get_provenance();
        j["fixes"] = x.get_fixes();
        j["taxa"] = x.get_taxa();
        j["webRequest"] = x.get_web_request();
        j["webResponse"] = x.get_web_response();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Result& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Result & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ResultProvenanceProperties& x) {
        x.set_first_detection_time_utc(j.at("firstDetectionTimeUtc").get<libsarif::Schema>());
        x.set_last_detection_time_utc(j.at("lastDetectionTimeUtc").get<libsarif::Schema>());
        x.set_first_detection_run_guid(j.at("firstDetectionRunGuid").get<libsarif::MimeType>());
        x.set_last_detection_run_guid(j.at("lastDetectionRunGuid").get<libsarif::MimeType>());
        x.set_invocation_index(j.at("invocationIndex").get<libsarif::PuneHedgehog>());
        x.set_conversion_sources(j.at("conversionSources").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ResultProvenanceProperties & x) {
        j = json::object();
        j["firstDetectionTimeUtc"] = x.get_first_detection_time_utc();
        j["lastDetectionTimeUtc"] = x.get_last_detection_time_utc();
        j["firstDetectionRunGuid"] = x.get_first_detection_run_guid();
        j["lastDetectionRunGuid"] = x.get_last_detection_run_guid();
        j["invocationIndex"] = x.get_invocation_index();
        j["conversionSources"] = x.get_conversion_sources();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ResultProvenance& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ResultProvenanceProperties>());
    }

    inline void to_json(json & j, const libsarif::ResultProvenance & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::RunProperties& x) {
        x.set_tool(j.at("tool").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_invocations(j.at("invocations").get<libsarif::HammerfestPonies>());
        x.set_conversion(j.at("conversion").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_language(j.at("language").get<libsarif::MimeType>());
        x.set_version_control_provenance(j.at("versionControlProvenance").get<libsarif::HammerfestPonies>());
        x.set_original_uri_base_ids(j.at("originalUriBaseIds").get<libsarif::FinalState>());
        x.set_artifacts(j.at("artifacts").get<libsarif::HammerfestPonies>());
        x.set_logical_locations(j.at("logicalLocations").get<libsarif::HammerfestPonies>());
        x.set_graphs(j.at("graphs").get<libsarif::HammerfestPonies>());
        x.set_results(j.at("results").get<libsarif::HammerfestPonies>());
        x.set_automation_details(j.at("automationDetails").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_run_aggregates(j.at("runAggregates").get<libsarif::HammerfestPonies>());
        x.set_baseline_guid(j.at("baselineGuid").get<libsarif::MimeType>());
        x.set_redaction_tokens(j.at("redactionTokens").get<libsarif::Arguments>());
        x.set_default_encoding(j.at("defaultEncoding").get<libsarif::TartuGecko>());
        x.set_default_source_language(j.at("defaultSourceLanguage").get<libsarif::TartuGecko>());
        x.set_newline_sequences(j.at("newlineSequences").get<libsarif::Arguments>());
        x.set_column_kind(j.at("columnKind").get<libsarif::Version>());
        x.set_external_property_file_references(j.at("externalPropertyFileReferences").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_thread_flow_locations(j.at("threadFlowLocations").get<libsarif::HammerfestPonies>());
        x.set_taxonomies(j.at("taxonomies").get<libsarif::HammerfestPonies>());
        x.set_addresses(j.at("addresses").get<libsarif::HammerfestPonies>());
        x.set_translations(j.at("translations").get<libsarif::HammerfestPonies>());
        x.set_policies(j.at("policies").get<libsarif::HammerfestPonies>());
        x.set_web_requests(j.at("webRequests").get<libsarif::HammerfestPonies>());
        x.set_web_responses(j.at("webResponses").get<libsarif::HammerfestPonies>());
        x.set_special_locations(j.at("specialLocations").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::RunProperties & x) {
        j = json::object();
        j["tool"] = x.get_tool();
        j["invocations"] = x.get_invocations();
        j["conversion"] = x.get_conversion();
        j["language"] = x.get_language();
        j["versionControlProvenance"] = x.get_version_control_provenance();
        j["originalUriBaseIds"] = x.get_original_uri_base_ids();
        j["artifacts"] = x.get_artifacts();
        j["logicalLocations"] = x.get_logical_locations();
        j["graphs"] = x.get_graphs();
        j["results"] = x.get_results();
        j["automationDetails"] = x.get_automation_details();
        j["runAggregates"] = x.get_run_aggregates();
        j["baselineGuid"] = x.get_baseline_guid();
        j["redactionTokens"] = x.get_redaction_tokens();
        j["defaultEncoding"] = x.get_default_encoding();
        j["defaultSourceLanguage"] = x.get_default_source_language();
        j["newlineSequences"] = x.get_newline_sequences();
        j["columnKind"] = x.get_column_kind();
        j["externalPropertyFileReferences"] = x.get_external_property_file_references();
        j["threadFlowLocations"] = x.get_thread_flow_locations();
        j["taxonomies"] = x.get_taxonomies();
        j["addresses"] = x.get_addresses();
        j["translations"] = x.get_translations();
        j["policies"] = x.get_policies();
        j["webRequests"] = x.get_web_requests();
        j["webResponses"] = x.get_web_responses();
        j["specialLocations"] = x.get_special_locations();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Run& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::RunProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Run & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::RunAutomationDetailsProperties& x) {
        x.set_description(j.at("description").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_id(j.at("id").get<libsarif::TartuGecko>());
        x.set_guid(j.at("guid").get<libsarif::MimeType>());
        x.set_correlation_guid(j.at("correlationGuid").get<libsarif::MimeType>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::RunAutomationDetailsProperties & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["id"] = x.get_id();
        j["guid"] = x.get_guid();
        j["correlationGuid"] = x.get_correlation_guid();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::RunAutomationDetails& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::RunAutomationDetailsProperties>());
    }

    inline void to_json(json & j, const libsarif::RunAutomationDetails & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::SpecialLocationsProperties& x) {
        x.set_display_base(j.at("displayBase").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::SpecialLocationsProperties & x) {
        j = json::object();
        j["displayBase"] = x.get_display_base();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::SpecialLocations& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::SpecialLocationsProperties>());
    }

    inline void to_json(json & j, const libsarif::SpecialLocations & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::StackProperties& x) {
        x.set_message(j.at("message").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_frames(j.at("frames").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::StackProperties & x) {
        j = json::object();
        j["message"] = x.get_message();
        j["frames"] = x.get_frames();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Stack& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::StackProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Stack & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ParametersItems& x) {
        x.set_type(j.at("type").get<libsarif::PurpleType>());
        x.set_items_default(j.at("default").get<std::vector<json>>());
    }

    inline void to_json(json & j, const libsarif::ParametersItems & x) {
        j = json::object();
        j["type"] = x.get_type();
        j["default"] = x.get_items_default();
    }

    inline void from_json(const json & j, libsarif::Parameters& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<libsarif::FluffyType>());
        x.set_min_items(j.at("minItems").get<int64_t>());
        x.set_unique_items(j.at("uniqueItems").get<bool>());
        x.set_parameters_default(j.at("default").get<std::vector<json>>());
        x.set_items(j.at("items").get<libsarif::ParametersItems>());
    }

    inline void to_json(json & j, const libsarif::Parameters & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["minItems"] = x.get_min_items();
        j["uniqueItems"] = x.get_unique_items();
        j["default"] = x.get_parameters_default();
        j["items"] = x.get_items();
    }

    inline void from_json(const json & j, libsarif::StackFrameProperties& x) {
        x.set_location(j.at("location").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties_module(j.at("module").get<libsarif::TartuGecko>());
        x.set_thread_id(j.at("threadId").get<libsarif::TartuGecko>());
        x.set_parameters(j.at("parameters").get<libsarif::Parameters>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::StackFrameProperties & x) {
        j = json::object();
        j["location"] = x.get_location();
        j["module"] = x.get_properties_module();
        j["threadId"] = x.get_thread_id();
        j["parameters"] = x.get_parameters();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::StackFrame& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::StackFrameProperties>());
    }

    inline void to_json(json & j, const libsarif::StackFrame & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::SuppressionProperties& x) {
        x.set_guid(j.at("guid").get<libsarif::MimeType>());
        x.set_kind(j.at("kind").get<libsarif::Version>());
        x.set_state(j.at("state").get<libsarif::Version>());
        x.set_justification(j.at("justification").get<libsarif::TartuGecko>());
        x.set_location(j.at("location").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::SuppressionProperties & x) {
        j = json::object();
        j["guid"] = x.get_guid();
        j["kind"] = x.get_kind();
        j["state"] = x.get_state();
        j["justification"] = x.get_justification();
        j["location"] = x.get_location();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Suppression& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::SuppressionProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Suppression & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ThreadFlowProperties& x) {
        x.set_id(j.at("id").get<libsarif::TartuGecko>());
        x.set_message(j.at("message").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_initial_state(j.at("initialState").get<libsarif::FinalState>());
        x.set_immutable_state(j.at("immutableState").get<libsarif::FinalState>());
        x.set_locations(j.at("locations").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ThreadFlowProperties & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["message"] = x.get_message();
        j["initialState"] = x.get_initial_state();
        j["immutableState"] = x.get_immutable_state();
        j["locations"] = x.get_locations();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ThreadFlow& x) {
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ThreadFlowProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::ThreadFlow & x) {
        j = json::object();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ThreadFlowLocationProperties& x) {
        x.set_index(j.at("index").get<libsarif::PuneHedgehog>());
        x.set_location(j.at("location").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_stack(j.at("stack").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_kinds(j.at("kinds").get<libsarif::Arguments>());
        x.set_taxa(j.at("taxa").get<libsarif::HammerfestPonies>());
        x.set_properties_module(j.at("module").get<libsarif::TartuGecko>());
        x.set_state(j.at("state").get<libsarif::FinalState>());
        x.set_nesting_level(j.at("nestingLevel").get<libsarif::PuneHedgehog>());
        x.set_execution_order(j.at("executionOrder").get<libsarif::PuneHedgehog>());
        x.set_execution_time_utc(j.at("executionTimeUtc").get<libsarif::Schema>());
        x.set_importance(j.at("importance").get<libsarif::Level>());
        x.set_web_request(j.at("webRequest").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_web_response(j.at("webResponse").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ThreadFlowLocationProperties & x) {
        j = json::object();
        j["index"] = x.get_index();
        j["location"] = x.get_location();
        j["stack"] = x.get_stack();
        j["kinds"] = x.get_kinds();
        j["taxa"] = x.get_taxa();
        j["module"] = x.get_properties_module();
        j["state"] = x.get_state();
        j["nestingLevel"] = x.get_nesting_level();
        j["executionOrder"] = x.get_execution_order();
        j["executionTimeUtc"] = x.get_execution_time_utc();
        j["importance"] = x.get_importance();
        j["webRequest"] = x.get_web_request();
        j["webResponse"] = x.get_web_response();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ThreadFlowLocation& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ThreadFlowLocationProperties>());
    }

    inline void to_json(json & j, const libsarif::ThreadFlowLocation & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ToolProperties& x) {
        x.set_driver(j.at("driver").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_extensions(j.at("extensions").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ToolProperties & x) {
        j = json::object();
        j["driver"] = x.get_driver();
        j["extensions"] = x.get_extensions();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Tool& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ToolProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::Tool & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ToolComponentProperties& x) {
        x.set_guid(j.at("guid").get<libsarif::MimeType>());
        x.set_name(j.at("name").get<libsarif::TartuGecko>());
        x.set_organization(j.at("organization").get<libsarif::TartuGecko>());
        x.set_product(j.at("product").get<libsarif::TartuGecko>());
        x.set_product_suite(j.at("productSuite").get<libsarif::TartuGecko>());
        x.set_short_description(j.at("shortDescription").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_full_description(j.at("fullDescription").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_full_name(j.at("fullName").get<libsarif::TartuGecko>());
        x.set_version(j.at("version").get<libsarif::TartuGecko>());
        x.set_semantic_version(j.at("semanticVersion").get<libsarif::TartuGecko>());
        x.set_dotted_quad_file_version(j.at("dottedQuadFileVersion").get<libsarif::MimeType>());
        x.set_release_date_utc(j.at("releaseDateUtc").get<libsarif::TartuGecko>());
        x.set_download_uri(j.at("downloadUri").get<libsarif::Schema>());
        x.set_information_uri(j.at("informationUri").get<libsarif::Schema>());
        x.set_global_message_strings(j.at("globalMessageStrings").get<libsarif::FinalState>());
        x.set_notifications(j.at("notifications").get<libsarif::HammerfestPonies>());
        x.set_rules(j.at("rules").get<libsarif::HammerfestPonies>());
        x.set_taxa(j.at("taxa").get<libsarif::HammerfestPonies>());
        x.set_locations(j.at("locations").get<libsarif::HammerfestPonies>());
        x.set_language(j.at("language").get<libsarif::MimeType>());
        x.set_contents(j.at("contents").get<libsarif::Roles>());
        x.set_is_comprehensive(j.at("isComprehensive").get<libsarif::Enabled>());
        x.set_localized_data_semantic_version(j.at("localizedDataSemanticVersion").get<libsarif::TartuGecko>());
        x.set_minimum_required_localized_data_semantic_version(j.at("minimumRequiredLocalizedDataSemanticVersion").get<libsarif::TartuGecko>());
        x.set_associated_component(j.at("associatedComponent").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_translation_metadata(j.at("translationMetadata").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_supported_taxonomies(j.at("supportedTaxonomies").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ToolComponentProperties & x) {
        j = json::object();
        j["guid"] = x.get_guid();
        j["name"] = x.get_name();
        j["organization"] = x.get_organization();
        j["product"] = x.get_product();
        j["productSuite"] = x.get_product_suite();
        j["shortDescription"] = x.get_short_description();
        j["fullDescription"] = x.get_full_description();
        j["fullName"] = x.get_full_name();
        j["version"] = x.get_version();
        j["semanticVersion"] = x.get_semantic_version();
        j["dottedQuadFileVersion"] = x.get_dotted_quad_file_version();
        j["releaseDateUtc"] = x.get_release_date_utc();
        j["downloadUri"] = x.get_download_uri();
        j["informationUri"] = x.get_information_uri();
        j["globalMessageStrings"] = x.get_global_message_strings();
        j["notifications"] = x.get_notifications();
        j["rules"] = x.get_rules();
        j["taxa"] = x.get_taxa();
        j["locations"] = x.get_locations();
        j["language"] = x.get_language();
        j["contents"] = x.get_contents();
        j["isComprehensive"] = x.get_is_comprehensive();
        j["localizedDataSemanticVersion"] = x.get_localized_data_semantic_version();
        j["minimumRequiredLocalizedDataSemanticVersion"] = x.get_minimum_required_localized_data_semantic_version();
        j["associatedComponent"] = x.get_associated_component();
        j["translationMetadata"] = x.get_translation_metadata();
        j["supportedTaxonomies"] = x.get_supported_taxonomies();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ToolComponent& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ToolComponentProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::ToolComponent & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::ToolComponentReferenceProperties& x) {
        x.set_name(j.at("name").get<libsarif::TartuGecko>());
        x.set_index(j.at("index").get<libsarif::PuneHedgehog>());
        x.set_guid(j.at("guid").get<libsarif::MimeType>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::ToolComponentReferenceProperties & x) {
        j = json::object();
        j["name"] = x.get_name();
        j["index"] = x.get_index();
        j["guid"] = x.get_guid();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ToolComponentReference& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::ToolComponentReferenceProperties>());
    }

    inline void to_json(json & j, const libsarif::ToolComponentReference & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::TranslationMetadataProperties& x) {
        x.set_name(j.at("name").get<libsarif::TartuGecko>());
        x.set_full_name(j.at("fullName").get<libsarif::TartuGecko>());
        x.set_short_description(j.at("shortDescription").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_full_description(j.at("fullDescription").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_download_uri(j.at("downloadUri").get<libsarif::Schema>());
        x.set_information_uri(j.at("informationUri").get<libsarif::Schema>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::TranslationMetadataProperties & x) {
        j = json::object();
        j["name"] = x.get_name();
        j["fullName"] = x.get_full_name();
        j["shortDescription"] = x.get_short_description();
        j["fullDescription"] = x.get_full_description();
        j["downloadUri"] = x.get_download_uri();
        j["informationUri"] = x.get_information_uri();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::TranslationMetadata& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::TranslationMetadataProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::TranslationMetadata & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::VersionControlDetailsProperties& x) {
        x.set_repository_uri(j.at("repositoryUri").get<libsarif::Schema>());
        x.set_revision_id(j.at("revisionId").get<libsarif::TartuGecko>());
        x.set_branch(j.at("branch").get<libsarif::TartuGecko>());
        x.set_revision_tag(j.at("revisionTag").get<libsarif::TartuGecko>());
        x.set_as_of_time_utc(j.at("asOfTimeUtc").get<libsarif::Schema>());
        x.set_mapped_to(j.at("mappedTo").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::VersionControlDetailsProperties & x) {
        j = json::object();
        j["repositoryUri"] = x.get_repository_uri();
        j["revisionId"] = x.get_revision_id();
        j["branch"] = x.get_branch();
        j["revisionTag"] = x.get_revision_tag();
        j["asOfTimeUtc"] = x.get_as_of_time_utc();
        j["mappedTo"] = x.get_mapped_to();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::VersionControlDetails& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<libsarif::VersionControlDetailsProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
    }

    inline void to_json(json & j, const libsarif::VersionControlDetails & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, libsarif::WebRequestProperties& x) {
        x.set_index(j.at("index").get<libsarif::PuneHedgehog>());
        x.set_protocol(j.at("protocol").get<libsarif::TartuGecko>());
        x.set_version(j.at("version").get<libsarif::TartuGecko>());
        x.set_target(j.at("target").get<libsarif::TartuGecko>());
        x.set_method(j.at("method").get<libsarif::TartuGecko>());
        x.set_headers(j.at("headers").get<libsarif::Hashes>());
        x.set_parameters(j.at("parameters").get<libsarif::Hashes>());
        x.set_body(j.at("body").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::WebRequestProperties & x) {
        j = json::object();
        j["index"] = x.get_index();
        j["protocol"] = x.get_protocol();
        j["version"] = x.get_version();
        j["target"] = x.get_target();
        j["method"] = x.get_method();
        j["headers"] = x.get_headers();
        j["parameters"] = x.get_parameters();
        j["body"] = x.get_body();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::WebRequest& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::WebRequestProperties>());
    }

    inline void to_json(json & j, const libsarif::WebRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::WebResponseProperties& x) {
        x.set_index(j.at("index").get<libsarif::PuneHedgehog>());
        x.set_protocol(j.at("protocol").get<libsarif::TartuGecko>());
        x.set_version(j.at("version").get<libsarif::TartuGecko>());
        x.set_status_code(j.at("statusCode").get<libsarif::TartuGecko>());
        x.set_reason_phrase(j.at("reasonPhrase").get<libsarif::TartuGecko>());
        x.set_headers(j.at("headers").get<libsarif::Hashes>());
        x.set_body(j.at("body").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
        x.set_no_response_received(j.at("noResponseReceived").get<libsarif::Enabled>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::WebResponseProperties & x) {
        j = json::object();
        j["index"] = x.get_index();
        j["protocol"] = x.get_protocol();
        j["version"] = x.get_version();
        j["statusCode"] = x.get_status_code();
        j["reasonPhrase"] = x.get_reason_phrase();
        j["headers"] = x.get_headers();
        j["body"] = x.get_body();
        j["noResponseReceived"] = x.get_no_response_received();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::WebResponse& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::WebResponseProperties>());
    }

    inline void to_json(json & j, const libsarif::WebResponse & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Definitions& x) {
        x.set_address(j.at("address").get<libsarif::Address>());
        x.set_artifact(j.at("artifact").get<libsarif::Artifact>());
        x.set_artifact_change(j.at("artifactChange").get<libsarif::ArtifactChange>());
        x.set_artifact_content(j.at("artifactContent").get<libsarif::ArtifactContent>());
        x.set_artifact_location(j.at("artifactLocation").get<libsarif::ArtifactLocation>());
        x.set_attachment(j.at("attachment").get<libsarif::Attachment>());
        x.set_code_flow(j.at("codeFlow").get<libsarif::CodeFlow>());
        x.set_configuration_override(j.at("configurationOverride").get<libsarif::ConfigurationOverride>());
        x.set_conversion(j.at("conversion").get<libsarif::Conversion>());
        x.set_edge(j.at("edge").get<libsarif::Edge>());
        x.set_edge_traversal(j.at("edgeTraversal").get<libsarif::EdgeTraversal>());
        x.set_exception(j.at("exception").get<libsarif::Exception>());
        x.set_external_properties(j.at("externalProperties").get<libsarif::ExternalProperties>());
        x.set_external_property_file_reference(j.at("externalPropertyFileReference").get<libsarif::ExternalPropertyFileReference>());
        x.set_external_property_file_references(j.at("externalPropertyFileReferences").get<libsarif::ExternalPropertyFileReferences>());
        x.set_fix(j.at("fix").get<libsarif::Fix>());
        x.set_graph(j.at("graph").get<libsarif::Graph>());
        x.set_graph_traversal(j.at("graphTraversal").get<libsarif::GraphTraversal>());
        x.set_invocation(j.at("invocation").get<libsarif::Invocation>());
        x.set_location(j.at("location").get<libsarif::Location>());
        x.set_location_relationship(j.at("locationRelationship").get<libsarif::LocationRelationship>());
        x.set_logical_location(j.at("logicalLocation").get<libsarif::LogicalLocation>());
        x.set_message(j.at("message").get<libsarif::Message>());
        x.set_multiformat_message_string(j.at("multiformatMessageString").get<libsarif::MultiformatMessageString>());
        x.set_node(j.at("node").get<libsarif::Node>());
        x.set_notification(j.at("notification").get<libsarif::Notification>());
        x.set_physical_location(j.at("physicalLocation").get<libsarif::PhysicalLocation>());
        x.set_property_bag(j.at("propertyBag").get<libsarif::PropertyBag>());
        x.set_rectangle(j.at("rectangle").get<libsarif::Rectangle>());
        x.set_region(j.at("region").get<libsarif::Region>());
        x.set_replacement(j.at("replacement").get<libsarif::Replacement>());
        x.set_reporting_descriptor(j.at("reportingDescriptor").get<libsarif::ReportingDescriptor>());
        x.set_reporting_configuration(j.at("reportingConfiguration").get<libsarif::ReportingConfiguration>());
        x.set_reporting_descriptor_reference(j.at("reportingDescriptorReference").get<libsarif::ReportingDescriptorReference>());
        x.set_reporting_descriptor_relationship(j.at("reportingDescriptorRelationship").get<libsarif::ReportingDescriptorRelationship>());
        x.set_result(j.at("result").get<libsarif::Result>());
        x.set_result_provenance(j.at("resultProvenance").get<libsarif::ResultProvenance>());
        x.set_run(j.at("run").get<libsarif::Run>());
        x.set_run_automation_details(j.at("runAutomationDetails").get<libsarif::RunAutomationDetails>());
        x.set_special_locations(j.at("specialLocations").get<libsarif::SpecialLocations>());
        x.set_stack(j.at("stack").get<libsarif::Stack>());
        x.set_stack_frame(j.at("stackFrame").get<libsarif::StackFrame>());
        x.set_suppression(j.at("suppression").get<libsarif::Suppression>());
        x.set_thread_flow(j.at("threadFlow").get<libsarif::ThreadFlow>());
        x.set_thread_flow_location(j.at("threadFlowLocation").get<libsarif::ThreadFlowLocation>());
        x.set_tool(j.at("tool").get<libsarif::Tool>());
        x.set_tool_component(j.at("toolComponent").get<libsarif::ToolComponent>());
        x.set_tool_component_reference(j.at("toolComponentReference").get<libsarif::ToolComponentReference>());
        x.set_translation_metadata(j.at("translationMetadata").get<libsarif::TranslationMetadata>());
        x.set_version_control_details(j.at("versionControlDetails").get<libsarif::VersionControlDetails>());
        x.set_web_request(j.at("webRequest").get<libsarif::WebRequest>());
        x.set_web_response(j.at("webResponse").get<libsarif::WebResponse>());
    }

    inline void to_json(json & j, const libsarif::Definitions & x) {
        j = json::object();
        j["address"] = x.get_address();
        j["artifact"] = x.get_artifact();
        j["artifactChange"] = x.get_artifact_change();
        j["artifactContent"] = x.get_artifact_content();
        j["artifactLocation"] = x.get_artifact_location();
        j["attachment"] = x.get_attachment();
        j["codeFlow"] = x.get_code_flow();
        j["configurationOverride"] = x.get_configuration_override();
        j["conversion"] = x.get_conversion();
        j["edge"] = x.get_edge();
        j["edgeTraversal"] = x.get_edge_traversal();
        j["exception"] = x.get_exception();
        j["externalProperties"] = x.get_external_properties();
        j["externalPropertyFileReference"] = x.get_external_property_file_reference();
        j["externalPropertyFileReferences"] = x.get_external_property_file_references();
        j["fix"] = x.get_fix();
        j["graph"] = x.get_graph();
        j["graphTraversal"] = x.get_graph_traversal();
        j["invocation"] = x.get_invocation();
        j["location"] = x.get_location();
        j["locationRelationship"] = x.get_location_relationship();
        j["logicalLocation"] = x.get_logical_location();
        j["message"] = x.get_message();
        j["multiformatMessageString"] = x.get_multiformat_message_string();
        j["node"] = x.get_node();
        j["notification"] = x.get_notification();
        j["physicalLocation"] = x.get_physical_location();
        j["propertyBag"] = x.get_property_bag();
        j["rectangle"] = x.get_rectangle();
        j["region"] = x.get_region();
        j["replacement"] = x.get_replacement();
        j["reportingDescriptor"] = x.get_reporting_descriptor();
        j["reportingConfiguration"] = x.get_reporting_configuration();
        j["reportingDescriptorReference"] = x.get_reporting_descriptor_reference();
        j["reportingDescriptorRelationship"] = x.get_reporting_descriptor_relationship();
        j["result"] = x.get_result();
        j["resultProvenance"] = x.get_result_provenance();
        j["run"] = x.get_run();
        j["runAutomationDetails"] = x.get_run_automation_details();
        j["specialLocations"] = x.get_special_locations();
        j["stack"] = x.get_stack();
        j["stackFrame"] = x.get_stack_frame();
        j["suppression"] = x.get_suppression();
        j["threadFlow"] = x.get_thread_flow();
        j["threadFlowLocation"] = x.get_thread_flow_location();
        j["tool"] = x.get_tool();
        j["toolComponent"] = x.get_tool_component();
        j["toolComponentReference"] = x.get_tool_component_reference();
        j["translationMetadata"] = x.get_translation_metadata();
        j["versionControlDetails"] = x.get_version_control_details();
        j["webRequest"] = x.get_web_request();
        j["webResponse"] = x.get_web_response();
    }

    inline void from_json(const json & j, libsarif::LibsarifProperties& x) {
        x.set_schema(j.at("$schema").get<libsarif::Schema>());
        x.set_version(j.at("version").get<libsarif::Version>());
        x.set_runs(j.at("runs").get<libsarif::HammerfestPonies>());
        x.set_inline_external_properties(j.at("inlineExternalProperties").get<libsarif::HammerfestPonies>());
        x.set_properties(j.at("properties").get<libsarif::LivingstoneSouthernWhiteFacedOwl>());
    }

    inline void to_json(json & j, const libsarif::LibsarifProperties & x) {
        j = json::object();
        j["$schema"] = x.get_schema();
        j["version"] = x.get_version();
        j["runs"] = x.get_runs();
        j["inlineExternalProperties"] = x.get_inline_external_properties();
        j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Libsarif& x) {
        x.set_schema(j.at("$schema").get<std::string>());
        x.set_title(j.at("title").get<std::string>());
        x.set_id(j.at("id").get<std::string>());
        x.set_description(j.at("description").get<std::string>());
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_type(j.at("type").get<std::string>());
        x.set_properties(j.at("properties").get<libsarif::LibsarifProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_definitions(j.at("definitions").get<libsarif::Definitions>());
    }

    inline void to_json(json & j, const libsarif::Libsarif & x) {
        j = json::object();
        j["$schema"] = x.get_schema();
        j["title"] = x.get_title();
        j["id"] = x.get_id();
        j["description"] = x.get_description();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["definitions"] = x.get_definitions();
    }

    inline void from_json(const json & j, libsarif::PurpleType & x) {
        if (j == "boolean") x = libsarif::PurpleType::BOOLEAN;
        else if (j == "integer") x = libsarif::PurpleType::INTEGER;
        else if (j == "number") x = libsarif::PurpleType::NUMBER;
        else if (j == "string") x = libsarif::PurpleType::STRING;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::PurpleType & x) {
        switch (x) {
            case libsarif::PurpleType::BOOLEAN: j = "boolean"; break;
            case libsarif::PurpleType::INTEGER: j = "integer"; break;
            case libsarif::PurpleType::NUMBER: j = "number"; break;
            case libsarif::PurpleType::STRING: j = "string"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::Format & x) {
        if (j == "date-time") x = libsarif::Format::DATE_TIME;
        else if (j == "uri") x = libsarif::Format::URI;
        else if (j == "uri-reference") x = libsarif::Format::URI_REFERENCE;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::Format & x) {
        switch (x) {
            case libsarif::Format::DATE_TIME: j = "date-time"; break;
            case libsarif::Format::URI: j = "uri"; break;
            case libsarif::Format::URI_REFERENCE: j = "uri-reference"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::FluffyType & x) {
        if (j == "array") x = libsarif::FluffyType::ARRAY;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::FluffyType & x) {
        switch (x) {
            case libsarif::FluffyType::ARRAY: j = "array"; break;
            default: throw "This should not happen";
        }
    }
}
