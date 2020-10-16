/*
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Auth/HMACSHA1.h"
#include "BigNumber.h"

#if defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER < 0x10100000L
HMAC_CTX* HMAC_CTX_new()
{
    HMAC_CTX *ctx = new HMAC_CTX();
    HMAC_CTX_init(ctx);
    return ctx;
}

void HMAC_CTX_free(HMAC_CTX* ctx)
{
    HMAC_CTX_cleanup(ctx);
    delete ctx;
}
#endif

HMACSHA1::HMACSHA1(const uint8 *seed, size_t len) : m_ctx(HMAC_CTX_new())
{
    HMAC_Init_ex(m_ctx, seed, len, EVP_sha1(), nullptr);
}

HMACSHA1::~HMACSHA1()
{
    HMAC_CTX_free(m_ctx);
}

void HMACSHA1::UpdateBigNumber(const BigNumber *bn)
{
    UpdateData(bn->AsByteArray());
}

void HMACSHA1::UpdateData(const std::vector<uint8>& data)
{
    HMAC_Update(m_ctx, data.data(), data.size());
}

void HMACSHA1::UpdateData(const uint8 *data, size_t length)
{
    HMAC_Update(m_ctx, data, length);
}

void HMACSHA1::UpdateData(const std::string &str)
{
    UpdateData((uint8 const*)str.c_str(), str.length());
}

void HMACSHA1::Finalize()
{
    uint32 length = 0;
    HMAC_Final(m_ctx, m_digest, &length);
    //MANGOS_ASSERT(length == SHA_DIGEST_LENGTH);
}

const uint8 *HMACSHA1::ComputeHash(const BigNumber *bn)
{
    auto byteArray = bn->AsByteArray();
    HMAC_Update(m_ctx, byteArray.data(), byteArray.size());
    Finalize();
    return m_digest;
}