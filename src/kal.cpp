#include <string>
#include <cctype>
#include <cstdlib>

// a token is one if these if known, otherwise an int in [0, 255]
enum Token {
	token_eof = -1,
	token_def = -2, token_extern = -3,
	token_identifier = -4, token_number = -5
};

static std::string Identifier; // used if these is a token_identifier
static double NumVal; // used if there is a token_number

// get_next_token - get the next token from stdin
static int get_next_token() {
	static int last_char = ' ';

	while (isspace(last_char)) {
		last_char = getchar();

		// handle identifiers and control structures
		if (isalpha(last_char)) { // last_char in ([a-zA-Z]|[0-9])*
			Identifier = last_char;

			while(isalnum(last_char = getchar())) {
				Identifier += last_char; 
			}

			if (Identifier == "def") {
				return token_def;
			}

			if (Identifier == "external") {
				return token_extern;
			}

			return token_identifier;
		}

		// handle numbers
		if (isdigit(last_char) || last_char == '.') {
			std::string number;

			do {
				number += last_char;
				last_char = getchar();
			} while (isdigit(last_char) || last_char == '.');

			NumVal = strtod(number.c_str(), 0);

			return token_identifier;
		}

		// handle comments
		if (last_char == '#') {
			do last_char = getchar();
			while (last_char != EOF && last_char != '\n' && last_char != '\r');

			if (last_char != EOF) {
				return get_next_token();
			}
		}
	}
}