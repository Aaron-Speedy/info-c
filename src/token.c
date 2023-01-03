#include "token.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define ISDIGIT(a) ((a) >= '0' && (a) <= '9')
#define ISALPHA(a) (((a) | 32) >= 'a' && ((a) | 32) <= 'z')
#define ISWHITESPACE(a) ((a) == ' ' || (a) == '\t' || (a) == '\r' || (a) == '\n' || (a) == '\v' || (a) == '\f')
#define ISGRAPHICCHAR(a) ((a) == '{' || (a) == '}' || (a) == '(' || (a) == ')' || (a) == ';'

const void intLit(char **str, Token *token) {
	char *end; 
	for(size_t i = 1; i < strlen(*str); i++) {
		if(!ISDIGIT(*str[i])) {token->type=T_INTLIT; end = *str+i-1; token->intValue=strtol(*str, &end, 10); *str=end+1; break; }
	}
}
const void keywordAndIdent(char **str, Token *token) {
	size_t size = 0;  
	for(size_t i = 1; i < strlen(*str); i++) {
		if(!ISALPHA((*str)[i]) && !ISDIGIT((*str)[i]) && (*str)[i] != '_') {size = i; break; } 
	}
	char *substr = malloc(size);
	strncpy(substr, *str, size);
	if(strcmp(substr, "int") == 0) token->type=T_INT;
	else if(strcmp(substr, "return") == 0) token->type=T_RETURN;
	else {token->type=T_IDENTIFIER; token->stringValue=substr;}
	*str += size;
}

const void graphicChar(char **str, Token *token) { // This wont work later and the name will have to be changed but it's fine for now
	const char words[] = {'{', '}', '(', ')', ';'}; 
	const char gcTokens[] = {T_RCURLY, T_LCURLY, T_RPAREN, T_LPAREN, T_SEMICOLON}; 
	for(size_t i = 0; i < sizeof(words); i++) {
		if(**str == words[i]) {token->type=gcTokens[i]; break; }
	}
	*str += 1; 
}

const int genSingleToken(char **str, Token *token) {
startGenSingleToken:
	if(ISWHITESPACE((*str)[0])) {*str += 1; goto startGenSingleToken; } 
	if(ISDIGIT((*str)[0])) {intLit(str, token); return 1; } 
	if(ISALPHA((*str)[0]) || (*str)[0] == '_') {keywordAndIdent(str, token); return 1; } 
	if(ISGRAPHICCHAR((*str)[0]))) {graphicChar(str, token); return 1; } // This seems like a bad idea
	return 0; 
}

const char *tokenStrings[] = {
	"IDENTIFIER", "INTLIT", 
	"LCURLY", "RCURLY", 
	"LPAREN", "RPAREN", 
	"SEMICOLON", 
	"INT", "RETURN"
}; 

void printTokens(Token token) {
	while(1) {
		printf("%s   ", tokenStrings[token.type]);
		if(token.next == NULL) break; 
		token = *token.next; 
	}
	printf("\n"); 
}

Token *genTokens(char *str) {
	Token *start = malloc(sizeof(Token)); 
	Token *current = start; 
	while(genSingleToken(&str, current)) {
		current->next=malloc(sizeof(Token)); 
		current=current->next; 
	}
	printTokens(*start);
}
