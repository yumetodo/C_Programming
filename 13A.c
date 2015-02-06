#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>//in gcc
#include <errno.h>//in gcc

#define LISTMAX 1000

typedef char * elementtype;

typedef struct {
	elementtype music[LISTMAX];
	int n;
} ListPlayer;
typedef struct _CMD{
	char cmd;
	int play_begin;
	int play_end;
	int d;
	char* search_string;
}CMD;

ListPlayer LP_init();
ListPlayer LP_addmusic(ListPlayer lp, elementtype music);
void LP_play(ListPlayer lp, int b, int e);
void LP_search(ListPlayer lp, char *buf);
void chomp(char *buf, int n);
/// <summary>終端文字を検出します。</summary>
/// <param name="character">判定する文字を指定します。</param>
/// <returns>EOFならEOF,\n\r\0はtrue,それ以外はfalseを返します。</returns>
int istermination(char character);

/// <summary>行の終わりまで空読みします。終端はistermination関数が判定します。</summary>
/// <param name="stream">ファイルポインタやstdinなどを指定します。</param>
/// <returns>EOFならEOF,それ以外は0を返します。</returns>
/// <seealso cref = "istermination" / >
int ignore_rest_of_line(FILE* stream);

/// <summary>標準入力から文字列を読み取ります。使用後はfreeが必要です。</summary>
/// <returns>文字列が入った動的確保されたメモリー空間へのポインターを返します。NULLのときは最初のcallocに失敗しています</returns>
char* new_string_getline_from_stdin(void);

/// <summary>標準入力から文字列を読み取ります。使用後はfreeが必要です。</summary>
/// <param name="numof_arrray">NULLではない場合は、最終的に確保された配列の要素数を返します</param>
/// <param name="str_len">NULLではない場合は、読み込んだ文字数を返します</param>
/// <param name="iseof">NULLではない場合は、EOFに遭遇したらtrue,それ以外はfalseを返します。</param>
/// <param name="str_len">NULLではない場合は、reallocに失敗したか、一行が4,194,311文字以上の文字列に遭遇するとtrue,それ以外はfalseを返します。</param>
/// <returns>文字列が入った動的確保されたメモリー空間へのポインターを返します。NULLのときは最初のcallocに失敗しています</returns>
char* new_string_getline_from_stdin2(size_t* numof_arrray, size_t* str_len, bool* iseof, bool* is_too_long_line);

/// <summary>標準入力やファイルストリームなどから文字列を読み取ります。使用後はfreeが必要です。</summary>
/// <param name="stream">ファイルポインタやstdinなどを指定します。</param>
/// <param name="numof_arrray">NULLではない場合は、最終的に確保された配列の要素数を返します</param>
/// <param name="str_len">NULLではない場合は、読み込んだ文字数を返します</param>
/// <param name="iseof">NULLではない場合は、EOFに遭遇したらtrue,それ以外はfalseを返します。</param>
/// <param name="str_len">NULLではない場合は、reallocに失敗したか、一行が4,194,311文字以上の文字列に遭遇するとtrue,それ以外はfalseを返します。</param>
/// <returns>文字列が入った動的確保されたメモリー空間へのポインターを返します。NULLのときは最初のcallocに失敗しています</returns>
char* new_string_getline(FILE* stream, size_t* numof_arrray, size_t* str_len, bool* iseof, bool* is_too_long_line);

/// <summary>文字列を解析してコマンドを実行する準備をする。</summary>
/// <param name="in_str">変換するchar型文字列</param>
/// <returns>CMD型の構造体を返します。in_strがNULLの時はすべての要素が0の状態で返却します。</returns>
CMD command_parser(char* in_str);
/// <summary>文字列をint型に変換する</summary>
/// <param name="in_str">変換するchar型文字列</param>
/// <param name="endptr">strtolが返す変換できなかった文字列の最初の要素へのポインター</param>
/// <param name="first_skip">数字が出るまで読み飛ばすかどうか</param>
/// <returns>その他:正常,-1:異常</returns>
int parseInt(char const * in_str, char* endptr, bool first_skip);


