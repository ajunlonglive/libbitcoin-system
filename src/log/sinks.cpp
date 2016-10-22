/**
 * Copyright (c) 2011-2013 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/bitcoin/log/sinks.hpp>

#include <map>
#include <string>
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <bitcoin/bitcoin/log/attributes.hpp>
#include <bitcoin/bitcoin/log/severity.hpp>
#include <bitcoin/bitcoin/unicode/ofstream.hpp>

namespace libbitcoin {
namespace log {

using namespace boost::log::expressions;
using namespace boost::log::keywords;
using namespace boost::log::sinks;
using namespace boost::posix_time;

#define TIME_FORMAT "%H:%M:%S.%f"
#define TIME_STAMP attributes::timestamp.get_name()
#define TIME_FORMATTER format_date_time<ptime, char>(TIME_STAMP, TIME_FORMAT)
#define SEVERITY_FORMATTER attributes::severity
#define CHANNEL_FORMATTER "[" << attributes::channel << "]"
#define MESSAGE_FORMATTER smessage

#define LINE_FORMATTER boost::log::expressions::stream \
    << TIME_FORMATTER << " " \
    << SEVERITY_FORMATTER << " " \
    << CHANNEL_FORMATTER << " " \
    << MESSAGE_FORMATTER

typedef synchronous_sink<text_file_backend> text_file_sink;
typedef synchronous_sink<text_ostream_backend> text_stream_sink;

const auto error_filter =
    (attributes::severity == severity::warning) ||
    (attributes::severity == severity::error) ||
    (attributes::severity == severity::fatal);

const auto info_filter =
    (attributes::severity == severity::info);

const auto mode = std::ofstream::out | std::ofstream::app;

static std::map<severity, std::string> severity_mapping
{
    { severity::debug, "DEBUG" },
    { severity::info, "INFO" },
    { severity::warning, "WARNING" },
    { severity::error, "ERROR" },
    { severity::fatal, "FATAL" }
};

formatter& operator<<(formatter& stream, severity level)
{
    stream << severity_mapping[level];
    return stream;
}

static boost::shared_ptr<text_file_sink> add_text_file_sink(
    const file_sink_configuration& config)
{
    // Construct a log sink.
    const auto sink = boost::make_shared<text_file_sink>();

//    sink->locked_backend()->set_open_mode(mode);

    // Add a stream for the sink to write to.
#ifdef _MSC_VER
    sink->locked_backend()->set_file_name_pattern(bc::to_utf16(config.name_pattern));
#else
    sink->locked_backend()->set_file_name_pattern(config.name_pattern);
#endif

    if (config.rotation_size > 0)
        sink->locked_backend()->set_rotation_size(config.rotation_size);

    // Flush the sink after each logical line.
    sink->locked_backend()->auto_flush(true);

    // Add the formatter to the sink.
    sink->set_formatter(LINE_FORMATTER);

    sink->locked_backend()->set_file_collector(
        boost::log::sinks::file::make_collector(
#ifdef _MSC_VER
            target = bc::to_utf16(config.rotation_path),
#else
            target = config.rotation_path,
#endif
//            max_files = config.rotation_max_files,
            max_size = config.rotation_max_files_size,
            min_free_space = config.rotation_min_free_space
        ));

    // Register the sink with the logging core.
    boost::log::core::get()->add_sink(sink);

    return sink;
}

template<typename Stream>
static boost::shared_ptr<text_stream_sink> add_text_stream_sink(
    boost::shared_ptr<Stream>& stream)
{
    // Construct a log sink.
    const auto sink = boost::make_shared<text_stream_sink>();

    // Add a stream for the sink to write to.
    sink->locked_backend()->add_stream(stream);

    // Flush the sink after each logical line.
    sink->locked_backend()->auto_flush(true);

    // Add the formatter to the sink.
    sink->set_formatter(LINE_FORMATTER);

    // Register the sink with the logging core.
    boost::log::core::get()->add_sink(sink);

    return sink;
}

void initialize(log::file& debug_file, log::file& error_file,
    log::stream& output_stream, log::stream& error_stream)
{
    add_text_stream_sink(debug_file);
    add_text_stream_sink(error_file)->set_filter(error_filter);
    add_text_stream_sink(output_stream)->set_filter(info_filter);
    add_text_stream_sink(error_stream)->set_filter(error_filter);
}

void initialize(const file_sink_configuration& debug_file,
    const file_sink_configuration& error_file,
    log::stream& output_stream, log::stream& error_stream)
{
    add_text_file_sink(debug_file);
    add_text_file_sink(error_file)->set_filter(error_filter);
    add_text_stream_sink(output_stream)->set_filter(info_filter);
    add_text_stream_sink(error_stream)->set_filter(error_filter);
}

} // namespace log
} // namespace libbitcoin