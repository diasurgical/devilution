#include "../types.h"

using namespace dvlnet;

static constexpr bool disable_encryption = false;

const buffer_t& packet::data()
{
	if (!have_decrypted || !have_encrypted)
		ABORT();
	return encrypted_buffer;
}

packet_type packet::type()
{
	if (!have_decrypted)
		ABORT();
	return m_type;
}

plr_t packet::src()
{
	if (!have_decrypted)
		ABORT();
	return m_src;
}

plr_t packet::dest()
{
	if (!have_decrypted)
		ABORT();
	return m_dest;
}

const buffer_t &packet::message()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_MESSAGE)
		throw packet_exception();
	return m_message;
}

turn_t packet::turn()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_TURN)
		throw packet_exception();
	return m_turn;
}

cookie_t packet::cookie()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_JOIN_REQUEST && m_type != PT_JOIN_ACCEPT)
		throw packet_exception();
	return m_cookie;
}

plr_t packet::newplr()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_JOIN_ACCEPT)
		throw packet_exception();
	return m_newplr;
}

plr_t packet::oldplr()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_LEAVE_GAME)
		throw packet_exception();
	return m_oldplr;
}

const buffer_t &packet::info()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_JOIN_ACCEPT)
		throw packet_exception();
	return m_info;
}

void packet_in::create(buffer_t buf)
{
	if (have_encrypted || have_decrypted)
		ABORT();
	encrypted_buffer = std::move(buf);
	have_encrypted = true;
}

void packet_in::decrypt()
{
	if (!have_encrypted)
		ABORT();
	if (have_decrypted)
		return;
	if (!disable_encryption) {
		if (encrypted_buffer.size() < crypto_secretbox_NONCEBYTES +
			crypto_secretbox_MACBYTES + sizeof(packet_type) + 2 * sizeof(plr_t))
			throw packet_exception();
		auto pktlen = encrypted_buffer.size() - crypto_secretbox_NONCEBYTES - crypto_secretbox_MACBYTES;
		decrypted_buffer.resize(pktlen);
		if (crypto_secretbox_open_easy(decrypted_buffer.data(),
		        encrypted_buffer.data() + crypto_secretbox_NONCEBYTES,
		        encrypted_buffer.size() - crypto_secretbox_NONCEBYTES,
		        encrypted_buffer.data(),
		        key.data()))
			throw packet_exception();
	} else {
		if (encrypted_buffer.size() < sizeof(packet_type) + 2 * sizeof(plr_t))
			throw packet_exception();
		decrypted_buffer = encrypted_buffer;
	}

	process_data();

	have_decrypted = true;
}

void packet_out::create(packet_type t,
    plr_t s,
    plr_t d,
    buffer_t m)
{
	if (have_encrypted || have_decrypted)
		ABORT();
	if (t != PT_MESSAGE)
		ABORT();
	have_decrypted = true;
	m_type = t;
	m_src = s;
	m_dest = d;
	m_message = std::move(m);
}

void packet_out::create(packet_type t,
    plr_t s,
    plr_t d,
    turn_t u)
{
	if (have_encrypted || have_decrypted)
		ABORT();
	if (t != PT_TURN)
		ABORT();
	have_decrypted = true;
	m_type = t;
	m_src = s;
	m_dest = d;
	m_turn = u;
}

void packet_out::create(packet_type t,
    plr_t s,
    plr_t d,
    cookie_t c)
{
	if (have_encrypted || have_decrypted)
		ABORT();
	if (t != PT_JOIN_REQUEST)
		ABORT();
	have_decrypted = true;
	m_type = t;
	m_src = s;
	m_dest = d;
	m_cookie = c;
}

void packet_out::create(packet_type t,
    plr_t s,
    plr_t d,
    cookie_t c,
    plr_t n,
    buffer_t i)
{
	if (have_encrypted || have_decrypted)
		ABORT();
	if (t != PT_JOIN_ACCEPT)
		ABORT();
	have_decrypted = true;
	m_type = t;
	m_src = s;
	m_dest = d;
	m_cookie = c;
	m_newplr = n;
	m_info = i;
}

void packet_out::create(packet_type t,
    plr_t s,
    plr_t d,
    plr_t o)
{
	if (have_encrypted || have_decrypted)
		ABORT();
	if (t != PT_LEAVE_GAME)
		ABORT();
	have_decrypted = true;
	m_type = t;
	m_src = s;
	m_dest = d;
	m_oldplr = o;
}

void packet_out::encrypt()
{
	if (!have_decrypted)
		ABORT();
	if (have_encrypted)
		return;

	process_data();

	if (!disable_encryption) {
		auto len_cleartext = encrypted_buffer.size();
		encrypted_buffer.insert(encrypted_buffer.begin(), crypto_secretbox_NONCEBYTES, 0);
		encrypted_buffer.insert(encrypted_buffer.end(), crypto_secretbox_MACBYTES, 0);
		randombytes_buf(encrypted_buffer.data(), crypto_secretbox_NONCEBYTES);
		if (crypto_secretbox_easy(encrypted_buffer.data() + crypto_secretbox_NONCEBYTES,
		        encrypted_buffer.data() + crypto_secretbox_NONCEBYTES,
		        len_cleartext,
		        encrypted_buffer.data(),
		        key.data()))
			ABORT();
	}
	have_encrypted = true;
}
