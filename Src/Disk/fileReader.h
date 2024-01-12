#ifndef FileReader_h
#define FileReader_h

// based on westlicht's fileReader

#include "file.h"
#include "hash.h"

class FileReader {

public:

	bool read_ok() {
		return read_ok_;
	}

	uint32_t version() {
		return version_;
	}

	void start(File *file, const char* path) {
		num_read = 0;
		num_readable = 0;

		file_ = file;
		read_ok_ = file_->open(path);

		hash_.init();

		if (read_ok_) {
			read(version_);
		}
	}

	void stop() {
		if (read_ok_) {
			uint32_t hash = 0;
			read_buffer(&hash, sizeof(hash));
			read_ok_ = (hash == hash_.read());
		}

		if (!read_ok_) {
			file_->close();
			return;
		}

		read_ok_ = file_->close();
	}

	template<typename T>
	void read(T &data) {
		read_buffer(&data, sizeof(T));
		hash_.write(&data, sizeof(T));
	}

	template<typename ReadT, typename T>
	void read_as(T &data) {
		ReadT temp = 0;
		read(temp);
		data = temp;
	}

	void skip(uint32_t size) {
		uint8_t dummy = 0;
		while (size--) {
			read(dummy);
		}
	}

private:
	static const int kBufferSize = 512;
	uint8_t buffer[kBufferSize];

	File *file_;
	bool read_ok_;
	uint32_t num_read = 0;
	uint32_t num_readable = 0;
	uint32_t version_ = 0;

	Hash hash_;

	void read_buffer(void *data, uint32_t size) {
		uint8_t *data_ = reinterpret_cast<uint8_t *>(data);

		while (read_ok_ && (size > 0)) {
			if (num_read < num_readable) {
				*data_++ = buffer[num_read++];
				--size;
			} else {
				read_ok_ = fill_buffer(size);
			}
		}
	}

	bool fill_buffer(uint32_t requested_size) {
		num_read = 0;
		if (file_->read(buffer, kBufferSize, &num_readable)) {
			return (num_readable >= requested_size) || (num_readable >= kBufferSize);
		}
		return false;
	}

};

#endif
