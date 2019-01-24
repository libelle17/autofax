#define HAVE_NCURSESW_NCURSES_H
#include "kons.h"
#include "efdr.h"
#ifdef HAVE_SETLOCALE
#include <locale.h>
#endif
#include <unistd.h> // getcwd
#include <sys/stat.h> // struct stat
#include <dirent.h>
#include <cctype> // isdigit
#include <errno.h> // errno
#include <iostream> // cout
#include <algorithm> // sort
#include <fstream> // ofstream
using namespace std;
extern struct hotkst hk[];
const char* const NUMBER_FMT{"%4d. %s"};
// #define isChar(c)               ((int)(c) >= 0 && (int)(c) < KEY_MIN)
int isChar(const int c)
{
	return c>=0 && c<KEY_MIN;
}
int isSonder(const unsigned char was)
{
	switch (was) {
		case 194:
		case 195:
		case 197:
			return 1;
		case 226: // für €
			return 2;
	}
	return 0;
}


void chtstr::gibaus() const
{ 
	for(size_t i=0;i<len;i++)
		cout<<inh[i]<<" ";
	cout<<endl;
}
// chtstr::chtstr(size_t len):len(len) { inh=new chtype[len]; }

// GSchade 17.11.18; s. cdk.h
// einbauart akteinbart;

//ALL_SCREENS *all_screens;
vector<SScreen*> all_screens;
vector<GObj*> all_objects;

/*
 * Return an integer like 'floor()', which returns a double.
 */
int floorCDK(double value)
{
   int result = (int)value;
   if (result > value)		/* e.g., value < 0.0 and value is not an integer */
      result--;
   return result;
}

/*
 * Return an integer like 'ceil()', which returns a double.
 */
int ceilCDK(double value)
{
   return -floorCDK(-value);
}

/*
 * This beeps then flushes the stdout stream.
 */
void Beep(void)
{
   beep();
   fflush(stdout);
}

/*
 * If the dimension is a negative value, the dimension will be the full
 * height/width of the parent window - the value of the dimension.  Otherwise,
 * the dimension will be the given value.
 */
int setWidgetDimension(int parentDim, int proposedDim, int adjustment)
{
	int dimension = 0;
	/* If the user passed in FULL, return the parent's size. */
	if ((proposedDim == FULL) || (!proposedDim)) {
		dimension = parentDim;
	} else {
		/* If they gave a positive value, return it. */
		if (proposedDim >= 0) {
			if (proposedDim >= parentDim)
				dimension = parentDim;
			else
				dimension = (proposedDim + adjustment);
		} else {
			/*
			 * If they gave a negative value, then return the
			 * dimension of the parent plus the value given.
			 */
			dimension = parentDim + proposedDim;
			/* Just to make sure. */
			if (dimension < 0)
				dimension = parentDim;
		}
	}
	return dimension;
}

static int encodeAttribute(const char *string, int from, chtype *mask)
{
	int pair = 0;
	*mask = 0;
	switch (string[from + 1]) {
		case 'B':
			*mask = A_BOLD;
			break;
		case 'D':
			*mask = A_DIM;
			break;
		case 'K':
			*mask = A_BLINK;
			break;
		case 'R':
			*mask = A_REVERSE;
			break;
		case 'S':
			*mask = A_STANDOUT;
			break;
		case 'U':
			*mask = A_UNDERLINE;
			break;
	}
	if (*mask) {
		from++;
	} else {
		int digits;
		pair = 0;
		for (digits = 1; digits <= 3; ++digits) {
			if (!isdigit ((unsigned char)string[1 + from]))
				break;
			pair *= 10;
			pair += DigitOf(string[++from]);
		}
#ifdef HAVE_START_COLOR
#define MAX_PAIR (int) (A_COLOR / (((~A_COLOR) << 1) & A_COLOR))
		if (pair > MAX_PAIR )
			pair = MAX_PAIR;
		*mask = (chtype)COLOR_PAIR(pair);
#else
		*mask = A_BOLD;
#endif
	}
	return from;
} // static int encodeAttribute(const char *string, int from, chtype *mask)

/*
 * This function takes a character string, full of format markers
 * and translates them into a chtype * array. This is better suited
 * to curses, because curses uses chtype almost exclusively
 */
// highinr G.Schade 26.9.18
chtstr::chtstr(const char *string, int *to, int *align, const int highinr/*=0*/)
{
	//	chtype *result = 0;
	inh=0;
	chtype attrib,lastChar,mask;
	(*to) = 0;
	*align = LEFT;
	if (string && *string) {
		/*int */len = (int)strlen(string);
		int pass;
		int used = 0;
		/*
		 * We make two passes because we may have indents and tabs to expand, and
		 * do not know in advance how large the result will be.
		 */
		for (pass = 0; pass < 2; pass++) {
			int insideMarker;
			int from;
			int adjust;
			int start;
			int x = 3;
			if (pass) {
				//				if ((result = typeMallocN(chtype, used + 2)) == 0)
				if (!(inh=new chtype[used+2])) {
					used = 0;
					break;
				}
			}
			adjust = 0;
			attrib = A_NORMAL;
			start = 0;
			used = 0;
			/* Look for an alignment marker.  */
			if (*string == L_MARKER) {
				if (string[1] == 'C' && string[2] == R_MARKER) {
					(*align) = CENTER;
					start = 3;
				} else if (string[1] == 'R' && string[2] == R_MARKER) {
					(*align) = RIGHT;
					start = 3;
				} else if (string[1] == 'L' && string[2] == R_MARKER) {
					start = 3;
				} else if (string[1] == 'B' && string[2] == '=') {
					/* Set the item index value in the string.       */
					if (inh) {
						inh[0] = ' ';
						inh[1] = ' ';
						inh[2] = ' ';
					}
					/* Pull out the bullet marker.  */
					while (string[x] != R_MARKER && string[x]) {
						if (inh)
							inh[x] = (chtype)string[x] | A_BOLD;
						x++;
					}
					adjust = 1;
					/* Set the alignment variables.  */
					start = x;
					used = x;
				} else if (string[1] == 'I' && string[2] == '=') {
					from = 2;
					x = 0;
					while (string[++from] != R_MARKER && string[from]) {
						if (isdigit ((unsigned char)string[from])) {
							adjust = (adjust * 10) + DigitOf(string[from]);
							x++;
						}
					}
					start = x + 4;
				}
			}
			while (adjust-- > 0) {
				if (inh)
					inh[used] = ' ';
				used++;
			}
			/* Set the format marker boolean to false.  */
			insideMarker = FALSE;
			// GSchade 25.9.18
			//size_t pos=0;
			/* Start parsing the character string.  */
			for (from = start; from < (int)len; from++) {
				/* Are we inside a format marker?  */
				if (!insideMarker) {
					if (string[from] == L_MARKER
							&& (string[from + 1] == '/'
								|| string[from + 1] == '!'
								|| string[from + 1] == '#'))
					{
						insideMarker = TRUE;
					} else if (string[from] == '\\' && string[from + 1] == L_MARKER) {
						from++;
						if (inh)
							inh[used] = (unsigned char)string[from] | attrib;
						used++;
						from++;
					} else if (string[from] == '\t') {
						do {
							if (inh)
								inh[used] = ' ';
							used++;
						}
						while (used & 7);
					} // else if (inh && !strchr("ö",string[from])) KLA inh[used++]=(unsigned char)'o'|attrib;
					// GSchade 25.9.18
					/*
						 else if (strchr("äöüÄÖÜß",string[from])) {
						 printf("from: %i, string[from]: %i\n",from,(int)string[from]+256);
					//if (inh) inh[used]=(unsigned char)'z'|attrib; used++;
					if (inh) inh[used]=(unsigned char)-61|attrib; used++;
					if (!strchr("ä",string[from])) { if (inh) inh[used]=(unsigned char)164-256|attrib; used++; }
					else if (!strchr("ö",string[from])) { if (inh) inh[used]=(unsigned char)182-256|attrib; used++; }
					else if (!strchr("ü",string[from])) { if (inh) inh[used]=(unsigned char)188-256|attrib; used++; }
					else if (!strchr("Ä",string[from])) { if (inh) inh[used]=(unsigned char)132|attrib; used++; }
					else if (!strchr("Ö",string[from])) { if (inh) inh[used]=(unsigned char)150|attrib; used++; }
					else if (!strchr("Ü",string[from])) { if (inh) inh[used]=(unsigned char)156|attrib; used++; }
					else if (!strchr("ß",string[from])) { if (inh) inh[used]=(unsigned char)159|attrib; used++; }
					}
					 */
					// Ende GSchade 25.9.18
					else {
						if (inh) {
							// GSchade 26.9.18
							if (used==highinr-1) {
								inh[used] = (unsigned char)string[from] | attrib|COLOR_PAIR(1);
							} else {
								// Ende GSchade 
								inh[used] = (unsigned char)string[from] | attrib;
							}
						}
						used++;
					}
				} else {
					switch (string[from]) {
						case R_MARKER:
							insideMarker = 0;
							break;
						case '#':
							{
								lastChar = 0;
								switch (string[from + 2]) {
									case 'L':
										switch (string[from + 1]) {
											case 'L':
												lastChar = ACS_LLCORNER;
												break;
											case 'U':
												lastChar = ACS_ULCORNER;
												break;
											case 'H':
												lastChar = ACS_HLINE;
												break;
											case 'V':
												lastChar = ACS_VLINE;
												break;
											case 'P':
												lastChar = ACS_PLUS;
												break;
										}
										break;
									case 'R':
										switch (string[from + 1]) {
											case 'L':
												lastChar = ACS_LRCORNER;
												break;
											case 'U':
												lastChar = ACS_URCORNER;
												break;
										}
										break;
									case 'T':
										switch (string[from + 1]) {
											case 'T':
												lastChar = ACS_TTEE;
												break;
											case 'R':
												lastChar = ACS_RTEE;
												break;
											case 'L':
												lastChar = ACS_LTEE;
												break;
											case 'B':
												lastChar = ACS_BTEE;
												break;
										}
										break;
									case 'A':
										switch (string[from + 1]) {
											case 'L':
												lastChar = ACS_LARROW;
												break;
											case 'R':
												lastChar = ACS_RARROW;
												break;
											case 'U':
												lastChar = ACS_UARROW;
												break;
											case 'D':
												lastChar = ACS_DARROW;
												break;
										}
										break;
									default:
										if (string[from + 1] == 'D' &&
												string[from + 2] == 'I')
											lastChar = ACS_DIAMOND;
										else if (string[from + 1] == 'C' &&
												string[from + 2] == 'B')
											lastChar = ACS_CKBOARD;
										else if (string[from + 1] == 'D' &&
												string[from + 2] == 'G')
											lastChar = ACS_DEGREE;
										else if (string[from + 1] == 'P' &&
												string[from + 2] == 'M')
											lastChar = ACS_PLMINUS;
										else if (string[from + 1] == 'B' &&
												string[from + 2] == 'U')
											lastChar = ACS_BULLET;
										else if (string[from + 1] == 'S' &&
												string[from + 2] == '1')
											lastChar = ACS_S1;
										else if (string[from + 1] == 'S' &&
												string[from + 2] == '9')
											lastChar = ACS_S9;
								}
								if (lastChar) {
									adjust = 1;
									from += 2;
									if (string[from + 1] == '(')
										/* Check for a possible numeric modifier.  */
									{
										from++;
										adjust = 0;
										while (string[++from] != ')' && string[from]) {
											if (isdigit((unsigned char)string[from])) {
												adjust =(adjust * 10) + DigitOf(string[from]);
											}
										}
									}
								}
								for (x = 0; x < adjust; x++) {
									if (inh)
										inh[used] = lastChar | attrib;
									used++;
								}
								break;
							}
						case '/':
							from = encodeAttribute(string, from, &mask);
							attrib = attrib | mask;
							break;
						case '!':
							from = encodeAttribute(string, from, &mask);
							attrib = attrib & ~mask;
							break;
					}
				}
			}
			if (inh) {
				inh[used] = 0;
				inh[used + 1] = 0;
			}
			/*
			 * If there are no characters, put the attribute into the
			 * the first character of the array.
			 */
			if (!used && inh) {
				inh[0] = attrib;
			}
		}
		*to = used;
	} else {
		/*
		 * Try always to return something; otherwise lists of chtype strings
		 * would get a spurious null pointer whenever there is a blank line,
		 * and CDKfreeChtypes() would fail to free the whole list.
		 */
		//		inh = typeCallocN(chtype, 1);
		inh=new chtype[1];
	}
	return /*result*/;
} // chtstr::chtstr(const char *string, int *to, int *align, const int highinr/*=0*/)

/*
 * This returns a pointer to char * of a chtype *
 * Formatting codes are omitted.
 */
char *chtstr::chtype2Char()
{
	if (inh) {
		int len = chlen(inh);
		if (ch) delete[] ch;
		if ((ch = new char[len+1])) {
			for (int x = 0; x < len; x++) {
				ch[x] = (char)(unsigned char)inh[x];
			}
			ch[len] = '\0';
		}
	}
	return ch;
}


/*
 * This determines the length of a chtype string
 */
int chlen(const chtype *string)
{
	int result = 0;
	if (string) {
		while (string[result])
			result++;
	}
	return (result);
}

/*
 * This takes a string, a field width and a justification type
 * and returns the adjustment to make, to fill
 * the justification requirement.
 */
int justifyString(int boxWidth, int mesgLength, int justify)
{
	/*
	 * Make sure the message isn't longer than the width.
	 * If it is, return 0.
	 */
	if (mesgLength >= boxWidth)
		return (0);
	/* Try to justify the message.  */
	if (justify == LEFT)
		return (0);
	if (justify == RIGHT)
		return boxWidth - mesgLength;
	if (justify == CENTER)
		return ((int)((boxWidth - mesgLength) / 2));
	return (justify);
}

/*
 * This takes an x and y position and realigns the values iff they sent in
 * values like CENTER, LEFT, RIGHT, ...
 */
void alignxy(WINDOW *window, int *xpos, int *ypos, int boxWidth, int boxHeight)
{
	int first, gap, last;
	first = getbegx(window);
	last = getmaxx(window);
	if ((gap = (last - boxWidth)) < 0)
		gap = 0;
	last = first + gap;
	switch (*xpos) {
		case LEFT:
			(*xpos) = first;
			break;
		case RIGHT:
			(*xpos) = first + gap;
			break;
		case CENTER:
			(*xpos) = first + (gap / 2);
			break;
		default:
			if ((*xpos) > last)
				(*xpos) = last;
			else if ((*xpos) < first)
				(*xpos) = first;
			break;
	}
	first = getbegy(window);
	last = getmaxy(window);
	if ((gap =(last - boxHeight)) < 0)
		gap = 0;
	last = first + gap;

	switch (*ypos) {
		case TOP:
			(*ypos) = first;
			break;
		case BOTTOM:
			(*ypos) = first + gap;
			break;
		case CENTER:
			(*ypos) = first +(gap / 2);
			break;
		default:
			if ((*ypos) > last) {
				(*ypos) = last;
			}
			else if ((*ypos) < first) {
				(*ypos) = first;
			}
			break;
	}
}

/*
 * This sets a string to the given character.
 */
void cleanChar(char *s, int len, char character)
{
	if (s) {
		int x;
		for (x = 0; x < len; x++) {
			s[x] = character;
		}
		s[--x] = '\0';
	}
}

/*
 * This writes out a chtype * string.
 */
void writeChtype(WINDOW *window,
		int xpos,
		int ypos,
		const chtype *const string,
		int align,
		int start,
		int end)
{
	writeChtypeAttrib(window, xpos, ypos, string, A_NORMAL, align, start, end);
}

/*
 * This writes out a chtype * string * with the given attributes added.
 */
void writeChtypeAttrib(WINDOW *window,
		int xpos,
		int ypos,
		const chtype *const string,
		chtype attr,
		int align,
		int start,
		int end)
{
	int display;
	/* *INDENT-EQLS* */
	int diff=end-start;

	if (align == HORIZONTAL) {
		/* Draw the message on a horizontal axis. */
		display = MINIMUM(diff, getmaxx(window) - xpos);
		int altumlz{0};
		for (int x = 0; x < display; x++) {
			// GSchade 25.9.18
			const int wieSonder{isSonder(string[x+start])};
			if (1&&wieSonder) { // ((int)(unsigned char)string[x+start]==194||(int)(unsigned char)string[x+start]==195||(int)(unsigned char)string[x+start]==226))
				//			printf("Buchstabe: %c %i\r\n",(unsigned char)string[x+start], (int)(unsigned char)string[x+start]);
				char ausg[6]{0}; // mindestens 4
				for(int i=0;i<wieSonder+1;i++) {
					ausg[i]=string[x+start+i];
				}
//				const chtype attrib=COLOR_PAIR(2)|A_REVERSE;//A_REVERSE|COLOR_GREEN;
//				printf("String: %s, Farbe: %lu\n\r",ausg,attrib/*window->_attrs*/);
				wattron(window,string[x+start]); 
				mvwprintw(window,ypos,xpos+x-altumlz,"%s",ausg);
				wattroff(window,string[x+start]); 
				x++;
				altumlz+=wieSonder;
			} else {
//				printf("Buchstabe: %c, Farbe: %lu\n\r",(unsigned char)string[x+start],attr);
				(void)mvwaddch(window, ypos, xpos + x-altumlz, string[x + start] |attr);
			}
		}
	} else {
		/* Draw the message on a vertical axis. */
		display = MINIMUM(diff, getmaxy(window) - ypos);
		for (int x = 0; x < display; x++) {
			(void)mvwaddch(window, ypos + x, xpos, string[x + start] | attr);
		}
	}
} // void writeChtypeAttrib(

/*
 * This draws a box with attributes and lets the user define
 * each element of the box.
 */
void attrbox(WINDOW *win,
		chtype tlc,
		chtype trc,
		chtype blc,
		chtype brc,
		chtype horz,
		chtype vert,
		chtype attr)
{
	/* *INDENT-EQLS* */
	int x1       = 0;
	int y1       = 0;
	int y2       = getmaxy(win) - 1;
	int x2       = getmaxx(win) - 1;
	int count    = 0;

	/* Draw horizontal lines. */
	if (horz) {
		(void)mvwhline(win, y1, 0, horz | attr, getmaxx(win));
		(void)mvwhline(win, y2, 0, horz | attr, getmaxx(win));
		count++;
	}

	/* Draw vertical lines. */
	if (vert) {
		(void)mvwvline(win, 0, x1, vert | attr, getmaxy(win));
		(void)mvwvline(win, 0, x2, vert | attr, getmaxy(win));
		count++;
	}

	/* Draw in the corners. */
	if (tlc) {
		(void)mvwaddch(win, y1, x1, tlc | attr);
		count++;
	}
	if (trc) {
		(void)mvwaddch(win, y1, x2, trc | attr);
		count++;
	}
	if (blc) {
		(void)mvwaddch(win, y2, x1, blc | attr);
		count++;
	}
	if (brc) {
		(void)mvwaddch(win, y2, x2, brc | attr);
		count++;
	}
	if (count) {
		wrefresh(win);
	}
} // void attrbox(

/*
 * This draws a shadow around a window.
 */
void drawShadow(WINDOW *shadowWin)
{
	if (shadowWin) {
		int x_hi = getmaxx(shadowWin) - 1;
		int y_hi = getmaxy(shadowWin) - 1;

		/* Draw the line on the bottom. */
		(void)mvwhline(shadowWin, y_hi, 1, ACS_HLINE | A_DIM, x_hi);

		/* Draw the line on the right. */
		(void)mvwvline(shadowWin, 0, x_hi, ACS_VLINE | A_DIM, y_hi);

		(void)mvwaddch(shadowWin, 0, x_hi, ACS_URCORNER | A_DIM);
		(void)mvwaddch(shadowWin, y_hi, 0, ACS_LLCORNER | A_DIM);
		(void)mvwaddch(shadowWin, y_hi, x_hi, ACS_LRCORNER | A_DIM);
		wrefresh(shadowWin);
	}
}

/*
 * This is a dummy function used to ensure that the constant for mapping has
 * a distinct address.
 */
int getcCDKBind(EObjectType cdktype GCC_UNUSED,
		 void *object GCC_UNUSED,
		 void *clientData GCC_UNUSED,
		 chtype input GCC_UNUSED)
{
   return 0;
}

/*
 * Refresh one CDK window.
 * FIXME: this should be rewritten to use the panel library, so it would not
 * be necessary to touch the window to ensure that it covers other windows.
 */
void refreshCDKWindow(WINDOW *win)
{
   touchwin(win);
   wrefresh(win);
}


/*
 * This safely erases a given window.
 */
void eraseCursesWindow(WINDOW *window)
{
	if (window) {
		werase(window);
		wrefresh(window);
	}
}

/*
 * This safely deletes a given window.
 */
void deleteCursesWindow(WINDOW *window)
{
	if (window) {
		eraseCursesWindow(window);
		delwin(window);
	}
}

/*
 * This moves a given window (if we're able to set the window's beginning).
 * We do not use mvwin(), because it does (usually) not move subwindows.
 */
void moveCursesWindow(WINDOW *window, int xdiff, int ydiff)
{
	if (window) {
		// int xpos, ypos;
		// getbegyx(window, ypos, xpos);
		// (void)setbegyx(window,(short)ypos,(short)xpos);
		int ypos{window->_begy+ydiff}; // += xdiff;
		int xpos{window->_begx+xdiff}; // += xdiff;
		werase(window);
//		(void)setbegyx(window,(short)ypos,(short)xpos);
		window->_begy=(short)ypos;
		window->_begx=(short)xpos;
	}
}


int comparSort(const void *a, const void *b)
{
	return strcmp(*(const char *const *)a,(*(const char *const *)b));
}
/*
void sortList(CDK_CSTRING *list, int length)
{
	if (length > 1)
		qsort(list,(unsigned)length, sizeof(list[0]), comparSort);
}
*/

/*
 * This looks for a subset of a word in the given list.
 */
int searchList(vector<string> *plistp, const char *pattern)
{
	int Index = -1;
	/* Make sure the pattern isn't null. */
	if (pattern) {
		size_t len = strlen(pattern);
		/* Cycle through the list looking for the word. */
		int x=0;
		for(vector<string>::const_iterator it0=plistp->begin();it0!=plistp->end();++x,++it0) {
			const int ret{strncmp(it0->c_str(),pattern,len)};
			if (ret<0) {
				Index=ret;
			} else {
				if (!ret) Index=x;
				break;
			}
		}
	}
	return Index;
}

/*
 * Add a new string to a list.  Keep a null pointer on the end so we can use
 * CDKfreeStrings() to deallocate the whole list.
 */
void
CDKallocStrings(vector<string> *plistp, char *item)
{
	plistp->push_back(string(item));
}

/*
 * Write a string of blanks, using writeChar().
 */
void writeBlanks(WINDOW *window, int xpos, int ypos, int align, int start, int end)
{
	if (start < end) {
		string blanks(end-start+1000,' ');
		writeChar(window, xpos, ypos, blanks.c_str(), align, start, end);
	}
}

/*
 * This writes out a char * string with no attributes.
 */
void writeChar(WINDOW *window,
		int xpos,
		int ypos,
		const char *string,
		int align,
		int start,
		int end)
{
	writeCharAttrib(window, xpos, ypos, string, A_NORMAL, align, start, end);
}

/*
 * This writes out a char * string with attributes.
 */
void writeCharAttrib(WINDOW *window,
		int xpos,
		int ypos,
		const char *string,
		chtype attr,
		int align,
		int start,
		int end)
{
	int display = end - start;
	int x;
	if (align == HORIZONTAL) {
		/* Draw the message on a horizontal axis. */
		display = MINIMUM(display, getmaxx(window) - 1);
		for (x = 0; x < display; x++) {
			(void)mvwaddch(window,
					ypos,
					xpos + x,
					(unsigned char)string[x + start] | attr);
		}
	} else {
		/* Draw the message on a vertical axis. */
		display = MINIMUM(display, getmaxy(window) - 1);
		for (x = 0; x < display; x++) {
			(void)mvwaddch(window,
					ypos + x,
					xpos,
					(unsigned char)string[x + start] | attr);
		}
	}
}

// die nächsten 3 aus display.c
/*
 * Given a character pointer, returns the equivalent display type.
 */
EDisplayType char2DisplayType(const char *string)
{
	/* *INDENT-OFF* */
	static const struct {
		const char *name;
		EDisplayType code;
	} table[] = {
		{ "CHAR",		vCHAR },
		{ "HCHAR",	vHCHAR },
		{ "INT",		vINT },
		{ "HINT",		vHINT },
		{ "UCHAR",	vUCHAR },
		{ "LCHAR",	vLCHAR },
		{ "UHCHAR",	vUHCHAR },
		{ "LHCHAR",	vLHCHAR },
		{ "MIXED",	vMIXED },
		{ "HMIXED",	vHMIXED },
		{ "UMIXED",	vUMIXED },
		{ "LMIXED",	vLMIXED },
		{ "UHMIXED",	vUHMIXED },
		{ "LHMIXED",	vLHMIXED },
		{ "VIEWONLY",	vVIEWONLY },
		{ 0,		vINVALID },
	};
	/* *INDENT-ON* */
	if (string) {
		for (int n = 0; table[n].name; n++) {
			if (!strcmp(string, table[n].name))
				return table[n].code;
		}
	}
	return (EDisplayType) vINVALID;
}

/*
 * Tell if a display type is "hidden"
 */
bool isHiddenDisplayType(EDisplayType type)
{
	bool result = FALSE;
	switch (type) {
		case vHCHAR:
		case vHINT:
		case vHMIXED:
		case vLHCHAR:
		case vLHMIXED:
		case vUHCHAR:
		case vUHMIXED:
			result = TRUE;
			break;
		case vCHAR:
		case vINT:
		case vINVALID:
		case vLCHAR:
		case vLMIXED:
		case vMIXED:
		case vUCHAR:
		case vUMIXED:
		case vVIEWONLY:
			result = FALSE;
			break;
	}
	return result;
}