int parseInt(char const * in_str, char* endptr, bool first_skip){
	long t;
	unsigned int i;
	if (first_skip) for (i = 0; '\0' != in_str[i] && 0 == isdigit(in_str[i]); i++);//first_skipがtrueなら数字が出るまで読み飛ばす。
	errno = 0;
	t = strtol(&in_str[i], &endptr, 10);
	if (errno != 0 || in_str[0] == endptr[0] || t < INT_MIN || INT_MAX < t){
		return -1;
	}
	return (int)t;
}
int istermination(char character){
	if (EOF == character) return EOF;
	if ('\n' == character || '\r' == character || '\0' == character) return true;
	return false;
}
int ignore_rest_of_line(FILE* stream){
	char buf;
	int temp;
	do{
		buf = fgetc(stream);
	} while (false == (temp = istermination(buf)));
	if (EOF == temp){
		ungetc(buf, stream);//feofでEOF判定できるように
		return EOF;
	}
	return 0;
}
char* new_string_getline_from_stdin(void){
	bool is_too_long_line;
	char* return_str = new_string_getline(stdin, NULL, NULL, NULL, &is_too_long_line);
	if (NULL == return_str || is_too_long_line){
		free(return_str);
		return NULL;
	}
	return return_str;
}
char* new_string_getline_from_stdin2(size_t* numof_arrray, size_t* str_len, bool* iseof, bool* is_too_long_line){
	return new_string_getline(stdin, numof_arrray, str_len, iseof, is_too_long_line);
}
char* new_string_getline(FILE* stream, size_t* numof_arrray, size_t* str_len, bool* iseof, bool* is_too_long_line){
	/*
	戻り値：文字列が入った動的確保されたメモリー空間へのポインター
	エラー
	戻り値がNULL：最初のcallocに失敗
	iseofがtrue：EOFに遭遇（戻り値はEOFまでの文字列）
	is_too_long_line：reallocに失敗したか、一行が4,194,311文字以上の文字列に遭遇
	*/
	const size_t lim_len = 4194304 + 7;//コマンドプロンプトの最大長は8191、CentOS6では2621440、無限ループ防止
	const size_t numof_allocated_array_at_a_time = 10;//10個づつ確保する
	size_t i = 0, j, numof_return_arrray = numof_allocated_array_at_a_time;
	if (NULL != iseof) *iseof = false;
	if (NULL != is_too_long_line) *is_too_long_line = false;
	char* return_str = (char*)calloc(numof_allocated_array_at_a_time, sizeof(char));
	if (NULL == return_str) return NULL;

	char buf1;
	char* buf;
	int temp_eof;
	do{
		for (j = 0; i < lim_len && j < numof_allocated_array_at_a_time; i++, j++){
			buf1 = fgetc(stream);//バッファに一文字読み込む
			if (false != (temp_eof = istermination(buf1))){//do-whileループを抜けるか判定
				if (EOF == temp_eof){
					ungetc(buf1, stream);//feofでEOF判定できるように
					if (NULL != iseof) *iseof = true;
				}
				memset(&return_str[i], '\0', numof_allocated_array_at_a_time - j);
				break;//まずfor文を抜ける
			}
			return_str[i] = buf1;//バッファから、返却する文字列に、コピー
		}
		if (NULL != str_len) str_len[0] = i;
		if (temp_eof) break;//do-whileループを抜ける
		const size_t temp = numof_return_arrray + numof_allocated_array_at_a_time;
		if (temp < lim_len && NULL != (buf = (char*)realloc(return_str, temp * sizeof(char)))){
			return_str = buf;//正常処理
			numof_return_arrray = temp;
			return_str[numof_return_arrray - 1] = '\0';//予防措置。デバッガーで文字が追えるように
		}
		else{
			if (NULL != is_too_long_line) *is_too_long_line = true;
			return_str[numof_return_arrray - 1] = '\0';//読み込み済みの最後の一字を消す
			if (NULL != str_len) str_len[0]--;//文字数も減る
			if (EOF == ignore_rest_of_line(stream) && NULL != iseof) *iseof = true;
			break;//do-whileループを抜ける
		}
	} while (i < lim_len);
	if (NULL != numof_arrray) *numof_arrray = numof_return_arrray;
	return return_str;
}
CMD command_parser(char* in_str){
	CMD command = { 0 };
	if (NULL == in_str) return command;
	elementtype endptr1, endptr2;

	command.play_begin = parseInt(in_str, endptr1, false);
	if (command.play_begin < 1) command.play_begin = 1;
	if ('.' == endptr1[0]){
		command.play_end = parseInt(endptr1, endptr2, true);
		if (command.play_end < 1) command.play_end = 1;
	}
	else{
		endptr2 = endptr1;
	}
	if ('/' != endptr2[0]){
		command.d = parseInt(endptr2, NULL, true);
		command.search_string = NULL;
	}
	else{
		command.search_string = endptr2;
	}
	command.cmd = endptr2[0];
	return command;
}
int main(void) {
	ListPlayer myplayer = LP_init();
	int b, e, d, bi, ci;
	char buf[1024], cmdbuf[16];
	
	
	while(1) {
		char *music = new_string_getline_from_stdin();
		if (NULL == music) continue;
		if ('.' == music[0]) break;
		myplayer = LP_addmusic(myplayer, music);
	}
	
	/* command parser */
	while(1){
		b = e = d = 0;
		char* cmd_buf = new_string_getline_from_stdin();
		if (NULL == cmd_buf) continue;
		CMD command = command_parser(cmd_buf);
		const char cmd = command.cmd;
		/* command execution */
		if (cmd == 'p') {
			LP_play(myplayer, command.play_begin, command.play_end);
		} else if (cmd == '/') {
			LP_search(myplayer, command.search_string);
		} else if (cmd == '.') {
			break;
		}
	}
	
	return 0;
}

void LP_search(ListPlayer lp, char *buf) {
  printf("LP_search : %s size %d\n", buf, (int)strlen(buf));
  /*
  Question B
  */

}

ListPlayer LP_addmusic(ListPlayer lp, elementtype music) {
	int j;
	
	if(lp.n >= LISTMAX)
	  return lp;
	
	j = 1;
	while(j <= lp.n) {
	  if(strcmp(lp.music[j], music) > 0) {
	    elementtype tmp;
	    tmp = lp.music[j];
	    lp.music[j] = music;
	    music = tmp;
	  }
	  j += 1;
	}
	
	lp.music[j] = music;
	lp.n += 1;
	//for(j = 0; j < lp.n; j += 1)
	//printf("music[%d] : %s\n", j, lp.music[j]);
	
	return lp;
}

void LP_play(ListPlayer lp, int play_begin, int play_end) {
	play_begin--;
	play_end--;//配列は0から始まる
	if(play_end < play_begin)
	  play_end = play_begin;
	int i = (play_begin < 0)? 0 : play_begin;
	for (i = play_begin; i <= play_end; i++){
		printf("%s\n", lp.music[i]);
	}
}

ListPlayer LP_init() {
  ListPlayer lp;
  lp.n = 0/*LISTMAX - 1*/;
  return lp;
}

void chomp(char *buf, int n)  {
  int i;
  for(i = 0; i < n; i += 1) {
    if(buf[i] == '\n') {
      buf[i] = '\0';
      break;
    }
  }
}
