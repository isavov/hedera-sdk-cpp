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
#include "AccountRecordsQuery.h"
#include "AccountId.h"
#include "AccountRecords.h"
#include "Client.h"
#include "TransactionRecord.h"
#include "TransferTransaction.h"
#include "impl/Node.h"

#include <proto/crypto_get_account_records.pb.h>
#include <proto/query.pb.h>
#include <proto/query_header.pb.h>
#include <proto/response.pb.h>

namespace Hedera
{
//-----
AccountRecordsQuery& AccountRecordsQuery::setAccountId(const AccountId& accountId)
{
  mAccountId = accountId;
  return *this;
}

//-----
proto::Query AccountRecordsQuery::makeRequest(const Client& client, const std::shared_ptr<internal::Node>& node) const
{
  proto::Query query;
  proto::CryptoGetAccountRecordsQuery* getAccountRecordsQuery = query.mutable_cryptogetaccountrecords();

  proto::QueryHeader* header = getAccountRecordsQuery->mutable_header();
  header->set_responsetype(proto::ANSWER_ONLY);

  TransferTransaction tx = TransferTransaction()
                             .setTransactionId(TransactionId::generate(*client.getOperatorAccountId()))
                             .setNodeAccountIds({ node->getAccountId() })
                             .setMaxTransactionFee(Hbar(1LL))
                             .addHbarTransfer(*client.getOperatorAccountId(), Hbar(-1LL))
                             .addHbarTransfer(node->getAccountId(), Hbar(1LL));
  tx.onSelectNode(node);
  header->set_allocated_payment(new proto::Transaction(tx.makeRequest(client, node)));

  getAccountRecordsQuery->set_allocated_accountid(mAccountId.toProtobuf().release());

  return query;
}

//-----
AccountRecords AccountRecordsQuery::mapResponse(const proto::Response& response) const
{
  return AccountRecords::fromProtobuf(response.cryptogetaccountrecords());
}

//-----
Status AccountRecordsQuery::mapResponseStatus(const proto::Response& response) const
{
  return gProtobufResponseCodeToStatus.at(response.cryptogetaccountrecords().header().nodetransactionprecheckcode());
}

//-----
grpc::Status AccountRecordsQuery::submitRequest(const Client& client,
                                                const std::chrono::system_clock::time_point& deadline,
                                                const std::shared_ptr<internal::Node>& node,
                                                proto::Response* response) const
{
  return node->submitQuery(
    proto::Query::QueryCase::kCryptoGetAccountRecords, makeRequest(client, node), deadline, response);
}

} // namespace Hedera