/*
 * Given a character input, check if it is allowed by the display type,
 * and return the character to apply to the display, or ERR if not.
 */
int filterByDisplayType(EDisplayType type, chtype input)
{
	int result = (unsigned char)input;
	if (!isChar(input)) {
		result = ERR;
	} else if ((type == vINT ||
				type == vHINT) &&
			!isdigit((unsigned char)result)) {
		result = ERR;
	} else if ((type == vCHAR ||
				type == vUCHAR ||
				type == vLCHAR ||
				type == vUHCHAR ||
				type == vLHCHAR) &&
			isdigit((unsigned char)result)) {
		result = ERR;
	} else if (type == vVIEWONLY) {
		result = ERR;
	} else if ((type == vUCHAR ||
				type == vUHCHAR ||
				type == vUMIXED ||
				type == vUHMIXED) &&
			isalpha((unsigned char)result)) {
		result = toupper(result);
	} else if ((type == vLCHAR ||
				type == vLHCHAR ||
				type == vLMIXED ||
				type == vLHMIXED) &&
			isalpha((unsigned char)result)) {
		result = tolower(result);
	}
	return result;
}

/*
 * This is added to remain consistent.
 */
void endCDK(void)
{
   /* Turn echoing back on. */
   echo();
   /* Turn off cbreak. */
   nocbreak();
   /* End the curses windows. */
   endwin();
#ifdef HAVE_XCURSES
   XCursesExit();
#endif
}

static bool checkMenuKey(int keyCode, int functionKey)
{
	return (keyCode == KEY_ESC && !functionKey);
}
// aus cdk.c:


/*
 * Return the length of the given lists.
 */
int lenCharList(const char **list)
{
	int result = 0;
	if (list) {
		while (*list++)
			++result;
	}
	return result;
}

void initCDKColor(void)
{
#ifdef HAVE_START_COLOR
	if (has_colors()) {
		int color[] =
		{
			COLOR_WHITE, COLOR_RED, COLOR_GREEN,
			COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA,
			COLOR_CYAN, COLOR_BLACK
		};
		int pair = 1;
		int fg, bg;
		int limit;
		start_color();
		limit =(COLORS < MAX_COLORS) ? COLORS : MAX_COLORS;
		/* Create the color pairs. */
		for (fg = 0; fg < limit; fg++) {
			for (bg = 0; bg < limit; bg++) {
				init_pair((short)pair++,(short)color[fg],(short)color[bg]);
			}
		}
	}
#endif
}


/*
 * Returns the object on which the focus lies.
 */
GObj* SScreen::getCDKFocusCurrent()
{
   GObj *result = 0;
   int n = this->objectFocus;
   if (n >= 0 && n < this->objectCount)
      result = this->object[n];
   return result;
}

/*
 * Set focus to the next object, returning it.
 */
GObj *SScreen::setCDKFocusNext()
{
	GObj *result = 0;
	GObj *curobj;
	int n = getFocusIndex();
	int first = n;
	for (;;) {
		if (++n >= this->objectCount)
			n = 0;
		curobj = this->object[n];
		if (curobj && curobj->acceptsFocus) {
			result = curobj;
			break;
		} else {
			if (n == first) {
				break;
			}
		}
	}
	setFocusIndex((result) ? n : -1);
	return result;
}

/*
 * Set focus to the previous object, returning it.
 */
GObj* SScreen::setCDKFocusPrevious()
{
	GObj *result = 0;
	GObj *curobj;
	int n = getFocusIndex();
	int first = n;
	for (;;) {
		if (--n < 0)
			n = this->objectCount - 1;
		curobj = this->object[n];
		if (curobj && curobj->acceptsFocus) {
			result = curobj;
			break;
		} else if (n == first) {
			break;
		}
	}
	setFocusIndex((result) ? n : -1);
	return result;
}

/*
 * Set focus to a specific object, returning it.
 * If the object cannot be found, return null.
 */
GObj* SScreen::setCDKFocusCurrent(/*SScreen *screen, */GObj *newobj)
{
	GObj *result = 0;
	GObj *curobj;
	int n = getFocusIndex();
	int first = n;
	for (;;) {
		if (++n >= this->objectCount)
			n = 0;
		curobj = this->object[n];
		if (curobj == newobj) {
			result = curobj;
			break;
		} else if (n == first) {
			break;
		}
	}
	setFocusIndex(/*this, */(result) ? n : -1);
	return result;
}

/*
 * Set focus to the first object in the screen.
 */
GObj* SScreen::setCDKFocusFirst(/*SScreen *screen*/)
{
   setFocusIndex(/*screen, screen->*/objectCount - 1);
   return switchFocus(setCDKFocusNext(/*screen*/), 0);
}

/*
 * Set focus to the last object in the screen.
 */
/*GObj **/void SScreen::setCDKFocusLast(/*SScreen *screen*/)
{
   setFocusIndex(/*screen, */0);
   /*return */switchFocus(setCDKFocusPrevious(/*screen*/), 0);
}

/*
 * Save data in widgets on a screen
 */
void SScreen::saveDataCDKScreen(/*SScreen *screen*/)
{
   for (int i = 0; i < /*screen->*/objectCount; ++i)
      object[i]->/*saveDataObj*/saveDataCDK(/*screen->*//*object[i]*/);
}

/*
 * Refresh data in widgets on a screen
 */
void SScreen::refreshDataCDKScreen(/*SScreen *screen*/)
{
   for (int i = 0; i < /*screen->*/objectCount; ++i)
      object[i]->/*refreshDataObj*/refreshDataCDK(/*screen->*//*object[i]*/);
}


void SScreen::exitOKCDKScreen(/*SScreen *screen*/)
{
   /*screen->*/exitStatus = CDKSCREEN_EXITOK;
}

void SScreen::exitCancelCDKScreen(/*SScreen *screen*/)
{
   /*screen->*/exitStatus = CDKSCREEN_EXITCANCEL;
}

/*
void GObj::exitOKCDKScreenOf()
{
   screen->exitOKCDKScreen();
}
*/

/*
void GObj::exitCancelCDKScreenOf()
{
   screen->exitCancelCDKScreen();
}
*/

void SScreen::resetCDKScreen()
{
   refreshDataCDKScreen();
}
/*
void GObj::resetCDKScreenOf()
{
   screen->resetCDKScreen();
}
*/

void SScreen::traverseCDKOnce(/*SScreen *screen,*/
		GObj *curobj,
		int keyCode,
		bool functionKey,
		CHECK_KEYCODE funcMenuKey)
{
	switch (keyCode) {
		case KEY_BTAB:
			switchFocus(setCDKFocusPrevious(/*screen*/), curobj);
			break;
		case KEY_TAB:
			switchFocus(setCDKFocusNext(/*screen*/), curobj);
			break;
		case KEY_F(10):
			/* save data and exit */
			exitOKCDKScreen(/*screen*/);
			break;
		case CTRL('X'):
			exitCancelCDKScreen(/*screen*/);
			break;
		case CTRL('R'):
			/* reset data to defaults */
			resetCDKScreen(/*screen*/);
			curobj->setFocus();
			break;
		case CDK_REFRESH:
			/* redraw screen */
			refreshCDKScreen(/*screen*/); // oder object-> ?
			curobj->setFocus();
			break;
		default:
			/* not everyone wants menus, so we make them optional here */
			if (funcMenuKey && funcMenuKey(keyCode, functionKey)) {
				/* find and enable drop down menu */
				for (int j = 0; j < /*screen->*/objectCount; ++j)
					if (/*ObjTypeOf(*//*screen->*/object[j]->cdktype/*)*/ == vMENU) {
						handleMenu(/*screen, *//*screen->*/object[j], curobj);
						break;
					}
			} else {
				curobj->injectObj(/*curobj, */(chtype)keyCode);
			}
			break;
	}
}

/*
 * Traverse the widgets on a screen.
 */
int SScreen::traverseCDKScreen(/*SScreen *screen*/)
{
	int result = 0;
	GObj *curobj = setCDKFocusFirst(/*screen*/);
	if (curobj) {
		refreshDataCDKScreen(/*screen*/);
		/*screen->*/exitStatus = CDKSCREEN_NOEXIT;
		while (((curobj = getCDKFocusCurrent(/*screen*/))) && (/*screen->*/exitStatus == CDKSCREEN_NOEXIT)) {
			bool function;
			int key = curobj->getchCDKObject(/*curobj, */&function);
			traverseCDKOnce(/*screen, */curobj, key, function, checkMenuKey);
		}
		if (/*screen->*/exitStatus == CDKSCREEN_EXITOK) {
			saveDataCDKScreen(/*screen*/);
			result = 1;
		}
	}
	return result;
}


GObj* SScreen::handleMenu(/*SScreen *screen, */GObj *menu, GObj *oldobj)
{
	bool done = FALSE;
	GObj *newobj;
	switchFocus(menu, oldobj);
	while (!done) {
		bool functionKey;
		int key = menu->getchCDKObject(/*menu, */&functionKey);
		switch (key) {
			case KEY_TAB:
				done = TRUE;
				break;
			case KEY_ESC:
				/* cleanup the menu */
				//				((CDKMENU*)menu)->injectSMenu(/*(CDKMENU *)menu, */(chtype)key);
				menu->injectObj((chtype)key);
				done = TRUE;
				break;
			default:
//				done =(menu->injectSMenu(/*(CDKMENU *)menu, */(chtype)key) >= 0);
				if (menu->injectObj(chtype(key))) {
					done=menu->resultData.valueInt;
				} else {
					done=-1; // unknownInt;
				}
				break;
		}
	}
	if (!(newobj = this->getCDKFocusCurrent()))
		newobj = this->setCDKFocusNext();
	/*return */switchFocus(newobj, menu);
	return newobj;
}



void GObj::unsetFocus()
{
   curs_set(0);
//   if (obj) {
//      HasFocusObj(this) = FALSE;
			hasFocus=0;
      unfocusObj();
//   }
}

void GObj::setFocus()
{
//   if (obj) {
//      HasFocusObj(this) = TRUE;
			hasFocus=1;
      focusObj();
//   }
   curs_set(1);
}

GObj* switchFocus(GObj *newobj, GObj *oldobj)
{
   if (oldobj != newobj) {
      if (oldobj) oldobj->unsetFocus();
      if (newobj) newobj->setFocus();
   }
 return newobj;
}

/*
 * This registers a CDK object with a screen.
 */
void GObj::registerCDKObject(SScreen *screen, EObjectType cdktype)
{
	if (validObjType(cdktype)) {
		setScreenIndex(screen);
		screen->objectCount++;
	}
}

/*
 * This registers a CDK object with a screen.
 */
void GObj::reRegisterCDKObject(EObjectType cdktype/*, void *object*/)
{
//   GObj *obj =(GObj *)object;
   registerCDKObject(/*obj->*/screen, cdktype/*, object*/);
}

//#define validIndex(screen, n)((n) >= 0 &&(n) <(screen)->objectCount)
#define validIndex(n)((n) >= 0 &&(n) <(this)->objectCount)

void SScreen::swapCDKIndices(/*SScreen *screen, */int n1, int n2)
{
	if (n1 != n2 && validIndex(n1) && validIndex(n2)) {
		iter_swap(object.begin()+n1,object.begin()+n2);
		if (this->objectFocus == n1)
			this->objectFocus = n2;
		else if (this->objectFocus == n2)
			this->objectFocus = n1;
	}
}

/*
 * This 'brings' a CDK object to the top of the stack.
 */
void GObj::raiseCDKObject(EObjectType cdktype/*, void *object*/)
{
//   GObj *obj = (GObj *)object;
//   if (validObjType(obj, cdktype)) {
//      SScreen *screen = obj->screen;
      screen->swapCDKIndices(screenIndex, screen->objectCount - 1);
//   }
}

/*
 * This 'lowers' an object.
 */
void GObj::lowerCDKObject(EObjectType cdktype/*, void *object*/)
{
//   GObj *obj = (GObj *)object;
//   if (validObjType(obj, cdktype)) {
//      SScreen *screen = obj->screen;
      screen->swapCDKIndices(screenIndex, 0);
//   }
}



/*
 * Set the object's exit-type based on the input.
 * The .exitType field should have been part of the GObj struct, but it
 * is used too pervasively in older applications to move(yet).
 */
//void GObj::setCdkExitType(chtype ch)
void GObj::setExitType(chtype ch)
{
   switch (ch) {
   case KEY_ERROR:
      exitType = vERROR;
      break;
   case KEY_ESC:
      exitType = vESCAPE_HIT;
      break;
   case KEY_TAB:
   case KEY_ENTER:
      exitType = vNORMAL;
      break;
   case 0:
      exitType = vEARLY_EXIT;
      break;
   }
}

/*
 * Set indices so the screen and object point to each other.
 */
// etwas andere Funktionalität
void GObj::setScreenIndex(SScreen *pscreen)
{
  screen=pscreen;
	screen->object.push_back(this);
	screenIndex=screen->object.size()-1;
}

GObj::~GObj()
{
	destroyCDKObject();
}

void GObj::destroyCDKObject()
{
	size_t pos{0};
	for(auto akt:all_objects) {
		if (akt==this) {
			all_objects.erase(all_objects.begin()+pos);
			break;
			akt->destroyObj();
			free(akt);
		}
		pos++;
	}
}

void GObj::destroyObj()
{
	destroyCDKObject();
}

/*
 * This removes an object from the CDK screen.
 */
void GObj::unregisterCDKObject(EObjectType cdktype/*, void *object*/)
{
	//   GObj *obj = (GObj *)object;
	if (validObjType(cdktype) && this->screenIndex >= 0) {
//		SScreen *screen = (this)->screen;
		if (screen) {
			int Index = (this)->screenIndex;
			this->screenIndex = -1;
			screen->object.erase(screen->object.begin()+Index);
			if (--screen->objectCount>0) {
				if (screen->objectFocus == Index) {
					screen->objectFocus--;
					screen->setCDKFocusNext();
				} else if (screen->objectFocus > Index) {
					screen->objectFocus--;
				}
			}
		}
	}
}

/*
 * Resequence the numbers after a insertion/deletion.
 */
void SScroll::resequence(/*SScroll *scrollp*/)
{
	if (/*scrollp->*/numbers) {
		int j{0};
		for(piter=pitem.begin();piter!=pitem.end();++j,piter++) {
			char source[80];
			chtype *target =  // eigentlich const chtype *target
				piter->getinh();
			sprintf(source, NUMBER_FMT, j + 1, "");
			for (int k = 0; source[k]; ++k) {
				/* handle deletions that change the length of number */
				if (source[k] == '.' && (unsigned char)target[k] != '.') {
					int k2 = k;
					while ((target[k2] = target[k2 + 1]))
						++k2;
					/*scrollp->*/itemLen[j] -= 1;
				}
				target[k] &= A_ATTRIBUTES;
				target[k] |= (chtype)(unsigned char)source[k];
			}
		}
	}
}


/*
 * This adds a single item to a scrolling list, at the end of the list.
 */
//#define AvailableWidth(w)  ((w)->boxWidth - 2 * BorderOf(w))
#define AvailableWidth() (boxWidth - 2 * borderSize)
// #define WidestItem(w)      ((w)->maxLeftChar + AvailableWidth(w))
#define WidestItem()      (maxLeftChar + AvailableWidth())
void SScroll::addCDKScrollItem(/*SScroll *scrollp,*/ const char *item)
{
   int itemNumber = /*scrollp->*/ listSize ;
   int widestItem = WidestItem(/*scrollp*//*this*/);
   if (allocListItem(/*scrollp,*/ itemNumber, /*scrollp->*/numbers ?(itemNumber + 1) : 0, item)) {
      /* Determine the size of the widest item. */
      widestItem = MAXIMUM(/*scrollp->*/itemLen[itemNumber], widestItem);
      updateViewWidth(/*scrollp, */widestItem);
      setViewSize(/*scrollp, *//*scrollp->*/ listSize);
   }
}

/*
 * This adds a single item to a scrolling list, before the current item.
 */
void SScroll::insertCDKScrollItem(/*SScroll *scrollp, */const char *item)
{
	int widestItem = WidestItem(/*scrollp*//*this*/);
	if (allocListItem(/*scrollp,*/ /*scrollp->*/currentItem, /*scrollp->*/numbers ?(/*scrollp->*/currentItem + 1) : 0, item)) {
		/* Determine the size of the widest item. */
		widestItem = MAXIMUM(/*scrollp->*/itemLen[/*scrollp->*/currentItem], widestItem);
		updateViewWidth(/*scrollp, */widestItem);
		setViewSize(/*scrollp, *//*scrollp->*/ listSize);
		resequence(/*scrollp*/);
	}
}

/*
 * This removes a single item from a scrolling list.
 */
void SScroll::deleteCDKScrollItem(/*SScroll *scrollp, */int position)
{
	if (position>=0 && position<listSize) {
		pitem.erase(pitem.begin()+position);
		listSize--;
    itemLen.erase(itemLen.begin()+position);
    itemPos.erase(itemPos.begin()+position);
		setViewSize(/*scrollp, *//*scrollp->*/ listSize 
				);
		if (/*scrollp->*/ listSize > 0)
			resequence(/*scrollp*/);
		if (/*scrollp->*/ listSize < /*m*/MaxViewSize(/*scrollp*/))
			werase(/*scrollp->*/win);	/* force the next redraw to be complete */
		/* do this to update the view size, etc. */
		setCDKScrollPosition(/*scrollp, *//*scrollp->*/currentItem);
	}
}

void SScroll::focusCDKScroll(/*GObj *object*/)
{
//   SScroll *scrollp =(SScroll *)object;
   drawCDKScrollCurrent(/*scrollp*/);
   wrefresh(/*scrollp->*/listWin);
}

void SScroll::unfocusCDKScroll(/*GObj *object*/)
{
//   SScroll *scrollp =(SScroll *)object;
   drawCDKScrollCurrent(/*scrollp*/);
   wrefresh(/*scrollp->*/listWin);
}


SEntry::~SEntry()
{
//		SEntry *entry =(SEntry *)object;
		cleanCdkTitle();
		//freeChtype(this->label);
		delete labelp;
		/* Delete the windows. */
		deleteCursesWindow(this->fieldWin);
		deleteCursesWindow(this->labelWin);
		deleteCursesWindow(this->shadowWin);
		deleteCursesWindow(this->win);
		/* Clean the key bindings. */
		cleanCDKObjectBindings();
		/* Unregister this object. */
		unregisterCDKObject(vENTRY);
}

const int abstand{
	// wer rausfindet warum, bekommt einen Preis
	2
}; // Abstand des Scrollfeldes vom Entryfeld
/*
 * This moves the entry field to the given location.
 */
void SEntry::moveCDKEntry(/*GObj *object,*/
		int xplace,
		int yplace,
		bool relative,
		bool refresh_flag)
{
	/* *INDENT-EQLS* */
//	SEntry *entry =(SEntry *)object;
	int currentX    = getbegx(this->win);
	int currentY    = getbegy(this->win);
	int xpos        = xplace;
	int ypos        = yplace;
	int xdiff       = 0;
	int ydiff       = 0;
	/*
	 * If this is a relative move, then we will adjust where we want
	 * to move to.
	 */
	if (relative) {
		xpos = getbegx(this->win) + xplace;
		ypos = getbegy(this->win) + yplace;
	}
	/* Adjust the window if we need to. */
	alignxy(screen->window, &xpos, &ypos, this->boxWidth, this->boxHeight);
	/* Get the difference. */
	xdiff = currentX - xpos;
	ydiff = currentY - ypos;
	/* Move the window to the new location. */
	moveCursesWindow(this->win, -xdiff, -ydiff);
	moveCursesWindow(this->fieldWin, -xdiff, -ydiff);
	moveCursesWindow(this->labelWin, -xdiff, -ydiff);
	moveCursesWindow(this->shadowWin, -xdiff, -ydiff);
	/* Touch the windows so they 'move'. */
	refreshCDKWindow(screen->window);
	/* Redraw the window, if they asked for it. */
	if (refresh_flag) {
		drawCDKEntry(obbox);
	}
}

/*
 * This moves the alphalist field to the given location.
 */
void SAlphalist::moveCDKAlphalist(
			       int xplace,
			       int yplace,
			       bool relative,
			       bool refresh_flag)
{
//	SAlphalist *alphalist = (SAlphalist *)object;
   /* *INDENT-EQLS* */
   int currentX = getbegx(this->win);
   int currentY = getbegy(this->win);
   /*int */xpos     = xplace;
   /*int */ypos     = yplace;
   int xdiff    = 0;
   int ydiff    = 0;
   /*
    * If this is a relative move, then we will adjust where we want
    * to move to.
    */
   if (relative) {
      xpos = getbegx(this->win) + xplace;
      ypos = getbegy(this->win) + yplace;
   }
   /* Adjust the window if we need to. */
   alignxy(screen->window, &xpos, &ypos, this->boxWidth, this->boxHeight);
   /* Get the difference. */
   xdiff = currentX - xpos;
   ydiff = currentY - ypos;
   /* Move the window to the new location. */
   moveCursesWindow(this->win, -xdiff, -ydiff);
   moveCursesWindow(this->shadowWin, -xdiff, -ydiff);
   /* Move the sub-widgets. */
   entryField->moveCDKEntry(xplace, yplace, relative, FALSE);
   scrollField->moveCDKScroll(xplace, yplace+abstand+obbox, relative, FALSE);
   /* Touch the windows so they 'move'. */
   refreshCDKWindow(screen->window);
   /* Redraw the window, if they asked for it. */
   if (refresh_flag) {
      drawCDKAlphalist(obbox);
   }
} // void SAlphalist::moveCDKAlphalist(

/*
 * This moves the fselect field to the given location.
 */
void SFSelect::moveCDKFselect(/*GObj *object,*/
			     int xplace,
			     int yplace,
			     bool relative,
			     bool refresh_flag)
{
	//   SFSelect *fselect =(SFSelect *)object;
	/* *INDENT-EQLS* */
	int currentX = getbegx(this->win);
	int currentY = getbegy(this->win);
	/*int */xpos     = xplace;
	/*int */ypos     = yplace;
	int xdiff    = 0;
	int ydiff    = 0;
	/*
	 * If this is a relative move, then we will adjust where we want
	 * to move to.
	 */
	if (relative) {
		xpos = getbegx(this->win) + xplace;
		ypos = getbegy(this->win) + yplace;
	}
	/* Adjust the window if we need to. */
	alignxy(screen->window, &xpos, &ypos, this->boxWidth, this->boxHeight);
	/* Get the difference. */
	xdiff = currentX - xpos;
	ydiff = currentY - ypos;
	/* Move the window to the new location. */
	moveCursesWindow(this->win, -xdiff, -ydiff);
	moveCursesWindow(this->shadowWin, -xdiff, -ydiff);
	/* Move the sub-widgets. */
	entryField->moveCDKEntry(xplace, yplace, relative, FALSE);
	scrollField->moveCDKScroll(xplace, yplace+abstand+obbox, relative, FALSE);
	/* Redraw the window, if they asked for it. */
	if (refresh_flag) {
		drawCDKFselect(/*this, ObjOf(this)->*/obbox);
	}
}

/*
 * This means you want to use the given file selector. It takes input
 * from the keyboard, and when it's done, it fills the entry info
 * element of the structure with what was typed.
 */
const char *SFSelect::activateCDKFselect(/*SFSelect *fselect, */chtype *actions,int (&WeitereZc)[6],int obpfeil/*=0*/)
{
#ifndef false
   /* Draw the widget. */
   drawCDKFselect(obbox,/*obmitscroller*/1);
   /* Activate the widget. */
   const char *ret = entryField->activateCDKEntry(actions,WeitereZc,obpfeil);
   /* Copy the exit type from the entry field. */
//   copyExitType(this, this->entryField);
	 exitType=entryField->exitType;
   /* Determine the exit status. */
   if (this->exitType != vEARLY_EXIT) {
      return ret;
   }
   return 0;
#else

	const char *ret = 0;
	chtype input = 0;
	bool functionKey;
	/* Draw the widget. */
	drawCDKFselect(/*fselect, ObjOf(fselect)->*/obbox); //   ret = entryField->activateCDKEntry(actions,Zweitzeichen,Drittzeichen,obpfeil);
	if (!actions) {
		for (;;) {
			input =(chtype)getchCDKObject(/*ObjOf(fselect->entryField), */&functionKey);
			/* Inject the character into the widget. */
			// if (input==KEY_BTAB) return ret;
			ret=injectSFselect(input)?resultData.valueString:0/*unknownString*/;
			if (this->exitType != vEARLY_EXIT) {
				return ret;
			}
		}
	} else {
		int length = chlen(actions);
		/* Inject each character one at a time. */
		for (int x = 0; x < length; x++) {
			ret=injectSFselect(actions[x])?resultData.valueString:0/*unknownString*/;
			if (this->exitType != vEARLY_EXIT) {
				return ret;
			}
		}
	}
	/* Set the exit type and exit. */
	setExitType(/*fselect, */0);
	return 0;
#endif
}

/*
 * This moves the scroll field to the given location.
 */
void SScroll::moveCDKScroll(
			    int xplace,
			    int yplace,
			    bool relative,
			    bool refresh_flag)
{
   /* *INDENT-EQLS* */
//   SScroll *scrollp = (SScroll *)object;
   int currentX       = getbegx(this->win);
   int currentY       = getbegy(this->win);
   int xpos           = xplace;
   int ypos           = yplace;
   /*
    * If this is a relative move, then we will adjust where we want
    * to move to.
    */
   if (relative) {
      xpos = getbegx(this->win) + xplace;
      ypos = getbegy(this->win) + yplace;
   }
   /* Adjust the window if we need to. */
   alignxy(screen->window, &xpos, &ypos, this->boxWidth, this->boxHeight);
   /* Get the difference. */
   int xdiff = currentX - xpos;
   int ydiff = currentY - ypos;
   /* Move the window to the new location. */
   moveCursesWindow(this->win, -xdiff, -ydiff);
   moveCursesWindow(this->listWin, -xdiff, -ydiff);
   moveCursesWindow(this->shadowWin, -xdiff, -ydiff);
   moveCursesWindow(this->scrollbarWin, -xdiff, -ydiff);
   /* Touch the windows so they 'move'. */
   refreshCDKWindow(screen->window);
   /* Redraw the window, if they asked for it. */
   if (refresh_flag) {
		 // hier entstehen keine Fehler
      drawCDKScroll(obbox,1);
   }
}


