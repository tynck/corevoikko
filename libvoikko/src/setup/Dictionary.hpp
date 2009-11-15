/* Libvoikko: Library of Finnish language tools
 * Copyright (C) 2008 - 2009 Harri Pitkänen <hatapitk@iki.fi>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *********************************************************************************/

#ifndef VOIKKO_SETUP_DICTIONARY
#define VOIKKO_SETUP_DICTIONARY

#include <string>

namespace libvoikko { namespace setup {

class Dictionary {

	friend bool operator<(const Dictionary & d1, const Dictionary & d2);

	private:
	std::string morPath;
	std::string morBackend;
	std::string spellBackend;
	std::string variant;
	std::string description;
	bool isDefaultDict;

	public:
	Dictionary();
	Dictionary(const std::string & morPath,
	           const std::string & morBackend,
	           const std::string & spellBackend,
	           const std::string & variant,
	           const std::string & description);
	Dictionary(const Dictionary & dictionary);
	const std::string & getMorPath() const;
	const std::string & getMorBackend() const;
	const std::string & getSpellBackend() const;
	const std::string & getVariant() const;
	const std::string & getDescription() const;
	bool isValid() const;
	bool isDefault() const;
	void setDefault(bool isDefault);
};

} }

#endif
