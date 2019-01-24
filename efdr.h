#define NCURSES_INTERNALS // fuer openSuse, nicht ubuntu

#ifdef HAVE_XCURSES
#include <xcurses.h>
#ifndef mvwhline
#define mvwhline(win,y,x,c,n)     (wmove(win,y,x) == ERR ? ERR : whline(win,c,n))
#endif
#ifndef mvwvline
#define mvwvline(win,y,x,c,n)     (wmove(win,y,x) == ERR ? ERR : wvline(win,c,n))
#endif
#elif defined(HAVE_NCURSESW_NCURSES_H)
#include <ncursesw/ncurses.h>
#elif defined(HAVE_NCURSES_NCURSES_H)
#include <ncurses/ncurses.h>
#elif defined(HAVE_NCURSES_H)
#include <ncurses.h>
#else
#include <curses.h>
#endif
#include <map> // bindv
//#include <set> // plist
#include <vector> // vector<chtstr> titles

//#include "cdk_test.h"
#ifndef CDKINCLUDES
#ifndef CDK_TEST_H
#define CDK_TEST_H
/*
 * The whole point of this header is to define ExitProgram(), which is used for
 * leak-checking when ncurses's _nc_free_and_exit() function is available. 
 * Invoking that rather than 'exit()' tells ncurses to free all of the
 * "permanent" memory leaks, making analysis much simpler.
 */
#ifdef HAVE_NC_ALLOC_H

#ifndef HAVE_LIBDBMALLOC
#define HAVE_LIBDBMALLOC 0
#endif

#ifndef HAVE_LIBDMALLOC
#define HAVE_LIBDMALLOC 0
#endif

#ifndef HAVE_LIBMPATROL
#define HAVE_LIBMPATROL 0
#endif

#include <nc_alloc.h>

#else

#if defined(NCURSES_VERSION) && defined(HAVE__NC_FREE_AND_EXIT)
/* nc_alloc.h normally not installed */
extern void _nc_free_and_exit(int) GCC_NORETURN;
#define ExitProgram(code) _nc_free_and_exit(code)
#endif

#endif /* HAVE_NC_ALLOC_H */

#include <pwd.h> // getpwd
#include <grp.h> // getgrgid
#include <time.h> // ctime

#ifndef ExitProgram
#define ExitProgram(code) exit(code)
#endif

#endif /* CDK_TEST_H */
#endif /* CDKINCLUDES */
// GSchade 17.11.18
// enum einbauart { einb_direkt, einb_alphalist, einb_sonst };
//extern einbauart akteinbart;
struct GObj; // GObj
extern std::vector<GObj*> all_objects;

#include <string.h> // strlen
#include <stdlib.h> // malloc

// #define CDK_CONST /*nothing*/
// #define CDK_CSTRING CDK_CONST char *
// #define CDK_CSTRING2 CDK_CONST char * CDK_CONST *
// #define CDK_PATCHDATE 20180306
// #define CDK_VERSION "5.0"
// #define HAVE_DIRENT_H 1
// #define HAVE_GETBEGX 1
// #define HAVE_GETBEGY 1
// #define HAVE_GETCWD 1
// #define HAVE_GETLOGIN 1
// #define HAVE_GETMAXX 1
// #define HAVE_GETMAXY 1
// #define HAVE_GETOPT_H 1
// #define HAVE_GETOPT_HEADER 1
// #define HAVE_GRP_H 1
// #define HAVE_INTTYPES_H 1
// #define HAVE_LIMITS_H 1
// #define HAVE_LSTAT 1
// #define HAVE_MEMORY_H 1
// #define HAVE_MKTIME 1
#define HAVE_NCURSES_H 1
#define HAVE_PWD_H 1
#define HAVE_SETLOCALE 1
// #define HAVE_SLEEP 1
#define HAVE_START_COLOR 1
// #define HAVE_STDINT_H 1
// #define HAVE_STDLIB_H 1
// #define HAVE_STRDUP 1
#define HAVE_STRERROR 1
// #define HAVE_STRINGS_H 1
// #define HAVE_STRING_H 1
// #define HAVE_SYS_STAT_H 1
// #define HAVE_SYS_TYPES_H 1
// #define HAVE_TERM_H 1
// #define HAVE_TYPE_CHTYPE 1
// #define HAVE_UNCTRL_H 1
// #define HAVE_UNISTD_H 1
// #define MIXEDCASE_FILENAMES 1
// #define NCURSES 1
// #define PACKAGE "cdk"
// #define STDC_HEADERS 1
// #define SYSTEM_NAME "linux-gnu"
// #define TYPE_CHTYPE_IS_SCALAR 1
// #define setbegyx(win,y,x)((win)->_begy =(y),(win)->_begx =(x), OK)

// #define freeChecked(p)          if ((p) != 0) free(p)
// #define freeAndNull(p)          if ((p) != 0) { free(p); p = 0; }
/*
 * Declare miscellaneous defines.
 */
#define	LEFT		9000
#define	RIGHT		9001
#define	CENTER		9002
#define	TOP		9003
#define	BOTTOM		9004
#define	HORIZONTAL	9005
#define	VERTICAL	9006
#define	FULL		9007

#define NONE		0
#define ROW		1
#define COL		2

#define MAX_BINDINGS	300	/* unused by widgets */
#define MAX_ITEMS	2000	/* unused by widgets */
#define MAX_BUTTONS	200	/* unused by widgets */

#define	MAXIMUM(a,b)	((a) >(b) ?(a) :(b))
#define	MINIMUM(a,b)	((a) <(b) ?(a) :(b))
// #define	HALF(a)		((a) >> 1)

// #define NUMBER_FMT      "%4d. %s"
// #define NUMBER_LEN(s)  (8 + strlen(s))

#ifndef COLOR_PAIR
#define	COLOR_PAIR(a)	A_NORMAL
#endif
/*
 * This header file adds some useful curses-style definitions.
 */

#undef CTRL
#define CTRL(c)		((c)&0x1f)