void SAlphalist::destroyInfo()
{
	plist.clear();
}

SAlphalist::~SAlphalist()
{
//      SAlphalist *alphalist =(SAlphalist *)object;

      destroyInfo();
      /* Clean the key bindings. */
      cleanCDKObjectBindings();
//      destroyCDKEntry(this->entryField);
			entryField->~SEntry();
//      destroyCDKScroll(this->scrollField);
			scrollField->~SScroll();
      /* Free up the window pointers. */
      deleteCursesWindow(this->shadowWin);
      deleteCursesWindow(this->win);
      /* Unregister the object. */
      unregisterCDKObject(vALPHALIST);
}


SFSelect::~SFSelect()
{
//      SAlphalist *alphalist = (SAlphalist *)object;

//   if (object) {
//      SFSelect *fselect =(SFSelect *)object;

      cleanCDKObjectBindings(/*vFSELECT, fselect*/);

      /* Free up the character pointers. */

      /* Destroy the other Cdk objects. */
			//      destroyCDKScroll(this->scrollField);
			scrollField->destroyObj();
			//      destroyCDKEntry(this->entryField);
			entryField->~SEntry();

      /* Free up the window pointers. */
      deleteCursesWindow(this->shadowWin);
      deleteCursesWindow(this->win);

      /* Clean the key bindings. */
      /* Unregister the object. */
      unregisterCDKObject(vFSELECT/*, this*/);
//   }
}

/*
 * This function sets the pre-process function.
 */
/*
void SAlphalist::setCDKAlphalistPreProcess(PROCESSFN callback, void *data)
{
   entryField->setCDKObjectPreProcess(callback, data);
}
*/

/*
 * This function sets the post-process function.
 */
/*
void SAlphalist::setCDKAlphalistPostProcess(PROCESSFN callback, void *data)
{
   entryField->setCDKObjectPostProcess(callback, data);
}
*/

/*
 * This function draws the scrolling list widget.
 */
void SScroll::drawCDKScroll(bool Box,bool obmit)
{
	//   SScroll *scrollp =(SScroll *)object;
	/* Draw in the shadow if we need to. */
	if (this->shadowWin)
		drawShadow(this->shadowWin);
	drawCdkTitle(this->win);
	/* Draw in the scolling list items. */
	// Kommentar GSchade 0 11.11.18
	// GSchade: auskommentieren und dann noch vor dem Wechsel zu anderem alle übrigen zeichnen
	// if (akteinbart==einb_alphalist &&obmit) KLA
	//	 if (obmit && Znr==mutter->objnr && !erstmals) KLA
	if ((mutter->cdktype!=vALPHALIST && mutter->cdktype!=vFSELECT) || ((ComboB*)mutter)->zeichnescroll) {
		drawCDKScrollList(Box); 
		wrefresh(parent); // gleichbedeutend: wrefresh(obj.screen->window);
	}
	/*
		 static int nr=0;
		 ofstream prot;
		 prot.open("protok.txt",ios::out|ios::app);
		 prot<<nr++<<": Znr: "<<Znr<<", mutter->objnr: "<<mutter->objnr<<", erstmals: "<<erstmals<<", obmit: "<<obmit<<endl;
		 prot.close();
		 */
	 // KLZ
}

/*
 * This function destroys
 */
SScroll::~SScroll(/*GObj *object*/)
{
		//SScroll *scrollp =(SScroll *)object;
		cleanCdkTitle();
		/* Clean up the windows. */
		deleteCursesWindow(this->scrollbarWin);
		deleteCursesWindow(this->shadowWin);
		deleteCursesWindow(this->listWin);
		deleteCursesWindow(this->win);
		/* Clean the key bindings. */
		cleanCDKObjectBindings();
		/* Unregister this object. */
//		unregisterCDKObject(vSCROLL); s.Konstruktor
}

/*
 * Set the widget's title.
 */
int GObj::setCdkTitle(const char *titlec, int boxWidth)
{
	cleanCdkTitle();
	if (titlec) {
		vector<string> temp;
		int titleWidth;
		int x;
		int len;
		int align;

		/* We need to split the title on \n. */
		aufSplit(&temp,titlec,'\n');
		titleLines=temp.size();
		titlePos = new int[titleLines];
		titleLen=new int[titleLines];
		if (boxWidth >= 0) {
			int maxWidth = 0;
			/* We need to determine the widest title line. */
			for (x = 0; x < titleLines; x++) {
//				chtype *holder = char2Chtypeh(temp[x], &len, &align);
				chtstr holder(temp[x].c_str(),&len,&align);
				maxWidth = MAXIMUM(maxWidth, len);
//				freeChtype(holder);
			}
			boxWidth = MAXIMUM(boxWidth, maxWidth + 2 * borderSize);
		} else {
			boxWidth = -(boxWidth - 1);
		}

		/* For each line in the title, convert from char * to chtype * */
		titleWidth = boxWidth - (2 * borderSize);
		for (x = 0; x < titleLines; x++) {
//			title[x] = char2Chtypeh(temp[x], &titleLen[x], &titlePos[x]);
			titles.push_back(chtstr(temp[x].c_str() ,&titleLen[x],&titlePos[x]));
			titlePos[x] = justifyString(titleWidth, titleLen[x], titlePos[x]);
		}
	}
	return boxWidth;
} // int GObj::setCdkTitle(const char *title, int boxWidth)

/*
 * Draw the widget's title.
 */
void GObj::drawCdkTitle(WINDOW *win)
{
	for (int x = 0; x < titleLines; x++) {
		writeChtype(win,
				titlePos[x] + borderSize,
				x + borderSize,
				titles[x].getinh(),
				HORIZONTAL, 0,
				titleLen[x]);
	}
}


/*
 * Remove storage for the widget's title.
 */
void GObj::cleanCdkTitle()
{
//	CDKfreeChtypes(title);
//	title = 0;
//	freeAndNull(titlePos);
	delete [] titlePos;
//	freeAndNull(titleLen);
	delete [] titleLen;
	titleLines = 0;
}

bool GObj::validObjType(EObjectType type)
{
	bool valid = FALSE;
	//   if (obj && ObjTypeOf(obj) == type) {
	switch (type) {
		case vALPHALIST:
		case vBUTTON:
		case vBUTTONBOX:
		case vCALENDAR:
		case vDSCALE:
		case vENTRY:
		case vFSCALE:
		case vFSELECT:
		case vFSLIDER:
		case vGRAPH:
		case vHISTOGRAM:
		case vITEMLIST:
		case vLABEL:
		case vMARQUEE:
		case vMATRIX:
		case vMENTRY:
		case vMENU:
		case vRADIO:
		case vSCALE:
		case vSCROLL:
		case vSELECTION:
		case vSLIDER:
		case vSWINDOW:
		case vTEMPLATE:
		case vUSCALE:
		case vUSLIDER:
		case vVIEWER:
			valid = TRUE;
			break;
		case vDIALOG: // fuehrt zum Absturz
		case vTRAVERSE:		/* not really an object */
		case vNULL:
			break;
	}
	//	 }
	return valid;
}

/*
 * The cdktype parameter passed to bindCDKObject, etc., is redundant since
 * the object parameter also has the same information.  For compatibility
 * just use it for a sanity check.
 */

#ifndef KEY_MAX
#define KEY_MAX 512
#endif

GObj* GObj::bindableObject()
{
	return this;
}

GObj* ComboB::bindableObject()
{
	return entryField;
}

/*
 * This inserts a binding.
 */
void GObj::bindCDKObject(
		    chtype key,
		    BINDFN function,
		    void *data)
{
	GObj *obj = bindableObject();
	if (obj) {
		if (key==9) {
			// int test{0};
		}
		obj->bindv[key]=CDKBINDING(function,data);
	}
}

/*
 * This removes a binding on an object.
 */
void GObj::unbindCDKObject(chtype key)
{
	GObj *obj = bindableObject();
	if (obj) {
		obj->bindv.erase(key);
	}
}

/*
 * This removes all the bindings for the given objects.
 */
void GObj::cleanCDKObjectBindings()
{
	GObj *obj = bindableObject();
	if (obj) {
		obj->bindv.clear();
	}
}


/*
 * This checks to see if the binding for the key exists:
 * If it does then it runs the command and returns its value, normally TRUE.
 * If it doesn't it returns a FALSE.  This way we can 'overwrite' coded
 * bindings.
 */
int GObj::checkCDKObjectBind(chtype key)
{
	GObj *obj = bindableObject();
	if (obj) {
		if (obj->bindv.find(key)!=obj->bindv.end()) {
			BINDFN function=obj->bindv[key].bindFunction;
			void *data=obj->bindv[key].bindData;
			return function(cdktype, this, data, key);
		}
	}
	return(FALSE);
}

/*
 * This checks to see if the binding for the key exists.
 */
bool GObj::isCDKObjectBind(chtype key)
{
	bool result = FALSE;
	GObj *obj = bindableObject();
	if (obj) {
		if (obj->bindv.find(key)!=obj->bindv.end()) {
			result=TRUE;
		}
	}
	return (result);
}


/*
 * Draw a box around the given window using the object's defined line-drawing
 * characters.
 */
void GObj::drawObjBox(WINDOW *win)
{
	attrbox(win,
			ULChar,
			URChar,
			LLChar,
			LRChar,
			HZChar,
			VTChar,
			BXAttr);
}

/*
 * Read from the input window, filtering keycodes as needed.
 */
int GObj::getcCDKObject()
{
	// EObjectType cdktype = ObjTypeOf(this);
	GObj *test = bindableObject();
	int result = wgetch(inputWindow);
	// printf("%c %ul\n",result,result); //G.Schade
	//BINDFN fn{0};
	//CDKBINDING *bnd{0}; 
	if (result>=0 && test) {
		bindvit=test->bindv.find(result);
	}
	if (result>=0 && test && bindvit!=test->bindv.end() && bindvit->second.bindFunction == getcCDKBind) {
		result=(int)(long)test->bindv[result].bindData;
	} else if (!test || bindvit==test->bindv.end() || !bindvit->second.bindFunction) {
		switch (result) {
			case '\r':
			case '\n':
				result = KEY_ENTER;
				break;
			case '\t':
				result = KEY_TAB;
				break;
			case DELETE:
				result = KEY_DC;
				break;
			case '\b':		/* same as CTRL('H'), for ASCII */
				result = KEY_BACKSPACE;
				break;
			case CDK_BEGOFLINE:
				result = KEY_HOME;
				break;
			case CDK_ENDOFLINE:
				result = KEY_END;
				break;
			case CDK_FORCHAR:
				result = KEY_RIGHT;
				break;
			case CDK_BACKCHAR:
				result = KEY_LEFT;
				break;
			case CDK_NEXT:
				result = KEY_TAB;
				break;
			case CDK_PREV:
				result = KEY_BTAB;
				break;
		}
	}
	return result;
} // int GObj::getcCDKObject()

/*
 * Use this function rather than getcCDKObject(), since we can extend it to
 * handle wide-characters.
 */
int GObj::getchCDKObject(bool *functionKey)
{
   int key = getcCDKObject();
   *functionKey = (key >= KEY_MIN && key <= KEY_MAX);
   return key;
}


/*
 * This is a generic character parser for the entry field. It is used as a
 * callback function, so any personal modifications can be made by creating
 * a new function and calling the activation with its name.
 */
void SEntry::schreibl(chtype character)
{
  static int altobuml{0},uraltobuml{0},verbote{0};
//  const bool obuml=(character==(chtype)-61||character==(chtype)-62||character==(chtype)-30);
  const int obuml{isSonder(character)};
  int plainchar;
  if (uraltobuml==2||altobuml||obuml) plainchar=character; else plainchar=filterByDisplayType(dispType, character);
	// wenn Ende erreicht wuerde, dann von 2-Buchstabenlaengen langen Buchstaben keinen schreiben
//	const int slen=strlen(efld.c_str());
	const size_t slen{efld.length()};
//	for(int i=0;i<5;i++) mvwprintw(screen->window,1+i,1,"%i:                                                                                ",i);
  if (obuml==2 && slen>maxlen-3) verbote=3;
	else if (obuml==1 && slen>maxlen-2) verbote=2;
	else if (slen>maxlen-1) verbote=1;
  if (plainchar == ERR ||verbote) {
		verbote--;
		// (altobuml&&slen>maxlen-1-obuml&&!isSonder(efld[slen-obuml])/*efld[slen-1]!=-61&&efld[slen-1]!=-62&&efld[slen-1]!=-30*/))
    Beep();
		mvwprintw(screen->window,1+(obuml?1:altobuml?2:uraltobuml?3:5),1,"Beep!: slen: %i, obuml: %i, altobuml: %i, uraltobuml: %i    ",slen,obuml,altobuml,uraltobuml);
  } else {
    /* Update the screen and pointer. */
		efld.insert(efld.begin()+screenCol+leftChar,(char)plainchar);
		static size_t rupos=1;
		mvwprintw(screen->window,rupos % 40,125,"%i: lC: %i, sC: %i, lC+sC: %i, plC: %i, plC: %c ",rupos,leftChar,screenCol,leftChar+screenCol, plainchar,(unsigned char)plainchar);
		rupos++;
		mvwprintw(screen->window,rupos % 40,125,"                                                                  ");
		if (sbuch != fieldWidth - 1) {
			screenCol++;
			//      if (!obuml) sbuch++;
			sbuch+=1-obuml;
		} else {
			/* Update the character pointer. */
			//			efld.resize(slen+1);
			//      efld[slen] =(char)plainchar;
			//			efld+=(char)plainchar;
			//			if (obuml) {
			//				screenCol+=obuml;
			//			} else {
			/* Do not update the pointer if it's the last character */
			//        if (slen + 1 < maxlen) {
			const int wieweit{isSonder(efld[leftChar])};
			//					leftChar+=wieweit;
			//					screenCol-=wieweit;
			if (!altobuml && uraltobuml!=2) { // nur beim ersten angegebenen Durchlauf leftChar und lbuch erhöhen
				leftChar+=1+wieweit;
				screenCol-=1+wieweit;
				lbuch++;
			}
			screenCol++;
			//        }
			//      }
		}
		/* Update the entry field. */
		if (!obuml&&altobuml!=2) {
			zeichneFeld();
		}
	}
	uraltobuml=altobuml;
	altobuml=obuml;
}

/*
 * This redraws the entry field.
 */
void SEntry::zeichneFeld()
{
	// setlocale(LC_ALL,"");
	/* Set background color and attributes of the entry field */
	wbkgd(fieldWin, fieldAttr);
	/* Draw in the filler characters. */
	(void)mvwhline(fieldWin, 0, 0/*x*/, filler | fieldAttr, fieldWidth);
	/* If there is information in the field. Then draw it in. */
//	if (!efld.empty()) KLA
	if (1) {
		const size_t efldLength{efld.length()};
		/* Redraw the field. */
		if (isHiddenDisplayType(dispType)) {
			for (size_t x = leftChar; x < efldLength; x++) {
				(void)mvwaddch(fieldWin, 0, x - leftChar, hidden | fieldAttr);
			}
		} else {
				/*
			if (0) {
				char ausgabe[efldLength-leftChar+1];
				memcpy(ausgabe,&efld[leftChar],efldLength-leftChar);
				ausgabe[efldLength-leftChar]=0;
			} else if (0) {
				mvwprintw(parent,1,1,"x:%i,len:%i,fwidth:%i,maxlen:%i,lChar:%i,lbuch:%i,sCol:%i,sbuch:%i,info:%s   ",x,efldLength,fieldWidth,maxlen,leftChar,lbuch,screenCol,sbuch,info);
				for (x = leftChar; x < efldLength; x++) {
					mvwprintw(parent,2+x,2,"x:%i, info[x]:%i  ",x,info[x]);
				}
				mvwprintw(parent,2+efldLength,2,"                            ");
				mvwprintw(parent,2+efldLength+1,2,"                            ");
				wrefresh(parent); // gleichbedeutend: wrefresh(obj.screen->window);
			}
				*/
			size_t aktumlz{0};
			for (size_t x = leftChar; x < efldLength; x++) {
				const int wieSonder{isSonder(efld[x])};
				if (wieSonder) { // (efld[x]==-61 || efld[x]==-62|| efld[x]==-30)
					char ausg[6]{0}; // mindestens 4
					for(int i=0;i<wieSonder+1;i++) {
						ausg[i]=efld[x+i];
					}
					//GSchade: Hier Umlautausgabe
					mvwprintw(fieldWin,0,x-leftChar-aktumlz,ausg);
					x+=wieSonder;
					aktumlz+=wieSonder;
				} else {
					(void)mvwaddch(fieldWin, 0, x - leftChar-aktumlz,(unsigned char)efld[x] | fieldAttr);
				}
			}
		}
		wmove(fieldWin, 0, sbuch);
	}
	wrefresh(fieldWin);
} // void SEntry::zeichneFeld


/*
 * This creates a pointer to an entry widget.
 */
SEntry::SEntry(SScreen *cdkscreen,
		int xplace,
		int yplace,
		const char *title,
		const char *labelstr,
		chtype fieldAttrp,
		chtype fillerp,
		EDisplayType dispTypep,
		int fWidth,
		int minp,
		int maxp,
		bool obBox,
		bool pshadow,
		// GSchade Anfang
		GObj* pmutter,
		int highnr/*=0*/,
		int aktent/*=-1*/
		// GSchade Ende
		): GObj(cdkscreen,cdkscreen->window,obBox,pshadow,vENTRY,/*acceptsFocus*/1,/*hasFocus*/1,/*isVisible*/1,/*objnr*/aktent)
			,fieldWidth(fWidth),boxWidth(0),boxHeight(borderSize*2+1)
{
	// GSchade Anfang
	mutter=pmutter?pmutter:this;
//	cdktype=vENTRY;
	// GSchade Ende
	/* *INDENT-EQLS* */
	int xpos             = xplace;
	int ypos             = yplace;
	int junk             = 0;
	int horizontalAdjust, oldWidth;

	//	if ((entry = newCDKObject(SEntry, &my_funcs)) == 0) return (0);
//	objnr=aktent;
	//setBox(Box);
//	boxHeight =(borderSize * 2) + 1;

	/*
	 * If the fieldWidth is a negative value, the fieldWidth will
	 * be COLS-fieldWidth, otherwise, the fieldWidth will be the
	 * given width.
	 */
	fieldWidth = setWidgetDimension(parentWidth, fieldWidth, 0);
	boxWidth = fieldWidth + 2 * borderSize;

	/* Set some basic values of the entry field. */
	//label = 0;
	labelLen = 0;
	labelWin = 0;
	labelumlz=0; // GSchade

	// GSchade

	/* Translate the label char *pointer to a chtype pointer. */
	if (labelstr) {
		//		label = char2Chtypeh(labelstr, &labelLen, &junk /* GSchade Anfang*/ ,highnr /* GSchade Ende*/);
		labelp=new chtstr(labelstr,&labelLen,&junk,highnr);
		// GSchade Anfang
		for(int i=0;labelp->getinh()[i];i++) {
			labelumlz+=isSonder(labelp->getinh()[i]);
				// ((int)((unsigned char)labelp->getinh()[i])==194 ||(int)((unsigned char)labelp->getinh()[i])==195||(int)((unsigned char)labelp->getinh()[i])==226) 
		}
		// GSchade Ende
		boxWidth += labelLen;
	}

	oldWidth = boxWidth;
	boxWidth = setCdkTitle(title, boxWidth);
	horizontalAdjust =(boxWidth - oldWidth) / 2;

	boxHeight += titleLines;

	/*
	 * Make sure we didn't extend beyond the dimensions of the window.
	 */
	boxWidth = MINIMUM(boxWidth, parentWidth);
	boxHeight = MINIMUM(boxHeight, parentHeight);
	fieldWidth = MINIMUM(fieldWidth, (size_t)boxWidth - labelLen +labelumlz - 2 * borderSize);

	/* Rejustify the x and y positions if we need to. */
	alignxy(cdkscreen->window, &xpos, &ypos, boxWidth, boxHeight);

	/* Make the label window. */
	win = newwin(boxHeight, boxWidth, ypos, xpos);
	if (!win) {
		destroyCDKObject();
		return;
	} else {
		keypad(win, TRUE);

		/* Make the field window. */
		fieldWin = subwin(win, 1, fieldWidth,
				(ypos + titleLines + borderSize),
				(xpos + labelLen -labelumlz
				 + horizontalAdjust
				 + borderSize));
		if (!fieldWin) {
			destroyCDKObject();
		} else {
			keypad(fieldWin, TRUE);

			/* Make the label win, if we need to. */
			if (labelstr) {
				labelWin = subwin(win, 1, labelLen,
						ypos + titleLines + borderSize,
						xpos + horizontalAdjust + borderSize);
			}

			/* Make room for the info char * pointer. */
			// info ist vorher noch leer
			//efld.resize(maxp+3);
			efld.reserve(maxp+3);

			infoWidth = maxp + 3;

			/* *INDENT-EQLS* Set up the rest of the structure. */
//			screen        = cdkscreen;
//			parent                = cdkscreen->window;
			shadowWin             = 0;
			fieldAttr             = fieldAttrp;
			//				fieldWidth            = fieldWidth;
			filler                = fillerp;
			hidden                = fillerp;
			/*ObjOf(this)->*/inputWindow   = fieldWin;
//			ObjOf(this)->acceptsFocus  = TRUE;
//			dataPtr             = NULL;
//			shadow                = pshadow;
			screenCol             = 0;
			sbuch=0;
			leftChar              = 0;
			lbuch=0;
			minlen                   = minp;
			maxlen                   = maxp;
			//				boxWidth              = boxWidth;
			//				boxHeight             = boxHeight;
			//				initExitType(this);
			exitType =vNEVER_ACTIVATED;
			dispType              = dispTypep;
			callbfn            = &SEntry::schreibl;

			/* Do we want a shadow? */
			if (pshadow) {
				shadowWin = newwin(
						boxHeight,
						boxWidth,
						ypos + 1,
						xpos + 1);
			}
			registerCDKObject(cdkscreen, vENTRY);
		}
	}
	//	return (entry);
} // SEntry::SEntry

chtype GObj::holcht()
{
//	bool functionKey;
	chtype input{0};
	if (actionzahl) {
		if (actionnr==actionzahl) {
			hoerauf=1;
		} else {
			input=actions[actionnr++];
		}
	} else {
		input=getcCDKObject(/*&functionKey*/);
	}
	return input;
}


/*
 * This means you want to use the given entry field. It takes input
 * from the keyboard, and when its done, it fills the entry info
 * element of the structure with what was typed.
 */
