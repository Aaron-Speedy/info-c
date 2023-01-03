enum {
	T_IDENTIFIER, T_INTLIT, 
	T_LCURLY, T_RCURLY, 
	T_LPAREN, T_RPAREN, 
	T_SEMICOLON, 
	T_INT, T_RETURN
};

typedef struct Token {
	int type; 
	struct Token *next; 
	
	union {
		int intValue; 
		char *stringValue; 
	}; 
} Token; 

Token initToken(); 
Token *genTokens(char *input); 
void printTokens(Token token); 