#undef  CDK_REFRESH
#define CDK_REFRESH	CTRL('L')
#undef  CDK_PASTE
#define CDK_PASTE	CTRL('V')
#undef  CDK_COPY
#define CDK_COPY	CTRL('Y')
#undef  CDK_ERASE
#define CDK_ERASE	CTRL('U')
#undef  CDK_CUT
#define CDK_CUT		CTRL('X')
#undef  CDK_BEGOFLINE
#define CDK_BEGOFLINE	CTRL('A')
#undef  CDK_ENDOFLINE
#define CDK_ENDOFLINE	CTRL('E')
#undef  CDK_BACKCHAR
#define CDK_BACKCHAR	CTRL('B')
#undef  CDK_FORCHAR
#define CDK_FORCHAR	CTRL('F')
#undef  CDK_TRANSPOSE
#define CDK_TRANSPOSE	CTRL('T')
#undef  CDK_NEXT
#define CDK_NEXT	CTRL('N')
#undef  CDK_PREV
#define CDK_PREV	CTRL('P')
#undef  SPACE
#define SPACE		' '
#undef  DELETE
#define DELETE		'\177'	/* Delete key				*/
#undef  TAB
#define TAB		'\t'	/* Tab key.				*/
#undef  KEY_ESC
#define KEY_ESC		'\033'	/* Escape Key.				*/
#undef  KEY_RETURN
#define KEY_RETURN	'\012'	/* Return key				*/
#undef  KEY_TAB
#define KEY_TAB		'\t'	/* Tab key				*/
#undef  KEY_F1
#define KEY_F1          KEY_F(1)
#undef  KEY_F2
#define KEY_F2          KEY_F(2)
#undef  KEY_F3
#define KEY_F3          KEY_F(3)
#undef  KEY_F4
#define KEY_F4          KEY_F(4)
#undef  KEY_F5
#define KEY_F5          KEY_F(5)
#undef  KEY_F6
#define KEY_F6          KEY_F(6)
#undef  KEY_F7
#define KEY_F7          KEY_F(7)
#undef  KEY_F8
#define KEY_F8          KEY_F(8)
#undef  KEY_F9
#define KEY_F9          KEY_F(9)
#undef  KEY_F10
#define KEY_F10		KEY_F(10)
#undef  KEY_F11
#define KEY_F11		KEY_F(11)
#undef  KEY_F12
#define KEY_F12		KEY_F(12)

#define KEY_ERROR      ((chtype)ERR)


//#define ObjOf(ptr)              (&(ptr)->obj)
//#define ObjOf(ptr)              (ptr)
//#define MethodOf(ptr)           (ObjOf(ptr)->fn)
//#define ScreenOf(ptr)           (ObjOf(ptr)->screen)
//#define WindowOf(ptr)           (ScreenOf(ptr)->window)
//#define BorderOf(p)             (ObjOf(p)->borderSize)
//#define ResultOf(p)             (ObjOf(p)->resultData)
//#define ExitTypeOf(p)           (ObjOf(p)->exitType)
//#define EarlyExitOf(p)          (ObjOf(p)->earlyExit)

/* titles */
// #define TitleOf(w)              ObjOf(w)->title
// #define TitlePosOf(w)           ObjOf(w)->titlePos
// #define TitleLenOf(w)           ObjOf(w)->titleLen
// #define TitleLinesOf(w)         ObjOf(w)->titleLines

/* line-drawing characters */
//#define ULCharOf(w)             ObjOf(w)->ULChar
//#define URCharOf(w)             ObjOf(w)->URChar
//#define LLCharOf(w)             ObjOf(w)->LLChar
//#define LRCharOf(w)             ObjOf(w)->LRChar
//#define VTCharOf(w)             ObjOf(w)->VTChar
//#define HZCharOf(w)             ObjOf(w)->HZChar
//#define BXAttrOf(w)             ObjOf(w)->BXAttr

//#define setULCharOf(o,c)        MethodOf(o)->setULcharObj(ObjOf(o),c)
//#define setURCharOf(o,c)        MethodOf(o)->setURcharObj(ObjOf(o),c)
//#define setLLCharOf(o,c)        MethodOf(o)->setLLcharObj(ObjOf(o),c)
//#define setLRCharOf(o,c)        MethodOf(o)->setLRcharObj(ObjOf(o),c)
//#define setVTCharOf(o,c)        MethodOf(o)->setVTcharObj(ObjOf(o),c)
//#define setHZCharOf(o,c)        MethodOf(o)->setHZcharObj(ObjOf(o),c)
//#define setBXAttrOf(o,c)        MethodOf(o)->setBXattrObj(ObjOf(o),c)
//#define setBKAttrOf(o,c)        MethodOf(o)->setBKattrObj(ObjOf(o),c)

   /* pre/post-processing */
//#define PreProcessFuncOf(w)	(ObjOf(w)->preProcessFunction)
//#define PreProcessDataOf(w)	(ObjOf(w)->preProcessData)
//#define PostProcessFuncOf(w)	(ObjOf(w)->postProcessFunction)
//#define PostProcessDataOf(w)	(ObjOf(w)->postProcessData)
/*
 * Position within the data area of a widget, accounting for border and title.
 */
//#define SCREEN_XPOS(w,n)((n) + BorderOf(w))
// #define SCREEN_XPOS(w,n)((n) + borderSize)
//#define SCREEN_YPOS(w,n)((n) + BorderOf(w) + TitleLinesOf(w))
// #define SCREEN_YPOS(w,n)((n) + borderSize + titleLines)

/* The cast is needed because traverse.c wants to use GObj pointers */
// #define ObjPtr(p)          ((GObj*)(p))

//#define MethodPtr(p,m)     ((ObjPtr(p))->fn->m)
//#define MethodPtr(p,m)     ((ObjPtr(p))->m)

/* Use these when we're certain it is a GObj pointer */
/*
#define ObjTypeOf(p)            MethodPtr(p,objectType)
#define DataTypeOf(p)           MethodPtr(p,returnType)
#define DrawObj(p)              MethodPtr(p,drawObj)         (p,p->obbox)
#define EraseObj(p)             MethodPtr(p,eraseObj)        (p)
#define DestroyObj(p)           MethodPtr(p,destroyObj)      (p)
#define InjectObj(p,k)          MethodPtr(p,injectObj)       (p,(k))
#define InputWindowObj(p)       MethodPtr(p,inputWindowObj)  (p)
#define FocusObj(p)             MethodPtr(p,focusObj)        (p)
#define UnfocusObj(p)           MethodPtr(p,unfocusObj)      (p)
#define SaveDataObj(p)          MethodPtr(p,saveDataObj)     (p)
#define RefreshDataObj(p)       MethodPtr(p,refreshDataObj)  (p)
#define SetBackAttrObj(p,c)     MethodPtr(p,setBKattrObj)    (p,c)
*/