const char* SEntry::activateCDKEntry(chtype *pactions,int (&WeitereZc)[6], int obpfeil/*=0*/)
{
	chtype input{0};
	const char *ret{0};
	/* Draw the widget. */
	drawCDKEntry(/*entry, ObjOf(entry)->*/obbox);
	hoerauf=0;
	actionnr=0;
	actions=pactions;
	if (actions) actionzahl=chlen(actions); else actionzahl=0;
//	if (!actions) KLA
		for (;;) {
			//static int y=2;
			*WeitereZc=0;
			input = holcht(); // (chtype)getchCDKObject(&functionKey);
			// GSchade Anfang //=Return
			if (input==KEY_ENTER) { // 343, oktal: 0527, in curses.h
	// 3.1.19: bei Return (343) pruefen, ob Teil von Alphalist oder FSelect, ob Schalter zur Anzeige der Auswahlen (zeichnescroll) eingestellt; 
	// falls ja, umstellen und nicht aufhoeren (vEARLY_EXIT),
	// falls FSelect, dann dort inject, andernfalls Rückfrage zum Schluss 
				if ((mutter->cdktype==vALPHALIST || mutter->cdktype==vFSELECT) && ((ComboB*)mutter)->zeichnescroll) {
					if (mutter->cdktype==vALPHALIST) {
						((ComboB*)mutter)->zeichnescroll=0;
						// muss, wenn nicht gleich wieder auf Return gedrückt wird, wieder auf 1 gesetzt werden
						*WeitereZc=-12;
					} else if (mutter->cdktype==vFSELECT) {
						int iret{((SFSelect*)mutter)->injectSFselect(/*GObj *object, */input)};
						ret =iret?resultData.valueString:0;
						if (((SFSelect*)mutter)->exitType) {
							((ComboB*)mutter)->zeichnescroll=0;
						} else {
							((ComboB*)mutter)->zeichnescroll=1;
						}
						//					exitType = vNORMAL;
						*WeitereZc=-12;
						return ret;
					}
				}
			} else {
				if ((mutter->cdktype==vALPHALIST || mutter->cdktype==vFSELECT) && !((ComboB*)mutter)->zeichnescroll) {
          ((ComboB*)mutter)->zeichnescroll=1;
				}
				if (input==27) {
					*WeitereZc = holcht(); // (chtype)getchCDKObject(&functionKey);
					const int wieSonder{isSonder(*WeitereZc)};
					if (wieSonder) { // (*Zweitzeichen==194||*Zweitzeichen==195||*Zweitzeichen==226)
						for(int i=0;i<wieSonder;) {
							++i;
							WeitereZc[i] = holcht(); // (chtype)getchCDKObject(&functionKey);
						}
					} else if (*WeitereZc=='+') {
						// Vervollständigen
						if (mutter->cdktype==vALPHALIST) {
							completeWordCB(mutter->cdktype, 0, (ComboB*)mutter, 0);
						}
					}
				} else if (input==9||(obpfeil && input==KEY_DOWN)) {
					*WeitereZc=-9;
				} else if (input==KEY_BTAB||(obpfeil && input==KEY_UP)) {
					*WeitereZc=-8;
				} else if (input==KEY_NPAGE) {
					*WeitereZc=-10;
				} else if (input==KEY_PPAGE) {
					*WeitereZc=-11;
				}
			}
//		if (0) {
//				static bool afk{0}; static chtype ai{0}; static int aZz{0}; static EExitType	aex{vEARLY_EXIT};
				/*
				if (afk!=functionKey||ai!=input||aZz!=*Zweitzeichen||aex!=entry->exitType)
					mvwprintw(entry->parent,y++,30,"eingeb:%i %i %i %i",functionKey,input,*Zweitzeichen,entry->exitType);
				 */
//			afk=functionKey; ai=input; aZz=*Zweitzeichen; aex=entry->exitType;
//			}
			

			//mvwprintw(entry->parent,1,60,"info:%s -> ",entry->info);
			// GSchade Ende
			/* Inject the character into the widget. */
//			ret = injectSEntry(entry, input);
			ret=injectSEntry(input)?resultData.valueString:0/*unknownString*/;
			// GSchade Anfang
      /*
			mvwprintw(entry->parent,1,80,"info:%s ",entry->info);
			for(int i=0;i<strlen(entry->info);i++) {
				mvwprintw(entry->parent,2+i,60,"i: %i: %i",i,entry->info[i]);
			}
			wrefresh(entry->parent); // gleichbedeutend: wrefresh(entry->obj.screen->window);
      */
      drawCDKEntry(/*entry, ObjOf(entry)->*/obbox);
      // GSchade Ende

			if (this->exitType != vEARLY_EXIT||*WeitereZc==-8||*WeitereZc==-9||*WeitereZc==-10||*WeitereZc==-11) {
//					mvwprintw(entry->parent,3,2,"Zweitzeichen: %i         , Drittzeichen: %i     ",*Zweitzeichen,*Drittzeichen);
				return ret;
			}
//			mvwprintw(entry->parent,3,2,"kein Zweitzeichen");
		}
		/*
	KLZ else KLA
		int length{chlen(actions)};
		// Inject each character one at a time.
		for (int x = 0; x < length; x++) {
//					mvwprintw(entry->parent,4,2,"vor inject 2");
//			ret = injectSEntry(entry, actions[x]);
			ret = injectSEntry(actions[x])?resultData.valueString:0; //unknownString
			if (this->exitType != vEARLY_EXIT) {
				return ret;
			}
		}
	KLZ
	*/
	/* Make sure we return the correct info. */
	if (this->exitType == vNORMAL) {
		return this->efld.c_str();
	} else {
		return 0;
	}
} // char * SEntry::activateCDKEntry(chtype *actions,int *Zweitzeichen/*=0*/,int *Drittzeichen/*=0*/, int obpfeil/*=0*/)


/*
 * This activates the file selector.
 */
const char* SAlphalist::activateCDKAlphalist(chtype *actions,int (&WeitereZc)[6],int obpfeil/*=0*/)
{
   /* Draw the widget. */
   drawCDKAlphalist(obbox,/*obmitscroller*/1);
   /* Activate the widget. */
   const char *ret = entryField->activateCDKEntry(actions,WeitereZc,obpfeil);
   /* Copy the exit type from the entry field. */
//   copyExitType(this, this->entryField);
	 exitType=entryField->exitType;
   /* Determine the exit status. */
   if (this->exitType != vEARLY_EXIT) {
      return ret;
   }
   return 0;
}



/*
 * This draws the entry field.
 */
//void SEntry::drawCDKEntry(bool Box)
void SEntry::drawCDKEntry(bool Box)
{
//	SEntry *entry =(SEntry *)object;
	/* Did we ask for a shadow? */
	if (this->shadowWin) {
		drawShadow(this->shadowWin);
	}
	/* Box the widget if asked. */
	if (Box) {
		drawObjBox(this->win/*, ObjOf(this)*/);
	}
	drawCdkTitle(this->win/*, object*/);
	wrefresh(this->win);

	/* Draw in the label to the widget. */
	if (this->labelWin) {
		//int f1,f2;
		writeChtype(this->labelWin, 0, 0, this->labelp->getinh(), HORIZONTAL, 0, this->labelLen);
		wrefresh(this->labelWin);
	}
	this->zeichneFeld();
}

/*
 * This injects a single character into the widget.
 */
int SEntry::injectSEntry(chtype input)
{
//	SEntry *widget =(SEntry *)object;
	int ppReturn{1};
	const char *ret{0}/*unknownString*/;
	bool complete{FALSE};
	static char umlaut[6]{0}; // mindestens 4
	const int inpint{(int)input};
//	static chtype altinput{0},uraltinput{0},ururaltinput{0};
//	static int zahl{0};
//	mvwprintw(screen->window,1,2,"%i injectSEntry %c %i          ",zahl-3,ururaltinput,ururaltinput);
//	mvwprintw(screen->window,2,2,"%i injectSEntry %c %i          ",zahl-2,uraltinput,uraltinput);
//	mvwprintw(screen->window,3,2,"%i injectSEntry %c %i          ",zahl-1,altinput,altinput);
//	mvwprintw(screen->window,4,2,"%i injectSEntry %c %i          ",zahl++,input,input);
//	ururaltinput=uraltinput;
//	uraltinput=altinput;
//	altinput=input;
//	screen->refreshCDKScreen(); // 21.12.18: Übeltäter, schreibt Listeneinträge an falsche Stellen
	/* Set the exit type. */
	setExitType(0);
	/* Refresh the widget field. */
	zeichneFeld();
	/* Check if there is a pre-process function to be called. */
	size_t/*int*/ currPos{(size_t)(screenCol+leftChar)};
	if (preProcessFunction) {
		ppReturn = (preProcessFunction)(vENTRY,
				this,
				(preProcessData),
				input);
	}
	/* Should we continue? */
	if (ppReturn) {
		/* Check a predefined binding... */
		if (checkCDKObjectBind(input)) {
			//			checkEarlyExit(this);
			if (earlyExit != vNEVER_ACTIVATED) 
				exitType = earlyExit;
			complete = TRUE;
		} else {
			const size_t efldLength=efld.length();
//			size_t/*int*/ currPos = screenCol + leftChar; // zum untenstehenden Debuggen nach oben verschoben
			switch (input) {
				case KEY_UP:
				case KEY_DOWN:
					Beep();
					break;
				case KEY_HOME:
					leftChar = 0;
					lbuch=0;
					screenCol = 0;
					sbuch=0;
					zeichneFeld();
//					mvwprintw(parent,3,3,"Key_home");
					wrefresh(win);
					//refreshCDKScreen(allgscr);
					break;
				case CDK_TRANSPOSE:
					if (currPos >= efldLength - 1) {
						Beep();
					} else {
						const char holder{efld[currPos]};
						efld[currPos] = efld[currPos + 1];
						efld[currPos + 1] = holder;
						zeichneFeld();
					}
					break;
				case KEY_END:
					settoend();
					zeichneFeld();
					break;
				case KEY_LEFT:
					if (currPos <= 0) {
						Beep();
					} else if (!screenCol) {
						/* Scroll left.  */
						if (currPos>1) {
							if (isSonder(efld[currPos-3])==2) leftChar-=2;
							else if (isSonder(efld[currPos-2])) leftChar--;
						}
						leftChar--;
						lbuch--;
						zeichneFeld();
					} else {
						/* Move left. */
						wmove(fieldWin, 0, --sbuch);
						screenCol--;
						if (currPos>2 && isSonder(efld[currPos-3])==2) screenCol-=2;
						else if (currPos>1 && isSonder(efld[currPos-2])) screenCol--; 
					}
					break;
				case KEY_RIGHT:
					if (currPos >= efldLength || currPos>(size_t)maxlen) {
						Beep();
					} else if (sbuch == fieldWidth - 1) {
						/* Scroll to the right. */
						const int wieSonderleft{isSonder(efld[leftChar])};
						if (wieSonderleft) { // (efld[leftChar]==-61 || efld[leftChar]==-62|| efld[leftChar]==-30)
							screenCol--;
							leftChar++;
							if (wieSonderleft==2) {
								screenCol--;
								leftChar++;
							}
						}
						leftChar++;
						lbuch++;
						screenCol+=isSonder(efld[currPos]);
						zeichneFeld();
					} else {
						/* Move right. */
						wmove(fieldWin, 0, ++sbuch);
						screenCol++;
						screenCol+=isSonder(efld[currPos]);
					}
					break;
				case KEY_BACKSPACE:
				case KEY_DC:
					if (dispType == vVIEWONLY) {
						Beep();
					} else {
						// mvwprintw(parent,1,100,"!!!!!!!!!, currPos: %i  ",currPos);
						bool success{FALSE};
						if (input == KEY_BACKSPACE) {
							--currPos;
							if (isSonder(efld[currPos-2])==2) currPos-=2;
							else if (isSonder(efld[currPos-1])) --currPos;
						}
						// .. und jetzt fuer den zu loeschenden
						const int obuml{isSonder(efld[currPos])};
						if (currPos >= 0 && efldLength > 0) {
							if (currPos < efldLength) {
						// mvwprintw(parent,2,100,"!!!!!!!!!, currPos: %i, obuml: %i",currPos,obuml);
								// wrefresh(parent);
								efld.erase(currPos,1+obuml);
								success = TRUE;
							} else if (input == KEY_BACKSPACE) {
								efld.resize(efldLength-1);
								success = TRUE;
                if (efldLength>1) if (obuml) 
									efld.resize(efldLength-2);
              }
						}
						if (success) {
							if (input == KEY_BACKSPACE) {
								if (screenCol > 0 && !lbuch) {
									screenCol--;
									screenCol-=obuml;
                  sbuch--;
                } else {
									leftChar--;
									const int wieSonderbs{isSonder(efld[leftChar-1])};
									if (wieSonderbs) { 
										leftChar--;
										screenCol++;
										if (wieSonderbs==2) {
											leftChar--;
											screenCol++;
										}
									}
									lbuch--;
									screenCol-=obuml;
                }
							}
							zeichneFeld();
						} else {
							Beep();
						}
					}
					break;
				case KEY_ESC:
					setExitType(input);
					complete = TRUE;
//					mvwprintw(parent,2,2,"Key_esc");
					break;
				case CDK_ERASE:
					if (efldLength) {
						cleanCDKEntry();
						zeichneFeld();
					}
					break;
				case CDK_CUT:
					if (efldLength) {
						GPasteBuffer=efld;
						cleanCDKEntry();
						zeichneFeld();
					} else {
						Beep();
					}
					break;
				case CDK_COPY:
					if (efldLength) {
						GPasteBuffer=efld;
					} else {
						Beep();
					}
					break;
				case CDK_PASTE:
					if (!GPasteBuffer.empty()) {
						setCDKEntryValue(GPasteBuffer);
						zeichneFeld();
					} else {
						Beep();
					}
					break;
				case KEY_TAB:
				case KEY_ENTER:
					if (efldLength >= (size_t)minlen) {
						setExitType(input);
						ret = efld.c_str();
						complete = TRUE;
					} else {
						Beep();
					}
					break;
				case KEY_ERROR:
					setExitType(input);
					complete = TRUE;
					break;
				case CDK_REFRESH:
					screen->eraseCDKScreen();
					screen->refreshCDKScreen();
					break;
				default:
	        int wieSonder{isSonder(inpint)};
					/*
	        static int ablehnenzahl{0};
					long aktablz{(long)(efldLength+wieSonder-maxlen)};
	        if (aktablz>0) ablehnenzahl+=aktablz;
					if (ablehnenzahl-- >0) break;
					*/

					if (wieSonder) { // (inpint==194 || inpint==195 || inpint==226)
						//		printf("Eintrag: %i\n",inpint);
						//		mvwprintw(screen->window,5,2,"schreibe Umlaut");
						memset(umlaut,0,elemzahl(umlaut));
						*umlaut=inpint;
					} else if (isSonder(*umlaut) && !umlaut[1]) {
						//		printf("Folgezeichen: %i\n",inpint);
						//printf("%c (%i)\n",inpint,inpint);
						//		mvwprintw(screen->window,5,2,"schrieb  Umlaut (1)");
						umlaut[1]=inpint;
					} else if (isSonder(*umlaut)==2 && !umlaut[2]) {
						//		mvwprintw(screen->window,5,2,"schrieb  Umlaut (2)");
						umlaut[2]=inpint;
					} else {
						//		mvwprintw(screen->window,5,2,"               ");
						//		printf("sonstiges Zeichen: %i\n",inpint);
						memset(umlaut,0,elemzahl(umlaut));
					}
					// printf("%i %i %i\n",umlaut[0],umlaut[1],umlaut[2]);
					if (umlaut[1]) {
//						printf("Sonderdruck Anfang");
//						setlocale(LC_ALL,"");
			//			wprintw(fieldWin,"%s",umlaut);
//			wprintw(fieldWin,"Achtung!");
						schreibl(umlaut[0]);
						schreibl(umlaut[1]);
						if (umlaut[2]) schreibl(umlaut[2]);
						memset(umlaut,0,elemzahl(umlaut));
						//						printf("\n%i %i %i\n",umlaut[0],umlaut[1],umlaut[2]);
//						printf("Sonderdruck Ende");
					} else if (!*umlaut) {
						(this->*callbfn)(input); // auch schreibl
					}
					break;
			}
		}
		/* Should we do a post-process? */
		if (!complete && ((postProcessFunction))) {
			(postProcessFunction)(vENTRY,
					this,
					(postProcessData),
					input);
		}
	}
	if (!complete) setExitType(0);
	resultData.valueString = ret;
	mvwprintw(screen->window,1,1,"leftChar: %i, lbuch: %i, screenCol: %i, sbuch: %i, efld.length(): %i, currPos: %i    ",leftChar,lbuch,screenCol,sbuch,efld.length(),currPos);
//	mvwprintw(screen->window,2,1,"umlaut: %i %i %i %i (%c %c %c %c)",umlaut[0],umlaut[1],umlaut[2],umlaut[3],umlaut[0],umlaut[1],umlaut[2],umlaut[3]);
	for(size_t i=0;i<30;i++) {
		if (i<efld.length()) {
			mvwprintw(screen->window,i+1,100,"%i: %i %i %c   ",i,efld[i],(unsigned char)efld[i],efld[i]);
		} else {
			mvwprintw(screen->window,i+1,100,"%i:                ",i);
		}
	}
	screen->refreshCDKScreen(); // 21.12.18: Übeltäter, schreibt Listeneinträge an falsche Stellen
	return (ret != 0/*unknownString*/);
} // int SEntry::injectSEntry(chtype input)

/*
 * This removes the old information in the entry field and keeps the
 * new information given.
 */
void SEntry::setCDKEntryValue(string newValue)
{
	/* OK, erase the old value, and copy in the new value. */
	efld=newValue;
	//			if (maxlen>efld.length()) efld.resize(maxlen);
	settoend();
}
/*
void SEntry::setCDKEntryValue(const char *newValue)
{
	// If the pointer sent in is the same pointer as before, do nothing.
	if (!newValue || this->efld != newValue) {
		// Just to be sure, if lets make sure the new value isn't null.
		if (!newValue) {
			// Then we want to just erase the old value.
			efld.clear();
//			efld.resize(infoWidth);
			// Set the pointers back to zero.
			this->leftChar = 0;
      this->lbuch=0;
			this->screenCol = 0;
      this->sbuch=0;
		} else {
			setCDKEntryValue(string(newValue));
		}
	}
}
*/

/*
const char* SEntry::getCDKEntryValue()
{
	return efld.c_str();
}
*/

/*
 * This sets specific attributes of the entry field.
 */
void SEntry::setCDKEntry(
//		const char *value,
		string& value,
		int pmin,
		int pmax,
		bool Box GCC_UNUSED)
{
	setCDKEntryValue(value);
	minlen=pmin;
	maxlen=pmax;
}


void SEntry::settoend()
{
  screenCol=sbuch=leftChar=lbuch=0;
	vector<size_t> sColvon;
	for(size_t pos=0;pos<efld.length();pos++) {
	  sColvon.push_back(pos);
		pos+=isSonder(efld[pos]);
	}
	screenCol=efld.length();
	const long diff{(long)sColvon.size()-(long)fieldWidth+1};
	if (diff<=0) {
		sbuch=sColvon.size();
		if (efld.length()>=maxlen) {
			sbuch--;
			screenCol=sColvon[sbuch];
		}
	} else {
		lbuch=diff;
		sbuch=fieldWidth-1;
		leftChar=sColvon[diff];
		screenCol-=leftChar;
		if (efld.length()>=maxlen) {
			leftChar--;
			lbuch--;
			screenCol++;
			sbuch++;
		}
	}
	/*
		 if ((lbuch=fieldWidth-1
		 for(int i=efld.length();i;) {
		 --i;
    if (sbuch<fieldWidth) {
      screenCol++;
			sbuch+=1-isSonder(efld[i]);
      // if (!isSonder(efld[i])) sbuch++; // ((unsigned char)efld[i]!=194 && (unsigned char)efld[i]!=195&& (unsigned char)efld[i]!=226) sbuch++;
    } else {
      leftChar++;
			lbuch+=1-isSonder(efld[i]);
      // if (!isSonder(efld[i])) lbuch++; // ((unsigned char)efld[i]!=194 && (unsigned char)efld[i]!=195&& (unsigned char)efld[i]!=226) lbuch++;
    }
  }
	// Cursor rechts des letzten Buchstabens setzen
  if (sbuch>=fieldWidth && (sbuch+lbuch<maxlen)) {
    leftChar++;
		lbuch++;
    screenCol--;
		sbuch--;
  }
	*/
}

/*
 * This erases the information in the entry field
 * and redraws a clean and empty entry field.
 */
void SEntry::cleanCDKEntry()
{
	/* Erase the information in the character pointer. */
	efld.clear();
//	efld=string(infoWidth,'\0');
	/* Clean the entry screen field. */
	(void)mvwhline(fieldWin, 0, 0, this->filler, fieldWidth);
	/* Reset some variables. */
	this->screenCol = 0;
	sbuch=0;
	this->leftChar = 0;
	lbuch=0;
	/* Refresh the entry field. */
	wrefresh(fieldWin);
}  

/*
 * This erases an entry widget from the screen.
 */
void SEntry::eraseCDKEntry()
{
//	if (validCDKObject(object))
	{
		eraseCursesWindow(fieldWin);
		eraseCursesWindow(labelWin);
		eraseCursesWindow(win);
		eraseCursesWindow(shadowWin);
	}
}

/*
 * This erases the file selector from the screen.
 */
void ComboB::eraseObj() // eraseCDKFselect(/*GObj *object*/)
{
	//   if (validCDKObject(object)) {
	//      SFSelect *fselect =(SFSelect *)object;
	scrollField->eraseCDKScroll(/*fselect->scrollField*/);
	entryField->eraseCDKEntry(/*fselect->entryField*/);
	eraseCursesWindow(shadowWin);
	eraseCursesWindow(/*fselect->*/win);
	//   }
}
/*
 * This erases the file selector from the screen.
 */
/*
void SAlphalist::eraseCDKAlphalist() // _eraseCDKAlphalist
{
	//   if (validCDKObject(object))
	{
		//      SAlphalist *alphalist =(SAlphalist *)object;
		scrollField->eraseCDKScroll();
		//      eraseCDKEntry(entryField);
		entryField->eraseCDKEntry();
		eraseCursesWindow(win);
	}
}
*/

/*
 * This function erases the scrolling list from the screen.
 */
void SScroll::eraseCDKScroll/*_eraseCDKScroll*/(/*GObj *object*/)
{
//   if (validCDKObject(object))
   {
//      SScroll *scrollp =(SScroll *)object;
      eraseCursesWindow(win);
      eraseCursesWindow(shadowWin);
   }
}

/*
 * This calls refreshCDKScreen. (made consistent with widgets)
 */
void GObj::drawCDKScreen()
{
   screen->refreshCDKScreen();
}

/*
 * This refreshes all the objects in the screen.
 */
void SScreen::refreshCDKScreen(/*SScreen *cdkscreen*/)
{
//	int objectCount = /*screen->*/objectCount;
	int x;
	int focused = -1;
	int visible = -1;
#define richtig
#ifdef richtig
	refreshCDKWindow(/*screen->*/window);
#endif
	/* We erase all the invisible objects, then only
	 * draw it all back, so that the objects
	 * can overlap, and the visible ones will always
	 * be drawn after all the invisible ones are erased */
	for (x = 0; x < objectCount; x++) {
		GObj *obj = /*screen->*/object[x];
		if (obj) {
			//		if (validObjType(obj, ObjTypeOf(obj))) KLA
			if (obj->validObjType(obj->cdktype)) {
				if (obj->isVisible) {
					if (visible < 0)
						visible = x;
					if (obj->hasFocus && focused < 0)
						focused = x;
				} else {
					obj->eraseObj();
				}
			}
		}
	}
	for (x = 0; x < objectCount; x++) {
		GObj *obj = /*screen->*/object[x];
		if (obj) {
			//		if (validObjType (obj, ObjTypeOf (obj))) KLA
			if (obj->validObjType(obj->cdktype)) {
				obj->hasFocus =(x == focused);
				if (obj->isVisible) {
					// GSchade 13.11.18 hier gehts vorbei
					obj->drawObj(obj->obbox);
				}
			}
		}
	}
} // void SScreen::refreshCDKScreen()


/*
 * This sets the widgets box attribute.
 */
/*
void GObj::setBox(bool Box)
{
	obbox = Box;
	borderSize = Box ? 1 : 0;
}
*/

/*
 * This sets the background attribute of the widget.
 */
void SEntry::setBKattrEntry(chtype attrib)
{
	wbkgd(win, attrib);
	wbkgd(fieldWin, attrib);
	if (labelWin) {
		wbkgd(labelWin, attrib);
	}
}

/*
 * This sets the attribute of the entry field.
 */
void SEntry::setCDKEntryHighlight(chtype highlight, bool cursor)
{
	wbkgd(fieldWin, highlight);
	fieldAttr = highlight;
	curs_set(cursor);
	/*
	 *  FIXME -  if (cursor) { move the cursor to this widget }
	 */
}

void SEntry::focusCDKEntry()
{
	wmove(fieldWin, 0, sbuch);
	wrefresh(fieldWin);
}

void SEntry::unfocusCDKEntry()
{
	drawObj(obbox);
	wrefresh(fieldWin);
}

void GObj::refreshDataCDK()
{
}

void GObj::saveDataCDK()
{
}

/*
 * The alphalist's focus resides in the entry widget.  But the scroll widget
 * will not draw items highlighted unless it has focus.  Temporarily adjust the
 * focus of the scroll widget when drawing on it to get the right highlighting.
 */
//   bool save = HasFocusObj(ObjOf(widget->scrollField));
#define SaveFocus(widget) \
   bool save = widget->scrollField->hasFocus; \
	 widget->scrollField->hasFocus=widget->entryField->hasFocus

//   HasFocusObj(ObjOf(widget->scrollField)) = save
#define RestoreFocus(widget) \
	widget->scrollField->hasFocus=save

void ComboB::injectMyScroller(chtype key)
{
	SaveFocus(this);
	scrollField->injectSScroll(key);
	RestoreFocus(this);
}

/*
 * This injects a single character into the alphalist.
 */
int SAlphalist::injectSAlphalist(chtype input)
{
//   SAlphalist *alphalist =(SAlphalist *)object;
   const char *ret;
   /* Draw the widget. */
   drawCDKAlphalist(obbox);
   /* Inject a character into the widget. */
	 ret=entryField->injectSEntry(input)?entryField->resultData.valueString:0/*unknownString*/;
	 /* Copy the exit type from the entry field. */
//   copyExitType(this, this->entryField);
	 exitType=entryField->exitType;
   /* Determine the exit status. */
   if (this->exitType == vEARLY_EXIT)
      ret = 0/*unknownString*/;
   resultData.valueString = ret;
   return (ret != 0/*unknownString*/);
}

/*
 * This injects a single character into the file selector.
 */
int SFSelect::injectSFselect(/*GObj *object, */chtype input)
{
	//   SFSelect *fselect =(SFSelect *)object;
	const char *filename{""};
	bool complete{FALSE};
	/* Let the user play. */
	if (entryField) {
	 if (entryField->injectSEntry(/*this->entryField, */input)) 
		 filename=entryField->resultData.valueString;
  }
	/* Copy the entry field exitType to the fileselector. */
//	copyExitType(this, this->entryField);
  exitType=entryField->exitType;	
	/* If we exited early, make sure we don't interpret it as a file. */
	if (this->exitType == vEARLY_EXIT) {
		return 0;
	}
	/* Can we change into the directory? */
	bool file{chdir(filename)};
	if (chdir(this->pwd.c_str())) {
		return 0;
	}
	// damit auch Verzeichnisse ausgewählt werden können
	if (pfadname==filename) {
		complete = TRUE;
	} else {
		this->pfadname=filename;
	}
	/* If it's not a directory, return the filename. */
	if (file) {
		/* It's a regular file, create the full path. */
		// this->pfadname=filename;
		/* Return the complete pathname. */
		complete = TRUE;
	} else {
		/* Set the file selector information. */
		setCDKFselect(/*this, */filename
				,this->fieldAttribute
				,this->fillerChar
				,this->highlight
				,this->dirAttribute.c_str()
				,this->fileAttribute.c_str()
				,this->linkAttribute.c_str()
				,this->sockAttribute.c_str()
				, /*ObjOf(this)->*/obbox);

		/* Redraw the scrolling list. */
		drawMyScroller(/*this*/);
	}
	if (!complete) {
		setExitType(/*this, */0);
	}
  resultData.valueString=pfadname.c_str();
	return !pfadname.empty();
}


