#ifndef DiskUtils_h
#define DiskUtils_h

#include "disk.h"
#include "stringBuilder.h"

class DiskUtils {

public:

	static const char* result_text(FRESULT result) {
		switch (result) {
		case FR_OK:						return "OK";
		case FR_DISK_ERR:				return "DISK_ERR";
		case FR_INT_ERR:				return "INT_ERR";
		case FR_NOT_READY:				return "NOT_READY";
		case FR_NO_FILE:				return "NO_FILE";
		case FR_NO_PATH:				return "NO_PATH";
		case FR_INVALID_NAME:			return "INVALID_NAME";
		case FR_DENIED:					return "DENIED";
		case FR_EXIST:					return "EXISTS";
		case FR_INVALID_OBJECT:			return "INVALID_OBJECT";
		case FR_WRITE_PROTECTED:		return "WRITE_PROTECTED";
		case FR_INVALID_DRIVE:			return "INVALID_DRIVE";
		case FR_NOT_ENABLED:			return "NOT_ENABLED";
		case FR_NO_FILESYSTEM:			return "NO_FILESYSTEM";
		case FR_MKFS_ABORTED:			return "MKFS_ABORTED";
		case FR_TIMEOUT:				return "TIMEOUT";
		case FR_LOCKED:					return "LOCKED";
		case FR_NOT_ENOUGH_CORE:		return "NOT_ENOUGH_CORE";
		case FR_TOO_MANY_OPEN_FILES:	return "TOO_MANY_OPEN_FILES";
		case FR_INVALID_PARAMETER:		return "INVALID_PARAMETER";
		default:						return "UNKNOWN";
		}
	}

	static const char* user_result_text(FRESULT result) {
		switch (result) {
		case FR_WRITE_PROTECTED:		return "CARD IS WRITE PROTECTED";
		case FR_NO_FILESYSTEM:			return "CARD NOT FAT FORMATTED";
		case FR_LOCKED:					return "CARD IS LOCKED";
		case FR_DISK_ERR:				return "CARD NOT FOUND";
		default:						return "FAT ERROR";
		}
	}

private:

};

#endif