// #define AcceptsFocusObj(p)      (ObjPtr(p)->acceptsFocus)
// #define HasFocusObj(p)          (ObjPtr(p)->hasFocus)
// #define IsVisibleObj(p)         (ObjPtr(p)->isVisible)
// #define InputWindowOf(p)        (ObjPtr(p)->inputWindow)


// #define typeCallocN(type,n)     (type*)calloc((size_t)(n), sizeof(type))
// #define typeCalloc(type)        typeCallocN(type,1)

// #define typeReallocN(type,p,n)  (type*)realloc(p,(size_t)(n) * sizeof(type))

// #define typeMallocN(type,n)     (type*)malloc((size_t)(n) * sizeof(type))
// #define typeMalloc(type)        typeMallocN(type,1)

// #define freeChecked(p)          if ((p) != 0) free(p)
// #define freeAndNull(p)          if ((p) != 0) { free(p); p = 0; }

// #define isChar(c)               ((int)(c) >= 0 && (int)(c) < KEY_MIN)
// #define CharOf(c)               ((unsigned char)(c))

// #define SIZEOF(v)               (sizeof(v)/sizeof((v)[0]))

#define MAX_COLORS		8

#define L_MARKER '<'
#define R_MARKER '>'
#define DigitOf(c) ((c)-'0')
// #define ReturnOf(p)   (ObjPtr(p)->dataPtr)

/*
 * Hide details of modifying widget->exitType
 */
// #define storeExitType(d)	ObjOf(d)->exitType =(d)->exitType
// #define initExitType(d)		storeExitType(d) = vNEVER_ACTIVATED
// #define setExitType(w,c)	setCdkExitType(ObjOf(w), &((w)->exitType), c)
// #define copyExitType(d,s)	storeExitType(d) = ExitTypeOf(s)
/*
 * Use this if checkCDKObjectBind() returns true, use this function to
 * decide if the exitType should be set as a side-effect.
 */
// #define checkEarlyExit(w)	if (EarlyExitOf(w) != vNEVER_ACTIVATED) storeExitType(w) = EarlyExitOf(w)

/*
 * Macros to check if caller is attempting to make the widget as high (or wide)
 * as the screen.
 */
#define isFullWidth(n)		((n) == FULL || (COLS != 0 &&((n) >= COLS)))
#define isFullHeight(n)		((n) == FULL || (LINES != 0 && ((n) >= LINES)))

/*
 * These set the drawing characters of the widget.
 */
// #define setCDKEntryULChar(w,c)             setULCharOf(w,c)
// #define setCDKEntryURChar(w,c)             setURCharOf(w,c)
// #define setCDKEntryLLChar(w,c)             setLLCharOf(w,c)
// #define setCDKEntryLRChar(w,c)             setLRCharOf(w,c)
// #define setCDKEntryVerticalChar(w,c)       setVTCharOf(w,c)
// #define setCDKEntryHorizontalChar(w,c)     setHZCharOf(w,c)
// #define setCDKEntryBoxAttribute(w,c)       setBXAttrOf(w,c)

/*
#if	!defined(HAVE_GETMAXYX) && !defined(getmaxyx)
#define getmaxyx(win,y,x)	(y = (win)?(win)->_maxy:ERR, x = (win)?(win)->_maxx:ERR)
#endif
*/

#define	NONUMBERS	FALSE
#define	NUMBERS		TRUE

// #define SCREENPOS(w,n) (w)->itemPos[n] - (w)->leftChar	/* + scrollbarAdj + BorderOf(w) */

// CDKOBJS wurde durch GObj ersetzt

enum EExitStatus 
{
	CDKSCREEN_NOEXIT = 0
		, CDKSCREEN_EXITOK
		, CDKSCREEN_EXITCANCEL
};

union CDKDataUnion {
   char const * valueString;
   int    valueInt;
   float  valueFloat;
   double valueDouble;
   unsigned valueUnsigned;
};

//#define unknownString   (char *)0
// #define unknownInt      (-1)
// #define unknownFloat    (0.0)
// #define unknownDouble   (0.0)
// #define unknownUnsigned (0)

/*
 * This injects a single character into the menu widget.
 */
//#define injectSObject(o,c,type)      (MethodOf(o)->injectObj    (ObjOf(o),c) ? ResultOf(o).value ## type : unknown ## type)
// #define injectSObject(/*o,*/c,type)      (injectObj    (/*ObjOf(o),*/c) ? ResultOf(this).value ## type : unknown ## type)
// #define injectSMenu(/*obj,*/input) injectSObject(/*obj,*/input,Int)

/*
 * This enumerated typedef lists all of the CDK widget types.
 */
enum EObjectType
{
	vNULL = 0
		,vALPHALIST
		,vBUTTON
		,vBUTTONBOX
		,vCALENDAR
		,vDIALOG
		,vDSCALE
		,vENTRY
		,vFSCALE
		,vFSELECT
		,vFSLIDER
		,vGRAPH
		,vHISTOGRAM
		,vITEMLIST
		,vLABEL
		,vMARQUEE
		,vMATRIX
		,vMENTRY
		,vMENU
		,vRADIO
		,vSCALE
		,vSCROLL
		,vSELECTION
		,vSLIDER
		,vSWINDOW
		,vTEMPLATE
		,vTRAVERSE
		,vUSCALE
		,vUSLIDER
		,vVIEWER
};

/*
 * This enumerated typedef lists all the valid display types for
 * the entry, mentry, and template widgets.
 */
enum EDisplayType 
{	
	vINVALID = 0
		,vCHAR
		,vHCHAR
		,vINT
		,vHINT
		,vMIXED
		,vHMIXED
		,vUCHAR
		,vLCHAR
		,vUHCHAR
		,vLHCHAR
		,vUMIXED
		,vLMIXED
		,vUHMIXED
		,vLHMIXED
		,vVIEWONLY
};

