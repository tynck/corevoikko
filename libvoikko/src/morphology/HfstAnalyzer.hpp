/* Libvoikko: Library of Finnish language tools
 * Copyright (C) 2009 Harri Pitkänen <hatapitk@iki.fi>
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

#ifndef VOIKKO_MORPHOLOGY_HFST_ANALYZER
#define VOIKKO_MORPHOLOGY_HFST_ANALYZER

#include <ospell.h>
#include "morphology/Analyzer.hpp"
#include "setup/DictionaryException.hpp"
#include <map>
#include <string>

namespace libvoikko { namespace morphology {

/**
 * Morphological analyzer that uses Hfst to analyze words.
 */
class HfstAnalyzer : public Analyzer {
	public:
		HfstAnalyzer(const std::string & directoryName) throw(setup::DictionaryException);
		std::list<Analysis *> * analyze(const wchar_t * word);
		std::list<Analysis *> * analyze(const wchar_t * word, size_t wlen);
		std::list<Analysis *> * analyze(const char * word);
		void terminate();

		HfstAnalyzer & operator = (const HfstAnalyzer & other);
	private:
		hfst_ol::Transducer *t;

		HfstAnalyzer(HfstAnalyzer const & other);

};

} }

#endif
