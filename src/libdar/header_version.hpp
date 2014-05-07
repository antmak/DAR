/*********************************************************************/
// dar - disk archive - a backup/restoration program
// Copyright (C) 2002-2052 Denis Corbin
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// to contact the author : http://dar.linux.free.fr/email.html
/*********************************************************************/

    /// \file header_version.hpp
    /// \brief archive global header structure is defined here
    /// \ingroup Private

#ifndef HEADER_VERSION_HPP
#define HEADER_VERSION_HPP

#include "../my_config.h"
#include "infinint.hpp"
#include "generic_file.hpp"
#include "tools.hpp"
#include "archive_version.hpp"
#include "on_pool.hpp"
#include "crypto.hpp"

namespace libdar
{

	/// \addtogroup Private
	/// @{

	// FLAG VALUES

    const U_I VERSION_FLAG_SAVED_EA_ROOT = 0x80;      //< no more used since version "05"
    const U_I VERSION_FLAG_SAVED_EA_USER = 0x40;      //< no more used since version "05"
    const U_I VERSION_FLAG_SCRAMBLED     = 0x20;      //< scrambled or strong encryption used
    const U_I VERSION_FLAG_SEQUENCE_MARK = 0x10;      //< escape sequence marks present for sequential reading
    const U_I VERSION_FLAG_INITIAL_OFFSET = 0x08;     //< whether the header contains the initial offset (size of clear data before encrypted) NOTE : This value is set internally by header_version, no need to set flag with it! But that's OK to set it or not, it will be updated according to initial_offset's value.
    const U_I VERSION_FLAG_HAS_CRYPTED_KEY = 0x04;    //< the header contains a symmetrical key encrypted with asymmetrical algorithm
    const U_I VERSION_FLAG_HAS_AN_EXTENDED_SIZE = 0x01; //< reserved for future use


	/// manages of the archive header and trailer
    struct header_version : public on_pool
    {
        archive_version edition;
        char algo_zip;
        std::string cmd_line; // used long ago to store cmd_line, then abandonned, then recycled as a user comment field
        unsigned char flag; // added at edition 02
	infinint initial_offset; // not dropped to archive if set to zero (at dump() time, the flag is also updated with VERSION_FLAG_INITIAL_OFFSET accordingly to this value)
	crypto_algo sym;
	memory_file *crypted_key;

	header_version();
        void read(generic_file &f);
        void write(generic_file &f) const;
    };

} // end of namespace

#endif