/*
 * This is the prototype for the process callback functions.
 */
typedef int(*PROCESSFN)(
		EObjectType	/* cdktype */,
		void *		/* object */,
		void *		/* clientData */,
		chtype 		/* input */);

/*
 * This is the key binding prototype, typed for use with Perl.
 */
typedef int (*BINDFN)(EObjectType,void*,void*,chtype);

struct CDKBINDING {
   BINDFN       bindFunction;
   void *       bindData;
   PROCESSFN    callbackfn;
	 CDKBINDING(BINDFN f,void* d);
	 CDKBINDING();
};

EDisplayType char2DisplayType (const char *string);
bool isHiddenDisplayType (EDisplayType type);
int filterByDisplayType (EDisplayType type, chtype input);
int isSonder(const unsigned char was);

// typedef struct _all_objects { struct _all_objects *link; GObj *object; } ALL_OBJECTS;
typedef bool(*CHECK_KEYCODE)(int /* keyCode */, int /* functionKey */);
/*
 * Define the CDK screen structure.
 */
struct SScreen 
{ // SScreen
   WINDOW *		window;
	 std::vector<GObj*> object;// GObj
   int			objectCount;	/* last-used index in object[] */
   EExitStatus		exitStatus;
   int			objectFocus;	/* focus index in object[] */
	 void eraseCDKScreen();
	 GObj* setCDKFocusNext();
	 GObj* setCDKFocusPrevious();
	 GObj* setCDKFocusCurrent(/*SScreen *screen, */GObj *newobj);
	 GObj* setCDKFocusFirst(/*SScreen *screen*/);
	 /*GObj **/void setCDKFocusLast(/*SScreen *screen*/);
	 int getFocusIndex();
	 void setFocusIndex(int value);
	 SScreen(WINDOW *window);
	 void swapCDKIndices(/*SScreen *screen, */int n1, int n2);
	 void destroyCDKScreenObjects();
	 void destroyCDKScreen();
	 GObj* getCDKFocusCurrent();
	 GObj* handleMenu(/*SScreen *screen, */GObj *menu, GObj *oldobj);
	 void saveDataCDKScreen(/*SScreen *screen*/);
	 void refreshDataCDKScreen(/*SScreen *screen*/);
	 void resetCDKScreen(/*SScreen *screen*/);
	 void exitOKCDKScreen(/*SScreen *screen*/);
	 void exitCancelCDKScreen(/*SScreen *screen*/);
	 void traverseCDKOnce(/*SScreen *screen,*/ GObj *curobj, int keyCode, bool functionKey, CHECK_KEYCODE funcMenuKey);
	 int traverseCDKScreen(/*SScreen *screen*/);
	 void popupLabel(/*SScreen *screen, */ std::vector<std::string> mesg);
	 void popupLabelAttrib(/*SScreen *screen, */ std::vector<std::string> mesg, chtype attrib);
	 virtual void refreshCDKScreen();
};

/*
 * This enumerated typedef defines the type of exits the widgets
 * recognize.
 */
enum EExitType 
{
	vEARLY_EXIT
		, vESCAPE_HIT
		, vNORMAL
		, vNEVER_ACTIVATED
		, vERROR
};

//int getmaxxf(WINDOW *win);
//int getmaxyf(WINDOW *win);

void Beep();
int floorCDK(double value);
int ceilCDK(double value);
int setWidgetDimension(int parentDim, int proposedDim, int adjustment);
//static int encodeAttribute(const char *string, int from, chtype *mask);
chtype *char2Chtype(const char *string, int *to, int *align);
int chlen(const chtype *string);
void freeChtype(chtype *string);
int justifyString(int boxWidth, int mesgLength, int justify);
void CDKfreeStrings(char **list);
void CDKfreeChtypes(chtype **list);
void alignxy(WINDOW *window, int *xpos, int *ypos, int boxWidth, int boxHeight);
void cleanChar(char *s, int len, char character);
void writeChtype(WINDOW *window, int xpos, int ypos, const chtype *const string, int align, int start, int end);
void writeChtypeAttrib(WINDOW *window, int xpos, int ypos, const chtype *const string, chtype attr, int align, int start, int end);
void attrbox(WINDOW *win, chtype tlc, chtype trc, chtype blc, chtype brc, chtype horz, chtype vert, chtype attr);
void drawShadow(WINDOW *shadowWin);
int getcCDKBind(EObjectType cdktype GCC_UNUSED, void *object GCC_UNUSED, void *clientData GCC_UNUSED, chtype input GCC_UNUSED);
void refreshCDKWindow(WINDOW *win);
void eraseCursesWindow(WINDOW *window);
void deleteCursesWindow(WINDOW *window);
void moveCursesWindow(WINDOW *window, int xdiff, int ydiff);
bool isHiddenDisplayType(EDisplayType type);
int comparSort(const void *a, const void *b);
// void sortList(CDK_CSTRING *list, int length);
/*
static int adjustAlphalistCB(EObjectType objectType GCC_UNUSED, void
			      *object GCC_UNUSED,
			      void *clientData,
			      chtype key);
static int completeWordCB(EObjectType objectType GCC_UNUSED, void *object GCC_UNUSED,
			   void *clientData,
			   chtype key GCC_UNUSED);
						*/
int searchList(std::vector<std::string> *plistp, const char *pattern);
// unsigned CDKallocStrings(char ***list, char *item, unsigned length, unsigned used);
void CDKallocStrings(std::vector<std::string> *plistp, char *item);
void writeBlanks(WINDOW *window, int xpos, int ypos, int align, int start, int end);
void writeChar(WINDOW *window, int xpos, int ypos, const char *string, int align, int start, int end);
void writeCharAttrib(WINDOW *window, int xpos, int ypos, const char *string, chtype attr, int align, int start, int end);
//static bool checkMenuKey(int keyCode, int functionKey);
GObj* switchFocus(GObj *newobj, GObj *oldobj);
int lenCharList(const char **list);
void initCDKColor(void);
void endCDK(void);
std::string errorMessage(const char *format);
void freeCharList(char **list, unsigned size);
//static int displayFileInfoCB(EObjectType objectType GCC_UNUSED, void *object, void *clientData, chtype key GCC_UNUSED);
int mode2Char(char *string, mode_t mode);

