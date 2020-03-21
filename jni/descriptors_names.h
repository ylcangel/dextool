/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ART_LIBDEXFILE_DEX_DESCRIPTORS_NAMES_H_
#define ART_LIBDEXFILE_DEX_DESCRIPTORS_NAMES_H_

#include <string>
	
/*
 * Returns the number of UTF-16 characters in the given modified UTF-8 string.
*/
size_t CountModifiedUtf8Chars(const char* utf8);
size_t CountModifiedUtf8Chars(const char* utf8, size_t byte_count);

/*
 * Retrieve the next UTF-16 character or surrogate pair from a UTF-8 string.
 * single byte, 2-byte and 3-byte UTF-8 sequences result in a single UTF-16
 * character (possibly one half of a surrogate) whereas 4-byte UTF-8 sequences
 * result in a surrogate pair. Use GetLeadingUtf16Char and GetTrailingUtf16Char
 * to process the return value of this function.
 *
 * Advances "*utf8_data_in" to the start of the next character.
 *
 * WARNING: If a string is corrupted by dropping a '\0' in the middle
 * of a multi byte sequence, you can end up overrunning the buffer with
 * reads (and possibly with the writes if the length was computed and
 * cached before the damage). For performance reasons, this function
 * assumes that the string being parsed is known to be valid (e.g., by
 * already being verified). Most strings we process here are coming
 * out of dex files or other internal translations, so the only real
 * risk comes from the JNI NewStringUTF call.
 */
uint32_t GetUtf16FromUtf8(const char** utf8_data_in);

/**
 * Gets the leading UTF-16 character from a surrogate pair, or the sole
 * UTF-16 character from the return value of GetUtf16FromUtf8.
 */
inline uint16_t GetLeadingUtf16Char(uint32_t maybe_pair);

/**
 * Gets the trailing UTF-16 character from a surrogate pair, or 0 otherwise
 * from the return value of GetUtf16FromUtf8.
 */
inline uint16_t GetTrailingUtf16Char(uint32_t maybe_pair);

// Used to implement PrettyClass, PrettyField, PrettyMethod, and PrettyTypeOf,
// one of which is probably more useful to you.
// Returns a human-readable equivalent of 'descriptor'. So "I" would be "int",
// "[[I" would be "int[][]", "[Ljava/lang/String;" would be
// "java.lang.String[]", and so forth.
void AppendPrettyDescriptor(const char* descriptor, std::string* result);
std::string PrettyDescriptor(const char* descriptor);

// Performs JNI name mangling as described in section 11.3 "Linking Native Methods"
// of the JNI spec.
std::string MangleForJni(const std::string& s);

std::string GetJniShortName(const std::string& class_name, const std::string& method_name);

// Turn "java.lang.String" into "Ljava/lang/String;".
std::string DotToDescriptor(const char* class_name);

// Turn "Ljava/lang/String;" into "java.lang.String" using the conventions of
// java.lang.Class.getName().
std::string DescriptorToDot(const char* descriptor);

// Turn "Ljava/lang/String;" into "java/lang/String" using the opposite conventions of
// java.lang.Class.getName().
std::string DescriptorToName(const char* descriptor);

// Tests for whether 's' is a valid class name in the three common forms:
bool IsValidBinaryClassName(const char* s);  // "java.lang.String"
bool IsValidJniClassName(const char* s);     // "java/lang/String"
bool IsValidDescriptor(const char* s);       // "Ljava/lang/String;"

// Returns whether the given string is a valid field or method name,
// additionally allowing names that begin with '<' and end with '>'.
bool IsValidMemberName(const char* s);


#endif  // ART_LIBDEXFILE_DEX_DESCRIPTORS_NAMES_H_
