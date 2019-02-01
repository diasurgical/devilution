#include "../types.h"

static constexpr bool disable_encryption = false;

const dvlnet_udp::buffer_t &dvlnet_udp::packet::data()
{
	if (!have_decrypted || !have_encrypted)
		ABORT();
	return encrypted_buffer;
}

dvlnet_udp::packet_type dvlnet_udp::packet::type()
{
	if (!have_decrypted)
		ABORT();
	return m_type;
}

dvlnet_udp::plr_t dvlnet_udp::packet::src()
{
	if (!have_decrypted)
		ABORT();
	return m_src;
}

dvlnet_udp::plr_t dvlnet_udp::packet::dest()
{
	if (!have_decrypted)
		ABORT();
	return m_dest;
}

const dvlnet_udp::buffer_t &dvlnet_udp::packet::message()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_MESSAGE)
		throw dvlnet_udp::packet_exception();
	return m_message;
}

dvlnet_udp::turn_t dvlnet_udp::packet::turn()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_TURN)
		throw dvlnet_udp::packet_exception();
	return m_turn;
}

dvlnet_udp::cookie_t dvlnet_udp::packet::cookie()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_JOIN_REQUEST && m_type != PT_JOIN_ACCEPT)
		throw dvlnet_udp::packet_exception();
	return m_cookie;
}

dvlnet_udp::plr_t dvlnet_udp::packet::newplr()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_JOIN_ACCEPT)
		throw dvlnet_udp::packet_exception();
	return m_newplr;
}

dvlnet_udp::plr_t dvlnet_udp::packet::oldplr()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_LEAVE_GAME)
		throw dvlnet_udp::packet_exception();
	return m_oldplr;
}

const dvlnet_udp::buffer_t &dvlnet_udp::packet::info()
{
	if (!have_decrypted)
		ABORT();
	if (m_type != PT_JOIN_ACCEPT)
		throw dvlnet_udp::packet_exception();
	return m_info;
}

void dvlnet_udp::packet_in::create(dvlnet_udp::buffer_t buf)
{
	if (have_encrypted || have_decrypted)
		ABORT();
	encrypted_buffer = std::move(buf);
	have_encrypted = true;
}

void dvlnet_udp::packet_in::decrypt()
{
	if (!have_encrypted)
		ABORT();
	if (have_decrypted)
		return;
	if (!disable_encryption) {
		if (encrypted_buffer.size() < crypto_secretbox_NONCEBYTES +
			crypto_secretbox_MACBYTES + sizeof(packet_type) + 2 * sizeof(plr_t))
			throw dvlnet_udp::packet_exception();
		auto pktlen = encrypted_buffer.size() - crypto_secretbox_NONCEBYTES - crypto_secretbox_MACBYTES;
		decrypted_buffer.resize(pktlen);
		if (crypto_secretbox_open_easy(decrypted_buffer.data(),
		        encrypted_buffer.data() + crypto_secretbox_NONCEBYTES,
		        encrypted_buffer.size() - crypto_secretbox_NONCEBYTES,
		        encrypted_buffer.data(),
		        key.data()))
			throw dvlnet_udp::packet_exception();
	} else {
		if (encrypted_buffer.size() < sizeof(packet_type) + 2 * sizeof(plr_t))
			throw dvlnet_udp::packet_exception();
		decrypted_buffer = encrypted_buffer;
	}

	process_data(*this);

	have_decrypted = true;
}

void dvlnet_udp::packet_out::create(dvlnet_udp::packet_type t,
    dvlnet_udp::plr_t s,
    dvlnet_udp::plr_t d,
    dvlnet_udp::buffer_t m)
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

void dvlnet_udp::packet_out::create(dvlnet_udp::packet_type t,
    dvlnet_udp::plr_t s,
    dvlnet_udp::plr_t d,
    dvlnet_udp::turn_t u)
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

void dvlnet_udp::packet_out::create(dvlnet_udp::packet_type t,
    dvlnet_udp::plr_t s,
    dvlnet_udp::plr_t d,
    dvlnet_udp::cookie_t c)
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

void dvlnet_udp::packet_out::create(dvlnet_udp::packet_type t,
    dvlnet_udp::plr_t s,
    dvlnet_udp::plr_t d,
    dvlnet_udp::cookie_t c,
    dvlnet_udp::plr_t n,
    dvlnet_udp::buffer_t i)
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

void dvlnet_udp::packet_out::create(dvlnet_udp::packet_type t,
    dvlnet_udp::plr_t s,
    dvlnet_udp::plr_t d,
    dvlnet_udp::plr_t o)
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

void dvlnet_udp::packet_out::encrypt()
{
	if (!have_decrypted)
		ABORT();
	if (have_encrypted)
		return;

	process_data(*this);

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