//typedef struct SScreen CDKSCREEN;

struct _all_screens
{
   struct _all_screens *link;
   SScreen *screen;
};
// ALL_SCREENS;

// chtype string
class chtstr
{
	private:
	chtype *inh;
	char *ch=0;
	size_t len;
	public:
	void gibaus() const;
//	chtstr(size_t len);
	// chtype *char2Chtypeh(const char *string, int *to, int *align, int highinr=0);
	chtstr(const char *string, int *to, int *align, const int highnr=0);
	int rauskopier(chtype **ziel);
	char *chtype2Char();
	inline chtype *getinh() const { return inh; }
	inline size_t getlen() const { return len; }
};


void registerCDKObject(SScreen *screen, EObjectType cdktype, void *object);

/*
 * Data common to all objects (widget instances).  This appears first in
 * each widget's struct to allow us to use generic functions in binding.c,
 * cdkscreen.c, position.c, etc.
 */
struct GObj
{
   SScreen *  screen;
   WINDOW *	parent;
   WINDOW *	win;
   bool      obbox;
   int       borderSize;
   bool	shadow;
   WINDOW *	shadowWin;
   int          screenIndex=-1;
	 EObjectType cdktype; 
	 //const CDKFUNCS * fn;
   bool      acceptsFocus=TRUE; // im Original nur im Menu-Widget falsch
   bool      hasFocus;
   bool      isVisible;
   WINDOW *     inputWindow;
//   void *       dataPtr=0; // wird im Original nur unter #if 0 in entry.c und itemlist verwendet
   CDKDataUnion resultData;
	 std::map<chtype,CDKBINDING> bindv;
	 std::map<chtype,CDKBINDING>::const_iterator bindvit;
   /* title-drawing */
//   chtype **	title=0;
	 std::vector<chtstr> titles;
   int *	titlePos=0;
   int *	titleLen=0;
   int		titleLines=0;
   /* line-drawing (see 'obbox') */
   chtype       ULChar;		/* lines: upper-left */
   chtype       URChar;		/* lines: upper-right */
   chtype       LLChar;		/* lines: lower-left */
   chtype       LRChar;		/* lines: lower-right */
   chtype       VTChar;		/* lines: vertical */
   chtype       HZChar;		/* lines: horizontal */
   chtype       BXAttr;
   /* events */
   EExitType	exitType;
   EExitType	earlyExit;
	 GObj *mutter=0;
	 int parentWidth;      
	 int parentHeight;     
	 int objnr=-1; // Objektnr bei Eingabefeld, wird wahrscheinlich nicht gebraucht
	 chtype *actions;
	 long actionzahl,actionnr;
	 bool hoerauf;
	 chtype holcht();
	 GObj(
			 SScreen* pscreen
			 ,WINDOW* pparent
			 ,bool obBox
			 ,bool pshadow
			 ,EObjectType pcdktype
			 ,bool pacceptsFocus
			 ,bool phasFocus
			 ,bool pisVisible
			 ,int objnr=-1
			 );
   PROCESSFN	preProcessFunction=0;
   void *	preProcessData=0;
   PROCESSFN	postProcessFunction=0;
   void *	postProcessData=0;
   // EObjectType  objectType;
   //CDKDataType  returnType;
	 virtual void drawObj(bool);
	 virtual void eraseObj();
	 virtual void destroyObj();
	 virtual void focusObj();
	 virtual void unfocusObj();
	 virtual void setFocus();
	 virtual int injectObj(chtype);
	 /*
	 virtual void moveObj(int,int,bool,bool);
	 virtual void saveDataObj();
	 virtual void refreshDataObj();
	 */
   // line-drawing 
	 virtual void setULcharObj(chtype);
	 /*
	 virtual void setURcharObj(chtype);
	 virtual void setLLcharObj(chtype);
	 virtual void setLRcharObj(chtype);
	 virtual void setVTcharObj(chtype);
	 virtual void setHZcharObj(chtype);
	 virtual void setBXattrObj(chtype);
	 */
//	 void setBox(bool Box);
   // background attribute
	 virtual void setBKattrObj(chtype);
	 void refreshDataCDK();
	 virtual void saveDataCDK();
	 void drawCDKScreen();
	 virtual GObj* bindableObject();
	 void bindCDKObject(chtype key, BINDFN function, void *data);
	 void unbindCDKObject(chtype key);
	 void cleanCDKObjectBindings();
	 int checkCDKObjectBind(chtype key);
	 bool isCDKObjectBind(chtype key);
	 //	 void setCdkExitType(chtype ch);
	 void setExitType(chtype ch);
	 void setCDKObjectPreProcess(/*GObj *obj, */PROCESSFN fn, void *data);
//	 void setCDKObjectPostProcess(/*GObj *obj, */PROCESSFN fn, void *data);
//	 GObj();
	 ~GObj();
	 void unregisterCDKObject(EObjectType cdktype/*, void *object*/);
	 void destroyCDKObject(/*GObj *obj*/);
	 int setCdkTitle(/*GObj *obj, */const char *title, int boxWidth);
	 void drawCdkTitle(WINDOW *);
	 void cleanCdkTitle();
	 bool validObjType(EObjectType type);
	 void registerCDKObject(SScreen *screen, EObjectType cdktype);
	 void reRegisterCDKObject(EObjectType cdktype/*, void *object*/);
	 void setScreenIndex(SScreen *pscreen);
	 void drawObjBox(WINDOW *win);
	 int getcCDKObject();
	 int getchCDKObject(bool *functionKey);
	 void raiseCDKObject(EObjectType cdktype/*, void *object*/);
	 void lowerCDKObject(EObjectType cdktype/*, void *object*/);
	 void unsetFocus();
//	 void exitOKCDKScreenOf(/*GObj *obj*/);
//	 void exitCancelCDKScreenOf(/*GObj *obj*/);
//	 void resetCDKScreenOf(/*GObj *obj*/);
	 void setCDKObjectBackgroundColor(/*GObj *obj, */const char *color);
}; // struct GObj

