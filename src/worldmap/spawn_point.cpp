//  SuperTux - Worldmap Spawnpoint
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <config.h>

#include <stdexcept>
#include <iostream>
#include "spawn_point.hpp"
#include "lisp/lisp.hpp"
#include "lisp/list_iterator.hpp"
#include "log.hpp"

namespace WorldMapNS
{

// from worldmap.cpp
Direction string_to_direction(const std::string& directory);

SpawnPoint::SpawnPoint(const lisp::Lisp* slisp) : auto_dir(D_NONE)
{
    pos.x = -1;
    pos.y = -1;
    lisp::ListIterator iter(slisp);
    while(iter.next()) {
        const std::string& token = iter.item();
        if(token == "name") {
            iter.value()->get(name);
        } else if(token == "x") {
            iter.value()->get(pos.x);
        } else if(token == "y") {
            iter.value()->get(pos.y);
        } else if(token == "auto-dir") {
            std::string s = "";
            iter.value()->get(s);
            auto_dir = string_to_direction(s);
        } else {
            log_warning << "unknown token '" << token << "' in SpawnPoint" << std::endl;
        }
    }

    if(name == "")
        throw std::runtime_error("No name specified for spawnpoint");
    if(pos.x < 0 || pos.y < 0)
        throw std::runtime_error("Invalid coordinates for spawnpoint");
}

}