/*
 * This sets multiple attributes of the widget.
 */
/*
void SAlphalist::setCDKAlphalist(vector<string> *plistp, chtype fillerChar, chtype highlight, bool Box)
{
   setCDKAlphalistContents(plistp);
   setCDKAlphalistFillerChar(fillerChar);
   setCDKAlphalistHighlight(highlight);
   setCDKAlphalistBox(Box);
}
*/

/*
 * This sets certain attributes of the scrolling list.
 */
void SScroll::setCDKScroll(vector<string> *plistp, bool numbers, chtype hl, bool Box)
{
   setCDKScrollItems(plistp, numbers);
	 highlight=hl;
	 obbox=Box;
}

/*
 * This sets the box attribute of the scrolling list.
 */
/*
	 // statt dessen: setBox
void SScroll::setCDKScrollBox(//SScroll *scrollp, 
							bool Box)
{
   //ObjOf(scrollp)->
	obbox = Box;
   //ObjOf(scrollp)->
	borderSize = Box ? 1 : 0;
}
bool SScroll::getCDKScrollBox()
{
	return //ObjOf(scrollp)->
		obbox;
}
*/

/*
 * This sets the scrolling list items.
 */
void SScroll::setCDKScrollItems(vector<string> *plistp, bool numbers)
{
   if (createCDKScrollItemList(numbers, plistp) <= 0)
      return;
   /* Clean up the display. */
   for (int x = 0; x < this->viewSize; x++) {
      writeBlanks(this->win, 1, x+borderSize+titleLines, // SCREEN_YPOS(this, x),
		   HORIZONTAL, 0, this->boxWidth - 2);
   }
   setViewSize(listSize);
   setCDKScrollPosition(0);
   this->leftChar = 0;
}

void SScroll::setCDKScrollCurrentTop(/*SScroll *widget, */int item)
{
   if (item < 0)
      item = 0;
   else if (item > /*widget->*/maxTopItem)
      item = /*widget->*/maxTopItem;
   /*widget->*/currentTop = item;
   SetPosition(/*(CDKSCROLLER *)widget,*/ item);
}


/*
 * This allows the user to accelerate to a position in the scrolling list.
 */
void SScroll::setCDKScrollPosition(int item)
{
 SetPosition(item);
}

/*
 * This function sets the information inside the file selector.
 */
void SAlphalist::setCDKAlphalistContents(vector<string> *plistp)
{
	 plist=*plistp;
   /* Set the information in the scrolling list. */
   scrollField->setCDKScroll(plistp, NONUMBERS, scrollField->highlight, scrollField->obbox);
   /* Clean out the entry field. */
   setCDKAlphalistCurrentItem(0);
   entryField->cleanCDKEntry();
   /* Redraw the this. */
   this->eraseObj(); // eraseCDKAlphalist();
   this->drawCDKAlphalist(obbox);
}

/*
 * This returns the contents of the widget.
 */
/*
vector<string> *SAlphalist::getCDKAlphalistContents()
{
	return &plist;
}
*/

/*
 * Get/set the current position in the scroll-widget.
 */
/*
int SAlphalist::getCDKAlphalistCurrentItem()
{
   return scrollField->currentItem;
}
*/

void SAlphalist::setCDKAlphalistCurrentItem(int item)
{
	if (plist.size()) {
		scrollField->setCDKScrollCurrent(item);
		entryField->setCDKEntryValue(*next(plist.begin(),item));
	}
}

void SScroll::setCDKScrollCurrent(int item)
{
	SetPosition(item);
}

/*
 * This sets the filler character of the entry field of the alphalist.
 */
/*
void SAlphalist::setCDKAlphalistFillerChar(chtype fillerChar)
{
	fillerChar = fillerChar;
	entryField->filler=fillerChar;
}
*/

/*
chtype SAlphalist::getCDKAlphalistFillerChar()
{
   return fillerChar;
}
*/

/*
 * This sets the highlight bar attributes.
 */
/*
void SAlphalist::setCDKAlphalistHighlight(chtype hl)
{
   highlight = hl;
}
*/

/*
chtype SAlphalist::getCDKAlphalistHighlight()
{
   return highlight;
}
*/

/*
 * This sets whether or not the widget will be drawn with a box.
 */
/*
void SAlphalist::setCDKAlphalistBox(bool Box)
{
  obbox = Box;
  borderSize = Box ? 1 : 0;
}
*/

/*
bool SAlphalist::getCDKAlphalistBox()
{
  return obbox;
}
*/

/*
 * These functions set the drawing characters of the widget.
 */
void SAlphalist::setMyULchar(chtype character)
{
	 entryField->ULChar=character;
}
void SAlphalist::setMyURchar(chtype character)
{
	 entryField->URChar=character;
}
void SAlphalist::setMyLLchar(chtype character)
{
	 scrollField->LLChar=character;
}
void SAlphalist::setMyLRchar(chtype character)
{
	 scrollField->LRChar=character;
}
void SAlphalist::setMyVTchar(chtype character)
{
   entryField->VTChar=character;// setCDKEntryVerticalChar(character);
   scrollField->VTChar=character;//setCDKScrollVerticalChar(character);
}
void SAlphalist::setMyHZchar(chtype character)
{
   entryField->HZChar=character;//setCDKEntryHorizontalChar(character);
   scrollField->HZChar=character;//setCDKScrollHorizontalChar(character);
}
void SAlphalist::setMyBXattr(chtype character)
{
   entryField->BXAttr=character; //setCDKEntryBoxAttribute(character);
   scrollField->BXAttr=character; // setCDKScrollBoxAttribute(character);
}
/*
 * This sets the background attribute of the widget.
 */
void SAlphalist::setMyBKattr(chtype character)
{
	 entryField->setBKattrEntry(character);//setCDKEntryBoxAttribute(character);
	 scrollField->setBKattrScroll(character);// setCDKScrollBoxAttribute(character);
}

/*
 * This sets the background attribute of the widget.
 */
void SScroll::setBKattrScroll(chtype attrib)
{
	//      SScroll *widget =(SScroll *)object;
	wbkgd(this->win, attrib);
	wbkgd(this->listWin, attrib);
	if (this->scrollbarWin) {
		wbkgd(this->scrollbarWin, attrib);
	}
}

/*
 * Start of callback functions.
 */
static int adjustAlphalistCB(EObjectType objectType GCC_UNUSED, void
		*object GCC_UNUSED,
		void *clientData,
		chtype key)
{
	/* *INDENT-EQLS* */
	SAlphalist *alphalist = (SAlphalist *)clientData;
	SScroll *scrollp      = alphalist->scrollField;
	SEntry *entry         = alphalist->entryField;
	if (scrollp->listSize > 0) {
		/* Adjust the scrolling list. */
		alphalist->injectMyScroller(key);
		/* Set the value in the entry field. */
		entry->setCDKEntryValue(scrollp->pitem[scrollp->currentItem].chtype2Char());
		entry->drawObj(alphalist->obbox);
		return TRUE;
	}
	Beep();
	return FALSE;
}

/*
 * This tries to complete the word in the entry field.
 */
int completeWordCB(EObjectType objectType GCC_UNUSED, void *object GCC_UNUSED, void *clientData, chtype key GCC_UNUSED)
{
   /* *INDENT-EQLS* */
   SAlphalist *alphalist = (SAlphalist *)clientData;
   SEntry *entry         = (SEntry *)alphalist->entryField;
   SScroll *scrollp      = 0;
	 vector<string> altWords;
//   wordLength = (int)strlen(entry->efld.c_str());
	 size_t wordLength{entry->efld.length()};

   /* If the word length is equal to zero, just leave. */
   if (!wordLength) {
      Beep();
      return TRUE;
   }

   /* Look for a unique word match. */
   int Index = searchList(&alphalist->plist, entry->efld.c_str());

   /* If the index is less than zero, return we didn't find a match. */
   if (Index < 0) {
      Beep();
      return TRUE;
   }

   /* Did we find the last word in the list? */
   if (Index == (int)alphalist-> plist.size() - 1) {
      entry->setCDKEntryValue(alphalist-> plist[Index]);
      entry->drawObj(entry->obbox);
      return TRUE;
   }

   /* Ok, we found a match, is the next item similar? */
   int ret = strncmp(alphalist->plist[Index + 1].c_str(), entry->efld.c_str(),(size_t) wordLength);
	 if (!ret) {
		 int currentIndex{Index};
		 while ((currentIndex<(int)alphalist->plist.size()) && (!strncmp(alphalist->plist[currentIndex].c_str(), entry->efld.c_str(),(size_t)wordLength))) {
			 altWords.push_back(alphalist->plist[currentIndex++]);
		 }

		 /* Determine the height of the scrolling list. */
		 int altCount=altWords.size();
		 int height = (altCount < 8 ? altCount + 3 : 11);

		 /* Create a scrolling list of close matches. */
		 scrollp = new SScroll(entry->/*obj.*/screen,
				 CENTER, CENTER, RIGHT, height, -30,
				 "<C></B/5>Possible Matches.",
				 &altWords,
				 NUMBERS, A_REVERSE, 0, TRUE, FALSE);

		 /* Allow them to select a close match. */
		 /*int match = */scrollp->activateCDKScroll(0);
		 int selected = scrollp->currentItem;

		 /* Check how they exited the list. */
		 if (scrollp->exitType == vESCAPE_HIT) {
			 /* Destroy the scrolling list. */
			// scrollp->destroyCDKScroll();
			 scrollp->destroyObj();
			 /* Clean up. */
			 /* Beep at the user. */
			 Beep();
			 /* Redraw the alphalist and return. */
			 alphalist->drawCDKAlphalist(alphalist->obbox);
			 return (TRUE);
		 }
		 /* Destroy the scrolling list. */
//		 destroyCDKScroll(scrollp);
		 scrollp->destroyObj();
		 /* Set the entry field to the selected value. */
		 entry->setCDKEntry(
				 alphalist->plist[Index+selected], // .c_str()
				 entry->minlen,
				 entry->maxlen,
				 alphalist->obbox);
		 /* Move the highlight bar down to the selected value. */
		 for (int x = 0; x < selected; x++) {
			 alphalist->injectMyScroller(KEY_DOWN);
		 }

		 /* Clean up. */

		 /* Redraw the alphalist. */
		 alphalist->drawCDKAlphalist(alphalist->obbox);
	 } else {
		 /* Set the entry field with the found item. */
		 entry->setCDKEntry(
				 alphalist->plist[Index], // .c_str()
				 entry->minlen,
				 entry->maxlen,
				 entry->obbox);
		 entry->drawObj(alphalist->obbox);
	 }
	 return (TRUE);
}

void SAlphalist::focusCDKAlphalist()
{
//   SAlphalist *widget = (SAlphalist *)object;
	/*
	FocusObj(entryField);
	MethodPtr(entryField,focusObj)(entryField);
	((ObjPtr(entryField))->focusObj)(entryField);
	(((GObj*)(entryField))->focusObj)(entryField);
	entryField->focusObj(entryField);
	*/
	entryField->focusCDKEntry();
}

void SAlphalist::unfocusCDKAlphalist()
{
//   SAlphalist *widget = (SAlphalist *)object;
//   UnfocusObj(ObjOf(entryField));
	entryField->unfocusCDKEntry();
}

void SFSelect::focusCDKFileSelector()
{
	entryField->focusCDKEntry();
}

void SFSelect::unfocusCDKFileSelector()
{
	entryField->unfocusCDKEntry();
}

/*
 * Set data for preprocessing.
 */
void GObj::setCDKObjectPreProcess(/*GObj *obj, */PROCESSFN fn, void *data)
{
   preProcessFunction = fn;
   preProcessData = data;
}

/*
 * Set data for postprocessing.
 */
/*
void GObj::setCDKObjectPostProcess(PROCESSFN fn, void *data)
{
   postProcessFunction = fn;
   postProcessData = data;
}
*/

/*
 * This is the heart-beat of the widget.
 */
static int preProcessEntryField(EObjectType cdktype GCC_UNUSED, void
				 *object GCC_UNUSED,
				 void *clientData,
				 chtype input)
{
	/* *INDENT-EQLS* */
	SAlphalist *alphalist = (SAlphalist *)clientData;
	SScroll *scrollp      = alphalist->scrollField;
	SEntry *entry         = alphalist->entryField;
	int result              = 1;
	bool empty              = FALSE;

	/* Make sure the entry field isn't empty. */
	if (0) {
		empty = TRUE;
	} else if (alphalist->isCDKObjectBind(input)) {
		result = 1;		/* don't try to use this key in editing */
	} else if ((isChar(input) &&
				(isalnum((unsigned char)input) || ispunct(input))) || input == KEY_BACKSPACE || input == KEY_DC) {
		int currPos {entry->screenCol + entry->leftChar};
		string pattern{entry->efld};
		if (input == KEY_BACKSPACE || input == KEY_DC) {
			if (input == KEY_BACKSPACE)
				--currPos;
			if (currPos >= 0)
				pattern.erase(currPos,1);
		} else {
			/*
				 if (currPos==pattern.length()-1) {
				 pattern.append(1,(char)input);
				 } else {
			 */
//mvwprintw(entry->screen->window,3,2,"preProcessEntryField,input: %c,crrPos: %i, pattern.length(): %i,screenCol: %i, leftChar: %i          ",input,currPos,pattern.length(),entry->screenCol, entry->leftChar);
			pattern.insert(pattern.begin()+currPos,(char)input);
		/*
			 }
		 */
			// wrefresh(entry->screen->window);
		}
		int Index;
		if (!strlen(pattern.c_str())) empty=TRUE;
		else if ((Index = searchList(
						&alphalist->plist,
						pattern.c_str()
						))>=0) {
			/* *INDENT-EQLS* */
			int difference{Index - scrollp->currentItem};
			int absoluteDifference{abs(difference)};

			/*
			 * If the difference is less than zero, then move up.
			 * Otherwise move down.
			 *
			 * If the difference is greater than 10 jump to the new
			 * index position.  Otherwise provide the nice scroll.
			 */
			if (absoluteDifference <= 10) {
				for (int x = 0; x < absoluteDifference; x++) {
					alphalist->injectMyScroller(
							(chtype)((difference <= 0)
								? KEY_UP
								: KEY_DOWN));
				}
			} else {
				scrollp->SetPosition(Index);
			}
			alphalist->drawMyScroller();
		} else {
			/* Kommentar G.Schade 17.11.18, erlaubt nicht in der Liste vertretene Eingaben
				 Beep();
				 result = 0;
			 */
		}
	}
	if (empty) {
		scrollp->SetPosition(0);
		alphalist->drawMyScroller();
	}
	return result;
} // static int preProcessEntryField(


/*
 * This creates the alphalist widget.
 */
SAlphalist::SAlphalist(SScreen *cdkscreen,
			       int xplace,
			       int yplace,
			       int height,
			       int width,
			       const char *title,
			       const char *label,
						 vector<string> *plistp,
						 size_t maxlen,
			       chtype pfillerChar,
			       chtype phighlight,
			       bool obBox,
						 bool pshadow,
						 // GSchade Anfang
						 int highnr/*=0*/,
						 int aktent/*=-1*/
						 // GSchade Ende
		): ComboB(cdkscreen,cdkscreen->window,obBox,pshadow,vALPHALIST,/*pAcceptsFocus*/1,/*phasFocus*/1,/*pisVisible*/1
			,/*xpos*/xplace,/*ypos*/yplace,height,width,/*highlight*/phighlight,/*fillerChar*/pfillerChar
			,/*objnr*/aktent),
	plist(*plistp)
{
//	cdktype = vALPHALIST;
//	shadow=pshadow;
	/* *INDENT-EQLS* */
//	SAlphalist *alphalist      = 0;
//	int parentWidth              = getmaxx(cdkscreen->window);
//	int parentHeight             = getmaxy(cdkscreen->window);
	int tempWidth                = 0;
	int tempHeight               = 0;
	int labelLen                 = 0;
	/* *INDENT-OFF* */
	static const struct { int from; int to; } bindings[] = {
		{ CDK_BACKCHAR,	KEY_PPAGE },
		{ CDK_FORCHAR,	KEY_NPAGE },
	};
	/* *INDENT-ON* */

//	::GObj();
//	objnr=aktent;
//	setBox(Box);
	/* Translate the label char *pointer to a chtype pointer. */
	if (label) {
		int junk2;
		//		chtype *chtypeLabel = char2Chtypeh(label, &labelLen, &junk2 /* GSchade Anfang */ ,highnr /* GSchade Ende */);
//		freeChtype(chtypeLabel);
		chtstr chtypeLabel(label,&labelLen,&junk2,highnr);
	}
	/* Rejustify the x and y positions if we need to. */
	alignxy(cdkscreen->window, &xpos, &ypos, boxWidth, boxHeight);
	/* Make the file selector window. */
	this->win = newwin(boxHeight, boxWidth, ypos, xpos);
	if (!this->win) {
		destroyCDKObject();
		return;
	}
	keypad(this->win, TRUE);
	/* *INDENT-EQLS* Set some variables. */
//	ScreenOf(this)         = cdkscreen;
//	screen									= cdkscreen;
//	this->parent            = cdkscreen->window;
//	this->highlight         = highlight;
//	this->fillerChar        = fillerChar;
//	this->boxHeight         = boxHeight;
//	this->boxWidth          = boxWidth;
//	initExitType(this);
//	exitType=vNEVER_ACTIVATED;
//	this->shadow            = shadow;
	this->shadowWin         = 0;
	/* Do we want a shadow? */
	if (shadow) {
		this->shadowWin = newwin(boxHeight, boxWidth, ypos + 1, xpos + 1);
	}

	/* Create the entry field. */
	tempWidth = (isFullWidth(width) ? FULL : boxWidth - 2 - labelLen);
	this->entryField = new SEntry(cdkscreen,
			getbegx(this->win),
			getbegy(this->win),
			title, label,
			A_NORMAL, fillerChar,
			vMIXED, tempWidth, 0, maxlen,
			obBox, FALSE
			// GSchade Anfang
			,this
			,highnr
			// GSchade Ende
			);
	if (!this->entryField) {
//		destroyCDKObject(this);
		return;
	}
	//setCDKEntryLLChar(this->entryField, ACS_LTEE);
   LLChar=ACS_LTEE;		/* lines: lower-left */
	//setCDKEntryLRChar(this->entryField, ACS_RTEE);
   LRChar=ACS_RTEE;		/* lines: lower-right */

	/* Set the key bindings for the entry field. */
	entryField->bindCDKObject(
			KEY_UP,
			adjustAlphalistCB,
			this);
	entryField->bindCDKObject(
			KEY_DOWN,
			adjustAlphalistCB,
			this);
	entryField->bindCDKObject(
			KEY_NPAGE,
			adjustAlphalistCB,
			this);
	entryField->bindCDKObject(
			KEY_PPAGE,
			adjustAlphalistCB,
			this);
	entryField->bindCDKObject(
//			KEY_TAB,
			KEY_F3,
			completeWordCB,
			this);

	/* Set up the post-process function for the entry field. */
	entryField->setCDKObjectPreProcess(preProcessEntryField, this);

	/*
	 * Create the scrolling list.  It overlaps the entry field by one line if
	 * we are using box-borders.
	 */
	tempHeight = getmaxy(this->entryField->win) - borderSize;
	tempWidth =(isFullWidth(width) ? FULL : boxWidth - 1);
	this->scrollField = new SScroll(cdkscreen,
			getbegx(this->win),
			getbegy(this->entryField->win) + tempHeight,
			RIGHT,
			boxHeight - tempHeight,
			tempWidth, 0, 
			plistp,
			NONUMBERS, A_REVERSE,
			/*pmutter*/this,
			obBox, FALSE);
//	setCDKScrollULChar(this->scrollField, ACS_LTEE);
   ULChar=ACS_LTEE;
//	setCDKScrollURChar(this->scrollField, ACS_RTEE);
   URChar=ACS_LTEE;	

	/* Setup the key bindings. */
	for (int x = 0; x <(int)elemzahl(bindings); ++x)
		bindCDKObject(
				(chtype)bindings[x].from,
				getcCDKBind,
				(void *)(long)bindings[x].to);
	registerCDKObject(cdkscreen, vALPHALIST);
//	return (this);
}

/*
 * The fselect's focus resides in the entry widget.  But the scroll widget
 * will not draw items highlighted unless it has focus.  Temporarily adjust the
 * focus of the scroll widget when drawing on it to get the right highlighting.
 */

void ComboB::drawMyScroller(/*SFSelect *widget*/)
{
   SaveFocus(this);
	// mit 1 entstehen hier Fehler nicht unten, nur oben
   scrollField->drawCDKScroll(/*widget->scrollField, ObjOf(widget->scrollField)->*/scrollField->obbox);
   RestoreFocus(this);
}

/*
 * This draws the file selector widget.
 */
void SAlphalist::drawCDKAlphalist(bool Box GCC_UNUSED, bool obmitscroller/*=0*/)
{
//   SAlphalist *alphalist =(SAlphalist *)obj;
   /* Does this widget have a shadow? */
   if (shadowWin) {
      drawShadow(shadowWin);
   }
   /* Draw in the entry field. */
   entryField->drawObj(entryField->obbox);
   /* Draw in the scroll field. */
	 // Kommentar GSchade 11.11.18: bewirkt, dass der Scroller erst gezeichnet wird, wenn in ihm ein Tastendruck erfolgt, z.B. Pfeil nach unten
	 if (obmitscroller)
		 this->drawMyScroller();
}


void SScroll_basis::scroll_KEY_UP()
{
	if (listSize <= 0 || currentItem <= 0) {
		Beep();
		return;
   }
   currentItem--;
   if (currentHigh) {
      currentHigh--;
   }
   if (currentTop && currentItem < currentTop) {
      currentTop--;
   }
}

void SScroll_basis::scroll_KEY_DOWN()
{
   if (listSize <= 0 || currentItem >= lastItem) {
      Beep();
      return;
   }
   currentItem++;
   if(currentHigh < viewSize - 1) {
      currentHigh++;
   }
   if(currentTop < maxTopItem && currentItem >(currentTop + viewSize - 1)) {
      currentTop++;
   }
}

void SScroll_basis::scroll_KEY_LEFT()
{
   if (listSize <= 0 || leftChar <= 0) {
      Beep();
      return;
   }
   leftChar--;
}

void SScroll_basis::scroll_KEY_RIGHT()
{
   if (listSize <= 0 || leftChar >= maxLeftChar) {
      Beep();
      return;
   }
   leftChar++;
}

void SScroll_basis::scroll_KEY_PPAGE()
{
   int vS = viewSize - 1;
   if (listSize <= 0 || currentTop <= 0) {
      Beep();
      return;
   }
   if (currentTop < vS) {
      scroll_KEY_HOME();
   } else {
      currentTop -= vS;
      currentItem -= vS;
   }
}

void SScroll_basis::scroll_KEY_NPAGE()
{
   int vS = viewSize - 1;
   if (listSize <= 0 || currentTop >= maxTopItem) {
      Beep();
      return;
   }
   if ((currentTop + vS) <= maxTopItem) {
      currentTop += vS;
      currentItem += vS;
   } else {
      scroll_KEY_END();
   }
}

void SScroll_basis::scroll_KEY_HOME()
{
   currentTop = 0;
   currentItem = 0;
   currentHigh = 0;
}

void SScroll_basis::scroll_KEY_END()
{
   currentTop = maxTopItem;
   currentItem = lastItem;
   currentHigh = viewSize - 1;
}

void SScroll_basis::scroll_FixCursorPosition()
{
   int scrollbarAdj =(scrollbarPlacement == LEFT) ? 1 : 0;
   int ypos = currentItem-currentTop+borderSize+titleLines; // SCREEN_YPOS(this,currentItem - currentTop);
   int xpos = borderSize+scrollbarAdj; // SCREEN_XPOS(this,0) + scrollbarAdj;
   wmove(inputWindow, ypos, xpos);
   wrefresh(inputWindow);
}

void SScroll_basis::SetPosition(int item)
{
   /* item out of band */
   if (item <= 0) {
      scroll_KEY_HOME();
      return;
   }
   /* item out of band */
   if (item >= lastItem) {
      scroll_KEY_END();
      return;
   }
   /* item in first view port */
   if (item < viewSize) {
      currentTop = 0;
   } /* item in last view port */ else if (item >= lastItem - viewSize) {
      currentTop = maxTopItem;
   } /* item not in visible view port */ else if (item < currentTop || item >= currentTop + viewSize) {
      currentTop = item;
   }
   currentItem = item;
   currentHigh = currentItem - currentTop;
}

int SScroll_basis::MaxViewSize()
{
   return(boxHeight -(2 * borderSize + titleLines));
}

void SScroll_basis::setViewSize(int size)
{
   int max_view_size = MaxViewSize();
   viewSize = max_view_size;
   lastItem = size - 1;
   maxTopItem = size - viewSize;
   if (size < viewSize) {
      viewSize = size;
      maxTopItem = 0;
   }
   if (listSize > 0 && max_view_size > 0) {
      step = (float)(max_view_size /(double)listSize);
      toggleSize =((listSize > max_view_size) ? 1 : ceilCDK(step));
   } else {
      step = 1;
      toggleSize = 1;
   }
}

/*
 * This function creates a new scrolling list widget.
 */