struct SEntry;
struct SScroll;
struct ComboB:GObj
{
	SEntry*	entryField;
	SScroll*	scrollField;
	int		xpos;
	int		ypos;
	int		height;
	int		width;
	chtype	highlight;
	chtype	fillerChar;
	int		boxHeight;
	int		boxWidth;
	bool zeichnescroll=1;
	GObj* bindableObject();
	ComboB(
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
			);
	 void injectMyScroller(chtype key);
	 void drawMyScroller(/*SAlphalist *widget*/);
	 void eraseObj();// {eraseCDKFselect();}
};

/*
 * Define the CDK entry widget structure.
 */

struct SEntry:GObj 
{
//   GObj	obj;
   WINDOW *	labelWin;
   WINDOW *	fieldWin;
//   chtype *	label;
	 chtstr *labelp=0;
   int		labelLen;
	 int		labelumlz; // GSchade
   int		titleAdj;
   chtype	fieldAttr;
   size_t		fieldWidth;
	 std::string efld/*info*/;
   int		infoWidth;
   int		screenCol; // Offset auf efld, wo der Cursor sitzt
   size_t    sbuch; // GSchade: Abstand des Cursors vom linken Eingabefeldrand
   int		leftChar; // Offset des links ersten sichtbaren Zeichens in efld
   size_t    lbuch; // GSchade: Zahl der links vom linken Eingabefeldrand befindlichen Buchstaben
   size_t		minlen;
   size_t		maxlen;
   int		boxWidth;
   int		boxHeight;
   void settoend(); // GSchade
	 void schreibl(chtype); // GSchade, callbackfn
   void zeichneFeld(); // GSchade
	 void setCDKEntry(/*const char **/std::string& value, int min, int max, bool Box GCC_UNUSED);
//	 const char* getCDKEntryValue();
	 void setBKattrEntry(chtype attrib);
	 void setBKattrObj(chtype);
	 void setCDKEntryHighlight(chtype highlight, bool cursor);
	 void focusCDKEntry();
	 void focusObj();
	 void unfocusCDKEntry();
	 void unfocusObj();
   EDisplayType dispType;
   chtype	filler;
   chtype	hidden;
	 std::string GPasteBuffer;
	 void		*callbackData;
	 /*
		* This creates a pointer to a new CDK entry widget.
		*/
	 SEntry(
			 SScreen *	/* cdkscreen */,
			 int		/* xpos */,
			 int		/* ypos */,
			 const char *	/* title */,
			 const char *	/* labelstr */,
			 chtype		/* fieldAttrib */,
			 chtype		/* filler */,
			 EDisplayType	/* disptype */,
			 int		/* fWidth */,
			 int		/* min */,
			 int		/* max */,
			 bool   /* Box */,
			 bool		/* shadow */,
			 // GSchade 17.11.18
			 GObj *pmutter,
			 int highnr/*=0*/,
			 int aktent=-1
			 // Ende GSchade 17.11.18
			 );
	 ~SEntry();
	 void destroyObj();
	 void drawCDKEntry(bool);
	 void drawObj(bool Box);
	 void cleanCDKEntry();
	 int injectSEntry(chtype);
	 int injectObj(chtype ch);
	 void setCDKEntryValue(std::string newValue);
//	 void setCDKEntryValue(const char *newValue);
	 void eraseCDKEntry();
	 void eraseObj();
	 const char *activateCDKEntry(/*SFSelect *fselect, */chtype *actions,int (&WeitereZc)[6],int obpfeil=0);
	 void moveCDKEntry(int,int,bool,bool);
	 void (SEntry::*callbfn)(chtype character)=NULL;
}; // struct SEntry:GObj
// typedef struct SEntry CDKENTRY;

struct SScroll_basis:public GObj 
{
	/* This field must stay on top */
//	GObj  obj; 
	WINDOW * scrollbarWin; 
	int      titleAdj;   /* unused */ 
	std::vector<chtstr> pitem;
	std::vector<chtstr>::const_iterator piter;
	std::vector<int> itemLen;
	std::vector<int> itemPos;

	int      currentTop; 
	int      currentItem; 
	int      currentHigh; 

	int      maxTopItem; 
	int      maxLeftChar; 
	int      maxchoicelen; 
	int      leftChar; 
	int      lastItem; 
	int      listSize=0; 
	int      boxWidth; 
	int      boxHeight; 
	int      viewSize; 

	int      scrollbarPlacement; 
	bool  scrollbar; 
	int      toggleSize; /* size of scrollbar thumb/toggle */ 
	int      togglePos; /* position of scrollbar thumb/toggle */ 
	float    step; /* increment for scrollbar */ 

	chtype   highlight;
	void updateViewWidth(int widest);
	int MaxViewSize();
	void SetPosition(int item);
	void scroll_KEY_HOME();
	void scroll_KEY_END();
	void scroll_FixCursorPosition();
	void scroll_KEY_UP();
	void scroll_KEY_DOWN();
	void scroll_KEY_LEFT();
	void scroll_KEY_RIGHT();
	void scroll_KEY_PPAGE();
	void scroll_KEY_NPAGE();
	void setViewSize(int listSize);
	SScroll_basis(
			 SScreen* pscreen
			 ,WINDOW* pparent
			 ,bool obBox
			 ,bool pshadow
			 ,EObjectType pcdktype
			 ,bool pacceptsFocus
			 ,bool phasFocus
			 ,bool pisVisible
			 ,int objnr=-1
			 );
};

/*
struct SScroller:SScroll_basis
{
};
typedef struct SScroller CDKSCROLLER;
*/

/*
 * Declare scrolling list definitions.
 */
