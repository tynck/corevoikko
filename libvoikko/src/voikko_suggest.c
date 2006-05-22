/* Libvoikko: Finnish spellchecker and hyphenator library
 * Copyright (C) 2006 Harri Pitkänen <hatapitk@iki.fi>
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

#include "voikko_defs.h"
#include "voikko_utils.h"
#include "voikko_setup.h"
#include "voikko_suggest.h"
#include "voikko_spell.h"
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <malaga.h>

#define MAX_SUGGESTIONS 10

void voikko_suggest_correct_case(int handle, wchar_t *** suggestions, int * max_suggestions,
                                 const wchar_t * word, size_t wlen, int * cost) {
	enum spellresult sres;
	wchar_t * newsugg;
	value_t analysis;
	const char * analysis_str;
	char * malaga_buffer;
	size_t i, j;
	if (*max_suggestions == 0) return;
	sres = voikko_do_spell(word, wlen);
	(*cost)++;
	switch (sres) {
		case SPELL_FAILED:
		case SPELL_OK:
			return;
		case SPELL_CAP_FIRST:
			newsugg = malloc((wlen + 1) * sizeof(wchar_t));
			newsugg[0] = towupper(word[0]);
			wcsncpy(newsugg + 1, word + 1, wlen - 1);
			newsugg[wlen] = L'\0';
			**suggestions = newsugg;
			(*suggestions)++;
			(*max_suggestions)--;
			return;
		case SPELL_CAP_ERROR:
			malaga_buffer = voikko_ucs4tocstr(word, "UTF-8");
			analyse_item(malaga_buffer, MORPHOLOGY);
			free(malaga_buffer);
			(*cost)++;
			analysis = first_analysis_result();
			if (!analysis) return;
			analysis_str = get_value_string(analysis);
			newsugg = malloc((wlen + 1) * sizeof(wchar_t));
			wcscpy(newsugg, word);
			j = 0;
			for (i = 0; i < wlen; i++) {
				while (analysis_str[j] == '=') j++;
				if (analysis_str[j] == '\0') break;
				if (analysis_str[j] == 'i' || analysis_str[j] == 'j')
					newsugg[i] = towupper(newsugg[i]);
				else if (analysis_str[j] == 'p' || analysis_str[j] == 'q')
					newsugg[i] = towlower(newsugg[i]);
				j++;
			}
			free((char *) analysis_str);
			**suggestions = newsugg;
			(*suggestions)++;
			(*max_suggestions)--;
			return;
	}
}

wchar_t ** voikko_suggest_ucs4(int handle, const wchar_t * word) {
	wchar_t ** suggestions;
	wchar_t ** free_sugg;
	size_t wlen;
	int cost;
	int suggestions_left;
	if (word == 0) return 0;
	wlen = wcslen(word);
	if (wlen <= 1) return 0;
	
	suggestions = calloc(MAX_SUGGESTIONS + 1, sizeof(wchar_t *));
	free_sugg = suggestions;
	suggestions_left = MAX_SUGGESTIONS;
	cost = 0;
	
	voikko_suggest_correct_case(handle, &free_sugg, &suggestions_left, word, wlen, &cost);
	
	if (suggestions_left == MAX_SUGGESTIONS) {
		free(suggestions);
		return 0;
	}
	return suggestions;
}

char ** voikko_suggest_cstr(int handle, const char * word) {
	wchar_t * word_ucs4;
	wchar_t ** suggestions_ucs4;
	char ** suggestions;
	int i;
	int scount;
	char * suggestion;
	if (word == 0 || word[0] == '\0') return 0;
	word_ucs4 = voikko_cstrtoucs4(word, voikko_options.encoding);
	if (word_ucs4 == 0) return 0;
	suggestions_ucs4 = voikko_suggest_ucs4(handle, word_ucs4);
	free(word_ucs4);
	if (suggestions_ucs4 == 0) return 0;
	scount = 0;
	while (suggestions_ucs4[scount] != 0) scount++;
	suggestions = malloc((scount + 1) * sizeof(char *));
	for (i = 0; i < scount; i++) {
		suggestion = voikko_ucs4tocstr(suggestions_ucs4[i], voikko_options.encoding);
		if (suggestion == 0) return 0; /* suggestion cannot be encoded */
		suggestions[i] = suggestion;
		free(suggestions_ucs4[i]);
	}
	suggestions[scount] = 0;
	free(suggestions_ucs4);
	return suggestions;
}
