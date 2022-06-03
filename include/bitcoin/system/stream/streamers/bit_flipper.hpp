/**
 * Copyright (c) 2011-2021 libbitcoin developers (see AUTHORS)
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

// Sponsored in part by Digital Contract Design, LLC

#ifndef LIBBITCOIN_SYSTEM_STREAM_STREAMERS_BIT_FLIPPER_HPP
#define LIBBITCOIN_SYSTEM_STREAM_STREAMERS_BIT_FLIPPER_HPP

#include <iostream>
#include <bitcoin/system/define.hpp>
#include <bitcoin/system/stream/streamers/bit_reader.hpp>
#include <bitcoin/system/stream/streamers/bit_writer.hpp>
#include <bitcoin/system/stream/streamers/interfaces/bitflipper.hpp>

// Suppress multiple inheritance warnings.
// The only multiple inheritance conflict is destructors and bool/!.
BC_PUSH_WARNING(4250)

namespace libbitcoin {
namespace system {

/// A bit reader/writer that accepts an iostream.
/// Bit actions may lead to unextected read behavior, as they are read and
/// flushed to the byte reader/writer on byte boundaries. Flushing a
/// partial write will require a merged read, and reading after a partial
/// write will require a merged flush. These are not yet implemented.
/// In general it is not presently advisable to mix byte and byte operations
/// with the bit flipper. If at all, perform byte operations first, then bit
/// then flush, at which point the bit position is again on a byte boudary.
template <typename IOStream = std::iostream>
class bit_flipper
  : public bit_reader<IOStream>,
    public bit_writer<IOStream>,
    public virtual bitflipper
{
public:
    /// Constructors.
    bit_flipper(IOStream& stream) noexcept
      : bit_reader<IOStream>(stream), bit_writer<IOStream>(stream)
    {
        // Base constructions only capture references.
        // There are two references to the iostream:
        // bit_reader -> byte_reader (istream&)
        // bit_writer -> byte_writer (ostream&)
    }

    /// Defaults.
    bit_flipper(bit_flipper&&) = default;
    bit_flipper(const bit_flipper&) = default;
    bit_flipper& operator=(bit_flipper&&) = default;
    bit_flipper& operator=(const bit_flipper&) = default;

    // Two base destructor calls order is unimportant (only writes flush).
    ~bit_flipper() override = default;

    operator bool() const noexcept override
    {
        // Rely on reader implementation, both are trivial and identical.
        return bit_reader<IOStream>::operator bool();
    }

    bool operator!() const noexcept override
    {
        // Rely on reader implementation, both are trivial and identical.
        return bit_reader<IOStream>::operator!();
    }
};

} // namespace system
} // namespace libbitcoin

BC_POP_WARNING()

#endif