SScroll::SScroll(SScreen *cdkscreen,
			 int xplace,
			 int yplace,
			 int splace,
			 int height,
			 int width,
			 const char *title,
			 vector<string> *plistp,
			 bool numbers,
			 chtype phighlight,
			 GObj *pmutter,
			 bool obBox,
			 bool pshadow)
		: SScroll_basis(cdkscreen,cdkscreen->window,obBox,pshadow,vSCROLL,/*pAcceptsFocus*/1,/*phasFocus*/1,/*pisVisible*/1)
{
	mutter=pmutter?pmutter:this;
	size_t listSize{plistp->size()};
//	cdktype=vSCROLL;
   /* *INDENT-EQLS* */
   //SScroll *scrollp           = 0;
//   int parentWidth              = getmaxx(cdkscreen->window);
//   int parentHeight             = getmaxy(cdkscreen->window);
   int xpos                     = xplace;
   int ypos                     = yplace;
   int scrollAdjust             = 0;
   int x;
   /* *INDENT-OFF* */
   static const struct { int from; int to; } bindings[] = {
		{ CDK_BACKCHAR,	KEY_PPAGE },
		{ CDK_FORCHAR,	KEY_NPAGE },
		{ 'g',		KEY_HOME },
		{ '1',		KEY_HOME },
		{ 'G',		KEY_END },
		{ '<',		KEY_HOME },
		{ '>',		KEY_END },
   };
   /* *INDENT-ON* */

//   if ((scrollp = newCDKObject(SScroll, &my_funcs)) == 0) { destroyCDKObject(scrollp); return(0); }
//	::GObj();
//   setBox(Box);

   /*
    * If the height is a negative value, the height will
    * be ROWS-height, otherwise, the height will be the
    * given height.
    */
   boxHeight = setWidgetDimension(parentHeight, height, 0);

   /*
    * If the width is a negative value, the width will
    * be COLS-width, otherwise, the width will be the
    * given width.
    */
   boxWidth = setWidgetDimension(parentWidth, width, 0);

   boxWidth = setCdkTitle(title, boxWidth);

   /* Set the box height. */
   if (titleLines > boxHeight) {
      boxHeight =(titleLines + MINIMUM(listSize , 8) + 2 * borderSize);
   }

   /* Adjust the box width if there is a scrollp bar. */
   if ((splace == LEFT) ||(splace == RIGHT)) {
      scrollbar = TRUE;
      boxWidth += 1;
   } else {
      scrollbar = FALSE;
   }

   /*
    * Make sure we didn't extend beyond the dimensions of the window.
    */
   boxWidth =(boxWidth > parentWidth ?(parentWidth - scrollAdjust) : boxWidth);
   boxHeight =(boxHeight > parentHeight ? parentHeight : boxHeight);

   setViewSize(listSize);

   /* Rejustify the x and y positions if we need to. */
   alignxy(cdkscreen->window, &xpos, &ypos, boxWidth, boxHeight);

   /* Make the scrolling window */
   win = newwin(boxHeight, boxWidth, ypos, xpos);

   /* Is the scrolling window null?? */
   if (!win) {
      destroyCDKObject();
			return;
   }

   /* Turn the keypad on for the window. */
   keypad(win, TRUE);

   /* Create the scrollbar window. */
   if (splace == RIGHT) {
      scrollbarWin = subwin(win,
				      MaxViewSize(), 1,
				      ypos+borderSize+titleLines, // SCREEN_YPOS(this, ypos),
				      xpos + boxWidth
				      - borderSize - 1);
   } else if (splace == LEFT) {
      scrollbarWin = subwin(win,
				      MaxViewSize(), 1,
				      ypos+borderSize+titleLines,// SCREEN_YPOS(this, ypos),
				      xpos+borderSize); // SCREEN_XPOS(this, xpos));
   } else {
      scrollbarWin = 0;
   }

   /* create the list window */

   listWin = subwin(win,
			      MaxViewSize(),
			      boxWidth
			      - 2 * borderSize - scrollAdjust,
			      ypos+borderSize+titleLines, // SCREEN_YPOS(this, ypos),
			      xpos+borderSize // SCREEN_XPOS(this, xpos)
			      +(splace == LEFT ? 1 : 0));

   /* *INDENT-EQLS* Set the rest of the variables */
   //ScreenOf(this)           = cdkscreen;
//	 screen							 = cdkscreen;
//   parent              = cdkscreen->window;
   shadowWin           = 0;
   scrollbarPlacement  = splace;
   maxLeftChar         = 0;
   leftChar            = 0;
//   initExitType(this);
//	 exitType=vNEVER_ACTIVATED;
//   ObjOf(this)->acceptsFocus = TRUE;
   /*ObjOf(this)->*/inputWindow = win;
//   shadow              = pshadow;
	 highlight						 = phighlight;
   SetPosition(0);
   /* Create the scrolling list item list and needed variables. */
   if (createCDKScrollItemList(numbers,plistp) <= 0) {
      destroyCDKObject();
      return;
   }
   /* Do we need to create a shadow? */
   if (shadow) {
      shadowWin = newwin(boxHeight,
				   boxWidth,
				   ypos + 1,
				   xpos + 1);
   }
   /* Setup the key bindings. */
   for (x = 0; x <(int)elemzahl(bindings); ++x)
      bindCDKObject(/*vSCROLL,
		     this,*/
		    (chtype)bindings[x].from,
		     getcCDKBind,
		    (void *)(long)bindings[x].to);
   // registerCDKObject(cdkscreen, vSCROLL); // 3.1.19: wird sonst bei refreshCDKScreen zu oft gezeichnet 
   /* Return the scrolling list */
//   return this;
}

/*
 * This actually does all the 'real' work of managing the scrolling list.
 */
int SScroll::activateCDKScroll(chtype *actions)
{
	/* Draw the scrolling list */
	// hier entstehen keine Fehler
	int ret;
	this->drawCDKScroll(obbox,1);
	if (!actions) {
		chtype input;
		bool functionKey;
		for (;;) {
			scroll_FixCursorPosition();
			input = (chtype)this->getchCDKObject(&functionKey);
			/* Inject the character into the widget. */
			ret = this->injectSScroll(input);
			if (this->exitType != vEARLY_EXIT) {
				return ret;
			}
		}
	} else {
		int length = chlen(actions);
		/* Inject each character one at a time. */
		for (int i = 0; i < length; i++) {
			ret = injectSScroll(actions[i]);
			if (this->exitType != vEARLY_EXIT)
				return ret;
		}
	}
	/* Set the exit type for the widget and return. */
	setExitType(0);
	return -1;
}

const int einrueck{1};
void SScroll::drawCDKScrollCurrent()
{
   /* Rehighlight the current menu item. */
   const int screenPos{itemPos[this->currentItem] - this->leftChar};
   const chtype hilight = /*HasFocusObj(this)*/hasFocus ? this->highlight : 
		 // Anfang G.Schade 2.10.18
		 this->highlight
		 /*A_NORMAL*/
		 // Ende G.Schade 2.10.18
		 ;
   writeChtypeAttrib(this->listWin,
		      ((screenPos >= 0) ? screenPos : 0)+einrueck,
		      this->currentHigh,
					this->pitem[this->currentItem].getinh(),
		      hilight,
		      HORIZONTAL,
		      (screenPos >= 0) ? 0 :(1 - screenPos),
		      this->itemLen[this->currentItem]);
}

// #undef  SCREEN_YPOS		/* because listWin is separate */
// #define SCREEN_YPOS(w,n)(n)

/*
 * This redraws the scrolling list.
 */
void SScroll::drawCDKScrollList(bool Box)
{
	static int reihe{0};
//	int anzy{0};
	/* If the list is empty, don't draw anything. */
	if (this->listSize > 0) {
		/* Redraw the list */
		reihe++;
		if (reihe>=22 && reihe<42) {
			reihe=reihe;
		}
		for (int j = 0; j < this->viewSize; j++) {
			int xpos = 0; // SCREEN_YPOS(this, 0);
			int ypos = j; // SCREEN_YPOS(this, j);
			writeBlanks(this->listWin, xpos, ypos, HORIZONTAL, 0, this->boxWidth - 2 * borderSize);
			int k = j + this->currentTop;
			/* Draw the elements in the scroll list. */
			if (k < this->listSize) {
				const int screenPos{itemPos[k]-leftChar}; //  SCREENPOS(this, k);
				/* Write in the correct line. */
				// zeichnet alle, ohne das Aktuelle zu markieren
//				mvwprintw(parent,anzy++,90,"%i: cury: %i %s",reihe,listWin->_cury,pitem[k].chtype2Char());
				writeChtype(this->listWin,
						((screenPos >= 0) ? screenPos : 1)+einrueck,
						ypos, 
						this->pitem[k].getinh(),
						HORIZONTAL,
						(screenPos >= 0) ? 0 :(1 - screenPos),
						this->itemLen[k]);
			}
		}
		// zeichnet nur das Markierte
		this->drawCDKScrollCurrent(); wrefresh(this->win);
		/* Determine where the toggle is supposed to be. */
		if (this->scrollbarWin) {
			this->togglePos = floorCDK(this->currentItem *(double)this->step);
			/* Make sure the toggle button doesn't go out of bounds. */
			if (this->togglePos >= getmaxy(this->scrollbarWin))
				this->togglePos = getmaxy(this->scrollbarWin) - 1;
			/* Draw the scrollbar. */
			(void)mvwvline(this->scrollbarWin,
					0, 0,
					ACS_CKBOARD,
					getmaxy(this->scrollbarWin));
			(void)mvwvline(this->scrollbarWin,
					this->togglePos, 0,
					' ' | A_REVERSE,
					this->toggleSize);
		}
	}
	/* Box it if needed. */
	if(Box) {
		drawObjBox(win);
	} else {
		touchwin(this->win);
	}
	wrefresh(this->win);
} // static void drawCDKScrollList


/*
 * This injects a single character into the widget.
 */
int SScroll::injectSScroll(/*GObj *object, */chtype input)
{
	//   SScroll *myself =(SScroll *)object;
//	CDKSCROLLER *widget =(CDKSCROLLER *)this;
	int ppReturn = 1;
	int ret = -1; // unknownInt;
	bool complete = FALSE;

	/* Set the exit type for the widget. */
	setExitType(0);

	/* Draw the scrolling list */
	drawCDKScrollList(obbox);

	/* Check if there is a pre-process function to be called. */
	if ((preProcessFunction)) {
		/* Call the pre-process function. */
		ppReturn = (preProcessFunction)(vSCROLL,
				this,
				(preProcessData),
				input);
	}

	/* Should we continue? */
	if (ppReturn) {
		/* Check for a predefined key binding. */
		if (checkCDKObjectBind(input)) {
			// checkEarlyExit(this);
			if (earlyExit != vNEVER_ACTIVATED) exitType = earlyExit;
			complete = TRUE;
		} else {
			switch (input) {
				case KEY_UP:
					scroll_KEY_UP();
					break;

				case KEY_DOWN:
					scroll_KEY_DOWN();
					break;

				case KEY_RIGHT:
					scroll_KEY_RIGHT();
					break;

				case KEY_LEFT:
					scroll_KEY_LEFT();
					break;

				case KEY_PPAGE:
					scroll_KEY_PPAGE();
					break;

				case KEY_NPAGE:
					scroll_KEY_NPAGE();
					break;

				case KEY_HOME:
					scroll_KEY_HOME();
					break;

				case KEY_END:
					scroll_KEY_END();
					break;

				case '$':
					/*widget->*/leftChar = /*widget->*/maxLeftChar;
					break;

				case '|':
					/*widget->*/leftChar = 0;
					break;

				case KEY_ESC:
					setExitType(input);
					complete = TRUE;
					break;

				case KEY_ERROR:
					setExitType(input);
					complete = TRUE;
					break;

				case CDK_REFRESH:
					screen->eraseCDKScreen();
					screen->refreshCDKScreen();
					break;

				case KEY_TAB:
				case KEY_ENTER:
					setExitType(input);
					ret = /*widget->*/currentItem;
					complete = TRUE;
					break;

				default:
					break;
			}
		}
		/* Should we call a post-process? */
		if (!complete && (postProcessFunction)) {
			(postProcessFunction)(vSCROLL,
					this/*widget*/,
					(postProcessData),
					input);
		}
	}
	if (!complete) {
		drawCDKScrollList(obbox);
		setExitType(0);
	}
	scroll_FixCursorPosition();
	resultData.valueInt = ret;
	return (ret != -1); // unknownInt);
} // static int _injectSScroll

/*
 * This sets the background attribute of the widget.
 */
void GObj::setBKattrObj(/*GObj *object, */chtype attrib)
{
//   if (object) {
//      SLabel *widget =(SLabel *)object;
      wbkgd(this->win, attrib);
//   }
}

/*
 * This function creates the scrolling list information and sets up the needed
 * variables for the scrolling list to work correctly.
 */
int SScroll::createCDKScrollItemList(bool nummern, vector<string> *plistp)
{
	int status{0};
	pitem.clear();
	itemPos.clear();
	itemLen.clear();
	listSize=0;
	if (plistp->size() > 0) {
		/* *INDENT-EQLS* */
		int widestItem = 0;
		/* Create the items in the scrolling list. */
		status = 1;
		for (size_t x = 0; x < plistp->size() ; x++) {
			if (!allocListItem(x, nummern ?(x + 1) : 0, plistp->at(x).c_str())) {
				status = 0;
				break;
			}
			status=1;
			widestItem = MAXIMUM(this->itemLen[x], widestItem);
		}
		if (status) {
			updateViewWidth(widestItem);
			/* Keep the boolean flag 'numbers' */
			this->numbers = nummern;
		}
	} else {
		status = 1;		/* null list is ok - for a while */
	}
	return status;
}

void SScroll_basis::updateViewWidth(int widest)
{
/* Determine how many characters we can shift to the right */
/* before all the items have been scrolled off the screen. */
	maxLeftChar=boxWidth>widest?0:widest-(boxWidth-2*borderSize);
}

bool SScroll::allocListItem(int which, int number, const char *value)
{
	string valuestr;
	if (number > 0) {
		size_t need = strlen(value)+8; // NUMBER_LEN(value);
		valuestr.resize(need);
		sprintf(&valuestr[0],NUMBER_FMT,number,value);
		valuestr.resize(strlen(valuestr.c_str())+1);
		value=valuestr.c_str();
	}
//	if (!(this->sitem[which] = char2Chtypeh(value, &(this->itemLen[which]), &(this->itemPos[which])))) return FALSE;
	int len,pos;
	chtstr sitemneu(value,&len,&pos);
  pos=justifyString(boxWidth,len,pos);
	pitem.insert(pitem.begin()+which,sitemneu);
	listSize++;
	itemLen.insert(itemLen.begin()+which,len);
	itemPos.insert(itemPos.begin()+which,pos);
	return TRUE;
}

int chtstr::rauskopier(chtype **ziel)
{
	if ((*ziel=new chtype[len])) {
    memcpy(ziel,&inh,len);	
		return TRUE;
	}
	return FALSE;
}

/*
 * Destroy all of the objects on a screen
 */

void SScreen::destroyCDKScreenObjects()
{
	for (int x = 0; x < this->objectCount; x++) {
		GObj *obj = this->object[x];
		if (obj) {
			int before = this->objectCount;
			//		if (validObjType(obj, ObjTypeOf(obj))) KLA
			//			MethodPtr(obj, eraseObj)(obj);
			obj->eraseObj();
			obj->destroyCDKObject();
			x -= (this->objectCount - before);
			//		KLZ
		}
	}
}

/*
 * This destroys a CDK screen.
 */
void SScreen::destroyCDKScreen()
{
	size_t pos{0};
	for(auto akt:all_screens) {
		if (akt==this) {
			all_screens.erase(all_screens.begin()+pos);
			break;
//			akt->destroyObj();
			free(akt);
		}
		pos++;
	}
	/*
	ALL_SCREENS *p, *q;
	for (p = all_screens, q = 0; p; q = p, p = p->link) {
		if (screen == p->screen) {
			if (q)
				q->link = p->link;
			else
				all_screens = p->link;
			free(p);
			free(screen);
			break;
		}
	}
	*/
}

/*
 * This clears all the objects in the screen.
 */
void SScreen::eraseCDKScreen()
{
//	int objectCount = this->objectCount;
	/* We just call the drawObject function. */
	for (int x = 0; x < objectCount; x++) {
		GObj *obj = this->object[x];
		if (obj) {
			//		if (validObjType(obj, ObjTypeOf(obj))) KLA
			if (obj->validObjType(obj->cdktype)) {
				obj->eraseObj();
			}
		}
	}
	/* Refresh the screen. */
	wrefresh (this->window);
}

void GObj::eraseObj()
{
}

#define limitFocusIndex(screen, value) \
 	(((value) >=(screen)->objectCount ||(value) < 0) \
	 ? 0 \
	 :(value))

int SScreen::getFocusIndex()
{
   int result = limitFocusIndex(this, objectFocus);
   return result;
}


void SScreen::setFocusIndex(int value)
{
   objectFocus = limitFocusIndex(this, value);
}


/*
 * This creates a new CDK screen.
 */
//SScreen *initCDKScreen(WINDOW *window)
SScreen::SScreen(WINDOW *window)
{
	//	ALL_SCREENS *item;
	//	SScreen *screen = 0;
	/* initialization, for the first time */
	if (/*all_screens == 0 || */!stdscr || !window) {
		/* Set up basic curses settings. */
#ifdef HAVE_SETLOCALE
		setlocale(LC_ALL, "");
#endif
		/* Initialize curses after setting the locale, since curses depends
		 * on having a correct locale to reflect the terminal's encoding.
		 */
		if (!stdscr || !window) {
			window = initscr();
		}
		noecho();
		cbreak();
	}

	//	if ((item = typeMalloc(ALL_SCREENS))) {
	//		if ((screen = typeCalloc(SScreen))) {
	/*
		 item->link = all_screens;
		 item->screen = this;
		 all_screens = item;
	 */
	all_screens.push_back(this);

	/* Initialize the SScreen pointer. */
	this->objectCount = 0;
	this->window = window;

	/* OK, we are done. */
	//		} else { free(item); }
	//	}
	//	return(screen);
}

/*
 * This creates a label widget.
 */
//SLabel *newCDKLabel(SScreen *cdkscreen,
SLabel::SLabel(SScreen *cdkscreen,
		       int xplace,
		       int yplace,
					 vector<string> mesg,
		       bool obBox,
		       bool pshadow
		): GObj(cdkscreen,cdkscreen->window,obBox,pshadow,vLABEL,/*pAcceptsFocus*/0,/*phasFocus*/0,/*pisVisible*/1)
	,xpos(xplace),ypos(yplace), rows(mesg.size()),boxWidth(INT_MIN),boxHeight(rows+2*borderSize)
{
//	shadow=pshadow;
   /* *INDENT-EQLS* */
//   SLabel *label      = 0;
//   int parentWidth      = getmaxx(cdkscreen->window);
//   int parentHeight     = getmaxy(cdkscreen->window);
//   int boxWidth         = INT_MIN;
//   int boxHeight;
   //int xpos             = xplace;
   //int ypos             = yplace;

//	::GObj();
   if (rows <= 0) {
      destroyCDKObject(/*label*/);
      return /*(0)*/;
   }
//   setBox(/*label, */Box);
//   boxHeight = rows + 2 * /*BorderOf(label)*/ borderSize;

   /* Determine the box width. */
   for (size_t x = 0; x < mesg.size() ; x++) {
      /* Translate the char * to a chtype. */
//      /*label->*/info[x] = char2Chtypeh(mesg[x], &/*label->*/infoLen[x], &/*label->*/infoPos[x]);
		 int len,pos;
		 chtstr infoneu(mesg[x].c_str(),&len,&pos);
		 //	pos=justifyString(boxWidth,len,pos);
		 pinfo.insert(pinfo.begin()+x,infoneu);
		 // listSize++
		 infoLen.insert(infoLen.begin()+x,len);
		 infoPos.insert(infoPos.begin()+x,pos);
		 boxWidth = MAXIMUM(boxWidth, /*label->*/infoLen[x]);
	 }
   boxWidth += 2 * /*BorderOf(label)*/ borderSize;

   /* Create the string alignments. */
   for (int x = 0; x < rows; x++) {
      /*label->*/infoPos[x] = justifyString(boxWidth - 2 * /*BorderOf(label)*/ borderSize,
					 /*label->*/infoLen[x],
					 /*label->*/infoPos[x]);
   }

   /*
    * Make sure we didn't extend beyond the dimensions of the window.
    */
   boxWidth =(boxWidth > parentWidth ? parentWidth : boxWidth);
   boxHeight =(boxHeight > parentHeight ? parentHeight : boxHeight);

   /* Rejustify the x and y positions if we need to. */
   alignxy(cdkscreen->window, &xpos, &ypos, boxWidth, boxHeight);

   /* *INDENT-EQLS* Create the label. */
//   /*ScreenOf(label)*/screen     = cdkscreen;
//   /*label->*/parent        = cdkscreen->window;
   /*label->*/win           = newwin(boxHeight, boxWidth, ypos, xpos);
   /*label->*/shadowWin     = 0;
//   /*label->*/xpos          = xpos;
//   /*label->*/ypos          = ypos;
//   /*label->*/rows          = rows;
//   /*label->*/boxWidth      = boxWidth;
//   /*label->*/boxHeight     = boxHeight;
   /*ObjOf(label)->*/inputWindow = /*label->*/win;
//   /*ObjOf(label)->*/hasFocus = FALSE;
//   label->shadow        = shadow;

   /* Is the window null? */
   if (/*label->*/!win)
   {
      destroyCDKObject(/*label*/);
      return /*(0)*/;
   }
   keypad(/*label->*/win, TRUE);

   /* If a shadow was requested, then create the shadow window. */
   if (shadow)
   {
      /*label->*/shadowWin = newwin(boxHeight, boxWidth, ypos + 1, xpos + 1);
   }

   /* Register this baby. */
   registerCDKObject(cdkscreen, vLABEL/*, label*/);

   /* Return the label pointer. */
//   return (label);
}

/*
bool SLabel::getCDKLabelBox()
{
   return obbox;
}
*/

/*
 * This was added for the builder.
 */
void SLabel::activateCDKLabel(/*SLabel *label, */chtype *actions GCC_UNUSED)
{
   drawCDKLabel(/*label, ObjOf(label)->*/obbox);
}

/*
 * This sets multiple attributes of the widget.
 */
// fand ich nur in: clock, serial, topsign, menu_ex 
/*
void SLabel::setCDKLabel(//SLabel *label,
			 std::vector<std::string> mesg
		, bool Box)
{
   setCDKLabelMessage(mesg);
   setBox(Box);
}
*/

/*
 * This sets the information within the label.
 */
void SLabel::setCDKLabelMessage(/*SLabel *label, */ std::vector<std::string> s_info)
{
   /* Clean out the old message. */
	 pinfo.clear();
	 infoPos.clear();
	 infoLen.clear();

   /* update the label's length - but taking into account its window size */
   int limit{/*label->*/boxHeight -(2 * /*BorderOf(label)*/ borderSize)};
	 rows=s_info.size();
	 if (rows>limit) rows=limit;

   /* Copy in the new message. */
   for (int x = 0; x < /*label->*/rows; x++) {
//      /*label->*/info[x] = char2Chtypeh(s_info[x], &/*label->*/infoLen[x], &/*label->*/infoPos[x]);
		 int len,pos;
		 chtstr infoneu(s_info[x].c_str(),&len,&pos);
		 pos=justifyString(boxWidth-2*borderSize,len,pos);
		 pinfo.insert(pinfo.begin()+x,infoneu);
		 // listSize++
		 infoLen.insert(infoLen.begin()+x,len);
		 infoPos.insert(infoPos.begin()+x,pos);
   }

   /* Redraw the label widget. */
   eraseCDKLabel(/*label*/);
   drawCDKLabel(/*label, ObjOf(label)->*/obbox);
}


/*
 * This sets the background attribute of the widget.
 */
void SLabel::setBKattrLabel(/*GObj *object, */chtype attrib)
{
//   if (object) {
//      SLabel *widget =(SLabel *)object;
      wbkgd(/*widget->*/win, attrib);
//   }
}

/*
 * This draws the label widget.
 */
void SLabel::drawCDKLabel(/*GObj *object, */bool Box GCC_UNUSED)
{
//   SLabel *label =(SLabel *)object;
   /* Is there a shadow? */
   if (/*label->*/shadowWin) {
      drawShadow(/*label->*/shadowWin);
   }
   /* Box the widget if asked. */
   if (/*ObjOf(label)->*/obbox) {
      drawObjBox(/*label->*/win/*, ObjOf(label)*/);
   }
   /* Draw in the message. */
   for (int x = 0; x < /*label->*/rows; x++) {
      writeChtype(/*label->*/win,
		   /*label->*/infoPos[x] + /*BorderOf(label)*/ borderSize,
		   x + /*BorderOf(label)*/ borderSize,
						this->pinfo[x].getinh(),
		   HORIZONTAL,
		   0,
		   /*label->*/infoLen[x]);
   }
   /* Refresh the window. */
   wrefresh(/*label->*/win);
} // SLabel::drawCDKLabel

/*
 * This erases the label widget.
 */
void SLabel::eraseCDKLabel(/*GObj *object*/)
{
//   if (validCDKObject(object)) {
//      SLabel *label =(SLabel *)object;
      eraseCursesWindow(/*label->*/win);
      eraseCursesWindow(/*label->*/shadowWin);
//   }
}

/*
 * This moves the label field to the given location.
 */
void SLabel::moveCDKLabel(/*GObj *object,*/
			   int xplace,
			   int yplace,
			   bool relative,
			   bool refresh_flag)
{
//   SLabel *label =(SLabel *)object;
   /* *INDENT-EQLS* */
   int currentX = getbegx(/*label->*/win);
   int currentY = getbegy(/*label->*/win);
   int xpos     = xplace;
   int ypos     = yplace;
   int xdiff    = 0;
   int ydiff    = 0;

   /*
    * If this is a relative move, then we will adjust where we want
    * to move to.
    */
   if (relative) {
      xpos = getbegx(/*label->*/win) + xplace;
      ypos = getbegy(/*label->*/win) + yplace;
   }

   /* Adjust the window if we need to. */
   alignxy(screen->window, &xpos, &ypos, /*label->*/boxWidth, /*label->*/boxHeight);

   /* Get the difference. */
   xdiff = currentX - xpos;
   ydiff = currentY - ypos;

   /* Move the window to the new location. */
   moveCursesWindow(/*label->*/win, -xdiff, -ydiff);
   moveCursesWindow(/*label->*/shadowWin, -xdiff, -ydiff);

   /* Touch the windows so they 'move'. */
   refreshCDKWindow(screen->window);

   /* Redraw the window, if they asked for it. */
   if (refresh_flag) {
      drawCDKLabel(/*label, ObjOf(label)->*/obbox);
   }
}

