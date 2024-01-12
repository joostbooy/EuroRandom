#include "settings.h"
#include "disk.h"
#include "fileWriter.h"
#include "fileReader.h"

Settings settings;
FileWriter fileWriter;
FileReader fileReader;


bool Settings::save(const char* new_path) {
	path.write(new_path);
	if (!save()) {
		path.clear();
		return false;
	}
	return true;
}

bool Settings::save() {
	if (!path.length()) {
		return false;
	}

	fileWriter.start(&disk.file, path.read(), current_version());

	if (!fileWriter.write_ok()) {
		fileWriter.stop();
		return false;
	}

	return true;
};

bool Settings::load(const char* new_path) {
	init();	// also clears the path

	fileReader.start(&disk.file, new_path);

	if (!fileReader.read_ok()) {
		fileReader.stop();
		init();
		return false;
	}

	path.write(new_path);	// the new valid path
	return true;
};
