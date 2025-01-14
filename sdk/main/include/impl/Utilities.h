/*-
 *
 * Hedera C++ SDK
 *
 * Copyright (C) 2020 - 2022 Hedera Hashgraph, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License")
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
 *
 */
#ifndef HEDERA_SDK_CPP_IMPL_UTILITIES_H_
#define HEDERA_SDK_CPP_IMPL_UTILITIES_H_

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace Hedera::internal::Utilities
{
/**
 * Determine if a byte array is the prefix of another.
 *
 * @param bytes  The bytes in which to look for the prefix.
 * @param prefix The prefix bytes to find in the byte array.
 * @return \c TRUE If prefix is a prefix of bytes, otherwise \c FALSE.
 */
[[nodiscard]] bool isPrefixOf(const std::vector<std::byte>& bytes, const std::vector<std::byte>& prefix);

/**
 * Remove a certain number of bytes from the beginning of a byte vector.
 *
 * @param bytes The bytes from which to remove the prefix.
 * @param num   The number of bytes to remove.
 * @return The byte vector with the removed prefix bytes.
 */
[[nodiscard]] std::vector<std::byte> removePrefix(const std::vector<std::byte>& bytes, long num);

/**
 * Concatenate byte vectors together (in the order of the arguments).
 *
 * @param vectors The byte vectors to concatenate together.
 * @return A byte vector containing the input byte vectors concatenated into one.
 */
[[nodiscard]] std::vector<std::byte> concatenateVectors(const std::vector<std::vector<std::byte>>& vectors);

/**
 * Convert a string to a byte vector.
 *
 * @param str The string to convert.
 * @return The byte vector representing the input string.
 */
[[nodiscard]] std::vector<std::byte> stringToByteVector(std::string_view str);

/**
 * Convert a string to a byte.
 *
 * @param str The string to convert.
 * @return The byte representing the string.
 */
[[nodiscard]] std::byte stringToByte(std::string_view str);

/**
 * Convert a byte vector to a string.
 *
 * @param bytes The byte vector to convert to a string.
 * @return The string that represent of the byte vector.
 */
[[nodiscard]] std::string byteVectorToString(const std::vector<std::byte>& bytes);

} // namespace Hedera::internal::Utilities

#endif // HEDERA_SDK_CPP_IMPL_UTILITIES_H_
