/* Copyright (C) 2003 MySQL AB

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#ifndef SECTION_READER_HPP
#define SECTION_READER_HPP

#include <ndb_types.h>

class SectionReader {
public:
  SectionReader(struct SegmentedSectionPtr &,
		class SectionSegmentPool &);
  SectionReader(Uint32 firstSectionIVal,
                class SectionSegmentPool &);

  /* reset : Set SectionReader to start of section */
  void reset();
  /* step : Step over given number of words */
  bool step(Uint32 len);
  /* getWord : Copy one word to dst + move forward */
  bool getWord(Uint32 * dst);
  /* peekWord : Copy one word to dst */
  bool peekWord(Uint32 * dst) const ;
  /* peekWords : Copy len words to dst */
  bool peekWords(Uint32 * dst, Uint32 len) const;
  /* getSize : Get total size of section */
  Uint32 getSize() const;
  /* getWords : Copy len words to dst + move forward */
  bool getWords(Uint32 * dst, Uint32 len);

  /* getWordsPtr : Get const ptr to next contiguous
   *               block of words
   * In success case will return at least 1 word
   */
  bool getWordsPtr(const Uint32*& readPtr,
                   Uint32& actualLen);
  /* getWordsPtr : Get const ptr to at most maxLen words
   * In success case will return at least 1 word
   */
  bool getWordsPtr(Uint32 maxLen,
                   const Uint32*& readPtr,
                   Uint32& actualLen);

private:
  Uint32 m_pos;
  Uint32 m_len;
  class SectionSegmentPool & m_pool;
  struct SectionSegment * m_head;
  struct SectionSegment * m_currentSegment;
};

inline
Uint32 SectionReader::getSize() const
{
  return m_len;
}

#endif
