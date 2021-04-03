#include "SHA256.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::hex;
using std::uppercase;
using std::setfill;
using std::setw;


std::string SHA256::hash(std::string input) {
	message_blocks.clear();

	// Preprocessing stage.
	add_pading(input);
	parse_message(input);

	// Hash computation.
	return compute_hash();
}

// ======================================================
// Preprocessing.
// ======================================================

void SHA256::add_pading(std::string &input) {
	uint64_t message_bits = input.size() * 8;
	uint64_t bits_last_block = message_bits % 512;

	// The last block contains: [message, 1-bit delimiter, padding zeros, and 64 bits for message length]. 
	// If message size is greater than 447 bits there isn't enough space for the message length and delimiter,
	// therefore more padding needs to be added ti create a new block.


	// 在二进制的消息数据后附加0b1000000
	input.push_back(0b10000000);

	// 得出需要在消息体后附加几个0
	int16_t padding_zeros = 0;
	if (bits_last_block > 448 - 1) {
		padding_zeros = 1024 - bits_last_block - 64;
	}
	else {
		padding_zeros = 512 - bits_last_block - 64;
	}

	// 附加除了已经附加的0b10000000(8位)之外的其他0，填充至512-64=448位
	for (int16_t i = padding_zeros - 8; i > 0; i -= 8) {
		input.push_back(0);
	}

	// 附加最后64位的消息体长度
	for (int8_t shift = 64 - 8; shift >= 0; shift -= 8) {
		input.push_back((message_bits >> shift) & 0xFF);
	}
}

void SHA256::parse_message(std::string& input) {
	Block current_block;
	uint32_t word = 0;
	uint8_t processed_characters = 0;
	uint8_t processed_words = 0;

	for (const uint8_t& character : input) {
		word <<= 8;
		word += character;

		// 每拼接4个8位数据将得到1个32位数据字段
		if (++processed_characters == 4) {
			current_block.words[processed_words++] = word;
			word = processed_characters = 0;

			// 每拼接16个32位数据将得到1个512位数据块
			if (processed_words == 16) {
				message_blocks.push_back(current_block);
				processed_words = 0;
				current_block = {};
			}
		}
	}
}

// ======================================================
// Hash Computation.
// ======================================================

std::string SHA256::compute_hash() {
	uint32_t H[8] = { 0 };

	for (uint8_t i = 0; i < 8; i++) {
		H[i] = initial_hash_value[i];
	}

	for (const auto& block : message_blocks) {
		uint32_t a, b, c, d, e, f, g, h, temp1, temp2, W[64];

		// Prepare the message schedule.
		for (uint8_t i = 0; i <= 15; i++) {
			W[i] = block.words[i];
		}

		/*
			For i from w[16…63]:
			s0 = (w[i-15] rightrotate 7) xor (w[i-15] rightrotate 18) xor (w[i-15] rightshift 3)
			s1 = (w[i- 2] rightrotate 17) xor (w[i- 2] rightrotate 19) xor (w[i- 2] rightshift 10)
			w[i] = w[i-16] + s0 + w[i-7] + s1
		*/
		for (uint8_t i = 16; i <= 63; i++) {
			W[i] = W[i - 16] + lowerSigma0(W[i - 15]) + W[i - 7] + lowerSigma1(W[i - 2]);
		}

		// Initialize working variables.
		a = H[0];
		b = H[1];
		c = H[2];
		d = H[3];
		e = H[4];
		f = H[5];
		g = H[6];
		h = H[7];

		// Compression loop function.
		for (uint8_t i = 0; i < 64; i++) {
			temp1 = h + upperSigma1(e) + Choose(e, f, g) + round_constant[i] + W[i];
			temp2 = upperSigma0(a) + majority(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}

		// Compute intermediate hash value.
		H[0] = a + H[0];
		H[1] = b + H[1];
		H[2] = c + H[2];
		H[3] = d + H[3];
		H[4] = e + H[4];
		H[5] = f + H[5];
		H[6] = g + H[6];
		H[7] = h + H[7];
	}

	/* 每8位16进制数据显示补0 */
	std::stringstream hash_string;
	for (uint8_t i = 0; i < 8; ++i) {
		hash_string << setfill('0') << setw(8) << hex << H[i];
	}

	return hash_string.str();
}

// ======================================================
// Hashing functions and operators.
// ======================================================

uint32_t SHA256::RightRotate(uint32_t word, uint32_t positions) {
	return (word >> positions) | (word << (32 - positions));
}

uint32_t SHA256::Choose(uint32_t E, uint32_t F, uint32_t G ){
	return (E & F) ^ (~E & G);
}

uint32_t SHA256::majority(uint32_t A, uint32_t B, uint32_t C){
	return (A & B) ^ (A & C) ^ (B & C);
}

uint32_t SHA256::upperSigma0(uint32_t A) {
	return RightRotate(A, 2) ^ RightRotate(A, 13) ^ RightRotate(A, 22);
}

uint32_t SHA256::upperSigma1(uint32_t E) {
	return RightRotate(E, 6) ^ RightRotate(E, 11) ^ RightRotate(E, 25);
}

uint32_t SHA256::lowerSigma0(uint32_t x) {
	return RightRotate(x, 7) ^ RightRotate(x, 18) ^ (x >> 3);
}

uint32_t SHA256::lowerSigma1(uint32_t x) {
	return RightRotate(x, 17) ^ RightRotate(x, 19) ^ (x >> 10);
}