/*
 * This destroys the label object pointer.
 */
void SLabel::destroyCDKLabel(/*GObj *object*/)
{
//   if (object) {
//      SLabel *label =(SLabel *)object;


      /* Free up the window pointers. */
      deleteCursesWindow(/*label->*/shadowWin);
      deleteCursesWindow(/*label->*/win);

      /* Clean the key bindings. */
      cleanCDKObjectBindings(/*vLABEL, this*/);

      /* Unregister the object. */
      unregisterCDKObject(vLABEL/*, this*/);
//   }
}

/*
 * This pauses until a user hits a key...
 */
char SLabel::waitCDKLabel(/*SLabel *label, */char key)
{
	int code;
	bool functionKey;
	/* If the key is null, we'll accept anything. */
	if (!key) {
		code = getchCDKObject(/*ObjOf(label), */&functionKey);
	} else {
		/* Only exit when a specific key is hit. */
		for (;;) {
			code = getchCDKObject(/*ObjOf(label), */&functionKey);
			if (code == key) {
				break;
			}
		}
	}
	return (char)(code);
}

/*
 * This pops up a message.
 */
void SScreen::popupLabel(/*SScreen *screen, */
			 std::vector<std::string> mesg
		)
{
//   SLabel *popup = 0;
   int oldCursState;
   bool functionKey;
   /* Create the label. */
   SLabel popup(this,CENTER, CENTER, mesg, 
			 TRUE, FALSE);
   oldCursState = curs_set(0);
   /* Draw it on the screen. */
   popup.drawCDKLabel(/*popup, */TRUE);
   /* Wait for some input. */
   keypad(popup.win, TRUE);
   popup.getchCDKObject(/*ObjOf(popup), */&functionKey);
   /* Kill it. */
   popup.destroyCDKLabel();
   /* Clean the screen. */
   curs_set(oldCursState);
   eraseCDKScreen();
   refreshCDKScreen();
}

/*
 * This pops up a message.
 */
void SScreen::popupLabelAttrib(/*SScreen *screen, */
			 std::vector<std::string> mesg
		, chtype attrib)
{
//   SLabel *popup = 0;
   int oldCursState;
   bool functionKey;
   /* Create the label. */
   SLabel popup(this,CENTER, CENTER, mesg, 
			 TRUE, FALSE);
//   popup.setCDKLabelBackgroundAttrib(attrib);
   popup.setBKattrObj(attrib);
   oldCursState = curs_set(0);
   /* Draw it on the screen. */
   popup.drawCDKLabel(TRUE);
   /* Wait for some input. */
   keypad(popup.win, TRUE);
   popup.getchCDKObject(/*ObjOf(popup), */&functionKey);
   /* Kill it. */
   popup.destroyCDKLabel();
   /* Clean the screen. */
   curs_set(oldCursState);
   eraseCDKScreen();
   refreshCDKScreen();
} 

/*
 * This sets the background color of the widget.
 */
void GObj::setCDKObjectBackgroundColor(/*GObj *obj, */const char *color)
{
   int junk1, junk2;
   /* Make sure the color isn't null. */
   if (!color) {
      return;
   }
   /* Convert the value of the environment variable to a chtype. */
//   chtype *holder = char2Chtypeh(color, &junk1, &junk2);
	 chtstr holder(color,&junk1,&junk2);
   /* Set the widget's background color. */
   setBKattrObj(/*obj, */holder.getinh()[0]);
   /* Clean up. */
//   freeChtype(holder);
}


void GObj::setULcharObj(chtype ch)
{
	ULChar=ch;
}

void GObj::drawObj(bool Box)
{
}
void SEntry::drawObj(bool Box)
{
	drawCDKEntry(Box);
}
void SScroll::drawObj(bool Box)
{
	// mit 1 entstehen hier Fehler nur unten, nicht oben
	drawCDKScroll(Box,1);
}
void SFSelect::drawObj(bool Box)
{
	drawCDKFselect(Box);
}
void SAlphalist::drawObj(bool Box)
{
	drawCDKAlphalist(Box);
}

//void GObj::setBKattrObj(chtype attrib) { wbkgd(win, attrib); }

void SLabel::setBKattrObj(chtype attrib)
{
	setBKattrLabel(attrib);
}
/*
 * This sets the background attribute of the widget.
 */
void SEntry::setBKattrObj(chtype attrib)
{
	setBKattrEntry(attrib);
}

/*
 * This sets the background attribute of the widget.
 */
void SAlphalist::setBKattrObj(chtype attrib)
{
	entryField->setBKattrObj(attrib);
	scrollField->setBKattrObj(attrib);
}

/*
 * This sets the background attribute of the widget.
 */
void SScroll::setBKattrObj(chtype attrib)
{
	setBKattrScroll(attrib);
}

/*
 * This draws the file selector widget.
 */
void SFSelect::drawCDKFselect(/*GObj *object, */bool Box GCC_UNUSED, bool obmitscroller/*=0*/)
{
//   SFSelect *fselect =(SFSelect *)object;

   /* Draw in the shadow if we need to. */
   if (/*fselect->*/shadowWin) {
      drawShadow(/*fselect->*/shadowWin);
   }

   /* Draw in the entry field. */
   entryField->drawCDKEntry(/*fselect->entryField, ObjOf(fselect->entryField)->*/obbox);

   /* Draw in the scroll field. */
	 if (obmitscroller)
		 drawMyScroller(/*fselect*/);
}

/*
 * Store the name of the current working directory.
 */
void SFSelect::setPWD(/*SFSelect *fselect*/)
{
   char buffer[PATH_MAX];
   if (!getcwd(buffer, sizeof(buffer)))
      strcpy(buffer, ".");
	 this->pwd=buffer;
// #include <filesystem>
//	 this->pwd=std::filesystem::current_path();
}

/*
 * This opens the current directory and reads the contents.
 */
int CDKgetDirectoryContents(const char *directory, vector<string> *plist)
{
	/* Declare local variables.  */
	struct dirent *dirStruct;
	DIR *dp;
	/* Open the directory.  */
	dp = opendir(directory);
	/* Could we open the directory?  */
	if (!dp) {
		return -1;
	}
	/* Read the directory.  */
	while ((dirStruct = readdir(dp))) {
		if (strcmp(dirStruct->d_name, "."))
      plist->push_back(dirStruct->d_name);
	}
	/* Close the directory.  */
	closedir(dp);
	/* Sort the info.  */
	sort(plist->begin(),plist->end());
	/* Return the number of files in the directory.  */
	return 
		plist->size();
}

int mode2Filetype(mode_t mode)
{
	/* *INDENT-OFF* */
	static const struct {
		mode_t	mode;
		char	code;
	} table[] = {
#ifdef S_IFBLK
		{ S_IFBLK,  'b' },  /* Block device */
#endif
		{ S_IFCHR,  'c' },  /* Character device */
		{ S_IFDIR,  'd' },  /* Directory */
		{ S_IFREG,  '-' },  /* Regular file */
#ifdef S_IFLNK
		{ S_IFLNK,  'l' },  /* Socket */
#endif
#ifdef S_IFSOCK
		{ S_IFSOCK, '@' },  /* Socket */
#endif
		{ S_IFIFO,  '&' },  /* Pipe */
	};
	/* *INDENT-ON* */

	int filetype = '?';
	for (unsigned n = 0; n < elemzahl(table); n++) {
		if ((mode & S_IFMT) == table[n].mode) {
			filetype = table[n].code;
			break;
		}
	}
	return filetype;
}


/*
 * This creates a list of the files in the current directory.
 */
int SFSelect::setCDKFselectdirContents(/*CDKFSELECT *fselect*/)
{
	struct stat fileStat;
	vector<string> dirList;
	int fileCount;
	/* Get the directory contents. */
	fileCount = CDKgetDirectoryContents(this->pwd.c_str(), &dirList);
	if (fileCount <= 0) {
		return 0;
	}
	/* Clean out the old directory list. */
	this->dirContents = dirList;
	/* Set the properties of the files. */
	for (size_t x = 0; x < 
			dirList.size()
			; x++) {
		const char *attr = "";
		const char *mode = "?";

		/* FIXME: access() would give a more correct answer */
		if (!lstat(dirList[x].c_str(), &fileStat)) {
			mode = " ";
			if ((fileStat.st_mode & S_IXUSR)) {
				mode = "*";
			}
#if defined(S_IXGRP) && defined(S_IXOTH)
			else if (((fileStat.st_mode & S_IXGRP)) ||
					((fileStat.st_mode & S_IXOTH))) {
				mode = "*";
			}
#endif
		}
		switch (mode2Filetype(fileStat.st_mode)) {
			case 'l':
				attr = this->linkAttribute
					.c_str()
					;
				mode = "@";
				break;
			case '@':
				attr = this->sockAttribute
					.c_str()
					;
				mode = "&";
				break;
			case '-':
				attr = this->fileAttribute
					.c_str()
					;
				break;
			case 'd':
				attr = this->dirAttribute
					.c_str()
					;
				mode = "/";
				break;
			default:
				break;
		}
		this->dirContents[x]=attr+dirList[x]+mode;
	}
	return 1;
}

string make_pathname(const string& dir,const string& file)
{
	if (dir=="/") return dir+file;
	else return dir+"/"+file;
}

/*
 * trim the 'mode' from a copy of a dirContents[] entry.
 */
static char *trim1Char(char *source)
{
   size_t len;
   if ((len = strlen(source)))
      source[--len] = '\0';
   return source;
}

/*
 * Start of callback functions.
 */
int fselectAdjustScrollCB(EObjectType objectType GCC_UNUSED,
				  void *object GCC_UNUSED,
				  void *clientData,
				  chtype key)
{
	/* *INDENT-EQLS* */
	SFSelect *fselect  =(SFSelect *)clientData;
	SScroll *scrollp   =(SScroll *)fselect->scrollField;
	SEntry *entry      =(SEntry *)fselect->entryField;
	if (scrollp->listSize > 0) {
		char *current;
		/* Move the scrolling list. */
		fselect->injectMyScroller(key);
		/* Get the currently highlighted filename. */
		current = scrollp->pitem[scrollp->currentItem].chtype2Char();
		trim1Char(current);
		/* Set the value in the entry field. */
		entry->setCDKEntryValue(make_pathname(fselect->pwd, current));
		entry->drawCDKEntry(/*entry, ObjOf(entry)->*/entry->obbox);
		return (TRUE);
	}
	Beep();
	return (FALSE);
}

// Pfadname einer Datei
//std::string dirName(const std::string& path)
std::string dirName(string path)
{
  size_t letzt=path.find_last_of("/\\");
	if (letzt==string::npos) return {};
  return path.substr(0,letzt);
} // std::string dir_name(std::string const & path)
std::string dirName(const char* pfad)
{
	string path{pfad};
	return dirName(path);
} // std::string dir_name(std::string const & path)

/*
 * This takes a ~ type account name and returns the full pathname.
 */
static const char *expandTilde(const char *filename)
{
	const char *result = 0;
	std::string account,pathname;
	int len;

	/* Make sure the filename is not null/empty, and begins with a tilde */
	if ((filename) &&
			(len =(int)strlen(filename)) &&
			filename[0] == '~' &&
			(account=filename,!account.empty())
			&& (pathname=filename,!pathname.empty())
		)
	{
		bool slash = FALSE;
		int len_a = 0;
		int len_p = 0;
		struct passwd *accountInfo;

		/* Find the account name in the filename. */
		for (int x = 1; x < len; x++) {
			if (filename[x] == '/' && !slash) {
				slash = TRUE;
			} else if (slash) {
				pathname[len_p++] = filename[x];
			} else {
				account[len_a++] = filename[x];
			}
		}
		account.resize(len_a);
		pathname.resize(len_p);

		//const char *home = 0;
		string home;
#ifdef HAVE_PWD_H
		if (!account.empty() && (accountInfo=getpwnam(account.c_str()))) {
			home = accountInfo->pw_dir;
		}
#endif
//		if (home == 0 || *home == '\0')
		if (home.empty())
			home = getenv("HOME");
//		if (home == 0 || *home == '\0')
		if (home.empty())
			home = "/";

		/*
		 * Construct the full pathname. We do this because someone
		 * may have a pathname at the end of the account name
		 * and we want to keep it.
		 */
		result = make_pathname(home, pathname).c_str();

	}
	return result;
}

string format1String(const char* format, const char *stri)
{
	string ziel;
	ziel.resize(strlen(format)+strlen(stri));
	sprintf(&ziel[0],format,stri);
	ziel.resize(ziel.find((char)0));
	return ziel;
}

string errorMessage(const char *format)
{
	char *message;
#ifdef HAVE_STRERROR
	message = strerror(errno);
#else
	message = "Unknown reason.";
#endif
	return format1String(format, message);
}

string format1StrVal(const char* format, const char *stri, int value)
{
	string ziel;
	ziel.resize(strlen(format)+strlen(stri)+20);
	sprintf(&ziel[0],format,stri,value);
	ziel.resize(ziel.find((char)0));
	return ziel;
}

string format1Number(const char* format, long value)
{
	string ziel;
	ziel.resize(strlen(format)+20);
	sprintf(&ziel[0],format,value);
	ziel.resize(ziel.find((char)0));
	return ziel;
}

string format1Date(const char* format, time_t value)
{
	string ziel;
	char *temp=ctime(&value);
	ziel.resize(strlen(format)+strlen(temp)+1);
	sprintf(&ziel[0],format,trim1Char(temp));
	ziel.resize(ziel.find((char)0));
	return ziel;
}

/*
 * This function sets the information inside the file selector.
 */
void SFSelect::setCDKFselect(/*SFSelect *fselect,*/
		    const char *directory,
		    chtype fieldAttrib,
		    chtype pfiller,
		    chtype phighlight,
		    const char *dirAttribute,
		    const char *fileAttribute,
		    const char *linkAttribute,
		    const char *sockAttribute,
		    bool Box GCC_UNUSED)
{
	/* *INDENT-EQLS* */
	const char *tempDir        = 0;
	/* Keep the info sent to us. */
	this->fieldAttribute = fieldAttrib;
	this->fillerChar = pfiller;
	this->highlight = phighlight;
	/* Set the attributes of the entry field/scrolling list. */
	//   setCDKEntryFillerChar(entryField, filler);
	entryField->filler=pfiller;
	//   setCDKScrollHighlight(scrollField, phighlight);
	scrollField->highlight=phighlight;

	/* Only do the directory stuff if the directory is not null. */
	if (directory) {
		string newDirectory;
		/* Try to expand the directory if it starts with a ~ */
		if ((tempDir = expandTilde(directory))) {
			newDirectory = tempDir;
		} else {
			newDirectory=directory;
		}
		/* Change directories. */
		if (chdir(newDirectory.c_str())) {
			vector<string> mesg(4);
			Beep();
			/* Could not get into the directory, pop up a little message. */
			mesg[0] = format1String("<C>Could not change into %s", newDirectory.c_str());
			mesg[1] = errorMessage("<C></U>%s");
			mesg[2]=" ";
			mesg[3]="<C>Press Any Key To Continue.";
			/* Pop Up a message. */
			screen->popupLabel(/*ScreenOf(this), */ mesg);
			/* Clean up some memory. */
			/* Get out of here. */
			eraseObj(); // eraseCDKFselect(/*this*/);
			drawCDKFselect(/*this, ObjOf(this)->*/obbox);
			return;
		}
	}
	/*
	 * If the information coming in is the same as the information
	 * that is already there, there is no need to destroy it.
	 */
	if (this->pwd != directory) {
		setPWD(/*this*/);
	}
	this->fileAttribute=fileAttribute;
	this->dirAttribute=dirAttribute;
	this->linkAttribute=linkAttribute;
	this->sockAttribute=sockAttribute;

	/* Set the contents of the entry field. */
	entryField->setCDKEntryValue(/*entryField, */this->pwd);
	entryField->drawCDKEntry(/*entryField, ObjOf(entryField)->*/obbox);

	/* Get the directory contents. */
	if (!setCDKFselectdirContents(/*this*/)) {
		Beep();
		return;
	}
	/* Set the values in the scrolling list. */
	scrollField->setCDKScrollItems(/*scrollField,*/ &dirContents, FALSE);
}

/*
 * Return the plain string that corresponds to an item in dirContents[].
 */
const char *SFSelect::contentToPath(/*SFSelect *fselect, */const char *content)
{
   char *tempChar;
   int j, j2;

//   chtype *tempChtype = char2Chtypeh(content, &j, &j2);
	 chtstr tempChtype(content,&j,&j2);
   tempChar = tempChtype.chtype2Char();
   trim1Char(tempChar);	/* trim the 'mode' stored on the end */

   /* Create the pathname. */
   const char *result = make_pathname(this->pwd,tempChar).c_str();

   /* Clean up. */
//   freeChtype(tempChtype);
   return result;
}


/*
 * This tries to complete the filename.
 */
static int completeFilenameCB(EObjectType objectType GCC_UNUSED,
			       void *object GCC_UNUSED,
			       void *clientData,
			       chtype key GCC_UNUSED)
{
	/* *INDENT-EQLS* */
	SFSelect *fselect  = (SFSelect *)clientData;
	SScroll *scrollp   = fselect->scrollField;
	SEntry *entry      = fselect->entryField;
	string filename(entry->efld);
	string mydirname      = dirName(filename);
	const char *newFilename    = 0;
	int isDirectory;
	vector<string> plist;

	/* Make sure the filename is not null/empty. */
	size_t filenameLen{filename.length()};
	if (filename.empty()) {
		Beep();
		return (TRUE);
	}

	/* Try to expand the filename if it starts with a ~ */
	if ((newFilename = expandTilde(filename.c_str()))) {
		filename = newFilename;
		entry->setCDKEntryValue(filename);
		entry->drawCDKEntry(entry->obbox);
	}

	/* Make sure we can change into the directory. */
	isDirectory = chdir(filename.c_str());
	if (chdir(fselect->pwd.c_str())) {
		return FALSE;
	}
	fselect->setCDKFselect(/*fselect,*/
			(isDirectory ? mydirname : filename).c_str()
			,fselect->fieldAttribute
			,fselect->fillerChar
			,fselect->highlight
			,fselect->dirAttribute.c_str()
			,fselect->fileAttribute.c_str()
			,fselect->linkAttribute.c_str()
			,fselect->sockAttribute.c_str()
			,fselect->obbox);
	/* If we can, change into the directory. */
	if (isDirectory) {
		/*
		 * Set the entry field with the filename so the current
		 * filename selection shows up.
		 */
		entry->setCDKEntryValue(/*entry, */filename);
		entry->drawCDKEntry(/*entry, ObjOf(entry)->*/entry->obbox);
	}

	/* Create the file list. */
		for (size_t x = 0; x < fselect->dirContents.size(); x++) {
			plist.push_back(fselect->contentToPath(/*fselect,*/fselect->dirContents[x].c_str()));
		}

		size_t Index;
		/* Look for a unique filename match. */
		Index = searchList(
		&plist,
				filename.c_str());
		/* If the index is less than zero, return we didn't find a match. */
		if (Index < 0) {
			Beep();
		} else {
			/* Move to the current item in the scrolling list. */
			int difference = Index - scrollp->currentItem;
			int absoluteDifference = abs(difference);
			if (difference < 0) {
				for (int x = 0; x < absoluteDifference; x++) {
					fselect->injectMyScroller(/*fselect, */KEY_UP);
				}
			} else if (difference > 0) {
				for (int x = 0; x < absoluteDifference; x++) {
					fselect->injectMyScroller(/*fselect, */KEY_DOWN);
				}
			}
			fselect->drawMyScroller(/*fselect*/);

			/* Ok, we found a match, is the next item similar? */
			if (Index + 1 < fselect->
					dirContents.size()
					&& !plist[Index + 1].empty()
					&& plist[Index + 1]==filename
						) {
				size_t currentIndex = Index;
				int baseChars =(int)filenameLen;
				int matches = 0;

				/* Determine the number of files which match. */
				while (currentIndex < fselect->
					dirContents.size()
						) {
					if (!plist[currentIndex].empty()) {
					  if (filename==plist[currentIndex]) {
							matches++;
						}
					}
					currentIndex++;
				}
				/* Start looking for the common base characters. */
				for (;;) {
					int secondaryMatches = 0;
					for (size_t x = Index; x < Index + matches; x++) {
						if (plist[Index][baseChars] == plist[x][baseChars]) {
							secondaryMatches++;
						}
					}
					if (secondaryMatches != matches) {
						Beep();
						break;
					}
					/* Inject the character into the entry field. */
					fselect->entryField->injectSEntry(/*fselect->entryField,*/(chtype)plist[Index][baseChars]);
					baseChars++;
				}
			} else {
				if (Index<plist.size())
					/* Set the entry field with the found item. */
					entry->setCDKEntryValue(/*entry, */plist[Index]);
				entry->drawCDKEntry(/*entry, ObjOf(entry)->*/entry->obbox);
			}
		}
	return(TRUE);
}

/*
 * This function takes a mode_t type and creates a string represntation
 * of the permission mode.
 */
int mode2Char(char *string, mode_t mode)
{
	/* *INDENT-OFF* */
	static struct {
		mode_t	mask;
		unsigned	col;
		char	flag;
	} table[] = {
		{ S_IRUSR,	1,	'r' },
		{ S_IWUSR,	2,	'w' },
		{ S_IXUSR,	3,	'x' },
#if defined(S_IRGRP) && defined(S_IWGRP) && defined(S_IXGRP)
		{ S_IRGRP,	4,	'r' },
		{ S_IWGRP,	5,	'w' },
		{ S_IXGRP,	6,	'x' },
#endif
#if defined(S_IROTH) && defined(S_IWOTH) && defined(S_IXOTH)
		{ S_IROTH,	7,	'r' },
		{ S_IWOTH,	8,	'w' },
		{ S_IXOTH,	9,	'x' },
#endif
#ifdef S_ISUID
		{ S_ISUID,	3,	's' },
#endif
#ifdef S_ISGID
		{ S_ISGID,	6,	's' },
#endif
#ifdef S_ISVTX
		{ S_ISVTX,	9,	't' },
#endif
	};
	/* *INDENT-ON* */

	/* Declare local variables.  */
	int permissions = 0;
	int filetype = mode2Filetype(mode);
	unsigned n;

	/* Clean the string.  */
	cleanChar(string, 11, '-');
	string[11] = '\0';

	if (filetype == '?')
		return -1;

	for (n = 0; n < elemzahl(table); n++) {
		if ((mode & table[n].mask)) {
			string[table[n].col] = table[n].flag;
			permissions |= (int)table[n].mask;
		}
	}

	/* Check for unusual permissions.  */
#ifdef S_ISUID
	if (((mode & S_IXUSR) == 0) &&
			((mode & S_IXGRP) == 0) &&
			((mode & S_IXOTH) == 0) &&
			(mode & S_ISUID))
	{
		string[3] = 'S';
	}
#endif

	return permissions;
}

/*
 * This is a callback to the scrolling list which displays information
 * about the current file. (and the whole directory as well)
 */
static int displayFileInfoCB(EObjectType objectType GCC_UNUSED,
			      void *object,
			      void *clientData,
			      chtype key GCC_UNUSED)
{
	SEntry *entry =(SEntry *)object;
	SFSelect *fselect =(SFSelect *)clientData;
	SLabel *infoLabel;
	struct stat fileStat;
#ifdef HAVE_PWD_H
	struct passwd *pwEnt;
	struct group *grEnt;
#endif
	const char *filetype;
	string filename;
	vector<string> mesg(9);
	char stringMode[15];
	int intMode;
	bool functionKey;
	filename = fselect->entryField->efld;
	if (!lstat(filename.c_str(), &fileStat)) {
		switch (mode2Filetype(fileStat.st_mode)) {
			case 'l':
				filetype = "Symbolic Link";
				break;
			case '@':
				filetype = "Socket";
				break;
			case '-':
				filetype = "Regular File";
				break;
			case 'd':
				filetype = "Directory";
				break;
			case 'c':
				filetype = "Character Device";
				break;
			case 'b':
				filetype = "Block Device";
				break;
			case '&':
				filetype = "FIFO Device";
				break;
			default:
				filetype = "Unknown";
				break;
		}
	} else {
		filetype = "Unknown";
	}
	/* Get the user name and group name. */
#ifdef HAVE_PWD_H
	pwEnt = getpwuid(fileStat.st_uid);
	grEnt = getgrgid(fileStat.st_gid);
#endif
	/* Convert the mode_t type to both string and int. */
	intMode = mode2Char(stringMode, fileStat.st_mode);
	/* Create the message. */
	mesg[0] = format1String("Directory  : </U>%s", fselect->pwd.c_str());
	mesg[1] = format1String("Filename   : </U>%s", filename.c_str());
#ifdef HAVE_PWD_H
	mesg[2] = format1StrVal("Owner      : </U>%s<!U> (%d)", pwEnt->pw_name, (int)fileStat.st_uid);
	mesg[3] = format1StrVal("Group      : </U>%s<!U> (%d)", grEnt->gr_name, (int)fileStat.st_gid);
#else
	mesg[2] = format1Number("Owner      : (%ld)", (long)fileStat.st_uid);
	mesg[3] = format1Number("Group      : (%ld)", (long)fileStat.st_gid);
#endif
	mesg[4] = format1StrVal("Permissions: </U>%s<!U> (%o)", stringMode, intMode);
	mesg[5] = format1Number("Size       : </U>%ld<!U> bytes",(long)fileStat.st_size);
	mesg[6] = format1Date("Last Access: </U>%s", fileStat.st_atime);
	mesg[7] = format1Date("Last Change: </U>%s", fileStat.st_ctime);
	mesg[8] = format1String("File Type  : </U>%s", filetype);
	/* Create the pop up label. */
	infoLabel = new SLabel(entry->/*obj.*/screen,
			CENTER, CENTER,
			mesg,
			TRUE, FALSE);
	infoLabel->drawCDKLabel(/*infoLabel, */TRUE);
	infoLabel->getchCDKObject(/*ObjOf(infoLabel), */&functionKey);
	/* Clean up some memory. */
	infoLabel->destroyCDKLabel(/*infoLabel*/);
	/* Redraw the file selector. */
	fselect->drawCDKFselect(/*fselect, ObjOf(fselect)->*/fselect->obbox);
	return (TRUE);
}


