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

    /// \file cat_blockdev.hpp
    /// \brief class used to record block special devices in a catalogue
    /// \ingroup Private

#ifndef CAT_BLOCKDEV_HPP
#define CAT_BLOCKDEV_HPP

#include "../my_config.h"

extern "C"
{
} // end extern "C"

#include "cat_device.hpp"

namespace libdar
{

	/// \addtogroup Private
	/// @{

	/// the block device class
    class blockdev : public device
    {
    public:
        blockdev(const infinint & uid, const infinint & gid, U_16 perm,
                 const datetime & last_access,
                 const datetime & last_modif,
		 const datetime & last_change,
                 const std::string & name,
                 U_16 major,
                 U_16 minor,
		 const infinint & fs_device) : device(uid, gid, perm, last_access,
						      last_modif, last_change, name,
						      major, minor, fs_device) {};
        blockdev(user_interaction & dialog,
		 generic_file & f,
		 const archive_version & reading_ver,
		 saved_status saved,
		 compressor *efsa_loc,
		 escape *ptr) : device(dialog, f, reading_ver, saved, efsa_loc, ptr) {};

            // using dump from device class
            // using method is_more_recent_than() from device class
            // using method has_changed_since() from device class
        unsigned char signature() const { return mk_signature('b', get_saved_status()); };
        cat_entree *clone() const { return new (get_pool()) blockdev(*this); };
    };

	/// @}

} // end of namespace

#endif