struct SScroll:SScroll_basis 
{
	bool	numbers;	/* */
	chtype	titlehighlight;	/* */
	WINDOW	*listWin;
	SScroll(
			SScreen *	/* cdkscreen */,
			int		/* xpos */,
			int		/* ypos */,
			int		/* spos */,
			int		/* height */,
			int		/* width */,
			const char *	/* title */,
			 std::vector<std::string> *plistp,
			bool		/* numbers */,
			chtype		/* highlight */,
			GObj *mutter,
			bool		/* Box */,
			bool		/* shadow */);
	~SScroll();
	void destroyObj();
	void eraseCDKScroll/*_eraseCDKScroll*/(/*GObj *object*/);
	void eraseObj();
	int createCDKScrollItemList(bool numbers,std::vector<std::string> *plistp);
	bool allocListItem(int which, 
                                                      			int number, const char *value);
	int injectSScroll(/*GObj *object, */chtype input);
	int injectObj(chtype ch);
	void drawCDKScrollList(bool Box);
	int activateCDKScroll(chtype *actions);
	void setCDKScrollPosition(int item);
	void drawCDKScroll(bool Box,bool obmit=0);
	 void drawObj(bool Box);
	 void drawCDKScrollCurrent();
	 void moveCDKScroll(int xplace, int yplace, bool relative, bool refresh_flag);
	 void setCDKScroll(std::vector<std::string> *plistp, bool numbers, chtype hl, bool Box);
	 void setCDKScrollItems(std::vector<std::string> *plistp, bool numbers);
	 void setCDKScrollCurrentTop(/*SScroll *widget, */int item);
	 void setCDKScrollCurrent(int item);
	 void setBKattrScroll(chtype attrib);
	 void setBKattrObj(chtype attrib);
	 //void setCDKScrollBox(/*SScroll *scrollp, */bool Box);
	 //bool getCDKScrollBox();
	 void resequence(/*SScroll *scrollp*/);
	 void addCDKScrollItem(/*SScroll *scrollp,*/ const char *item);
	 void insertCDKScrollItem(/*SScroll *scrollp, */const char *item);
	 void deleteCDKScrollItem(/*SScroll *scrollp, */int position);
	 void focusCDKScroll(/*GObj *object*/);
	 void focusObj();
	 void unfocusCDKScroll(/*GObj *object*/);
	 void unfocusObj();
}; // struct SScroll:SScroll_basis
// typedef struct SScroll CDKSCROLL;


int fselectAdjustScrollCB(EObjectType objectType GCC_UNUSED, void *object GCC_UNUSED, void *clientData, chtype key);
std::string format1String(const char* format, const char *string);
std::string format1StrVal(const char* format, const char *string, int value);
std::string format1Number(const char* format, long value);
std::string format1Date(const char* format, time_t value);
//static const char *expandTilde(const char *filename);
std::string dirName(std::string path);
std::string dirName(const char* pfad);
//static char *trim1Char(char *source);
//static char *make_pathname(const char *directory, const char *filename);
int mode2Filetype(mode_t mode);
int CDKgetDirectoryContents(const char *directory, char ***list);
/*
static int preProcessEntryField(EObjectType cdktype GCC_UNUSED, void
				 *object GCC_UNUSED,
				 void *clientData,
				 chtype input);
				 */

/*
 * Define the CDK file selector widget structure.
 */
struct SFSelect:ComboB
{
	int setCDKFselectdirContents(/*SFSelect *fselect*/);
	//   GObj	obj;
	std::vector<std::string> dirContents;
	std::string pwd;
	std::string pfadname;
	chtype	fieldAttribute;
	std::string dirAttribute;
	std::string fileAttribute;
	std::string linkAttribute;
	std::string sockAttribute;
/*
 * This creates a new CDK file selector widget.
 */
// SFSelect *newCDKFselect(
	SFSelect(
		SScreen*	/* cdkscreen */,
		int		/* xpos */,
		int		/* ypos */,
		int		/* height */,
		int		/* width */,
		const char *	/* title */,
		const char *	/* label */,
		chtype		/* fieldAttribute */,
		chtype		/* fillerChar */,
		chtype		/* highlight */,
		const char *	/* dirAttributes */,
		const char *	/* fileAttributes */,
		const char *	/* linkAttribute */,
		const char *	/* sockAttribute */,
		bool		/* Box */,
		bool		/* shadow */,
		int highnr/*=0*/,
		int aktent=-1
		);
	~SFSelect();
	void moveCDKFselect(/*GObj *object, */int xplace, int yplace, bool relative, bool refresh_flag);
	 const char *activateCDKFselect(/*SFSelect *fselect, */chtype *actions,int (&WeitereZc)[6],int obpfeil=0);
	void destroyObj();
//	void eraseCDKFselect();
	 void drawCDKFselect(bool Box, bool obmitscroller=0);
	 void drawObj(bool Box);
	 void setPWD(/*SFSelect *fselect*/);
	 int injectSFselect(chtype input);
	 int injectObj(chtype ch);
	 void setCDKFselect(/*SFSelect *fselect, */const char *directory, chtype fieldAttrib, chtype filler, chtype highlight, 
			 const char *dirAttribute, const char *fileAttribute, const char *linkAttribute, const char *sockAttribute, bool Box GCC_UNUSED);
	 const char *contentToPath(/*SFSelect *fselect, */const char *content);
	 void focusCDKFileSelector();
	 void focusObj();
	 void unfocusCDKFileSelector();
	 void unfocusObj();
}; // struct SFSelect:GObj
//typedef struct SFSelect CDKFSELECT;