/*
 * This creates a file selection widget.
 */
//SFSelect *newCDKFselect(
SFSelect::SFSelect(
		SScreen *cdkscreen,
		int xplace,
		int yplace,
		int height,
		int width,
		const char *title,
		const char *label,
		chtype fieldAttribute,
		chtype pfillerChar,
		chtype phighlight,
		const char *dAttribute,
		const char *fAttribute,
		const char *lAttribute,
		const char *sAttribute,
		bool obBox,
		bool pshadow,
		int highnr/*=0*/,
		int aktent/*=-1*/
		): ComboB(cdkscreen,cdkscreen->window,obBox,pshadow,vFSELECT,/*pAcceptsFocus*/1,/*phasFocus*/1,/*pisVisible*/1
			,/*xpos*/xplace,/*ypos*/yplace,height,width,/*highlight*/phighlight,/*fillerChar*/pfillerChar
			,/*objnr*/aktent
				)
{
//	cdktype = vFSELECT;
	/* *INDENT-EQLS* */
//	SFSelect *fselect  = 0;
//	int parentWidth      = getmaxx(cdkscreen->window);
//	int parentHeight     = getmaxy(cdkscreen->window);
//	int boxWidth;
//	int boxHeight;
//	int xpos             = xplace;
//	int ypos             = yplace;
	int tempWidth        = 0;
	int tempHeight       = 0;
	int labelLen, junk;
	/* *INDENT-OFF* */
	static const struct {
		int from;
		int to;
	} bindings[] = {
		{ CDK_BACKCHAR,	KEY_PPAGE },
		{ CDK_FORCHAR,	KEY_NPAGE },
	};
	/* *INDENT-ON* */

//	if ((fselect = newCDKObject(SFSelect, &my_funcs)) == 0) return (0);
//	::GObj();
//	objnr=aktent;
//	setBox(Box);

	/* Rejustify the x and y positions if we need to. */
	alignxy(cdkscreen->window, &xpos, &ypos, boxWidth, boxHeight);

	/* Make sure the box isn't too small. */
	boxWidth =(boxWidth < 15 ? 15 : boxWidth);
	boxHeight =(boxHeight < 6 ? 6 : boxHeight);

	/* Make the file selector window. */
	this->win = newwin(boxHeight, boxWidth, ypos, xpos);

	/* Is the window null? */
	if (!this->win) {
		destroyCDKObject();
		return;
	}
	keypad(this->win, TRUE);

	/* *INDENT-EQLS* Set some variables. */
//	screen           = cdkscreen;
//	this->parent              = cdkscreen->window;
	this->dirAttribute				=	dAttribute;
	this->fileAttribute       = fAttribute;
	this->linkAttribute				= lAttribute;
	this->sockAttribute				= sAttribute;
//	this->highlight           = phighlight;
//	this->fillerChar     = pfillerChar;
	this->fieldAttribute      = fieldAttribute;
	this->boxHeight           = boxHeight;
	this->boxWidth            = boxWidth;
//	initExitType(this);
//	exitType=vNEVER_ACTIVATED;
	/*ObjOf(this)->*/inputWindow = this->win;
//	this->shadow              = shadow;
	this->shadowWin           = 0;

   /* Get the present working directory. */
   setPWD();

   /* Get the contents of the current directory. */
   setCDKFselectdirContents();

   /* Create the entry field in the selector. */
//	 chtype *chtypeString= char2Chtypeh(label, &labelLen, &junk);
	 chtstr chtypeString(label,&labelLen,&junk);
//   freeChtype(chtypeString);
   tempWidth = (isFullWidth(width) ? FULL : boxWidth - 2 - labelLen);
   this->entryField = new SEntry(cdkscreen,
				      getbegx(this->win),
				      getbegy(this->win),
				      title, label,
				      fieldAttribute, fillerChar,
				      vMIXED, tempWidth, 0, 512,
				      obBox, FALSE,this,highnr);

   /* Make sure the widget was created. */
   if (!this->entryField) {
      destroyCDKObject();
      return ;
   }

   /* Set the lower left/right characters of the entry field. */
	 entryField->LLChar=ACS_LTEE;
   //setCDKEntryLLChar(this->entryField, ACS_LTEE);
	 entryField->LRChar=ACS_RTEE;
   //setCDKEntryLRChar(this->entryField, ACS_RTEE);

   /* Define the callbacks for the entry field. */
   entryField->bindCDKObject(/*vENTRY,
		  this->entryField,*/
		  KEY_UP,
		  fselectAdjustScrollCB,
		  this);
   entryField->bindCDKObject(/*vENTRY,
		  this->entryField,*/
		  KEY_PPAGE,
		  fselectAdjustScrollCB,
		  this);
   entryField->bindCDKObject(/*vENTRY,
		  this->entryField,*/
		  KEY_DOWN,
		  fselectAdjustScrollCB,
		  this);
   entryField->bindCDKObject(/*vENTRY,
		  this->entryField, */
		  KEY_NPAGE,
		  fselectAdjustScrollCB,
		  this);
   entryField->bindCDKObject(/*vENTRY,
		  this->entryField,*/
		  KEY_TAB,
		  completeFilenameCB,
		  this);
   entryField->bindCDKObject(/*vENTRY,
		  this->entryField,*/
		  CTRL('^'),
		  displayFileInfoCB,
		  this);

   /* Put the current working directory in the entry field. */
   entryField->setCDKEntryValue(/*this->entryField, */this->pwd);

   /* Create the scrolling list in the selector. */
   tempHeight = getmaxy(this->entryField->win) - borderSize;
   tempWidth = (isFullWidth(width) ? FULL : boxWidth - 1);
   this->scrollField = new SScroll(cdkscreen,
					getbegx(this->win),
					getbegy(this->win) + tempHeight,
					RIGHT,
					boxHeight - tempHeight,
					tempWidth,
					0,
					&this->dirContents,
					NONUMBERS, this->highlight,
					/*pmutter*/this,
					obBox, FALSE);

   /* Set the lower left/right characters of the entry field. */
//   scrollField->setCDKScrollULChar(/*this->scrollField, */ACS_LTEE);
   ULChar=ACS_LTEE;
//   scrollField->setCDKScrollURChar(/*this->scrollField, */ACS_RTEE);
	 URChar=ACS_RTEE;

   /* Do we want a shadow? */
   if (shadow) {
      this->shadowWin = newwin(boxHeight, boxWidth, ypos + 1, xpos + 1);
   }

   /* Setup the key bindings. */
   for (int x = 0; x <(int)elemzahl(bindings); ++x)
      bindCDKObject(/*vFSELECT,
		     this, */
		    (chtype)bindings[x].from,
		     getcCDKBind,
		    (void *)(long)bindings[x].to);

   registerCDKObject(cdkscreen, vFSELECT/*, this*/);

//   return (this);
}

/*
 * This function creates a dialog widget.
 */
SDialog::SDialog(SScreen *cdkscreen,
			 int xplace,
			 int yplace,
			 vector<string> *mesg,
			 vector<string> *buttonLabel,
			 chtype phighlight,
			 bool pseparator,
			 bool obBox,
			 bool pshadow
		): GObj(cdkscreen,cdkscreen->window,obBox,pshadow,vDIALOG,/*pAcceptsFocus*/1,/*phasFocus*/1,/*pisVisible*/1)
	,separator(pseparator),highlight(phighlight)
{
   /* *INDENT-EQLS* */
   // CDKDIALOG *dialog    = 0;
   int boxHeight;
   int boxWidth         = MIN_DIALOG_WIDTH;
   int maxmessagewidth  = -1;
   int buttonwidth      = 0;
   int xpos             = xplace;
   int ypos             = yplace;
//   int temp             = 0;
   int buttonadj        = 0;

//	 ::GObj();
//	 setBox(obBox);
   boxHeight = mesg->size() + 2 * borderSize + separator + 1;

   for (size_t x = 0; x < mesg->size() ; x++) {
		 /* Translate the char * message to a chtype * */
		 int len,pos;
		 chtstr infoneu(mesg->at(x).c_str(),&len,&pos);
		 pinfo.insert(pinfo.begin()+x,infoneu);
		 infoLen.insert(infoLen.begin()+x,len);
		 infoPos.insert(infoPos.begin()+x,pos);
		 maxmessagewidth  = MAXIMUM(maxmessagewidth, /*label->*/infoLen[x]);
	 }
   maxmessagewidth += 2 * /*BorderOf(label)*/ borderSize;

   /* Translate the button label char * to a chtype * */
	 for (size_t x = 0; x < buttonLabel->size(); x++) {
		 int len,pos;
		 chtstr buttonneu(buttonLabel->at(x).c_str(),&len,&pos);
		 pbutton.insert(pbutton.begin()+x,buttonneu);
		 buttonLen.insert(buttonLen.begin()+x,len);
		 buttonPos.insert(buttonPos.begin()+x,pos);
		 buttonwidth            += this->buttonLen[x] + 1;
	 }
	 buttonwidth--;

	 /* Determine the final dimensions of the box. */
	 boxWidth = MAXIMUM (boxWidth, maxmessagewidth);
	 boxWidth = MAXIMUM (boxWidth, buttonwidth);
	 boxWidth = boxWidth + 2 + 2 * borderSize;

	 /* Now we have to readjust the x and y positions. */
	 alignxy(cdkscreen->window, &xpos, &ypos, boxWidth, boxHeight);

   /* *INDENT-EQLS* Set up the dialog box attributes. */
//   screen            = cdkscreen;
//   this->parent               = cdkscreen->window;
   this->win                  = newwin (boxHeight, boxWidth, ypos, xpos);
   this->shadowWin            = 0;
   this->currentButton        = 0;
   this->boxHeight            = boxHeight;
   this->boxWidth             = boxWidth;
//   this->highlight            = highlight;
//   this->separator            = separator;
   // initExitType (this);
//	 exitType=vNEVER_ACTIVATED;
//	 acceptsFocus = TRUE;
   inputWindow  = this->win;
//   this->shadow               = shadow;

   /* If we couldn't create the window, we should return a null value. */
   if (!this->win) {
      destroyCDKObject();
      return;
   }
   keypad(this->win, TRUE);

   /* Find the button positions. */
   buttonadj = ((int)((boxWidth - buttonwidth) / 2));
   for (size_t x = 0; x < pbutton.size(); x++) {
      this->buttonPos[x] = buttonadj;
      buttonadj = buttonadj + this->buttonLen[x] + borderSize/*BorderOf (this)*/;
   }

   /* Create the string alignments. */
   for (size_t x = 0; x < pinfo.size(); x++) {
      this->infoPos[x] = justifyString(boxWidth - 2 * borderSize/*BorderOf (this)*/, this->infoLen[x], this->infoPos[x]);
   }

   /* Was there a shadow? */
   if (shadow) {
      this->shadowWin = newwin(boxHeight, boxWidth, ypos + 1, xpos + 1);
   }
   /* Register this baby. */
   registerCDKObject(cdkscreen, vDIALOG/*, this*/);
   /* Return the dialog box pointer. */
//   return (this);
}


/*
 * This lets the user select the button.
 */
int SDialog::activateCDKDialog(/*CDKDIALOG *dialog, */chtype *actions)
{
	chtype input = 0;
	bool functionKey;
	int ret;

	/* Draw the dialog box. */
	drawCDKDialog(/*dialog, ObjOf (dialog)->*/obbox);

	/* Lets move to the first button. */
	writeChtypeAttrib (this->win,
			this->buttonPos[this->currentButton],
			this->boxHeight - 1 - borderSize,
			this->pbutton[this->currentButton].getinh(),
			this->highlight,
			HORIZONTAL,
			0, this->buttonLen[this->currentButton]);
	wrefresh(this->win);

	if (!actions) {
		for (;;) {
			input = (chtype)getchCDKObject(/*ObjOf (this), */&functionKey);
			/* Inject the character into the widget. */
			ret = injectSDialog(/*this, */input);
			if (this->exitType != vEARLY_EXIT) {
				return ret;
			}
		}
	} else {
		int length = chlen(actions);
		/* Inject each character one at a time. */
		for (int x = 0; x < length; x++) {
			ret = injectSDialog(/*this, */actions[x]);
			if (this->exitType != vEARLY_EXIT) {
				return ret;
			}
		}
	}
	/* Set the exit type and exit. */
	setExitType(0);
	return -1;
}

/*
 * This injects a single character into the dialog widget.
 */
int SDialog::injectSDialog(/*GObj *object, */chtype input)
{
	/* *INDENT-EQLS* */
	//   CDKDIALOG *widget = (CDKDIALOG *)object;
	int lastButton    = pbutton.size()/*this->buttonCount*/ - 1;
	int ppReturn      = 1;
	int ret           = -1; // unknownInt;
	bool complete     = FALSE;

	/* Set the exit type. */
	setExitType(0);

	/* Check if there is a pre-process function to be called. */
	if ((preProcessFunction)) {
		ppReturn = (preProcessFunction) (vDIALOG,
				this,
				(preProcessData),
				input);
	}

	/* Should we continue? */
	if (ppReturn) {
		/* Check for a key binding. */
		if (checkCDKObjectBind(/*vDIALOG, this, */input)) {
			//checkEarlyExit(this);
			complete = TRUE;
		} else {
			int firstButton = 0;
			switch (input) {
				case KEY_LEFT:
				case KEY_BTAB:
				case KEY_BACKSPACE:
					if (this->currentButton == firstButton) {
						this->currentButton = lastButton;;
					} else {
						this->currentButton--;
					}
					break;
				case KEY_RIGHT:
				case KEY_TAB:
				case SPACE:
					if (this->currentButton == lastButton) {
						this->currentButton = firstButton;
					} else {
						this->currentButton++;
					}
					break;
				case KEY_UP:
				case KEY_DOWN:
					Beep();
					break;
				case CDK_REFRESH:
					screen->eraseCDKScreen(/*ScreenOf (this)*/);
					screen->refreshCDKScreen(/*ScreenOf (this)*/);
					break;
				case KEY_ESC:
					setExitType(/*this, */input);
					complete = TRUE;
					break;
				case KEY_ERROR:
					setExitType(/*this, */input);
					complete = TRUE;
					break;
				case KEY_ENTER:
					setExitType(/*this, */input);
					ret = this->currentButton;
					complete = TRUE;
					break;
				default:
					break;
			}
		}
		/* Should we call a post-process? */
		if (!complete && (postProcessFunction)) {
			(postProcessFunction)(vDIALOG,
					this,
					(postProcessData),
					input);
		}
	}
	if (!complete) {
		drawCDKDialogButtons(/*widget*/);
		wrefresh(this->win);
		setExitType(/*this, */0);
	}
	this->resultData.valueInt = ret;
//	return(ret != unknownInt);
	return ret;
}

/*
 * This moves the dialog field to the given location.
 */
void SDialog::moveCDKDialog(/*GObj *object,*/
			    int xplace,
			    int yplace,
			    bool relative,
			    bool refresh_flag)
{
//   CDKDIALOG *dialog = (CDKDIALOG *)object;
   /* *INDENT-EQLS* */
   int currentX = getbegx(this->win);
   int currentY = getbegy(this->win);
   int xpos     = xplace;
   int ypos     = yplace;

   /*
    * If this is a relative move, then we will adjust where we want
    * to move to.
    */
   if (relative) {
      xpos = getbegx(this->win) + xplace;
      ypos = getbegy(this->win) + yplace;
   }

   /* Adjust the window if we need to. */
   alignxy (screen->window, &xpos, &ypos, this->boxWidth, this->boxHeight);

   /* Get the difference. */
   int xdiff = currentX - xpos;
   int ydiff = currentY - ypos;

   /* Move the window to the new location. */
   moveCursesWindow(this->win, -xdiff, -ydiff);
   moveCursesWindow(this->shadowWin, -xdiff, -ydiff);

   /* Touch the windows so they 'move'. */
   refreshCDKWindow(screen->window);

   /* Redraw the window, if they asked for it. */
   if (refresh_flag) {
      drawCDKDialog(/*this, ObjOf (this)->*/obbox);
   }
}

/*
 * This function draws the dialog widget.
 */
void SDialog::drawCDKDialog(/*GObj *object, */bool obBox)
{
   /* Is there a shadow? */
   if (this->shadowWin) {
      drawShadow(this->shadowWin);
   }
   /* Box the widget if they asked. */
   if (obBox) {
      drawObjBox(this->win/*, ObjOf (this)*/);
   }
   /* Draw in the message. */
   for (size_t x = 0; x < this->pinfo.size(); x++) {
      writeChtype(this->win,
		   this->infoPos[x] + borderSize, x + borderSize,
		   this->pinfo[x].getinh(),
		   HORIZONTAL, 0,
		   this->infoLen[x]);
   }
   /* Draw in the buttons. */
   drawCDKDialogButtons(/*dialog*/);
   wrefresh(this->win);
}

/*
 * This function destroys the dialog widget.
 */
void SDialog::destroyCDKDialog(/*GObj *object*/)
{
	//   if (object != 0) {
	/* Clean up the windows. */
	deleteCursesWindow(win);
	deleteCursesWindow(shadowWin);
	/* Clean the key bindings. */
	cleanCDKObjectBindings(/*vDIALOG, dialog*/);

	/* Unregister this object. */
	unregisterCDKObject(vDIALOG/*, dialog*/);
	//   }
}

/*
 * This function erases the dialog widget from the screen.
 */
void SDialog::eraseCDKDialog(/*GObj *object*/)
{
	//   if (validCDKObject (object)) {
	eraseCursesWindow(win);
	eraseCursesWindow(shadowWin);
	//   }
}

/*
 * This sets attributes of the dialog box.
 */
// kommt nirgends vor
/*
void SDialog::setCDKDialog(//CDKDIALOG *dialog,
									chtype highlight, bool separator, bool obBox)
{
   setCDKDialogHighlight(highlight);
   setCDKDialogSeparator(separator);
   setBox(obBox);
}
*/

/*
 * This sets the highlight attribute for the buttons.
 */
void SDialog::setCDKDialogHighlight(/*CDKDIALOG *dialog, */chtype hi)
{
   /*dialog->*/highlight = hi;
}
/*
chtype SDialog::getCDKDialogHighlight()
{
   return highlight;
}
*/

/*
 * This sets whether or not the dialog box will have a separator line.
 */
void SDialog::setCDKDialogSeparator(/*CDKDIALOG *dialog, */bool sep)
{
   separator = sep;
}
/*
bool SDialog::getCDKDialogSeparator()
{
   return separator;
}
*/

/*
bool SDialog::getCDKDialogBox()
{
   return obbox;
}
*/

/*
 * This sets the background attribute of the widget.
 */
void SDialog::setBKattrDialog(/*GObj *object, */chtype attrib)
{
	wbkgd(this->win, attrib);
}

/*
 * This draws the dialog buttons and the separation line.
 */
void SDialog::drawCDKDialogButtons(/*CDKDIALOG *dialog*/)
{
	for (size_t x = 0; x < pbutton.size(); x++) {
		writeChtype(this->win,
				this->buttonPos[x],
				this->boxHeight - 1 - borderSize,
				this->pbutton[x].getinh(),
				HORIZONTAL, 0,
				this->buttonLen[x]);
	}

	/* Draw the separation line. */
	if (this->separator) {
		chtype boxattr = BXAttr;

		for (int x = 1; x < this->boxWidth - 1; x++) {
			(void)mvwaddch(this->win, this->boxHeight - 2 - borderSize, x, ACS_HLINE | boxattr);
		}
		(void)mvwaddch(this->win, this->boxHeight - 2 - borderSize, 0, ACS_LTEE | boxattr);
		(void)mvwaddch(this->win, this->boxHeight - 2 - borderSize, getmaxx (this->win) - 1, ACS_RTEE | boxattr);
	}
	writeChtypeAttrib(this->win,
			this->buttonPos[this->currentButton],
			this->boxHeight - 1 - borderSize,
			this->pbutton[this->currentButton].getinh(),
			this->highlight,
			HORIZONTAL, 0,
			this->buttonLen[this->currentButton]);
}

void SDialog::focusCDKDialog(/*GObj *object*/)
{
   drawCDKDialog(/*widget, ObjOf (widget)->*/obbox);
}

void SDialog::unfocusCDKDialog(/*GObj *object*/)
{
   drawCDKDialog(/*this, ObjOf (widget)->*/obbox);
}

GObj::GObj(
			 SScreen* pscreen
			 ,WINDOW* pparent
			 ,bool obBox
			 ,bool pshadow
			 ,EObjectType pcdktype
			 ,bool pacceptsFocus
			 ,bool phasFocus
			 ,bool pisVisible
			 ,int objnr/*=-1*/
			 )
		 :screen(pscreen),parent(pparent),obbox(obBox),borderSize(obBox?1:0),shadow(pshadow),cdktype(pcdktype),
			acceptsFocus(pacceptsFocus),hasFocus(phasFocus),isVisible(pisVisible)
	 /* set default line-drawing characters */
	 ,ULChar(ACS_ULCORNER)
	 ,URChar(ACS_URCORNER)
	 ,LLChar(ACS_LLCORNER)
	 ,LRChar(ACS_LRCORNER)
	 ,VTChar(ACS_VLINE)
	 ,HZChar(ACS_HLINE)
	 ,BXAttr(A_NORMAL)
	 /* set default exit-types */
	 ,exitType(vNEVER_ACTIVATED)
	 ,earlyExit(vNEVER_ACTIVATED)
	 ,parentWidth(parent?parent->_maxx:ERR)
   ,parentHeight(parent?parent->_maxy:ERR)
{
	all_objects.push_back(this);
}

//dummyRefreshData (Dialog)
//dummySaveData (Dialog)
SScroll_basis::SScroll_basis(
			 SScreen* pscreen
			 ,WINDOW* pparent
			 ,bool obBox
			 ,bool pshadow
			 ,EObjectType pcdktype
			 ,bool pacceptsFocus
			 ,bool phasFocus
			 ,bool pisVisible
			 ,int objnr/*=-1*/
			 )
	: GObj(pscreen,pparent,obBox,pshadow,pcdktype,pacceptsFocus,phasFocus,pisVisible,objnr/*=-1*/)
{
}

ComboB::ComboB(
		SScreen* pscreen
		,WINDOW* pparent
		,bool obBox
		,bool pshadow
		,EObjectType pcdktype
		,bool pacceptsFocus
		,bool phasFocus
		,bool pisVisible
		,int xplace
		,int yplace
		,int height
		,int width
		,chtype phighlight
		,chtype pfillerChar
		,int objnr/*=-1*/
		)
	:GObj(pscreen,pparent,obBox,pshadow,pcdktype,pacceptsFocus,phasFocus,pisVisible,objnr),xpos(xplace),ypos(yplace)
	 ,height(height),width(width),highlight(phighlight),fillerChar(pfillerChar)
	 ,boxHeight(setWidgetDimension(parentHeight, height, 0))
	 ,boxWidth(setWidgetDimension(parentWidth, width, 0))
{
	/*
	 * If the height is a negative value, the height will
	 * be ROWS-height, otherwise, the height will be the
	 * given height.
	 */
//	boxHeight = setWidgetDimension(parentHeight, height, 0);

	/*
	 * If the width is a negative value, the width will
	 * be COLS-width, otherwise, the width will be the
	 * given width.
	 */
//	boxWidth = setWidgetDimension(parentWidth, width, 0);

}

CDKBINDING::CDKBINDING(BINDFN f,void* d)
	:bindFunction(f),bindData(d)
{
}

CDKBINDING::CDKBINDING()
{
}

void GObj::focusObj()
{
}

void GObj::unfocusObj()
{
}

int GObj::injectObj(chtype)
{
	return 0;
}
void SEntry::focusObj()
{
	focusCDKEntry();
}
void SEntry::unfocusObj()
{
	unfocusCDKEntry();
}
void SEntry::eraseObj()
{
	eraseCDKEntry();
}
void SEntry::destroyObj()
{
	this->~SEntry();
}
int SEntry::injectObj(chtype ch)
{
	return injectSEntry(ch);
}
void SScroll::destroyObj()
{
	this->~SScroll();
}
void SScroll::eraseObj()
{
	eraseCDKScroll();
}
int SScroll::injectObj(chtype ch)
{
	return injectSScroll(ch);
}
void SScroll::focusObj()
{
	focusCDKScroll();
}
void SScroll::unfocusObj()
{
	unfocusCDKScroll();
}
void SFSelect::destroyObj()
{
	this->~SFSelect();
}
int SFSelect::injectObj(chtype ch)
{
	return injectSFselect(ch);
}
void SFSelect::focusObj()
{
	focusCDKFileSelector();
}
void SFSelect::unfocusObj()
{
	unfocusCDKFileSelector();
}
	 void SAlphalist::destroyObj()
{
	this->~SAlphalist();
}
int SAlphalist::injectObj(chtype ch)
{
	return injectSAlphalist(ch);
}
void SAlphalist::focusObj()
{
	focusCDKAlphalist();
}
void SAlphalist::unfocusObj()
{
	unfocusCDKAlphalist();
}
