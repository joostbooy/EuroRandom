#ifndef Settings_h
#define Settings_h

#include "stringBuilder.h"

class Settings {

public:

	void init() {

	}


	// save & load
	bool save();
	bool save(const char* new_path);
	bool load(const char* new_path);

	const char* read_path() {
		return path.read();
	}

	bool has_valid_path() {
		return path.length() > 0; // && StringUtils::is_equal(file_name.read(), song.name());
	}

	uint32_t current_version() {
		return 0;
	}

private:
	StringBuilderBase<63>path;
};

extern Settings settings;

#endif
