#ifndef Utils_h
#define Utils_h

class Utils {

public:

	static int clip(int min, int max, int value) {
		return value > max ? max : (value < min ? min : value);
	}

private:

};

#endif
