#ifndef FileWriter_h
#define FileWriter_h

// based on westlicht's fileWriter

#include "file.h"
#include "hash.h"

class FileWriter {

public:

	bool write_ok() {
		return write_ok_;
	}

	void start(File *file, const char* path, uint32_t version) {
		buff_pos = 0;

		file_ = file;
		write_ok_ = file_->open(path, File::WRITE | File::OPEN_ALWAYS);

		hash_.init();

		if (write_ok_) {
			write(version);
		}
	}

	void stop() {
		// send remaing buffer data
		if (write_ok_) {
			write_ok_ = send_buffer();
		}

		if (write_ok_) {
			uint32_t hash = hash_.read();
			write_ok_ = file_->write(&hash, sizeof(hash));
		}

		if (!write_ok_) {
			file_->close();
			return;
		}

		write_ok_ = file_->close();
	}

	template<typename T>
	void write(T &data) {
		write_buffer(&data, sizeof(T));
		hash_.write(&data, sizeof(T));
	}

private:
	static const int kBufferSize = 512;
	uint8_t buffer[kBufferSize];
	uint32_t buff_pos;

	File *file_;
	Hash hash_;
	bool write_ok_;


	void write_buffer(void *data, uint32_t size) {
		uint8_t *data_ = reinterpret_cast<uint8_t *>(data);

		while (write_ok_ && (size > 0)) {
			if (buff_pos < kBufferSize) {
				buffer[buff_pos++] = *data_++;
				--size;
			} else {
				write_ok_ = send_buffer();
			}
		}
	}

	bool send_buffer() {
		uint32_t size = buff_pos;
		buff_pos = 0;
		return file_->write(buffer, size);
	}

};

#endif
