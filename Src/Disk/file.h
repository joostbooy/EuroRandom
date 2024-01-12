#ifndef File_h
#define File_h

#include "ff.h"
#include "stringBuilder.h"

class File {

public:

	enum Mode {
		OPEN_EXISTING	= 0x00,
		READ			= 0x01,
		WRITE			= 0x02,
		CREATE_NEW		= 0x04,	// Creates a new file, the function fails if the file is existing.
		CREATE_ALWAYS	= 0x08,	// Creates a new file, if the file is existing, it will be truncated and overwritten.
		OPEN_ALWAYS		= 0x10,	// Opens the file if it is existing. If not, a new file will be created.
		OPEN_APPEND		= 0x30	// Same as OPEN_ALWAYS except the read/write pointer is set end of the file.
	};

	void init(FIL* fil_, StringBuilder* dir_path_, FRESULT* res_) {
		fil = fil_;
		dir_path = dir_path_;
	}

	bool open(const char* path_, uint8_t mode = READ) {
		return f_open(fil, path_, mode) == FR_OK;
	}

	bool open(const char* dir, const char* name, uint8_t mode = READ) {
		return f_open(fil, path.write(dir, "/", name), mode) == FR_OK;
	}

	bool open_in_curr_dir(const char* name, uint8_t mode = READ) {
		path.write(dir_path->read(), "/", name);
		return f_open(fil, path.read(), mode) == FR_OK;
	}

	bool close() {
		return f_close(fil) == FR_OK;
	}

	bool sync() {
		return f_sync(fil) == FR_OK;
	}

	bool write(const void* data, uint32_t size, uint32_t* num_written = nullptr) {
		UINT bw;
		FRESULT res = f_write(fil, data, size, &bw);
		if (num_written) {
			*num_written = bw;
		}
		return (bw > 0) && (res == FR_OK);
	}

	bool read(void* data, uint32_t size, uint32_t* num_read = nullptr) {
		UINT br;
		FRESULT res = f_read(fil, data, size, &br);
		if (num_read) {
			*num_read = br;
		}
		return (br > 0) && (res == FR_OK);
	}

	bool end() {
		return f_eof(fil);
	}

	uint32_t position() {
		return f_tell(fil);
	}

	bool seek(uint32_t offset) {
		return f_lseek(fil, offset) == FR_OK;
	}

	bool advance(uint32_t num_bytes) {
		uint32_t pos = f_tell(fil) + num_bytes;
		return f_lseek(fil, pos) == FR_OK;
	}

	bool rewind() {
		return f_rewind(fil) == FR_OK;
	}

private:
	FIL* fil;
	StringBuilder* dir_path;
	StringBuilderBase<64>path;
};

#endif
