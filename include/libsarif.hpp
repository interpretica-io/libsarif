//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     TopLevel data = nlohmann::json::parse(jsonString);

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

    class ClassMemberConstraints {
        private:
        std::optional<int> min_value;
        std::optional<int> max_value;
        std::optional<size_t> min_length;
        std::optional<size_t> max_length;
        std::optional<std::string> pattern;

        public:
        ClassMemberConstraints(
            std::optional<int> min_value,
            std::optional<int> max_value,
            std::optional<size_t> min_length,
            std::optional<size_t> max_length,
            std::optional<std::string> pattern
        ) : min_value(min_value), max_value(max_value), min_length(min_length), max_length(max_length), pattern(pattern) {}
        ClassMemberConstraints() = default;
        virtual ~ClassMemberConstraints() = default;

        void set_min_value(int min_value) { this->min_value = min_value; }
        auto get_min_value() const { return min_value; }

        void set_max_value(int max_value) { this->max_value = max_value; }
        auto get_max_value() const { return max_value; }

        void set_min_length(size_t min_length) { this->min_length = min_length; }
        auto get_min_length() const { return min_length; }

        void set_max_length(size_t max_length) { this->max_length = max_length; }
        auto get_max_length() const { return max_length; }

        void set_pattern(const std::string &  pattern) { this->pattern = pattern; }
        auto get_pattern() const { return pattern; }
    };

    class ClassMemberConstraintException : public std::runtime_error {
        public:
        ClassMemberConstraintException(const std::string &  msg) : std::runtime_error(msg) {}
    };

    class ValueTooLowException : public ClassMemberConstraintException {
        public:
        ValueTooLowException(const std::string &  msg) : ClassMemberConstraintException(msg) {}
    };

    class ValueTooHighException : public ClassMemberConstraintException {
        public:
        ValueTooHighException(const std::string &  msg) : ClassMemberConstraintException(msg) {}
    };

    class ValueTooShortException : public ClassMemberConstraintException {
        public:
        ValueTooShortException(const std::string &  msg) : ClassMemberConstraintException(msg) {}
    };

    class ValueTooLongException : public ClassMemberConstraintException {
        public:
        ValueTooLongException(const std::string &  msg) : ClassMemberConstraintException(msg) {}
    };

    class InvalidPatternException : public ClassMemberConstraintException {
        public:
        InvalidPatternException(const std::string &  msg) : ClassMemberConstraintException(msg) {}
    };

    void CheckConstraint(const std::string &  name, const ClassMemberConstraints & c, int64_t value) {
        if (c.get_min_value() != std::nullopt && value < *c.get_min_value()) {
            throw ValueTooLowException ("Value too low for " + name + " (" + std::to_string(value) + "<" + std::to_string(*c.get_min_value()) + ")");
        }

        if (c.get_max_value() != std::nullopt && value > *c.get_max_value()) {
            throw ValueTooHighException ("Value too high for " + name + " (" + std::to_string(value) + ">" + std::to_string(*c.get_max_value()) + ")");
        }
    }

    void CheckConstraint(const std::string &  name, const ClassMemberConstraints & c, const std::string &  value) {
        if (c.get_min_length() != std::nullopt && value.length() < *c.get_min_length()) {
            throw ValueTooShortException ("Value too short for " + name + " (" + std::to_string(value.length()) + "<" + std::to_string(*c.get_min_length()) + ")");
        }

        if (c.get_max_length() != std::nullopt && value.length() > *c.get_max_length()) {
            throw ValueTooLongException ("Value too long for " + name + " (" + std::to_string(value.length()) + ">" + std::to_string(*c.get_max_length()) + ")");
        }

        if (c.get_pattern() != std::nullopt) {
            std::smatch result;
            std::regex_search(value, result, std::regex( *c.get_pattern() ));
            if (result.empty()) {
                throw InvalidPatternException ("Value doesn't match pattern for " + name + " (" + value +" != " + *c.get_pattern() + ")");
            }
        }
    }

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

    /**
     * Key/value pairs that provide additional information about the address.
     *
     * Key/value pairs that provide additional information about the object.
     *
     * Key/value pairs that provide additional information about the artifact content.
     *
     * Key/value pairs that provide additional information about the message.
     *
     * Key/value pairs that provide additional information about the artifact location.
     *
     * Key/value pairs that provide additional information about the artifact.
     *
     * Contains configuration information specific to a report.
     *
     * Key/value pairs that provide additional information about the reporting configuration.
     *
     * Key/value pairs that provide additional information about the reporting descriptor
     * reference.
     *
     * Key/value pairs that provide additional information about the toolComponentReference.
     *
     * Key/value pairs that provide additional information about the configuration override.
     *
     * Key/value pairs that provide additional information about the invocation.
     *
     * Key/value pairs that provide additional information about the exception.
     *
     * Key/value pairs that provide additional information about the region.
     *
     * Key/value pairs that provide additional information about the logical location.
     *
     * Key/value pairs that provide additional information about the physical location.
     *
     * Key/value pairs that provide additional information about the location.
     *
     * Key/value pairs that provide additional information about the location relationship.
     *
     * Key/value pairs that provide additional information about the stack frame.
     *
     * Key/value pairs that provide additional information about the stack.
     *
     * Key/value pairs that provide additional information about the notification.
     *
     * Key/value pairs that provide additional information about the conversion.
     *
     * Key/value pairs that provide additional information about the report.
     *
     * Key/value pairs that provide additional information about the tool component.
     *
     * Key/value pairs that provide additional information about the translation metadata.
     *
     * Key/value pairs that provide additional information about the tool.
     *
     * Key/value pairs that provide additional information that will be merged with a separate
     * run.
     *
     * Key/value pairs that provide additional information about the edge.
     *
     * Key/value pairs that provide additional information about the node.
     *
     * Key/value pairs that provide additional information about the graph.
     *
     * Key/value pairs that provide additional information about the external properties.
     *
     * Key/value pairs that provide additional information about the attachment.
     *
     * Key/value pairs that provide additional information about the rectangle.
     *
     * Key/value pairs that provide additional information about the code flow.
     *
     * Key/value pairs that provide additional information about the threadflow location.
     *
     * Key/value pairs that provide additional information about the request.
     *
     * Key/value pairs that provide additional information about the response.
     *
     * Key/value pairs that provide additional information about the thread flow.
     *
     * Key/value pairs that provide additional information about the change.
     *
     * Key/value pairs that provide additional information about the replacement.
     *
     * Key/value pairs that provide additional information about the fix.
     *
     * Key/value pairs that provide additional information about the edge traversal.
     *
     * Key/value pairs that provide additional information about the graph traversal.
     *
     * Key/value pairs that provide additional information about the result.
     *
     * Key/value pairs that provide additional information about the suppression.
     *
     * Key/value pairs that provide additional information about the log file.
     *
     * Key/value pairs that provide additional information about the run automation details.
     *
     * Key/value pairs that provide additional information about the external property file.
     *
     * Key/value pairs that provide additional information about the external property files.
     *
     * Key/value pairs that provide additional information about the run.
     *
     * Key/value pairs that provide additional information about the special locations.
     *
     * Key/value pairs that provide additional information about the version control details.
     */
    class PropertyBag {
        public:
        PropertyBag() = default;
        virtual ~PropertyBag() = default;

        private:
        std::shared_ptr<std::vector<std::string>> tags;

        public:
        /**
         * A set of distinct strings that provide additional information.
         */
        std::shared_ptr<std::vector<std::string>> get_tags() const { return tags; }
        void set_tags(std::shared_ptr<std::vector<std::string>> value) { this->tags = value; }
    };

    /**
     * A physical or virtual address, or a range of addresses, in an 'addressable region'
     * (memory or a binary file).
     *
     * The address of the location.
     */
    class Address {
        public:
        Address() :
            absolute_address_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            parent_index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~Address() = default;

        private:
        std::shared_ptr<int64_t> absolute_address;
        ClassMemberConstraints absolute_address_constraint;
        std::shared_ptr<std::string> fully_qualified_name;
        std::shared_ptr<int64_t> index;
        ClassMemberConstraints index_constraint;
        std::shared_ptr<std::string> kind;
        std::shared_ptr<int64_t> length;
        std::shared_ptr<std::string> name;
        std::shared_ptr<int64_t> offset_from_parent;
        std::shared_ptr<int64_t> parent_index;
        ClassMemberConstraints parent_index_constraint;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<int64_t> relative_address;

        public:
        /**
         * The address expressed as a byte offset from the start of the addressable region.
         */
        std::shared_ptr<int64_t> get_absolute_address() const { return absolute_address; }
        void set_absolute_address(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("absolute_address", absolute_address_constraint, *value); this->absolute_address = value; }

        /**
         * A human-readable fully qualified name that is associated with the address.
         */
        std::shared_ptr<std::string> get_fully_qualified_name() const { return fully_qualified_name; }
        void set_fully_qualified_name(std::shared_ptr<std::string> value) { this->fully_qualified_name = value; }

        /**
         * The index within run.addresses of the cached object for this address.
         */
        std::shared_ptr<int64_t> get_index() const { return index; }
        void set_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("index", index_constraint, *value); this->index = value; }

        /**
         * An open-ended string that identifies the address kind. 'data', 'function',
         * 'header','instruction', 'module', 'page', 'section', 'segment', 'stack', 'stackFrame',
         * 'table' are well-known values.
         */
        std::shared_ptr<std::string> get_kind() const { return kind; }
        void set_kind(std::shared_ptr<std::string> value) { this->kind = value; }

        /**
         * The number of bytes in this range of addresses.
         */
        std::shared_ptr<int64_t> get_length() const { return length; }
        void set_length(std::shared_ptr<int64_t> value) { this->length = value; }

        /**
         * A name that is associated with the address, e.g., '.text'.
         */
        std::shared_ptr<std::string> get_name() const { return name; }
        void set_name(std::shared_ptr<std::string> value) { this->name = value; }

        /**
         * The byte offset of this address from the absolute or relative address of the parent
         * object.
         */
        std::shared_ptr<int64_t> get_offset_from_parent() const { return offset_from_parent; }
        void set_offset_from_parent(std::shared_ptr<int64_t> value) { this->offset_from_parent = value; }

        /**
         * The index within run.addresses of the parent object.
         */
        std::shared_ptr<int64_t> get_parent_index() const { return parent_index; }
        void set_parent_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("parent_index", parent_index_constraint, *value); this->parent_index = value; }

        /**
         * Key/value pairs that provide additional information about the address.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The address expressed as a byte offset from the absolute address of the top-most parent
         * object.
         */
        std::shared_ptr<int64_t> get_relative_address() const { return relative_address; }
        void set_relative_address(std::shared_ptr<int64_t> value) { this->relative_address = value; }
    };

    /**
     * An alternate rendered representation of the artifact (e.g., a decompiled representation
     * of a binary region).
     *
     * A message string or message format string rendered in multiple formats.
     *
     * A comprehensive description of the tool component.
     *
     * A description of the report. Should, as far as possible, provide details sufficient to
     * enable resolution of any problem indicated by the result.
     *
     * Provides the primary documentation for the report, useful when there is no online
     * documentation.
     *
     * A concise description of the report. Should be a single sentence that is understandable
     * when visible space is limited to a single line of text.
     *
     * A brief description of the tool component.
     *
     * A comprehensive description of the translation metadata.
     *
     * A brief description of the translation metadata.
     */
    class MultiformatMessageString {
        public:
        MultiformatMessageString() = default;
        virtual ~MultiformatMessageString() = default;

        private:
        std::shared_ptr<std::string> markdown;
        std::shared_ptr<PropertyBag> properties;
        std::string text;

        public:
        /**
         * A Markdown message string or format string.
         */
        std::shared_ptr<std::string> get_markdown() const { return markdown; }
        void set_markdown(std::shared_ptr<std::string> value) { this->markdown = value; }

        /**
         * Key/value pairs that provide additional information about the message.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * A plain text message string or format string.
         */
        const std::string & get_text() const { return text; }
        std::string & get_mutable_text() { return text; }
        void set_text(const std::string & value) { this->text = value; }
    };

    /**
     * The contents of the artifact.
     *
     * Represents the contents of an artifact.
     *
     * The portion of the artifact contents within the specified region.
     *
     * The body of the request.
     *
     * The body of the response.
     *
     * The content to insert at the location specified by the 'deletedRegion' property.
     */
    class ArtifactContent {
        public:
        ArtifactContent() = default;
        virtual ~ArtifactContent() = default;

        private:
        std::shared_ptr<std::string> binary;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<MultiformatMessageString> rendered;
        std::shared_ptr<std::string> text;

        public:
        /**
         * MIME Base64-encoded content from a binary artifact, or from a text artifact in its
         * original encoding.
         */
        std::shared_ptr<std::string> get_binary() const { return binary; }
        void set_binary(std::shared_ptr<std::string> value) { this->binary = value; }

        /**
         * Key/value pairs that provide additional information about the artifact content.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * An alternate rendered representation of the artifact (e.g., a decompiled representation
         * of a binary region).
         */
        std::shared_ptr<MultiformatMessageString> get_rendered() const { return rendered; }
        void set_rendered(std::shared_ptr<MultiformatMessageString> value) { this->rendered = value; }

        /**
         * UTF-8-encoded content from a text artifact.
         */
        std::shared_ptr<std::string> get_text() const { return text; }
        void set_text(std::shared_ptr<std::string> value) { this->text = value; }
    };

    /**
     * A short description of the artifact.
     *
     * A short description of the artifact location.
     *
     * A message relevant to the region.
     *
     * A message relevant to the location.
     *
     * A description of the location relationship.
     *
     * A message relevant to this call stack.
     *
     * A message that describes the condition that was encountered.
     *
     * A description of the reporting descriptor relationship.
     *
     * A description of the graph.
     *
     * A short description of the edge.
     *
     * A short description of the node.
     *
     * A message describing the role played by the attachment.
     *
     * A message relevant to the rectangle.
     *
     * A message relevant to the code flow.
     *
     * A message relevant to the thread flow.
     *
     * A message that describes the proposed fix, enabling viewers to present the proposed
     * change to an end user.
     *
     * A description of this graph traversal.
     *
     * A message to display to the user as the edge is traversed.
     *
     * A message that describes the result. The first sentence of the message only will be
     * displayed when visible space is limited.
     *
     * A description of the identity and role played within the engineering system by this
     * object's containing run object.
     *
     * Encapsulates a message intended to be read by the end user.
     */
    class Message {
        public:
        Message() = default;
        virtual ~Message() = default;

        private:
        std::shared_ptr<std::vector<std::string>> arguments;
        std::shared_ptr<std::string> id;
        std::shared_ptr<std::string> markdown;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::string> text;

        public:
        /**
         * An array of strings to substitute into the message string.
         */
        std::shared_ptr<std::vector<std::string>> get_arguments() const { return arguments; }
        void set_arguments(std::shared_ptr<std::vector<std::string>> value) { this->arguments = value; }

        /**
         * The identifier for this message.
         */
        std::shared_ptr<std::string> get_id() const { return id; }
        void set_id(std::shared_ptr<std::string> value) { this->id = value; }

        /**
         * A Markdown message string.
         */
        std::shared_ptr<std::string> get_markdown() const { return markdown; }
        void set_markdown(std::shared_ptr<std::string> value) { this->markdown = value; }

        /**
         * Key/value pairs that provide additional information about the message.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * A plain text message string.
         */
        std::shared_ptr<std::string> get_text() const { return text; }
        void set_text(std::shared_ptr<std::string> value) { this->text = value; }
    };

    /**
     * The location of the artifact.
     *
     * Specifies the location of an artifact.
     *
     * An absolute URI specifying the location of the analysis tool's executable.
     *
     * A file containing the standard error stream from the process that was invoked.
     *
     * A file containing the standard input stream to the process that was invoked.
     *
     * A file containing the standard output stream from the process that was invoked.
     *
     * A file containing the interleaved standard output and standard error stream from the
     * process that was invoked.
     *
     * The working directory for the analysis tool run.
     *
     * Identifies the artifact that the analysis tool was instructed to scan. This need not be
     * the same as the artifact where the result actually occurred.
     *
     * The location of the attachment.
     *
     * The location of the artifact to change.
     *
     * The location of the external property file.
     *
     * Provides a suggestion to SARIF consumers to display file paths relative to the specified
     * location.
     *
     * The location in the local file system to which the root of the repository was mapped at
     * the time of the analysis.
     */
    class ArtifactLocation {
        public:
        ArtifactLocation() :
            index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~ArtifactLocation() = default;

        private:
        std::shared_ptr<Message> description;
        std::shared_ptr<int64_t> index;
        ClassMemberConstraints index_constraint;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::string> uri;
        std::shared_ptr<std::string> uri_base_id;

        public:
        /**
         * A short description of the artifact location.
         */
        std::shared_ptr<Message> get_description() const { return description; }
        void set_description(std::shared_ptr<Message> value) { this->description = value; }

        /**
         * The index within the run artifacts array of the artifact object associated with the
         * artifact location.
         */
        std::shared_ptr<int64_t> get_index() const { return index; }
        void set_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("index", index_constraint, *value); this->index = value; }

        /**
         * Key/value pairs that provide additional information about the artifact location.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * A string containing a valid relative or absolute URI.
         */
        std::shared_ptr<std::string> get_uri() const { return uri; }
        void set_uri(std::shared_ptr<std::string> value) { this->uri = value; }

        /**
         * A string which indirectly specifies the absolute URI with respect to which a relative URI
         * in the "uri" property is interpreted.
         */
        std::shared_ptr<std::string> get_uri_base_id() const { return uri_base_id; }
        void set_uri_base_id(std::shared_ptr<std::string> value) { this->uri_base_id = value; }
    };

    enum class Role : int { ADDED, ANALYSIS_TARGET, ATTACHMENT, DEBUG_OUTPUT_FILE, DELETED, DIRECTORY, DRIVER, EXTENSION, MEMORY_CONTENTS, MODIFIED, POLICY, REFERENCED_ON_COMMAND_LINE, RENAMED, RESPONSE_FILE, RESULT_FILE, STANDARD_STREAM, TAXONOMY, TOOL_SPECIFIED_CONFIGURATION, TRACED_FILE, TRANSLATION, UNCONTROLLED, UNMODIFIED, USER_SPECIFIED_CONFIGURATION };

    /**
     * A single artifact. In some cases, this artifact might be nested within another artifact.
     */
    class Artifact {
        public:
        Artifact() :
            length_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            mime_type_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("[^/]+/.+")),
            offset_constraint(0, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            parent_index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~Artifact() = default;

        private:
        std::shared_ptr<ArtifactContent> contents;
        std::shared_ptr<Message> description;
        std::shared_ptr<std::string> encoding;
        std::shared_ptr<std::map<std::string, std::string>> hashes;
        std::shared_ptr<std::string> last_modified_time_utc;
        std::shared_ptr<int64_t> length;
        ClassMemberConstraints length_constraint;
        std::shared_ptr<ArtifactLocation> location;
        std::shared_ptr<std::string> mime_type;
        ClassMemberConstraints mime_type_constraint;
        std::shared_ptr<int64_t> offset;
        ClassMemberConstraints offset_constraint;
        std::shared_ptr<int64_t> parent_index;
        ClassMemberConstraints parent_index_constraint;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::vector<Role>> roles;
        std::shared_ptr<std::string> source_language;

        public:
        /**
         * The contents of the artifact.
         */
        std::shared_ptr<ArtifactContent> get_contents() const { return contents; }
        void set_contents(std::shared_ptr<ArtifactContent> value) { this->contents = value; }

        /**
         * A short description of the artifact.
         */
        std::shared_ptr<Message> get_description() const { return description; }
        void set_description(std::shared_ptr<Message> value) { this->description = value; }

        /**
         * Specifies the encoding for an artifact object that refers to a text file.
         */
        std::shared_ptr<std::string> get_encoding() const { return encoding; }
        void set_encoding(std::shared_ptr<std::string> value) { this->encoding = value; }

        /**
         * A dictionary, each of whose keys is the name of a hash function and each of whose values
         * is the hashed value of the artifact produced by the specified hash function.
         */
        std::shared_ptr<std::map<std::string, std::string>> get_hashes() const { return hashes; }
        void set_hashes(std::shared_ptr<std::map<std::string, std::string>> value) { this->hashes = value; }

        /**
         * The Coordinated Universal Time (UTC) date and time at which the artifact was most
         * recently modified. See "Date/time properties" in the SARIF spec for the required format.
         */
        std::shared_ptr<std::string> get_last_modified_time_utc() const { return last_modified_time_utc; }
        void set_last_modified_time_utc(std::shared_ptr<std::string> value) { this->last_modified_time_utc = value; }

        /**
         * The length of the artifact in bytes.
         */
        std::shared_ptr<int64_t> get_length() const { return length; }
        void set_length(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("length", length_constraint, *value); this->length = value; }

        /**
         * The location of the artifact.
         */
        std::shared_ptr<ArtifactLocation> get_location() const { return location; }
        void set_location(std::shared_ptr<ArtifactLocation> value) { this->location = value; }

        /**
         * The MIME type (RFC 2045) of the artifact.
         */
        std::shared_ptr<std::string> get_mime_type() const { return mime_type; }
        void set_mime_type(std::shared_ptr<std::string> value) { if (value) CheckConstraint("mime_type", mime_type_constraint, *value); this->mime_type = value; }

        /**
         * The offset in bytes of the artifact within its containing artifact.
         */
        std::shared_ptr<int64_t> get_offset() const { return offset; }
        void set_offset(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("offset", offset_constraint, *value); this->offset = value; }

        /**
         * Identifies the index of the immediate parent of the artifact, if this artifact is nested.
         */
        std::shared_ptr<int64_t> get_parent_index() const { return parent_index; }
        void set_parent_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("parent_index", parent_index_constraint, *value); this->parent_index = value; }

        /**
         * Key/value pairs that provide additional information about the artifact.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The role or roles played by the artifact in the analysis.
         */
        std::shared_ptr<std::vector<Role>> get_roles() const { return roles; }
        void set_roles(std::shared_ptr<std::vector<Role>> value) { this->roles = value; }

        /**
         * Specifies the source language for any artifact object that refers to a text file that
         * contains source code.
         */
        std::shared_ptr<std::string> get_source_language() const { return source_language; }
        void set_source_language(std::shared_ptr<std::string> value) { this->source_language = value; }
    };

    /**
     * Specifies the failure level for the report.
     *
     * A value specifying the severity level of the notification.
     *
     * A value specifying the severity level of the result.
     */
    enum class Level : int { ERROR, NONE, NOTE, WARNING };

    /**
     * Specifies how the rule or notification was configured during the scan.
     *
     * Information about a rule or notification that can be configured at runtime.
     *
     * Default reporting configuration information.
     */
    class ReportingConfiguration {
        public:
        ReportingConfiguration() :
            rank_constraint(-1, 100, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~ReportingConfiguration() = default;

        private:
        std::shared_ptr<bool> enabled;
        std::shared_ptr<Level> level;
        std::shared_ptr<PropertyBag> parameters;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<double> rank;
        ClassMemberConstraints rank_constraint;

        public:
        /**
         * Specifies whether the report may be produced during the scan.
         */
        std::shared_ptr<bool> get_enabled() const { return enabled; }
        void set_enabled(std::shared_ptr<bool> value) { this->enabled = value; }

        /**
         * Specifies the failure level for the report.
         */
        std::shared_ptr<Level> get_level() const { return level; }
        void set_level(std::shared_ptr<Level> value) { this->level = value; }

        /**
         * Contains configuration information specific to a report.
         */
        std::shared_ptr<PropertyBag> get_parameters() const { return parameters; }
        void set_parameters(std::shared_ptr<PropertyBag> value) { this->parameters = value; }

        /**
         * Key/value pairs that provide additional information about the reporting configuration.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * Specifies the relative priority of the report. Used for analysis output only.
         */
        std::shared_ptr<double> get_rank() const { return rank; }
        void set_rank(std::shared_ptr<double> value) { if (value) CheckConstraint("rank", rank_constraint, *value); this->rank = value; }
    };

    /**
     * A reference used to locate the toolComponent associated with the descriptor.
     *
     *
     *
     * The component which is strongly associated with this component. For a translation, this
     * refers to the component which has been translated. For an extension, this is the driver
     * that provides the extension's plugin model.
     */
    class ToolComponentReference {
        public:
        ToolComponentReference() :
            guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$")),
            index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~ToolComponentReference() = default;

        private:
        std::shared_ptr<std::string> guid;
        ClassMemberConstraints guid_constraint;
        std::shared_ptr<int64_t> index;
        ClassMemberConstraints index_constraint;
        std::shared_ptr<std::string> name;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * The 'guid' property of the referenced toolComponent.
         */
        std::shared_ptr<std::string> get_guid() const { return guid; }
        void set_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("guid", guid_constraint, *value); this->guid = value; }

        /**
         * An index into the referenced toolComponent in tool.extensions.
         */
        std::shared_ptr<int64_t> get_index() const { return index; }
        void set_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("index", index_constraint, *value); this->index = value; }

        /**
         * The 'name' property of the referenced toolComponent.
         */
        std::shared_ptr<std::string> get_name() const { return name; }
        void set_name(std::shared_ptr<std::string> value) { this->name = value; }

        /**
         * Key/value pairs that provide additional information about the toolComponentReference.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * A reference used to locate the descriptor whose configuration was overridden.
     *
     * A reference used to locate the rule descriptor associated with this notification.
     *
     * A reference used to locate the descriptor relevant to this notification.
     *
     * A reference to the related reporting descriptor.
     *
     * A reference used to locate the rule descriptor relevant to this result.
     *
     * Information about how to locate a relevant reporting descriptor.
     */
    class ReportingDescriptorReference {
        public:
        ReportingDescriptorReference() :
            guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$")),
            index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~ReportingDescriptorReference() = default;

        private:
        std::shared_ptr<std::string> guid;
        ClassMemberConstraints guid_constraint;
        std::shared_ptr<std::string> id;
        std::shared_ptr<int64_t> index;
        ClassMemberConstraints index_constraint;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<ToolComponentReference> tool_component;

        public:
        /**
         * A guid that uniquely identifies the descriptor.
         */
        std::shared_ptr<std::string> get_guid() const { return guid; }
        void set_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("guid", guid_constraint, *value); this->guid = value; }

        /**
         * The id of the descriptor.
         */
        std::shared_ptr<std::string> get_id() const { return id; }
        void set_id(std::shared_ptr<std::string> value) { this->id = value; }

        /**
         * The index into an array of descriptors in toolComponent.ruleDescriptors,
         * toolComponent.notificationDescriptors, or toolComponent.taxonomyDescriptors, depending on
         * context.
         */
        std::shared_ptr<int64_t> get_index() const { return index; }
        void set_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("index", index_constraint, *value); this->index = value; }

        /**
         * Key/value pairs that provide additional information about the reporting descriptor
         * reference.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * A reference used to locate the toolComponent associated with the descriptor.
         */
        std::shared_ptr<ToolComponentReference> get_tool_component() const { return tool_component; }
        void set_tool_component(std::shared_ptr<ToolComponentReference> value) { this->tool_component = value; }
    };

    /**
     * Information about how a specific rule or notification was reconfigured at runtime.
     */
    class ConfigurationOverride {
        public:
        ConfigurationOverride() = default;
        virtual ~ConfigurationOverride() = default;

        private:
        ReportingConfiguration configuration;
        ReportingDescriptorReference descriptor;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * Specifies how the rule or notification was configured during the scan.
         */
        const ReportingConfiguration & get_configuration() const { return configuration; }
        ReportingConfiguration & get_mutable_configuration() { return configuration; }
        void set_configuration(const ReportingConfiguration & value) { this->configuration = value; }

        /**
         * A reference used to locate the descriptor whose configuration was overridden.
         */
        const ReportingDescriptorReference & get_descriptor() const { return descriptor; }
        ReportingDescriptorReference & get_mutable_descriptor() { return descriptor; }
        void set_descriptor(const ReportingDescriptorReference & value) { this->descriptor = value; }

        /**
         * Key/value pairs that provide additional information about the configuration override.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * A region within an artifact where a result was detected.
     *
     * Specifies a portion of the artifact that encloses the region. Allows a viewer to display
     * additional context around the region.
     *
     * Specifies a portion of the artifact.
     *
     * The region of the artifact to delete.
     */
    class Region {
        public:
        Region() :
            byte_length_constraint(0, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            byte_offset_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            char_length_constraint(0, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            char_offset_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            end_column_constraint(1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            end_line_constraint(1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            start_column_constraint(1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            start_line_constraint(1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~Region() = default;

        private:
        std::shared_ptr<int64_t> byte_length;
        ClassMemberConstraints byte_length_constraint;
        std::shared_ptr<int64_t> byte_offset;
        ClassMemberConstraints byte_offset_constraint;
        std::shared_ptr<int64_t> char_length;
        ClassMemberConstraints char_length_constraint;
        std::shared_ptr<int64_t> char_offset;
        ClassMemberConstraints char_offset_constraint;
        std::shared_ptr<int64_t> end_column;
        ClassMemberConstraints end_column_constraint;
        std::shared_ptr<int64_t> end_line;
        ClassMemberConstraints end_line_constraint;
        std::shared_ptr<Message> message;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<ArtifactContent> snippet;
        std::shared_ptr<std::string> source_language;
        std::shared_ptr<int64_t> start_column;
        ClassMemberConstraints start_column_constraint;
        std::shared_ptr<int64_t> start_line;
        ClassMemberConstraints start_line_constraint;

        public:
        /**
         * The length of the region in bytes.
         */
        std::shared_ptr<int64_t> get_byte_length() const { return byte_length; }
        void set_byte_length(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("byte_length", byte_length_constraint, *value); this->byte_length = value; }

        /**
         * The zero-based offset from the beginning of the artifact of the first byte in the region.
         */
        std::shared_ptr<int64_t> get_byte_offset() const { return byte_offset; }
        void set_byte_offset(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("byte_offset", byte_offset_constraint, *value); this->byte_offset = value; }

        /**
         * The length of the region in characters.
         */
        std::shared_ptr<int64_t> get_char_length() const { return char_length; }
        void set_char_length(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("char_length", char_length_constraint, *value); this->char_length = value; }

        /**
         * The zero-based offset from the beginning of the artifact of the first character in the
         * region.
         */
        std::shared_ptr<int64_t> get_char_offset() const { return char_offset; }
        void set_char_offset(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("char_offset", char_offset_constraint, *value); this->char_offset = value; }

        /**
         * The column number of the character following the end of the region.
         */
        std::shared_ptr<int64_t> get_end_column() const { return end_column; }
        void set_end_column(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("end_column", end_column_constraint, *value); this->end_column = value; }

        /**
         * The line number of the last character in the region.
         */
        std::shared_ptr<int64_t> get_end_line() const { return end_line; }
        void set_end_line(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("end_line", end_line_constraint, *value); this->end_line = value; }

        /**
         * A message relevant to the region.
         */
        std::shared_ptr<Message> get_message() const { return message; }
        void set_message(std::shared_ptr<Message> value) { this->message = value; }

        /**
         * Key/value pairs that provide additional information about the region.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The portion of the artifact contents within the specified region.
         */
        std::shared_ptr<ArtifactContent> get_snippet() const { return snippet; }
        void set_snippet(std::shared_ptr<ArtifactContent> value) { this->snippet = value; }

        /**
         * Specifies the source language, if any, of the portion of the artifact specified by the
         * region object.
         */
        std::shared_ptr<std::string> get_source_language() const { return source_language; }
        void set_source_language(std::shared_ptr<std::string> value) { this->source_language = value; }

        /**
         * The column number of the first character in the region.
         */
        std::shared_ptr<int64_t> get_start_column() const { return start_column; }
        void set_start_column(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("start_column", start_column_constraint, *value); this->start_column = value; }

        /**
         * The line number of the first character in the region.
         */
        std::shared_ptr<int64_t> get_start_line() const { return start_line; }
        void set_start_line(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("start_line", start_line_constraint, *value); this->start_line = value; }
    };

    /**
     * A logical location of a construct that produced a result.
     */
    class LogicalLocation {
        public:
        LogicalLocation() :
            index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            parent_index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~LogicalLocation() = default;

        private:
        std::shared_ptr<std::string> decorated_name;
        std::shared_ptr<std::string> fully_qualified_name;
        std::shared_ptr<int64_t> index;
        ClassMemberConstraints index_constraint;
        std::shared_ptr<std::string> kind;
        std::shared_ptr<std::string> name;
        std::shared_ptr<int64_t> parent_index;
        ClassMemberConstraints parent_index_constraint;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * The machine-readable name for the logical location, such as a mangled function name
         * provided by a C++ compiler that encodes calling convention, return type and other details
         * along with the function name.
         */
        std::shared_ptr<std::string> get_decorated_name() const { return decorated_name; }
        void set_decorated_name(std::shared_ptr<std::string> value) { this->decorated_name = value; }

        /**
         * The human-readable fully qualified name of the logical location.
         */
        std::shared_ptr<std::string> get_fully_qualified_name() const { return fully_qualified_name; }
        void set_fully_qualified_name(std::shared_ptr<std::string> value) { this->fully_qualified_name = value; }

        /**
         * The index within the logical locations array.
         */
        std::shared_ptr<int64_t> get_index() const { return index; }
        void set_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("index", index_constraint, *value); this->index = value; }

        /**
         * The type of construct this logical location component refers to. Should be one of
         * 'function', 'member', 'module', 'namespace', 'parameter', 'resource', 'returnType',
         * 'type', 'variable', 'object', 'array', 'property', 'value', 'element', 'text',
         * 'attribute', 'comment', 'declaration', 'dtd' or 'processingInstruction', if any of those
         * accurately describe the construct.
         */
        std::shared_ptr<std::string> get_kind() const { return kind; }
        void set_kind(std::shared_ptr<std::string> value) { this->kind = value; }

        /**
         * Identifies the construct in which the result occurred. For example, this property might
         * contain the name of a class or a method.
         */
        std::shared_ptr<std::string> get_name() const { return name; }
        void set_name(std::shared_ptr<std::string> value) { this->name = value; }

        /**
         * Identifies the index of the immediate parent of the construct in which the result was
         * detected. For example, this property might point to a logical location that represents
         * the namespace that holds a type.
         */
        std::shared_ptr<int64_t> get_parent_index() const { return parent_index; }
        void set_parent_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("parent_index", parent_index_constraint, *value); this->parent_index = value; }

        /**
         * Key/value pairs that provide additional information about the logical location.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * Identifies the artifact and region.
     *
     * A physical location relevant to a result. Specifies a reference to a programming artifact
     * together with a range of bytes or characters within that artifact.
     */
    class PhysicalLocation {
        public:
        PhysicalLocation() = default;
        virtual ~PhysicalLocation() = default;

        private:
        std::shared_ptr<Address> address;
        std::shared_ptr<ArtifactLocation> artifact_location;
        std::shared_ptr<Region> context_region;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<Region> region;

        public:
        /**
         * The address of the location.
         */
        std::shared_ptr<Address> get_address() const { return address; }
        void set_address(std::shared_ptr<Address> value) { this->address = value; }

        /**
         * The location of the artifact.
         */
        std::shared_ptr<ArtifactLocation> get_artifact_location() const { return artifact_location; }
        void set_artifact_location(std::shared_ptr<ArtifactLocation> value) { this->artifact_location = value; }

        /**
         * Specifies a portion of the artifact that encloses the region. Allows a viewer to display
         * additional context around the region.
         */
        std::shared_ptr<Region> get_context_region() const { return context_region; }
        void set_context_region(std::shared_ptr<Region> value) { this->context_region = value; }

        /**
         * Key/value pairs that provide additional information about the physical location.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * Specifies a portion of the artifact.
         */
        std::shared_ptr<Region> get_region() const { return region; }
        void set_region(std::shared_ptr<Region> value) { this->region = value; }
    };

    /**
     * Information about the relation of one location to another.
     */
    class LocationRelationship {
        public:
        LocationRelationship() :
            target_constraint(0, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~LocationRelationship() = default;

        private:
        std::shared_ptr<Message> description;
        std::shared_ptr<std::vector<std::string>> kinds;
        std::shared_ptr<PropertyBag> properties;
        int64_t target;
        ClassMemberConstraints target_constraint;

        public:
        /**
         * A description of the location relationship.
         */
        std::shared_ptr<Message> get_description() const { return description; }
        void set_description(std::shared_ptr<Message> value) { this->description = value; }

        /**
         * A set of distinct strings that categorize the relationship. Well-known kinds include
         * 'includes', 'isIncludedBy' and 'relevant'.
         */
        std::shared_ptr<std::vector<std::string>> get_kinds() const { return kinds; }
        void set_kinds(std::shared_ptr<std::vector<std::string>> value) { this->kinds = value; }

        /**
         * Key/value pairs that provide additional information about the location relationship.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * A reference to the related location.
         */
        const int64_t & get_target() const { return target; }
        int64_t & get_mutable_target() { return target; }
        void set_target(const int64_t & value) { CheckConstraint("target", target_constraint, value); this->target = value; }
    };

    /**
     * The location to which this stack frame refers.
     *
     * A location within a programming artifact.
     *
     * A code location associated with the node.
     *
     * The code location.
     *
     * Identifies the location associated with the suppression.
     */
    class Location {
        public:
        Location() :
            id_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~Location() = default;

        private:
        std::shared_ptr<std::vector<Region>> annotations;
        std::shared_ptr<int64_t> id;
        ClassMemberConstraints id_constraint;
        std::shared_ptr<std::vector<LogicalLocation>> logical_locations;
        std::shared_ptr<Message> message;
        std::shared_ptr<PhysicalLocation> physical_location;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::vector<LocationRelationship>> relationships;

        public:
        /**
         * A set of regions relevant to the location.
         */
        std::shared_ptr<std::vector<Region>> get_annotations() const { return annotations; }
        void set_annotations(std::shared_ptr<std::vector<Region>> value) { this->annotations = value; }

        /**
         * Value that distinguishes this location from all other locations within a single result
         * object.
         */
        std::shared_ptr<int64_t> get_id() const { return id; }
        void set_id(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("id", id_constraint, *value); this->id = value; }

        /**
         * The logical locations associated with the result.
         */
        std::shared_ptr<std::vector<LogicalLocation>> get_logical_locations() const { return logical_locations; }
        void set_logical_locations(std::shared_ptr<std::vector<LogicalLocation>> value) { this->logical_locations = value; }

        /**
         * A message relevant to the location.
         */
        std::shared_ptr<Message> get_message() const { return message; }
        void set_message(std::shared_ptr<Message> value) { this->message = value; }

        /**
         * Identifies the artifact and region.
         */
        std::shared_ptr<PhysicalLocation> get_physical_location() const { return physical_location; }
        void set_physical_location(std::shared_ptr<PhysicalLocation> value) { this->physical_location = value; }

        /**
         * Key/value pairs that provide additional information about the location.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * An array of objects that describe relationships between this location and others.
         */
        std::shared_ptr<std::vector<LocationRelationship>> get_relationships() const { return relationships; }
        void set_relationships(std::shared_ptr<std::vector<LocationRelationship>> value) { this->relationships = value; }
    };

    /**
     * A function call within a stack trace.
     */
    class StackFrame {
        public:
        StackFrame() = default;
        virtual ~StackFrame() = default;

        private:
        std::shared_ptr<Location> location;
        std::shared_ptr<std::string> stack_frame_module;
        std::shared_ptr<std::vector<std::string>> parameters;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<int64_t> thread_id;

        public:
        /**
         * The location to which this stack frame refers.
         */
        std::shared_ptr<Location> get_location() const { return location; }
        void set_location(std::shared_ptr<Location> value) { this->location = value; }

        /**
         * The name of the module that contains the code of this stack frame.
         */
        std::shared_ptr<std::string> get_stack_frame_module() const { return stack_frame_module; }
        void set_stack_frame_module(std::shared_ptr<std::string> value) { this->stack_frame_module = value; }

        /**
         * The parameters of the call that is executing.
         */
        std::shared_ptr<std::vector<std::string>> get_parameters() const { return parameters; }
        void set_parameters(std::shared_ptr<std::vector<std::string>> value) { this->parameters = value; }

        /**
         * Key/value pairs that provide additional information about the stack frame.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The thread identifier of the stack frame.
         */
        std::shared_ptr<int64_t> get_thread_id() const { return thread_id; }
        void set_thread_id(std::shared_ptr<int64_t> value) { this->thread_id = value; }
    };

    /**
     * The sequence of function calls leading to the exception.
     *
     * A call stack that is relevant to a result.
     *
     * The call stack leading to this location.
     */
    class Stack {
        public:
        Stack() = default;
        virtual ~Stack() = default;

        private:
        std::vector<StackFrame> frames;
        std::shared_ptr<Message> message;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * An array of stack frames that represents a sequence of calls, rendered in reverse
         * chronological order, that comprise the call stack.
         */
        const std::vector<StackFrame> & get_frames() const { return frames; }
        std::vector<StackFrame> & get_mutable_frames() { return frames; }
        void set_frames(const std::vector<StackFrame> & value) { this->frames = value; }

        /**
         * A message relevant to this call stack.
         */
        std::shared_ptr<Message> get_message() const { return message; }
        void set_message(std::shared_ptr<Message> value) { this->message = value; }

        /**
         * Key/value pairs that provide additional information about the stack.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * The runtime exception, if any, relevant to this notification.
     */
    class Exception {
        public:
        Exception() = default;
        virtual ~Exception() = default;

        private:
        std::shared_ptr<std::vector<Exception>> inner_exceptions;
        std::shared_ptr<std::string> kind;
        std::shared_ptr<std::string> message;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<Stack> stack;

        public:
        /**
         * An array of exception objects each of which is considered a cause of this exception.
         */
        std::shared_ptr<std::vector<Exception>> get_inner_exceptions() const { return inner_exceptions; }
        void set_inner_exceptions(std::shared_ptr<std::vector<Exception>> value) { this->inner_exceptions = value; }

        /**
         * A string that identifies the kind of exception, for example, the fully qualified type
         * name of an object that was thrown, or the symbolic name of a signal.
         */
        std::shared_ptr<std::string> get_kind() const { return kind; }
        void set_kind(std::shared_ptr<std::string> value) { this->kind = value; }

        /**
         * A message that describes the exception.
         */
        std::shared_ptr<std::string> get_message() const { return message; }
        void set_message(std::shared_ptr<std::string> value) { this->message = value; }

        /**
         * Key/value pairs that provide additional information about the exception.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The sequence of function calls leading to the exception.
         */
        std::shared_ptr<Stack> get_stack() const { return stack; }
        void set_stack(std::shared_ptr<Stack> value) { this->stack = value; }
    };

    /**
     * Describes a condition relevant to the tool itself, as opposed to being relevant to a
     * target being analyzed by the tool.
     */
    class Notification {
        public:
        Notification() = default;
        virtual ~Notification() = default;

        private:
        std::shared_ptr<ReportingDescriptorReference> associated_rule;
        std::shared_ptr<ReportingDescriptorReference> descriptor;
        std::shared_ptr<Exception> exception;
        std::shared_ptr<Level> level;
        std::shared_ptr<std::vector<Location>> locations;
        Message message;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<int64_t> thread_id;
        std::shared_ptr<std::string> time_utc;

        public:
        /**
         * A reference used to locate the rule descriptor associated with this notification.
         */
        std::shared_ptr<ReportingDescriptorReference> get_associated_rule() const { return associated_rule; }
        void set_associated_rule(std::shared_ptr<ReportingDescriptorReference> value) { this->associated_rule = value; }

        /**
         * A reference used to locate the descriptor relevant to this notification.
         */
        std::shared_ptr<ReportingDescriptorReference> get_descriptor() const { return descriptor; }
        void set_descriptor(std::shared_ptr<ReportingDescriptorReference> value) { this->descriptor = value; }

        /**
         * The runtime exception, if any, relevant to this notification.
         */
        std::shared_ptr<Exception> get_exception() const { return exception; }
        void set_exception(std::shared_ptr<Exception> value) { this->exception = value; }

        /**
         * A value specifying the severity level of the notification.
         */
        std::shared_ptr<Level> get_level() const { return level; }
        void set_level(std::shared_ptr<Level> value) { this->level = value; }

        /**
         * The locations relevant to this notification.
         */
        std::shared_ptr<std::vector<Location>> get_locations() const { return locations; }
        void set_locations(std::shared_ptr<std::vector<Location>> value) { this->locations = value; }

        /**
         * A message that describes the condition that was encountered.
         */
        const Message & get_message() const { return message; }
        Message & get_mutable_message() { return message; }
        void set_message(const Message & value) { this->message = value; }

        /**
         * Key/value pairs that provide additional information about the notification.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The thread identifier of the code that generated the notification.
         */
        std::shared_ptr<int64_t> get_thread_id() const { return thread_id; }
        void set_thread_id(std::shared_ptr<int64_t> value) { this->thread_id = value; }

        /**
         * The Coordinated Universal Time (UTC) date and time at which the analysis tool generated
         * the notification.
         */
        std::shared_ptr<std::string> get_time_utc() const { return time_utc; }
        void set_time_utc(std::shared_ptr<std::string> value) { this->time_utc = value; }
    };

    /**
     * An invocation object that describes the invocation of the converter.
     *
     * The runtime environment of the analysis tool run.
     */
    class Invocation {
        public:
        Invocation() = default;
        virtual ~Invocation() = default;

        private:
        std::shared_ptr<std::string> account;
        std::shared_ptr<std::vector<std::string>> arguments;
        std::shared_ptr<std::string> command_line;
        std::shared_ptr<std::string> end_time_utc;
        std::shared_ptr<std::map<std::string, std::string>> environment_variables;
        std::shared_ptr<ArtifactLocation> executable_location;
        bool execution_successful;
        std::shared_ptr<int64_t> exit_code;
        std::shared_ptr<std::string> exit_code_description;
        std::shared_ptr<std::string> exit_signal_name;
        std::shared_ptr<int64_t> exit_signal_number;
        std::shared_ptr<std::string> machine;
        std::shared_ptr<std::vector<ConfigurationOverride>> notification_configuration_overrides;
        std::shared_ptr<int64_t> process_id;
        std::shared_ptr<std::string> process_start_failure_message;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::vector<ArtifactLocation>> response_files;
        std::shared_ptr<std::vector<ConfigurationOverride>> rule_configuration_overrides;
        std::shared_ptr<std::string> start_time_utc;
        std::shared_ptr<ArtifactLocation> stderr_;
        std::shared_ptr<ArtifactLocation> stdin_;
        std::shared_ptr<ArtifactLocation> stdout_;
        std::shared_ptr<ArtifactLocation> stdout_stderr_;
        std::shared_ptr<std::vector<Notification>> tool_configuration_notifications;
        std::shared_ptr<std::vector<Notification>> tool_execution_notifications;
        std::shared_ptr<ArtifactLocation> working_directory;

        public:
        /**
         * The account that ran the analysis tool.
         */
        std::shared_ptr<std::string> get_account() const { return account; }
        void set_account(std::shared_ptr<std::string> value) { this->account = value; }

        /**
         * An array of strings, containing in order the command line arguments passed to the tool
         * from the operating system.
         */
        std::shared_ptr<std::vector<std::string>> get_arguments() const { return arguments; }
        void set_arguments(std::shared_ptr<std::vector<std::string>> value) { this->arguments = value; }

        /**
         * The command line used to invoke the tool.
         */
        std::shared_ptr<std::string> get_command_line() const { return command_line; }
        void set_command_line(std::shared_ptr<std::string> value) { this->command_line = value; }

        /**
         * The Coordinated Universal Time (UTC) date and time at which the run ended. See "Date/time
         * properties" in the SARIF spec for the required format.
         */
        std::shared_ptr<std::string> get_end_time_utc() const { return end_time_utc; }
        void set_end_time_utc(std::shared_ptr<std::string> value) { this->end_time_utc = value; }

        /**
         * The environment variables associated with the analysis tool process, expressed as
         * key/value pairs.
         */
        std::shared_ptr<std::map<std::string, std::string>> get_environment_variables() const { return environment_variables; }
        void set_environment_variables(std::shared_ptr<std::map<std::string, std::string>> value) { this->environment_variables = value; }

        /**
         * An absolute URI specifying the location of the analysis tool's executable.
         */
        std::shared_ptr<ArtifactLocation> get_executable_location() const { return executable_location; }
        void set_executable_location(std::shared_ptr<ArtifactLocation> value) { this->executable_location = value; }

        /**
         * Specifies whether the tool's execution completed successfully.
         */
        const bool & get_execution_successful() const { return execution_successful; }
        bool & get_mutable_execution_successful() { return execution_successful; }
        void set_execution_successful(const bool & value) { this->execution_successful = value; }

        /**
         * The process exit code.
         */
        std::shared_ptr<int64_t> get_exit_code() const { return exit_code; }
        void set_exit_code(std::shared_ptr<int64_t> value) { this->exit_code = value; }

        /**
         * The reason for the process exit.
         */
        std::shared_ptr<std::string> get_exit_code_description() const { return exit_code_description; }
        void set_exit_code_description(std::shared_ptr<std::string> value) { this->exit_code_description = value; }

        /**
         * The name of the signal that caused the process to exit.
         */
        std::shared_ptr<std::string> get_exit_signal_name() const { return exit_signal_name; }
        void set_exit_signal_name(std::shared_ptr<std::string> value) { this->exit_signal_name = value; }

        /**
         * The numeric value of the signal that caused the process to exit.
         */
        std::shared_ptr<int64_t> get_exit_signal_number() const { return exit_signal_number; }
        void set_exit_signal_number(std::shared_ptr<int64_t> value) { this->exit_signal_number = value; }

        /**
         * The machine that hosted the analysis tool run.
         */
        std::shared_ptr<std::string> get_machine() const { return machine; }
        void set_machine(std::shared_ptr<std::string> value) { this->machine = value; }

        /**
         * An array of configurationOverride objects that describe notifications related runtime
         * overrides.
         */
        std::shared_ptr<std::vector<ConfigurationOverride>> get_notification_configuration_overrides() const { return notification_configuration_overrides; }
        void set_notification_configuration_overrides(std::shared_ptr<std::vector<ConfigurationOverride>> value) { this->notification_configuration_overrides = value; }

        /**
         * The process id for the analysis tool run.
         */
        std::shared_ptr<int64_t> get_process_id() const { return process_id; }
        void set_process_id(std::shared_ptr<int64_t> value) { this->process_id = value; }

        /**
         * The reason given by the operating system that the process failed to start.
         */
        std::shared_ptr<std::string> get_process_start_failure_message() const { return process_start_failure_message; }
        void set_process_start_failure_message(std::shared_ptr<std::string> value) { this->process_start_failure_message = value; }

        /**
         * Key/value pairs that provide additional information about the invocation.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The locations of any response files specified on the tool's command line.
         */
        std::shared_ptr<std::vector<ArtifactLocation>> get_response_files() const { return response_files; }
        void set_response_files(std::shared_ptr<std::vector<ArtifactLocation>> value) { this->response_files = value; }

        /**
         * An array of configurationOverride objects that describe rules related runtime overrides.
         */
        std::shared_ptr<std::vector<ConfigurationOverride>> get_rule_configuration_overrides() const { return rule_configuration_overrides; }
        void set_rule_configuration_overrides(std::shared_ptr<std::vector<ConfigurationOverride>> value) { this->rule_configuration_overrides = value; }

        /**
         * The Coordinated Universal Time (UTC) date and time at which the run started. See
         * "Date/time properties" in the SARIF spec for the required format.
         */
        std::shared_ptr<std::string> get_start_time_utc() const { return start_time_utc; }
        void set_start_time_utc(std::shared_ptr<std::string> value) { this->start_time_utc = value; }

        /**
         * A file containing the standard error stream from the process that was invoked.
         */
        std::shared_ptr<ArtifactLocation> get_stderr() const { return stderr_; }
        void set_stderr(std::shared_ptr<ArtifactLocation> value) { this->stderr_ = value; }

        /**
         * A file containing the standard input stream to the process that was invoked.
         */
        std::shared_ptr<ArtifactLocation> get_stdin() const { return stdin_; }
        void set_stdin(std::shared_ptr<ArtifactLocation> value) { this->stdin_ = value; }

        /**
         * A file containing the standard output stream from the process that was invoked.
         */
        std::shared_ptr<ArtifactLocation> get_stdout() const { return stdout_; }
        void set_stdout(std::shared_ptr<ArtifactLocation> value) { this->stdout_ = value; }

        /**
         * A file containing the interleaved standard output and standard error stream from the
         * process that was invoked.
         */
        std::shared_ptr<ArtifactLocation> get_stdout_stderr() const { return stdout_stderr_; }
        void set_stdout_stderr(std::shared_ptr<ArtifactLocation> value) { this->stdout_stderr_ = value; }

        /**
         * A list of conditions detected by the tool that are relevant to the tool's configuration.
         */
        std::shared_ptr<std::vector<Notification>> get_tool_configuration_notifications() const { return tool_configuration_notifications; }
        void set_tool_configuration_notifications(std::shared_ptr<std::vector<Notification>> value) { this->tool_configuration_notifications = value; }

        /**
         * A list of runtime conditions detected by the tool during the analysis.
         */
        std::shared_ptr<std::vector<Notification>> get_tool_execution_notifications() const { return tool_execution_notifications; }
        void set_tool_execution_notifications(std::shared_ptr<std::vector<Notification>> value) { this->tool_execution_notifications = value; }

        /**
         * The working directory for the analysis tool run.
         */
        std::shared_ptr<ArtifactLocation> get_working_directory() const { return working_directory; }
        void set_working_directory(std::shared_ptr<ArtifactLocation> value) { this->working_directory = value; }
    };

    enum class Content : int { LOCALIZED_DATA, NON_LOCALIZED_DATA };

    /**
     * Information about the relation of one reporting descriptor to another.
     */
    class ReportingDescriptorRelationship {
        public:
        ReportingDescriptorRelationship() = default;
        virtual ~ReportingDescriptorRelationship() = default;

        private:
        std::shared_ptr<Message> description;
        std::shared_ptr<std::vector<std::string>> kinds;
        std::shared_ptr<PropertyBag> properties;
        ReportingDescriptorReference target;

        public:
        /**
         * A description of the reporting descriptor relationship.
         */
        std::shared_ptr<Message> get_description() const { return description; }
        void set_description(std::shared_ptr<Message> value) { this->description = value; }

        /**
         * A set of distinct strings that categorize the relationship. Well-known kinds include
         * 'canPrecede', 'canFollow', 'willPrecede', 'willFollow', 'superset', 'subset', 'equal',
         * 'disjoint', 'relevant', and 'incomparable'.
         */
        std::shared_ptr<std::vector<std::string>> get_kinds() const { return kinds; }
        void set_kinds(std::shared_ptr<std::vector<std::string>> value) { this->kinds = value; }

        /**
         * Key/value pairs that provide additional information about the reporting descriptor
         * reference.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * A reference to the related reporting descriptor.
         */
        const ReportingDescriptorReference & get_target() const { return target; }
        ReportingDescriptorReference & get_mutable_target() { return target; }
        void set_target(const ReportingDescriptorReference & value) { this->target = value; }
    };

    /**
     * Metadata that describes a specific report produced by the tool, as part of the analysis
     * it provides or its runtime reporting.
     */
    class ReportingDescriptor {
        public:
        ReportingDescriptor() :
            guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$"))
        {}
        virtual ~ReportingDescriptor() = default;

        private:
        std::shared_ptr<ReportingConfiguration> default_configuration;
        std::shared_ptr<std::vector<std::string>> deprecated_guids;
        std::shared_ptr<std::vector<std::string>> deprecated_ids;
        std::shared_ptr<std::vector<std::string>> deprecated_names;
        std::shared_ptr<MultiformatMessageString> full_description;
        std::shared_ptr<std::string> guid;
        ClassMemberConstraints guid_constraint;
        std::shared_ptr<MultiformatMessageString> help;
        std::shared_ptr<std::string> help_uri;
        std::string id;
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> message_strings;
        std::shared_ptr<std::string> name;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::vector<ReportingDescriptorRelationship>> relationships;
        std::shared_ptr<MultiformatMessageString> short_description;

        public:
        /**
         * Default reporting configuration information.
         */
        std::shared_ptr<ReportingConfiguration> get_default_configuration() const { return default_configuration; }
        void set_default_configuration(std::shared_ptr<ReportingConfiguration> value) { this->default_configuration = value; }

        /**
         * An array of unique identifies in the form of a GUID by which this report was known in
         * some previous version of the analysis tool.
         */
        std::shared_ptr<std::vector<std::string>> get_deprecated_guids() const { return deprecated_guids; }
        void set_deprecated_guids(std::shared_ptr<std::vector<std::string>> value) { this->deprecated_guids = value; }

        /**
         * An array of stable, opaque identifiers by which this report was known in some previous
         * version of the analysis tool.
         */
        std::shared_ptr<std::vector<std::string>> get_deprecated_ids() const { return deprecated_ids; }
        void set_deprecated_ids(std::shared_ptr<std::vector<std::string>> value) { this->deprecated_ids = value; }

        /**
         * An array of readable identifiers by which this report was known in some previous version
         * of the analysis tool.
         */
        std::shared_ptr<std::vector<std::string>> get_deprecated_names() const { return deprecated_names; }
        void set_deprecated_names(std::shared_ptr<std::vector<std::string>> value) { this->deprecated_names = value; }

        /**
         * A description of the report. Should, as far as possible, provide details sufficient to
         * enable resolution of any problem indicated by the result.
         */
        std::shared_ptr<MultiformatMessageString> get_full_description() const { return full_description; }
        void set_full_description(std::shared_ptr<MultiformatMessageString> value) { this->full_description = value; }

        /**
         * A unique identifer for the reporting descriptor in the form of a GUID.
         */
        std::shared_ptr<std::string> get_guid() const { return guid; }
        void set_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("guid", guid_constraint, *value); this->guid = value; }

        /**
         * Provides the primary documentation for the report, useful when there is no online
         * documentation.
         */
        std::shared_ptr<MultiformatMessageString> get_help() const { return help; }
        void set_help(std::shared_ptr<MultiformatMessageString> value) { this->help = value; }

        /**
         * A URI where the primary documentation for the report can be found.
         */
        std::shared_ptr<std::string> get_help_uri() const { return help_uri; }
        void set_help_uri(std::shared_ptr<std::string> value) { this->help_uri = value; }

        /**
         * A stable, opaque identifier for the report.
         */
        const std::string & get_id() const { return id; }
        std::string & get_mutable_id() { return id; }
        void set_id(const std::string & value) { this->id = value; }

        /**
         * A set of name/value pairs with arbitrary names. Each value is a multiformatMessageString
         * object, which holds message strings in plain text and (optionally) Markdown format. The
         * strings can include placeholders, which can be used to construct a message in combination
         * with an arbitrary number of additional string arguments.
         */
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> get_message_strings() const { return message_strings; }
        void set_message_strings(std::shared_ptr<std::map<std::string, MultiformatMessageString>> value) { this->message_strings = value; }

        /**
         * A report identifier that is understandable to an end user.
         */
        std::shared_ptr<std::string> get_name() const { return name; }
        void set_name(std::shared_ptr<std::string> value) { this->name = value; }

        /**
         * Key/value pairs that provide additional information about the report.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * An array of objects that describe relationships between this reporting descriptor and
         * others.
         */
        std::shared_ptr<std::vector<ReportingDescriptorRelationship>> get_relationships() const { return relationships; }
        void set_relationships(std::shared_ptr<std::vector<ReportingDescriptorRelationship>> value) { this->relationships = value; }

        /**
         * A concise description of the report. Should be a single sentence that is understandable
         * when visible space is limited to a single line of text.
         */
        std::shared_ptr<MultiformatMessageString> get_short_description() const { return short_description; }
        void set_short_description(std::shared_ptr<MultiformatMessageString> value) { this->short_description = value; }
    };

    /**
     * Translation metadata, required for a translation, not populated by other component
     * types.
     *
     * Provides additional metadata related to translation.
     */
    class TranslationMetadata {
        public:
        TranslationMetadata() = default;
        virtual ~TranslationMetadata() = default;

        private:
        std::shared_ptr<std::string> download_uri;
        std::shared_ptr<MultiformatMessageString> full_description;
        std::shared_ptr<std::string> full_name;
        std::shared_ptr<std::string> information_uri;
        std::string name;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<MultiformatMessageString> short_description;

        public:
        /**
         * The absolute URI from which the translation metadata can be downloaded.
         */
        std::shared_ptr<std::string> get_download_uri() const { return download_uri; }
        void set_download_uri(std::shared_ptr<std::string> value) { this->download_uri = value; }

        /**
         * A comprehensive description of the translation metadata.
         */
        std::shared_ptr<MultiformatMessageString> get_full_description() const { return full_description; }
        void set_full_description(std::shared_ptr<MultiformatMessageString> value) { this->full_description = value; }

        /**
         * The full name associated with the translation metadata.
         */
        std::shared_ptr<std::string> get_full_name() const { return full_name; }
        void set_full_name(std::shared_ptr<std::string> value) { this->full_name = value; }

        /**
         * The absolute URI from which information related to the translation metadata can be
         * downloaded.
         */
        std::shared_ptr<std::string> get_information_uri() const { return information_uri; }
        void set_information_uri(std::shared_ptr<std::string> value) { this->information_uri = value; }

        /**
         * The name associated with the translation metadata.
         */
        const std::string & get_name() const { return name; }
        std::string & get_mutable_name() { return name; }
        void set_name(const std::string & value) { this->name = value; }

        /**
         * Key/value pairs that provide additional information about the translation metadata.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * A brief description of the translation metadata.
         */
        std::shared_ptr<MultiformatMessageString> get_short_description() const { return short_description; }
        void set_short_description(std::shared_ptr<MultiformatMessageString> value) { this->short_description = value; }
    };

    /**
     * The analysis tool that was run.
     *
     * A component, such as a plug-in or the driver, of the analysis tool that was run.
     *
     * The analysis tool object that will be merged with a separate run.
     */
    class ToolComponent {
        public:
        ToolComponent() :
            dotted_quad_file_version_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("[0-9]+(\.[0-9]+){3}")),
            guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$")),
            language_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[a-zA-Z]{2}|^[a-zA-Z]{2}-[a-zA-Z]{2}]?$"))
        {}
        virtual ~ToolComponent() = default;

        private:
        std::shared_ptr<ToolComponentReference> associated_component;
        std::shared_ptr<std::vector<Content>> contents;
        std::shared_ptr<std::string> dotted_quad_file_version;
        ClassMemberConstraints dotted_quad_file_version_constraint;
        std::shared_ptr<std::string> download_uri;
        std::shared_ptr<MultiformatMessageString> full_description;
        std::shared_ptr<std::string> full_name;
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> global_message_strings;
        std::shared_ptr<std::string> guid;
        ClassMemberConstraints guid_constraint;
        std::shared_ptr<std::string> information_uri;
        std::shared_ptr<bool> is_comprehensive;
        std::shared_ptr<std::string> language;
        ClassMemberConstraints language_constraint;
        std::shared_ptr<std::string> localized_data_semantic_version;
        std::shared_ptr<std::vector<ArtifactLocation>> locations;
        std::shared_ptr<std::string> minimum_required_localized_data_semantic_version;
        std::string name;
        std::shared_ptr<std::vector<ReportingDescriptor>> notifications;
        std::shared_ptr<std::string> organization;
        std::shared_ptr<std::string> product;
        std::shared_ptr<std::string> product_suite;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::string> release_date_utc;
        std::shared_ptr<std::vector<ReportingDescriptor>> rules;
        std::shared_ptr<std::string> semantic_version;
        std::shared_ptr<MultiformatMessageString> short_description;
        std::shared_ptr<std::vector<ToolComponentReference>> supported_taxonomies;
        std::shared_ptr<std::vector<ReportingDescriptor>> taxa;
        std::shared_ptr<TranslationMetadata> translation_metadata;
        std::shared_ptr<std::string> version;

        public:
        /**
         * The component which is strongly associated with this component. For a translation, this
         * refers to the component which has been translated. For an extension, this is the driver
         * that provides the extension's plugin model.
         */
        std::shared_ptr<ToolComponentReference> get_associated_component() const { return associated_component; }
        void set_associated_component(std::shared_ptr<ToolComponentReference> value) { this->associated_component = value; }

        /**
         * The kinds of data contained in this object.
         */
        std::shared_ptr<std::vector<Content>> get_contents() const { return contents; }
        void set_contents(std::shared_ptr<std::vector<Content>> value) { this->contents = value; }

        /**
         * The binary version of the tool component's primary executable file expressed as four
         * non-negative integers separated by a period (for operating systems that express file
         * versions in this way).
         */
        std::shared_ptr<std::string> get_dotted_quad_file_version() const { return dotted_quad_file_version; }
        void set_dotted_quad_file_version(std::shared_ptr<std::string> value) { if (value) CheckConstraint("dotted_quad_file_version", dotted_quad_file_version_constraint, *value); this->dotted_quad_file_version = value; }

        /**
         * The absolute URI from which the tool component can be downloaded.
         */
        std::shared_ptr<std::string> get_download_uri() const { return download_uri; }
        void set_download_uri(std::shared_ptr<std::string> value) { this->download_uri = value; }

        /**
         * A comprehensive description of the tool component.
         */
        std::shared_ptr<MultiformatMessageString> get_full_description() const { return full_description; }
        void set_full_description(std::shared_ptr<MultiformatMessageString> value) { this->full_description = value; }

        /**
         * The name of the tool component along with its version and any other useful identifying
         * information, such as its locale.
         */
        std::shared_ptr<std::string> get_full_name() const { return full_name; }
        void set_full_name(std::shared_ptr<std::string> value) { this->full_name = value; }

        /**
         * A dictionary, each of whose keys is a resource identifier and each of whose values is a
         * multiformatMessageString object, which holds message strings in plain text and
         * (optionally) Markdown format. The strings can include placeholders, which can be used to
         * construct a message in combination with an arbitrary number of additional string
         * arguments.
         */
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> get_global_message_strings() const { return global_message_strings; }
        void set_global_message_strings(std::shared_ptr<std::map<std::string, MultiformatMessageString>> value) { this->global_message_strings = value; }

        /**
         * A unique identifer for the tool component in the form of a GUID.
         */
        std::shared_ptr<std::string> get_guid() const { return guid; }
        void set_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("guid", guid_constraint, *value); this->guid = value; }

        /**
         * The absolute URI at which information about this version of the tool component can be
         * found.
         */
        std::shared_ptr<std::string> get_information_uri() const { return information_uri; }
        void set_information_uri(std::shared_ptr<std::string> value) { this->information_uri = value; }

        /**
         * Specifies whether this object contains a complete definition of the localizable and/or
         * non-localizable data for this component, as opposed to including only data that is
         * relevant to the results persisted to this log file.
         */
        std::shared_ptr<bool> get_is_comprehensive() const { return is_comprehensive; }
        void set_is_comprehensive(std::shared_ptr<bool> value) { this->is_comprehensive = value; }

        /**
         * The language of the messages emitted into the log file during this run (expressed as an
         * ISO 639-1 two-letter lowercase language code) and an optional region (expressed as an ISO
         * 3166-1 two-letter uppercase subculture code associated with a country or region). The
         * casing is recommended but not required (in order for this data to conform to RFC5646).
         */
        std::shared_ptr<std::string> get_language() const { return language; }
        void set_language(std::shared_ptr<std::string> value) { if (value) CheckConstraint("language", language_constraint, *value); this->language = value; }

        /**
         * The semantic version of the localized strings defined in this component; maintained by
         * components that provide translations.
         */
        std::shared_ptr<std::string> get_localized_data_semantic_version() const { return localized_data_semantic_version; }
        void set_localized_data_semantic_version(std::shared_ptr<std::string> value) { this->localized_data_semantic_version = value; }

        /**
         * An array of the artifactLocation objects associated with the tool component.
         */
        std::shared_ptr<std::vector<ArtifactLocation>> get_locations() const { return locations; }
        void set_locations(std::shared_ptr<std::vector<ArtifactLocation>> value) { this->locations = value; }

        /**
         * The minimum value of localizedDataSemanticVersion required in translations consumed by
         * this component; used by components that consume translations.
         */
        std::shared_ptr<std::string> get_minimum_required_localized_data_semantic_version() const { return minimum_required_localized_data_semantic_version; }
        void set_minimum_required_localized_data_semantic_version(std::shared_ptr<std::string> value) { this->minimum_required_localized_data_semantic_version = value; }

        /**
         * The name of the tool component.
         */
        const std::string & get_name() const { return name; }
        std::string & get_mutable_name() { return name; }
        void set_name(const std::string & value) { this->name = value; }

        /**
         * An array of reportingDescriptor objects relevant to the notifications related to the
         * configuration and runtime execution of the tool component.
         */
        std::shared_ptr<std::vector<ReportingDescriptor>> get_notifications() const { return notifications; }
        void set_notifications(std::shared_ptr<std::vector<ReportingDescriptor>> value) { this->notifications = value; }

        /**
         * The organization or company that produced the tool component.
         */
        std::shared_ptr<std::string> get_organization() const { return organization; }
        void set_organization(std::shared_ptr<std::string> value) { this->organization = value; }

        /**
         * A product suite to which the tool component belongs.
         */
        std::shared_ptr<std::string> get_product() const { return product; }
        void set_product(std::shared_ptr<std::string> value) { this->product = value; }

        /**
         * A localizable string containing the name of the suite of products to which the tool
         * component belongs.
         */
        std::shared_ptr<std::string> get_product_suite() const { return product_suite; }
        void set_product_suite(std::shared_ptr<std::string> value) { this->product_suite = value; }

        /**
         * Key/value pairs that provide additional information about the tool component.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * A string specifying the UTC date (and optionally, the time) of the component's release.
         */
        std::shared_ptr<std::string> get_release_date_utc() const { return release_date_utc; }
        void set_release_date_utc(std::shared_ptr<std::string> value) { this->release_date_utc = value; }

        /**
         * An array of reportingDescriptor objects relevant to the analysis performed by the tool
         * component.
         */
        std::shared_ptr<std::vector<ReportingDescriptor>> get_rules() const { return rules; }
        void set_rules(std::shared_ptr<std::vector<ReportingDescriptor>> value) { this->rules = value; }

        /**
         * The tool component version in the format specified by Semantic Versioning 2.0.
         */
        std::shared_ptr<std::string> get_semantic_version() const { return semantic_version; }
        void set_semantic_version(std::shared_ptr<std::string> value) { this->semantic_version = value; }

        /**
         * A brief description of the tool component.
         */
        std::shared_ptr<MultiformatMessageString> get_short_description() const { return short_description; }
        void set_short_description(std::shared_ptr<MultiformatMessageString> value) { this->short_description = value; }

        /**
         * An array of toolComponentReference objects to declare the taxonomies supported by the
         * tool component.
         */
        std::shared_ptr<std::vector<ToolComponentReference>> get_supported_taxonomies() const { return supported_taxonomies; }
        void set_supported_taxonomies(std::shared_ptr<std::vector<ToolComponentReference>> value) { this->supported_taxonomies = value; }

        /**
         * An array of reportingDescriptor objects relevant to the definitions of both standalone
         * and tool-defined taxonomies.
         */
        std::shared_ptr<std::vector<ReportingDescriptor>> get_taxa() const { return taxa; }
        void set_taxa(std::shared_ptr<std::vector<ReportingDescriptor>> value) { this->taxa = value; }

        /**
         * Translation metadata, required for a translation, not populated by other component types.
         */
        std::shared_ptr<TranslationMetadata> get_translation_metadata() const { return translation_metadata; }
        void set_translation_metadata(std::shared_ptr<TranslationMetadata> value) { this->translation_metadata = value; }

        /**
         * The tool component version, in whatever format the component natively provides.
         */
        std::shared_ptr<std::string> get_version() const { return version; }
        void set_version(std::shared_ptr<std::string> value) { this->version = value; }
    };

    /**
     * A tool object that describes the converter.
     *
     * The analysis tool that was run.
     *
     * Information about the tool or tool pipeline that generated the results in this run. A run
     * can only contain results produced by a single tool or tool pipeline. A run can aggregate
     * results from multiple log files, as long as context around the tool run (tool
     * command-line arguments and the like) is identical for all aggregated files.
     */
    class Tool {
        public:
        Tool() = default;
        virtual ~Tool() = default;

        private:
        ToolComponent driver;
        std::shared_ptr<std::vector<ToolComponent>> extensions;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * The analysis tool that was run.
         */
        const ToolComponent & get_driver() const { return driver; }
        ToolComponent & get_mutable_driver() { return driver; }
        void set_driver(const ToolComponent & value) { this->driver = value; }

        /**
         * Tool extensions that contributed to or reconfigured the analysis tool that was run.
         */
        std::shared_ptr<std::vector<ToolComponent>> get_extensions() const { return extensions; }
        void set_extensions(std::shared_ptr<std::vector<ToolComponent>> value) { this->extensions = value; }

        /**
         * Key/value pairs that provide additional information about the tool.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * A conversion object that will be merged with a separate run.
     *
     * Describes how a converter transformed the output of a static analysis tool from the
     * analysis tool's native output format into the SARIF format.
     *
     * A conversion object that describes how a converter transformed an analysis tool's native
     * reporting format into the SARIF format.
     */
    class Conversion {
        public:
        Conversion() = default;
        virtual ~Conversion() = default;

        private:
        std::shared_ptr<std::vector<ArtifactLocation>> analysis_tool_log_files;
        std::shared_ptr<Invocation> invocation;
        std::shared_ptr<PropertyBag> properties;
        Tool tool;

        public:
        /**
         * The locations of the analysis tool's per-run log files.
         */
        std::shared_ptr<std::vector<ArtifactLocation>> get_analysis_tool_log_files() const { return analysis_tool_log_files; }
        void set_analysis_tool_log_files(std::shared_ptr<std::vector<ArtifactLocation>> value) { this->analysis_tool_log_files = value; }

        /**
         * An invocation object that describes the invocation of the converter.
         */
        std::shared_ptr<Invocation> get_invocation() const { return invocation; }
        void set_invocation(std::shared_ptr<Invocation> value) { this->invocation = value; }

        /**
         * Key/value pairs that provide additional information about the conversion.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * A tool object that describes the converter.
         */
        const Tool & get_tool() const { return tool; }
        Tool & get_mutable_tool() { return tool; }
        void set_tool(const Tool & value) { this->tool = value; }
    };

    /**
     * Represents a directed edge in a graph.
     */
    class Edge {
        public:
        Edge() = default;
        virtual ~Edge() = default;

        private:
        std::string id;
        std::shared_ptr<Message> label;
        std::shared_ptr<PropertyBag> properties;
        std::string source_node_id;
        std::string target_node_id;

        public:
        /**
         * A string that uniquely identifies the edge within its graph.
         */
        const std::string & get_id() const { return id; }
        std::string & get_mutable_id() { return id; }
        void set_id(const std::string & value) { this->id = value; }

        /**
         * A short description of the edge.
         */
        std::shared_ptr<Message> get_label() const { return label; }
        void set_label(std::shared_ptr<Message> value) { this->label = value; }

        /**
         * Key/value pairs that provide additional information about the edge.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * Identifies the source node (the node at which the edge starts).
         */
        const std::string & get_source_node_id() const { return source_node_id; }
        std::string & get_mutable_source_node_id() { return source_node_id; }
        void set_source_node_id(const std::string & value) { this->source_node_id = value; }

        /**
         * Identifies the target node (the node at which the edge ends).
         */
        const std::string & get_target_node_id() const { return target_node_id; }
        std::string & get_mutable_target_node_id() { return target_node_id; }
        void set_target_node_id(const std::string & value) { this->target_node_id = value; }
    };

    /**
     * Represents a node in a graph.
     */
    class Node {
        public:
        Node() = default;
        virtual ~Node() = default;

        private:
        std::shared_ptr<std::vector<Node>> children;
        std::string id;
        std::shared_ptr<Message> label;
        std::shared_ptr<Location> location;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * Array of child nodes.
         */
        std::shared_ptr<std::vector<Node>> get_children() const { return children; }
        void set_children(std::shared_ptr<std::vector<Node>> value) { this->children = value; }

        /**
         * A string that uniquely identifies the node within its graph.
         */
        const std::string & get_id() const { return id; }
        std::string & get_mutable_id() { return id; }
        void set_id(const std::string & value) { this->id = value; }

        /**
         * A short description of the node.
         */
        std::shared_ptr<Message> get_label() const { return label; }
        void set_label(std::shared_ptr<Message> value) { this->label = value; }

        /**
         * A code location associated with the node.
         */
        std::shared_ptr<Location> get_location() const { return location; }
        void set_location(std::shared_ptr<Location> value) { this->location = value; }

        /**
         * Key/value pairs that provide additional information about the node.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * A network of nodes and directed edges that describes some aspect of the structure of the
     * code (for example, a call graph).
     */
    class Graph {
        public:
        Graph() = default;
        virtual ~Graph() = default;

        private:
        std::shared_ptr<Message> description;
        std::shared_ptr<std::vector<Edge>> edges;
        std::shared_ptr<std::vector<Node>> nodes;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * A description of the graph.
         */
        std::shared_ptr<Message> get_description() const { return description; }
        void set_description(std::shared_ptr<Message> value) { this->description = value; }

        /**
         * An array of edge objects representing the edges of the graph.
         */
        std::shared_ptr<std::vector<Edge>> get_edges() const { return edges; }
        void set_edges(std::shared_ptr<std::vector<Edge>> value) { this->edges = value; }

        /**
         * An array of node objects representing the nodes of the graph.
         */
        std::shared_ptr<std::vector<Node>> get_nodes() const { return nodes; }
        void set_nodes(std::shared_ptr<std::vector<Node>> value) { this->nodes = value; }

        /**
         * Key/value pairs that provide additional information about the graph.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * An area within an image.
     */
    class Rectangle {
        public:
        Rectangle() = default;
        virtual ~Rectangle() = default;

        private:
        std::shared_ptr<double> bottom;
        std::shared_ptr<double> left;
        std::shared_ptr<Message> message;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<double> right;
        std::shared_ptr<double> top;

        public:
        /**
         * The Y coordinate of the bottom edge of the rectangle, measured in the image's natural
         * units.
         */
        std::shared_ptr<double> get_bottom() const { return bottom; }
        void set_bottom(std::shared_ptr<double> value) { this->bottom = value; }

        /**
         * The X coordinate of the left edge of the rectangle, measured in the image's natural units.
         */
        std::shared_ptr<double> get_left() const { return left; }
        void set_left(std::shared_ptr<double> value) { this->left = value; }

        /**
         * A message relevant to the rectangle.
         */
        std::shared_ptr<Message> get_message() const { return message; }
        void set_message(std::shared_ptr<Message> value) { this->message = value; }

        /**
         * Key/value pairs that provide additional information about the rectangle.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The X coordinate of the right edge of the rectangle, measured in the image's natural
         * units.
         */
        std::shared_ptr<double> get_right() const { return right; }
        void set_right(std::shared_ptr<double> value) { this->right = value; }

        /**
         * The Y coordinate of the top edge of the rectangle, measured in the image's natural units.
         */
        std::shared_ptr<double> get_top() const { return top; }
        void set_top(std::shared_ptr<double> value) { this->top = value; }
    };

    /**
     * An artifact relevant to a result.
     */
    class Attachment {
        public:
        Attachment() = default;
        virtual ~Attachment() = default;

        private:
        ArtifactLocation artifact_location;
        std::shared_ptr<Message> description;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::vector<Rectangle>> rectangles;
        std::shared_ptr<std::vector<Region>> regions;

        public:
        /**
         * The location of the attachment.
         */
        const ArtifactLocation & get_artifact_location() const { return artifact_location; }
        ArtifactLocation & get_mutable_artifact_location() { return artifact_location; }
        void set_artifact_location(const ArtifactLocation & value) { this->artifact_location = value; }

        /**
         * A message describing the role played by the attachment.
         */
        std::shared_ptr<Message> get_description() const { return description; }
        void set_description(std::shared_ptr<Message> value) { this->description = value; }

        /**
         * Key/value pairs that provide additional information about the attachment.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * An array of rectangles specifying areas of interest within the image.
         */
        std::shared_ptr<std::vector<Rectangle>> get_rectangles() const { return rectangles; }
        void set_rectangles(std::shared_ptr<std::vector<Rectangle>> value) { this->rectangles = value; }

        /**
         * An array of regions of interest within the attachment.
         */
        std::shared_ptr<std::vector<Region>> get_regions() const { return regions; }
        void set_regions(std::shared_ptr<std::vector<Region>> value) { this->regions = value; }
    };

    /**
     * The state of a result relative to a baseline of a previous run.
     */
    enum class BaselineState : int { ABSENT, NEW, UNCHANGED, UPDATED };

    /**
     * Specifies the importance of this location in understanding the code flow in which it
     * occurs. The order from most to least important is "essential", "important",
     * "unimportant". Default: "important".
     */
    enum class Importance : int { ESSENTIAL, IMPORTANT, UNIMPORTANT };

    /**
     * A web request associated with this thread flow location.
     *
     * A web request object.
     *
     * A web request associated with this result.
     */
    class WebRequest {
        public:
        WebRequest() :
            index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~WebRequest() = default;

        private:
        std::shared_ptr<ArtifactContent> body;
        std::shared_ptr<std::map<std::string, std::string>> headers;
        std::shared_ptr<int64_t> index;
        ClassMemberConstraints index_constraint;
        std::shared_ptr<std::string> method;
        std::shared_ptr<std::map<std::string, std::string>> parameters;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::string> protocol;
        std::shared_ptr<std::string> target;
        std::shared_ptr<std::string> version;

        public:
        /**
         * The body of the request.
         */
        std::shared_ptr<ArtifactContent> get_body() const { return body; }
        void set_body(std::shared_ptr<ArtifactContent> value) { this->body = value; }

        /**
         * The request headers.
         */
        std::shared_ptr<std::map<std::string, std::string>> get_headers() const { return headers; }
        void set_headers(std::shared_ptr<std::map<std::string, std::string>> value) { this->headers = value; }

        /**
         * The index within the run.webRequests array of the request object associated with this
         * result.
         */
        std::shared_ptr<int64_t> get_index() const { return index; }
        void set_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("index", index_constraint, *value); this->index = value; }

        /**
         * The HTTP method. Well-known values are 'GET', 'PUT', 'POST', 'DELETE', 'PATCH', 'HEAD',
         * 'OPTIONS', 'TRACE', 'CONNECT'.
         */
        std::shared_ptr<std::string> get_method() const { return method; }
        void set_method(std::shared_ptr<std::string> value) { this->method = value; }

        /**
         * The request parameters.
         */
        std::shared_ptr<std::map<std::string, std::string>> get_parameters() const { return parameters; }
        void set_parameters(std::shared_ptr<std::map<std::string, std::string>> value) { this->parameters = value; }

        /**
         * Key/value pairs that provide additional information about the request.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The request protocol. Example: 'http'.
         */
        std::shared_ptr<std::string> get_protocol() const { return protocol; }
        void set_protocol(std::shared_ptr<std::string> value) { this->protocol = value; }

        /**
         * The target of the request.
         */
        std::shared_ptr<std::string> get_target() const { return target; }
        void set_target(std::shared_ptr<std::string> value) { this->target = value; }

        /**
         * The request version. Example: '1.1'.
         */
        std::shared_ptr<std::string> get_version() const { return version; }
        void set_version(std::shared_ptr<std::string> value) { this->version = value; }
    };

    /**
     * A web response associated with this thread flow location.
     *
     * A web response object.
     *
     * A web response associated with this result.
     */
    class WebResponse {
        public:
        WebResponse() :
            index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~WebResponse() = default;

        private:
        std::shared_ptr<ArtifactContent> body;
        std::shared_ptr<std::map<std::string, std::string>> headers;
        std::shared_ptr<int64_t> index;
        ClassMemberConstraints index_constraint;
        std::shared_ptr<bool> no_response_received;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::string> protocol;
        std::shared_ptr<std::string> reason_phrase;
        std::shared_ptr<int64_t> status_code;
        std::shared_ptr<std::string> version;

        public:
        /**
         * The body of the response.
         */
        std::shared_ptr<ArtifactContent> get_body() const { return body; }
        void set_body(std::shared_ptr<ArtifactContent> value) { this->body = value; }

        /**
         * The response headers.
         */
        std::shared_ptr<std::map<std::string, std::string>> get_headers() const { return headers; }
        void set_headers(std::shared_ptr<std::map<std::string, std::string>> value) { this->headers = value; }

        /**
         * The index within the run.webResponses array of the response object associated with this
         * result.
         */
        std::shared_ptr<int64_t> get_index() const { return index; }
        void set_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("index", index_constraint, *value); this->index = value; }

        /**
         * Specifies whether a response was received from the server.
         */
        std::shared_ptr<bool> get_no_response_received() const { return no_response_received; }
        void set_no_response_received(std::shared_ptr<bool> value) { this->no_response_received = value; }

        /**
         * Key/value pairs that provide additional information about the response.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The response protocol. Example: 'http'.
         */
        std::shared_ptr<std::string> get_protocol() const { return protocol; }
        void set_protocol(std::shared_ptr<std::string> value) { this->protocol = value; }

        /**
         * The response reason. Example: 'Not found'.
         */
        std::shared_ptr<std::string> get_reason_phrase() const { return reason_phrase; }
        void set_reason_phrase(std::shared_ptr<std::string> value) { this->reason_phrase = value; }

        /**
         * The response status code. Example: 451.
         */
        std::shared_ptr<int64_t> get_status_code() const { return status_code; }
        void set_status_code(std::shared_ptr<int64_t> value) { this->status_code = value; }

        /**
         * The response version. Example: '1.1'.
         */
        std::shared_ptr<std::string> get_version() const { return version; }
        void set_version(std::shared_ptr<std::string> value) { this->version = value; }
    };

    /**
     * A location visited by an analysis tool while simulating or monitoring the execution of a
     * program.
     */
    class ThreadFlowLocation {
        public:
        ThreadFlowLocation() :
            execution_order_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            nesting_level_constraint(0, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~ThreadFlowLocation() = default;

        private:
        std::shared_ptr<int64_t> execution_order;
        ClassMemberConstraints execution_order_constraint;
        std::shared_ptr<std::string> execution_time_utc;
        std::shared_ptr<Importance> importance;
        std::shared_ptr<int64_t> index;
        ClassMemberConstraints index_constraint;
        std::shared_ptr<std::vector<std::string>> kinds;
        std::shared_ptr<Location> location;
        std::shared_ptr<std::string> thread_flow_location_module;
        std::shared_ptr<int64_t> nesting_level;
        ClassMemberConstraints nesting_level_constraint;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<Stack> stack;
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> state;
        std::shared_ptr<std::vector<ReportingDescriptorReference>> taxa;
        std::shared_ptr<WebRequest> web_request;
        std::shared_ptr<WebResponse> web_response;

        public:
        /**
         * An integer representing the temporal order in which execution reached this location.
         */
        std::shared_ptr<int64_t> get_execution_order() const { return execution_order; }
        void set_execution_order(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("execution_order", execution_order_constraint, *value); this->execution_order = value; }

        /**
         * The Coordinated Universal Time (UTC) date and time at which this location was executed.
         */
        std::shared_ptr<std::string> get_execution_time_utc() const { return execution_time_utc; }
        void set_execution_time_utc(std::shared_ptr<std::string> value) { this->execution_time_utc = value; }

        /**
         * Specifies the importance of this location in understanding the code flow in which it
         * occurs. The order from most to least important is "essential", "important",
         * "unimportant". Default: "important".
         */
        std::shared_ptr<Importance> get_importance() const { return importance; }
        void set_importance(std::shared_ptr<Importance> value) { this->importance = value; }

        /**
         * The index within the run threadFlowLocations array.
         */
        std::shared_ptr<int64_t> get_index() const { return index; }
        void set_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("index", index_constraint, *value); this->index = value; }

        /**
         * A set of distinct strings that categorize the thread flow location. Well-known kinds
         * include 'acquire', 'release', 'enter', 'exit', 'call', 'return', 'branch', 'implicit',
         * 'false', 'true', 'caution', 'danger', 'unknown', 'unreachable', 'taint', 'function',
         * 'handler', 'lock', 'memory', 'resource', 'scope' and 'value'.
         */
        std::shared_ptr<std::vector<std::string>> get_kinds() const { return kinds; }
        void set_kinds(std::shared_ptr<std::vector<std::string>> value) { this->kinds = value; }

        /**
         * The code location.
         */
        std::shared_ptr<Location> get_location() const { return location; }
        void set_location(std::shared_ptr<Location> value) { this->location = value; }

        /**
         * The name of the module that contains the code that is executing.
         */
        std::shared_ptr<std::string> get_thread_flow_location_module() const { return thread_flow_location_module; }
        void set_thread_flow_location_module(std::shared_ptr<std::string> value) { this->thread_flow_location_module = value; }

        /**
         * An integer representing a containment hierarchy within the thread flow.
         */
        std::shared_ptr<int64_t> get_nesting_level() const { return nesting_level; }
        void set_nesting_level(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("nesting_level", nesting_level_constraint, *value); this->nesting_level = value; }

        /**
         * Key/value pairs that provide additional information about the threadflow location.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The call stack leading to this location.
         */
        std::shared_ptr<Stack> get_stack() const { return stack; }
        void set_stack(std::shared_ptr<Stack> value) { this->stack = value; }

        /**
         * A dictionary, each of whose keys specifies a variable or expression, the associated value
         * of which represents the variable or expression value. For an annotation of kind
         * 'continuation', for example, this dictionary might hold the current assumed values of a
         * set of global variables.
         */
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> get_state() const { return state; }
        void set_state(std::shared_ptr<std::map<std::string, MultiformatMessageString>> value) { this->state = value; }

        /**
         * An array of references to rule or taxonomy reporting descriptors that are applicable to
         * the thread flow location.
         */
        std::shared_ptr<std::vector<ReportingDescriptorReference>> get_taxa() const { return taxa; }
        void set_taxa(std::shared_ptr<std::vector<ReportingDescriptorReference>> value) { this->taxa = value; }

        /**
         * A web request associated with this thread flow location.
         */
        std::shared_ptr<WebRequest> get_web_request() const { return web_request; }
        void set_web_request(std::shared_ptr<WebRequest> value) { this->web_request = value; }

        /**
         * A web response associated with this thread flow location.
         */
        std::shared_ptr<WebResponse> get_web_response() const { return web_response; }
        void set_web_response(std::shared_ptr<WebResponse> value) { this->web_response = value; }
    };

    class ThreadFlow {
        public:
        ThreadFlow() = default;
        virtual ~ThreadFlow() = default;

        private:
        std::shared_ptr<std::string> id;
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> immutable_state;
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> initial_state;
        std::vector<ThreadFlowLocation> locations;
        std::shared_ptr<Message> message;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * An string that uniquely identifies the threadFlow within the codeFlow in which it occurs.
         */
        std::shared_ptr<std::string> get_id() const { return id; }
        void set_id(std::shared_ptr<std::string> value) { this->id = value; }

        /**
         * Values of relevant expressions at the start of the thread flow that remain constant.
         */
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> get_immutable_state() const { return immutable_state; }
        void set_immutable_state(std::shared_ptr<std::map<std::string, MultiformatMessageString>> value) { this->immutable_state = value; }

        /**
         * Values of relevant expressions at the start of the thread flow that may change during
         * thread flow execution.
         */
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> get_initial_state() const { return initial_state; }
        void set_initial_state(std::shared_ptr<std::map<std::string, MultiformatMessageString>> value) { this->initial_state = value; }

        /**
         * A temporally ordered array of 'threadFlowLocation' objects, each of which describes a
         * location visited by the tool while producing the result.
         */
        const std::vector<ThreadFlowLocation> & get_locations() const { return locations; }
        std::vector<ThreadFlowLocation> & get_mutable_locations() { return locations; }
        void set_locations(const std::vector<ThreadFlowLocation> & value) { this->locations = value; }

        /**
         * A message relevant to the thread flow.
         */
        std::shared_ptr<Message> get_message() const { return message; }
        void set_message(std::shared_ptr<Message> value) { this->message = value; }

        /**
         * Key/value pairs that provide additional information about the thread flow.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * A set of threadFlows which together describe a pattern of code execution relevant to
     * detecting a result.
     */
    class CodeFlow {
        public:
        CodeFlow() = default;
        virtual ~CodeFlow() = default;

        private:
        std::shared_ptr<Message> message;
        std::shared_ptr<PropertyBag> properties;
        std::vector<ThreadFlow> thread_flows;

        public:
        /**
         * A message relevant to the code flow.
         */
        std::shared_ptr<Message> get_message() const { return message; }
        void set_message(std::shared_ptr<Message> value) { this->message = value; }

        /**
         * Key/value pairs that provide additional information about the code flow.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * An array of one or more unique threadFlow objects, each of which describes the progress
         * of a program through a thread of execution.
         */
        const std::vector<ThreadFlow> & get_thread_flows() const { return thread_flows; }
        std::vector<ThreadFlow> & get_mutable_thread_flows() { return thread_flows; }
        void set_thread_flows(const std::vector<ThreadFlow> & value) { this->thread_flows = value; }
    };

    /**
     * The replacement of a single region of an artifact.
     */
    class Replacement {
        public:
        Replacement() = default;
        virtual ~Replacement() = default;

        private:
        Region deleted_region;
        std::shared_ptr<ArtifactContent> inserted_content;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * The region of the artifact to delete.
         */
        const Region & get_deleted_region() const { return deleted_region; }
        Region & get_mutable_deleted_region() { return deleted_region; }
        void set_deleted_region(const Region & value) { this->deleted_region = value; }

        /**
         * The content to insert at the location specified by the 'deletedRegion' property.
         */
        std::shared_ptr<ArtifactContent> get_inserted_content() const { return inserted_content; }
        void set_inserted_content(std::shared_ptr<ArtifactContent> value) { this->inserted_content = value; }

        /**
         * Key/value pairs that provide additional information about the replacement.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * A change to a single artifact.
     */
    class ArtifactChange {
        public:
        ArtifactChange() = default;
        virtual ~ArtifactChange() = default;

        private:
        ArtifactLocation artifact_location;
        std::shared_ptr<PropertyBag> properties;
        std::vector<Replacement> replacements;

        public:
        /**
         * The location of the artifact to change.
         */
        const ArtifactLocation & get_artifact_location() const { return artifact_location; }
        ArtifactLocation & get_mutable_artifact_location() { return artifact_location; }
        void set_artifact_location(const ArtifactLocation & value) { this->artifact_location = value; }

        /**
         * Key/value pairs that provide additional information about the change.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * An array of replacement objects, each of which represents the replacement of a single
         * region in a single artifact specified by 'artifactLocation'.
         */
        const std::vector<Replacement> & get_replacements() const { return replacements; }
        std::vector<Replacement> & get_mutable_replacements() { return replacements; }
        void set_replacements(const std::vector<Replacement> & value) { this->replacements = value; }
    };

    /**
     * A proposed fix for the problem represented by a result object. A fix specifies a set of
     * artifacts to modify. For each artifact, it specifies a set of bytes to remove, and
     * provides a set of new bytes to replace them.
     */
    class Fix {
        public:
        Fix() = default;
        virtual ~Fix() = default;

        private:
        std::vector<ArtifactChange> artifact_changes;
        std::shared_ptr<Message> description;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * One or more artifact changes that comprise a fix for a result.
         */
        const std::vector<ArtifactChange> & get_artifact_changes() const { return artifact_changes; }
        std::vector<ArtifactChange> & get_mutable_artifact_changes() { return artifact_changes; }
        void set_artifact_changes(const std::vector<ArtifactChange> & value) { this->artifact_changes = value; }

        /**
         * A message that describes the proposed fix, enabling viewers to present the proposed
         * change to an end user.
         */
        std::shared_ptr<Message> get_description() const { return description; }
        void set_description(std::shared_ptr<Message> value) { this->description = value; }

        /**
         * Key/value pairs that provide additional information about the fix.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * Represents the traversal of a single edge during a graph traversal.
     */
    class EdgeTraversal {
        public:
        EdgeTraversal() :
            step_over_edge_count_constraint(0, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~EdgeTraversal() = default;

        private:
        std::string edge_id;
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> final_state;
        std::shared_ptr<Message> message;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<int64_t> step_over_edge_count;
        ClassMemberConstraints step_over_edge_count_constraint;

        public:
        /**
         * Identifies the edge being traversed.
         */
        const std::string & get_edge_id() const { return edge_id; }
        std::string & get_mutable_edge_id() { return edge_id; }
        void set_edge_id(const std::string & value) { this->edge_id = value; }

        /**
         * The values of relevant expressions after the edge has been traversed.
         */
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> get_final_state() const { return final_state; }
        void set_final_state(std::shared_ptr<std::map<std::string, MultiformatMessageString>> value) { this->final_state = value; }

        /**
         * A message to display to the user as the edge is traversed.
         */
        std::shared_ptr<Message> get_message() const { return message; }
        void set_message(std::shared_ptr<Message> value) { this->message = value; }

        /**
         * Key/value pairs that provide additional information about the edge traversal.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The number of edge traversals necessary to return from a nested graph.
         */
        std::shared_ptr<int64_t> get_step_over_edge_count() const { return step_over_edge_count; }
        void set_step_over_edge_count(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("step_over_edge_count", step_over_edge_count_constraint, *value); this->step_over_edge_count = value; }
    };

    /**
     * Represents a path through a graph.
     */
    class GraphTraversal {
        public:
        GraphTraversal() :
            result_graph_index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            run_graph_index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~GraphTraversal() = default;

        private:
        std::shared_ptr<Message> description;
        std::shared_ptr<std::vector<EdgeTraversal>> edge_traversals;
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> immutable_state;
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> initial_state;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<int64_t> result_graph_index;
        ClassMemberConstraints result_graph_index_constraint;
        std::shared_ptr<int64_t> run_graph_index;
        ClassMemberConstraints run_graph_index_constraint;

        public:
        /**
         * A description of this graph traversal.
         */
        std::shared_ptr<Message> get_description() const { return description; }
        void set_description(std::shared_ptr<Message> value) { this->description = value; }

        /**
         * The sequences of edges traversed by this graph traversal.
         */
        std::shared_ptr<std::vector<EdgeTraversal>> get_edge_traversals() const { return edge_traversals; }
        void set_edge_traversals(std::shared_ptr<std::vector<EdgeTraversal>> value) { this->edge_traversals = value; }

        /**
         * Values of relevant expressions at the start of the graph traversal that remain constant
         * for the graph traversal.
         */
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> get_immutable_state() const { return immutable_state; }
        void set_immutable_state(std::shared_ptr<std::map<std::string, MultiformatMessageString>> value) { this->immutable_state = value; }

        /**
         * Values of relevant expressions at the start of the graph traversal that may change during
         * graph traversal.
         */
        std::shared_ptr<std::map<std::string, MultiformatMessageString>> get_initial_state() const { return initial_state; }
        void set_initial_state(std::shared_ptr<std::map<std::string, MultiformatMessageString>> value) { this->initial_state = value; }

        /**
         * Key/value pairs that provide additional information about the graph traversal.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The index within the result.graphs to be associated with the result.
         */
        std::shared_ptr<int64_t> get_result_graph_index() const { return result_graph_index; }
        void set_result_graph_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("result_graph_index", result_graph_index_constraint, *value); this->result_graph_index = value; }

        /**
         * The index within the run.graphs to be associated with the result.
         */
        std::shared_ptr<int64_t> get_run_graph_index() const { return run_graph_index; }
        void set_run_graph_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("run_graph_index", run_graph_index_constraint, *value); this->run_graph_index = value; }
    };

    /**
     * A value that categorizes results by evaluation state.
     */
    enum class ResultKind : int { FAIL, INFORMATIONAL, NOT_APPLICABLE, OPEN, PASS, REVIEW };

    /**
     * Information about how and when the result was detected.
     *
     * Contains information about how and when a result was detected.
     */
    class ResultProvenance {
        public:
        ResultProvenance() :
            first_detection_run_guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$")),
            invocation_index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            last_detection_run_guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$"))
        {}
        virtual ~ResultProvenance() = default;

        private:
        std::shared_ptr<std::vector<PhysicalLocation>> conversion_sources;
        std::shared_ptr<std::string> first_detection_run_guid;
        ClassMemberConstraints first_detection_run_guid_constraint;
        std::shared_ptr<std::string> first_detection_time_utc;
        std::shared_ptr<int64_t> invocation_index;
        ClassMemberConstraints invocation_index_constraint;
        std::shared_ptr<std::string> last_detection_run_guid;
        ClassMemberConstraints last_detection_run_guid_constraint;
        std::shared_ptr<std::string> last_detection_time_utc;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * An array of physicalLocation objects which specify the portions of an analysis tool's
         * output that a converter transformed into the result.
         */
        std::shared_ptr<std::vector<PhysicalLocation>> get_conversion_sources() const { return conversion_sources; }
        void set_conversion_sources(std::shared_ptr<std::vector<PhysicalLocation>> value) { this->conversion_sources = value; }

        /**
         * A GUID-valued string equal to the automationDetails.guid property of the run in which the
         * result was first detected.
         */
        std::shared_ptr<std::string> get_first_detection_run_guid() const { return first_detection_run_guid; }
        void set_first_detection_run_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("first_detection_run_guid", first_detection_run_guid_constraint, *value); this->first_detection_run_guid = value; }

        /**
         * The Coordinated Universal Time (UTC) date and time at which the result was first
         * detected. See "Date/time properties" in the SARIF spec for the required format.
         */
        std::shared_ptr<std::string> get_first_detection_time_utc() const { return first_detection_time_utc; }
        void set_first_detection_time_utc(std::shared_ptr<std::string> value) { this->first_detection_time_utc = value; }

        /**
         * The index within the run.invocations array of the invocation object which describes the
         * tool invocation that detected the result.
         */
        std::shared_ptr<int64_t> get_invocation_index() const { return invocation_index; }
        void set_invocation_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("invocation_index", invocation_index_constraint, *value); this->invocation_index = value; }

        /**
         * A GUID-valued string equal to the automationDetails.guid property of the run in which the
         * result was most recently detected.
         */
        std::shared_ptr<std::string> get_last_detection_run_guid() const { return last_detection_run_guid; }
        void set_last_detection_run_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("last_detection_run_guid", last_detection_run_guid_constraint, *value); this->last_detection_run_guid = value; }

        /**
         * The Coordinated Universal Time (UTC) date and time at which the result was most recently
         * detected. See "Date/time properties" in the SARIF spec for the required format.
         */
        std::shared_ptr<std::string> get_last_detection_time_utc() const { return last_detection_time_utc; }
        void set_last_detection_time_utc(std::shared_ptr<std::string> value) { this->last_detection_time_utc = value; }

        /**
         * Key/value pairs that provide additional information about the result.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * A string that indicates where the suppression is persisted.
     */
    enum class SuppressionKind : int { EXTERNAL, IN_SOURCE };

    /**
     * A string that indicates the state of the suppression.
     */
    enum class State : int { ACCEPTED, REJECTED, UNDER_REVIEW };

    /**
     * A suppression that is relevant to a result.
     */
    class Suppression {
        public:
        Suppression() :
            guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$"))
        {}
        virtual ~Suppression() = default;

        private:
        std::shared_ptr<std::string> guid;
        ClassMemberConstraints guid_constraint;
        std::shared_ptr<std::string> justification;
        SuppressionKind kind;
        std::shared_ptr<Location> location;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<State> state;

        public:
        /**
         * A stable, unique identifer for the suprression in the form of a GUID.
         */
        std::shared_ptr<std::string> get_guid() const { return guid; }
        void set_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("guid", guid_constraint, *value); this->guid = value; }

        /**
         * A string representing the justification for the suppression.
         */
        std::shared_ptr<std::string> get_justification() const { return justification; }
        void set_justification(std::shared_ptr<std::string> value) { this->justification = value; }

        /**
         * A string that indicates where the suppression is persisted.
         */
        const SuppressionKind & get_kind() const { return kind; }
        SuppressionKind & get_mutable_kind() { return kind; }
        void set_kind(const SuppressionKind & value) { this->kind = value; }

        /**
         * Identifies the location associated with the suppression.
         */
        std::shared_ptr<Location> get_location() const { return location; }
        void set_location(std::shared_ptr<Location> value) { this->location = value; }

        /**
         * Key/value pairs that provide additional information about the suppression.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * A string that indicates the state of the suppression.
         */
        std::shared_ptr<State> get_state() const { return state; }
        void set_state(std::shared_ptr<State> value) { this->state = value; }
    };

    /**
     * A result produced by an analysis tool.
     */
    class Result {
        public:
        Result() :
            correlation_guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$")),
            guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$")),
            occurrence_count_constraint(1, std::nullopt, std::nullopt, std::nullopt, std::nullopt),
            rank_constraint(-1, 100, std::nullopt, std::nullopt, std::nullopt),
            rule_index_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~Result() = default;

        private:
        std::shared_ptr<ArtifactLocation> analysis_target;
        std::shared_ptr<std::vector<Attachment>> attachments;
        std::shared_ptr<BaselineState> baseline_state;
        std::shared_ptr<std::vector<CodeFlow>> code_flows;
        std::shared_ptr<std::string> correlation_guid;
        ClassMemberConstraints correlation_guid_constraint;
        std::shared_ptr<std::map<std::string, std::string>> fingerprints;
        std::shared_ptr<std::vector<Fix>> fixes;
        std::shared_ptr<std::vector<Graph>> graphs;
        std::shared_ptr<std::vector<GraphTraversal>> graph_traversals;
        std::shared_ptr<std::string> guid;
        ClassMemberConstraints guid_constraint;
        std::shared_ptr<std::string> hosted_viewer_uri;
        std::shared_ptr<ResultKind> kind;
        std::shared_ptr<Level> level;
        std::shared_ptr<std::vector<Location>> locations;
        Message message;
        std::shared_ptr<int64_t> occurrence_count;
        ClassMemberConstraints occurrence_count_constraint;
        std::shared_ptr<std::map<std::string, std::string>> partial_fingerprints;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<ResultProvenance> provenance;
        std::shared_ptr<double> rank;
        ClassMemberConstraints rank_constraint;
        std::shared_ptr<std::vector<Location>> related_locations;
        std::shared_ptr<ReportingDescriptorReference> rule;
        std::shared_ptr<std::string> rule_id;
        std::shared_ptr<int64_t> rule_index;
        ClassMemberConstraints rule_index_constraint;
        std::shared_ptr<std::vector<Stack>> stacks;
        std::shared_ptr<std::vector<Suppression>> suppressions;
        std::shared_ptr<std::vector<ReportingDescriptorReference>> taxa;
        std::shared_ptr<WebRequest> web_request;
        std::shared_ptr<WebResponse> web_response;
        std::shared_ptr<std::vector<std::string>> work_item_uris;

        public:
        /**
         * Identifies the artifact that the analysis tool was instructed to scan. This need not be
         * the same as the artifact where the result actually occurred.
         */
        std::shared_ptr<ArtifactLocation> get_analysis_target() const { return analysis_target; }
        void set_analysis_target(std::shared_ptr<ArtifactLocation> value) { this->analysis_target = value; }

        /**
         * A set of artifacts relevant to the result.
         */
        std::shared_ptr<std::vector<Attachment>> get_attachments() const { return attachments; }
        void set_attachments(std::shared_ptr<std::vector<Attachment>> value) { this->attachments = value; }

        /**
         * The state of a result relative to a baseline of a previous run.
         */
        std::shared_ptr<BaselineState> get_baseline_state() const { return baseline_state; }
        void set_baseline_state(std::shared_ptr<BaselineState> value) { this->baseline_state = value; }

        /**
         * An array of 'codeFlow' objects relevant to the result.
         */
        std::shared_ptr<std::vector<CodeFlow>> get_code_flows() const { return code_flows; }
        void set_code_flows(std::shared_ptr<std::vector<CodeFlow>> value) { this->code_flows = value; }

        /**
         * A stable, unique identifier for the equivalence class of logically identical results to
         * which this result belongs, in the form of a GUID.
         */
        std::shared_ptr<std::string> get_correlation_guid() const { return correlation_guid; }
        void set_correlation_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("correlation_guid", correlation_guid_constraint, *value); this->correlation_guid = value; }

        /**
         * A set of strings each of which individually defines a stable, unique identity for the
         * result.
         */
        std::shared_ptr<std::map<std::string, std::string>> get_fingerprints() const { return fingerprints; }
        void set_fingerprints(std::shared_ptr<std::map<std::string, std::string>> value) { this->fingerprints = value; }

        /**
         * An array of 'fix' objects, each of which represents a proposed fix to the problem
         * indicated by the result.
         */
        std::shared_ptr<std::vector<Fix>> get_fixes() const { return fixes; }
        void set_fixes(std::shared_ptr<std::vector<Fix>> value) { this->fixes = value; }

        /**
         * An array of zero or more unique graph objects associated with the result.
         */
        std::shared_ptr<std::vector<Graph>> get_graphs() const { return graphs; }
        void set_graphs(std::shared_ptr<std::vector<Graph>> value) { this->graphs = value; }

        /**
         * An array of one or more unique 'graphTraversal' objects.
         */
        std::shared_ptr<std::vector<GraphTraversal>> get_graph_traversals() const { return graph_traversals; }
        void set_graph_traversals(std::shared_ptr<std::vector<GraphTraversal>> value) { this->graph_traversals = value; }

        /**
         * A stable, unique identifer for the result in the form of a GUID.
         */
        std::shared_ptr<std::string> get_guid() const { return guid; }
        void set_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("guid", guid_constraint, *value); this->guid = value; }

        /**
         * An absolute URI at which the result can be viewed.
         */
        std::shared_ptr<std::string> get_hosted_viewer_uri() const { return hosted_viewer_uri; }
        void set_hosted_viewer_uri(std::shared_ptr<std::string> value) { this->hosted_viewer_uri = value; }

        /**
         * A value that categorizes results by evaluation state.
         */
        std::shared_ptr<ResultKind> get_kind() const { return kind; }
        void set_kind(std::shared_ptr<ResultKind> value) { this->kind = value; }

        /**
         * A value specifying the severity level of the result.
         */
        std::shared_ptr<Level> get_level() const { return level; }
        void set_level(std::shared_ptr<Level> value) { this->level = value; }

        /**
         * The set of locations where the result was detected. Specify only one location unless the
         * problem indicated by the result can only be corrected by making a change at every
         * specified location.
         */
        std::shared_ptr<std::vector<Location>> get_locations() const { return locations; }
        void set_locations(std::shared_ptr<std::vector<Location>> value) { this->locations = value; }

        /**
         * A message that describes the result. The first sentence of the message only will be
         * displayed when visible space is limited.
         */
        const Message & get_message() const { return message; }
        Message & get_mutable_message() { return message; }
        void set_message(const Message & value) { this->message = value; }

        /**
         * A positive integer specifying the number of times this logically unique result was
         * observed in this run.
         */
        std::shared_ptr<int64_t> get_occurrence_count() const { return occurrence_count; }
        void set_occurrence_count(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("occurrence_count", occurrence_count_constraint, *value); this->occurrence_count = value; }

        /**
         * A set of strings that contribute to the stable, unique identity of the result.
         */
        std::shared_ptr<std::map<std::string, std::string>> get_partial_fingerprints() const { return partial_fingerprints; }
        void set_partial_fingerprints(std::shared_ptr<std::map<std::string, std::string>> value) { this->partial_fingerprints = value; }

        /**
         * Key/value pairs that provide additional information about the result.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * Information about how and when the result was detected.
         */
        std::shared_ptr<ResultProvenance> get_provenance() const { return provenance; }
        void set_provenance(std::shared_ptr<ResultProvenance> value) { this->provenance = value; }

        /**
         * A number representing the priority or importance of the result.
         */
        std::shared_ptr<double> get_rank() const { return rank; }
        void set_rank(std::shared_ptr<double> value) { if (value) CheckConstraint("rank", rank_constraint, *value); this->rank = value; }

        /**
         * A set of locations relevant to this result.
         */
        std::shared_ptr<std::vector<Location>> get_related_locations() const { return related_locations; }
        void set_related_locations(std::shared_ptr<std::vector<Location>> value) { this->related_locations = value; }

        /**
         * A reference used to locate the rule descriptor relevant to this result.
         */
        std::shared_ptr<ReportingDescriptorReference> get_rule() const { return rule; }
        void set_rule(std::shared_ptr<ReportingDescriptorReference> value) { this->rule = value; }

        /**
         * The stable, unique identifier of the rule, if any, to which this notification is
         * relevant. This member can be used to retrieve rule metadata from the rules dictionary, if
         * it exists.
         */
        std::shared_ptr<std::string> get_rule_id() const { return rule_id; }
        void set_rule_id(std::shared_ptr<std::string> value) { this->rule_id = value; }

        /**
         * The index within the tool component rules array of the rule object associated with this
         * result.
         */
        std::shared_ptr<int64_t> get_rule_index() const { return rule_index; }
        void set_rule_index(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("rule_index", rule_index_constraint, *value); this->rule_index = value; }

        /**
         * An array of 'stack' objects relevant to the result.
         */
        std::shared_ptr<std::vector<Stack>> get_stacks() const { return stacks; }
        void set_stacks(std::shared_ptr<std::vector<Stack>> value) { this->stacks = value; }

        /**
         * A set of suppressions relevant to this result.
         */
        std::shared_ptr<std::vector<Suppression>> get_suppressions() const { return suppressions; }
        void set_suppressions(std::shared_ptr<std::vector<Suppression>> value) { this->suppressions = value; }

        /**
         * An array of references to taxonomy reporting descriptors that are applicable to the
         * result.
         */
        std::shared_ptr<std::vector<ReportingDescriptorReference>> get_taxa() const { return taxa; }
        void set_taxa(std::shared_ptr<std::vector<ReportingDescriptorReference>> value) { this->taxa = value; }

        /**
         * A web request associated with this result.
         */
        std::shared_ptr<WebRequest> get_web_request() const { return web_request; }
        void set_web_request(std::shared_ptr<WebRequest> value) { this->web_request = value; }

        /**
         * A web response associated with this result.
         */
        std::shared_ptr<WebResponse> get_web_response() const { return web_response; }
        void set_web_response(std::shared_ptr<WebResponse> value) { this->web_response = value; }

        /**
         * The URIs of the work items associated with this result.
         */
        std::shared_ptr<std::vector<std::string>> get_work_item_uris() const { return work_item_uris; }
        void set_work_item_uris(std::shared_ptr<std::vector<std::string>> value) { this->work_item_uris = value; }
    };

    /**
     * The SARIF format version of this external properties object.
     *
     * The SARIF format version of this log file.
     */
    enum class Version : int { THE_210 };

    class ExternalProperties {
        public:
        ExternalProperties() :
            guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$")),
            run_guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$"))
        {}
        virtual ~ExternalProperties() = default;

        private:
        std::shared_ptr<std::vector<Address>> addresses;
        std::shared_ptr<std::vector<Artifact>> artifacts;
        std::shared_ptr<Conversion> conversion;
        std::shared_ptr<ToolComponent> driver;
        std::shared_ptr<std::vector<ToolComponent>> extensions;
        std::shared_ptr<PropertyBag> externalized_properties;
        std::shared_ptr<std::vector<Graph>> graphs;
        std::shared_ptr<std::string> guid;
        ClassMemberConstraints guid_constraint;
        std::shared_ptr<std::vector<Invocation>> invocations;
        std::shared_ptr<std::vector<LogicalLocation>> logical_locations;
        std::shared_ptr<std::vector<ToolComponent>> policies;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::vector<Result>> results;
        std::shared_ptr<std::string> run_guid;
        ClassMemberConstraints run_guid_constraint;
        std::shared_ptr<std::string> schema;
        std::shared_ptr<std::vector<ToolComponent>> taxonomies;
        std::shared_ptr<std::vector<ThreadFlowLocation>> thread_flow_locations;
        std::shared_ptr<std::vector<ToolComponent>> translations;
        std::shared_ptr<Version> version;
        std::shared_ptr<std::vector<WebRequest>> web_requests;
        std::shared_ptr<std::vector<WebResponse>> web_responses;

        public:
        /**
         * Addresses that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<Address>> get_addresses() const { return addresses; }
        void set_addresses(std::shared_ptr<std::vector<Address>> value) { this->addresses = value; }

        /**
         * An array of artifact objects that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<Artifact>> get_artifacts() const { return artifacts; }
        void set_artifacts(std::shared_ptr<std::vector<Artifact>> value) { this->artifacts = value; }

        /**
         * A conversion object that will be merged with a separate run.
         */
        std::shared_ptr<Conversion> get_conversion() const { return conversion; }
        void set_conversion(std::shared_ptr<Conversion> value) { this->conversion = value; }

        /**
         * The analysis tool object that will be merged with a separate run.
         */
        std::shared_ptr<ToolComponent> get_driver() const { return driver; }
        void set_driver(std::shared_ptr<ToolComponent> value) { this->driver = value; }

        /**
         * Tool extensions that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<ToolComponent>> get_extensions() const { return extensions; }
        void set_extensions(std::shared_ptr<std::vector<ToolComponent>> value) { this->extensions = value; }

        /**
         * Key/value pairs that provide additional information that will be merged with a separate
         * run.
         */
        std::shared_ptr<PropertyBag> get_externalized_properties() const { return externalized_properties; }
        void set_externalized_properties(std::shared_ptr<PropertyBag> value) { this->externalized_properties = value; }

        /**
         * An array of graph objects that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<Graph>> get_graphs() const { return graphs; }
        void set_graphs(std::shared_ptr<std::vector<Graph>> value) { this->graphs = value; }

        /**
         * A stable, unique identifer for this external properties object, in the form of a GUID.
         */
        std::shared_ptr<std::string> get_guid() const { return guid; }
        void set_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("guid", guid_constraint, *value); this->guid = value; }

        /**
         * Describes the invocation of the analysis tool that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<Invocation>> get_invocations() const { return invocations; }
        void set_invocations(std::shared_ptr<std::vector<Invocation>> value) { this->invocations = value; }

        /**
         * An array of logical locations such as namespaces, types or functions that will be merged
         * with a separate run.
         */
        std::shared_ptr<std::vector<LogicalLocation>> get_logical_locations() const { return logical_locations; }
        void set_logical_locations(std::shared_ptr<std::vector<LogicalLocation>> value) { this->logical_locations = value; }

        /**
         * Tool policies that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<ToolComponent>> get_policies() const { return policies; }
        void set_policies(std::shared_ptr<std::vector<ToolComponent>> value) { this->policies = value; }

        /**
         * Key/value pairs that provide additional information about the external properties.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * An array of result objects that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<Result>> get_results() const { return results; }
        void set_results(std::shared_ptr<std::vector<Result>> value) { this->results = value; }

        /**
         * A stable, unique identifer for the run associated with this external properties object,
         * in the form of a GUID.
         */
        std::shared_ptr<std::string> get_run_guid() const { return run_guid; }
        void set_run_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("run_guid", run_guid_constraint, *value); this->run_guid = value; }

        /**
         * The URI of the JSON schema corresponding to the version of the external property file
         * format.
         */
        std::shared_ptr<std::string> get_schema() const { return schema; }
        void set_schema(std::shared_ptr<std::string> value) { this->schema = value; }

        /**
         * Tool taxonomies that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<ToolComponent>> get_taxonomies() const { return taxonomies; }
        void set_taxonomies(std::shared_ptr<std::vector<ToolComponent>> value) { this->taxonomies = value; }

        /**
         * An array of threadFlowLocation objects that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<ThreadFlowLocation>> get_thread_flow_locations() const { return thread_flow_locations; }
        void set_thread_flow_locations(std::shared_ptr<std::vector<ThreadFlowLocation>> value) { this->thread_flow_locations = value; }

        /**
         * Tool translations that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<ToolComponent>> get_translations() const { return translations; }
        void set_translations(std::shared_ptr<std::vector<ToolComponent>> value) { this->translations = value; }

        /**
         * The SARIF format version of this external properties object.
         */
        std::shared_ptr<Version> get_version() const { return version; }
        void set_version(std::shared_ptr<Version> value) { this->version = value; }

        /**
         * Requests that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<WebRequest>> get_web_requests() const { return web_requests; }
        void set_web_requests(std::shared_ptr<std::vector<WebRequest>> value) { this->web_requests = value; }

        /**
         * Responses that will be merged with a separate run.
         */
        std::shared_ptr<std::vector<WebResponse>> get_web_responses() const { return web_responses; }
        void set_web_responses(std::shared_ptr<std::vector<WebResponse>> value) { this->web_responses = value; }
    };

    /**
     * Automation details that describe this run.
     *
     * Information that describes a run's identity and role within an engineering system process.
     */
    class RunAutomationDetails {
        public:
        RunAutomationDetails() :
            correlation_guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$")),
            guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$"))
        {}
        virtual ~RunAutomationDetails() = default;

        private:
        std::shared_ptr<std::string> correlation_guid;
        ClassMemberConstraints correlation_guid_constraint;
        std::shared_ptr<Message> description;
        std::shared_ptr<std::string> guid;
        ClassMemberConstraints guid_constraint;
        std::shared_ptr<std::string> id;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * A stable, unique identifier for the equivalence class of runs to which this object's
         * containing run object belongs in the form of a GUID.
         */
        std::shared_ptr<std::string> get_correlation_guid() const { return correlation_guid; }
        void set_correlation_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("correlation_guid", correlation_guid_constraint, *value); this->correlation_guid = value; }

        /**
         * A description of the identity and role played within the engineering system by this
         * object's containing run object.
         */
        std::shared_ptr<Message> get_description() const { return description; }
        void set_description(std::shared_ptr<Message> value) { this->description = value; }

        /**
         * A stable, unique identifer for this object's containing run object in the form of a GUID.
         */
        std::shared_ptr<std::string> get_guid() const { return guid; }
        void set_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("guid", guid_constraint, *value); this->guid = value; }

        /**
         * A hierarchical string that uniquely identifies this object's containing run object.
         */
        std::shared_ptr<std::string> get_id() const { return id; }
        void set_id(std::shared_ptr<std::string> value) { this->id = value; }

        /**
         * Key/value pairs that provide additional information about the run automation details.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * Specifies the unit in which the tool measures columns.
     */
    enum class ColumnKind : int { UNICODE_CODE_POINTS, UTF16_CODE_UNITS };

    /**
     * An external property file containing a run.conversion object to be merged with the root
     * log file.
     *
     * An external property file containing a run.driver object to be merged with the root log
     * file.
     *
     * An external property file containing a run.properties object to be merged with the root
     * log file.
     */
    class ExternalPropertyFileReference {
        public:
        ExternalPropertyFileReference() :
            guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$")),
            item_count_constraint(-1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)
        {}
        virtual ~ExternalPropertyFileReference() = default;

        private:
        std::shared_ptr<std::string> guid;
        ClassMemberConstraints guid_constraint;
        std::shared_ptr<int64_t> item_count;
        ClassMemberConstraints item_count_constraint;
        std::shared_ptr<ArtifactLocation> location;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * A stable, unique identifer for the external property file in the form of a GUID.
         */
        std::shared_ptr<std::string> get_guid() const { return guid; }
        void set_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("guid", guid_constraint, *value); this->guid = value; }

        /**
         * A non-negative integer specifying the number of items contained in the external property
         * file.
         */
        std::shared_ptr<int64_t> get_item_count() const { return item_count; }
        void set_item_count(std::shared_ptr<int64_t> value) { if (value) CheckConstraint("item_count", item_count_constraint, *value); this->item_count = value; }

        /**
         * The location of the external property file.
         */
        std::shared_ptr<ArtifactLocation> get_location() const { return location; }
        void set_location(std::shared_ptr<ArtifactLocation> value) { this->location = value; }

        /**
         * Key/value pairs that provide additional information about the external property file.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * References to external property files that should be inlined with the content of a root
     * log file.
     */
    class ExternalPropertyFileReferences {
        public:
        ExternalPropertyFileReferences() = default;
        virtual ~ExternalPropertyFileReferences() = default;

        private:
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> addresses;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> artifacts;
        std::shared_ptr<ExternalPropertyFileReference> conversion;
        std::shared_ptr<ExternalPropertyFileReference> driver;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> extensions;
        std::shared_ptr<ExternalPropertyFileReference> externalized_properties;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> graphs;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> invocations;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> logical_locations;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> policies;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> results;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> taxonomies;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> thread_flow_locations;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> translations;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> web_requests;
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> web_responses;

        public:
        /**
         * An array of external property files containing run.addresses arrays to be merged with the
         * root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_addresses() const { return addresses; }
        void set_addresses(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->addresses = value; }

        /**
         * An array of external property files containing run.artifacts arrays to be merged with the
         * root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_artifacts() const { return artifacts; }
        void set_artifacts(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->artifacts = value; }

        /**
         * An external property file containing a run.conversion object to be merged with the root
         * log file.
         */
        std::shared_ptr<ExternalPropertyFileReference> get_conversion() const { return conversion; }
        void set_conversion(std::shared_ptr<ExternalPropertyFileReference> value) { this->conversion = value; }

        /**
         * An external property file containing a run.driver object to be merged with the root log
         * file.
         */
        std::shared_ptr<ExternalPropertyFileReference> get_driver() const { return driver; }
        void set_driver(std::shared_ptr<ExternalPropertyFileReference> value) { this->driver = value; }

        /**
         * An array of external property files containing run.extensions arrays to be merged with
         * the root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_extensions() const { return extensions; }
        void set_extensions(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->extensions = value; }

        /**
         * An external property file containing a run.properties object to be merged with the root
         * log file.
         */
        std::shared_ptr<ExternalPropertyFileReference> get_externalized_properties() const { return externalized_properties; }
        void set_externalized_properties(std::shared_ptr<ExternalPropertyFileReference> value) { this->externalized_properties = value; }

        /**
         * An array of external property files containing a run.graphs object to be merged with the
         * root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_graphs() const { return graphs; }
        void set_graphs(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->graphs = value; }

        /**
         * An array of external property files containing run.invocations arrays to be merged with
         * the root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_invocations() const { return invocations; }
        void set_invocations(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->invocations = value; }

        /**
         * An array of external property files containing run.logicalLocations arrays to be merged
         * with the root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_logical_locations() const { return logical_locations; }
        void set_logical_locations(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->logical_locations = value; }

        /**
         * An array of external property files containing run.policies arrays to be merged with the
         * root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_policies() const { return policies; }
        void set_policies(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->policies = value; }

        /**
         * Key/value pairs that provide additional information about the external property files.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * An array of external property files containing run.results arrays to be merged with the
         * root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_results() const { return results; }
        void set_results(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->results = value; }

        /**
         * An array of external property files containing run.taxonomies arrays to be merged with
         * the root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_taxonomies() const { return taxonomies; }
        void set_taxonomies(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->taxonomies = value; }

        /**
         * An array of external property files containing run.threadFlowLocations arrays to be
         * merged with the root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_thread_flow_locations() const { return thread_flow_locations; }
        void set_thread_flow_locations(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->thread_flow_locations = value; }

        /**
         * An array of external property files containing run.translations arrays to be merged with
         * the root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_translations() const { return translations; }
        void set_translations(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->translations = value; }

        /**
         * An array of external property files containing run.requests arrays to be merged with the
         * root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_web_requests() const { return web_requests; }
        void set_web_requests(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->web_requests = value; }

        /**
         * An array of external property files containing run.responses arrays to be merged with the
         * root log file.
         */
        std::shared_ptr<std::vector<ExternalPropertyFileReference>> get_web_responses() const { return web_responses; }
        void set_web_responses(std::shared_ptr<std::vector<ExternalPropertyFileReference>> value) { this->web_responses = value; }
    };

    /**
     * A specialLocations object that defines locations of special significance to SARIF
     * consumers.
     *
     * Defines locations of special significance to SARIF consumers.
     */
    class SpecialLocations {
        public:
        SpecialLocations() = default;
        virtual ~SpecialLocations() = default;

        private:
        std::shared_ptr<ArtifactLocation> display_base;
        std::shared_ptr<PropertyBag> properties;

        public:
        /**
         * Provides a suggestion to SARIF consumers to display file paths relative to the specified
         * location.
         */
        std::shared_ptr<ArtifactLocation> get_display_base() const { return display_base; }
        void set_display_base(std::shared_ptr<ArtifactLocation> value) { this->display_base = value; }

        /**
         * Key/value pairs that provide additional information about the special locations.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }
    };

    /**
     * Specifies the information necessary to retrieve a desired revision from a version control
     * system.
     */
    class VersionControlDetails {
        public:
        VersionControlDetails() = default;
        virtual ~VersionControlDetails() = default;

        private:
        std::shared_ptr<std::string> as_of_time_utc;
        std::shared_ptr<std::string> branch;
        std::shared_ptr<ArtifactLocation> mapped_to;
        std::shared_ptr<PropertyBag> properties;
        std::string repository_uri;
        std::shared_ptr<std::string> revision_id;
        std::shared_ptr<std::string> revision_tag;

        public:
        /**
         * A Coordinated Universal Time (UTC) date and time that can be used to synchronize an
         * enlistment to the state of the repository at that time.
         */
        std::shared_ptr<std::string> get_as_of_time_utc() const { return as_of_time_utc; }
        void set_as_of_time_utc(std::shared_ptr<std::string> value) { this->as_of_time_utc = value; }

        /**
         * The name of a branch containing the revision.
         */
        std::shared_ptr<std::string> get_branch() const { return branch; }
        void set_branch(std::shared_ptr<std::string> value) { this->branch = value; }

        /**
         * The location in the local file system to which the root of the repository was mapped at
         * the time of the analysis.
         */
        std::shared_ptr<ArtifactLocation> get_mapped_to() const { return mapped_to; }
        void set_mapped_to(std::shared_ptr<ArtifactLocation> value) { this->mapped_to = value; }

        /**
         * Key/value pairs that provide additional information about the version control details.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The absolute URI of the repository.
         */
        const std::string & get_repository_uri() const { return repository_uri; }
        std::string & get_mutable_repository_uri() { return repository_uri; }
        void set_repository_uri(const std::string & value) { this->repository_uri = value; }

        /**
         * A string that uniquely and permanently identifies the revision within the repository.
         */
        std::shared_ptr<std::string> get_revision_id() const { return revision_id; }
        void set_revision_id(std::shared_ptr<std::string> value) { this->revision_id = value; }

        /**
         * A tag that has been applied to the revision.
         */
        std::shared_ptr<std::string> get_revision_tag() const { return revision_tag; }
        void set_revision_tag(std::shared_ptr<std::string> value) { this->revision_tag = value; }
    };

    /**
     * Describes a single run of an analysis tool, and contains the reported output of that run.
     */
    class Run {
        public:
        Run() :
            baseline_guid_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[1-5][0-9a-fA-F]{3}-[89abAB][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$")),
            language_constraint(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::string("^[a-zA-Z]{2}|^[a-zA-Z]{2}-[a-zA-Z]{2}]?$"))
        {}
        virtual ~Run() = default;

        private:
        std::shared_ptr<std::vector<Address>> addresses;
        std::shared_ptr<std::vector<Artifact>> artifacts;
        std::shared_ptr<RunAutomationDetails> automation_details;
        std::shared_ptr<std::string> baseline_guid;
        ClassMemberConstraints baseline_guid_constraint;
        std::shared_ptr<ColumnKind> column_kind;
        std::shared_ptr<Conversion> conversion;
        std::shared_ptr<std::string> default_encoding;
        std::shared_ptr<std::string> default_source_language;
        std::shared_ptr<ExternalPropertyFileReferences> external_property_file_references;
        std::shared_ptr<std::vector<Graph>> graphs;
        std::shared_ptr<std::vector<Invocation>> invocations;
        std::shared_ptr<std::string> language;
        ClassMemberConstraints language_constraint;
        std::shared_ptr<std::vector<LogicalLocation>> logical_locations;
        std::shared_ptr<std::vector<std::string>> newline_sequences;
        std::shared_ptr<std::map<std::string, ArtifactLocation>> original_uri_base_ids;
        std::shared_ptr<std::vector<ToolComponent>> policies;
        std::shared_ptr<PropertyBag> properties;
        std::shared_ptr<std::vector<std::string>> redaction_tokens;
        std::shared_ptr<std::vector<Result>> results;
        std::shared_ptr<std::vector<RunAutomationDetails>> run_aggregates;
        std::shared_ptr<SpecialLocations> special_locations;
        std::shared_ptr<std::vector<ToolComponent>> taxonomies;
        std::shared_ptr<std::vector<ThreadFlowLocation>> thread_flow_locations;
        Tool tool;
        std::shared_ptr<std::vector<ToolComponent>> translations;
        std::shared_ptr<std::vector<VersionControlDetails>> version_control_provenance;
        std::shared_ptr<std::vector<WebRequest>> web_requests;
        std::shared_ptr<std::vector<WebResponse>> web_responses;

        public:
        /**
         * Addresses associated with this run instance, if any.
         */
        std::shared_ptr<std::vector<Address>> get_addresses() const { return addresses; }
        void set_addresses(std::shared_ptr<std::vector<Address>> value) { this->addresses = value; }

        /**
         * An array of artifact objects relevant to the run.
         */
        std::shared_ptr<std::vector<Artifact>> get_artifacts() const { return artifacts; }
        void set_artifacts(std::shared_ptr<std::vector<Artifact>> value) { this->artifacts = value; }

        /**
         * Automation details that describe this run.
         */
        std::shared_ptr<RunAutomationDetails> get_automation_details() const { return automation_details; }
        void set_automation_details(std::shared_ptr<RunAutomationDetails> value) { this->automation_details = value; }

        /**
         * The 'guid' property of a previous SARIF 'run' that comprises the baseline that was used
         * to compute result 'baselineState' properties for the run.
         */
        std::shared_ptr<std::string> get_baseline_guid() const { return baseline_guid; }
        void set_baseline_guid(std::shared_ptr<std::string> value) { if (value) CheckConstraint("baseline_guid", baseline_guid_constraint, *value); this->baseline_guid = value; }

        /**
         * Specifies the unit in which the tool measures columns.
         */
        std::shared_ptr<ColumnKind> get_column_kind() const { return column_kind; }
        void set_column_kind(std::shared_ptr<ColumnKind> value) { this->column_kind = value; }

        /**
         * A conversion object that describes how a converter transformed an analysis tool's native
         * reporting format into the SARIF format.
         */
        std::shared_ptr<Conversion> get_conversion() const { return conversion; }
        void set_conversion(std::shared_ptr<Conversion> value) { this->conversion = value; }

        /**
         * Specifies the default encoding for any artifact object that refers to a text file.
         */
        std::shared_ptr<std::string> get_default_encoding() const { return default_encoding; }
        void set_default_encoding(std::shared_ptr<std::string> value) { this->default_encoding = value; }

        /**
         * Specifies the default source language for any artifact object that refers to a text file
         * that contains source code.
         */
        std::shared_ptr<std::string> get_default_source_language() const { return default_source_language; }
        void set_default_source_language(std::shared_ptr<std::string> value) { this->default_source_language = value; }

        /**
         * References to external property files that should be inlined with the content of a root
         * log file.
         */
        std::shared_ptr<ExternalPropertyFileReferences> get_external_property_file_references() const { return external_property_file_references; }
        void set_external_property_file_references(std::shared_ptr<ExternalPropertyFileReferences> value) { this->external_property_file_references = value; }

        /**
         * An array of zero or more unique graph objects associated with the run.
         */
        std::shared_ptr<std::vector<Graph>> get_graphs() const { return graphs; }
        void set_graphs(std::shared_ptr<std::vector<Graph>> value) { this->graphs = value; }

        /**
         * Describes the invocation of the analysis tool.
         */
        std::shared_ptr<std::vector<Invocation>> get_invocations() const { return invocations; }
        void set_invocations(std::shared_ptr<std::vector<Invocation>> value) { this->invocations = value; }

        /**
         * The language of the messages emitted into the log file during this run (expressed as an
         * ISO 639-1 two-letter lowercase culture code) and an optional region (expressed as an ISO
         * 3166-1 two-letter uppercase subculture code associated with a country or region). The
         * casing is recommended but not required (in order for this data to conform to RFC5646).
         */
        std::shared_ptr<std::string> get_language() const { return language; }
        void set_language(std::shared_ptr<std::string> value) { if (value) CheckConstraint("language", language_constraint, *value); this->language = value; }

        /**
         * An array of logical locations such as namespaces, types or functions.
         */
        std::shared_ptr<std::vector<LogicalLocation>> get_logical_locations() const { return logical_locations; }
        void set_logical_locations(std::shared_ptr<std::vector<LogicalLocation>> value) { this->logical_locations = value; }

        /**
         * An ordered list of character sequences that were treated as line breaks when computing
         * region information for the run.
         */
        std::shared_ptr<std::vector<std::string>> get_newline_sequences() const { return newline_sequences; }
        void set_newline_sequences(std::shared_ptr<std::vector<std::string>> value) { this->newline_sequences = value; }

        /**
         * The artifact location specified by each uriBaseId symbol on the machine where the tool
         * originally ran.
         */
        std::shared_ptr<std::map<std::string, ArtifactLocation>> get_original_uri_base_ids() const { return original_uri_base_ids; }
        void set_original_uri_base_ids(std::shared_ptr<std::map<std::string, ArtifactLocation>> value) { this->original_uri_base_ids = value; }

        /**
         * Contains configurations that may potentially override both
         * reportingDescriptor.defaultConfiguration (the tool's default severities) and
         * invocation.configurationOverrides (severities established at run-time from the command
         * line).
         */
        std::shared_ptr<std::vector<ToolComponent>> get_policies() const { return policies; }
        void set_policies(std::shared_ptr<std::vector<ToolComponent>> value) { this->policies = value; }

        /**
         * Key/value pairs that provide additional information about the run.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * An array of strings used to replace sensitive information in a redaction-aware property.
         */
        std::shared_ptr<std::vector<std::string>> get_redaction_tokens() const { return redaction_tokens; }
        void set_redaction_tokens(std::shared_ptr<std::vector<std::string>> value) { this->redaction_tokens = value; }

        /**
         * The set of results contained in an SARIF log. The results array can be omitted when a run
         * is solely exporting rules metadata. It must be present (but may be empty) if a log file
         * represents an actual scan.
         */
        std::shared_ptr<std::vector<Result>> get_results() const { return results; }
        void set_results(std::shared_ptr<std::vector<Result>> value) { this->results = value; }

        /**
         * Automation details that describe the aggregate of runs to which this run belongs.
         */
        std::shared_ptr<std::vector<RunAutomationDetails>> get_run_aggregates() const { return run_aggregates; }
        void set_run_aggregates(std::shared_ptr<std::vector<RunAutomationDetails>> value) { this->run_aggregates = value; }

        /**
         * A specialLocations object that defines locations of special significance to SARIF
         * consumers.
         */
        std::shared_ptr<SpecialLocations> get_special_locations() const { return special_locations; }
        void set_special_locations(std::shared_ptr<SpecialLocations> value) { this->special_locations = value; }

        /**
         * An array of toolComponent objects relevant to a taxonomy in which results are categorized.
         */
        std::shared_ptr<std::vector<ToolComponent>> get_taxonomies() const { return taxonomies; }
        void set_taxonomies(std::shared_ptr<std::vector<ToolComponent>> value) { this->taxonomies = value; }

        /**
         * An array of threadFlowLocation objects cached at run level.
         */
        std::shared_ptr<std::vector<ThreadFlowLocation>> get_thread_flow_locations() const { return thread_flow_locations; }
        void set_thread_flow_locations(std::shared_ptr<std::vector<ThreadFlowLocation>> value) { this->thread_flow_locations = value; }

        /**
         * Information about the tool or tool pipeline that generated the results in this run. A run
         * can only contain results produced by a single tool or tool pipeline. A run can aggregate
         * results from multiple log files, as long as context around the tool run (tool
         * command-line arguments and the like) is identical for all aggregated files.
         */
        const Tool & get_tool() const { return tool; }
        Tool & get_mutable_tool() { return tool; }
        void set_tool(const Tool & value) { this->tool = value; }

        /**
         * The set of available translations of the localized data provided by the tool.
         */
        std::shared_ptr<std::vector<ToolComponent>> get_translations() const { return translations; }
        void set_translations(std::shared_ptr<std::vector<ToolComponent>> value) { this->translations = value; }

        /**
         * Specifies the revision in version control of the artifacts that were scanned.
         */
        std::shared_ptr<std::vector<VersionControlDetails>> get_version_control_provenance() const { return version_control_provenance; }
        void set_version_control_provenance(std::shared_ptr<std::vector<VersionControlDetails>> value) { this->version_control_provenance = value; }

        /**
         * An array of request objects cached at run level.
         */
        std::shared_ptr<std::vector<WebRequest>> get_web_requests() const { return web_requests; }
        void set_web_requests(std::shared_ptr<std::vector<WebRequest>> value) { this->web_requests = value; }

        /**
         * An array of response objects cached at run level.
         */
        std::shared_ptr<std::vector<WebResponse>> get_web_responses() const { return web_responses; }
        void set_web_responses(std::shared_ptr<std::vector<WebResponse>> value) { this->web_responses = value; }
    };

    /**
     * Static Analysis Results Format (SARIF) Version 2.1.0 JSON Schema: a standard format for
     * the output of static analysis tools.
     */
    class TopLevel {
        public:
        TopLevel() = default;
        virtual ~TopLevel() = default;

        private:
        std::shared_ptr<std::string> schema;
        std::shared_ptr<std::vector<ExternalProperties>> inline_external_properties;
        std::shared_ptr<PropertyBag> properties;
        std::vector<Run> runs;
        Version version;

        public:
        /**
         * The URI of the JSON schema corresponding to the version.
         */
        std::shared_ptr<std::string> get_schema() const { return schema; }
        void set_schema(std::shared_ptr<std::string> value) { this->schema = value; }

        /**
         * References to external property files that share data between runs.
         */
        std::shared_ptr<std::vector<ExternalProperties>> get_inline_external_properties() const { return inline_external_properties; }
        void set_inline_external_properties(std::shared_ptr<std::vector<ExternalProperties>> value) { this->inline_external_properties = value; }

        /**
         * Key/value pairs that provide additional information about the log file.
         */
        std::shared_ptr<PropertyBag> get_properties() const { return properties; }
        void set_properties(std::shared_ptr<PropertyBag> value) { this->properties = value; }

        /**
         * The set of runs contained in this log file.
         */
        const std::vector<Run> & get_runs() const { return runs; }
        std::vector<Run> & get_mutable_runs() { return runs; }
        void set_runs(const std::vector<Run> & value) { this->runs = value; }

        /**
         * The SARIF format version of this log file.
         */
        const Version & get_version() const { return version; }
        Version & get_mutable_version() { return version; }
        void set_version(const Version & value) { this->version = value; }
    };
}
namespace nlohmann {
    template <typename T>
    static bool is_obj_valid(std::shared_ptr<T> ptr) {
        return ptr != nullptr;
    }

    template <typename T>
    static bool is_obj_valid(T obj) {
        return true;
    }

    void from_json(const json & j, libsarif::PropertyBag & x);
    void to_json(json & j, const libsarif::PropertyBag & x);

    void from_json(const json & j, libsarif::Address & x);
    void to_json(json & j, const libsarif::Address & x);

    void from_json(const json & j, libsarif::MultiformatMessageString & x);
    void to_json(json & j, const libsarif::MultiformatMessageString & x);

    void from_json(const json & j, libsarif::ArtifactContent & x);
    void to_json(json & j, const libsarif::ArtifactContent & x);

    void from_json(const json & j, libsarif::Message & x);
    void to_json(json & j, const libsarif::Message & x);

    void from_json(const json & j, libsarif::ArtifactLocation & x);
    void to_json(json & j, const libsarif::ArtifactLocation & x);

    void from_json(const json & j, libsarif::Artifact & x);
    void to_json(json & j, const libsarif::Artifact & x);

    void from_json(const json & j, libsarif::ReportingConfiguration & x);
    void to_json(json & j, const libsarif::ReportingConfiguration & x);

    void from_json(const json & j, libsarif::ToolComponentReference & x);
    void to_json(json & j, const libsarif::ToolComponentReference & x);

    void from_json(const json & j, libsarif::ReportingDescriptorReference & x);
    void to_json(json & j, const libsarif::ReportingDescriptorReference & x);

    void from_json(const json & j, libsarif::ConfigurationOverride & x);
    void to_json(json & j, const libsarif::ConfigurationOverride & x);

    void from_json(const json & j, libsarif::Region & x);
    void to_json(json & j, const libsarif::Region & x);

    void from_json(const json & j, libsarif::LogicalLocation & x);
    void to_json(json & j, const libsarif::LogicalLocation & x);

    void from_json(const json & j, libsarif::PhysicalLocation & x);
    void to_json(json & j, const libsarif::PhysicalLocation & x);

    void from_json(const json & j, libsarif::LocationRelationship & x);
    void to_json(json & j, const libsarif::LocationRelationship & x);

    void from_json(const json & j, libsarif::Location & x);
    void to_json(json & j, const libsarif::Location & x);

    void from_json(const json & j, libsarif::StackFrame & x);
    void to_json(json & j, const libsarif::StackFrame & x);

    void from_json(const json & j, libsarif::Stack & x);
    void to_json(json & j, const libsarif::Stack & x);

    void from_json(const json & j, libsarif::Exception & x);
    void to_json(json & j, const libsarif::Exception & x);

    void from_json(const json & j, libsarif::Notification & x);
    void to_json(json & j, const libsarif::Notification & x);

    void from_json(const json & j, libsarif::Invocation & x);
    void to_json(json & j, const libsarif::Invocation & x);

    void from_json(const json & j, libsarif::ReportingDescriptorRelationship & x);
    void to_json(json & j, const libsarif::ReportingDescriptorRelationship & x);

    void from_json(const json & j, libsarif::ReportingDescriptor & x);
    void to_json(json & j, const libsarif::ReportingDescriptor & x);

    void from_json(const json & j, libsarif::TranslationMetadata & x);
    void to_json(json & j, const libsarif::TranslationMetadata & x);

    void from_json(const json & j, libsarif::ToolComponent & x);
    void to_json(json & j, const libsarif::ToolComponent & x);

    void from_json(const json & j, libsarif::Tool & x);
    void to_json(json & j, const libsarif::Tool & x);

    void from_json(const json & j, libsarif::Conversion & x);
    void to_json(json & j, const libsarif::Conversion & x);

    void from_json(const json & j, libsarif::Edge & x);
    void to_json(json & j, const libsarif::Edge & x);

    void from_json(const json & j, libsarif::Node & x);
    void to_json(json & j, const libsarif::Node & x);

    void from_json(const json & j, libsarif::Graph & x);
    void to_json(json & j, const libsarif::Graph & x);

    void from_json(const json & j, libsarif::Rectangle & x);
    void to_json(json & j, const libsarif::Rectangle & x);

    void from_json(const json & j, libsarif::Attachment & x);
    void to_json(json & j, const libsarif::Attachment & x);

    void from_json(const json & j, libsarif::WebRequest & x);
    void to_json(json & j, const libsarif::WebRequest & x);

    void from_json(const json & j, libsarif::WebResponse & x);
    void to_json(json & j, const libsarif::WebResponse & x);

    void from_json(const json & j, libsarif::ThreadFlowLocation & x);
    void to_json(json & j, const libsarif::ThreadFlowLocation & x);

    void from_json(const json & j, libsarif::ThreadFlow & x);
    void to_json(json & j, const libsarif::ThreadFlow & x);

    void from_json(const json & j, libsarif::CodeFlow & x);
    void to_json(json & j, const libsarif::CodeFlow & x);

    void from_json(const json & j, libsarif::Replacement & x);
    void to_json(json & j, const libsarif::Replacement & x);

    void from_json(const json & j, libsarif::ArtifactChange & x);
    void to_json(json & j, const libsarif::ArtifactChange & x);

    void from_json(const json & j, libsarif::Fix & x);
    void to_json(json & j, const libsarif::Fix & x);

    void from_json(const json & j, libsarif::EdgeTraversal & x);
    void to_json(json & j, const libsarif::EdgeTraversal & x);

    void from_json(const json & j, libsarif::GraphTraversal & x);
    void to_json(json & j, const libsarif::GraphTraversal & x);

    void from_json(const json & j, libsarif::ResultProvenance & x);
    void to_json(json & j, const libsarif::ResultProvenance & x);

    void from_json(const json & j, libsarif::Suppression & x);
    void to_json(json & j, const libsarif::Suppression & x);

    void from_json(const json & j, libsarif::Result & x);
    void to_json(json & j, const libsarif::Result & x);

    void from_json(const json & j, libsarif::ExternalProperties & x);
    void to_json(json & j, const libsarif::ExternalProperties & x);

    void from_json(const json & j, libsarif::RunAutomationDetails & x);
    void to_json(json & j, const libsarif::RunAutomationDetails & x);

    void from_json(const json & j, libsarif::ExternalPropertyFileReference & x);
    void to_json(json & j, const libsarif::ExternalPropertyFileReference & x);

    void from_json(const json & j, libsarif::ExternalPropertyFileReferences & x);
    void to_json(json & j, const libsarif::ExternalPropertyFileReferences & x);

    void from_json(const json & j, libsarif::SpecialLocations & x);
    void to_json(json & j, const libsarif::SpecialLocations & x);

    void from_json(const json & j, libsarif::VersionControlDetails & x);
    void to_json(json & j, const libsarif::VersionControlDetails & x);

    void from_json(const json & j, libsarif::Run & x);
    void to_json(json & j, const libsarif::Run & x);

    void from_json(const json & j, libsarif::TopLevel & x);
    void to_json(json & j, const libsarif::TopLevel & x);

    void from_json(const json & j, libsarif::Role & x);
    void to_json(json & j, const libsarif::Role & x);

    void from_json(const json & j, libsarif::Level & x);
    void to_json(json & j, const libsarif::Level & x);

    void from_json(const json & j, libsarif::Content & x);
    void to_json(json & j, const libsarif::Content & x);

    void from_json(const json & j, libsarif::BaselineState & x);
    void to_json(json & j, const libsarif::BaselineState & x);

    void from_json(const json & j, libsarif::Importance & x);
    void to_json(json & j, const libsarif::Importance & x);

    void from_json(const json & j, libsarif::ResultKind & x);
    void to_json(json & j, const libsarif::ResultKind & x);

    void from_json(const json & j, libsarif::SuppressionKind & x);
    void to_json(json & j, const libsarif::SuppressionKind & x);

    void from_json(const json & j, libsarif::State & x);
    void to_json(json & j, const libsarif::State & x);

    void from_json(const json & j, libsarif::Version & x);
    void to_json(json & j, const libsarif::Version & x);

    void from_json(const json & j, libsarif::ColumnKind & x);
    void to_json(json & j, const libsarif::ColumnKind & x);

    inline void from_json(const json & j, libsarif::PropertyBag& x) {
        x.set_tags(libsarif::get_optional<std::vector<std::string>>(j, "tags"));
    }

    inline void to_json(json & j, const libsarif::PropertyBag & x) {
        j = json::object();
        if (is_obj_valid(x.get_tags()))
            j["tags"] = x.get_tags();
    }

    inline void from_json(const json & j, libsarif::Address& x) {
        x.set_absolute_address(libsarif::get_optional<int64_t>(j, "absoluteAddress"));
        x.set_fully_qualified_name(libsarif::get_optional<std::string>(j, "fullyQualifiedName"));
        x.set_index(libsarif::get_optional<int64_t>(j, "index"));
        x.set_kind(libsarif::get_optional<std::string>(j, "kind"));
        x.set_length(libsarif::get_optional<int64_t>(j, "length"));
        x.set_name(libsarif::get_optional<std::string>(j, "name"));
        x.set_offset_from_parent(libsarif::get_optional<int64_t>(j, "offsetFromParent"));
        x.set_parent_index(libsarif::get_optional<int64_t>(j, "parentIndex"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_relative_address(libsarif::get_optional<int64_t>(j, "relativeAddress"));
    }

    inline void to_json(json & j, const libsarif::Address & x) {
        j = json::object();
        if (is_obj_valid(x.get_absolute_address()))
            j["absoluteAddress"] = x.get_absolute_address();
        if (is_obj_valid(x.get_fully_qualified_name()))
            j["fullyQualifiedName"] = x.get_fully_qualified_name();
        if (is_obj_valid(x.get_index()))
            j["index"] = x.get_index();
        if (is_obj_valid(x.get_kind()))
            j["kind"] = x.get_kind();
        if (is_obj_valid(x.get_length()))
            j["length"] = x.get_length();
        if (is_obj_valid(x.get_name()))
            j["name"] = x.get_name();
        if (is_obj_valid(x.get_offset_from_parent()))
            j["offsetFromParent"] = x.get_offset_from_parent();
        if (is_obj_valid(x.get_parent_index()))
            j["parentIndex"] = x.get_parent_index();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_relative_address()))
            j["relativeAddress"] = x.get_relative_address();
    }

    inline void from_json(const json & j, libsarif::MultiformatMessageString& x) {
        x.set_markdown(libsarif::get_optional<std::string>(j, "markdown"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_text(j.at("text").get<std::string>());
    }

    inline void to_json(json & j, const libsarif::MultiformatMessageString & x) {
        j = json::object();
        if (is_obj_valid(x.get_markdown()))
            j["markdown"] = x.get_markdown();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_text()))
            j["text"] = x.get_text();
    }

    inline void from_json(const json & j, libsarif::ArtifactContent& x) {
        x.set_binary(libsarif::get_optional<std::string>(j, "binary"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_rendered(libsarif::get_optional<libsarif::MultiformatMessageString>(j, "rendered"));
        x.set_text(libsarif::get_optional<std::string>(j, "text"));
    }

    inline void to_json(json & j, const libsarif::ArtifactContent & x) {
        j = json::object();
        if (is_obj_valid(x.get_binary()))
            j["binary"] = x.get_binary();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_rendered()))
            j["rendered"] = x.get_rendered();
        if (is_obj_valid(x.get_text()))
            j["text"] = x.get_text();
    }

    inline void from_json(const json & j, libsarif::Message& x) {
        x.set_arguments(libsarif::get_optional<std::vector<std::string>>(j, "arguments"));
        x.set_id(libsarif::get_optional<std::string>(j, "id"));
        x.set_markdown(libsarif::get_optional<std::string>(j, "markdown"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_text(libsarif::get_optional<std::string>(j, "text"));
    }

    inline void to_json(json & j, const libsarif::Message & x) {
        j = json::object();
        if (is_obj_valid(x.get_arguments()))
            j["arguments"] = x.get_arguments();
        if (is_obj_valid(x.get_id()))
            j["id"] = x.get_id();
        if (is_obj_valid(x.get_markdown()))
            j["markdown"] = x.get_markdown();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_text()))
            j["text"] = x.get_text();
    }

    inline void from_json(const json & j, libsarif::ArtifactLocation& x) {
        x.set_description(libsarif::get_optional<libsarif::Message>(j, "description"));
        x.set_index(libsarif::get_optional<int64_t>(j, "index"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_uri(libsarif::get_optional<std::string>(j, "uri"));
        x.set_uri_base_id(libsarif::get_optional<std::string>(j, "uriBaseId"));
    }

    inline void to_json(json & j, const libsarif::ArtifactLocation & x) {
        j = json::object();
        if (is_obj_valid(x.get_description()))
            j["description"] = x.get_description();
        if (is_obj_valid(x.get_index()))
            j["index"] = x.get_index();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_uri()))
            j["uri"] = x.get_uri();
        if (is_obj_valid(x.get_uri_base_id()))
            j["uriBaseId"] = x.get_uri_base_id();
    }

    inline void from_json(const json & j, libsarif::Artifact& x) {
        x.set_contents(libsarif::get_optional<libsarif::ArtifactContent>(j, "contents"));
        x.set_description(libsarif::get_optional<libsarif::Message>(j, "description"));
        x.set_encoding(libsarif::get_optional<std::string>(j, "encoding"));
        x.set_hashes(libsarif::get_optional<std::map<std::string, std::string>>(j, "hashes"));
        x.set_last_modified_time_utc(libsarif::get_optional<std::string>(j, "lastModifiedTimeUtc"));
        x.set_length(libsarif::get_optional<int64_t>(j, "length"));
        x.set_location(libsarif::get_optional<libsarif::ArtifactLocation>(j, "location"));
        x.set_mime_type(libsarif::get_optional<std::string>(j, "mimeType"));
        x.set_offset(libsarif::get_optional<int64_t>(j, "offset"));
        x.set_parent_index(libsarif::get_optional<int64_t>(j, "parentIndex"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_roles(libsarif::get_optional<std::vector<libsarif::Role>>(j, "roles"));
        x.set_source_language(libsarif::get_optional<std::string>(j, "sourceLanguage"));
    }

    inline void to_json(json & j, const libsarif::Artifact & x) {
        j = json::object();
        if (is_obj_valid(x.get_contents()))
            j["contents"] = x.get_contents();
        if (is_obj_valid(x.get_description()))
            j["description"] = x.get_description();
        if (is_obj_valid(x.get_encoding()))
            j["encoding"] = x.get_encoding();
        if (is_obj_valid(x.get_hashes()))
            j["hashes"] = x.get_hashes();
        if (is_obj_valid(x.get_last_modified_time_utc()))
            j["lastModifiedTimeUtc"] = x.get_last_modified_time_utc();
        if (is_obj_valid(x.get_length()))
            j["length"] = x.get_length();
        if (is_obj_valid(x.get_location()))
            j["location"] = x.get_location();
        if (is_obj_valid(x.get_mime_type()))
            j["mimeType"] = x.get_mime_type();
        if (is_obj_valid(x.get_offset()))
            j["offset"] = x.get_offset();
        if (is_obj_valid(x.get_parent_index()))
            j["parentIndex"] = x.get_parent_index();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_roles()))
            j["roles"] = x.get_roles();
        if (is_obj_valid(x.get_source_language()))
            j["sourceLanguage"] = x.get_source_language();
    }

    inline void from_json(const json & j, libsarif::ReportingConfiguration& x) {
        x.set_enabled(libsarif::get_optional<bool>(j, "enabled"));
        x.set_level(libsarif::get_optional<libsarif::Level>(j, "level"));
        x.set_parameters(libsarif::get_optional<libsarif::PropertyBag>(j, "parameters"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_rank(libsarif::get_optional<double>(j, "rank"));
    }

    inline void to_json(json & j, const libsarif::ReportingConfiguration & x) {
        j = json::object();
        if (is_obj_valid(x.get_enabled()))
            j["enabled"] = x.get_enabled();
        if (is_obj_valid(x.get_level()))
            j["level"] = x.get_level();
        if (is_obj_valid(x.get_parameters()))
            j["parameters"] = x.get_parameters();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_rank()))
            j["rank"] = x.get_rank();
    }

    inline void from_json(const json & j, libsarif::ToolComponentReference& x) {
        x.set_guid(libsarif::get_optional<std::string>(j, "guid"));
        x.set_index(libsarif::get_optional<int64_t>(j, "index"));
        x.set_name(libsarif::get_optional<std::string>(j, "name"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::ToolComponentReference & x) {
        j = json::object();
        if (is_obj_valid(x.get_guid()))
            j["guid"] = x.get_guid();
        if (is_obj_valid(x.get_index()))
            j["index"] = x.get_index();
        if (is_obj_valid(x.get_name()))
            j["name"] = x.get_name();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ReportingDescriptorReference& x) {
        x.set_guid(libsarif::get_optional<std::string>(j, "guid"));
        x.set_id(libsarif::get_optional<std::string>(j, "id"));
        x.set_index(libsarif::get_optional<int64_t>(j, "index"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_tool_component(libsarif::get_optional<libsarif::ToolComponentReference>(j, "toolComponent"));
    }

    inline void to_json(json & j, const libsarif::ReportingDescriptorReference & x) {
        j = json::object();
        if (is_obj_valid(x.get_guid()))
            j["guid"] = x.get_guid();
        if (is_obj_valid(x.get_id()))
            j["id"] = x.get_id();
        if (is_obj_valid(x.get_index()))
            j["index"] = x.get_index();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_tool_component()))
            j["toolComponent"] = x.get_tool_component();
    }

    inline void from_json(const json & j, libsarif::ConfigurationOverride& x) {
        x.set_configuration(j.at("configuration").get<libsarif::ReportingConfiguration>());
        x.set_descriptor(j.at("descriptor").get<libsarif::ReportingDescriptorReference>());
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::ConfigurationOverride & x) {
        j = json::object();
        if (is_obj_valid(x.get_configuration()))
            j["configuration"] = x.get_configuration();
        if (is_obj_valid(x.get_descriptor()))
            j["descriptor"] = x.get_descriptor();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Region& x) {
        x.set_byte_length(libsarif::get_optional<int64_t>(j, "byteLength"));
        x.set_byte_offset(libsarif::get_optional<int64_t>(j, "byteOffset"));
        x.set_char_length(libsarif::get_optional<int64_t>(j, "charLength"));
        x.set_char_offset(libsarif::get_optional<int64_t>(j, "charOffset"));
        x.set_end_column(libsarif::get_optional<int64_t>(j, "endColumn"));
        x.set_end_line(libsarif::get_optional<int64_t>(j, "endLine"));
        x.set_message(libsarif::get_optional<libsarif::Message>(j, "message"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_snippet(libsarif::get_optional<libsarif::ArtifactContent>(j, "snippet"));
        x.set_source_language(libsarif::get_optional<std::string>(j, "sourceLanguage"));
        x.set_start_column(libsarif::get_optional<int64_t>(j, "startColumn"));
        x.set_start_line(libsarif::get_optional<int64_t>(j, "startLine"));
    }

    inline void to_json(json & j, const libsarif::Region & x) {
        j = json::object();
        if (is_obj_valid(x.get_byte_length()))
            j["byteLength"] = x.get_byte_length();
        if (is_obj_valid(x.get_byte_offset()))
            j["byteOffset"] = x.get_byte_offset();
        if (is_obj_valid(x.get_char_length()))
            j["charLength"] = x.get_char_length();
        if (is_obj_valid(x.get_char_offset()))
            j["charOffset"] = x.get_char_offset();
        if (is_obj_valid(x.get_end_column()))
            j["endColumn"] = x.get_end_column();
        if (is_obj_valid(x.get_end_line()))
            j["endLine"] = x.get_end_line();
        if (is_obj_valid(x.get_message()))
            j["message"] = x.get_message();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_snippet()))
            j["snippet"] = x.get_snippet();
        if (is_obj_valid(x.get_source_language()))
            j["sourceLanguage"] = x.get_source_language();
        if (is_obj_valid(x.get_start_column()))
            j["startColumn"] = x.get_start_column();
        if (is_obj_valid(x.get_start_line()))
            j["startLine"] = x.get_start_line();
    }

    inline void from_json(const json & j, libsarif::LogicalLocation& x) {
        x.set_decorated_name(libsarif::get_optional<std::string>(j, "decoratedName"));
        x.set_fully_qualified_name(libsarif::get_optional<std::string>(j, "fullyQualifiedName"));
        x.set_index(libsarif::get_optional<int64_t>(j, "index"));
        x.set_kind(libsarif::get_optional<std::string>(j, "kind"));
        x.set_name(libsarif::get_optional<std::string>(j, "name"));
        x.set_parent_index(libsarif::get_optional<int64_t>(j, "parentIndex"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::LogicalLocation & x) {
        j = json::object();
        if (is_obj_valid(x.get_decorated_name()))
            j["decoratedName"] = x.get_decorated_name();
        if (is_obj_valid(x.get_fully_qualified_name()))
            j["fullyQualifiedName"] = x.get_fully_qualified_name();
        if (is_obj_valid(x.get_index()))
            j["index"] = x.get_index();
        if (is_obj_valid(x.get_kind()))
            j["kind"] = x.get_kind();
        if (is_obj_valid(x.get_name()))
            j["name"] = x.get_name();
        if (is_obj_valid(x.get_parent_index()))
            j["parentIndex"] = x.get_parent_index();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::PhysicalLocation& x) {
        x.set_address(libsarif::get_optional<libsarif::Address>(j, "address"));
        x.set_artifact_location(libsarif::get_optional<libsarif::ArtifactLocation>(j, "artifactLocation"));
        x.set_context_region(libsarif::get_optional<libsarif::Region>(j, "contextRegion"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_region(libsarif::get_optional<libsarif::Region>(j, "region"));
    }

    inline void to_json(json & j, const libsarif::PhysicalLocation & x) {
        j = json::object();
        if (is_obj_valid(x.get_address()))
            j["address"] = x.get_address();
        if (is_obj_valid(x.get_artifact_location()))
            j["artifactLocation"] = x.get_artifact_location();
        if (is_obj_valid(x.get_context_region()))
            j["contextRegion"] = x.get_context_region();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_region()))
            j["region"] = x.get_region();
    }

    inline void from_json(const json & j, libsarif::LocationRelationship& x) {
        x.set_description(libsarif::get_optional<libsarif::Message>(j, "description"));
        x.set_kinds(libsarif::get_optional<std::vector<std::string>>(j, "kinds"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_target(j.at("target").get<int64_t>());
    }

    inline void to_json(json & j, const libsarif::LocationRelationship & x) {
        j = json::object();
        if (is_obj_valid(x.get_description()))
            j["description"] = x.get_description();
        if (is_obj_valid(x.get_kinds()))
            j["kinds"] = x.get_kinds();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_target()))
            j["target"] = x.get_target();
    }

    inline void from_json(const json & j, libsarif::Location& x) {
        x.set_annotations(libsarif::get_optional<std::vector<libsarif::Region>>(j, "annotations"));
        x.set_id(libsarif::get_optional<int64_t>(j, "id"));
        x.set_logical_locations(libsarif::get_optional<std::vector<libsarif::LogicalLocation>>(j, "logicalLocations"));
        x.set_message(libsarif::get_optional<libsarif::Message>(j, "message"));
        x.set_physical_location(libsarif::get_optional<libsarif::PhysicalLocation>(j, "physicalLocation"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_relationships(libsarif::get_optional<std::vector<libsarif::LocationRelationship>>(j, "relationships"));
    }

    inline void to_json(json & j, const libsarif::Location & x) {
        j = json::object();
        if (is_obj_valid(x.get_annotations()))
            j["annotations"] = x.get_annotations();
        if (is_obj_valid(x.get_id()))
            j["id"] = x.get_id();
        if (is_obj_valid(x.get_logical_locations()))
            j["logicalLocations"] = x.get_logical_locations();
        if (is_obj_valid(x.get_message()))
            j["message"] = x.get_message();
        if (is_obj_valid(x.get_physical_location()))
            j["physicalLocation"] = x.get_physical_location();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_relationships()))
            j["relationships"] = x.get_relationships();
    }

    inline void from_json(const json & j, libsarif::StackFrame& x) {
        x.set_location(libsarif::get_optional<libsarif::Location>(j, "location"));
        x.set_stack_frame_module(libsarif::get_optional<std::string>(j, "module"));
        x.set_parameters(libsarif::get_optional<std::vector<std::string>>(j, "parameters"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_thread_id(libsarif::get_optional<int64_t>(j, "threadId"));
    }

    inline void to_json(json & j, const libsarif::StackFrame & x) {
        j = json::object();
        if (is_obj_valid(x.get_location()))
            j["location"] = x.get_location();
        if (is_obj_valid(x.get_stack_frame_module()))
            j["module"] = x.get_stack_frame_module();
        if (is_obj_valid(x.get_parameters()))
            j["parameters"] = x.get_parameters();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_thread_id()))
            j["threadId"] = x.get_thread_id();
    }

    inline void from_json(const json & j, libsarif::Stack& x) {
        x.set_frames(j.at("frames").get<std::vector<libsarif::StackFrame>>());
        x.set_message(libsarif::get_optional<libsarif::Message>(j, "message"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::Stack & x) {
        j = json::object();
        if (is_obj_valid(x.get_frames()))
            j["frames"] = x.get_frames();
        if (is_obj_valid(x.get_message()))
            j["message"] = x.get_message();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Exception& x) {
        x.set_inner_exceptions(libsarif::get_optional<std::vector<libsarif::Exception>>(j, "innerExceptions"));
        x.set_kind(libsarif::get_optional<std::string>(j, "kind"));
        x.set_message(libsarif::get_optional<std::string>(j, "message"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_stack(libsarif::get_optional<libsarif::Stack>(j, "stack"));
    }

    inline void to_json(json & j, const libsarif::Exception & x) {
        j = json::object();
        if (is_obj_valid(x.get_inner_exceptions()))
            j["innerExceptions"] = x.get_inner_exceptions();
        if (is_obj_valid(x.get_kind()))
            j["kind"] = x.get_kind();
        if (is_obj_valid(x.get_message()))
            j["message"] = x.get_message();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_stack()))
            j["stack"] = x.get_stack();
    }

    inline void from_json(const json & j, libsarif::Notification& x) {
        x.set_associated_rule(libsarif::get_optional<libsarif::ReportingDescriptorReference>(j, "associatedRule"));
        x.set_descriptor(libsarif::get_optional<libsarif::ReportingDescriptorReference>(j, "descriptor"));
        x.set_exception(libsarif::get_optional<libsarif::Exception>(j, "exception"));
        x.set_level(libsarif::get_optional<libsarif::Level>(j, "level"));
        x.set_locations(libsarif::get_optional<std::vector<libsarif::Location>>(j, "locations"));
        x.set_message(j.at("message").get<libsarif::Message>());
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_thread_id(libsarif::get_optional<int64_t>(j, "threadId"));
        x.set_time_utc(libsarif::get_optional<std::string>(j, "timeUtc"));
    }

    inline void to_json(json & j, const libsarif::Notification & x) {
        j = json::object();
        if (is_obj_valid(x.get_associated_rule()))
            j["associatedRule"] = x.get_associated_rule();
        if (is_obj_valid(x.get_descriptor()))
            j["descriptor"] = x.get_descriptor();
        if (is_obj_valid(x.get_exception()))
            j["exception"] = x.get_exception();
        if (is_obj_valid(x.get_level()))
            j["level"] = x.get_level();
        if (is_obj_valid(x.get_locations()))
            j["locations"] = x.get_locations();
        if (is_obj_valid(x.get_message()))
            j["message"] = x.get_message();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_thread_id()))
            j["threadId"] = x.get_thread_id();
        if (is_obj_valid(x.get_time_utc()))
            j["timeUtc"] = x.get_time_utc();
    }

    inline void from_json(const json & j, libsarif::Invocation& x) {
        x.set_account(libsarif::get_optional<std::string>(j, "account"));
        x.set_arguments(libsarif::get_optional<std::vector<std::string>>(j, "arguments"));
        x.set_command_line(libsarif::get_optional<std::string>(j, "commandLine"));
        x.set_end_time_utc(libsarif::get_optional<std::string>(j, "endTimeUtc"));
        x.set_environment_variables(libsarif::get_optional<std::map<std::string, std::string>>(j, "environmentVariables"));
        x.set_executable_location(libsarif::get_optional<libsarif::ArtifactLocation>(j, "executableLocation"));
        x.set_execution_successful(j.at("executionSuccessful").get<bool>());
        x.set_exit_code(libsarif::get_optional<int64_t>(j, "exitCode"));
        x.set_exit_code_description(libsarif::get_optional<std::string>(j, "exitCodeDescription"));
        x.set_exit_signal_name(libsarif::get_optional<std::string>(j, "exitSignalName"));
        x.set_exit_signal_number(libsarif::get_optional<int64_t>(j, "exitSignalNumber"));
        x.set_machine(libsarif::get_optional<std::string>(j, "machine"));
        x.set_notification_configuration_overrides(libsarif::get_optional<std::vector<libsarif::ConfigurationOverride>>(j, "notificationConfigurationOverrides"));
        x.set_process_id(libsarif::get_optional<int64_t>(j, "processId"));
        x.set_process_start_failure_message(libsarif::get_optional<std::string>(j, "processStartFailureMessage"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_response_files(libsarif::get_optional<std::vector<libsarif::ArtifactLocation>>(j, "responseFiles"));
        x.set_rule_configuration_overrides(libsarif::get_optional<std::vector<libsarif::ConfigurationOverride>>(j, "ruleConfigurationOverrides"));
        x.set_start_time_utc(libsarif::get_optional<std::string>(j, "startTimeUtc"));
        x.set_stderr(libsarif::get_optional<libsarif::ArtifactLocation>(j, "stderr"));
        x.set_stdin(libsarif::get_optional<libsarif::ArtifactLocation>(j, "stdin"));
        x.set_stdout(libsarif::get_optional<libsarif::ArtifactLocation>(j, "stdout"));
        x.set_stdout_stderr(libsarif::get_optional<libsarif::ArtifactLocation>(j, "stdoutStderr"));
        x.set_tool_configuration_notifications(libsarif::get_optional<std::vector<libsarif::Notification>>(j, "toolConfigurationNotifications"));
        x.set_tool_execution_notifications(libsarif::get_optional<std::vector<libsarif::Notification>>(j, "toolExecutionNotifications"));
        x.set_working_directory(libsarif::get_optional<libsarif::ArtifactLocation>(j, "workingDirectory"));
    }

    inline void to_json(json & j, const libsarif::Invocation & x) {
        j = json::object();
        if (is_obj_valid(x.get_account()))
            j["account"] = x.get_account();
        if (is_obj_valid(x.get_arguments()))
            j["arguments"] = x.get_arguments();
        if (is_obj_valid(x.get_command_line()))
            j["commandLine"] = x.get_command_line();
        if (is_obj_valid(x.get_end_time_utc()))
            j["endTimeUtc"] = x.get_end_time_utc();
        if (is_obj_valid(x.get_environment_variables()))
            j["environmentVariables"] = x.get_environment_variables();
        if (is_obj_valid(x.get_executable_location()))
            j["executableLocation"] = x.get_executable_location();
        if (is_obj_valid(x.get_execution_successful()))
            j["executionSuccessful"] = x.get_execution_successful();
        if (is_obj_valid(x.get_exit_code()))
            j["exitCode"] = x.get_exit_code();
        if (is_obj_valid(x.get_exit_code_description()))
            j["exitCodeDescription"] = x.get_exit_code_description();
        if (is_obj_valid(x.get_exit_signal_name()))
            j["exitSignalName"] = x.get_exit_signal_name();
        if (is_obj_valid(x.get_exit_signal_number()))
            j["exitSignalNumber"] = x.get_exit_signal_number();
        if (is_obj_valid(x.get_machine()))
            j["machine"] = x.get_machine();
        if (is_obj_valid(x.get_notification_configuration_overrides()))
            j["notificationConfigurationOverrides"] = x.get_notification_configuration_overrides();
        if (is_obj_valid(x.get_process_id()))
            j["processId"] = x.get_process_id();
        if (is_obj_valid(x.get_process_start_failure_message()))
            j["processStartFailureMessage"] = x.get_process_start_failure_message();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_response_files()))
            j["responseFiles"] = x.get_response_files();
        if (is_obj_valid(x.get_rule_configuration_overrides()))
            j["ruleConfigurationOverrides"] = x.get_rule_configuration_overrides();
        if (is_obj_valid(x.get_start_time_utc()))
            j["startTimeUtc"] = x.get_start_time_utc();
        if (is_obj_valid(x.get_stderr()))
            j["stderr"] = x.get_stderr();
        if (is_obj_valid(x.get_stdin()))
            j["stdin"] = x.get_stdin();
        if (is_obj_valid(x.get_stdout()))
            j["stdout"] = x.get_stdout();
        if (is_obj_valid(x.get_stdout_stderr()))
            j["stdoutStderr"] = x.get_stdout_stderr();
        if (is_obj_valid(x.get_tool_configuration_notifications()))
            j["toolConfigurationNotifications"] = x.get_tool_configuration_notifications();
        if (is_obj_valid(x.get_tool_execution_notifications()))
            j["toolExecutionNotifications"] = x.get_tool_execution_notifications();
        if (is_obj_valid(x.get_working_directory()))
            j["workingDirectory"] = x.get_working_directory();
    }

    inline void from_json(const json & j, libsarif::ReportingDescriptorRelationship& x) {
        x.set_description(libsarif::get_optional<libsarif::Message>(j, "description"));
        x.set_kinds(libsarif::get_optional<std::vector<std::string>>(j, "kinds"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_target(j.at("target").get<libsarif::ReportingDescriptorReference>());
    }

    inline void to_json(json & j, const libsarif::ReportingDescriptorRelationship & x) {
        j = json::object();
        if (is_obj_valid(x.get_description()))
            j["description"] = x.get_description();
        if (is_obj_valid(x.get_kinds()))
            j["kinds"] = x.get_kinds();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_target()))
            j["target"] = x.get_target();
    }

    inline void from_json(const json & j, libsarif::ReportingDescriptor& x) {
        x.set_default_configuration(libsarif::get_optional<libsarif::ReportingConfiguration>(j, "defaultConfiguration"));
        x.set_deprecated_guids(libsarif::get_optional<std::vector<std::string>>(j, "deprecatedGuids"));
        x.set_deprecated_ids(libsarif::get_optional<std::vector<std::string>>(j, "deprecatedIds"));
        x.set_deprecated_names(libsarif::get_optional<std::vector<std::string>>(j, "deprecatedNames"));
        x.set_full_description(libsarif::get_optional<libsarif::MultiformatMessageString>(j, "fullDescription"));
        x.set_guid(libsarif::get_optional<std::string>(j, "guid"));
        x.set_help(libsarif::get_optional<libsarif::MultiformatMessageString>(j, "help"));
        x.set_help_uri(libsarif::get_optional<std::string>(j, "helpUri"));
        x.set_id(j.at("id").get<std::string>());
        x.set_message_strings(libsarif::get_optional<std::map<std::string, libsarif::MultiformatMessageString>>(j, "messageStrings"));
        x.set_name(libsarif::get_optional<std::string>(j, "name"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_relationships(libsarif::get_optional<std::vector<libsarif::ReportingDescriptorRelationship>>(j, "relationships"));
        x.set_short_description(libsarif::get_optional<libsarif::MultiformatMessageString>(j, "shortDescription"));
    }

    inline void to_json(json & j, const libsarif::ReportingDescriptor & x) {
        j = json::object();
        if (is_obj_valid(x.get_default_configuration()))
            j["defaultConfiguration"] = x.get_default_configuration();
        if (is_obj_valid(x.get_deprecated_guids()))
            j["deprecatedGuids"] = x.get_deprecated_guids();
        if (is_obj_valid(x.get_deprecated_ids()))
            j["deprecatedIds"] = x.get_deprecated_ids();
        if (is_obj_valid(x.get_deprecated_names()))
            j["deprecatedNames"] = x.get_deprecated_names();
        if (is_obj_valid(x.get_full_description()))
            j["fullDescription"] = x.get_full_description();
        if (is_obj_valid(x.get_guid()))
            j["guid"] = x.get_guid();
        if (is_obj_valid(x.get_help()))
            j["help"] = x.get_help();
        if (is_obj_valid(x.get_help_uri()))
            j["helpUri"] = x.get_help_uri();
        if (is_obj_valid(x.get_id()))
            j["id"] = x.get_id();
        if (is_obj_valid(x.get_message_strings()))
            j["messageStrings"] = x.get_message_strings();
        if (is_obj_valid(x.get_name()))
            j["name"] = x.get_name();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_relationships()))
            j["relationships"] = x.get_relationships();
        if (is_obj_valid(x.get_short_description()))
            j["shortDescription"] = x.get_short_description();
    }

    inline void from_json(const json & j, libsarif::TranslationMetadata& x) {
        x.set_download_uri(libsarif::get_optional<std::string>(j, "downloadUri"));
        x.set_full_description(libsarif::get_optional<libsarif::MultiformatMessageString>(j, "fullDescription"));
        x.set_full_name(libsarif::get_optional<std::string>(j, "fullName"));
        x.set_information_uri(libsarif::get_optional<std::string>(j, "informationUri"));
        x.set_name(j.at("name").get<std::string>());
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_short_description(libsarif::get_optional<libsarif::MultiformatMessageString>(j, "shortDescription"));
    }

    inline void to_json(json & j, const libsarif::TranslationMetadata & x) {
        j = json::object();
        if (is_obj_valid(x.get_download_uri()))
            j["downloadUri"] = x.get_download_uri();
        if (is_obj_valid(x.get_full_description()))
            j["fullDescription"] = x.get_full_description();
        if (is_obj_valid(x.get_full_name()))
            j["fullName"] = x.get_full_name();
        if (is_obj_valid(x.get_information_uri()))
            j["informationUri"] = x.get_information_uri();
        if (is_obj_valid(x.get_name()))
            j["name"] = x.get_name();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_short_description()))
            j["shortDescription"] = x.get_short_description();
    }

    inline void from_json(const json & j, libsarif::ToolComponent& x) {
        x.set_associated_component(libsarif::get_optional<libsarif::ToolComponentReference>(j, "associatedComponent"));
        x.set_contents(libsarif::get_optional<std::vector<libsarif::Content>>(j, "contents"));
        x.set_dotted_quad_file_version(libsarif::get_optional<std::string>(j, "dottedQuadFileVersion"));
        x.set_download_uri(libsarif::get_optional<std::string>(j, "downloadUri"));
        x.set_full_description(libsarif::get_optional<libsarif::MultiformatMessageString>(j, "fullDescription"));
        x.set_full_name(libsarif::get_optional<std::string>(j, "fullName"));
        x.set_global_message_strings(libsarif::get_optional<std::map<std::string, libsarif::MultiformatMessageString>>(j, "globalMessageStrings"));
        x.set_guid(libsarif::get_optional<std::string>(j, "guid"));
        x.set_information_uri(libsarif::get_optional<std::string>(j, "informationUri"));
        x.set_is_comprehensive(libsarif::get_optional<bool>(j, "isComprehensive"));
        x.set_language(libsarif::get_optional<std::string>(j, "language"));
        x.set_localized_data_semantic_version(libsarif::get_optional<std::string>(j, "localizedDataSemanticVersion"));
        x.set_locations(libsarif::get_optional<std::vector<libsarif::ArtifactLocation>>(j, "locations"));
        x.set_minimum_required_localized_data_semantic_version(libsarif::get_optional<std::string>(j, "minimumRequiredLocalizedDataSemanticVersion"));
        x.set_name(j.at("name").get<std::string>());
        x.set_notifications(libsarif::get_optional<std::vector<libsarif::ReportingDescriptor>>(j, "notifications"));
        x.set_organization(libsarif::get_optional<std::string>(j, "organization"));
        x.set_product(libsarif::get_optional<std::string>(j, "product"));
        x.set_product_suite(libsarif::get_optional<std::string>(j, "productSuite"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_release_date_utc(libsarif::get_optional<std::string>(j, "releaseDateUtc"));
        x.set_rules(libsarif::get_optional<std::vector<libsarif::ReportingDescriptor>>(j, "rules"));
        x.set_semantic_version(libsarif::get_optional<std::string>(j, "semanticVersion"));
        x.set_short_description(libsarif::get_optional<libsarif::MultiformatMessageString>(j, "shortDescription"));
        x.set_supported_taxonomies(libsarif::get_optional<std::vector<libsarif::ToolComponentReference>>(j, "supportedTaxonomies"));
        x.set_taxa(libsarif::get_optional<std::vector<libsarif::ReportingDescriptor>>(j, "taxa"));
        x.set_translation_metadata(libsarif::get_optional<libsarif::TranslationMetadata>(j, "translationMetadata"));
        x.set_version(libsarif::get_optional<std::string>(j, "version"));
    }

    inline void to_json(json & j, const libsarif::ToolComponent & x) {
        j = json::object();
        if (is_obj_valid(x.get_associated_component()))
            j["associatedComponent"] = x.get_associated_component();
        if (is_obj_valid(x.get_contents()))
            j["contents"] = x.get_contents();
        if (is_obj_valid(x.get_dotted_quad_file_version()))
            j["dottedQuadFileVersion"] = x.get_dotted_quad_file_version();
        if (is_obj_valid(x.get_download_uri()))
            j["downloadUri"] = x.get_download_uri();
        if (is_obj_valid(x.get_full_description()))
            j["fullDescription"] = x.get_full_description();
        if (is_obj_valid(x.get_full_name()))
            j["fullName"] = x.get_full_name();
        if (is_obj_valid(x.get_global_message_strings()))
            j["globalMessageStrings"] = x.get_global_message_strings();
        if (is_obj_valid(x.get_guid()))
            j["guid"] = x.get_guid();
        if (is_obj_valid(x.get_information_uri()))
            j["informationUri"] = x.get_information_uri();
        if (is_obj_valid(x.get_is_comprehensive()))
            j["isComprehensive"] = x.get_is_comprehensive();
        if (is_obj_valid(x.get_language()))
            j["language"] = x.get_language();
        if (is_obj_valid(x.get_localized_data_semantic_version()))
            j["localizedDataSemanticVersion"] = x.get_localized_data_semantic_version();
        if (is_obj_valid(x.get_locations()))
            j["locations"] = x.get_locations();
        if (is_obj_valid(x.get_minimum_required_localized_data_semantic_version()))
            j["minimumRequiredLocalizedDataSemanticVersion"] = x.get_minimum_required_localized_data_semantic_version();
        if (is_obj_valid(x.get_name()))
            j["name"] = x.get_name();
        if (is_obj_valid(x.get_notifications()))
            j["notifications"] = x.get_notifications();
        if (is_obj_valid(x.get_organization()))
            j["organization"] = x.get_organization();
        if (is_obj_valid(x.get_product()))
            j["product"] = x.get_product();
        if (is_obj_valid(x.get_product_suite()))
            j["productSuite"] = x.get_product_suite();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_release_date_utc()))
            j["releaseDateUtc"] = x.get_release_date_utc();
        if (is_obj_valid(x.get_rules()))
            j["rules"] = x.get_rules();
        if (is_obj_valid(x.get_semantic_version()))
            j["semanticVersion"] = x.get_semantic_version();
        if (is_obj_valid(x.get_short_description()))
            j["shortDescription"] = x.get_short_description();
        if (is_obj_valid(x.get_supported_taxonomies()))
            j["supportedTaxonomies"] = x.get_supported_taxonomies();
        if (is_obj_valid(x.get_taxa()))
            j["taxa"] = x.get_taxa();
        if (is_obj_valid(x.get_translation_metadata()))
            j["translationMetadata"] = x.get_translation_metadata();
        if (is_obj_valid(x.get_version()))
            j["version"] = x.get_version();
    }

    inline void from_json(const json & j, libsarif::Tool& x) {
        x.set_driver(j.at("driver").get<libsarif::ToolComponent>());
        x.set_extensions(libsarif::get_optional<std::vector<libsarif::ToolComponent>>(j, "extensions"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::Tool & x) {
        j = json::object();
        if (is_obj_valid(x.get_driver()))
            j["driver"] = x.get_driver();
        if (is_obj_valid(x.get_extensions()))
            j["extensions"] = x.get_extensions();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Conversion& x) {
        x.set_analysis_tool_log_files(libsarif::get_optional<std::vector<libsarif::ArtifactLocation>>(j, "analysisToolLogFiles"));
        x.set_invocation(libsarif::get_optional<libsarif::Invocation>(j, "invocation"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_tool(j.at("tool").get<libsarif::Tool>());
    }

    inline void to_json(json & j, const libsarif::Conversion & x) {
        j = json::object();
        if (is_obj_valid(x.get_analysis_tool_log_files()))
            j["analysisToolLogFiles"] = x.get_analysis_tool_log_files();
        if (is_obj_valid(x.get_invocation()))
            j["invocation"] = x.get_invocation();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_tool()))
            j["tool"] = x.get_tool();
    }

    inline void from_json(const json & j, libsarif::Edge& x) {
        x.set_id(j.at("id").get<std::string>());
        x.set_label(libsarif::get_optional<libsarif::Message>(j, "label"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_source_node_id(j.at("sourceNodeId").get<std::string>());
        x.set_target_node_id(j.at("targetNodeId").get<std::string>());
    }

    inline void to_json(json & j, const libsarif::Edge & x) {
        j = json::object();
        if (is_obj_valid(x.get_id()))
            j["id"] = x.get_id();
        if (is_obj_valid(x.get_label()))
            j["label"] = x.get_label();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_source_node_id()))
            j["sourceNodeId"] = x.get_source_node_id();
        if (is_obj_valid(x.get_target_node_id()))
            j["targetNodeId"] = x.get_target_node_id();
    }

    inline void from_json(const json & j, libsarif::Node& x) {
        x.set_children(libsarif::get_optional<std::vector<libsarif::Node>>(j, "children"));
        x.set_id(j.at("id").get<std::string>());
        x.set_label(libsarif::get_optional<libsarif::Message>(j, "label"));
        x.set_location(libsarif::get_optional<libsarif::Location>(j, "location"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::Node & x) {
        j = json::object();
        if (is_obj_valid(x.get_children()))
            j["children"] = x.get_children();
        if (is_obj_valid(x.get_id()))
            j["id"] = x.get_id();
        if (is_obj_valid(x.get_label()))
            j["label"] = x.get_label();
        if (is_obj_valid(x.get_location()))
            j["location"] = x.get_location();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Graph& x) {
        x.set_description(libsarif::get_optional<libsarif::Message>(j, "description"));
        x.set_edges(libsarif::get_optional<std::vector<libsarif::Edge>>(j, "edges"));
        x.set_nodes(libsarif::get_optional<std::vector<libsarif::Node>>(j, "nodes"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::Graph & x) {
        j = json::object();
        if (is_obj_valid(x.get_description()))
            j["description"] = x.get_description();
        if (is_obj_valid(x.get_edges()))
            j["edges"] = x.get_edges();
        if (is_obj_valid(x.get_nodes()))
            j["nodes"] = x.get_nodes();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Rectangle& x) {
        x.set_bottom(libsarif::get_optional<double>(j, "bottom"));
        x.set_left(libsarif::get_optional<double>(j, "left"));
        x.set_message(libsarif::get_optional<libsarif::Message>(j, "message"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_right(libsarif::get_optional<double>(j, "right"));
        x.set_top(libsarif::get_optional<double>(j, "top"));
    }

    inline void to_json(json & j, const libsarif::Rectangle & x) {
        j = json::object();
        if (is_obj_valid(x.get_bottom()))
            j["bottom"] = x.get_bottom();
        if (is_obj_valid(x.get_left()))
            j["left"] = x.get_left();
        if (is_obj_valid(x.get_message()))
            j["message"] = x.get_message();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_right()))
            j["right"] = x.get_right();
        if (is_obj_valid(x.get_top()))
            j["top"] = x.get_top();
    }

    inline void from_json(const json & j, libsarif::Attachment& x) {
        x.set_artifact_location(j.at("artifactLocation").get<libsarif::ArtifactLocation>());
        x.set_description(libsarif::get_optional<libsarif::Message>(j, "description"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_rectangles(libsarif::get_optional<std::vector<libsarif::Rectangle>>(j, "rectangles"));
        x.set_regions(libsarif::get_optional<std::vector<libsarif::Region>>(j, "regions"));
    }

    inline void to_json(json & j, const libsarif::Attachment & x) {
        j = json::object();
        if (is_obj_valid(x.get_artifact_location()))
            j["artifactLocation"] = x.get_artifact_location();
        if (is_obj_valid(x.get_description()))
            j["description"] = x.get_description();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_rectangles()))
            j["rectangles"] = x.get_rectangles();
        if (is_obj_valid(x.get_regions()))
            j["regions"] = x.get_regions();
    }

    inline void from_json(const json & j, libsarif::WebRequest& x) {
        x.set_body(libsarif::get_optional<libsarif::ArtifactContent>(j, "body"));
        x.set_headers(libsarif::get_optional<std::map<std::string, std::string>>(j, "headers"));
        x.set_index(libsarif::get_optional<int64_t>(j, "index"));
        x.set_method(libsarif::get_optional<std::string>(j, "method"));
        x.set_parameters(libsarif::get_optional<std::map<std::string, std::string>>(j, "parameters"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_protocol(libsarif::get_optional<std::string>(j, "protocol"));
        x.set_target(libsarif::get_optional<std::string>(j, "target"));
        x.set_version(libsarif::get_optional<std::string>(j, "version"));
    }

    inline void to_json(json & j, const libsarif::WebRequest & x) {
        j = json::object();
        if (is_obj_valid(x.get_body()))
            j["body"] = x.get_body();
        if (is_obj_valid(x.get_headers()))
            j["headers"] = x.get_headers();
        if (is_obj_valid(x.get_index()))
            j["index"] = x.get_index();
        if (is_obj_valid(x.get_method()))
            j["method"] = x.get_method();
        if (is_obj_valid(x.get_parameters()))
            j["parameters"] = x.get_parameters();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_protocol()))
            j["protocol"] = x.get_protocol();
        if (is_obj_valid(x.get_target()))
            j["target"] = x.get_target();
        if (is_obj_valid(x.get_version()))
            j["version"] = x.get_version();
    }

    inline void from_json(const json & j, libsarif::WebResponse& x) {
        x.set_body(libsarif::get_optional<libsarif::ArtifactContent>(j, "body"));
        x.set_headers(libsarif::get_optional<std::map<std::string, std::string>>(j, "headers"));
        x.set_index(libsarif::get_optional<int64_t>(j, "index"));
        x.set_no_response_received(libsarif::get_optional<bool>(j, "noResponseReceived"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_protocol(libsarif::get_optional<std::string>(j, "protocol"));
        x.set_reason_phrase(libsarif::get_optional<std::string>(j, "reasonPhrase"));
        x.set_status_code(libsarif::get_optional<int64_t>(j, "statusCode"));
        x.set_version(libsarif::get_optional<std::string>(j, "version"));
    }

    inline void to_json(json & j, const libsarif::WebResponse & x) {
        j = json::object();
        if (is_obj_valid(x.get_body()))
            j["body"] = x.get_body();
        if (is_obj_valid(x.get_headers()))
            j["headers"] = x.get_headers();
        if (is_obj_valid(x.get_index()))
            j["index"] = x.get_index();
        if (is_obj_valid(x.get_no_response_received()))
            j["noResponseReceived"] = x.get_no_response_received();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_protocol()))
            j["protocol"] = x.get_protocol();
        if (is_obj_valid(x.get_reason_phrase()))
            j["reasonPhrase"] = x.get_reason_phrase();
        if (is_obj_valid(x.get_status_code()))
            j["statusCode"] = x.get_status_code();
        if (is_obj_valid(x.get_version()))
            j["version"] = x.get_version();
    }

    inline void from_json(const json & j, libsarif::ThreadFlowLocation& x) {
        x.set_execution_order(libsarif::get_optional<int64_t>(j, "executionOrder"));
        x.set_execution_time_utc(libsarif::get_optional<std::string>(j, "executionTimeUtc"));
        x.set_importance(libsarif::get_optional<libsarif::Importance>(j, "importance"));
        x.set_index(libsarif::get_optional<int64_t>(j, "index"));
        x.set_kinds(libsarif::get_optional<std::vector<std::string>>(j, "kinds"));
        x.set_location(libsarif::get_optional<libsarif::Location>(j, "location"));
        x.set_thread_flow_location_module(libsarif::get_optional<std::string>(j, "module"));
        x.set_nesting_level(libsarif::get_optional<int64_t>(j, "nestingLevel"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_stack(libsarif::get_optional<libsarif::Stack>(j, "stack"));
        x.set_state(libsarif::get_optional<std::map<std::string, libsarif::MultiformatMessageString>>(j, "state"));
        x.set_taxa(libsarif::get_optional<std::vector<libsarif::ReportingDescriptorReference>>(j, "taxa"));
        x.set_web_request(libsarif::get_optional<libsarif::WebRequest>(j, "webRequest"));
        x.set_web_response(libsarif::get_optional<libsarif::WebResponse>(j, "webResponse"));
    }

    inline void to_json(json & j, const libsarif::ThreadFlowLocation & x) {
        j = json::object();
        if (is_obj_valid(x.get_execution_order()))
            j["executionOrder"] = x.get_execution_order();
        if (is_obj_valid(x.get_execution_time_utc()))
            j["executionTimeUtc"] = x.get_execution_time_utc();
        if (is_obj_valid(x.get_importance()))
            j["importance"] = x.get_importance();
        if (is_obj_valid(x.get_index()))
            j["index"] = x.get_index();
        if (is_obj_valid(x.get_kinds()))
            j["kinds"] = x.get_kinds();
        if (is_obj_valid(x.get_location()))
            j["location"] = x.get_location();
        if (is_obj_valid(x.get_thread_flow_location_module()))
            j["module"] = x.get_thread_flow_location_module();
        if (is_obj_valid(x.get_nesting_level()))
            j["nestingLevel"] = x.get_nesting_level();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_stack()))
            j["stack"] = x.get_stack();
        if (is_obj_valid(x.get_state()))
            j["state"] = x.get_state();
        if (is_obj_valid(x.get_taxa()))
            j["taxa"] = x.get_taxa();
        if (is_obj_valid(x.get_web_request()))
            j["webRequest"] = x.get_web_request();
        if (is_obj_valid(x.get_web_response()))
            j["webResponse"] = x.get_web_response();
    }

    inline void from_json(const json & j, libsarif::ThreadFlow& x) {
        x.set_id(libsarif::get_optional<std::string>(j, "id"));
        x.set_immutable_state(libsarif::get_optional<std::map<std::string, libsarif::MultiformatMessageString>>(j, "immutableState"));
        x.set_initial_state(libsarif::get_optional<std::map<std::string, libsarif::MultiformatMessageString>>(j, "initialState"));
        x.set_locations(j.at("locations").get<std::vector<libsarif::ThreadFlowLocation>>());
        x.set_message(libsarif::get_optional<libsarif::Message>(j, "message"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::ThreadFlow & x) {
        j = json::object();
        if (is_obj_valid(x.get_id()))
            j["id"] = x.get_id();
        if (is_obj_valid(x.get_immutable_state()))
            j["immutableState"] = x.get_immutable_state();
        if (is_obj_valid(x.get_initial_state()))
            j["initialState"] = x.get_initial_state();
        if (is_obj_valid(x.get_locations()))
            j["locations"] = x.get_locations();
        if (is_obj_valid(x.get_message()))
            j["message"] = x.get_message();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::CodeFlow& x) {
        x.set_message(libsarif::get_optional<libsarif::Message>(j, "message"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_thread_flows(j.at("threadFlows").get<std::vector<libsarif::ThreadFlow>>());
    }

    inline void to_json(json & j, const libsarif::CodeFlow & x) {
        j = json::object();
        if (is_obj_valid(x.get_message()))
            j["message"] = x.get_message();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_thread_flows()))
            j["threadFlows"] = x.get_thread_flows();
    }

    inline void from_json(const json & j, libsarif::Replacement& x) {
        x.set_deleted_region(j.at("deletedRegion").get<libsarif::Region>());
        x.set_inserted_content(libsarif::get_optional<libsarif::ArtifactContent>(j, "insertedContent"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::Replacement & x) {
        j = json::object();
        if (is_obj_valid(x.get_deleted_region()))
            j["deletedRegion"] = x.get_deleted_region();
        if (is_obj_valid(x.get_inserted_content()))
            j["insertedContent"] = x.get_inserted_content();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ArtifactChange& x) {
        x.set_artifact_location(j.at("artifactLocation").get<libsarif::ArtifactLocation>());
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_replacements(j.at("replacements").get<std::vector<libsarif::Replacement>>());
    }

    inline void to_json(json & j, const libsarif::ArtifactChange & x) {
        j = json::object();
        if (is_obj_valid(x.get_artifact_location()))
            j["artifactLocation"] = x.get_artifact_location();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_replacements()))
            j["replacements"] = x.get_replacements();
    }

    inline void from_json(const json & j, libsarif::Fix& x) {
        x.set_artifact_changes(j.at("artifactChanges").get<std::vector<libsarif::ArtifactChange>>());
        x.set_description(libsarif::get_optional<libsarif::Message>(j, "description"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::Fix & x) {
        j = json::object();
        if (is_obj_valid(x.get_artifact_changes()))
            j["artifactChanges"] = x.get_artifact_changes();
        if (is_obj_valid(x.get_description()))
            j["description"] = x.get_description();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::EdgeTraversal& x) {
        x.set_edge_id(j.at("edgeId").get<std::string>());
        x.set_final_state(libsarif::get_optional<std::map<std::string, libsarif::MultiformatMessageString>>(j, "finalState"));
        x.set_message(libsarif::get_optional<libsarif::Message>(j, "message"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_step_over_edge_count(libsarif::get_optional<int64_t>(j, "stepOverEdgeCount"));
    }

    inline void to_json(json & j, const libsarif::EdgeTraversal & x) {
        j = json::object();
        if (is_obj_valid(x.get_edge_id()))
            j["edgeId"] = x.get_edge_id();
        if (is_obj_valid(x.get_final_state()))
            j["finalState"] = x.get_final_state();
        if (is_obj_valid(x.get_message()))
            j["message"] = x.get_message();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_step_over_edge_count()))
            j["stepOverEdgeCount"] = x.get_step_over_edge_count();
    }

    inline void from_json(const json & j, libsarif::GraphTraversal& x) {
        x.set_description(libsarif::get_optional<libsarif::Message>(j, "description"));
        x.set_edge_traversals(libsarif::get_optional<std::vector<libsarif::EdgeTraversal>>(j, "edgeTraversals"));
        x.set_immutable_state(libsarif::get_optional<std::map<std::string, libsarif::MultiformatMessageString>>(j, "immutableState"));
        x.set_initial_state(libsarif::get_optional<std::map<std::string, libsarif::MultiformatMessageString>>(j, "initialState"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_result_graph_index(libsarif::get_optional<int64_t>(j, "resultGraphIndex"));
        x.set_run_graph_index(libsarif::get_optional<int64_t>(j, "runGraphIndex"));
    }

    inline void to_json(json & j, const libsarif::GraphTraversal & x) {
        j = json::object();
        if (is_obj_valid(x.get_description()))
            j["description"] = x.get_description();
        if (is_obj_valid(x.get_edge_traversals()))
            j["edgeTraversals"] = x.get_edge_traversals();
        if (is_obj_valid(x.get_immutable_state()))
            j["immutableState"] = x.get_immutable_state();
        if (is_obj_valid(x.get_initial_state()))
            j["initialState"] = x.get_initial_state();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_result_graph_index()))
            j["resultGraphIndex"] = x.get_result_graph_index();
        if (is_obj_valid(x.get_run_graph_index()))
            j["runGraphIndex"] = x.get_run_graph_index();
    }

    inline void from_json(const json & j, libsarif::ResultProvenance& x) {
        x.set_conversion_sources(libsarif::get_optional<std::vector<libsarif::PhysicalLocation>>(j, "conversionSources"));
        x.set_first_detection_run_guid(libsarif::get_optional<std::string>(j, "firstDetectionRunGuid"));
        x.set_first_detection_time_utc(libsarif::get_optional<std::string>(j, "firstDetectionTimeUtc"));
        x.set_invocation_index(libsarif::get_optional<int64_t>(j, "invocationIndex"));
        x.set_last_detection_run_guid(libsarif::get_optional<std::string>(j, "lastDetectionRunGuid"));
        x.set_last_detection_time_utc(libsarif::get_optional<std::string>(j, "lastDetectionTimeUtc"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::ResultProvenance & x) {
        j = json::object();
        if (is_obj_valid(x.get_conversion_sources()))
            j["conversionSources"] = x.get_conversion_sources();
        if (is_obj_valid(x.get_first_detection_run_guid()))
            j["firstDetectionRunGuid"] = x.get_first_detection_run_guid();
        if (is_obj_valid(x.get_first_detection_time_utc()))
            j["firstDetectionTimeUtc"] = x.get_first_detection_time_utc();
        if (is_obj_valid(x.get_invocation_index()))
            j["invocationIndex"] = x.get_invocation_index();
        if (is_obj_valid(x.get_last_detection_run_guid()))
            j["lastDetectionRunGuid"] = x.get_last_detection_run_guid();
        if (is_obj_valid(x.get_last_detection_time_utc()))
            j["lastDetectionTimeUtc"] = x.get_last_detection_time_utc();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::Suppression& x) {
        x.set_guid(libsarif::get_optional<std::string>(j, "guid"));
        x.set_justification(libsarif::get_optional<std::string>(j, "justification"));
        x.set_kind(j.at("kind").get<libsarif::SuppressionKind>());
        x.set_location(libsarif::get_optional<libsarif::Location>(j, "location"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_state(libsarif::get_optional<libsarif::State>(j, "state"));
    }

    inline void to_json(json & j, const libsarif::Suppression & x) {
        j = json::object();
        if (is_obj_valid(x.get_guid()))
            j["guid"] = x.get_guid();
        if (is_obj_valid(x.get_justification()))
            j["justification"] = x.get_justification();
        if (is_obj_valid(x.get_kind()))
            j["kind"] = x.get_kind();
        if (is_obj_valid(x.get_location()))
            j["location"] = x.get_location();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_state()))
            j["state"] = x.get_state();
    }

    inline void from_json(const json & j, libsarif::Result& x) {
        x.set_analysis_target(libsarif::get_optional<libsarif::ArtifactLocation>(j, "analysisTarget"));
        x.set_attachments(libsarif::get_optional<std::vector<libsarif::Attachment>>(j, "attachments"));
        x.set_baseline_state(libsarif::get_optional<libsarif::BaselineState>(j, "baselineState"));
        x.set_code_flows(libsarif::get_optional<std::vector<libsarif::CodeFlow>>(j, "codeFlows"));
        x.set_correlation_guid(libsarif::get_optional<std::string>(j, "correlationGuid"));
        x.set_fingerprints(libsarif::get_optional<std::map<std::string, std::string>>(j, "fingerprints"));
        x.set_fixes(libsarif::get_optional<std::vector<libsarif::Fix>>(j, "fixes"));
        x.set_graphs(libsarif::get_optional<std::vector<libsarif::Graph>>(j, "graphs"));
        x.set_graph_traversals(libsarif::get_optional<std::vector<libsarif::GraphTraversal>>(j, "graphTraversals"));
        x.set_guid(libsarif::get_optional<std::string>(j, "guid"));
        x.set_hosted_viewer_uri(libsarif::get_optional<std::string>(j, "hostedViewerUri"));
        x.set_kind(libsarif::get_optional<libsarif::ResultKind>(j, "kind"));
        x.set_level(libsarif::get_optional<libsarif::Level>(j, "level"));
        x.set_locations(libsarif::get_optional<std::vector<libsarif::Location>>(j, "locations"));
        x.set_message(j.at("message").get<libsarif::Message>());
        x.set_occurrence_count(libsarif::get_optional<int64_t>(j, "occurrenceCount"));
        x.set_partial_fingerprints(libsarif::get_optional<std::map<std::string, std::string>>(j, "partialFingerprints"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_provenance(libsarif::get_optional<libsarif::ResultProvenance>(j, "provenance"));
        x.set_rank(libsarif::get_optional<double>(j, "rank"));
        x.set_related_locations(libsarif::get_optional<std::vector<libsarif::Location>>(j, "relatedLocations"));
        x.set_rule(libsarif::get_optional<libsarif::ReportingDescriptorReference>(j, "rule"));
        x.set_rule_id(libsarif::get_optional<std::string>(j, "ruleId"));
        x.set_rule_index(libsarif::get_optional<int64_t>(j, "ruleIndex"));
        x.set_stacks(libsarif::get_optional<std::vector<libsarif::Stack>>(j, "stacks"));
        x.set_suppressions(libsarif::get_optional<std::vector<libsarif::Suppression>>(j, "suppressions"));
        x.set_taxa(libsarif::get_optional<std::vector<libsarif::ReportingDescriptorReference>>(j, "taxa"));
        x.set_web_request(libsarif::get_optional<libsarif::WebRequest>(j, "webRequest"));
        x.set_web_response(libsarif::get_optional<libsarif::WebResponse>(j, "webResponse"));
        x.set_work_item_uris(libsarif::get_optional<std::vector<std::string>>(j, "workItemUris"));
    }

    inline void to_json(json & j, const libsarif::Result & x) {
        j = json::object();
        if (is_obj_valid(x.get_analysis_target()))
            j["analysisTarget"] = x.get_analysis_target();
        if (is_obj_valid(x.get_attachments()))
            j["attachments"] = x.get_attachments();
        if (is_obj_valid(x.get_baseline_state()))
            j["baselineState"] = x.get_baseline_state();
        if (is_obj_valid(x.get_code_flows()))
            j["codeFlows"] = x.get_code_flows();
        if (is_obj_valid(x.get_correlation_guid()))
            j["correlationGuid"] = x.get_correlation_guid();
        if (is_obj_valid(x.get_fingerprints()))
            j["fingerprints"] = x.get_fingerprints();
        if (is_obj_valid(x.get_fixes()))
            j["fixes"] = x.get_fixes();
        if (is_obj_valid(x.get_graphs()))
            j["graphs"] = x.get_graphs();
        if (is_obj_valid(x.get_graph_traversals()))
            j["graphTraversals"] = x.get_graph_traversals();
        if (is_obj_valid(x.get_guid()))
            j["guid"] = x.get_guid();
        if (is_obj_valid(x.get_hosted_viewer_uri()))
            j["hostedViewerUri"] = x.get_hosted_viewer_uri();
        if (is_obj_valid(x.get_kind()))
            j["kind"] = x.get_kind();
        if (is_obj_valid(x.get_level()))
            j["level"] = x.get_level();
        if (is_obj_valid(x.get_locations()))
            j["locations"] = x.get_locations();
        if (is_obj_valid(x.get_message()))
            j["message"] = x.get_message();
        if (is_obj_valid(x.get_occurrence_count()))
            j["occurrenceCount"] = x.get_occurrence_count();
        if (is_obj_valid(x.get_partial_fingerprints()))
            j["partialFingerprints"] = x.get_partial_fingerprints();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_provenance()))
            j["provenance"] = x.get_provenance();
        if (is_obj_valid(x.get_rank()))
            j["rank"] = x.get_rank();
        if (is_obj_valid(x.get_related_locations()))
            j["relatedLocations"] = x.get_related_locations();
        if (is_obj_valid(x.get_rule()))
            j["rule"] = x.get_rule();
        if (is_obj_valid(x.get_rule_id()))
            j["ruleId"] = x.get_rule_id();
        if (is_obj_valid(x.get_rule_index()))
            j["ruleIndex"] = x.get_rule_index();
        if (is_obj_valid(x.get_stacks()))
            j["stacks"] = x.get_stacks();
        if (is_obj_valid(x.get_suppressions()))
            j["suppressions"] = x.get_suppressions();
        if (is_obj_valid(x.get_taxa()))
            j["taxa"] = x.get_taxa();
        if (is_obj_valid(x.get_web_request()))
            j["webRequest"] = x.get_web_request();
        if (is_obj_valid(x.get_web_response()))
            j["webResponse"] = x.get_web_response();
        if (is_obj_valid(x.get_work_item_uris()))
            j["workItemUris"] = x.get_work_item_uris();
    }

    inline void from_json(const json & j, libsarif::ExternalProperties& x) {
        x.set_addresses(libsarif::get_optional<std::vector<libsarif::Address>>(j, "addresses"));
        x.set_artifacts(libsarif::get_optional<std::vector<libsarif::Artifact>>(j, "artifacts"));
        x.set_conversion(libsarif::get_optional<libsarif::Conversion>(j, "conversion"));
        x.set_driver(libsarif::get_optional<libsarif::ToolComponent>(j, "driver"));
        x.set_extensions(libsarif::get_optional<std::vector<libsarif::ToolComponent>>(j, "extensions"));
        x.set_externalized_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "externalizedProperties"));
        x.set_graphs(libsarif::get_optional<std::vector<libsarif::Graph>>(j, "graphs"));
        x.set_guid(libsarif::get_optional<std::string>(j, "guid"));
        x.set_invocations(libsarif::get_optional<std::vector<libsarif::Invocation>>(j, "invocations"));
        x.set_logical_locations(libsarif::get_optional<std::vector<libsarif::LogicalLocation>>(j, "logicalLocations"));
        x.set_policies(libsarif::get_optional<std::vector<libsarif::ToolComponent>>(j, "policies"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_results(libsarif::get_optional<std::vector<libsarif::Result>>(j, "results"));
        x.set_run_guid(libsarif::get_optional<std::string>(j, "runGuid"));
        x.set_schema(libsarif::get_optional<std::string>(j, "schema"));
        x.set_taxonomies(libsarif::get_optional<std::vector<libsarif::ToolComponent>>(j, "taxonomies"));
        x.set_thread_flow_locations(libsarif::get_optional<std::vector<libsarif::ThreadFlowLocation>>(j, "threadFlowLocations"));
        x.set_translations(libsarif::get_optional<std::vector<libsarif::ToolComponent>>(j, "translations"));
        x.set_version(libsarif::get_optional<libsarif::Version>(j, "version"));
        x.set_web_requests(libsarif::get_optional<std::vector<libsarif::WebRequest>>(j, "webRequests"));
        x.set_web_responses(libsarif::get_optional<std::vector<libsarif::WebResponse>>(j, "webResponses"));
    }

    inline void to_json(json & j, const libsarif::ExternalProperties & x) {
        j = json::object();
        if (is_obj_valid(x.get_addresses()))
            j["addresses"] = x.get_addresses();
        if (is_obj_valid(x.get_artifacts()))
            j["artifacts"] = x.get_artifacts();
        if (is_obj_valid(x.get_conversion()))
            j["conversion"] = x.get_conversion();
        if (is_obj_valid(x.get_driver()))
            j["driver"] = x.get_driver();
        if (is_obj_valid(x.get_extensions()))
            j["extensions"] = x.get_extensions();
        if (is_obj_valid(x.get_externalized_properties()))
            j["externalizedProperties"] = x.get_externalized_properties();
        if (is_obj_valid(x.get_graphs()))
            j["graphs"] = x.get_graphs();
        if (is_obj_valid(x.get_guid()))
            j["guid"] = x.get_guid();
        if (is_obj_valid(x.get_invocations()))
            j["invocations"] = x.get_invocations();
        if (is_obj_valid(x.get_logical_locations()))
            j["logicalLocations"] = x.get_logical_locations();
        if (is_obj_valid(x.get_policies()))
            j["policies"] = x.get_policies();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_results()))
            j["results"] = x.get_results();
        if (is_obj_valid(x.get_run_guid()))
            j["runGuid"] = x.get_run_guid();
        if (is_obj_valid(x.get_schema()))
            j["schema"] = x.get_schema();
        if (is_obj_valid(x.get_taxonomies()))
            j["taxonomies"] = x.get_taxonomies();
        if (is_obj_valid(x.get_thread_flow_locations()))
            j["threadFlowLocations"] = x.get_thread_flow_locations();
        if (is_obj_valid(x.get_translations()))
            j["translations"] = x.get_translations();
        if (is_obj_valid(x.get_version()))
            j["version"] = x.get_version();
        if (is_obj_valid(x.get_web_requests()))
            j["webRequests"] = x.get_web_requests();
        if (is_obj_valid(x.get_web_responses()))
            j["webResponses"] = x.get_web_responses();
    }

    inline void from_json(const json & j, libsarif::RunAutomationDetails& x) {
        x.set_correlation_guid(libsarif::get_optional<std::string>(j, "correlationGuid"));
        x.set_description(libsarif::get_optional<libsarif::Message>(j, "description"));
        x.set_guid(libsarif::get_optional<std::string>(j, "guid"));
        x.set_id(libsarif::get_optional<std::string>(j, "id"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::RunAutomationDetails & x) {
        j = json::object();
        if (is_obj_valid(x.get_correlation_guid()))
            j["correlationGuid"] = x.get_correlation_guid();
        if (is_obj_valid(x.get_description()))
            j["description"] = x.get_description();
        if (is_obj_valid(x.get_guid()))
            j["guid"] = x.get_guid();
        if (is_obj_valid(x.get_id()))
            j["id"] = x.get_id();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ExternalPropertyFileReference& x) {
        x.set_guid(libsarif::get_optional<std::string>(j, "guid"));
        x.set_item_count(libsarif::get_optional<int64_t>(j, "itemCount"));
        x.set_location(libsarif::get_optional<libsarif::ArtifactLocation>(j, "location"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::ExternalPropertyFileReference & x) {
        j = json::object();
        if (is_obj_valid(x.get_guid()))
            j["guid"] = x.get_guid();
        if (is_obj_valid(x.get_item_count()))
            j["itemCount"] = x.get_item_count();
        if (is_obj_valid(x.get_location()))
            j["location"] = x.get_location();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::ExternalPropertyFileReferences& x) {
        x.set_addresses(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "addresses"));
        x.set_artifacts(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "artifacts"));
        x.set_conversion(libsarif::get_optional<libsarif::ExternalPropertyFileReference>(j, "conversion"));
        x.set_driver(libsarif::get_optional<libsarif::ExternalPropertyFileReference>(j, "driver"));
        x.set_extensions(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "extensions"));
        x.set_externalized_properties(libsarif::get_optional<libsarif::ExternalPropertyFileReference>(j, "externalizedProperties"));
        x.set_graphs(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "graphs"));
        x.set_invocations(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "invocations"));
        x.set_logical_locations(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "logicalLocations"));
        x.set_policies(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "policies"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_results(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "results"));
        x.set_taxonomies(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "taxonomies"));
        x.set_thread_flow_locations(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "threadFlowLocations"));
        x.set_translations(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "translations"));
        x.set_web_requests(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "webRequests"));
        x.set_web_responses(libsarif::get_optional<std::vector<libsarif::ExternalPropertyFileReference>>(j, "webResponses"));
    }

    inline void to_json(json & j, const libsarif::ExternalPropertyFileReferences & x) {
        j = json::object();
        if (is_obj_valid(x.get_addresses()))
            j["addresses"] = x.get_addresses();
        if (is_obj_valid(x.get_artifacts()))
            j["artifacts"] = x.get_artifacts();
        if (is_obj_valid(x.get_conversion()))
            j["conversion"] = x.get_conversion();
        if (is_obj_valid(x.get_driver()))
            j["driver"] = x.get_driver();
        if (is_obj_valid(x.get_extensions()))
            j["extensions"] = x.get_extensions();
        if (is_obj_valid(x.get_externalized_properties()))
            j["externalizedProperties"] = x.get_externalized_properties();
        if (is_obj_valid(x.get_graphs()))
            j["graphs"] = x.get_graphs();
        if (is_obj_valid(x.get_invocations()))
            j["invocations"] = x.get_invocations();
        if (is_obj_valid(x.get_logical_locations()))
            j["logicalLocations"] = x.get_logical_locations();
        if (is_obj_valid(x.get_policies()))
            j["policies"] = x.get_policies();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_results()))
            j["results"] = x.get_results();
        if (is_obj_valid(x.get_taxonomies()))
            j["taxonomies"] = x.get_taxonomies();
        if (is_obj_valid(x.get_thread_flow_locations()))
            j["threadFlowLocations"] = x.get_thread_flow_locations();
        if (is_obj_valid(x.get_translations()))
            j["translations"] = x.get_translations();
        if (is_obj_valid(x.get_web_requests()))
            j["webRequests"] = x.get_web_requests();
        if (is_obj_valid(x.get_web_responses()))
            j["webResponses"] = x.get_web_responses();
    }

    inline void from_json(const json & j, libsarif::SpecialLocations& x) {
        x.set_display_base(libsarif::get_optional<libsarif::ArtifactLocation>(j, "displayBase"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
    }

    inline void to_json(json & j, const libsarif::SpecialLocations & x) {
        j = json::object();
        if (is_obj_valid(x.get_display_base()))
            j["displayBase"] = x.get_display_base();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
    }

    inline void from_json(const json & j, libsarif::VersionControlDetails& x) {
        x.set_as_of_time_utc(libsarif::get_optional<std::string>(j, "asOfTimeUtc"));
        x.set_branch(libsarif::get_optional<std::string>(j, "branch"));
        x.set_mapped_to(libsarif::get_optional<libsarif::ArtifactLocation>(j, "mappedTo"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_repository_uri(j.at("repositoryUri").get<std::string>());
        x.set_revision_id(libsarif::get_optional<std::string>(j, "revisionId"));
        x.set_revision_tag(libsarif::get_optional<std::string>(j, "revisionTag"));
    }

    inline void to_json(json & j, const libsarif::VersionControlDetails & x) {
        j = json::object();
        if (is_obj_valid(x.get_as_of_time_utc()))
            j["asOfTimeUtc"] = x.get_as_of_time_utc();
        if (is_obj_valid(x.get_branch()))
            j["branch"] = x.get_branch();
        if (is_obj_valid(x.get_mapped_to()))
            j["mappedTo"] = x.get_mapped_to();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_repository_uri()))
            j["repositoryUri"] = x.get_repository_uri();
        if (is_obj_valid(x.get_revision_id()))
            j["revisionId"] = x.get_revision_id();
        if (is_obj_valid(x.get_revision_tag()))
            j["revisionTag"] = x.get_revision_tag();
    }

    inline void from_json(const json & j, libsarif::Run& x) {
        x.set_addresses(libsarif::get_optional<std::vector<libsarif::Address>>(j, "addresses"));
        x.set_artifacts(libsarif::get_optional<std::vector<libsarif::Artifact>>(j, "artifacts"));
        x.set_automation_details(libsarif::get_optional<libsarif::RunAutomationDetails>(j, "automationDetails"));
        x.set_baseline_guid(libsarif::get_optional<std::string>(j, "baselineGuid"));
        x.set_column_kind(libsarif::get_optional<libsarif::ColumnKind>(j, "columnKind"));
        x.set_conversion(libsarif::get_optional<libsarif::Conversion>(j, "conversion"));
        x.set_default_encoding(libsarif::get_optional<std::string>(j, "defaultEncoding"));
        x.set_default_source_language(libsarif::get_optional<std::string>(j, "defaultSourceLanguage"));
        x.set_external_property_file_references(libsarif::get_optional<libsarif::ExternalPropertyFileReferences>(j, "externalPropertyFileReferences"));
        x.set_graphs(libsarif::get_optional<std::vector<libsarif::Graph>>(j, "graphs"));
        x.set_invocations(libsarif::get_optional<std::vector<libsarif::Invocation>>(j, "invocations"));
        x.set_language(libsarif::get_optional<std::string>(j, "language"));
        x.set_logical_locations(libsarif::get_optional<std::vector<libsarif::LogicalLocation>>(j, "logicalLocations"));
        x.set_newline_sequences(libsarif::get_optional<std::vector<std::string>>(j, "newlineSequences"));
        x.set_original_uri_base_ids(libsarif::get_optional<std::map<std::string, libsarif::ArtifactLocation>>(j, "originalUriBaseIds"));
        x.set_policies(libsarif::get_optional<std::vector<libsarif::ToolComponent>>(j, "policies"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_redaction_tokens(libsarif::get_optional<std::vector<std::string>>(j, "redactionTokens"));
        x.set_results(libsarif::get_optional<std::vector<libsarif::Result>>(j, "results"));
        x.set_run_aggregates(libsarif::get_optional<std::vector<libsarif::RunAutomationDetails>>(j, "runAggregates"));
        x.set_special_locations(libsarif::get_optional<libsarif::SpecialLocations>(j, "specialLocations"));
        x.set_taxonomies(libsarif::get_optional<std::vector<libsarif::ToolComponent>>(j, "taxonomies"));
        x.set_thread_flow_locations(libsarif::get_optional<std::vector<libsarif::ThreadFlowLocation>>(j, "threadFlowLocations"));
        x.set_tool(j.at("tool").get<libsarif::Tool>());
        x.set_translations(libsarif::get_optional<std::vector<libsarif::ToolComponent>>(j, "translations"));
        x.set_version_control_provenance(libsarif::get_optional<std::vector<libsarif::VersionControlDetails>>(j, "versionControlProvenance"));
        x.set_web_requests(libsarif::get_optional<std::vector<libsarif::WebRequest>>(j, "webRequests"));
        x.set_web_responses(libsarif::get_optional<std::vector<libsarif::WebResponse>>(j, "webResponses"));
    }

    inline void to_json(json & j, const libsarif::Run & x) {
        j = json::object();
        if (is_obj_valid(x.get_addresses()))
            j["addresses"] = x.get_addresses();
        if (is_obj_valid(x.get_artifacts()))
            j["artifacts"] = x.get_artifacts();
        if (is_obj_valid(x.get_automation_details()))
            j["automationDetails"] = x.get_automation_details();
        if (is_obj_valid(x.get_baseline_guid()))
            j["baselineGuid"] = x.get_baseline_guid();
        if (is_obj_valid(x.get_column_kind()))
            j["columnKind"] = x.get_column_kind();
        if (is_obj_valid(x.get_conversion()))
            j["conversion"] = x.get_conversion();
        if (is_obj_valid(x.get_default_encoding()))
            j["defaultEncoding"] = x.get_default_encoding();
        if (is_obj_valid(x.get_default_source_language()))
            j["defaultSourceLanguage"] = x.get_default_source_language();
        if (is_obj_valid(x.get_external_property_file_references()))
            j["externalPropertyFileReferences"] = x.get_external_property_file_references();
        if (is_obj_valid(x.get_graphs()))
            j["graphs"] = x.get_graphs();
        if (is_obj_valid(x.get_invocations()))
            j["invocations"] = x.get_invocations();
        if (is_obj_valid(x.get_language()))
            j["language"] = x.get_language();
        if (is_obj_valid(x.get_logical_locations()))
            j["logicalLocations"] = x.get_logical_locations();
        if (is_obj_valid(x.get_newline_sequences()))
            j["newlineSequences"] = x.get_newline_sequences();
        if (is_obj_valid(x.get_original_uri_base_ids()))
            j["originalUriBaseIds"] = x.get_original_uri_base_ids();
        if (is_obj_valid(x.get_policies()))
            j["policies"] = x.get_policies();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_redaction_tokens()))
            j["redactionTokens"] = x.get_redaction_tokens();
        if (is_obj_valid(x.get_results()))
            j["results"] = x.get_results();
        if (is_obj_valid(x.get_run_aggregates()))
            j["runAggregates"] = x.get_run_aggregates();
        if (is_obj_valid(x.get_special_locations()))
            j["specialLocations"] = x.get_special_locations();
        if (is_obj_valid(x.get_taxonomies()))
            j["taxonomies"] = x.get_taxonomies();
        if (is_obj_valid(x.get_thread_flow_locations()))
            j["threadFlowLocations"] = x.get_thread_flow_locations();
        if (is_obj_valid(x.get_tool()))
            j["tool"] = x.get_tool();
        if (is_obj_valid(x.get_translations()))
            j["translations"] = x.get_translations();
        if (is_obj_valid(x.get_version_control_provenance()))
            j["versionControlProvenance"] = x.get_version_control_provenance();
        if (is_obj_valid(x.get_web_requests()))
            j["webRequests"] = x.get_web_requests();
        if (is_obj_valid(x.get_web_responses()))
            j["webResponses"] = x.get_web_responses();
    }

    inline void from_json(const json & j, libsarif::TopLevel& x) {
        x.set_schema(libsarif::get_optional<std::string>(j, "$schema"));
        x.set_inline_external_properties(libsarif::get_optional<std::vector<libsarif::ExternalProperties>>(j, "inlineExternalProperties"));
        x.set_properties(libsarif::get_optional<libsarif::PropertyBag>(j, "properties"));
        x.set_runs(j.at("runs").get<std::vector<libsarif::Run>>());
        x.set_version(j.at("version").get<libsarif::Version>());
    }

    inline void to_json(json & j, const libsarif::TopLevel & x) {
        j = json::object();
        j["$schema"] = x.get_schema();
        if (is_obj_valid(x.get_inline_external_properties()))
            j["inlineExternalProperties"] = x.get_inline_external_properties();
        if (is_obj_valid(x.get_properties()))
            j["properties"] = x.get_properties();
        if (is_obj_valid(x.get_runs()))
            j["runs"] = x.get_runs();
        if (is_obj_valid(x.get_version()))
            j["version"] = x.get_version();
    }

    inline void from_json(const json & j, libsarif::Role & x) {
        if (j == "added") x = libsarif::Role::ADDED;
        else if (j == "analysisTarget") x = libsarif::Role::ANALYSIS_TARGET;
        else if (j == "attachment") x = libsarif::Role::ATTACHMENT;
        else if (j == "debugOutputFile") x = libsarif::Role::DEBUG_OUTPUT_FILE;
        else if (j == "deleted") x = libsarif::Role::DELETED;
        else if (j == "directory") x = libsarif::Role::DIRECTORY;
        else if (j == "driver") x = libsarif::Role::DRIVER;
        else if (j == "extension") x = libsarif::Role::EXTENSION;
        else if (j == "memoryContents") x = libsarif::Role::MEMORY_CONTENTS;
        else if (j == "modified") x = libsarif::Role::MODIFIED;
        else if (j == "policy") x = libsarif::Role::POLICY;
        else if (j == "referencedOnCommandLine") x = libsarif::Role::REFERENCED_ON_COMMAND_LINE;
        else if (j == "renamed") x = libsarif::Role::RENAMED;
        else if (j == "responseFile") x = libsarif::Role::RESPONSE_FILE;
        else if (j == "resultFile") x = libsarif::Role::RESULT_FILE;
        else if (j == "standardStream") x = libsarif::Role::STANDARD_STREAM;
        else if (j == "taxonomy") x = libsarif::Role::TAXONOMY;
        else if (j == "toolSpecifiedConfiguration") x = libsarif::Role::TOOL_SPECIFIED_CONFIGURATION;
        else if (j == "tracedFile") x = libsarif::Role::TRACED_FILE;
        else if (j == "translation") x = libsarif::Role::TRANSLATION;
        else if (j == "uncontrolled") x = libsarif::Role::UNCONTROLLED;
        else if (j == "unmodified") x = libsarif::Role::UNMODIFIED;
        else if (j == "userSpecifiedConfiguration") x = libsarif::Role::USER_SPECIFIED_CONFIGURATION;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::Role & x) {
        switch (x) {
            case libsarif::Role::ADDED: j = "added"; break;
            case libsarif::Role::ANALYSIS_TARGET: j = "analysisTarget"; break;
            case libsarif::Role::ATTACHMENT: j = "attachment"; break;
            case libsarif::Role::DEBUG_OUTPUT_FILE: j = "debugOutputFile"; break;
            case libsarif::Role::DELETED: j = "deleted"; break;
            case libsarif::Role::DIRECTORY: j = "directory"; break;
            case libsarif::Role::DRIVER: j = "driver"; break;
            case libsarif::Role::EXTENSION: j = "extension"; break;
            case libsarif::Role::MEMORY_CONTENTS: j = "memoryContents"; break;
            case libsarif::Role::MODIFIED: j = "modified"; break;
            case libsarif::Role::POLICY: j = "policy"; break;
            case libsarif::Role::REFERENCED_ON_COMMAND_LINE: j = "referencedOnCommandLine"; break;
            case libsarif::Role::RENAMED: j = "renamed"; break;
            case libsarif::Role::RESPONSE_FILE: j = "responseFile"; break;
            case libsarif::Role::RESULT_FILE: j = "resultFile"; break;
            case libsarif::Role::STANDARD_STREAM: j = "standardStream"; break;
            case libsarif::Role::TAXONOMY: j = "taxonomy"; break;
            case libsarif::Role::TOOL_SPECIFIED_CONFIGURATION: j = "toolSpecifiedConfiguration"; break;
            case libsarif::Role::TRACED_FILE: j = "tracedFile"; break;
            case libsarif::Role::TRANSLATION: j = "translation"; break;
            case libsarif::Role::UNCONTROLLED: j = "uncontrolled"; break;
            case libsarif::Role::UNMODIFIED: j = "unmodified"; break;
            case libsarif::Role::USER_SPECIFIED_CONFIGURATION: j = "userSpecifiedConfiguration"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::Level & x) {
        if (j == "error") x = libsarif::Level::ERROR;
        else if (j == "none") x = libsarif::Level::NONE;
        else if (j == "note") x = libsarif::Level::NOTE;
        else if (j == "warning") x = libsarif::Level::WARNING;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::Level & x) {
        switch (x) {
            case libsarif::Level::ERROR: j = "error"; break;
            case libsarif::Level::NONE: j = "none"; break;
            case libsarif::Level::NOTE: j = "note"; break;
            case libsarif::Level::WARNING: j = "warning"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::Content & x) {
        if (j == "localizedData") x = libsarif::Content::LOCALIZED_DATA;
        else if (j == "nonLocalizedData") x = libsarif::Content::NON_LOCALIZED_DATA;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::Content & x) {
        switch (x) {
            case libsarif::Content::LOCALIZED_DATA: j = "localizedData"; break;
            case libsarif::Content::NON_LOCALIZED_DATA: j = "nonLocalizedData"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::BaselineState & x) {
        if (j == "absent") x = libsarif::BaselineState::ABSENT;
        else if (j == "new") x = libsarif::BaselineState::NEW;
        else if (j == "unchanged") x = libsarif::BaselineState::UNCHANGED;
        else if (j == "updated") x = libsarif::BaselineState::UPDATED;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::BaselineState & x) {
        switch (x) {
            case libsarif::BaselineState::ABSENT: j = "absent"; break;
            case libsarif::BaselineState::NEW: j = "new"; break;
            case libsarif::BaselineState::UNCHANGED: j = "unchanged"; break;
            case libsarif::BaselineState::UPDATED: j = "updated"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::Importance & x) {
        if (j == "essential") x = libsarif::Importance::ESSENTIAL;
        else if (j == "important") x = libsarif::Importance::IMPORTANT;
        else if (j == "unimportant") x = libsarif::Importance::UNIMPORTANT;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::Importance & x) {
        switch (x) {
            case libsarif::Importance::ESSENTIAL: j = "essential"; break;
            case libsarif::Importance::IMPORTANT: j = "important"; break;
            case libsarif::Importance::UNIMPORTANT: j = "unimportant"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::ResultKind & x) {
        if (j == "fail") x = libsarif::ResultKind::FAIL;
        else if (j == "informational") x = libsarif::ResultKind::INFORMATIONAL;
        else if (j == "notApplicable") x = libsarif::ResultKind::NOT_APPLICABLE;
        else if (j == "open") x = libsarif::ResultKind::OPEN;
        else if (j == "pass") x = libsarif::ResultKind::PASS;
        else if (j == "review") x = libsarif::ResultKind::REVIEW;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::ResultKind & x) {
        switch (x) {
            case libsarif::ResultKind::FAIL: j = "fail"; break;
            case libsarif::ResultKind::INFORMATIONAL: j = "informational"; break;
            case libsarif::ResultKind::NOT_APPLICABLE: j = "notApplicable"; break;
            case libsarif::ResultKind::OPEN: j = "open"; break;
            case libsarif::ResultKind::PASS: j = "pass"; break;
            case libsarif::ResultKind::REVIEW: j = "review"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::SuppressionKind & x) {
        if (j == "external") x = libsarif::SuppressionKind::EXTERNAL;
        else if (j == "inSource") x = libsarif::SuppressionKind::IN_SOURCE;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::SuppressionKind & x) {
        switch (x) {
            case libsarif::SuppressionKind::EXTERNAL: j = "external"; break;
            case libsarif::SuppressionKind::IN_SOURCE: j = "inSource"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::State & x) {
        if (j == "accepted") x = libsarif::State::ACCEPTED;
        else if (j == "rejected") x = libsarif::State::REJECTED;
        else if (j == "underReview") x = libsarif::State::UNDER_REVIEW;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::State & x) {
        switch (x) {
            case libsarif::State::ACCEPTED: j = "accepted"; break;
            case libsarif::State::REJECTED: j = "rejected"; break;
            case libsarif::State::UNDER_REVIEW: j = "underReview"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::Version & x) {
        if (j == "2.1.0") x = libsarif::Version::THE_210;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::Version & x) {
        switch (x) {
            case libsarif::Version::THE_210: j = "2.1.0"; break;
            default: throw "This should not happen";
        }
    }

    inline void from_json(const json & j, libsarif::ColumnKind & x) {
        if (j == "unicodeCodePoints") x = libsarif::ColumnKind::UNICODE_CODE_POINTS;
        else if (j == "utf16CodeUnits") x = libsarif::ColumnKind::UTF16_CODE_UNITS;
        else throw "Input JSON does not conform to schema";
    }

    inline void to_json(json & j, const libsarif::ColumnKind & x) {
        switch (x) {
            case libsarif::ColumnKind::UNICODE_CODE_POINTS: j = "unicodeCodePoints"; break;
            case libsarif::ColumnKind::UTF16_CODE_UNITS: j = "utf16CodeUnits"; break;
            default: throw "This should not happen";
        }
    }
}
