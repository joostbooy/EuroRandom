#ifndef Disk_h
#define Disk_h

#include "sdio.h"
#include "ff.h"
#include "directory.h"
#include "entry.h"
#include "file.h"

class Disk {

public:
	Directory dir;
	Entry entry;
	File file;

	void init() {
		const int root = 0;

		dir.init(&fdir, root, &result);
		entry.init(&fdir, &fil_info, dir.path_ptr());
		file.init(&fil, dir.path_ptr(), &result);

		sdio.init();
	}

	bool mount() {
		if (!mounted()) {
			return f_mount(&fs, dir.root(), 1) == FR_OK;
		} else {
			return true;
		}
	}

	bool mounted() {
		return sdio.initialised();
	}

	bool detected() {
		return sdio.detected();
	}

	FRESULT last_result() {
		return result;
	}

	void reset() {
		dir.reset();
		dir.close();
		entry.reset();
		file.close();
	}

	void available_kb(uint32_t *total_blocks, uint32_t *free_blocks) {
		FATFS* fs_ptr = &fs;
		uint32_t free_clusters;

		result = f_getfree(dir.root(), &free_clusters, &fs_ptr);
		if (result == FR_OK) {
			*total_blocks = ((fs_ptr->n_fatent - 2) * fs_ptr->csize) / 2;
			*free_blocks = (free_clusters * fs_ptr->csize) / 2;
		}
	}

private:

	FATFS fs;
	DIR fdir;
	FIL fil;
	FILINFO fil_info;
	FRESULT result;
};

extern Disk disk;

#endif