int completeWordCB(EObjectType objectType GCC_UNUSED, void *object GCC_UNUSED, void *clientData, chtype key GCC_UNUSED);
struct SAlphalist:ComboB
{
	 std::vector<std::string> plist;
	 SAlphalist(SScreen *cdkscreen,
			 int xplace,
			 int yplace,
			 int height,
			 int width,
			 const char *title,
			 const char *label,
			 std::vector<std::string> *plistp,
			 size_t maxlen,
			 chtype fillerChar,
			 chtype highlight,
			 bool Box,
			 bool shadow,
			 // GSchade Anfang
			 int highnr/*=0*/,
			 int aktent=-1
			 // GSchade Ende
			 );
	 ~SAlphalist();
	 void destroyObj();
	 void drawCDKAlphalist(bool Box GCC_UNUSED, bool obmitscroller=0);
	 void drawObj(bool Box);
	 void moveCDKAlphalist(int xplace, int yplace, bool relative, bool refresh_flag);
	 const char* activateCDKAlphalist(chtype *actions,int (&WeitereZc)[6],int obpfeil=0);
	 int injectSAlphalist(chtype input);
	 int injectObj(chtype ch);
//	 void eraseCDKAlphalist();
//	 void eraseObj(); //{eraseCDKAlphalist();}
	 void destroyInfo();
//	 void setCDKAlphalist(std::vector<std::string> *plistp, chtype fillerChar, chtype highlight, bool Box);
	 void setCDKAlphalistContents(std::vector<std::string> *plistp);
//	 std::vector<std::string> *getCDKAlphalistContents();
//	 int getCDKAlphalistCurrentItem();
	 void setCDKAlphalistCurrentItem(int item);
//	 void setCDKAlphalistFillerChar(chtype fillerChar);
//	 chtype getCDKAlphalistFillerChar();
//	 void setCDKAlphalistHighlight(chtype hl);
//	 chtype getCDKAlphalistHighlight();
	 void setBKattrObj(chtype attrib);
	 //	 void setCDKAlphalistBox(bool Box);
//	 bool getCDKAlphalistBox();
	 void setMyULchar(chtype character);
	 void setMyURchar(chtype character);
	 void setMyLLchar(chtype character);
	 void setMyLRchar(chtype character);
	 void setMyVTchar(chtype character);
	 void setMyHZchar(chtype character);
	 void setMyBXattr(chtype character);
	 void setMyBKattr(chtype character);
//	 void setCDKAlphalistPreProcess(PROCESSFN callback, void *data);
//	 void setCDKAlphalistPostProcess(PROCESSFN callback, void *data);
	 void focusCDKAlphalist();
	 void focusObj();
	 void unfocusCDKAlphalist();
	 void unfocusObj();
};
// typedef struct SAlphalist CDKALPHALIST;

/*
 * Define menu specific values.
 */
#define MAX_MENU_ITEMS	30
#define MAX_SUB_ITEMS	98

#ifndef INT_MIN
#define INT_MIN (-INT_MAX - 1)
#endif
#ifndef INT_MAX
#define INT_MAX 2147483647
#endif


/*
 * This draws the label.
 */
//#define drawCDKObject(/*o,*/box)           /*MethodOf(o)->*/drawObj       (/*ObjOf(o),*/box)
// #define drawCDKLabel(/*obj,*/Box) drawCDKObject(/*obj,*/Box)

/*
 * This erases the label.
 */
//#define eraseCDKObject(/*o*/)              /*MethodOf(o)->*/eraseObj      (/*ObjOf(o)*/)
//#define eraseCDKLabel(/*obj*/) eraseCDKObject(/*obj*/)


/*
 * Declare the CDK label structure.
 */
struct SLabel:GObj {
	//   GObj	obj;
	std::vector<chtstr> pinfo;
	std::vector<chtstr>::const_iterator pitinfo;
	std::vector<int> infoLen;
	std::vector<int> infoPos;
	int		xpos;
	int		ypos;
	int		rows;
	int		boxWidth;
	int		boxHeight;
	SLabel(SScreen *cdkscreen, int xplace, int yplace, std::vector<std::string> mesg , bool Box, bool shadow);
//	bool getCDKLabelBox(/*SLabel *label*/);
	void activateCDKLabel(/*SLabel *label, */chtype *actions GCC_UNUSED);
//	void setCDKLabel(/*SLabel *label, */ std::vector<std::string> mesg , bool Box);
	void setCDKLabelMessage(/*SLabel *label, */ std::vector<std::string> s_info);
	void setBKattrLabel(chtype attrib);
	void setBKattrObj(chtype attrib);
	void drawCDKLabel(/*GObj *object, */bool Box GCC_UNUSED);
	void eraseCDKLabel(/*GObj *object*/);
	void moveCDKLabel(/*GObj *object,*/ int xplace, int yplace, bool relative, bool refresh_flag);
	void destroyCDKLabel(/*GObj *object*/);
	char waitCDKLabel(/*SLabel *label, */char key);
};

/*
 * Declare definitions the dialog box may need.
 */
#define MAX_DIALOG_ROWS		50	/* unused by widgets */
#define MAX_DIALOG_BUTTONS	25	/* unused by widgets */
#define MIN_DIALOG_WIDTH	10

/*
 * Define the CDK dialog structure.
 */
struct SDialog:GObj {
	//   GObj	obj;
	std::vector<chtstr> pinfo;
	std::vector<chtstr>::const_iterator pitinfo;
	std::vector<int> infoLen;
	std::vector<int> infoPos;
	std::vector<chtstr> pbutton;
	std::vector<int> buttonLen;
	std::vector<int> buttonPos;
	int		currentButton;
	int		boxWidth;
	int		boxHeight;
	bool	separator;
	chtype	highlight;
	/*
	 * This returns a CDK dialog widget pointer.
	 */
	SDialog(SScreen* cdkscreen,int xPos,int yPos,
			std::vector<std::string> *mesg,
			std::vector<std::string> *buttonLabel,
			chtype	highlight ,
			bool		separator,
			bool		obBox,
			bool		shadow);
//	~SDialog();
	int activateCDKDialog(/*CDKDIALOG *dialog, */chtype *actions);
	int injectSDialog(/*GObj *object, */chtype input);
	void moveCDKDialog(/*GObj *object,*/
			int xplace,
			int yplace,
			bool relative,
			bool refresh_flag);
	void drawCDKDialog(/*GObj *object, */bool Box);
	void destroyCDKDialog(/*GObj *object*/);
	void eraseCDKDialog(/*GObj *object*/);
//	void setCDKDialog(/*CDKDIALOG *dialog, */chtype highlight, bool separator, bool Box);
	void setCDKDialogHighlight(/*CDKDIALOG *dialog, */chtype hi);
//	chtype getCDKDialogHighlight(/*CDKDIALOG *dialog*/);
	void setCDKDialogSeparator(/*CDKDIALOG *dialog, */bool sep);
//	bool getCDKDialogSeparator(/*CDKDIALOG *dialog*/);
//	bool getCDKDialogBox (/*CDKDIALOG *dialog*/);
	void setBKattrDialog(/*GObj *object, */chtype attrib);
	void drawCDKDialogButtons(/*CDKDIALOG *dialog*/);
	void focusCDKDialog(/*GObj *object*/);
	void unfocusCDKDialog(/*GObj *object*/);
};
