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
#include "impl/Endpoint.h"

#include <proto/basic_types.pb.h>
#include <sstream>

namespace Hedera::internal
{
//-----
Endpoint Endpoint::fromProtobuf(const proto::ServiceEndpoint& protoServiceEndpoint)
{
  return { IPv4Address::fromString(protoServiceEndpoint.ipaddressv4()),
           static_cast<int>(protoServiceEndpoint.port() & 0x00000000ffffffffL) };
}

//-----
Endpoint::Endpoint(const IPv4Address& ipAddressV4, int port)
  : mAddress(ipAddressV4)
  , mPort(port)
{
  // TODO: here we change the port to the TLS port, since the existing serialization of the testnet address book doesn't
  // include TLS endpoints. Once we have an up to date serialization, remove this
  if (mPort == 50211)
  {
    mPort = 50212;
  }
}

//-----
std::string Endpoint::toString() const
{
  std::stringstream outputStream;

  outputStream << mAddress.toString() << ":" << mPort;

  return outputStream.str();
}

} // namespace Hedera::internal
